//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <iostream>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/System/ISystem.hpp>
# include <Siv3D/MessageBox.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

void Main();

namespace s3d::detail::init
{
	void InitCommandLines(int argc, char** argv);

	void InitModulePath(const char* arg);
}

extern "C" int InitSiv3D()
{
	using namespace s3d;

	try
	{
		SIV3D_ENGINE(System)->init();
	}
	catch (const Error& error)
	{
		System::MessageBoxOK(error.what());
		
		std::cerr << error << '\n';
		return -1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	using namespace s3d;
	std::cout << "OpenSiv3D for Web\n";

	detail::init::InitCommandLines(argc, argv);
	detail::init::InitModulePath("/a.out");

	Siv3DEngine engine;
	
	if (InitSiv3D() != 0)
	{
		return -1;
	}

	LOG_TRACE(U"Main() ---");

	Main();

	LOG_TRACE(U"--- Main()");

	return 0;
}
