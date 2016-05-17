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
# if defined(SIV3D_TARGET_OSX)

# include <iostream>
# include <unistd.h>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/CharacterSet.hpp>
# include "Siv3DEngine.hpp"

void Main();

namespace s3d
{
	namespace detail
	{
		void OutputLicense();

        namespace init
        {
            void SetModulePath(const FilePath& path);
        }
    }
}

int main(int argc, char* argv[])
{
	using namespace s3d;

	std::cout << "Siv3D for Mac\n";
    
    const FilePath path = CharacterSet::Widen(argv[0]);
    FilePath modulePath = FileSystem::ParentPath(path, 2);

    if (modulePath.ends_with(L'/'))
    {
        modulePath.pop_back();
    }
    
    detail::init::SetModulePath(modulePath);

    chdir(FileSystem::ParentPath(path, 3).narrow().c_str());
    
	Siv3DEngine engine;

	Main();

	s3d::detail::OutputLicense();
}

# endif
