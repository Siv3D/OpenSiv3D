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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/TextToSpeech.hpp>
# include "CTextToSpeech.hpp"
# include "TextToSpeechDetail.hpp"

namespace s3d
{
	CTextToSpeech::CTextToSpeech()
		: m_detail(std::make_unique<CTextToSpeechDetail>())
	{
		
	}
	
	CTextToSpeech::~CTextToSpeech()
	{
		LOG_TRACE(U"CTextToSpeech::~CTextToSpeech()");
	}
	
	void CTextToSpeech::init()
	{
		LOG_TRACE(U"CTextToSpeech::init()");
		
		m_detail = std::make_unique<CTextToSpeechDetail>();
		
		LOG_INFO(U"ℹ️ CTextToSpeech initialized");
	}
	
	bool CTextToSpeech::hasLanguage(const int32 languageCode)
	{
		return m_detail->hasLanguage(languageCode);
	}
	
	void CTextToSpeech::setDefaultLanguage(const int32 languageCode)
	{
		m_detail->setDefaultLanguage(languageCode);
	}
	
	int32 CTextToSpeech::getDefaultLanguage() const
	{
		return m_detail->getDefaultLanguage();
	}
	
	bool CTextToSpeech::speak(const StringView text, const int32 languageCode)
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
