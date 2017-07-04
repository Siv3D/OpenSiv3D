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
# include <XAudio2.h>
# include <XAudio2fx.h>
# include <X3DAudio.h>
# include "../IAudio.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	struct Audio_XAudio28
	{

	};

	struct AudioDevice28
	{
		IXAudio2* xAudio2 = nullptr;

		DWORD channelMask = 0;

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

	class CAudio_XAudio28 : public ISiv3DAudio
	{
	private:

		HINSTANCE m_xaudio28 = nullptr;

		decltype(XAudio2Create)* p_XAudio2Create = nullptr;

		AudioDevice28 m_device;

		AssetHandleManager<Audio::IDType, std::shared_ptr<Audio_XAudio28>> m_audios{ S3DSTR("Audio") };

	public:

		static bool IsAvalibale();

		CAudio_XAudio28();

		~CAudio_XAudio28() override;

		bool init() override;

		Audio::IDType create(const Wave& wave) override;

		void release(Audio::IDType handleID) override;
	};
}

# endif
