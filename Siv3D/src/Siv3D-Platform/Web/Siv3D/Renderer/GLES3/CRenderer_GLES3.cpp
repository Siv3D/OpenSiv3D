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

# include "CRenderer_GLES3.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		static void GLDebugMessageARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const GLvoid* userParam)
		{
			// [Siv3D ToDo] Linux でのデバッグ用
		}
		
		static void GLDebugMessageAMD(GLuint id, GLuint category, GLenum severity, GLsizei length, const GLchar *message, GLvoid* userParam)
		{
			// [Siv3D ToDo] Linux でのデバッグ用
		}
	}

	CRenderer_GLES3::CRenderer_GLES3()
	{
	
	}

	CRenderer_GLES3::~CRenderer_GLES3()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GLES3::~CRenderer_GLES3()");
	}

	void CRenderer_GLES3::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GLES3::init()");
		
		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());
		
		::glfwMakeContextCurrent(m_window);
		::glfwSwapInterval(1);
		
		::glewExperimental = GL_TRUE;
		if (::glewInit() != GLEW_OK)
		{
			throw EngineError(U"glefInit() failed");
		}
		
		if (SIV3D_BUILD(DEBUG) && GLEW_ARB_debug_output)
		{
			::glDebugMessageCallbackARB(detail::GLDebugMessageARB, nullptr);
			LOG_INFO(U"ℹ️ GLEW_ARB_debug_output available");
		}
		else if (SIV3D_BUILD(DEBUG) && GLEW_AMD_debug_output)
		{
			::glDebugMessageCallbackAMD(detail::GLDebugMessageAMD, nullptr);
			LOG_INFO(U"ℹ️ GLEW_AMD_debug_output available");
		}
		
		const String renderer = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_RENDERER)));
		const String vendor = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_VENDOR)));
		const String version = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_VERSION)));
		const String glslVersion = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_SHADING_LANGUAGE_VERSION)));

		GLint major = 0, minor = 0;
		::glGetIntegerv(GL_MAJOR_VERSION, &major);
		::glGetIntegerv(GL_MINOR_VERSION, &minor);

		LOG_INFO(U"renderer: {}"_fmt(renderer));
		LOG_INFO(U"vendor: {}"_fmt(vendor));
		LOG_INFO(U"version: {}"_fmt(version));
		LOG_INFO(U"glslVersion: {}"_fmt(glslVersion));
		LOG_INFO(U"GL_MAJOR_VERSION: {}"_fmt(major));
		LOG_INFO(U"GL_MINOR_VERSION: {}"_fmt(minor));

		m_backBuffer = std::make_unique<GLES3BackBuffer>();
	}

	StringView CRenderer_GLES3::getName() const
	{
		static constexpr StringView name(U"OpenGL");
		return name;
	}	

	void CRenderer_GLES3::clear()
	{
		m_backBuffer->clear(GLES3ClearTarget::BackBuffer | GLES3ClearTarget::Scene);
		
		const auto& windowState = SIV3D_ENGINE(Window)->getState();

		if (const Size frameBufferSize = windowState.frameBufferSize; 
			(frameBufferSize != m_backBuffer->getBackBufferSize()))
		{
			m_backBuffer->setBackBufferSize(frameBufferSize);

			if (windowState.sizeMove)
			{
				// sleep
			}
		}	
	}

	void CRenderer_GLES3::flush()
	{
		// Scene に 2D 描画
		{
			m_backBuffer->bindSceneBuffer();
			SIV3D_ENGINE(Renderer2D)->flush();
			m_backBuffer->unbind();
		}

		// ウィンドウに Scene を描画
		{
			m_backBuffer->updateFromSceneBuffer();
		}
	}

	bool CRenderer_GLES3::present()
	{
		const bool vSync = true;
		
		if (vSync)
		{
			::glfwSwapBuffers(m_window);
		}
		else
		{
			/*
			const double targetRefreshRateHz = m_targetFrameRateHz.value();
			const double targetRefreshPeriodMillisec = (1000.0 / targetRefreshRateHz);
			*/
			::glfwSwapBuffers(m_window);
			/*
			double timeToSleepMillisec;
			double countMillisec;
			
			do
			{
				countMillisec = (Time::GetMicrosec() / 1000.0);
				const double timeSinceFlipMillisec = countMillisec - m_lastFlipTimeMillisec;
				
				timeToSleepMillisec = (targetRefreshPeriodMillisec - timeSinceFlipMillisec);
				
				if (timeToSleepMillisec > 0.0)
				{
					::usleep(static_cast<uint32>(std::floor(timeToSleepMillisec) * 1000));
				}
			} while (timeToSleepMillisec > 0.0);
			
			m_lastFlipTimeMillisec = countMillisec;
			 */
		}
		/*
		if (m_sceneTexture.hasCaptureRequest())
		{
			m_sceneTexture.capture();
		}
		*/
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			//CheckGLError();
		}
		
		return true;
	}

	void CRenderer_GLES3::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_backBuffer->setSceneResizeMode(resizeMode);
	}

	ResizeMode CRenderer_GLES3::getSceneResizeMode() const noexcept
	{
		return m_backBuffer->getSceneResizeMode();
	}

	void CRenderer_GLES3::setSceneBufferSize(const Size size)
	{
		m_backBuffer->setSceneBufferSize(size);
	}

	Size CRenderer_GLES3::getSceneBufferSize() const noexcept
	{
		return m_backBuffer->getSceneBufferSize();
	}

	void CRenderer_GLES3::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_backBuffer->setSceneTextureFilter(textureFilter);
	}

	TextureFilter CRenderer_GLES3::getSceneTextureFilter() const noexcept
	{
		return m_backBuffer->getSceneTextureFilter();
	}

	void CRenderer_GLES3::setBackgroundColor(const ColorF& color)
	{
		m_backBuffer->setBackgroundColor(color);
	}

	const ColorF& CRenderer_GLES3::getBackgroundColor() const noexcept
	{
		return m_backBuffer->getBackgroundColor();
	}

	void CRenderer_GLES3::setLetterboxColor(const ColorF& color)
	{
		m_backBuffer->setLetterboxColor(color);
	}

	const ColorF& CRenderer_GLES3::getLetterboxColor() const noexcept
	{
		return m_backBuffer->getLetterBoxColor();
	}

	std::pair<float, FloatRect> CRenderer_GLES3::getLetterboxComposition() const noexcept
	{
		return m_backBuffer->getLetterboxComposition();
	}
}
