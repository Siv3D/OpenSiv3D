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

# include "MockGLFW.hpp"

Optional<int> ReturnValue_glfwInit = none;

void SetReturnValue_glfwInit(Optional<int> mockReturnValue)
{
    ReturnValue_glfwInit = mockReturnValue;
}

__attribute__((import_name("glfwInit")))
extern "C" int Original_glfwInit();

extern "C" int glfwInit()
{
    if (ReturnValue_glfwInit.has_value())
    {
        return *ReturnValue_glfwInit;
    }
    return Original_glfwInit();
}
