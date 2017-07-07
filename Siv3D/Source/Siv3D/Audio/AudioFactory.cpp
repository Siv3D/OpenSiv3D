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

# include "AL/CAudio_AL.hpp"
# include "Null/CAudio_Null.hpp"

namespace s3d
{
# if defined(SIV3D_TARGET_WINDOWS)

	namespace detail
	{
		bool CAudio_X28_IsAvailable();
		ISiv3DAudio* CreateCAudio_X28();
		ISiv3DAudio* CreateCAudio_X27();
	}

# endif

	ISiv3DAudio* ISiv3DAudio::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		ISiv3DAudio* pAudio = nullptr;

		if (detail::CAudio_X28_IsAvailable())
		{
			pAudio = detail::CreateCAudio_X28();
		}
		else
		{
			pAudio = detail::CreateCAudio_X27();
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
