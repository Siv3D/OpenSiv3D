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

TEST_CASE("non-existent Texture (#44)")
{
    std::string cout, cerr;

    {
        Catch::OutputRedirect outputCapture{ cout, cerr };

	    const Texture texture{ U"example/windmill2.png" };
    }

# if SIV3D_PLATFORM(WEB)
	REQUIRE_THAT(cout, Catch::Matchers::Contains("SimpleHttp: Failed to get the url `example/windmill2.png`"));
# else
	REQUIRE_THAT(cout, Catch::Matchers::Contains("BinaryReader: Failed to open the file `example/windmill2.png`"));
# endif
}
