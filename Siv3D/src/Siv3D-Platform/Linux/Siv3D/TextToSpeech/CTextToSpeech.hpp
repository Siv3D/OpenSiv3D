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
# include <Siv3D/TextToSpeech/ITextToSpeech.hpp>

namespace s3d
{
	class CTextToSpeech final : public ISiv3DTextToSpeech
	{
	public:

		CTextToSpeech();

		~CTextToSpeech() override;

		void init() override;

		bool hasLanguage(LanguageCode languageCode) override;

		void setDefaultLanguage(LanguageCode languageCode) override;

		LanguageCode getDefaultLanguage() const override;

		bool speak(StringView text, LanguageCode languageCode) override;

		bool isSpeaking() const override;

		void pause() override;

		void resume() override;

		void setVolume(double volume) override;

		double getVolume() const override;

		void setSpeed(double speed) override;

		double getSpeed() const override;

	private:

	};
}
