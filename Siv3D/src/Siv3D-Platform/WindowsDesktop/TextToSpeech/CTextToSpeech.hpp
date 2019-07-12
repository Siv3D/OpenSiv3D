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
# include <Siv3D/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/HashTable.hpp>
# include <sapi.h>
# include <TextToSpeech/ITextToSpeech.hpp>

namespace s3d
{
	class CTextToSpeech : public ISiv3DTextToSpeech
	{
	private:

		ComPtr<ISpVoice> m_voice;

		HashTable<int32, ComPtr<ISpObjectToken>> m_tokenTable;

		int32 m_defaultLanguageCode = LanguageCode::Unspecified;

		double m_volume = 1.0;

		double m_speed = 1.0;

		bool loadLanguage(int32 languageCode);

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
