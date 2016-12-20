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

# include "../Siv3DEngine.hpp"
# include "CSystem.hpp"
# include "../Window/IWindow.hpp"

namespace s3d
{
	namespace WindowEvent
	{
		static constexpr uint32 ExitFlag = 0x10000000;
	}

	CSystem::CSystem()
	{

	}

	CSystem::~CSystem()
	{

	}

	bool CSystem::init()
	{

		return true;
	}

	void CSystem::exit()
	{
		m_event |= WindowEvent::ExitFlag;
	}

	bool CSystem::update()
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

		return true;
	}

	void CSystem::reportEvent(const uint32 windowEventFlag)
	{
		m_event |= windowEventFlag;
	}
}
