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
# include <Siv3D/DLL.hpp>

TEST_CASE("DLL")
{
# if SIV3D_PLATFORM(WEB)

	SECTION("No support")
	{
		REQUIRE_THROWS_MATCHES(DLL::Load(U"libsub.so"), s3d::EngineError, EngineErrorMatcher(U"To use dlopen, you need enable dynamic linking, see https://github.com/emscripten-core/emscripten/wiki/Linking"));
	}

# else

	SECTION("Existent Module")
	{
		auto handle = DLL::Load(U"libsub.so");

		REQUIRE(handle != nullptr);
	}

	SECTION("Non Existent Module")
	{
		auto handle = DLL::Load(U"libsub2.so");

		REQUIRE(handle == nullptr);
	}

# endif
}
