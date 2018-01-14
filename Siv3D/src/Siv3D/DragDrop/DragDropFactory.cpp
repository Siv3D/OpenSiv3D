//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CDragDrop_Windows.hpp"
# include "CDragDrop_macOS.hpp"
# include "CDragDrop_Linux.hpp"

namespace s3d
{
	ISiv3DDragDrop* ISiv3DDragDrop::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CDragDrop_Windows;

	# elif defined(SIV3D_TARGET_MACOS)
		
		return new CDragDrop_macOS;
		
	# elif defined(SIV3D_TARGET_LINUX)
		
		return new CDragDrop_Linux;
		
	# endif
	}
}

