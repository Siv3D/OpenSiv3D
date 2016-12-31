//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "CDragDrop_macOS.hpp"

namespace s3d
{
	CDragDrop_macOS::CDragDrop_macOS()
	{

	}

	CDragDrop_macOS::~CDragDrop_macOS()
	{

	}

	bool CDragDrop_macOS::init()
	{
		return true;
	}
	
	bool CDragDrop_macOS::update()
	{
		return true;
	}
}

# endif
