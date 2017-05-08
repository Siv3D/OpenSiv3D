//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "../Siv3DEngine.hpp"
# include "CSystem_Linux.hpp"
# include "../Logger/ILogger.hpp"
# include "../ImageFormat/IImageFormat.hpp"
# include "../Window/IWindow.hpp"
# include "../Profiler/IProfiler.hpp"
# include "../DragDrop/IDragDrop.hpp"
# include "../Clipboard/IClipboard.hpp"
# include "../Cursor/ICursor.hpp"
# include "../Keyboard/IKeyboard.hpp"
# include "../Mouse/IMouse.hpp"
# include "../Graphics/IGraphics.hpp"

namespace s3d
{
	CSystem_Linux::CSystem_Linux()
	{

	}

	CSystem_Linux::~CSystem_Linux()
	{

	}

	bool CSystem_Linux::init()
	{
		if (!Siv3DEngine::GetLogger()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetImageFormat()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetWindow()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetProfiler()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetDragDrop()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetClipboard()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetCursor()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetKeyboard()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetMouse()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetGraphics()->init())
		{
			return false;
		}

		Siv3DEngine::GetGraphics()->clear();

		return true;
	}

	bool CSystem_Linux::update()
	{
		m_previousEvent = m_event.exchange(0);

		if (const auto event = m_previousEvent & (WindowEvent::ExitFlag | m_exitEvent))
		{
			return false;
		}
		
		if (!Siv3DEngine::GetGraphics()->flush())
		{
			return false;
		}

		Siv3DEngine::GetProfiler()->endFrame();

		Siv3DEngine::GetGraphics()->present();

		Siv3DEngine::GetProfiler()->beginFrame();

		++m_systemFrameCount;
		++m_userFrameCount;

		const uint64 currentNanoSec = Time::GetNanosec();
		m_currentDeltaTimeSec = m_previousFrameTimeNanosec ?
			(currentNanoSec - m_previousFrameTimeNanosec) / 1'000'000'000.0 : 0.0;
		m_previousFrameTimeNanosec = currentNanoSec;

		if (!Siv3DEngine::GetWindow()->update())
		{
			return false;
		}

		Siv3DEngine::GetGraphics()->clear();

		if (!Siv3DEngine::GetDragDrop()->update())
		{
			return false;
		}

		Siv3DEngine::GetCursor()->update();

		Siv3DEngine::GetKeyboard()->update();

		Siv3DEngine::GetMouse()->update();
		
		return true;
	}

	void CSystem_Linux::reportEvent(const uint32 windowEventFlag)
	{
		m_event |= windowEventFlag;
	}

	void CSystem_Linux::setExitEvent(const uint32 windowEventFlag)
	{
		m_exitEvent = windowEventFlag;
	}

	uint32 CSystem_Linux::getPreviousEvent() const
	{
		return m_previousEvent;
	}

	uint64 CSystem_Linux::getSystemFrameCount() const noexcept
	{
		return m_systemFrameCount;
	}

	int32 CSystem_Linux::getUserFrameCount() const noexcept
	{
		return m_userFrameCount;
	}

	void CSystem_Linux::setUserFrameCount(const int32 count) noexcept
	{
		m_userFrameCount = count;
	}
	
	double CSystem_Linux::getDeltaTime() const noexcept
	{
		return m_currentDeltaTimeSec;
	}
}

# endif
