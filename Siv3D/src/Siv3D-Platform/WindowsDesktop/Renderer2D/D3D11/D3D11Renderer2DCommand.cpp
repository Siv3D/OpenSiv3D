//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "D3D11Renderer2DCommand.hpp"

namespace s3d
{
	namespace detail
	{
		static float CalculateMaxScaling(const Mat3x2& mat)
		{
			return Float2(mat._11 + mat._21, mat._12 + mat._22).length() / 1.4142135623730950488016887f;
		}
	}

	D3D11Renderer2DCommand::D3D11Renderer2DCommand()
	{
		m_psSamplerStates.fill(Array<SamplerState>{ SamplerState::Default2D });
		m_psTextures.fill(Array<TextureID>{ TextureID::InvalidValue()});

		reset();
	}

	void D3D11Renderer2DCommand::reset()
	{
		m_commands.clear();
		m_changes.reset();
		m_reservedTextures.clear();

		// Buffer リセット
		m_draws.clear();
		m_commands.emplace_back(RendererCommand::SetBuffers, 0);
		m_commands.emplace_back(RendererCommand::UpdateBuffers, 0);
		
		m_colorMuls = { m_colorMuls.back() };
		m_commands.emplace_back(RendererCommand::ColorMul, 0);

		m_colorAdds = { m_colorAdds.back() };
		m_commands.emplace_back(RendererCommand::ColorAdd, 0);

		m_blendStates = { m_blendStates.back() };
		m_commands.emplace_back(RendererCommand::BlendState, 0);

		m_rasterizerStates = { m_rasterizerStates.back() };
		m_commands.emplace_back(RendererCommand::RasterizerState, 0);

		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<RendererCommand>(FromEnum(RendererCommand::PSSamplerState0) + i);
			m_psSamplerStates[i] = { m_psSamplerStates[i].back() };
			m_commands.emplace_back(command, 0);
		}

		m_combinedTransforms = { m_combinedTransforms.back() };
		m_commands.emplace_back(RendererCommand::Transform, 0);

		m_pixelShaders = { m_pixelShaders.back() };
		m_commands.emplace_back(RendererCommand::SetPS, 0);

		m_scissorRects = { m_scissorRects.back() };
		m_commands.emplace_back(RendererCommand::ScissorRect, 0);

		m_viewports = { m_viewports.back() };
		m_commands.emplace_back(RendererCommand::Viewport, 0);

		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<RendererCommand>(FromEnum(RendererCommand::PSTexture0) + i);
			m_psTextures[i] = { TextureID::InvalidValue() };
			m_commands.emplace_back(command, 0);
		}

		m_sdfParams = { m_sdfParams.back() };
		m_commands.emplace_back(RendererCommand::SDFParam, 0);

		m_currentColorMul = m_colorMuls.front();
		m_currentColorAdd = m_colorAdds.front();
		m_currentBlendState = m_blendStates.front();
		m_currentRasterizerState = m_rasterizerStates.front();
		for (size_t i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			m_currentPSSamplerStates[i] = m_psSamplerStates[i].front();
		}
		m_currentCombinedTransform = m_combinedTransforms.front();
		m_currentPixelShader = m_pixelShaders.front();
		m_currentScissorRect = m_scissorRects.front();
		m_currentViewport = m_viewports.front();
		for (size_t i = 0; i < m_currentPSTextures.size(); ++i)
		{
			m_currentPSTextures[i] = TextureID::InvalidValue();
		}
		m_currentSdfParam = m_sdfParams.front();
	}

	const Array<std::pair<RendererCommand, uint32>>& D3D11Renderer2DCommand::getList() const
	{
		return m_commands;
	}

	void D3D11Renderer2DCommand::flush()
	{
		if (m_currentDraw.indexCount)
		{
			m_commands.emplace_back(RendererCommand::Draw, static_cast<uint32>(m_draws.size()));
			m_draws.push_back(m_currentDraw);
			m_currentDraw.indexCount = 0;
		}

		if (m_changes.has(RendererCommand::SetBuffers))
		{
			m_commands.emplace_back(RendererCommand::SetBuffers, 0);
		}

		if (m_changes.has(RendererCommand::ColorMul))
		{
			m_commands.emplace_back(RendererCommand::ColorMul, static_cast<uint32>(m_colorMuls.size()));
			m_colorMuls.push_back(m_currentColorMul);
		}

		if (m_changes.has(RendererCommand::ColorAdd))
		{
			m_commands.emplace_back(RendererCommand::ColorAdd, static_cast<uint32>(m_colorAdds.size()));
			m_colorAdds.push_back(m_currentColorAdd);
		}

		if (m_changes.has(RendererCommand::BlendState))
		{
			m_commands.emplace_back(RendererCommand::BlendState, static_cast<uint32>(m_blendStates.size()));
			m_blendStates.push_back(m_currentBlendState);
		}

		if (m_changes.has(RendererCommand::RasterizerState))
		{
			m_commands.emplace_back(RendererCommand::RasterizerState, static_cast<uint32>(m_rasterizerStates.size()));
			m_rasterizerStates.push_back(m_currentRasterizerState);
		}

		for (int32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<RendererCommand>(FromEnum(RendererCommand::PSSamplerState0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_psSamplerStates[i].size()));
				m_psSamplerStates[i].push_back(m_currentPSSamplerStates[i]);
			}
		}

		if (m_changes.has(RendererCommand::Transform))
		{
			m_commands.emplace_back(RendererCommand::Transform, static_cast<uint32>(m_combinedTransforms.size()));
			m_combinedTransforms.push_back(m_currentCombinedTransform);
		}

		if (m_changes.has(RendererCommand::SetPS))
		{
			m_commands.emplace_back(RendererCommand::SetPS, static_cast<uint32>(m_pixelShaders.size()));
			m_pixelShaders.push_back(m_currentPixelShader);
		}

		if (m_changes.has(RendererCommand::ScissorRect))
		{
			m_commands.emplace_back(RendererCommand::ScissorRect, static_cast<uint32>(m_scissorRects.size()));
			m_scissorRects.push_back(m_currentScissorRect);
		}

		if (m_changes.has(RendererCommand::Viewport))
		{
			m_commands.emplace_back(RendererCommand::Viewport, static_cast<uint32>(m_viewports.size()));
			m_viewports.push_back(m_currentViewport);
		}

		for (int32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<RendererCommand>(FromEnum(RendererCommand::PSTexture0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_psTextures[i].size()));
				m_psTextures[i].push_back(m_currentPSTextures[i]);
			}
		}

		if (m_changes.has(RendererCommand::SDFParam))
		{
			m_commands.emplace_back(RendererCommand::SDFParam, static_cast<uint32>(m_sdfParams.size()));
			m_sdfParams.push_back(m_currentSdfParam);
		}

		m_changes.reset();
	}

	void D3D11Renderer2DCommand::pushDraw(const uint16 indexCount)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_currentDraw.indexCount += indexCount;
	}

	const DrawCommand& D3D11Renderer2DCommand::getDraw(const uint32 index)
	{
		return m_draws[index];
	}

	void D3D11Renderer2DCommand::pushUpdateBuffers(const uint32 batchIndex)
	{
		flush();
		m_commands.emplace_back(RendererCommand::UpdateBuffers, batchIndex);
	}

	void D3D11Renderer2DCommand::pushColorMul(const Float4& color)
	{
		constexpr auto command = RendererCommand::ColorMul;
		auto& current = m_currentColorMul;
		auto& buffer = m_colorMuls;

		if (!m_changes.has(command))
		{
			if (color != current)
			{
				current = color;
				m_changes.set(command);
			}
		}
		else
		{
			if (color == buffer.back())
			{
				current = color;
				m_changes.clear(command);
			}
			else
			{
				current = color;
			}
		}
	}

	const Float4& D3D11Renderer2DCommand::getColorMul(const uint32 index) const
	{
		return m_colorMuls[index];
	}

	const Float4& D3D11Renderer2DCommand::getCurrentColorMul() const
	{
		return m_currentColorMul;
	}

	void D3D11Renderer2DCommand::pushColorAdd(const Float4& color)
	{
		constexpr auto command = RendererCommand::ColorAdd;
		auto& current = m_currentColorAdd;
		auto& buffer = m_colorAdds;

		if (!m_changes.has(command))
		{
			if (color != current)
			{
				current = color;
				m_changes.set(command);
			}
		}
		else
		{
			if (color == buffer.back())
			{
				current = color;
				m_changes.clear(command);
			}
			else
			{
				current = color;
			}
		}
	}

	const Float4& D3D11Renderer2DCommand::getColorAdd(const uint32 index) const
	{
		return m_colorAdds[index];
	}

	const Float4& D3D11Renderer2DCommand::getCurrentColorAdd() const
	{
		return m_currentColorAdd;
	}

	void D3D11Renderer2DCommand::pushBlendState(const BlendState& state)
	{
		constexpr auto command = RendererCommand::BlendState;
		auto& current = m_currentBlendState;
		auto& buffer = m_blendStates;

		if (!m_changes.has(command))
		{
			if (state != current)
			{
				current = state;
				m_changes.set(command);
			}
		}
		else
		{
			if (state == buffer.back())
			{
				current = state;
				m_changes.clear(command);
			}
			else
			{
				current = state;
			}
		}
	}
	
	const BlendState& D3D11Renderer2DCommand::getBlendState(const uint32 index) const
	{
		return m_blendStates[index];
	}

	const BlendState& D3D11Renderer2DCommand::getCurrentBlendState() const
	{
		return m_currentBlendState;
	}

	void D3D11Renderer2DCommand::pushRasterizerState(const RasterizerState& state)
	{
		constexpr auto command = RendererCommand::RasterizerState;
		auto& current = m_currentRasterizerState;
		auto& buffer = m_rasterizerStates;

		if (!m_changes.has(command))
		{
			if (state != current)
			{
				current = state;
				m_changes.set(command);
			}
		}
		else
		{
			if (state == buffer.back())
			{
				current = state;
				m_changes.clear(command);
			}
			else
			{
				current = state;
			}
		}
	}

	const RasterizerState& D3D11Renderer2DCommand::getRasterizerState(const uint32 index) const
	{
		return m_rasterizerStates[index];
	}

	const RasterizerState& D3D11Renderer2DCommand::getCurrentRasterizerState() const
	{
		return m_currentRasterizerState;
	}

	void D3D11Renderer2DCommand::pushPSSamplerState(const SamplerState& state, const uint32 slot)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto command = ToEnum<RendererCommand>(FromEnum(RendererCommand::PSSamplerState0) + slot);
		auto& current = m_currentPSSamplerStates[slot];
		auto& buffer = m_psSamplerStates[slot];

		if (!m_changes.has(command))
		{
			if (state != current)
			{
				current = state;
				m_changes.set(command);
			}
		}
		else
		{
			if (state == buffer.back())
			{
				current = state;
				m_changes.clear(command);
			}
			else
			{
				current = state;
			}
		}
	}

	const SamplerState& D3D11Renderer2DCommand::getPSSamplerState(const uint32 slot, const uint32 index) const
	{
		return m_psSamplerStates[slot][index];
	}

	const SamplerState& D3D11Renderer2DCommand::getPSCurrentSamplerState(const uint32 slot) const
	{
		return m_currentPSSamplerStates[slot];
	}

	void D3D11Renderer2DCommand::pushLocalTransform(const Mat3x2& local)
	{
		constexpr auto command = RendererCommand::Transform;
		auto& currentLocal = m_currentLocalTransform;
		auto& currentCombined = m_currentCombinedTransform;
		auto& buffer = m_combinedTransforms;
		const Mat3x2 combinedTransform = local * m_currentCameraTransform;

		if (!m_changes.has(command))
		{
			if (local != currentLocal)
			{
				currentLocal = local;
				currentCombined = combinedTransform;
				m_currentMaxScaling = detail::CalculateMaxScaling(combinedTransform);
				m_changes.set(command);
			}
		}
		else
		{
			if (combinedTransform == buffer.back())
			{
				currentLocal = local;
				currentCombined = combinedTransform;
				m_changes.clear(command);
			}
			else
			{
				currentLocal = local;
				currentCombined = combinedTransform;
			}

			m_currentMaxScaling = detail::CalculateMaxScaling(combinedTransform);
		}
	}

	const Mat3x2& D3D11Renderer2DCommand::getCurrentLocalTransform() const
	{
		return m_currentLocalTransform;
	}

	void D3D11Renderer2DCommand::pushCameraTransform(const Mat3x2& camera)
	{
		constexpr auto command = RendererCommand::Transform;
		auto& currentCamera = m_currentCameraTransform;
		auto& currentCombined = m_currentCombinedTransform;
		auto& buffer = m_combinedTransforms;
		const Mat3x2 combinedTransform = m_currentLocalTransform * camera;

		if (!m_changes.has(command))
		{
			if (camera != currentCamera)
			{
				currentCamera = camera;
				currentCombined = combinedTransform;
				m_currentMaxScaling = detail::CalculateMaxScaling(combinedTransform);
				m_changes.set(command);
			}
		}
		else
		{
			if (combinedTransform == buffer.back())
			{
				currentCamera = camera;
				currentCombined = combinedTransform;
				m_changes.clear(command);
			}
			else
			{
				currentCamera = camera;
				currentCombined = combinedTransform;
			}

			m_currentMaxScaling = detail::CalculateMaxScaling(combinedTransform);
		}
	}

	const Mat3x2& D3D11Renderer2DCommand::getCurrentCameraTransform() const
	{
		return m_currentCameraTransform;
	}

	const Mat3x2& D3D11Renderer2DCommand::getCombinedTransform(const uint32 index) const
	{
		return m_combinedTransforms[index];
	}

	const Mat3x2& D3D11Renderer2DCommand::getCurrentCombinedTransform() const
	{
		return m_currentCombinedTransform;
	}

	float D3D11Renderer2DCommand::getCurrentMaxScaling() const noexcept
	{
		return m_currentMaxScaling;
	}

	void D3D11Renderer2DCommand::pushPS(const size_t psIndex)
	{
		constexpr auto command = RendererCommand::SetPS;
		auto& current = m_currentPixelShader;
		auto& buffer = m_pixelShaders;

		if (!m_changes.has(command))
		{
			if (psIndex != current)
			{
				current = psIndex;
				m_changes.set(command);
			}
		}
		else
		{
			if (psIndex == buffer.back())
			{
				current = psIndex;
				m_changes.clear(command);
			}
			else
			{
				current = psIndex;
			}
		}
	}

	size_t D3D11Renderer2DCommand::getPS(const uint32 index) const
	{
		return m_pixelShaders[index];
	}

	size_t D3D11Renderer2DCommand::getCurrentPS() const
	{
		return m_currentPixelShader;
	}

	void D3D11Renderer2DCommand::pushScissorRect(const Rect& rect)
	{
		constexpr auto command = RendererCommand::ScissorRect;
		auto& current = m_currentScissorRect;
		auto& buffer = m_scissorRects;

		if (!m_changes.has(command))
		{
			if (rect != current)
			{
				current = rect;
				m_changes.set(command);
			}
		}
		else
		{
			if (rect == buffer.back())
			{
				current = rect;
				m_changes.clear(command);
			}
			else
			{
				current = rect;
			}
		}
	}

	const Rect& D3D11Renderer2DCommand::getScissorRect(const uint32 index) const
	{
		return m_scissorRects[index];
	}

	const Rect& D3D11Renderer2DCommand::getCurrentScissorRect() const
	{
		return m_currentScissorRect;
	}

	void D3D11Renderer2DCommand::pushViewport(const Optional<Rect>& rect)
	{
		constexpr auto command = RendererCommand::Viewport;
		auto& current = m_currentViewport;
		auto& buffer = m_viewports;

		if (!m_changes.has(command))
		{
			if (rect != current)
			{
				current = rect;
				m_changes.set(command);
			}
		}
		else
		{
			if (rect == buffer.back())
			{
				current = rect;
				m_changes.clear(command);
			}
			else
			{
				current = rect;
			}
		}
	}

	const Optional<Rect>& D3D11Renderer2DCommand::getViewport(const uint32 index) const
	{
		return m_viewports[index];
	}

	const Optional<Rect>& D3D11Renderer2DCommand::getCurrentViewport() const
	{
		return m_currentViewport;
	}

	void D3D11Renderer2DCommand::pushPSTexture(const uint32 slot, const Texture& texture)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto id = texture.id();
		const auto command = ToEnum<RendererCommand>(FromEnum(RendererCommand::PSTexture0) + slot);
		auto& current = m_currentPSTextures[slot];
		auto& buffer = m_psTextures[slot];

		if (!m_changes.has(command))
		{
			if (id != current)
			{
				current = id;
				m_changes.set(command);

				if (m_reservedTextures.find(id) == m_reservedTextures.end())
				{
					m_reservedTextures.emplace(id, texture);
				}
			}
		}
		else
		{
			if (id == buffer.back())
			{
				current = id;
				m_changes.clear(command);
			}
			else
			{
				current = id;

				if (m_reservedTextures.find(id) == m_reservedTextures.end())
				{
					m_reservedTextures.emplace(id, texture);
				}
			}
		}
	}

	const TextureID& D3D11Renderer2DCommand::getPSTexture(const uint32 slot, const uint32 index) const
	{
		return m_psTextures[slot][index];
	}

	void D3D11Renderer2DCommand::pushSdfParam(const Float4& param)
	{
		constexpr auto command = RendererCommand::SDFParam;
		auto& current = m_currentSdfParam;
		auto& buffer = m_sdfParams;

		if (!m_changes.has(command))
		{
			if (param != current)
			{
				current = param;
				m_changes.set(command);
			}
		}
		else
		{
			if (param == buffer.back())
			{
				current = param;
				m_changes.clear(command);
			}
			else
			{
				current = param;
			}
		}
	}

	const Float4& D3D11Renderer2DCommand::getSdfParam(const uint32 index) const
	{
		return m_sdfParams[index];
	}

	const Float4& D3D11Renderer2DCommand::getCurrentSdfParam() const
	{
		return m_currentSdfParam;
	}
}
