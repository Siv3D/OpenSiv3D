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

# include "CTextToSpeech.hpp"
# include "TextToSpeechDetail.hpp"
# include "TTS.hpp"

namespace s3d
{
	CTextToSpeech::CTextToSpeechDetail::CTextToSpeechDetail()
		: m_detail{ std::make_unique<TTS>() }
	{
		
	}
	
	CTextToSpeech::CTextToSpeechDetail::~CTextToSpeechDetail()
	{
		
	}
	
	bool CTextToSpeech::CTextToSpeechDetail::hasLanguage(const LanguageCode languageCode)
	{
		return m_detail->hasLanguage(languageCode);
	}
	
	void CTextToSpeech::CTextToSpeechDetail::setDefaultLanguage(const LanguageCode languageCode)
	{
		m_detail->setDefaultLanguage(languageCode);
	}
	
	LanguageCode CTextToSpeech::CTextToSpeechDetail::getDefaultLanguage() const
	{
		return m_detail->getDefaultLanguage();
	}
	
	bool CTextToSpeech::CTextToSpeechDetail::speak(const std::string& text, const LanguageCode languageCode)
	{
		return m_detail->speak(text, languageCode);
	}
	
	bool CTextToSpeech::CTextToSpeechDetail::isSpeaking() const
	{
		return m_detail->isSpeaking();
	}
	
	void CTextToSpeech::CTextToSpeechDetail::pause()
	{
		m_detail->pause();
	}
	
	void CTextToSpeech::CTextToSpeechDetail::resume()
	{
		m_detail->resume();
	}
	
	void CTextToSpeech::CTextToSpeechDetail::setVolume(const double volume)
	{
		m_detail->setVolume(volume);
	}
	
	double CTextToSpeech::CTextToSpeechDetail::getVolume() const
	{
		return m_detail->getVolume();
	}
	
	void CTextToSpeech::CTextToSpeechDetail::setSpeed(const double speed)
	{
		m_detail->setSpeed(speed);
	}
	
	double CTextToSpeech::CTextToSpeechDetail::getSpeed() const
	{
		return m_detail->getSpeed();
	}
}
