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

# include "../../Siv3DEngine.hpp"
# include "../../Window/IWindow.hpp"
# include "CGraphics_GL.hpp"
# include <Siv3D/Window.hpp>
# include <Siv3D/CharacterSet.hpp>
# include <Siv3D/System.hpp>

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
		
		::glfwSwapInterval(m_vsync);

		//////////////////////////////////////////////////////
		//
		//	 CTextureGL
		//
		m_texture = dynamic_cast<CTextureGL*>(Siv3DEngine::GetTexture());

		if (!m_texture)
		{
			return false;
		}

		if (!m_texture->init())
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
			::glfwSetWindowMonitor(m_glfwWindow, nullptr, 100, 100, size.x, size.y, GLFW_DONT_CARE);
			
			Siv3DEngine::GetWindow()->setTitle(Siv3DEngine::GetWindow()->getState().title, true);
		}
		else
		{
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			
			if (static_cast<int32>(displayIndex) > numMonitors)
			{
				return false;
			}
			
			::glfwSetWindowMonitor(m_glfwWindow, monitors[displayIndex], 0, 0, size.x, size.y, refreshRateHz);
		}
		
		Siv3DEngine::GetWindow()->updateClientSize(fullScreen, size);

		return true;
	}
	
	bool CGraphics_GL::present()
	{
		::glfwSwapBuffers(m_glfwWindow);
		
		if (::glfwGetWindowAttrib(m_glfwWindow, GLFW_ICONIFIED)
			|| !::glfwGetWindowAttrib(m_glfwWindow, GLFW_VISIBLE)
			|| !::glfwGetWindowAttrib(m_glfwWindow, GLFW_FOCUSED) // work around
			)
		{
			System::Sleep(16);
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
	
	void CGraphics_GL::setVSyncEnabled(const bool enabled)
	{
		if (enabled == m_vsync)
		{
			return;
		}
		
		m_vsync = enabled;
		
		::glfwSwapInterval(m_vsync);
	}
	
	bool CGraphics_GL::isVSyncEnabled() const
	{
		return m_vsync;
	}
}

# endif
