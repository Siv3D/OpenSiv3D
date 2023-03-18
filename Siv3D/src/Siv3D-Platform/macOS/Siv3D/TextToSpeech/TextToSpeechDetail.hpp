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

# pragma once
# include "CTextToSpeech.hpp"
# include "TTS.hpp"

namespace s3d
{
	class CTextToSpeech::CTextToSpeechDetail
	{
	public:
		
		CTextToSpeechDetail();
		
		~CTextToSpeechDetail();
		
		bool hasLanguage(LanguageCode languageCode);
		
		void setDefaultLanguage(LanguageCode languageCode);
		
		LanguageCode getDefaultLanguage() const;
		
		bool speak(const std::string& text, LanguageCode languageCode);
		
		bool isSpeaking() const;
		
		void pause();
		
		void resume();
		
		void setVolume(double volume);
		
		double getVolume() const;
		
		void setSpeed(double speed);
		
		double getSpeed() const;
		
	private:
			
		std::unique_ptr<TTS> m_detail;
	};
}
