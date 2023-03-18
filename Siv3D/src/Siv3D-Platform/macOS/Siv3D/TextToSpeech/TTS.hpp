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
# include <string>
# import <Foundation/Foundation.h>
# import <AppKit/AppKit.h>

namespace s3d
{
	class TTS
	{
	public:
		
		~TTS();
		
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
		
		NSSpeechSynthesizer* m_speechSynth = nullptr;
		
		LanguageCode m_defaultLanguageCode = LanguageCode::Unspecified;
		
		double m_volume = 1.0;
		
		double m_speed = 1.0;
		
		void reset();
	};
}
