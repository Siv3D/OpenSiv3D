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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../Siv3DEngine.hpp"
# include "CEyeTracking_Windows.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CEyeTracking_Windows::CEyeTracking_Windows()
	{

	}

	CEyeTracking_Windows::~CEyeTracking_Windows()
	{

	}

	bool CEyeTracking_Windows::init()
	{
		LOG_INFO(U"ℹ️ EyeTracking initialized");

		return true;
	}

	void CEyeTracking_Windows::update()
	{

	}
}

# endif
