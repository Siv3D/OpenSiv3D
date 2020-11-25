//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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
		m_psSamplerStates.fill(Array<SamplerState>{ SamplerState::Default2D });
		
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
			m_blendStates		= { m_blendStates.back() };
			m_rasterizerStates	= { m_rasterizerStates.back() };
			
			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				m_vsSamplerStates[i] = { m_vsSamplerStates[i].back() };
			}

			for (uint32 i = 0; i < SamplerState::MaxSamplerCount; ++i)
			{
				m_vsSamplerStates[i] = { m_vsSamplerStates[i].back() };
			}
			
			m_VSs				= { VertexShader::IDType::InvalidValue() };
			m_PSs				= { PixelShader::IDType::InvalidValue() };
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
}
