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

# include "../Siv3DEngine.hpp"
# include "ITextToSpeech.hpp"
# include <Siv3D/TextToSpeech.hpp>
# include <Siv3D/StringView.hpp>

namespace s3d
{
	namespace TextToSpeech
	{
		bool HasLanguage(const int32 languageCode)
		{
			return Siv3DEngine::GetTextToSpeech()->hasLanguage(languageCode);
		}

		void SetDefaultLanguage(const int32 languageCode)
		{
			return Siv3DEngine::GetTextToSpeech()->setDefaultLanguage(languageCode);
		}

		int32 GetDefaultLanguage()
		{
			return Siv3DEngine::GetTextToSpeech()->getDefaultLanguage();
		}

		bool Speak(const StringView text, const int32 languageCode)
		{
			return Siv3DEngine::GetTextToSpeech()->speak(text, languageCode);
		}

		bool IsSpeaking()
		{
			return Siv3DEngine::GetTextToSpeech()->isSpeaking();
		}

		void Pause()
		{
			Siv3DEngine::GetTextToSpeech()->pause();
		}

		void Resume()
		{
			Siv3DEngine::GetTextToSpeech()->resume();
		}

		void SetVolume(const double volume)
		{
			Siv3DEngine::GetTextToSpeech()->setVolume(volume);
		}

		double GetVolume()
		{
			return Siv3DEngine::GetTextToSpeech()->getVolume();
		}

		void SetSpeed(const double speed)
		{
			Siv3DEngine::GetTextToSpeech()->setVolume(speed);
		}

		double GetSpeed()
		{
			return Siv3DEngine::GetTextToSpeech()->getSpeed();
		}
	}
}
