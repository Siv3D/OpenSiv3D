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

# pragma once
# define GLFW_EXPOSE_NATIVE_X11
# include <ThirdParty/GL/glew.h>
# include <ThirdParty/GLFW/glfw3.h>
# include <ThirdParty/GLFW/glfw3native.h>

namespace s3d
{
	void CheckOpenGLError();
}
