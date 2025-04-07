//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

# include <Siv3DTest.hpp>
# include <Siv3DMock.hpp>
# include <ThirdParty/GLFW/glfw3.h>

SIV3D_MOCK_RETURN_VALUE(glfwInit, int);
SIV3D_MOCK_RETURN_VALUE(glfwCreateWindow, GLFWwindow*, int, int, const char*, GLFWmonitor*, GLFWwindow*);
