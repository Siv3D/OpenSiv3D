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

# include "Siv3DEngine.hpp"
# include "Logger/ILogger.hpp"
# include "System/ISystem.hpp"
# include "Console/IConsole.hpp"
# include "ImageFormat/IImageFormat.hpp"
# include "Window/IWindow.hpp"
# include "DragDrop/IDragDrop.hpp"
# include "Cursor/ICursor.hpp"
# include "Keyboard/IKeyboard.hpp"
# include "Mouse/IMouse.hpp"
# include "Graphics/IGraphics.hpp"

namespace s3d
{
	Siv3DEngine* Siv3DEngine::pEngine = nullptr;

	Siv3DEngine::Siv3DEngine()
	{
		pEngine = this;
	}

	Siv3DEngine::~Siv3DEngine()
	{
		m_graphics.release();
		m_mouse.release();
		m_keyboard.release();
		m_cursor.release();
		m_dragdrop.release();
		m_window.release();
		m_imageFormat.release();
		m_console.release();
		m_system.release();
		m_logger.release();

		pEngine = nullptr;
	}
}
