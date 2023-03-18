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

# include "MetalRenderer2DCommand.hpp"

namespace s3d
{
	MetalRenderer2DCommandManager::MetalRenderer2DCommandManager()
	{
		m_vsSamplerStates.fill(Array<SamplerState>{ SamplerState::Default2D });
		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			m_currentVSSamplerStates[i] = m_vsSamplerStates[i].back();
		}

		m_psSamplerStates.fill(Array<SamplerState>{ SamplerState::Default2D });
		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			m_currentPSSamplerStates[i] = m_psSamplerStates[i].back();
		}
		
		reset();
	}

	void MetalRenderer2DCommandManager::reset()
	{
		// clear commands
		{
			m_commands.clear();
			m_changes.clear();
		}

		// clear buffers
		{
			m_draws.clear();
			m_nullDraws.clear();
			m_colorMuls			= { m_colorMuls.back() };
			m_colorAdds			= { m_colorAdds.back() };
			m_blendStates		= { m_blendStates.back() };
			m_rasterizerStates	= { m_rasterizerStates.back() };
			
			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				m_vsSamplerStates[i] = { m_vsSamplerStates[i].back() };
			}

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				m_psSamplerStates[i] = { m_psSamplerStates[i].back() };
			}
			
			m_VSs					= { VertexShader::IDType::InvalidValue() };
			m_PSs					= { PixelShader::IDType::InvalidValue() };
			m_combinedTransforms	= { m_combinedTransforms.back() };
			m_constants.clear();
			m_constantBufferCommands.clear();
		}

		// clear reserves
		{
			m_reservedVSs.clear();
			m_reservedPSs.clear();
		}

		// Begin a new frame
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::SetBuffers, 0);
			m_commands.emplace_back(MetalRenderer2DCommandType::UpdateBuffers, 0);
			
			m_commands.emplace_back(MetalRenderer2DCommandType::ColorMul, 0);
			m_currentColorMul = m_colorMuls.front();

			m_commands.emplace_back(MetalRenderer2DCommandType::ColorAdd, 0);
			m_currentColorAdd = m_colorAdds.front();

			m_commands.emplace_back(MetalRenderer2DCommandType::BlendState, 0);
			m_currentBlendState = m_blendStates.front();

			m_commands.emplace_back(MetalRenderer2DCommandType::RasterizerState, 0);
			m_currentRasterizerState = m_rasterizerStates.front();
			
			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				const auto command = ToEnum<MetalRenderer2DCommandType>(FromEnum(MetalRenderer2DCommandType::VSSamplerState0) + i);
				m_commands.emplace_back(command, 0);
				m_currentVSSamplerStates[i] = m_currentVSSamplerStates.front();
			}

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				const auto command = ToEnum<MetalRenderer2DCommandType>(FromEnum(MetalRenderer2DCommandType::PSSamplerState0) + i);
				m_commands.emplace_back(command, 0);
				m_currentPSSamplerStates[i] = m_currentPSSamplerStates.front();
			}

			m_commands.emplace_back(MetalRenderer2DCommandType::SetVS, 0);
			m_currentVS = VertexShader::IDType::InvalidValue();

			m_commands.emplace_back(MetalRenderer2DCommandType::SetPS, 0);
			m_currentPS = PixelShader::IDType::InvalidValue();

			m_commands.emplace_back(MetalRenderer2DCommandType::Transform, 0);
			m_currentCombinedTransform = m_combinedTransforms.front();
		}
	}

	void MetalRenderer2DCommandManager::flush()
	{
		if (m_currentDraw.indexCount)
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::Draw, static_cast<uint32>(m_draws.size()));
			m_draws.push_back(m_currentDraw);
			m_currentDraw.indexCount = 0;
		}

		if (m_changes.has(MetalRenderer2DCommandType::SetBuffers))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::SetBuffers, 0);
		}

		if (m_changes.has(MetalRenderer2DCommandType::ColorMul))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::ColorMul, static_cast<uint32>(m_colorMuls.size()));
			m_colorMuls.push_back(m_currentColorMul);
		}

		if (m_changes.has(MetalRenderer2DCommandType::ColorAdd))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::ColorAdd, static_cast<uint32>(m_colorAdds.size()));
			m_colorAdds.push_back(m_currentColorAdd);
		}
		
		if (m_changes.has(MetalRenderer2DCommandType::BlendState))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::BlendState, static_cast<uint32>(m_blendStates.size()));
			m_blendStates.push_back(m_currentBlendState);
		}

		if (m_changes.has(MetalRenderer2DCommandType::RasterizerState))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::RasterizerState, static_cast<uint32>(m_rasterizerStates.size()));
			m_rasterizerStates.push_back(m_currentRasterizerState);
		}
		
		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<MetalRenderer2DCommandType>(FromEnum(MetalRenderer2DCommandType::VSSamplerState0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_vsSamplerStates[i].size()));
				m_vsSamplerStates[i].push_back(m_currentVSSamplerStates[i]);
			}
		}

		for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
		{
			const auto command = ToEnum<MetalRenderer2DCommandType>(FromEnum(MetalRenderer2DCommandType::PSSamplerState0) + i);

			if (m_changes.has(command))
			{
				m_commands.emplace_back(command, static_cast<uint32>(m_psSamplerStates[i].size()));
				m_psSamplerStates[i].push_back(m_currentPSSamplerStates[i]);
			}
		}

		if (m_changes.has(MetalRenderer2DCommandType::SetVS))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::SetVS, static_cast<uint32>(m_VSs.size()));
			m_VSs.push_back(m_currentVS);
		}

		if (m_changes.has(MetalRenderer2DCommandType::SetPS))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::SetPS, static_cast<uint32>(m_PSs.size()));
			m_PSs.push_back(m_currentPS);
		}

		if (m_changes.has(MetalRenderer2DCommandType::Transform))
		{
			m_commands.emplace_back(MetalRenderer2DCommandType::Transform, static_cast<uint32>(m_combinedTransforms.size()));
			m_combinedTransforms.push_back(m_currentCombinedTransform);
		}
		
		if (m_changes.has(MetalRenderer2DCommandType::SetConstantBuffer))
		{
			assert(not m_constantBufferCommands.isEmpty());
			m_commands.emplace_back(MetalRenderer2DCommandType::SetConstantBuffer, static_cast<uint32>(m_constantBufferCommands.size()) - 1);
		}

		m_changes.clear();
	}

	const Array<MetalRenderer2DCommand>& MetalRenderer2DCommandManager::getCommands() const noexcept
	{
		return m_commands;
	}

	void MetalRenderer2DCommandManager::pushUpdateBuffers(const uint32 batchIndex)
	{
		flush();

		m_commands.emplace_back(MetalRenderer2DCommandType::UpdateBuffers, batchIndex);
	}

	void MetalRenderer2DCommandManager::pushDraw(const Vertex2D::IndexType indexCount)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_currentDraw.indexCount += indexCount;
	}

	const MetalDrawCommand& MetalRenderer2DCommandManager::getDraw(const uint32 index) const noexcept
	{
		return m_draws[index];
	}

	void MetalRenderer2DCommandManager::pushNullVertices(const uint32 count)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_commands.emplace_back(MetalRenderer2DCommandType::DrawNull, static_cast<uint32>(m_nullDraws.size()));
		m_nullDraws.push_back(count);
		m_changes.set(MetalRenderer2DCommandType::DrawNull);
	}

	uint32 MetalRenderer2DCommandManager::getNullDraw(const uint32 index) const noexcept
	{
		return m_nullDraws[index];
	}

	void MetalRenderer2DCommandManager::pushColorMul(const Float4& color)
	{
		constexpr auto command = MetalRenderer2DCommandType::ColorMul;
		auto& current = m_currentColorMul;
		auto& buffer = m_colorMuls;

		if (not m_changes.has(command))
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

	const Float4& MetalRenderer2DCommandManager::getColorMul(const uint32 index) const
	{
		return m_colorMuls[index];
	}

	const Float4& MetalRenderer2DCommandManager::getCurrentColorMul() const
	{
		return m_currentColorMul;
	}

	void MetalRenderer2DCommandManager::pushColorAdd(const Float4& color)
	{
		constexpr auto command = MetalRenderer2DCommandType::ColorAdd;
		auto& current = m_currentColorAdd;
		auto& buffer = m_colorAdds;

		if (not m_changes.has(command))
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

	const Float4& MetalRenderer2DCommandManager::getColorAdd(const uint32 index) const
	{
		return m_colorAdds[index];
	}

	const Float4& MetalRenderer2DCommandManager::getCurrentColorAdd() const
	{
		return m_currentColorAdd;
	}

	void MetalRenderer2DCommandManager::pushBlendState(const BlendState& state)
	{
		constexpr auto command = MetalRenderer2DCommandType::BlendState;
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

	const BlendState& MetalRenderer2DCommandManager::getBlendState(const uint32 index) const
	{
		return m_blendStates[index];
	}

	const BlendState& MetalRenderer2DCommandManager::getCurrentBlendState() const
	{
		return m_currentBlendState;
	}

	void MetalRenderer2DCommandManager::pushRasterizerState(const RasterizerState& state)
	{
		constexpr auto command = MetalRenderer2DCommandType::RasterizerState;
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

	const RasterizerState& MetalRenderer2DCommandManager::getRasterizerState(const uint32 index) const
	{
		return m_rasterizerStates[index];
	}

	const RasterizerState& MetalRenderer2DCommandManager::getCurrentRasterizerState() const
	{
		return m_currentRasterizerState;
	}

	void MetalRenderer2DCommandManager::pushVSSamplerState(const SamplerState& state, const uint32 slot)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto command = ToEnum<MetalRenderer2DCommandType>(FromEnum(MetalRenderer2DCommandType::VSSamplerState0) + slot);
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

	const SamplerState& MetalRenderer2DCommandManager::getVSSamplerState(const uint32 slot, const uint32 index) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_vsSamplerStates[slot][index];
	}

	const SamplerState& MetalRenderer2DCommandManager::getVSCurrentSamplerState(const uint32 slot) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_currentVSSamplerStates[slot];
	}

	void MetalRenderer2DCommandManager::pushPSSamplerState(const SamplerState& state, const uint32 slot)
	{
		assert(slot < SamplerState::MaxSamplerCount);

		const auto command = ToEnum<MetalRenderer2DCommandType>(FromEnum(MetalRenderer2DCommandType::PSSamplerState0) + slot);
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

	const SamplerState& MetalRenderer2DCommandManager::getPSSamplerState(const uint32 slot, const uint32 index) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_psSamplerStates[slot][index];
	}

	const SamplerState& MetalRenderer2DCommandManager::getPSCurrentSamplerState(const uint32 slot) const
	{
		assert(slot < SamplerState::MaxSamplerCount);

		return m_currentPSSamplerStates[slot];
	}

	void MetalRenderer2DCommandManager::pushStandardVS(const VertexShader::IDType& id)
	{
		constexpr auto command = MetalRenderer2DCommandType::SetVS;
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

	void MetalRenderer2DCommandManager::pushCustomVS(const VertexShader& vs)
	{
		const auto id = vs.id();
		constexpr auto command = MetalRenderer2DCommandType::SetVS;
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

	const VertexShader::IDType& MetalRenderer2DCommandManager::getVS(const uint32 index) const
	{
		return m_VSs[index];
	}

	void MetalRenderer2DCommandManager::pushStandardPS(const PixelShader::IDType& id)
	{
		constexpr auto command = MetalRenderer2DCommandType::SetPS;
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

	void MetalRenderer2DCommandManager::pushCustomPS(const PixelShader& ps)
	{
		const auto id = ps.id();
		constexpr auto command = MetalRenderer2DCommandType::SetPS;
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

	const PixelShader::IDType& MetalRenderer2DCommandManager::getPS(const uint32 index) const
	{
		return m_PSs[index];
	}

	void MetalRenderer2DCommandManager::pushLocalTransform(const Mat3x2& local)
	{
		constexpr auto command = MetalRenderer2DCommandType::Transform;
		auto& currentLocal = m_currentLocalTransform;
		auto& currentCombined = m_currentCombinedTransform;
		auto& buffer = m_combinedTransforms;
		const Mat3x2 combinedTransform = local * m_currentCameraTransform;

		if (not m_changes.has(command))
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

	const Mat3x2& MetalRenderer2DCommandManager::getCurrentLocalTransform() const
	{
		return m_currentLocalTransform;
	}

	void MetalRenderer2DCommandManager::pushCameraTransform(const Mat3x2& camera)
	{
		constexpr auto command = MetalRenderer2DCommandType::Transform;
		auto& currentCamera = m_currentCameraTransform;
		auto& currentCombined = m_currentCombinedTransform;
		auto& buffer = m_combinedTransforms;
		const Mat3x2 combinedTransform = m_currentLocalTransform * camera;

		if (not m_changes.has(command))
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

	const Mat3x2& MetalRenderer2DCommandManager::getCurrentCameraTransform() const
	{
		return m_currentCameraTransform;
	}

	const Mat3x2& MetalRenderer2DCommandManager::getCombinedTransform(const uint32 index) const
	{
		return m_combinedTransforms[index];
	}

	const Mat3x2& MetalRenderer2DCommandManager::getCurrentCombinedTransform() const
	{
		return m_currentCombinedTransform;
	}

	float MetalRenderer2DCommandManager::getCurrentMaxScaling() const noexcept
	{
		return m_currentMaxScaling;
	}

	void MetalRenderer2DCommandManager::pushConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
	{
		constexpr auto command = MetalRenderer2DCommandType::SetConstantBuffer;

		flush();
		const __m128* pData = reinterpret_cast<const __m128*>(data);
		const uint32 offset = static_cast<uint32>(m_constants.size());
		m_constants.insert(m_constants.end(), pData, (pData + num_vectors));

		MetalConstantBufferCommand cb
		{
			.stage			= stage,
			.slot			= slot,
			.offset			= offset,
			.num_vectors	= num_vectors,
			.cbBase			= buffer
		};

		m_constantBufferCommands.push_back(cb);
		m_changes.set(command);
	}

	MetalConstantBufferCommand& MetalRenderer2DCommandManager::getConstantBuffer(const uint32 index)
	{
		return m_constantBufferCommands[index];
	}

	const __m128* MetalRenderer2DCommandManager::getConstantBufferPtr(const uint32 offset) const
	{
		return (m_constants.data() + offset);
	}
}
