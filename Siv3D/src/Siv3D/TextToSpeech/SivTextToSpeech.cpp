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

# include <Siv3DEngine.hpp>
# include <Siv3D/TextToSpeech.hpp>
# include <Siv3D/StringView.hpp>
# include "ITextToSpeech.hpp"

namespace s3d
{
	namespace TextToSpeech
	{
		bool HasLanguage(const int32 languageCode)
		{
			return Siv3DEngine::Get<ISiv3DTextToSpeech>()->hasLanguage(languageCode);
		}

		void SetDefaultLanguage(const int32 languageCode)
		{
			return Siv3DEngine::Get<ISiv3DTextToSpeech>()->setDefaultLanguage(languageCode);
		}

		int32 GetDefaultLanguage()
		{
			return Siv3DEngine::Get<ISiv3DTextToSpeech>()->getDefaultLanguage();
		}

		bool Speak(const StringView text, const int32 languageCode)
		{
			return Siv3DEngine::Get<ISiv3DTextToSpeech>()->speak(text, languageCode);
		}

		bool IsSpeaking()
		{
			return Siv3DEngine::Get<ISiv3DTextToSpeech>()->isSpeaking();
		}

		void Pause()
		{
			Siv3DEngine::Get<ISiv3DTextToSpeech>()->pause();
		}

		void Resume()
		{
			Siv3DEngine::Get<ISiv3DTextToSpeech>()->resume();
		}

		void SetVolume(const double volume)
		{
			Siv3DEngine::Get<ISiv3DTextToSpeech>()->setVolume(volume);
		}

		double GetVolume()
		{
			return Siv3DEngine::Get<ISiv3DTextToSpeech>()->getVolume();
		}

		void SetSpeed(const double speed)
		{
			Siv3DEngine::Get<ISiv3DTextToSpeech>()->setSpeed(speed);
		}

		double GetSpeed()
		{
			return Siv3DEngine::Get<ISiv3DTextToSpeech>()->getSpeed();
		}
	}
}
