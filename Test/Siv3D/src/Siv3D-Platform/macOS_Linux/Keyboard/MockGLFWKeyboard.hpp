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

# include <Siv3DTest.hpp>
# include <Siv3DMock.hpp>
# include <GLFW/glfw3.h>

SIV3D_MOCK_RETURN_VALUE(glfwGetKeysSiv3D, const char*, GLFWwindow*);
