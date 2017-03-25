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
# include "../DragDrop/IDragDrop.hpp"
# include "../Cursor/ICursor.hpp"
# include "../Keyboard/IKeyboard.hpp"
# include "../Mouse/IMouse.hpp"
# include "../Graphics/IGraphics.hpp"

namespace s3d
{
	namespace WindowEvent
	{
		static constexpr uint32 ExitFlag = 0x10000000;
	}

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

		if (!Siv3DEngine::GetDragDrop()->init())
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

	void CSystem_Linux::exit()
	{
		m_event |= WindowEvent::ExitFlag;
	}

	bool CSystem_Linux::update()
	{
		m_previousEvent = m_event.exchange(0);

		if (const auto event = m_previousEvent & (WindowEvent::ExitFlag | m_exitEvent))
		{
			return false;
		}

		Siv3DEngine::GetGraphics()->present();

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
}

# endif
