//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <unistd.h>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>
# include <Shader/IShader.hpp>
# include <Texture/ITexture.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <Shader/GL/CShader_GL.hpp>
# include <Texture/GL/CTexture_GL.hpp>
# include <Renderer2D/GL/CRenderer2D_GL.hpp>
# include "CGraphics_GL.hpp"

namespace s3d
{
	static void GLDebugMessageARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const GLvoid* userParam)
	{
		// [Siv3D ToDo] Linux でのデバッグ用
	}
	
	static void GLDebugMessageAMD(GLuint id, GLuint category, GLenum severity, GLsizei length, const GLchar *message, GLvoid* userParam)
	{
		// [Siv3D ToDo] Linux でのデバッグ用
	}
	
	static void CheckGLError()
	{
		GLenum err;
		while((err = glGetError()) != GL_NO_ERROR)
		{
			LOG_ERROR(U"OpenGL Error: 0x{}"_fmt(ToHex(err)));
		}
	}
	
	CGraphics_GL::CGraphics_GL()
	{

	}

	CGraphics_GL::~CGraphics_GL()
	{
		LOG_TRACE(U"CGraphics_GL::~CGraphics_GL()");
	}

	void CGraphics_GL::init()
	{
		LOG_TRACE(U"CGraphics_GL::init()");
		
		m_window = static_cast<GLFWwindow*>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());
		
		::glewExperimental = GL_TRUE;
		if (::glewInit() != GLEW_OK)
		{
			throw EngineError(U"glefInit() failed");
		}
		
		if (Platform::DebugBuild && GLEW_ARB_debug_output)
		{
			::glDebugMessageCallbackARB(GLDebugMessageARB, nullptr);
			LOG_INFO(U"ℹ️ GLEW_ARB_debug_output available");
		}
		else if (Platform::DebugBuild && GLEW_AMD_debug_output)
		{
			::glDebugMessageCallbackAMD(GLDebugMessageAMD, nullptr);
			LOG_INFO(U"ℹ️ GLEW_AMD_debug_output available");
		}
		
		::glfwGetFramebufferSize(m_window, &m_frameBufferSize.x, &m_frameBufferSize.y);
		
		if (!m_sceneTexture.init())
		{
			throw EngineError(U"SceneTexture::init() failed");
		}
		
		clear();

		if (CShader_GL* shader = dynamic_cast<CShader_GL*>(Siv3DEngine::Get<ISiv3DShader>()))
		{
			shader->init();
		}
		else
		{
			throw EngineError(U"dynamic_cast<CShader_GL*> failed");
		}

		if (CTexture_GL* texture = dynamic_cast<CTexture_GL*>(Siv3DEngine::Get<ISiv3DTexture>()))
		{
			texture->init();
		}
		else
		{
			throw EngineError(U"dynamic_cast<CTexture_GL*> failed");
		}
		
		m_pBlendState = std::make_unique<GLBlendState>();
		m_pRasterizerState = std::make_unique<GLRasterizerState>();
		m_pSamplerState = std::make_unique<GLSamplerState>();

		if (CRenderer2D_GL * renderer2D = dynamic_cast<CRenderer2D_GL*>(Siv3DEngine::Get<ISiv3DRenderer2D>()))
		{
			renderer2D->init();
		}
		else
		{
			throw EngineError(U"dynamic_cast<CRenderer2D_GL*> failed");
		}

		LOG_INFO(U"ℹ️ CGraphics_GL initialized");
	}

	bool CGraphics_GL::present()
	{
		const bool vSync = !m_targetFrameRateHz.has_value();
		
		if (vSync)
		{
			::glfwSwapBuffers(m_window);
		}
		else
		{
			const double targetRefreshRateHz = m_targetFrameRateHz.value();
			const double targetRefreshPeriodMillisec = (1000.0 / targetRefreshRateHz);
			
			::glfwSwapBuffers(m_window);
			
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
		}
		
		if (m_sceneTexture.hasCaptureRequest())
		{
			m_sceneTexture.capture();
		}
		
		if constexpr (Platform::DebugBuild)
		{
			CheckGLError();
		}
		
		return true;
	}

	void CGraphics_GL::clear()
	{
		if (!m_skipClearScene)
		{
			m_sceneTexture.clear(m_clearColor);
		}
		m_skipClearScene = false;
		
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		::glClearColor(
					   static_cast<float>(m_letterboxColor.r),
					   static_cast<float>(m_letterboxColor.g),
					   static_cast<float>(m_letterboxColor.b),
					   1.0f);
		::glClear(GL_COLOR_BUFFER_BIT);
	}

	void CGraphics_GL::flush()
	{
		::glfwGetFramebufferSize(m_window, &m_frameBufferSize.x, &m_frameBufferSize.y);
		
		// Scene に 2D 描画
		{
			m_sceneTexture.bindSceneFrameBuffer();
			Siv3DEngine::Get<ISiv3DRenderer2D>()->flush();
		}
		
		// ウィンドウに Scene を描画
		{
			getBlendState()->set(BlendState::Opaque);
			getRasterizerState()->set(RasterizerState::SolidCullNone);
			getSamplerState()->setPS(0, none);
			m_sceneTexture.resolve(m_sceneTextureFilter == TextureFilter::Linear);
		}
	}
	
	void CGraphics_GL::setSceneTextureFilter(const TextureFilter textureFilter)
	{
		m_sceneTextureFilter = textureFilter;
	}
	
	TextureFilter CGraphics_GL::getSceneTextureFilter() const
	{
		return m_sceneTextureFilter;
	}

	void CGraphics_GL::setBackgroundColor(const ColorF& color)
	{
		m_clearColor = color;
	}

	void CGraphics_GL::setLetterboxColor(const ColorF& color)
	{
		m_letterboxColor = color;
	}

	void CGraphics_GL::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		m_targetFrameRateHz = targetFrameRateHz;
		
		::glfwSwapInterval(m_targetFrameRateHz.has_value() ? 0 : 1);
	}

	Optional<double> CGraphics_GL::getTargetFrameRateHz() const
	{
		return m_targetFrameRateHz;
	}

	double CGraphics_GL::getDPIScaling() const
	{
		// [Siv3D ToDo]
		return 1.0;
	}

	double CGraphics_GL::getDisplayRefreshRateHz() const
	{
		// [Siv3D ToDo]
		return 60.0;
	}

	void CGraphics_GL::skipClearScreen()
	{
		m_skipClearScene = true;
	}

	const Size& CGraphics_GL::getBackBufferSize() const
	{
		return m_frameBufferSize;
	}

	const Size& CGraphics_GL::getSceneSize() const
	{
		return m_sceneTexture.getSize();
	}

	void CGraphics_GL::setSceneSize(const Size& sceneSize)
	{
		m_sceneTexture.resize(sceneSize, m_clearColor);
	}

	void CGraphics_GL::resizeBuffers(const Size& backBufferSize, const Size& sceneSize)
	{
		// [Siv3D ToDo]
	}

	Optional<Rect> CGraphics_GL::getFullscreenRect()
	{
		// do nothing for OpenGL
		return (none);
	}

	void CGraphics_GL::requestScreenCapture()
	{
		m_sceneTexture.requestCapture();
	}

	const Image& CGraphics_GL::getScreenCapture() const
	{
		return m_sceneTexture.getImage();
	}
}
