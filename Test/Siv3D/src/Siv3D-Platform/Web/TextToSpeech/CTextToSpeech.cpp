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
# include <Siv3D/TextToSpeech/CTextToSpeech.hpp>

# include <Siv3DTest.hpp>
# include <emscripten.h>

TEST_CASE("Platform::Web::CTextToSpeech")
{
    SECTION("init") {
        auto [cout, cerr] = CaptureStandardOutput([&]
        {
            s3d::CTextToSpeech textToSpeech {};

            textToSpeech.init();
            ::emscripten_sleep(3000);
        });

        REQUIRE_THAT(cout, Catch::Matchers::Contains("TextToSpeech available"));
    }
}
