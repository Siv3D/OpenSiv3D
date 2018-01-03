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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN8
# define  NTDDI_VERSION NTDDI_WIN8
# include <Windows.h>
# include "../../../ThirdParty/XAudio2_7/XAudio2.h"
# include "../../../ThirdParty/XAudio2_7/XAudio2fx.h"
# include "../../../ThirdParty/XAudio2_7/X3DAudio.h"

namespace s3d
{
	struct AudioDevice_X27
	{
		IXAudio2* xAudio2 = nullptr;

		XAUDIO2_DEVICE_DETAILS deviceDetails = {};

		IXAudio2MasteringVoice* masteringVoice = nullptr;

		IUnknown* pXAPO = nullptr;

		X3DAUDIO_HANDLE x3DInstance;

		void release()
		{
			if (pXAPO)
			{
				pXAPO->Release();
				pXAPO = nullptr;
			}

			if (masteringVoice)
			{
				masteringVoice->DestroyVoice();
				masteringVoice = nullptr;
			}

			if (xAudio2)
			{
				xAudio2->Release();
				xAudio2 = nullptr;
			}
		}
	};
}

# endif
