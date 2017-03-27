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

# include "CSystem_Windows.hpp"
# include "CSystem_macOS.hpp"
# include "CSystem_Linux.hpp"

namespace s3d
{
	ISiv3DSystem* ISiv3DSystem::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return new CSystem_Windows;

	# elif defined(SIV3D_TARGET_MACOS)

		return new CSystem_macOS;

	# elif defined(SIV3D_TARGET_LINUX)

		return new CSystem_Linux;

	# endif
	}
}
