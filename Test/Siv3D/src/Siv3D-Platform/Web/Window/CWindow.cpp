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

# include <Siv3D.hpp>
# include <Siv3D/Window/CWindow.hpp>

# include "../../../../../Siv3DTest.hpp"
# include "MockGLFW.hpp"

TEST_CASE("Platform::Web::CWindow::init")
{
    SECTION("glfwInit") {
        SetReturnValue_glfwInit(GLFW_FALSE);

        s3d::CWindow window {};
        REQUIRE_THROWS_AS(window.init(), s3d::EngineError);

        SetReturnValue_glfwInit(none);
    }

    SECTION("glfwCreateWindow") {
        SetReturnValue_glfwCreateWindow(nullptr);

        s3d::CWindow window {};
        REQUIRE_THROWS_AS(window.init(), s3d::EngineError);

        SetReturnValue_glfwCreateWindow(none);
    }
}
