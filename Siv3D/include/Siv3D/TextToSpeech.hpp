//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "LanguageCode.hpp"
# include "StringView.hpp"

namespace s3d
{
	namespace TextToSpeech
	{
		[[nodiscard]]
		bool HasLanguage(LanguageCode languageCode);

		void SetDefaultLanguage(LanguageCode languageCode);

		[[nodiscard]]
		LanguageCode GetDefaultLanguage();

		bool Speak(StringView text, LanguageCode languageCode = LanguageCode::Unspecified);

		[[nodiscard]]
		bool IsSpeaking();

		void Pause();

		void Resume();

		void SetVolume(double volume);

		[[nodiscard]]
		double GetVolume();

		void SetSpeed(double speed);

		[[nodiscard]]
		double GetSpeed();
	}
}
