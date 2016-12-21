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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include <GLFW/glfw3.h>
# include "IWindow.hpp"

namespace s3d
{
	class CWindow_Linux : public ISiv3DWindow
	{
	private:

		GLFWwindow* m_glfwWindow;
		
	public:

		CWindow_Linux();

		~CWindow_Linux() override;

		bool init() override;
		
		bool update() override;

		void destroy() override {}
	};
}

# endif
