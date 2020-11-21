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

# include "GL4Renderer2DCommand.hpp"

namespace s3d
{
	GL4Renderer2DCommandManager::GL4Renderer2DCommandManager()
	{
		reset();
	}

	void GL4Renderer2DCommandManager::reset()
	{
		m_commands.clear();
		m_changes.clear();

		{
			m_draws.clear();
		}

		// Begin a new frame
		{
			m_commands.emplace_back(GL4Renderer2DCommandType::SetBuffers, 0);
			m_commands.emplace_back(GL4Renderer2DCommandType::UpdateBuffers, 0);
		}
	}

	void GL4Renderer2DCommandManager::flush()
	{
		if (m_currentDraw.indexCount)
		{
			m_commands.emplace_back(GL4Renderer2DCommandType::Draw, static_cast<uint32>(m_draws.size()));
			m_draws.push_back(m_currentDraw);
			m_currentDraw.indexCount = 0;
		}

		if (m_changes.has(GL4Renderer2DCommandType::SetBuffers))
		{
			m_commands.emplace_back(GL4Renderer2DCommandType::SetBuffers, 0);
		}

		m_changes.clear();
	}

	const Array<GL4Renderer2DCommand>& GL4Renderer2DCommandManager::getCommands() const noexcept
	{
		return m_commands;
	}

	void GL4Renderer2DCommandManager::pushUpdateBuffers(const uint32 batchIndex)
	{
		flush();

		m_commands.emplace_back(GL4Renderer2DCommandType::UpdateBuffers, batchIndex);
	}

	void GL4Renderer2DCommandManager::pushDraw(const Vertex2D::IndexType indexCount)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_currentDraw.indexCount += indexCount;
	}

	const GL4DrawCommand& GL4Renderer2DCommandManager::getDraw(const uint32 index) const noexcept
	{
		return m_draws[index];
	}
}
