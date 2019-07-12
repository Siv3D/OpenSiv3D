//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/DLL.hpp>
# include <Audio/Null/CAudio_Null.hpp>

namespace s3d
{
	namespace detail
	{
		bool IsX28Available()
		{
			if (HMODULE xaudio28 = ::LoadLibraryExW(L"xaudio2_8.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32))
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

namespace s3d
{
	ISiv3DAudio* ISiv3DAudio::Create()
	{
		::CoInitialize(nullptr);

		ISiv3DAudio* pAudio = detail::IsX28Available() ?
			detail::CreateCAudio_X28() : detail::CreateCAudio_X27();

		if (!pAudio->hasAudioDevice())
		{
			delete pAudio;

			pAudio = new CAudio_Null;
		}

		return pAudio;
	}
}
