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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN8
# define  NTDDI_VERSION NTDDI_WIN8
# include <Windows.h>
# include "CAudio_XAudio28.hpp"

namespace s3d
{
	bool CAudio_XAudio28::IsAvalibale()
	{
		if (HINSTANCE xaudio28 = ::LoadLibraryW(L"xaudio2_8.dll"))
		{
			::FreeLibrary(xaudio28);

			return true;
		}

		return false;
	}

	CAudio_XAudio28::CAudio_XAudio28()
	{

	}

	CAudio_XAudio28::~CAudio_XAudio28()
	{

	}

	bool CAudio_XAudio28::init()
	{

		return true;
	}
}

# endif
