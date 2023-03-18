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

# include <iostream>
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

	detail::init::InitCommandLines(argc, argv);
	detail::init::InitModulePath(argv[0]);

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
