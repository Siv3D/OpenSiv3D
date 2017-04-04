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

# include "CClipboard_Linux.hpp"

namespace s3d
{
	CClipboard_Linux::CClipboard_Linux()
	{

	}

	CClipboard_Linux::~CClipboard_Linux()
	{

	}

	bool CClipboard_Linux::init()
	{
		return true;
	}

	void CClipboard_Linux::update()
	{

	}
}

# endif
