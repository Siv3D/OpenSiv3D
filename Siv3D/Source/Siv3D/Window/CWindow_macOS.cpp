//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
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
		glfwTerminate();
	}

	bool CWindow_macOS::init()
	{
		if (!glfwInit())
		{
			return false;
		}
		
		m_glfwWindow = glfwCreateWindow(640, 480, "Siv3D App", nullptr, nullptr);
		
		if (!m_glfwWindow)
		{
			glfwTerminate();
			
			return false;
		}

		glfwMakeContextCurrent(m_glfwWindow);

		return true;
	}
	
	bool CWindow_macOS::update()
	{
		glClearColor(11/255.0f, 22/255.0f, 33/255.0f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(m_glfwWindow);
		
		glfwPollEvents();
		
		if(glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_glfwWindow, GL_TRUE);
		}
		   
		if(glfwWindowShouldClose(m_glfwWindow))
		{
			return false;
		}
		
		return true;
	}
}

# endif
