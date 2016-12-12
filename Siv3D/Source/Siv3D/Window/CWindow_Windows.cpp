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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "CWindow_Windows.hpp"

namespace s3d
{
	CWindow_Windows::CWindow_Windows()
	{

	}

	CWindow_Windows::~CWindow_Windows()
	{

	}

	bool CWindow_Windows::init()
	{
		return true;
	}
	
	bool CWindow_Windows::update()
	{
		return false;
	}
}

# endif
