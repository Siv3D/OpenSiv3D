//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../Siv3DEngine.hpp"
# include "CSystem_Windows.hpp"
# include "../Logger/ILogger.hpp"
# include "../Window/IWindow.hpp"
# include "../DragDrop/IDragDrop.hpp"

namespace s3d
{
	namespace WindowEvent
	{
		static constexpr uint32 ExitFlag = 0x10000000;
	}

	CSystem_Windows::CSystem_Windows()
	{

	}

	CSystem_Windows::~CSystem_Windows()
	{

	}

	bool CSystem_Windows::init()
	{
		if (!Siv3DEngine::GetLogger()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetWindow()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetDragDrop()->init())
		{
			return false;
		}

		return true;
	}

	void CSystem_Windows::exit()
	{
		m_event |= WindowEvent::ExitFlag;
	}

	bool CSystem_Windows::update()
	{
		m_previousEvent = m_event.exchange(0);

		if (const auto event = m_previousEvent & (WindowEvent::ExitFlag | m_exitEvent))
		{
			return false;
		}

		if (!Siv3DEngine::GetWindow()->update())
		{
			return false;
		}

		System::Sleep(MillisecondsF(16.66));

		Siv3DEngine::GetDragDrop()->update();

		return true;
	}

	void CSystem_Windows::reportEvent(const uint32 windowEventFlag)
	{
		m_event |= windowEventFlag;
	}
}

# endif
