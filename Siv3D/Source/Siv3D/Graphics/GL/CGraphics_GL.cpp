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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <unistd.h>
# include "../../Siv3DEngine.hpp"
# include "../../Window/IWindow.hpp"
# include "../../Shader/IShader.hpp"
# include "CGraphics_GL.hpp"
# include <Siv3D/Window.hpp>
# include <Siv3D/CharacterSet.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	CGraphics_GL::CGraphics_GL()
	{

	}

	CGraphics_GL::~CGraphics_GL()
	{

	}

	bool CGraphics_GL::init()
	{
		m_glfwWindow = Siv3DEngine::GetWindow()->getHandle();
		
		::glfwSwapInterval(true);

		//////////////////////////////////////////////////////
		//
		//	 CTexture_GL
		//
		m_texture = dynamic_cast<CTexture_GL*>(Siv3DEngine::GetTexture());

		if (!m_texture)
		{
			return false;
		}

		if (!m_texture->init())
		{
			return false;
		}
		
		//////////////////////////////////////////////////////
		//
		//	 CShader_GL
		//
		m_shader = dynamic_cast<CShader_GL*>(Siv3DEngine::GetShader());
		
		if (!m_shader)
		{
			return false;
		}
		
		if (!m_shader->init())
		{
			return false;
		}
		
		//////////////////////////////////////////////////////
		//
		//	 GLBlendState
		//
		m_pBlendState = std::make_unique<GLBlendState>();
		
		//////////////////////////////////////////////////////
		//
		//	 GLRasterizerState
		//
		m_pRasterizerState = std::make_unique<GLRasterizerState>();
		
		//////////////////////////////////////////////////////
		//
		//	 GLSamplerState
		//
		m_pSamplerState = std::make_unique<GLSamplerState>();
		
		
		//////////////////////////////////////////////////////
		//
		//	 CRenderer2D_D3D11
		//
		m_renderer2D = dynamic_cast<CRenderer2D_GL*>(Siv3DEngine::GetRenderer2D());
		
		if (!m_renderer2D)
		{
			return false;
		}
		
		if (!m_renderer2D->init())
		{
			return false;
		}
		
		return true;
	}
	
	Array<DisplayOutput> CGraphics_GL::enumOutputs()
	{
		Array<DisplayOutput> outputs;
		
		int32 numMonitors;
		GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);

		for (int32 i = 0; i < numMonitors; ++i)
		{
			GLFWmonitor* monitor = monitors[i];
			
			DisplayOutput output;
			
			output.name = CharacterSet::Widen(::glfwGetMonitorName(monitor));
			
			int32 xPos, yPos, width, height;
			
			glfwGetMonitorRect_Siv3D(monitor, &xPos, &yPos, &width, &height);
			output.displayRect.x = xPos;
			output.displayRect.y = yPos;
			output.displayRect.w = width;
			output.displayRect.h = height;
			output.rotation = 0; // [Siv3D ToDo]
			
			int32 numModes;
			const GLFWvidmode* videoModes = ::glfwGetVideoModes(monitor, &numModes);
			
			for (int32 i = 0; i < numModes; ++i)
			{
				const GLFWvidmode& videoMode = videoModes[i];
				
				DisplayMode mode;
				
				mode.size.set(videoMode.width, videoMode.height);
				
				mode.refreshRateHz = videoMode.refreshRate;
				
				output.displayModes.push_back(mode);
			}
			
			outputs.push_back(output);
		}
		
		return outputs;
	}
	
	void CGraphics_GL::setClearColor(const ColorF& color)
	{
		m_clearColor = color;
	}
	
	bool CGraphics_GL::setFullScreen(const bool fullScreen, const Size& size, const size_t displayIndex, const double refreshRateHz)
	{
		if (!fullScreen)
		{
			::glfwSetWindowMonitor(m_glfwWindow, nullptr, 0, 0, size.x, size.y, GLFW_DONT_CARE);
			
			Siv3DEngine::GetWindow()->setTitle(Siv3DEngine::GetWindow()->getState().title, true);
			
			Siv3DEngine::GetWindow()->updateClientSize(false, size);
		}
		else
		{
			// [Siv3D ToDo] 対応しない解像度の場合 return false;
			
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			
			if (static_cast<int32>(displayIndex) > numMonitors)
			{
				return false;
			}
			
			::glfwSetWindowMonitor(m_glfwWindow, monitors[displayIndex], 0, 0, size.x, size.y, refreshRateHz);
			
			Siv3DEngine::GetWindow()->updateClientSize(true, size);
		}
		
		m_currentRenderTargetSize = size;

		return true;
	}
	
	bool CGraphics_GL::present()
	{
		const bool vSync = !m_targetFrameRateHz.has_value();
		
		if (vSync)
		{
			::glfwSwapBuffers(m_glfwWindow);
			
			if (::glfwGetWindowAttrib(m_glfwWindow, GLFW_ICONIFIED)
				|| !::glfwGetWindowAttrib(m_glfwWindow, GLFW_VISIBLE)
				|| !::glfwGetWindowAttrib(m_glfwWindow, GLFW_FOCUSED) // work around
				)
			{
				System::Sleep(16);
			}
		}
		else
		{
			const double targetRefreshRateHz = m_targetFrameRateHz.value();
			const double targetRefreshPeriodMillisec = (1000.0f / targetRefreshRateHz);

			::glfwSwapBuffers(m_glfwWindow);
			
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
	
	void CGraphics_GL::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		if (m_targetFrameRateHz != targetFrameRateHz)
		{
			::glfwSwapInterval(!targetFrameRateHz.has_value());
		}
		
		m_targetFrameRateHz = targetFrameRateHz;
	}
	
	Optional<double> CGraphics_GL::getTargetFrameRateHz() const
	{
		return m_targetFrameRateHz;
	}
	
	bool CGraphics_GL::flush()
	{
		m_renderer2D->flush();
		
		return true;
	}
	
	const Size& CGraphics_GL::getCurrentRenderTargetSize() const
	{
		return m_currentRenderTargetSize;
	}
}

# endif
