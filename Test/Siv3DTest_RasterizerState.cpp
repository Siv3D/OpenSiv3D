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

TEST_CASE("RasterizerState")
{
    auto [cout, cerr] = CaptureStandardOutput([]
    {
        ScopedRenderStates2D _renderState { RasterizerState::WireframeCullNone };

		Graphics2D::Flush();
    });

# if SIV3D_PLATFORM(WEB)
	REQUIRE_THAT(cout, Catch::Matchers::Contains("WireFrame rendendering is not supported because WebGL2 is lacking of glPolygonMode"));
# endif
}
