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
# include "Fwd.hpp"

namespace s3d
{
	namespace SpeechLanguage
	{
		inline constexpr int32 English = 0x409;

		inline constexpr int32 Japanese = 0x411;

		inline constexpr int32 Spanish = 0x40a;

		inline constexpr int32 French = 0x40c;

		inline constexpr int32 German = 0x407;

		inline constexpr int32 ChinesePRC = 0x804;

		inline constexpr int32 ChineseTaiwan = 0x404;

		inline constexpr int32 Unspecified = 0x000;
	}

	namespace TextToSpeech
	{
		[[nodiscard]] bool HasLanguage(int32 languageCode);

		void SetDefaultLanguage(int32 languageCode);

		[[nodiscard]] int32 GetDefaultLanguage();

		bool Speak(StringView text, int32 languageCode = SpeechLanguage::Unspecified);

		[[nodiscard]] bool IsSpeaking();

		void Pause();

		void Resume();

		void SetVolume(double volume);

		[[nodiscard]] double GetVolume();

		void SetSpeed(double speed);

		[[nodiscard]] double GetSpeed();
	}
}
