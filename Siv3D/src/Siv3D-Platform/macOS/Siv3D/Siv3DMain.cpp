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
# include <Siv3D/Error.hpp>

void Main();

namespace s3d::detail::init
{
	void InitCommandLines(int argc, char** argv);
}

int main(int argc, char* argv[])
{
	using namespace s3d;
	std::cout << "OpenSiv3D for macOS\n";
	
	detail::init::InitCommandLines(argc, argv);

	Siv3DEngine engine;
	
	try
	{
		SIV3D_ENGINE(System)->init();
	}
	catch (const Error& error)
	{
		std::cout << error << '\n';
		return -1;
	}

	Main();
	
	return 0;
}
