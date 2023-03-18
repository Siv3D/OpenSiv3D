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

# include <Siv3D/EngineLog.hpp>
# include "CTextToSpeech.hpp"

namespace s3d
{
	CTextToSpeech::CTextToSpeech() {}

	CTextToSpeech::~CTextToSpeech()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::~CTextToSpeech()");
	}

	void CTextToSpeech::init()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::init()");

		// [Siv3D ToDo]
	}

	bool CTextToSpeech::hasLanguage(const LanguageCode)
	{
		// [Siv3D ToDo]
		return(false);
	}

	void CTextToSpeech::setDefaultLanguage(const LanguageCode)
	{
		// [Siv3D ToDo]
	}

	LanguageCode CTextToSpeech::getDefaultLanguage() const
	{
		// [Siv3D ToDo]
		return(LanguageCode::Unspecified);
	}

	bool CTextToSpeech::speak(const StringView, const LanguageCode)
	{
		// [Siv3D ToDo]
		return(false);
	}

	bool CTextToSpeech::isSpeaking() const
	{
		// [Siv3D ToDo]
		return(false);
	}

	void CTextToSpeech::pause()
	{
		// [Siv3D ToDo]
	}

	void CTextToSpeech::resume()
	{
		// [Siv3D ToDo]
	}

	void CTextToSpeech::setVolume(const double)
	{
		// [Siv3D ToDo]
	}

	double CTextToSpeech::getVolume() const
	{
		// [Siv3D ToDo]
		return(1.0);
	}

	void CTextToSpeech::setSpeed(const double)
	{
		// [Siv3D ToDo]
	}

	double CTextToSpeech::getSpeed() const
	{
		// [Siv3D ToDo]
		return(1.0);
	}
}
