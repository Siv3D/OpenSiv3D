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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "../Siv3D_macOS.h"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CTextToSpeech_macOS::CTextToSpeech_macOS()
	{
		
	}

	CTextToSpeech_macOS::~CTextToSpeech_macOS()
	{
	
	}

	bool CTextToSpeech_macOS::init()
	{
		LOG_INFO(U"ℹ️ TextToSpeech initialized");

		return true;
	}

	bool CTextToSpeech_macOS::hasLanguage(const int32 languageCode)
	{
		// [Siv3D ToDo]
		return false;
	}

	void CTextToSpeech_macOS::setDefaultLanguage(const int32 languageCode)
	{
		// [Siv3D ToDo]
	}

	int32 CTextToSpeech_macOS::getDefaultLanguage() const
	{
		// [Siv3D ToDo]
		return 0;
	}

	bool CTextToSpeech_macOS::speak(const StringView text, const int32 languageCode)
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CTextToSpeech_macOS::isSpeaking() const
	{
		// [Siv3D ToDo]
		return false;
	}

	void CTextToSpeech_macOS::pause()
	{
		// [Siv3D ToDo]
	}

	void CTextToSpeech_macOS::resume()
	{
		// [Siv3D ToDo]
	}

	void CTextToSpeech_macOS::setVolume(const double volume)
	{
		// [Siv3D ToDo]
	}

	double CTextToSpeech_macOS::getVolume() const
	{
		// [Siv3D ToDo]
		return 1.0;
	}

	void CTextToSpeech_macOS::setSpeed(const double speed)
	{
		// [Siv3D ToDo]
	}

	double CTextToSpeech_macOS::getSpeed() const
	{
		// [Siv3D ToDo]
		return 1.0;
	}
}

# endif
