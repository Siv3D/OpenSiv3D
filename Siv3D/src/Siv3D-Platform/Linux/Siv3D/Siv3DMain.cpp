//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <iostream>
#include <unistd.h>
#include <limits.h>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/System/ISystem.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

void Main();

namespace s3d::detail::init
{
	void InitCommandLines(int argc, char** argv);
	void InitModulePath(const char* arg);
}

int main(int argc, char* argv[])
{
	using namespace s3d;
	std::clog << "OpenSiv3D for Linux\n";

	char absolutePath[PATH_MAX] = {};
    ssize_t absolutePathLen = readlink("/proc/self/exe", absolutePath, sizeof(absolutePath)-1);
    if (absolutePathLen == -1)
	{
		std::cerr << "Failed to get module path\n";
		return -1;
	}
    absolutePath[absolutePathLen] = '\0';
	detail::init::InitCommandLines(argc, argv);
	detail::init::InitModulePath(absolutePath);

	Siv3DEngine engine;
	
	try
	{
		SIV3D_ENGINE(System)->init();
	}
	catch (const Error& error)
	{
		std::cerr << error << '\n';
		return -1;
	}

	LOG_TRACE(U"Main() ---");

	Main();

	LOG_TRACE(U"--- Main()");

	return 0;
}
