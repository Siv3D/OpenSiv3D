//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <iostream>
# include <unistd.h>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/CharacterSet.hpp>
# include "Siv3DEngine.hpp"
# include "Logger/ILogger.hpp"

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

	std::cout << "Siv3D for macOS\n";
    
    const FilePath path = CharacterSet::Widen(argv[0]);
    FilePath modulePath = FileSystem::ParentPath(path, 2);

    if (modulePath.ends_with(L'/'))
    {
        modulePath.pop_back();
    }
    
    detail::init::SetModulePath(modulePath);

    chdir(FileSystem::ParentPath(path, 3).narrow().c_str());
    
	Siv3DEngine engine;

	if (!engine.GetLogger()->init())
	{
		return -1;
	}

	Main();
}

# endif
