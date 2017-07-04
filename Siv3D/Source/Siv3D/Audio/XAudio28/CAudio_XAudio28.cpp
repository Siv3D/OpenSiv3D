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
# include "../../EngineUtility.hpp"

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
		m_audios.destroy();

		m_device.release();

		::FreeLibrary(m_xaudio28);
	}

	bool CAudio_XAudio28::init()
	{
		m_xaudio28 = ::LoadLibraryW(L"xaudio2_8.dll");

		if (!m_xaudio28)
		{
			return false;
		}
		else
		{
			
		}

		p_XAudio2Create = FunctionPointer(m_xaudio28, "XAudio2Create");

		if (!p_XAudio2Create)
		{
			return false;
		}

		if (FAILED(p_XAudio2Create(&m_device.xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		{
			return false;
		}

		if (FAILED(m_device.xAudio2->CreateMasteringVoice(&m_device.masteringVoice)))
		{
			//LOG_FAIL(L"XAudio2: マスターボイスの作成に失敗しました。サウンドデバイスが有効か確認してください。");

			return false;
		}

		return true;
	}

	Audio::IDType CAudio_XAudio28::create(const Wave& wave)
	{
		return Audio::NullHandleID;
	}

	void CAudio_XAudio28::release(const Audio::IDType handleID)
	{

	}
}

# endif
