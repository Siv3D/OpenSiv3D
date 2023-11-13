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

# define CATCH_CONFIG_RUNNER

# include <Siv3D/OpenCV_Bridge.hpp>

# include "Siv3DTest.hpp"
# include <unordered_map>

// SIV3D_SET(EngineOption::Renderer::Headless) // Force non-graphical mode

void Main()
{
	Console.open();
	
	{
# if SIV3D_PLATFORM(WEB)
		Catch::Session().run();
# else
		FileSystem::Remove(U"test/");
	
		FileSystem::Copy(U"../../Test/test/", U"./test/");

		Catch::Session().run();

		FileSystem::Remove(U"test/");
# endif
	}
}

std::tuple<std::string, std::string> CaptureStandardOutput(const std::function<void(void)>& logic)
{
	std::string cout, cerr;

    {
        Catch::OutputRedirect outputCapture{ cout, cerr };

	    logic();
    }

	return { cout, cerr };
}

void AssertImagesAreEqual(const Image& target, const Image& checked)
{
	if (target != checked)
	{
		throw std::runtime_error{ "AssertImagesAreEqual: target != checked" };
	}
}
