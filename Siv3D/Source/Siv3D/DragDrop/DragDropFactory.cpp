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

# include "CDragDrop_Windows.hpp"
# include "CDragDrop_macOS.hpp"

namespace s3d
{
	ISiv3DDragDrop* ISiv3DDragDrop::Create()
	{
		# if defined(SIV3D_TARGET_WINDOWS)

			return new CDragDrop_Windows;

		# elif defined(SIV3D_TARGET_MACOS)
		
			return new CDragDrop_macOS;
		
		# endif
	}
}

