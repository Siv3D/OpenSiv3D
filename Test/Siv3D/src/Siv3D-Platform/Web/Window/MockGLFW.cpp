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

Optional<GLFWwindow*> ReturnValue_glfwCreateWindow = none;

void SetReturnValue_glfwCreateWindow(Optional<GLFWwindow*> mockReturnValue)
{
    ReturnValue_glfwCreateWindow = mockReturnValue;
}

__attribute__((import_name("glfwCreateWindow")))
extern "C" GLFWwindow* Original_glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);

extern "C" GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    if (ReturnValue_glfwCreateWindow.has_value())
    {
        return *ReturnValue_glfwCreateWindow;
    }
    return Original_glfwCreateWindow(width, height, title, monitor, share);
}
