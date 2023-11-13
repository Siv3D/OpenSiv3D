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

# include <Siv3DTest.hpp>
# include <Siv3D/Keyboard/CKeyboard.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "MockGLFWKeyboard.hpp"

TEST_CASE("Keyboard")
{
	const auto cKeyboard = Siv3DEngine::Get<ISiv3DKeyboard>();

	char returnValue[GLFW_KEY_LAST + 1] = { 0 };
	SetReturnValue_glfwGetKeysSiv3D(returnValue);

	SECTION("down")
	{
		returnValue[GLFW_KEY_0] = GLFW_TRUE;
		cKeyboard->update();

		REQUIRE(cKeyboard->down(0x30) == true);
		REQUIRE(cKeyboard->up(0x30) == false);
	}
	
	SECTION("up")
	{
		returnValue[GLFW_KEY_0] = GLFW_FALSE;
		cKeyboard->update();

		REQUIRE(cKeyboard->down(0x30) == false);
		REQUIRE(cKeyboard->up(0x30) == true);
	}
}
