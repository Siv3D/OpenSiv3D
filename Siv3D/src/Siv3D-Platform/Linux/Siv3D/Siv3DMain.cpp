//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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
	void InitModulePath(const char* arg);
}

int main(int, char* argv[])
{
	using namespace s3d;
	std::cout << "OpenSiv3D for Linux\n";

	detail::init::InitModulePath(argv[0]);

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
}
