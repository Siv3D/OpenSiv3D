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

# include <Siv3D/Math.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CTextToSpeech.hpp"

// [Siv3D ToDo]
namespace s3d
{
	CTextToSpeech::CTextToSpeech()
	{
		
	}

	CTextToSpeech::~CTextToSpeech()
	{
	}

	void CTextToSpeech::init()
	{
	}

	bool CTextToSpeech::hasLanguage(const int32 languageCode)
	{
		return false;
	}

	void CTextToSpeech::setDefaultLanguage(const int32 languageCode)
	{
	}

	int32 CTextToSpeech::getDefaultLanguage() const
	{
		return 0;
	}

	bool CTextToSpeech::speak(const StringView text, int32 languageCode)
	{
		return false;
	}

	bool CTextToSpeech::isSpeaking() const
	{
		return false;
	}

	void CTextToSpeech::pause()
	{
	}

	void CTextToSpeech::resume()
	{
	}

	void CTextToSpeech::setVolume(const double volume)
	{
	}

	double CTextToSpeech::getVolume() const
	{
		return 0.0;
	}

	void CTextToSpeech::setSpeed(const double speed)
	{
	}

	double CTextToSpeech::getSpeed() const
	{
		return 0.0;
	}
}
