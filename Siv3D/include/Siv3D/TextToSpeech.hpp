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
# include "Fwd.hpp"
# include "LanguageCode.hpp"

namespace s3d
{
	namespace TextToSpeech
	{
		[[nodiscard]] bool HasLanguage(int32 languageCode);

		void SetDefaultLanguage(int32 languageCode);

		[[nodiscard]] int32 GetDefaultLanguage();

		bool Speak(StringView text, int32 languageCode = LanguageCode::Unspecified);

		[[nodiscard]] bool IsSpeaking();

		void Pause();

		void Resume();

		void SetVolume(double volume);

		[[nodiscard]] double GetVolume();

		void SetSpeed(double speed);

		[[nodiscard]] double GetSpeed();
	}
}
