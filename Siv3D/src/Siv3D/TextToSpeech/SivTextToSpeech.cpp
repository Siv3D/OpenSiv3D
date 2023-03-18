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

# include <Siv3D/TextToSpeech.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/TextToSpeech/ITextToSpeech.hpp>

namespace s3d
{
	namespace TextToSpeech
	{
		bool HasLanguage(const LanguageCode languageCode)
		{
			return SIV3D_ENGINE(TextToSpeech)->hasLanguage(languageCode);
		}

		void SetDefaultLanguage(const LanguageCode languageCode)
		{
			return SIV3D_ENGINE(TextToSpeech)->setDefaultLanguage(languageCode);
		}

		LanguageCode GetDefaultLanguage()
		{
			return SIV3D_ENGINE(TextToSpeech)->getDefaultLanguage();
		}

		bool Speak(const StringView text, const LanguageCode languageCode)
		{
			return SIV3D_ENGINE(TextToSpeech)->speak(text, languageCode);
		}

		bool IsSpeaking()
		{
			return SIV3D_ENGINE(TextToSpeech)->isSpeaking();
		}

		void Pause()
		{
			SIV3D_ENGINE(TextToSpeech)->pause();
		}

		void Resume()
		{
			SIV3D_ENGINE(TextToSpeech)->resume();
		}

		void SetVolume(const double volume)
		{
			SIV3D_ENGINE(TextToSpeech)->setVolume(volume);
		}

		double GetVolume()
		{
			return SIV3D_ENGINE(TextToSpeech)->getVolume();
		}

		void SetSpeed(const double speed)
		{
			SIV3D_ENGINE(TextToSpeech)->setSpeed(speed);
		}

		double GetSpeed()
		{
			return SIV3D_ENGINE(TextToSpeech)->getSpeed();
		}
	}
}
