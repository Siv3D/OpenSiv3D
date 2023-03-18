//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "GL4Renderer3DCommand.hpp"

namespace s3d
{
	GL4Renderer3DCommandManager::GL4Renderer3DCommandManager()
	{
		m_vsSamplerStates.fill(Array<SamplerState>{ SamplerState::Default3D });
		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			m_currentVSSamplerStates[i] = m_vsSamplerStates[i].back();
		}

		m_psSamplerStates.fill(Array<SamplerState>{ SamplerState::Default3D });
		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			m_currentPSSamplerStates[i] = m_psSamplerStates[i].back();
		}

		m_vsTextures.fill(Array<Texture::IDType>{ Texture::IDType::InvalidValue()});
		m_psTextures.fill(Array<Texture::IDType>{ Texture::IDType::InvalidValue()});
		m_meshes = { Mesh::IDType::InvalidValue() };

		reset();
	}

	void GL4Renderer3DCommandManager::reset()
	{
		// clear commands
		{
			m_commands.clear();
			m_changes.clear();
		}

		// clear buffers
		{
			m_draws.clear();
			m_drawPhongMaterials.clear();

			m_drawLine3Ds.clear();

			//	m_nullDraws.clear();
			m_blendStates = { m_blendStates.back() };
			m_rasterizerStates = { m_rasterizerStates.back() };
			m_depthStencilStates = { m_depthStencilStates.back() };

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				m_vsSamplerStates[i] = { m_vsSamplerStates[i].back() };
			}

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				m_psSamplerStates[i] = { m_psSamplerStates[i].back() };
			}

			m_scissorRects = { m_scissorRects.back() };
			m_viewports = { m_viewports.back() };
			//	m_sdfParams				= { m_sdfParams.back() };
			m_RTs = { m_RTs.back() };
			m_inputLayouts = { m_inputLayouts.back() };

			m_VSs = { VertexShader::IDType::InvalidValue() };
			m_PSs = { PixelShader::IDType::InvalidValue() };
			m_cameraTransforms = { m_cameraTransforms.back() };
			m_eyePositions = { m_eyePositions.back() };
			m_localTransforms = { m_localTransforms.back() };
			m_uvTransforms = { Float4{ 1.0f, 1.0f, 0.0f, 0.0f } };
			m_globalAmbientColors	= { m_globalAmbientColors.back() };
			m_sunDirections			= { m_sunDirections.back() };
			m_sunColors				= { m_sunColors.back() };
			m_constants.clear();
			m_constantBufferCommands.clear();
		}

		// clear reserves
		{
			m_reservedVSs.clear();
			m_reservedPSs.clear();
			m_reservedTextures.clear();
			m_reservedMeshes.clear();
		}

		// Begin a new frame
		{
			//	m_commands.emplace_back(GL4Renderer2DCommandType::SetBuffers, 0);
			//	m_commands.emplace_back(GL4Renderer2DCommandType::UpdateBuffers, 0);

			m_commands.emplace_back(GL4Renderer3DCommandType::UpdateLine3DBuffers, 0);

			m_commands.emplace_back(GL4Renderer3DCommandType::BlendState, 0);
			m_currentBlendState = m_blendStates.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::RasterizerState, 0);
			m_currentRasterizerState = m_rasterizerStates.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::DepthStencilState, 0);
			m_currentDepthStencilState = m_depthStencilStates.back();

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::VSSamplerState0) + i);
				m_commands.emplace_back(command, 0);
				m_currentVSSamplerStates[i] = m_currentVSSamplerStates.back();
			}

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::PSSamplerState0) + i);
				m_commands.emplace_back(command, 0);
				m_currentPSSamplerStates[i] = m_currentPSSamplerStates.back();
			}

			m_commands.emplace_back(GL4Renderer3DCommandType::ScissorRect, 0);
			m_currentScissorRect = m_scissorRects.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::Viewport, 0);
			m_currentViewport = m_viewports.back();

			//	m_commands.emplace_back(GL4Renderer2DCommandType::SDFParams, 0);
			//	m_currentSDFParams = m_sdfParams.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::SetRT, 0);
			m_currentRT = m_RTs.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::InputLayout, 0);
			m_currentInputLayout = m_inputLayouts.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::SetVS, 0);
			m_currentVS = VertexShader::IDType::InvalidValue();

			m_commands.emplace_back(GL4Renderer3DCommandType::SetPS, 0);
			m_currentPS = PixelShader::IDType::InvalidValue();

			m_commands.emplace_back(GL4Renderer3DCommandType::CameraTransform, 0);
			m_currentCameraTransform = m_cameraTransforms.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::EyePosition, 0);
			m_currentEyePosition = m_eyePositions.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::LocalTransform, 0);
			m_currentLocalTransform = m_localTransforms.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::UVTransform, 0);
			m_currentUVTransform = m_uvTransforms.back();

			{
				for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
				{
					const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::VSTexture0) + i);
					m_vsTextures[i] = { Texture::IDType::InvalidValue() };
					m_commands.emplace_back(command, 0);
				}
				m_currentVSTextures.fill(Texture::IDType::InvalidValue());
			}

			{
				for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
				{
					const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::PSTexture0) + i);
					m_psTextures[i] = { Texture::IDType::InvalidValue() };
					m_commands.emplace_back(command, 0);
				}
				m_currentPSTextures.fill(Texture::IDType::InvalidValue());
			}

			{
				const auto command = GL4Renderer3DCommandType::SetMesh;
				m_meshes = { Mesh::IDType::InvalidValue() };
				m_commands.emplace_back(command, 0);
				m_currentMesh = Mesh::IDType::InvalidValue();
			}

			m_commands.emplace_back(GL4Renderer3DCommandType::SetGlobalAmbientColor, 0);
			m_currentGlobalAmbientColor = m_globalAmbientColors.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::SetSunDirection, 0);
			m_currentSunDirection = m_sunDirections.back();

			m_commands.emplace_back(GL4Renderer3DCommandType::SetSunColor, 0);
			m_currentSunColor = m_sunColors.back();
		}
	}

	void GL4Renderer3DCommandManager::flush()
	{
		//if (m_currentDraw.indexCount)
		//{
		//	m_commands.emplace_back(GL4Renderer2DCommandType::Draw, static_cast<uint32>(m_draws.size()));
		//	m_draws.push_back(m_currentDraw);
		//	m_currentDraw.indexCount = 0;
		//}

		if (m_currentDrawLine3D.indexCount)
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::DrawLine3D, static_cast<uint32>(m_drawLine3Ds.size()));
			m_drawLine3Ds.push_back(m_currentDrawLine3D);
			m_currentDrawLine3D.indexCount = 0;
		}

		//if (m_changes.has(GL4Renderer2DCommandType::SetBuffers))
		//{
		//	m_commands.emplace_back(GL4Renderer2DCommandType::SetBuffers, 0);
		//}

		if (m_changes.has(GL4Renderer3DCommandType::BlendState))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::BlendState, static_cast<uint32>(m_blendStates.size()));
			m_blendStates.push_back(m_currentBlendState);
		}

		if (m_changes.has(GL4Renderer3DCommandType::RasterizerState))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::RasterizerState, static_cast<uint32>(m_rasterizerStates.size()));
			m_rasterizerStates.push_back(m_currentRasterizerState);
		}

		if (m_changes.has(GL4Renderer3DCommandType::DepthStencilState))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::DepthStencilState, static_cast<uint32>(m_depthStencilStates.size()));
			m_depthStencilStates.push_back(m_currentDepthStencilState);
		}

		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::VSSamplerState0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_vsSamplerStates[i].size()));
				m_vsSamplerStates[i].push_back(m_currentVSSamplerStates[i]);
			}
		}

		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::PSSamplerState0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_psSamplerStates[i].size()));
				m_psSamplerStates[i].push_back(m_currentPSSamplerStates[i]);
			}
		}

		if (m_changes.has(GL4Renderer3DCommandType::ScissorRect))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::ScissorRect, static_cast<uint32>(m_scissorRects.size()));
			m_scissorRects.push_back(m_currentScissorRect);
		}

		if (m_changes.has(GL4Renderer3DCommandType::Viewport))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::Viewport, static_cast<uint32>(m_viewports.size()));
			m_viewports.push_back(m_currentViewport);
		}

		//if (m_changes.has(GL4Renderer2DCommandType::SDFParams))
		//{
		//	m_commands.emplace_back(GL4Renderer2DCommandType::SDFParams, static_cast<uint32>(m_sdfParams.size()));
		//	m_sdfParams.push_back(m_currentSDFParams);
		//}

		if (m_changes.has(GL4Renderer3DCommandType::InputLayout))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::InputLayout, static_cast<uint32>(m_inputLayouts.size()));
			m_inputLayouts.push_back(m_currentInputLayout);
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetRT))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::SetRT, static_cast<uint32>(m_RTs.size()));
			m_RTs.push_back(m_currentRT);
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetVS))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::SetVS, static_cast<uint32>(m_VSs.size()));
			m_VSs.push_back(m_currentVS);
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetPS))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::SetPS, static_cast<uint32>(m_PSs.size()));
			m_PSs.push_back(m_currentPS);
		}

		if (m_changes.has(GL4Renderer3DCommandType::CameraTransform))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::CameraTransform, static_cast<uint32>(m_cameraTransforms.size()));
			m_cameraTransforms.push_back(m_currentCameraTransform);
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetConstantBuffer))
		{
			assert(not m_constantBufferCommands.isEmpty());
			m_commands.emplace_back(GL4Renderer3DCommandType::SetConstantBuffer, static_cast<uint32>(m_constantBufferCommands.size()) - 1);
		}

		if (m_changes.has(GL4Renderer3DCommandType::EyePosition))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::EyePosition, static_cast<uint32>(m_eyePositions.size()));
			m_eyePositions.push_back(m_currentEyePosition);
		}

		if (m_changes.has(GL4Renderer3DCommandType::LocalTransform))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::LocalTransform, static_cast<uint32>(m_localTransforms.size()));
			m_localTransforms.push_back(m_currentLocalTransform);
		}

		if (m_changes.has(GL4Renderer3DCommandType::UVTransform))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::UVTransform, static_cast<uint32>(m_uvTransforms.size()));
			m_uvTransforms.push_back(m_currentUVTransform);
		}

		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::VSTexture0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_vsTextures[i].size()));
				m_vsTextures[i].push_back(m_currentVSTextures[i]);
			}
		}

		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::PSTexture0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_psTextures[i].size()));
				m_psTextures[i].push_back(m_currentPSTextures[i]);
			}
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetMesh))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::SetMesh, static_cast<uint32>(m_meshes.size()));
			m_meshes.push_back(m_currentMesh);
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetGlobalAmbientColor))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::SetGlobalAmbientColor, static_cast<uint32>(m_globalAmbientColors.size()));
			m_globalAmbientColors.push_back(m_currentGlobalAmbientColor);
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetSunDirection))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::SetSunDirection, static_cast<uint32>(m_sunDirections.size()));
			m_sunDirections.push_back(m_currentSunDirection);
		}

		if (m_changes.has(GL4Renderer3DCommandType::SetSunColor))
		{
			m_commands.emplace_back(GL4Renderer3DCommandType::SetSunColor, static_cast<uint32>(m_sunColors.size()));
			m_sunColors.push_back(m_currentSunColor);
		}

		m_changes.clear();
	}

	bool GL4Renderer3DCommandManager::hasDraw() const noexcept
	{
		return ((not m_draws.isEmpty())
			|| (not m_drawLine3Ds.isEmpty()));
	}

	const Array<GL4Renderer3DCommand>& GL4Renderer3DCommandManager::getCommands() const noexcept
	{
		return m_commands;
	}

	void GL4Renderer3DCommandManager::pushUpdateLine3DBuffers(uint32 batchIndex)
	{
		flush();

		m_commands.emplace_back(GL4Renderer3DCommandType::UpdateLine3DBuffers, batchIndex);
	}

	void GL4Renderer3DCommandManager::pushDraw(const uint32 startIndex, const uint32 indexCount, const PhongMaterialInternal& material, const uint32 instanceCount)
	{
		// [Siv3D ToDo]
		assert(instanceCount == 1);

		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_commands.emplace_back(GL4Renderer3DCommandType::Draw, static_cast<uint32>(m_draws.size()));
		m_draws.push_back({ startIndex, indexCount, instanceCount });
		m_drawPhongMaterials.push_back(material);
		m_changes.set(GL4Renderer3DCommandType::Draw);
	}

	//void GL4Renderer2DCommandManager::pushUpdateBuffers(const uint32 batchIndex)
	//{
	//	flush();

	//	m_commands.emplace_back(GL4Renderer2DCommandType::UpdateBuffers, batchIndex);
	//}

	const GL4Draw3DCommand& GL4Renderer3DCommandManager::getDraw(const uint32 index) const noexcept
	{
		return m_draws[index];
	}

	const PhongMaterialInternal& GL4Renderer3DCommandManager::getDrawPhongMaterial(const uint32 index) const noexcept
	{
		return m_drawPhongMaterials[index];
	}

	void GL4Renderer3DCommandManager::pushDrawLine3D(VertexLine3D::IndexType indexCount)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_currentDrawLine3D.indexCount += indexCount;
	}

	const GL4DrawLine3DCommand& GL4Renderer3DCommandManager::getDrawLine3D(uint32 index) const noexcept
	{
		return m_drawLine3Ds[index];
	}

	//void GL4Renderer2DCommandManager::pushNullVertices(const uint32 count)
	//{
	//	if (m_changes.hasStateChange())
	//	{
	//		flush();
	//	}

	//	m_commands.emplace_back(GL4Renderer2DCommandType::DrawNull, static_cast<uint32>(m_nullDraws.size()));
	//	m_nullDraws.push_back(count);
	//	m_changes.set(GL4Renderer2DCommandType::DrawNull);
	//}

	//uint32 GL4Renderer2DCommandManager::getNullDraw(const uint32 index) const noexcept
	//{
	//	return m_nullDraws[index];
	//}

	void GL4Renderer3DCommandManager::pushBlendState(const BlendState& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::BlendState;
		auto& current = m_currentBlendState;
		auto& buffer = m_blendStates;

		if (not m_changes.has(command))
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

	const BlendState& GL4Renderer3DCommandManager::getBlendState(const uint32 index) const
	{
		return m_blendStates[index];
	}

	const BlendState& GL4Renderer3DCommandManager::getCurrentBlendState() const
	{
		return m_currentBlendState;
	}

	void GL4Renderer3DCommandManager::pushRasterizerState(const RasterizerState& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::RasterizerState;
		auto& current = m_currentRasterizerState;
		auto& buffer = m_rasterizerStates;

		if (not m_changes.has(command))
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

	const RasterizerState& GL4Renderer3DCommandManager::getRasterizerState(const uint32 index) const
	{
		return m_rasterizerStates[index];
	}

	const RasterizerState& GL4Renderer3DCommandManager::getCurrentRasterizerState() const
	{
		return m_currentRasterizerState;
	}

	void GL4Renderer3DCommandManager::pushDepthStencilState(const DepthStencilState& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::DepthStencilState;
		auto& current = m_currentDepthStencilState;
		auto& buffer = m_depthStencilStates;

		if (not m_changes.has(command))
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

	const DepthStencilState& GL4Renderer3DCommandManager::getDepthStencilState(const uint32 index) const
	{
		return m_depthStencilStates[index];
	}

	const DepthStencilState& GL4Renderer3DCommandManager::getCurrentDepthStencilState() const
	{
		return m_currentDepthStencilState;
	}

	void GL4Renderer3DCommandManager::pushVSSamplerState(const SamplerState& state, const uint32 slot)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::VSSamplerState0) + slot);
		auto& current = m_currentVSSamplerStates[slot];
		auto& buffer = m_vsSamplerStates[slot];

		if (not m_changes.has(command))
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

	const SamplerState& GL4Renderer3DCommandManager::getVSSamplerState(const uint32 slot, const uint32 index) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_vsSamplerStates[slot][index];
	}

	const SamplerState& GL4Renderer3DCommandManager::getVSCurrentSamplerState(const uint32 slot) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_currentVSSamplerStates[slot];
	}

	void GL4Renderer3DCommandManager::pushPSSamplerState(const SamplerState& state, const uint32 slot)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::PSSamplerState0) + slot);
		auto& current = m_currentPSSamplerStates[slot];
		auto& buffer = m_psSamplerStates[slot];

		if (not m_changes.has(command))
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

	const SamplerState& GL4Renderer3DCommandManager::getPSSamplerState(const uint32 slot, const uint32 index) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_psSamplerStates[slot][index];
	}

	const SamplerState& GL4Renderer3DCommandManager::getPSCurrentSamplerState(const uint32 slot) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_currentPSSamplerStates[slot];
	}

	void GL4Renderer3DCommandManager::pushScissorRect(const Rect& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::ScissorRect;
		auto& current = m_currentScissorRect;
		auto& buffer = m_scissorRects;

		if (not m_changes.has(command))
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

	const Rect& GL4Renderer3DCommandManager::getScissorRect(const uint32 index) const
	{
		return m_scissorRects[index];
	}

	const Rect& GL4Renderer3DCommandManager::getCurrentScissorRect() const
	{
		return m_currentScissorRect;
	}

	void GL4Renderer3DCommandManager::pushViewport(const Optional<Rect>& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::Viewport;
		auto& current = m_currentViewport;
		auto& buffer = m_viewports;

		if (not m_changes.has(command))
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

	const Optional<Rect>& GL4Renderer3DCommandManager::getViewport(const uint32 index) const
	{
		return m_viewports[index];
	}

	const Optional<Rect>& GL4Renderer3DCommandManager::getCurrentViewport() const
	{
		return m_currentViewport;
	}

	//void GL4Renderer2DCommandManager::pushSDFParameters(const std::array<Float4, 3>& state)
	//{
	//	constexpr auto command = GL4Renderer2DCommandType::SDFParams;
	//	auto& current = m_currentSDFParams;
	//	auto& buffer = m_sdfParams;

	//	if (not m_changes.has(command))
	//	{
	//		if (state != current)
	//		{
	//			current = state;
	//			m_changes.set(command);
	//		}
	//	}
	//	else
	//	{
	//		if (state == buffer.back())
	//		{
	//			current = state;
	//			m_changes.clear(command);
	//		}
	//		else
	//		{
	//			current = state;
	//		}
	//	}
	//}

	//const std::array<Float4, 3>& GL4Renderer2DCommandManager::getSDFParameters(const uint32 index) const
	//{
	//	return m_sdfParams[index];
	//}

	//const std::array<Float4, 3>& GL4Renderer2DCommandManager::getCurrentSDFParameters() const
	//{
	//	return m_currentSDFParams;
	//}


	void GL4Renderer3DCommandManager::pushInputLayout(GL4InputLayout3D state)
	{
		constexpr auto command = GL4Renderer3DCommandType::InputLayout;
		auto& current = m_currentInputLayout;
		auto& buffer = m_inputLayouts;

		if (not m_changes.has(command))
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

	const GL4InputLayout3D& GL4Renderer3DCommandManager::getInputLayout(uint32 index) const
	{
		return m_inputLayouts[index];
	}

	const GL4InputLayout3D& GL4Renderer3DCommandManager::getCurrentInputLayout() const
	{
		return m_currentInputLayout;
	}

	void GL4Renderer3DCommandManager::pushStandardVS(const VertexShader::IDType& id)
	{
		constexpr auto command = GL4Renderer3DCommandType::SetVS;
		auto& current = m_currentVS;
		auto& buffer = m_VSs;

		if (not m_changes.has(command))
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

	void GL4Renderer3DCommandManager::pushCustomVS(const VertexShader& vs)
	{
		const auto id = vs.id();
		constexpr auto command = GL4Renderer3DCommandType::SetVS;
		auto& current = m_currentVS;
		auto& buffer = m_VSs;

		if (not m_changes.has(command))
		{
			if (id != current)
			{
				current = id;
				m_changes.set(command);
				m_reservedVSs.try_emplace(id, vs);
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
				m_reservedVSs.try_emplace(id, vs);
			}
		}
	}

	const VertexShader::IDType& GL4Renderer3DCommandManager::getVS(const uint32 index) const
	{
		return m_VSs[index];
	}

	void GL4Renderer3DCommandManager::pushStandardPS(const PixelShader::IDType& id)
	{
		constexpr auto command = GL4Renderer3DCommandType::SetPS;
		auto& current = m_currentPS;
		auto& buffer = m_PSs;

		if (not m_changes.has(command))
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

	void GL4Renderer3DCommandManager::pushCustomPS(const PixelShader& ps)
	{
		const auto id = ps.id();
		constexpr auto command = GL4Renderer3DCommandType::SetPS;
		auto& current = m_currentPS;
		auto& buffer = m_PSs;

		if (not m_changes.has(command))
		{
			if (id != current)
			{
				current = id;
				m_changes.set(command);
				m_reservedPSs.try_emplace(id, ps);
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
				m_reservedPSs.try_emplace(id, ps);
			}
		}
	}

	const PixelShader::IDType& GL4Renderer3DCommandManager::getPS(const uint32 index) const
	{
		return m_PSs[index];
	}

	void GL4Renderer3DCommandManager::pushCameraTransform(const Mat4x4& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::CameraTransform;
		auto& current = m_currentCameraTransform;
		auto& buffer = m_cameraTransforms;

		if (not m_changes.has(command))
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

	const Mat4x4& GL4Renderer3DCommandManager::getCurrentCameraTransform() const
	{
		return m_currentCameraTransform;
	}

	const Mat4x4& GL4Renderer3DCommandManager::getCameraTransform(const uint32 index) const
	{
		return m_cameraTransforms[index];
	}

	void GL4Renderer3DCommandManager::pushEyePosition(const Float3& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::EyePosition;
		auto& current = m_currentEyePosition;
		auto& buffer = m_eyePositions;

		if (not m_changes.has(command))
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

	const Float3& GL4Renderer3DCommandManager::getCurrentEyePosition() const
	{
		return m_currentEyePosition;
	}

	const Float3& GL4Renderer3DCommandManager::getEyePosition(const uint32 index) const
	{
		return m_eyePositions[index];
	}

	void GL4Renderer3DCommandManager::pushLocalTransform(const Mat4x4& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::LocalTransform;
		auto& current = m_currentLocalTransform;
		auto& buffer = m_localTransforms;

		if (not m_changes.has(command))
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

	const Mat4x4& GL4Renderer3DCommandManager::getCurrentLocalTransform() const
	{
		return m_currentLocalTransform;
	}

	const Mat4x4& GL4Renderer3DCommandManager::getLocalTransform(uint32 index) const
	{
		return m_localTransforms[index];
	}

	void GL4Renderer3DCommandManager::pushUVTransform(const Float4& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::UVTransform;
		auto& current = m_currentUVTransform;
		auto& buffer = m_uvTransforms;

		if (not m_changes.has(command))
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

	const Float4& GL4Renderer3DCommandManager::getCurrentUVTransform() const
	{
		return m_currentUVTransform;
	}

	const Float4& GL4Renderer3DCommandManager::getUVTransform(const uint32 index) const
	{
		return m_uvTransforms[index];
	}

	void GL4Renderer3DCommandManager::pushConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
	{
		constexpr auto command = GL4Renderer3DCommandType::SetConstantBuffer;

		flush();
		const __m128* pData = reinterpret_cast<const __m128*>(data);
		const uint32 offset = static_cast<uint32>(m_constants.size());
		m_constants.insert(m_constants.end(), pData, (pData + num_vectors));

		GL4ConstantBuffer3DCommand cb
		{
			.stage = stage,
			.slot = slot,
			.offset = offset,
			.num_vectors = num_vectors,
			.cbBase = buffer
		};

		m_constantBufferCommands.push_back(cb);
		m_changes.set(command);
	}

	GL4ConstantBuffer3DCommand& GL4Renderer3DCommandManager::getConstantBuffer(const uint32 index)
	{
		return m_constantBufferCommands[index];
	}

	const __m128* GL4Renderer3DCommandManager::getConstantBufferPtr(const uint32 offset) const
	{
		return (m_constants.data() + offset);
	}

	void GL4Renderer3DCommandManager::pushVSTextureUnbind(const uint32 slot)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto id = Texture::IDType::InvalidValue();
		const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::VSTexture0) + slot);
		auto& current = m_currentVSTextures[slot];
		auto& buffer = m_vsTextures[slot];

		if (not m_changes.has(command))
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

	void GL4Renderer3DCommandManager::pushVSTexture(const uint32 slot, const Texture& texture)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto id = texture.id();
		const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::VSTexture0) + slot);
		auto& current = m_currentVSTextures[slot];
		auto& buffer = m_vsTextures[slot];

		if (not m_changes.has(command))
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

	const Texture::IDType& GL4Renderer3DCommandManager::getVSTexture(const uint32 slot, const uint32 index) const
	{
		return m_vsTextures[slot][index];
	}

	const std::array<Texture::IDType, SamplerState::MaxSamplerCount>& GL4Renderer3DCommandManager::getCurrentVSTextures() const
	{
		return m_currentVSTextures;
	}

	void GL4Renderer3DCommandManager::pushPSTextureUnbind(const uint32 slot)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto id = Texture::IDType::InvalidValue();
		const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::PSTexture0) + slot);
		auto& current = m_currentPSTextures[slot];
		auto& buffer = m_psTextures[slot];

		if (not m_changes.has(command))
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

	void GL4Renderer3DCommandManager::pushPSTexture(const uint32 slot, const Texture& texture)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto id = texture.id();
		const auto command = ToEnum<GL4Renderer3DCommandType>(FromEnum(GL4Renderer3DCommandType::PSTexture0) + slot);
		auto& current = m_currentPSTextures[slot];
		auto& buffer = m_psTextures[slot];

		if (not m_changes.has(command))
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

	const Texture::IDType& GL4Renderer3DCommandManager::getPSTexture(const uint32 slot, const uint32 index) const
	{
		return m_psTextures[slot][index];
	}

	const std::array<Texture::IDType, SamplerState::MaxSamplerCount>& GL4Renderer3DCommandManager::getCurrentPSTextures() const
	{
		return m_currentPSTextures;
	}

	void GL4Renderer3DCommandManager::pushRT(const Optional<RenderTexture>& rt)
	{
		constexpr auto command = GL4Renderer3DCommandType::SetRT;
		auto& current = m_currentRT;
		auto& buffer = m_RTs;

		if (!m_changes.has(command))
		{
			if (rt != current)
			{
				current = rt;
				m_changes.set(command);
			}
		}
		else
		{
			if (rt == buffer.back())
			{
				current = rt;
				m_changes.clear(command);
			}
			else
			{
				current = rt;
			}
		}
	}

	const Optional<RenderTexture>& GL4Renderer3DCommandManager::getRT(const uint32 index) const
	{
		return m_RTs[index];
	}

	const Optional<RenderTexture>& GL4Renderer3DCommandManager::getCurrentRT() const
	{
		return m_currentRT;
	}

	void GL4Renderer3DCommandManager::pushMeshUnbind()
	{
		const auto id = Mesh::IDType::InvalidValue();
		const auto command = GL4Renderer3DCommandType::SetMesh;
		auto& current = m_currentMesh;
		auto& buffer = m_meshes;

		if (not m_changes.has(command))
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

	void GL4Renderer3DCommandManager::pushMesh(const Mesh& mesh)
	{
		const auto id = mesh.id();
		constexpr auto command = GL4Renderer3DCommandType::SetMesh;
		auto& current = m_currentMesh;
		auto& buffer = m_meshes;

		if (not m_changes.has(command))
		{
			if (id != current)
			{
				current = id;
				m_changes.set(command);

				if (not m_reservedMeshes.contains(id))
				{
					m_reservedMeshes.emplace(id, mesh);
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

				if (not m_reservedMeshes.contains(id))
				{
					m_reservedMeshes.emplace(id, mesh);
				}
			}
		}
	}

	const Mesh::IDType& GL4Renderer3DCommandManager::getMesh(const uint32 index) const
	{
		return m_meshes[index];
	}

	const Mesh::IDType& GL4Renderer3DCommandManager::getCurrentMesh() const
	{
		return m_currentMesh;
	}

	void GL4Renderer3DCommandManager::pushGlobalAmbientColor(const Float3& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::SetGlobalAmbientColor;
		auto& current = m_currentGlobalAmbientColor;
		auto& buffer = m_globalAmbientColors;

		if (not m_changes.has(command))
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

	const Float3& GL4Renderer3DCommandManager::getCurrentGlobalAmbientColor() const
	{
		return m_currentGlobalAmbientColor;
	}

	const Float3& GL4Renderer3DCommandManager::getGlobalAmbientColor(const uint32 index) const
	{
		return m_globalAmbientColors[index];
	}

	void GL4Renderer3DCommandManager::pushSunDirection(const Float3& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::SetSunDirection;
		auto& current = m_currentSunDirection;
		auto& buffer = m_sunDirections;

		if (not m_changes.has(command))
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

	const Float3& GL4Renderer3DCommandManager::getCurrentSunDirection() const
	{
		return m_currentSunDirection;
	}

	const Float3& GL4Renderer3DCommandManager::getSunDirection(const uint32 index) const
	{
		return m_sunDirections[index];
	}

	void GL4Renderer3DCommandManager::pushSunColor(const Float3& state)
	{
		constexpr auto command = GL4Renderer3DCommandType::SetSunColor;
		auto& current = m_currentSunColor;
		auto& buffer = m_sunColors;

		if (not m_changes.has(command))
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

	const Float3& GL4Renderer3DCommandManager::getCurrentSunColor() const
	{
		return m_currentSunColor;
	}

	const Float3& GL4Renderer3DCommandManager::getSunColor(const uint32 index) const
	{
		return m_sunColors[index];
	}
}
