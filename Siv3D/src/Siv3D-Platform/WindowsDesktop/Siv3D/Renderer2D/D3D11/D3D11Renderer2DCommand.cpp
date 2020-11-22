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

# include "D3D11Renderer2DCommand.hpp"

namespace s3d
{
	D3D11Renderer2DCommandManager::D3D11Renderer2DCommandManager()
	{
		reset();
	}

	void D3D11Renderer2DCommandManager::reset()
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
			m_blendStates = { m_blendStates.back() };
			m_rasterizerStates = { m_rasterizerStates.back() };
			m_VSs = { VertexShader::IDType::InvalidValue() };
			m_PSs = { PixelShader::IDType::InvalidValue() };
		}

		// clear reserves
		{
			m_reservedVSs.clear();
			m_reservedPSs.clear();
		}

		// Begin a new frame
		{
			m_commands.emplace_back(D3D11Renderer2DCommandType::SetBuffers, 0);
			m_commands.emplace_back(D3D11Renderer2DCommandType::UpdateBuffers, 0);

			m_commands.emplace_back(D3D11Renderer2DCommandType::BlendState, 0);
			m_currentBlendState = m_blendStates.front();

			m_commands.emplace_back(D3D11Renderer2DCommandType::RasterizerState, 0);
			m_currentRasterizerState = m_rasterizerStates.front();

			m_commands.emplace_back(D3D11Renderer2DCommandType::SetVS, 0);
			m_currentVS = VertexShader::IDType::InvalidValue();

			m_commands.emplace_back(D3D11Renderer2DCommandType::SetPS, 0);
			m_currentPS = PixelShader::IDType::InvalidValue();
		}
	}

	void D3D11Renderer2DCommandManager::flush()
	{
		if (m_currentDraw.indexCount)
		{
			m_commands.emplace_back(D3D11Renderer2DCommandType::Draw, static_cast<uint32>(m_draws.size()));
			m_draws.push_back(m_currentDraw);
			m_currentDraw.indexCount = 0;
		}

		if (m_changes.has(D3D11Renderer2DCommandType::SetBuffers))
		{
			m_commands.emplace_back(D3D11Renderer2DCommandType::SetBuffers, 0);
		}

		if (m_changes.has(D3D11Renderer2DCommandType::BlendState))
		{
			m_commands.emplace_back(D3D11Renderer2DCommandType::BlendState, static_cast<uint32>(m_blendStates.size()));
			m_blendStates.push_back(m_currentBlendState);
		}

		if (m_changes.has(D3D11Renderer2DCommandType::RasterizerState))
		{
			m_commands.emplace_back(D3D11Renderer2DCommandType::RasterizerState, static_cast<uint32>(m_rasterizerStates.size()));
			m_rasterizerStates.push_back(m_currentRasterizerState);
		}

		if (m_changes.has(D3D11Renderer2DCommandType::SetVS))
		{
			m_commands.emplace_back(D3D11Renderer2DCommandType::SetVS, static_cast<uint32>(m_VSs.size()));
			m_VSs.push_back(m_currentVS);
		}

		if (m_changes.has(D3D11Renderer2DCommandType::SetPS))
		{
			m_commands.emplace_back(D3D11Renderer2DCommandType::SetPS, static_cast<uint32>(m_PSs.size()));
			m_PSs.push_back(m_currentPS);
		}

		m_changes.clear();
	}

	const Array<D3D11Renderer2DCommand>& D3D11Renderer2DCommandManager::getCommands() const noexcept
	{
		return m_commands;
	}

	void D3D11Renderer2DCommandManager::pushUpdateBuffers(const uint32 batchIndex)
	{
		flush();

		m_commands.emplace_back(D3D11Renderer2DCommandType::UpdateBuffers, batchIndex);
	}

	void D3D11Renderer2DCommandManager::pushDraw(const Vertex2D::IndexType indexCount)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_currentDraw.indexCount += indexCount;
	}

	const D3D11DrawCommand& D3D11Renderer2DCommandManager::getDraw(const uint32 index) const noexcept
	{
		return m_draws[index];
	}

	void D3D11Renderer2DCommandManager::pushNullVertices(const uint32 count)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_commands.emplace_back(D3D11Renderer2DCommandType::DrawNull, static_cast<uint32>(m_nullDraws.size()));
		m_nullDraws.push_back(count);
		m_changes.set(D3D11Renderer2DCommandType::DrawNull);
	}

	uint32 D3D11Renderer2DCommandManager::getNullDraw(const uint32 index) const noexcept
	{
		return m_nullDraws[index];
	}

	void D3D11Renderer2DCommandManager::pushBlendState(const BlendState& state)
	{
		constexpr auto command = D3D11Renderer2DCommandType::BlendState;
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

	const BlendState& D3D11Renderer2DCommandManager::getBlendState(const uint32 index) const
	{
		return m_blendStates[index];
	}

	const BlendState& D3D11Renderer2DCommandManager::getCurrentBlendState() const
	{
		return m_currentBlendState;
	}

	void D3D11Renderer2DCommandManager::pushRasterizerState(const RasterizerState& state)
	{
		constexpr auto command = D3D11Renderer2DCommandType::RasterizerState;
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
	
	const RasterizerState& D3D11Renderer2DCommandManager::getRasterizerState(const uint32 index) const
	{
		return m_rasterizerStates[index];
	}

	const RasterizerState& D3D11Renderer2DCommandManager::getCurrentRasterizerState() const
	{
		return m_currentRasterizerState;
	}

	void D3D11Renderer2DCommandManager::pushStandardVS(const VertexShader::IDType& id)
	{
		constexpr auto command = D3D11Renderer2DCommandType::SetVS;
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

	void D3D11Renderer2DCommandManager::pushCustomVS(const VertexShader& vs)
	{
		const auto id = vs.id();
		constexpr auto command = D3D11Renderer2DCommandType::SetVS;
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

	const VertexShader::IDType& D3D11Renderer2DCommandManager::getVS(const uint32 index) const
	{
		return m_VSs[index];
	}

	void D3D11Renderer2DCommandManager::pushStandardPS(const PixelShader::IDType& id)
	{
		constexpr auto command = D3D11Renderer2DCommandType::SetPS;
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

	void D3D11Renderer2DCommandManager::pushCustomPS(const PixelShader& ps)
	{
		const auto id = ps.id();
		constexpr auto command = D3D11Renderer2DCommandType::SetPS;
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
	
	const PixelShader::IDType& D3D11Renderer2DCommandManager::getPS(const uint32 index) const
	{
		return m_PSs[index];
	}
}
