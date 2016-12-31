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

# include "CSystem_Windows.hpp"
# include "CSystem_macOS.hpp"

namespace s3d
{
	ISiv3DSystem* ISiv3DSystem::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CSystem_Windows;

	# elif defined(SIV3D_TARGET_MACOS)

		return new CSystem_macOS;

	# endif
	}
}
