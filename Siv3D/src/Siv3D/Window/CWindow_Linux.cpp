//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "CWindow_Linux.hpp"
# include "../Siv3DEngine.hpp"
# include "../System/ISystem.hpp"
# include <Siv3D/System.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CWindow_Linux::CWindow_Linux()
	{

	}

	CWindow_Linux::~CWindow_Linux()
	{
		::glfwTerminate();
	}

	bool CWindow_Linux::init()
	{
		if (!glfwInit())
		{
			return false;
		}

		::glfwWindowHint(GLFW_DEPTH_BITS, 32);
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		::glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		
		m_state.clientSize.set(Window::DefaultClientSize);
		m_state.title = SIV3D_IS_DEBUG ? U"Siv3D App [Debug Build]" : U"Siv3D App";
		m_state.showState = ShowState::Normal;
		m_state.focused = false;
		m_state.fullScreen = false;

		m_glfwWindow = ::glfwCreateWindow(Window::DefaultClientSize.x, Window::DefaultClientSize.y, m_state.title.narrow().c_str(), nullptr, nullptr);
		
		if (!m_glfwWindow)
		{
			::glfwTerminate();
			
			return false;
		}

		int32 windowPosX, windowPosY;
		::glfwGetWindowPos(m_glfwWindow, &windowPosX, &windowPosY);
		m_state.pos.set(windowPosX, windowPosY);

		int32 windowSizeX, windowSizeY;
		::glfwGetWindowSize(m_glfwWindow, &windowSizeX, &windowSizeY);
		m_state.windowSize.set(windowSizeX, windowSizeY);

		::glfwMakeContextCurrent(m_glfwWindow);

		if (::glewInit() != GLEW_OK)
		{
			return false;
		}
		
		//m_state.titleBarHeight

		LOG_INFO(U"ℹ️ Window initialized");
		
		return true;
	}

	void CWindow_Linux::show(bool)
	{

	}
	
	bool CWindow_Linux::update()
	{
		::glfwPollEvents();
		
		if (::glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			Siv3DEngine::GetSystem()->reportEvent(WindowEvent::AnyKey | WindowEvent::EscapeKey);
		}

		if (::glfwGetWindowAttrib(m_glfwWindow, GLFW_FOCUSED) == GL_FALSE)
		{
			Siv3DEngine::GetSystem()->reportEvent(WindowEvent::Unfocus);
			m_state.focused = false;
		}
		else
		{
			m_state.focused = true;
		}

		if (::glfwWindowShouldClose(m_glfwWindow))
		{
			Siv3DEngine::GetSystem()->reportEvent(WindowEvent::CloseButton);

			::glfwSetWindowShouldClose(m_glfwWindow, GL_FALSE);
		}
		
		int32 windowPosX, windowPosY;
		::glfwGetWindowPos(m_glfwWindow, &windowPosX, &windowPosY);
		m_state.pos.set(windowPosX, windowPosY);

		int32 windowSizeX, windowSizeY;
		::glfwGetWindowSize(m_glfwWindow, &windowSizeX, &windowSizeY);
		m_state.windowSize.set(windowSizeX, windowSizeY);
		
		return true;
	}
	WindowHandle CWindow_Linux::getHandle() const
	{
		return m_glfwWindow;
	}

	void CWindow_Linux::setTitle(const String& title, bool forceUpdate)
	{
		if (!forceUpdate && title == m_state.title)
		{
			return;
		}

		m_state.title = title;

		if constexpr (SIV3D_IS_DEBUG)
		{
			const String titleDebug = m_state.title + U" [Debug Build]";

			::glfwSetWindowTitle(m_glfwWindow, titleDebug.narrow().c_str());
		}
		else
		{
			::glfwSetWindowTitle(m_glfwWindow, m_state.title.narrow().c_str());
		}
	}

	const WindowState& CWindow_Linux::getState() const
    {   
        return m_state;
    }   
    
    void CWindow_Linux::setPos(const Point& pos)
    {   
        m_state.pos.set(pos);
    
        ::glfwSetWindowPos(m_glfwWindow, pos.x, pos.y);
    } 

	void CWindow_Linux::updateClientSize(const bool fullScreen, const Size& size)
	{
		m_state.clientSize.set(size);
		m_state.fullScreen = fullScreen;

		int32 windowSizeX, windowSizeY;
		::glfwGetWindowSize(m_glfwWindow, &windowSizeX, &windowSizeY);
		m_state.windowSize.set(windowSizeX, windowSizeY);
	}

	void CWindow_Linux::setBaseSize(const Size& size)
	{
		m_baseSize = size;
	}

	Size CWindow_Linux::getBaseSize() const
	{
		return m_baseSize;
	}
}

# endif
