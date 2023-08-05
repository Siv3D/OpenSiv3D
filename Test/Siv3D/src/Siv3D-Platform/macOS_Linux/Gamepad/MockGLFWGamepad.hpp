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

# include <Siv3DMock.hpp>
# include <GLFW/glfw3.h>

SIV3D_MOCK_FUNCTION(glfwJoystickPresent, int, int);
SIV3D_MOCK_FUNCTION(glfwGetJoystickButtons, const unsigned char*, int, int*);
SIV3D_MOCK_FUNCTION(glfwGetJoystickHats, const unsigned char*, int, int*);
SIV3D_MOCK_FUNCTION(siv3dGetJoystickInfo, const char*, int, unsigned*, unsigned*, unsigned*);
