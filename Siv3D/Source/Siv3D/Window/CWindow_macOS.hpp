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

# pragma once
# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "IWindow.hpp"

namespace s3d
{
	class CWindow_macOS : public ISiv3DWindow
	{
	private:

		GLFWwindow* m_glfwWindow;
		
	public:

		CWindow_macOS();

		~CWindow_macOS() override;

		bool init() override;
		
		bool update() override;
	};
}
