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

# pragma once
# include "CTextToSpeech.hpp"
# include "TTS.hpp"

namespace s3d
{
	class CTextToSpeech::CTextToSpeechDetail
	{
	private:
		
		std::unique_ptr<TTS> m_detail;
		
	public:
		
		CTextToSpeechDetail();
		
		~CTextToSpeechDetail();
		
		bool hasLanguage(int32 languageCode);
		
		void setDefaultLanguage(int32 languageCode);
		
		int32 getDefaultLanguage() const;
		
		bool speak(const std::string& text, int32 languageCode);
		
		bool isSpeaking() const;
		
		void pause();
		
		void resume();
		
		void setVolume(double volume);
		
		double getVolume() const;
		
		void setSpeed(double speed);
		
		double getSpeed() const;
	};
}
