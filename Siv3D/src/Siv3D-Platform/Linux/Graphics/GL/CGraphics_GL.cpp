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
		
		return true;
	}

	void CGraphics_GL::clear()
	{
		::glClearColor(
					   static_cast<float>(m_clearColor.r),
					   static_cast<float>(m_clearColor.g),
					   static_cast<float>(m_clearColor.b),
					   1.0f);
		
		::glClear(GL_COLOR_BUFFER_BIT);
	}

	void CGraphics_GL::flush()
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->flush();

		// [Siv3D ToDo]
	}

	void CGraphics_GL::setBackgroundColor(const ColorF& color)
	{
		// [Siv3D ToDo]
	}

	void CGraphics_GL::setLetterboxColor(const ColorF& color)
	{
		// [Siv3D ToDo]
	}

	void CGraphics_GL::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		m_targetFrameRateHz = targetFrameRateHz;
		
		::glfwSwapInterval(m_targetFrameRateHz.has_value() ? 0 : 1);
	}

	Optional<double> CGraphics_GL::getTargetFrameRateHz() const
	{
		// [Siv3D ToDo]
		return none;
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
		// [Siv3D ToDo]
	}

	const Size& CGraphics_GL::getBackBufferSize() const
	{
		// [Siv3D ToDo]
		static Size dummy(800, 600);
		return dummy;
	}

	const Size& CGraphics_GL::getSceneSize() const
	{
		// [Siv3D ToDo]
		static Size dummy(800, 600);
		return dummy;
	}

	void CGraphics_GL::setSceneSize(const Size& sceneSize)
	{
		// [Siv3D ToDo]
	}

	void CGraphics_GL::resizeBuffers(const Size& backBufferSize, const Size& sceneSize)
	{
		// [Siv3D ToDo]
	}

	Optional<Rect> CGraphics_GL::getFullscreenRect()
	{
		// [Siv3D ToDo]
		return (none);
	}

	void CGraphics_GL::requestScreenCapture()
	{
		// [Siv3D ToDo]
	}

	const Image& CGraphics_GL::getScreenCapture() const
	{
		// [Siv3D ToDo]
		static Image dummy;
		return dummy;
	}
}
