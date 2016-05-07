//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3D/Platform.hpp"
# if defined(SIV3D_TARGET_OSX)

# include <iostream>

void Main();

namespace s3d
{
	namespace detail
	{
		void OutputLicense();
	}
}

int main()
{
	std::cout << "Siv3D for Mac\n";

	Main();

	s3d::detail::OutputLicense();
}

# endif
