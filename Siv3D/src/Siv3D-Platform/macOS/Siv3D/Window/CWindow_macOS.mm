//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Common/OpenGL.hpp>
# define GLFW_EXPOSE_NATIVE_COCOA
# include <ThirdParty/GLFW/glfw3native.h>
# include <Siv3D/WindowState.hpp>

namespace s3d
{
	void Siv3D_MacOS_UpdateWindowState(GLFWwindow* handle, WindowState& state)
	{
		NSWindow* window = glfwGetCocoaWindow(handle);

		CGFloat contentHeight = [window contentRectForFrameRect: window.frame].size.height;
		state.titleBarHeight = (window.frame.size.height - contentHeight);
	}
}
