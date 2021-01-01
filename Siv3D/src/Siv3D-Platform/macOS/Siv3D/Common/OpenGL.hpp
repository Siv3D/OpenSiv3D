//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <ThirdParty/GL/glew.h>
# define GLFW_EXPOSE_NATIVE_COCOA
# include <ThirdParty/GLFW/glfw3.h>
# include <ThirdParty/GLFW/glfw3native.h>

namespace s3d
{
	void CheckOpenGLError();
}
