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

# include "Siv3D/Platform.hpp"
# if defined(SIV3D_TARGET_OSX)

# include <iostream>
# include <unistd.h>
# include "Siv3D/String.hpp"

void Main();

namespace s3d
{
	namespace detail
	{
		void OutputLicense();
	
        std::string ParentPath(std::string path)
        {
            if (path.empty())
            {
                return std::string();
            }
            
            if (path.back() == '/')
            {
                path.pop_back();
            }
            
            if (!path.empty())
            {
                do
                {
                    path.pop_back();
                } while (path.back() != '/' && !path.empty());
            }
            
            return path;
        }
    }
}

int main(int argc, char* argv[])
{
	std::cout << "Siv3D for Mac\n";

    const std::string appPath =
    s3d::detail::ParentPath(s3d::detail::ParentPath(s3d::detail::ParentPath(s3d::detail::ParentPath(argv[0]))));
    chdir(appPath.c_str());
    
	Main();

	s3d::detail::OutputLicense();
}

# endif
