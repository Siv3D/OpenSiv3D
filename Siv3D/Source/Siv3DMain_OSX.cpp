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
	std::cout << "Siv3D for Mac\n";
    
    const s3d::FilePath path = s3d::CharacterSet::Widen(argv[0]);
    s3d::FilePath modulePath = s3d::FileSystem::ParentPath(path, 2);

    if (modulePath.ends_with(L'/'))
    {
        modulePath.pop_back();
    }
    
    s3d::detail::init::SetModulePath(modulePath);

    chdir(s3d::FileSystem::ParentPath(path, 3).narrow().c_str());
    
	Main();

	s3d::detail::OutputLicense();
}

# endif
