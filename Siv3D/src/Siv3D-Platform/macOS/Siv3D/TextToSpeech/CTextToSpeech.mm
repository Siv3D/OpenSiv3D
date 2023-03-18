//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include "CTextToSpeech.hpp"
# include "TextToSpeechDetail.hpp"

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
		
		m_detail = std::make_unique<CTextToSpeechDetail>();
	}

	bool CTextToSpeech::hasLanguage(const LanguageCode languageCode)
	{
		return m_detail->hasLanguage(languageCode);
	}

	void CTextToSpeech::setDefaultLanguage(const LanguageCode languageCode)
	{
		m_detail->setDefaultLanguage(languageCode);
	}

	LanguageCode CTextToSpeech::getDefaultLanguage() const
	{
		return m_detail->getDefaultLanguage();
	}

	bool CTextToSpeech::speak(const StringView text, const LanguageCode languageCode)
	{
		return m_detail->speak(Unicode::ToUTF8(text), languageCode);
	}

	bool CTextToSpeech::isSpeaking() const
	{
		return m_detail->isSpeaking();
	}

	void CTextToSpeech::pause()
	{
		m_detail->pause();
	}

	void CTextToSpeech::resume()
	{
		m_detail->resume();
	}

	void CTextToSpeech::setVolume(const double volume)
	{
		m_detail->setVolume(volume);
	}

	double CTextToSpeech::getVolume() const
	{
		return 	m_detail->getVolume();
	}

	void CTextToSpeech::setSpeed(const double speed)
	{
		m_detail->setSpeed(speed);
	}

	double CTextToSpeech::getSpeed() const
	{
		return 	m_detail->getSpeed();
	}
}
