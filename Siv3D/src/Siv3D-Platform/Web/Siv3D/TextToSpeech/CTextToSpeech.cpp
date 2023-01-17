//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include "CTextToSpeech.hpp"

namespace s3d
{
	CTextToSpeech::CTextToSpeech() {}

	CTextToSpeech::~CTextToSpeech()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::~CTextToSpeech()");
	}

	void CTextToSpeech::init()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::init()");

		
	}

	bool CTextToSpeech::hasLanguage(const LanguageCode languageCode)
	{
		return false;
	}

	void CTextToSpeech::setDefaultLanguage(const LanguageCode languageCode)
	{
		
	}

	LanguageCode CTextToSpeech::getDefaultLanguage() const
	{
		return LanguageCode::Unspecified;
	}

	bool CTextToSpeech::speak(const StringView text, const LanguageCode languageCode)
	{
		return (false);
	}

	bool CTextToSpeech::isSpeaking() const
	{
		return (false);
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
		// [Siv3D ToDo]
		return 1.0;
	}
}
