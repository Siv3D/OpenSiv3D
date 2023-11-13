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

TEST_CASE("ChildProcess")
{
# if SIV3D_PLATFORM(WEB)
	SECTION("on Web")
	{
		auto [cout, cerr] = CaptureStandardOutput([]
		{
			ChildProcess cp { U"/this.program" };
		});
		
		REQUIRE_THAT(cout, Catch::Matchers::Contains("ChildProcess is not supported"));
	}
# endif
}