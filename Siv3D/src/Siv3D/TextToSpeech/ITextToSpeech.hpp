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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/TextToSpeech.hpp>

namespace s3d
{
	class ISiv3DTextToSpeech
	{
	public:

		static ISiv3DTextToSpeech* Create();

		virtual ~ISiv3DTextToSpeech() = default;

		virtual bool init() = 0;

		virtual bool hasLanguage(int32 languageCode) = 0;

		virtual void setDefaultLanguage(int32 languageCode) = 0;

		virtual int32 getDefaultLanguage() const = 0;

		virtual bool speak(StringView text, int32 languageCode) = 0;

		virtual bool isSpeaking() const = 0;

		virtual void pause() = 0;

		virtual void resume() = 0;

		virtual void setVolume(double volume) = 0;

		virtual double getVolume() const = 0;

		virtual void setSpeed(double speed) = 0;

		virtual double getSpeed() const = 0;
	};
}
