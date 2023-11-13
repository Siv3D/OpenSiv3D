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

# include "Siv3DTest.hpp"

TEST_CASE("Window::Resize")
{
	Window::Resize(1280, 720);

	REQUIRE(Window::GetState().virtualSize == Size(1280, 720));
	REQUIRE(Window::GetState().frameBufferSize == Size(1280, 720));
}
