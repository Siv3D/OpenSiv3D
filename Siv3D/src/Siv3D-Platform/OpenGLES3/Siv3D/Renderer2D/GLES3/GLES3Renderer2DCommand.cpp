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

# include "GLES3Renderer2DCommand.hpp"

namespace s3d
{
	GLES3Renderer2DCommandManager::GLES3Renderer2DCommandManager()
	{
		reset();
	}

	void GLES3Renderer2DCommandManager::reset()
	{
		m_commands.clear();
		m_changes.clear();

		{
			m_draws.clear();
		}

		// Begin a new frame
		{
			m_commands.emplace_back(GLES3Renderer2DCommandType::SetBuffers, 0);
			m_commands.emplace_back(GLES3Renderer2DCommandType::UpdateBuffers, 0);
		}
	}

	void GLES3Renderer2DCommandManager::flush()
	{
		if (m_currentDraw.indexCount)
		{
			m_commands.emplace_back(GLES3Renderer2DCommandType::Draw, static_cast<uint32>(m_draws.size()));
			m_draws.push_back(m_currentDraw);
			m_currentDraw.indexCount = 0;
		}

		if (m_changes.has(GLES3Renderer2DCommandType::SetBuffers))
		{
			m_commands.emplace_back(GLES3Renderer2DCommandType::SetBuffers, 0);
		}
	}

	const Array<GLES3Renderer2DCommand>& GLES3Renderer2DCommandManager::getCommands() const noexcept
	{
		return m_commands;
	}

	void GLES3Renderer2DCommandManager::pushUpdateBuffers(const uint32 batchIndex)
	{
		flush();

		m_commands.emplace_back(GLES3Renderer2DCommandType::UpdateBuffers, batchIndex);
	}

	void GLES3Renderer2DCommandManager::pushDraw(const Vertex2D::IndexType indexCount)
	{
		if (m_changes.hasStateChange())
		{
			flush();
		}

		m_currentDraw.indexCount += indexCount;
	}

	const GLES3DrawCommand& GLES3Renderer2DCommandManager::getDraw(const uint32 index) const noexcept
	{
		return m_draws[index];
	}
}
