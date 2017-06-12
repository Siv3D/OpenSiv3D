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
# include "Profiler/IProfiler.hpp"
# include "DragDrop/IDragDrop.hpp"
# include "Clipboard/IClipboard.hpp"
# include "Cursor/ICursor.hpp"
# include "Keyboard/IKeyboard.hpp"
# include "Mouse/IMouse.hpp"
# include "TextInput/ITextInput.hpp"
# include "Graphics/IGraphics.hpp"
# include "Texture/ITexture.hpp"
# include "Shader/IShader.hpp"
# include "Renderer2D/IRenderer2D.hpp"
# include "Font/IFont.hpp"
# include "Print/IPrint.hpp"
# include "ScreenCapture/IScreenCapture.hpp"

namespace s3d
{
	Siv3DEngine* Siv3DEngine::pEngine = nullptr;

	Siv3DEngine::Siv3DEngine()
	{
		pEngine = this;
	}

	Siv3DEngine::~Siv3DEngine()
	{
		m_screenCapture.release();
		m_print.release();
		m_font.release();
		m_renderer2D.release();
		m_shader.release();
		m_texture.release();
		m_graphics.release();
		m_textInput.release();
		m_mouse.release();
		m_keyboard.release();
		m_cursor.release();
		m_clipboard.release();
		m_dragdrop.release();
		m_profiler.release();
		m_window.release();
		m_imageFormat.release();
		m_console.release();
		m_system.release();
		m_logger.release();

		pEngine = nullptr;
	}
}
