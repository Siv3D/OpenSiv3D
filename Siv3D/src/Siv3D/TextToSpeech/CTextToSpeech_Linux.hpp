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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "ITextToSpeech.hpp"

namespace s3d
{
	class CTextToSpeech_Linux : public ISiv3DTextToSpeech
	{
	private:
		
	
	public:

		CTextToSpeech_Linux();

		~CTextToSpeech_Linux() override;

		bool init() override;

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

# endif
