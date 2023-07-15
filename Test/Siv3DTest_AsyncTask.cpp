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
# include <pthread.h>

TEST_CASE("AsyncTask")
{
# if SIV3D_PLATFORM(WEB) && !defined(__EMSCRIPTEN_PTHREADS__)
	SECTION("Web, no pthread support")
	{
		auto [cout, cerr] = CaptureStandardOutput([]
		{
			AsyncTask task([] { Console << U"Hello"; });

			REQUIRE(task.isValid() == false);
			REQUIRE(task.isReady() == false);
		});
		
		REQUIRE_THAT(cout, Catch::Matchers::Contains("Launching threads is not supported."));
	}
# else
	SECTION("With threading support")
	{
		auto [cout, cerr] = CaptureStandardOutput([]
		{
			AsyncTask task([] { Console << U"Hello"; });
			REQUIRE(task.isValid() == true);

			task.wait();
			REQUIRE(task.isReady() == true);
		});
		
		REQUIRE(cout == "Hello");
	}
# endif
	
}
