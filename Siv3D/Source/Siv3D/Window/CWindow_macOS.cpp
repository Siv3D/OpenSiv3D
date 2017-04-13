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
# if defined(SIV3D_TARGET_MACOS)

# include "CWindow_macOS.hpp"

namespace s3d
{
	CWindow_macOS::CWindow_macOS()
	{

	}

	CWindow_macOS::~CWindow_macOS()
	{
		::glfwTerminate();
	}

	bool CWindow_macOS::init()
	{
		if (!glfwInit())
		{
			return false;
		}
		
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		::glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		
		m_state.clientSize.set(Window::DefaultClientSize);
		m_state.title = L"Siv3D App";
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
		
		return true;
	}
	
	bool CWindow_macOS::update()
	{		
		::glfwPollEvents();
		
		if(::glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			::glfwSetWindowShouldClose(m_glfwWindow, GL_TRUE);
		}
		   
		if(::glfwWindowShouldClose(m_glfwWindow))
		{
			return false;
		}
		
		int32 windowPosX, windowPosY;
		::glfwGetWindowPos(m_glfwWindow, &windowPosX, &windowPosY);
		m_state.pos.set(windowPosX, windowPosY);
		
		int32 windowSizeX, windowSizeY;
		::glfwGetWindowSize(m_glfwWindow, &windowSizeX, &windowSizeY);
		m_state.windowSize.set(windowSizeX, windowSizeY);
		
		return true;
	}

	WindowHandle CWindow_macOS::getHandle() const
	{
		return m_glfwWindow;
	}

	void CWindow_macOS::setTitle(const String& title, bool forceUpdate)
	{
		if (!forceUpdate && title == m_state.title)
		{
			return;
		}

		m_state.title = title;

		::glfwSetWindowTitle(m_glfwWindow, m_state.title.narrow().c_str());
	}
	
	const WindowState& CWindow_macOS::getState() const
	{
		return m_state;
	}
	
	void CWindow_macOS::setPos(const Point& pos)
	{
		m_state.pos.set(pos);
		
		::glfwSetWindowPos(m_glfwWindow, pos.x, pos.y);
	}

	void CWindow_macOS::updateClientSize(const bool fullScreen, const Size& size)
	{
		m_state.clientSize.set(size);
		m_state.fullScreen = fullScreen;

		int32 windowSizeX, windowSizeY;
		::glfwGetWindowSize(m_glfwWindow, &windowSizeX, &windowSizeY);
		m_state.windowSize.set(windowSizeX, windowSizeY);
	}
}

# endif
