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

# include "X28/CAudio_X28.hpp"
# include "XAudio27/CAudio_XAudio27.hpp"
# include "AL/CAudio_AL.hpp"
# include "Null/CAudio_Null.hpp"

namespace s3d
{
	ISiv3DAudio* ISiv3DAudio::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		ISiv3DAudio* pAudio = nullptr;

		if (CAudio_X28::IsAvalibale())
		{
			pAudio = new CAudio_X28;
		}
		else
		{
			pAudio = new CAudio_XAudio27;
		}

		if (!pAudio->hasAudioDevice())
		{
			delete pAudio;

			return new CAudio_Null;
		}

		return pAudio;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
	
		return new CAudio_AL;

	# endif
	}
}
