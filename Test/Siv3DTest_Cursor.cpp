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

TEST_CASE("Cursor")
{
# if SIV3D_PLATFORM(WEB)
	SECTION("Register Custom Cursor on Web")
	{
		auto [cout, cerr] = CaptureStandardOutput([]
		{
			Image image{ Size(32, 32) };
			REQUIRE(Cursor::RegisterCustomCursorStyle(U"custom", image, Point{0, 0}) == false); 
		});
		
		REQUIRE_THAT(cout, Catch::Matchers::Contains("CreateCursor is not supported on Web platform."));
	}
# endif
}