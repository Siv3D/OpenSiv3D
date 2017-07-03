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

# include "XAudio28/CAudio_XAudio28.hpp"
# include "XAudio27/CAudio_XAudio27.hpp"
# include "AL/CAudio_AL.hpp"

namespace s3d
{
	ISiv3DAudio* ISiv3DAudio::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		if (CAudio_XAudio28::IsAvalibale())
		{
			return new CAudio_XAudio28;
		}
		else
		{
			return new CAudio_XAudio27;
		}

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
	
		return new CAudio_AL;

	# endif
	}
}
