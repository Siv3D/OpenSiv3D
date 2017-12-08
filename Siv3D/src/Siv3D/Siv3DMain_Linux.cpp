//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include <iostream>
# include <unistd.h>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Logger.hpp>
# include "Siv3DEngine.hpp"
# include "System/ISystem.hpp"

void Main();

namespace s3d
{
	namespace detail
	{
		namespace init
		{
			void SetModulePath(const FilePath& path);
		}
	}
}

int main(int, char* argv[])
{
	using namespace s3d;

	std::cout << "Siv3D for Linux\n";

	const FilePath path = Unicode::Widen(argv[0]);
	FilePath modulePath = FileSystem::ParentPath(path, 0);

	if (modulePath.ends_with(U'/'))
	{
		modulePath.pop_back();
	}

	detail::init::SetModulePath(modulePath);

	chdir(FileSystem::ParentPath(path, 0).narrow().c_str());

	Siv3DEngine engine;

	if (!Siv3DEngine::GetSystem()->init())
	{
		return -1;
	}

	Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");
	
	Main();
	
	Logger.writeRawHTML_UTF8(u8"<hr width=\"99%\">");
}

# endif
