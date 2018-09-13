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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <memory>
# include "ITextToSpeech.hpp"

namespace s3d
{
	class TTS_macOS;
	
	class CTextToSpeech_macOS : public ISiv3DTextToSpeech
	{
	private:

		class CTextToSpeechDetail;
		
		std::unique_ptr<CTextToSpeechDetail> m_detail;
	
	public:

		CTextToSpeech_macOS();

		~CTextToSpeech_macOS() override;

		bool init() override;

		bool hasLanguage(int32 languageCode) override;

		void setDefaultLanguage(int32 languageCode) override;

		int32 getDefaultLanguage() const override;

		bool speak(StringView text, int32 languageCode) override;

		bool isSpeaking() const override;

		void pause() override;

		void resume() override;

		void setVolume(double volume) override;

		double getVolume() const override;

		void setSpeed(double speed) override;

		double getSpeed() const override;
	};
	
	class CTextToSpeech_macOS::CTextToSpeechDetail
	{
	private:
		
		std::unique_ptr<TTS_macOS> m_detail;
		
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

# endif
