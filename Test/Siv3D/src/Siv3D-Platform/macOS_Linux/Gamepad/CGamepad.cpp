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
# include <Siv3D/Gamepad/CGamepad.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "MockGLFWGamepad.hpp"

TEST_CASE("Gamepad")
{
	const auto cGamepad = Siv3DEngine::Get<ISiv3DGamepad>();

	SetMockFunction_glfwJoystickPresent([](int){ return 0; });

	SECTION("Empty")
	{
		cGamepad->update();

		for (uint32 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			REQUIRE(cGamepad->isConnected(playerIndex) == false);
		}
	}

	SetMockFunction_glfwJoystickPresent([](int id) -> int { return id == 0; });
	SetMockFunction_siv3dGetJoystickInfo(
		[](int id, unsigned* vendorID, unsigned* productID, unsigned* version)
		{ 
			*vendorID = 1;
			*productID = 2;
			*version = 3;
			return "Mock Controller";
		});
	SetMockFunction_glfwGetJoystickButtons(
		[](int, int* buttonCount) -> const unsigned char*
		{
			*buttonCount = 0;
			return nullptr;
		});
	SetMockFunction_glfwGetJoystickHats(
		[](int, int* buttonCount) -> const unsigned char*
		{
			*buttonCount = 0;
			return nullptr;
		});
	
	SECTION("Connect")
	{
		auto [cout, cerr] = CaptureStandardOutput([&] { cGamepad->update(); });

		REQUIRE_THAT(cout, Catch::Matchers::Contains("Gamepad(0) `Mock Controller` connected"));

		REQUIRE(cGamepad->isConnected(0) == true);

		auto info = cGamepad->getInfo(0);

		REQUIRE(info.name == U"Mock Controller");
		REQUIRE(info.playerIndex == 0);
		REQUIRE(info.vendorID == 1);
		REQUIRE(info.productID == 2);

		for (uint32 playerIndex = 1; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			REQUIRE(cGamepad->isConnected(playerIndex) == false);
		}
	}

	SetMockFunction_glfwGetJoystickButtons(
		[](int, int* buttonCount) -> const unsigned char*
		{
			*buttonCount = 4;
			return reinterpret_cast<const unsigned char*>("\01\00\00\00");
		});

	SECTION("Buttons")
	{
		cGamepad->update();

		REQUIRE(cGamepad->pressed(0, 0) == true);

		for (uint32 buttonIndex = 1; buttonIndex < 4; ++buttonIndex)
		{
			REQUIRE(cGamepad->pressed(0, buttonIndex) == false);
		}
	}

	SetMockFunction_glfwGetJoystickHats(
		[](int, int* hatCount) -> const unsigned char*
		{
			*hatCount = 1;
			return reinterpret_cast<const unsigned char*>("\01\00");
		});

	SECTION("Hats")
	{
		cGamepad->update();

		REQUIRE(cGamepad->povDegree(0) == Optional{ 0 });
	}

	SetMockFunction_glfwJoystickPresent([](int){ return 0; });

	SECTION("Disconnect")
	{
		auto [cout, cerr] = CaptureStandardOutput([&] { cGamepad->update(); });

		REQUIRE_THAT(cout, Catch::Matchers::Contains("Gamepad(0) `Mock Controller` disconnected"));

		for (uint32 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			REQUIRE(cGamepad->isConnected(playerIndex) == false);
		}
	}
}
