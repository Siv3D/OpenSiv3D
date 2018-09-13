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
# if defined(SIV3D_TARGET_LINUX)

# include "CTextToSpeech_Linux.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CTextToSpeech_Linux::CTextToSpeech_Linux()
	{
		
	}

	CTextToSpeech_Linux::~CTextToSpeech_Linux()
	{
		
	}

	bool CTextToSpeech_Linux::init()
	{
		LOG_INFO(U"ℹ️ TextToSpeech initialized");

		return true;
	}

	bool CTextToSpeech_Linux::hasLanguage(const int32 languageCode)
	{
		// [Siv3D ToDo]
		return false;
	}

	void CTextToSpeech_Linux::setDefaultLanguage(const int32 languageCode)
	{
		// [Siv3D ToDo]
	}

	int32 CTextToSpeech_Linux::getDefaultLanguage() const
	{
		// [Siv3D ToDo]
		return 0;
	}

	bool CTextToSpeech_Linux::speak(const StringView text, const int32 languageCode)
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CTextToSpeech_Linux::isSpeaking() const
	{
		// [Siv3D ToDo]
		return false;
	}

	void CTextToSpeech_Linux::pause()
	{
		// [Siv3D ToDo]
	}

	void CTextToSpeech_Linux::resume()
	{
		// [Siv3D ToDo]
	}

	void CTextToSpeech_Linux::setVolume(const double volume)
	{
		// [Siv3D ToDo]
	}

	double CTextToSpeech_Linux::getVolume() const
	{
		// [Siv3D ToDo]
		return 1.0;
	}

	void CTextToSpeech_Linux::setSpeed(const double speed)
	{
		// [Siv3D ToDo]
	}

	double CTextToSpeech_Linux::getSpeed() const
	{
		// [Siv3D ToDo]
		return 1.0;
	}
}

# endif
