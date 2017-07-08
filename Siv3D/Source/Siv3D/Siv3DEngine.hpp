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

# pragma once
# include <cassert>

namespace s3d
{
	class ISiv3DLogger;
	class ISiv3DSystem;
	class ISiv3DCPU;
	class ISiv3DConsole;
	class ISiv3DImageFormat;
	class ISiv3DWindow;
	class ISiv3DProfiler;
	class ISiv3DDragDrop;
	class ISiv3DClipboard;
	class ISiv3DCursor;
	class ISiv3DKeyboard;
	class ISiv3DMouse;
	class ISiv3DTextInput;
	class ISiv3DAudioFormat;
	class ISiv3DAudio;
	class ISiv3DGraphics;
	class ISiv3DTexture;
	class ISiv3DShader;
	class ISiv3DRenderer2D;
	class ISiv3DFont;
	class ISiv3DPrint;
	class ISiv3DScreenCapture;
	class ISiv3DEffect;

	template <class Interface>
	class Siv3DComponent
	{
	private:

		Interface* pInterface = nullptr;

	public:

		Siv3DComponent()
			: pInterface(Interface::Create()) {}

		~Siv3DComponent()
		{
			assert(pInterface == nullptr);
		}

		Interface* get()
		{
			return pInterface;
		}

		void release()
		{
			delete pInterface;

			pInterface = nullptr;
		}
	};

	class Siv3DEngine
	{
	private:

		static Siv3DEngine* pEngine;

		Siv3DComponent<ISiv3DLogger> m_logger;

		Siv3DComponent<ISiv3DSystem> m_system;

		Siv3DComponent<ISiv3DCPU> m_cpu;

		Siv3DComponent<ISiv3DConsole> m_console;

		Siv3DComponent<ISiv3DImageFormat> m_imageFormat;

		Siv3DComponent<ISiv3DWindow> m_window;

		Siv3DComponent<ISiv3DProfiler> m_profiler;

		Siv3DComponent<ISiv3DDragDrop> m_dragdrop;

		Siv3DComponent<ISiv3DClipboard> m_clipboard;

		Siv3DComponent<ISiv3DCursor> m_cursor;

		Siv3DComponent<ISiv3DKeyboard> m_keyboard;

		Siv3DComponent<ISiv3DMouse> m_mouse;

		Siv3DComponent<ISiv3DTextInput> m_textInput;

		Siv3DComponent<ISiv3DAudioFormat> m_audioFormat;

		Siv3DComponent<ISiv3DAudio> m_audio;

		Siv3DComponent<ISiv3DGraphics> m_graphics;

		Siv3DComponent<ISiv3DTexture> m_texture;

		Siv3DComponent<ISiv3DShader> m_shader;

		Siv3DComponent<ISiv3DRenderer2D> m_renderer2D;

		Siv3DComponent<ISiv3DFont> m_font;

		Siv3DComponent<ISiv3DPrint> m_print;

		Siv3DComponent<ISiv3DScreenCapture> m_screenCapture;

		Siv3DComponent<ISiv3DEffect> m_effect;

	public:

		Siv3DEngine();

		~Siv3DEngine();

		static bool isActive()
		{
			return pEngine != nullptr;
		}

		static ISiv3DLogger* GetLogger()
		{
			return pEngine->m_logger.get();
		}

		static ISiv3DSystem* GetSystem()
		{
			return pEngine->m_system.get();
		}

		static ISiv3DCPU* GetCPU()
		{
			return pEngine->m_cpu.get();
		}

		static ISiv3DConsole* GetConsole()
		{
			return pEngine->m_console.get();
		}

		static ISiv3DImageFormat* GetImageFormat()
		{
			return pEngine->m_imageFormat.get();
		}
		
		static ISiv3DWindow* GetWindow()
		{
			return pEngine->m_window.get();
		}

		static ISiv3DProfiler* GetProfiler()
		{
			return pEngine->m_profiler.get();
		}

		static ISiv3DDragDrop* GetDragDrop()
		{
			return pEngine->m_dragdrop.get();
		}

		static ISiv3DClipboard* GetClipboard()
		{
			return pEngine->m_clipboard.get();
		}

		static ISiv3DCursor* GetCursor()
		{
			return pEngine->m_cursor.get();
		}

		static ISiv3DKeyboard* GetKeyboard()
		{
			return pEngine->m_keyboard.get();
		}

		static ISiv3DMouse* GetMouse()
		{
			return pEngine->m_mouse.get();
		}

		static ISiv3DTextInput* GetTextInput()
		{
			return pEngine->m_textInput.get();
		}

		static ISiv3DAudioFormat* GetAudioFormat()
		{
			return pEngine->m_audioFormat.get();
		}

		static ISiv3DAudio* GetAudio()
		{
			return pEngine->m_audio.get();
		}

		static ISiv3DGraphics* GetGraphics()
		{
			return pEngine->m_graphics.get();
		}

		static ISiv3DTexture* GetTexture()
		{
			return pEngine->m_texture.get();
		}

		static ISiv3DShader* GetShader()
		{
			return pEngine->m_shader.get();
		}

		static ISiv3DRenderer2D* GetRenderer2D()
		{
			return pEngine->m_renderer2D.get();
		}

		static ISiv3DFont* GetFont()
		{
			return pEngine->m_font.get();
		}

		static ISiv3DPrint* GetPrint()
		{
			return pEngine->m_print.get();
		}

		static ISiv3DScreenCapture* GetScreenCapture()
		{
			return pEngine->m_screenCapture.get();
		}

		static ISiv3DEffect* GetEffect()
		{
			return pEngine->m_effect.get();
		}
	};
}
