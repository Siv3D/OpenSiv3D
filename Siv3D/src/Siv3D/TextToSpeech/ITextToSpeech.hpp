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
# include <Siv3D/Common.hpp>
# include <Siv3D/TextToSpeech.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DTextToSpeech
	{
	public:

		static ISiv3DTextToSpeech* Create();

		virtual ~ISiv3DTextToSpeech() = default;

		virtual void init() = 0;

		virtual bool hasLanguage(LanguageCode languageCode) = 0;

		virtual void setDefaultLanguage(LanguageCode languageCode) = 0;

		virtual LanguageCode getDefaultLanguage() const = 0;

		virtual bool speak(StringView text, LanguageCode languageCode) = 0;

		virtual bool isSpeaking() const = 0;

		virtual void pause() = 0;

		virtual void resume() = 0;

		virtual void setVolume(double volume) = 0;

		virtual double getVolume() const = 0;

		virtual void setSpeed(double speed) = 0;

		virtual double getSpeed() const = 0;
	};
}
