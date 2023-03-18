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

# include <Siv3D/String.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/GlobalAudio.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CProfiler.hpp"

namespace s3d
{
	void CProfiler::init()
	{
		LOG_SCOPED_TRACE(U"CProfiler::init()");

		m_fpsTimestampMillisec = Time::GetMillisec();
	}

	void CProfiler::beginFrame()
	{
		// FPS
		{
			if (const int64 timestampMillisec = Time::GetMillisec();
				(timestampMillisec - m_fpsTimestampMillisec) < 1000)
			{
				++m_fpsCount;
			}
			else
			{
				m_currentFPS = m_fpsCount;
				m_fpsCount = 1;
				m_fpsTimestampMillisec = timestampMillisec;
			}
		}

		// Stat
		{
			{
				const auto stat = SIV3D_ENGINE(Renderer2D)->getStat();
				m_stat.drawCalls = stat.drawCalls;
				m_stat.triangleCount = stat.triangleCount;
			}

			m_stat.textureCount	= static_cast<uint32>(SIV3D_ENGINE(Texture)->getTextureCount());
			m_stat.fontCount	= static_cast<uint32>(SIV3D_ENGINE(Font)->getFontCount());
			m_stat.audioCount	= static_cast<uint32>(SIV3D_ENGINE(Audio)->getAudioCount());
			m_stat.activeVoice	= static_cast<uint32>(GlobalAudio::GetActiveVoiceCount());
		}
	}

	void CProfiler::endFrame()
	{

	}

	int32 CProfiler::getFPS() const noexcept
	{
		return m_currentFPS;
	}

	String CProfiler::getSimpleStatistics() const
	{
		const auto state = SIV3D_ENGINE(Window)->getState();
		const Size sceneSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		return U"{} | {} FPS | F {}x{} | V {}x{} | S {}x{}"_fmt(
			SIV3D_ENGINE(Renderer)->getName(),
			m_currentFPS,
			state.frameBufferSize.x, state.frameBufferSize.y,
			state.virtualSize.x, state.virtualSize.y,
			sceneSize.x, sceneSize.y);
	}

	const ProfilerStat& CProfiler::getStat() const
	{
		return m_stat;
	}
}
