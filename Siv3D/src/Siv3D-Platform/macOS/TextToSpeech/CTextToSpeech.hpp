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
# include <memory>
# include "ITextToSpeech.hpp"

namespace s3d
{
	class CTextToSpeech : public ISiv3DTextToSpeech
	{
	private:
		
		class CTextToSpeechDetail;
		
		std::unique_ptr<CTextToSpeechDetail> m_detail;
		
	public:
		
		CTextToSpeech();
		
		~CTextToSpeech() override;
		
		void init() override;
		
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
}
