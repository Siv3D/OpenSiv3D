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

# include "GLRenderer2DCommand.hpp"

namespace s3d
{
	namespace detail
	{
		static float CalculateMaxScaling(const Mat3x2& mat)
		{
			return Float2(mat._11 + mat._21, mat._12 + mat._22).length() / 1.4142135623730950488016887f;
		}
	}
	
	GLRenderer2DCommand::GLRenderer2DCommand()
	{
		m_psSamplerStates.fill(Array<SamplerState>{ SamplerState::Default2D });
		m_psTextures.fill(Array<TextureID>{ TextureID::InvalidValue()});
		
		reset();
	}
	
	void GLRenderer2DCommand::reset()
	{
		m_commands.clear();
		m_changes.reset();
		m_reservedPSs.clear();
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
		
		m_PSs = { PixelShaderID::InvalidValue() };
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
		m_currentPS = PixelShaderID::InvalidValue();
		m_currentScissorRect = m_scissorRects.front();
		m_currentViewport = m_viewports.front();
		for (size_t i = 0; i < m_currentPSTextures.size(); ++i)
		{
			m_currentPSTextures[i] = TextureID::InvalidValue();
		}
		m_currentSdfParam = m_sdfParams.front();
	}
	
	const Array<std::pair<RendererCommand, uint32>>& GLRenderer2DCommand::getList() const
	{
		return m_commands;
	}

	void GLRenderer2DCommand::flush()
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
		
		for (int32 i = 0; i < static_cast<int32>(SamplerState::MaxSamplerCount); ++i)
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
			m_commands.emplace_back(RendererCommand::SetPS, static_cast<uint32>(m_PSs.size()));
			m_PSs.push_back(m_currentPS);
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
		
		for (int32 i = 0; i < static_cast<int32>(SamplerState::MaxSamplerCount); ++i)
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
	
	void GLRenderer2DCommand::pushDraw(const uint16 indexCount)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}
		
		m_currentDraw.indexCount += indexCount;
	}
	
	const DrawCommand& GLRenderer2DCommand::getDraw(const uint32 index)
	{
		return m_draws[index];
	}
	
	void GLRenderer2DCommand::pushUpdateBuffers(const uint32 batchIndex)
	{
		flush();
		m_commands.emplace_back(RendererCommand::UpdateBuffers, batchIndex);
	}
	
	void GLRenderer2DCommand::pushColorMul(const Float4& color)
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
	
	const Float4& GLRenderer2DCommand::getColorMul(const uint32 index) const
	{
		return m_colorMuls[index];
	}
	
	const Float4& GLRenderer2DCommand::getCurrentColorMul() const
	{
		return m_currentColorMul;
	}
	
	void GLRenderer2DCommand::pushColorAdd(const Float4& color)
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
	
	const Float4& GLRenderer2DCommand::getColorAdd(const uint32 index) const
	{
		return m_colorAdds[index];
	}
	
	const Float4& GLRenderer2DCommand::getCurrentColorAdd() const
	{
		return m_currentColorAdd;
	}
	
	void GLRenderer2DCommand::pushBlendState(const BlendState& state)
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
	
	const BlendState& GLRenderer2DCommand::getBlendState(const uint32 index) const
	{
		return m_blendStates[index];
	}
	
	const BlendState& GLRenderer2DCommand::getCurrentBlendState() const
	{
		return m_currentBlendState;
	}
	
	void GLRenderer2DCommand::pushRasterizerState(const RasterizerState& state)
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
	
	const RasterizerState& GLRenderer2DCommand::getRasterizerState(const uint32 index) const
	{
		return m_rasterizerStates[index];
	}
	
	const RasterizerState& GLRenderer2DCommand::getCurrentRasterizerState() const
	{
		return m_currentRasterizerState;
	}
	
	void GLRenderer2DCommand::pushPSSamplerState(const SamplerState& state, const uint32 slot)
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
	
	const SamplerState& GLRenderer2DCommand::getPSSamplerState(const uint32 slot, const uint32 index) const
	{
		return m_psSamplerStates[slot][index];
	}
	
	const SamplerState& GLRenderer2DCommand::getPSCurrentSamplerState(const uint32 slot) const
	{
		return m_currentPSSamplerStates[slot];
	}
	
	void GLRenderer2DCommand::pushLocalTransform(const Mat3x2& local)
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
	
	const Mat3x2& GLRenderer2DCommand::getCurrentLocalTransform() const
	{
		return m_currentLocalTransform;
	}
	
	void GLRenderer2DCommand::pushCameraTransform(const Mat3x2& camera)
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
	
	const Mat3x2& GLRenderer2DCommand::getCurrentCameraTransform() const
	{
		return m_currentCameraTransform;
	}
	
	const Mat3x2& GLRenderer2DCommand::getCombinedTransform(const uint32 index) const
	{
		return m_combinedTransforms[index];
	}
	
	const Mat3x2& GLRenderer2DCommand::getCurrentCombinedTransform() const
	{
		return m_currentCombinedTransform;
	}
	
	float GLRenderer2DCommand::getCurrentMaxScaling() const noexcept
	{
		return m_currentMaxScaling;
	}
	
	void GLRenderer2DCommand::pushStandardPS(const PixelShaderID& id)
	{
		constexpr auto command = RendererCommand::SetPS;
		auto& current = m_currentPS;
		auto& buffer = m_PSs;
		
		if (!m_changes.has(command))
		{
			if (id != current)
			{
				current = id;
				m_changes.set(command);
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
			}
		}
	}
	
	void GLRenderer2DCommand::pushCustomPS(const PixelShader& ps)
	{
		const auto id = ps.id();
		constexpr auto command = RendererCommand::SetPS;
		auto& current = m_currentPS;
		auto& buffer = m_PSs;
		
		if (!m_changes.has(command))
		{
			if (id != current)
			{
				current = id;
				m_changes.set(command);
				
				if (m_reservedPSs.find(id) == m_reservedPSs.end())
				{
					m_reservedPSs.emplace(id, ps);
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
				
				if (m_reservedPSs.find(id) == m_reservedPSs.end())
				{
					m_reservedPSs.emplace(id, ps);
				}
			}
		}
	}
	
	const PixelShaderID& GLRenderer2DCommand::getPS(const uint32 index) const
	{
		return m_PSs[index];
	}
	
	void GLRenderer2DCommand::pushScissorRect(const Rect& rect)
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
	
	const Rect& GLRenderer2DCommand::getScissorRect(const uint32 index) const
	{
		return m_scissorRects[index];
	}
	
	const Rect& GLRenderer2DCommand::getCurrentScissorRect() const
	{
		return m_currentScissorRect;
	}
	
	void GLRenderer2DCommand::pushViewport(const Optional<Rect>& rect)
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
	
	const Optional<Rect>& GLRenderer2DCommand::getViewport(const uint32 index) const
	{
		return m_viewports[index];
	}
	
	const Optional<Rect>& GLRenderer2DCommand::getCurrentViewport() const
	{
		return m_currentViewport;
	}
	
	void GLRenderer2DCommand::pushPSTexture(const uint32 slot, const Texture& texture)
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
	
	const TextureID& GLRenderer2DCommand::getPSTexture(const uint32 slot, const uint32 index) const
	{
		return m_psTextures[slot][index];
	}
	
	void GLRenderer2DCommand::pushSdfParam(const Float4& param)
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
	
	const Float4& GLRenderer2DCommand::getSdfParam(const uint32 index) const
	{
		return m_sdfParams[index];
	}
	
	const Float4& GLRenderer2DCommand::getCurrentSdfParam() const
	{
		return m_currentSdfParam;
	}
}
