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

# include "AL/CAudio_AL.hpp"
# include "Null/CAudio_Null.hpp"

# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>

namespace s3d
{
	namespace detail
	{
		bool IsX28Available()
		{
			if (HINSTANCE xaudio28 = ::LoadLibraryExW(L"xaudio2_8.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32))
			{
				::FreeLibrary(xaudio28);

				return true;
			}

			return false;
		}

		ISiv3DAudio* CreateCAudio_X28();

		ISiv3DAudio* CreateCAudio_X27();
	}
}

# endif

namespace s3d
{
	ISiv3DAudio* ISiv3DAudio::Create()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		ISiv3DAudio* pAudio = detail::IsX28Available() ?
			detail::CreateCAudio_X28() : detail::CreateCAudio_X27();

		if (!pAudio->hasAudioDevice())
		{
			delete pAudio;

			pAudio = new CAudio_Null;
		}

		return pAudio;

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)
	
		return new CAudio_AL;

	# endif
	}
}
