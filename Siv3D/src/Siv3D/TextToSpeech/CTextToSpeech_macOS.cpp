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

# include "CTextToSpeech_macOS.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{	
	CTextToSpeech_macOS::CTextToSpeech_macOS()
	: m_detail(std::make_unique<CTextToSpeechDetail>())
	{
		
	}

	CTextToSpeech_macOS::~CTextToSpeech_macOS()
	{
	
	}

	bool CTextToSpeech_macOS::init()
	{
		m_detail = std::make_unique<CTextToSpeechDetail>();
		
		LOG_INFO(U"ℹ️ TextToSpeech initialized");

		return true;
	}

	bool CTextToSpeech_macOS::hasLanguage(const int32 languageCode)
	{
		return m_detail->hasLanguage(languageCode);
	}

	void CTextToSpeech_macOS::setDefaultLanguage(const int32 languageCode)
	{
		m_detail->setDefaultLanguage(languageCode);
	}

	int32 CTextToSpeech_macOS::getDefaultLanguage() const
	{
		return m_detail->getDefaultLanguage();
	}

	bool CTextToSpeech_macOS::speak(const StringView text, const int32 languageCode)
	{
		return m_detail->speak(Unicode::ToUTF8(text), languageCode);
	}

	bool CTextToSpeech_macOS::isSpeaking() const
	{
		return m_detail->isSpeaking();
	}

	void CTextToSpeech_macOS::pause()
	{
		m_detail->pause();
	}

	void CTextToSpeech_macOS::resume()
	{
		m_detail->resume();
	}

	void CTextToSpeech_macOS::setVolume(const double volume)
	{
		m_detail->setVolume(volume);
	}

	double CTextToSpeech_macOS::getVolume() const
	{
		return 	m_detail->getVolume();
	}

	void CTextToSpeech_macOS::setSpeed(const double speed)
	{
		m_detail->setSpeed(speed);
	}

	double CTextToSpeech_macOS::getSpeed() const
	{
		return 	m_detail->getSpeed();
	}
}

# endif
