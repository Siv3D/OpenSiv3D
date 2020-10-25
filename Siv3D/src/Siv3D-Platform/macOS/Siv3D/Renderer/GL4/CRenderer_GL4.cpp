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

# include "CRenderer_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Renderer2D/GL4/CRenderer2D_GL4.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer_GL4::CRenderer_GL4()
	{
	
	}

	CRenderer_GL4::~CRenderer_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::~CRenderer_GL4()");
	}

	EngineOption::Renderer CRenderer_GL4::getRendererType() const noexcept
	{
		return EngineOption::Renderer::OpenGL;
	}

	void CRenderer_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::init()");
		
		pRenderer2D = dynamic_cast<CRenderer2D_GL4*>(SIV3D_ENGINE(Renderer2D));
		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());
		
		::glfwMakeContextCurrent(m_window);
		::glfwSwapInterval(1);
		
		::glewExperimental = GL_TRUE;
		if (::glewInit() != GLEW_OK)
		{
			throw EngineError(U"glefInit() failed");
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
		
		m_backBuffer = std::make_unique<GL4BackBuffer>();

		SIV3D_ENGINE(Texture)->init();
		SIV3D_ENGINE(Shader)->init();
	}

	StringView CRenderer_GL4::getName() const
	{
		static constexpr StringView name(U"OpenGL");
		return name;
	}	

	void CRenderer_GL4::clear()
	{
		m_backBuffer->clear(GL4ClearTarget::BackBuffer | GL4ClearTarget::Scene);
		
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

	void CRenderer_GL4::flush()
	{
		// Scene に 2D 描画
		{
			m_backBuffer->bindSceneBuffer();
			pRenderer2D->flush();
			m_backBuffer->unbind();
		}

		// ウィンドウに Scene を描画
		{
			m_backBuffer->updateFromSceneBuffer();
		}
	}

	bool CRenderer_GL4::present()
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

	void CRenderer_GL4::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_backBuffer->setSceneResizeMode(resizeMode);
	}

	ResizeMode CRenderer_GL4::getSceneResizeMode() const noexcept
	{
		return m_backBuffer->getSceneResizeMode();
	}

	void CRenderer_GL4::setSceneBufferSize(const Size size)
	{
		m_backBuffer->setSceneBufferSize(size);
	}

	Size CRenderer_GL4::getSceneBufferSize() const noexcept
	{
		return m_backBuffer->getSceneBufferSize();
	}

	void CRenderer_GL4::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_backBuffer->setSceneTextureFilter(textureFilter);
	}

	TextureFilter CRenderer_GL4::getSceneTextureFilter() const noexcept
	{
		return m_backBuffer->getSceneTextureFilter();
	}

	void CRenderer_GL4::setBackgroundColor(const ColorF& color)
	{
		m_backBuffer->setBackgroundColor(color);
	}

	const ColorF& CRenderer_GL4::getBackgroundColor() const noexcept
	{
		return m_backBuffer->getBackgroundColor();
	}

	void CRenderer_GL4::setLetterboxColor(const ColorF& color)
	{
		m_backBuffer->setLetterboxColor(color);
	}

	const ColorF& CRenderer_GL4::getLetterboxColor() const noexcept
	{
		return m_backBuffer->getLetterBoxColor();
	}

	std::pair<float, RectF> CRenderer_GL4::getLetterboxComposition() const noexcept
	{
		return m_backBuffer->getLetterboxComposition();
	}
}
