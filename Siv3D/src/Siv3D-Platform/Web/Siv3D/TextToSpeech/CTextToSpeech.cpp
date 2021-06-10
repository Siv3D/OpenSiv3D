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

# include <Siv3D/EngineLog.hpp>
# include "CTextToSpeech.hpp"

namespace s3d
{
	namespace detail
	{
		struct AvailableLanguageList
		{
			struct AvailableLanguage
			{
				LanguageCode languageCode;

				bool isDefault;
			};

			size_t length;

			AvailableLanguage* data;
		};

		__attribute__((import_name("siv3dEnumerateAvailableTextToSpeechLanguages")))
		extern AvailableLanguageList siv3dEnumerateAvailableTextToSpeechLanguages();

		__attribute__((import_name("siv3dStartTextToSpeechLanguages")))
		extern void siv3dStartTextToSpeechLanguages(const char* text, double rate, double volume, LanguageCode code);

		__attribute__((import_name("siv3dIsSpeakingTextToSpeechLanguages")))
		extern bool siv3dIsSpeakingTextToSpeechLanguages();

		__attribute__((import_name("siv3dPauseTextToSpeechLanguages")))
		extern void siv3dPauseTextToSpeechLanguages();

		__attribute__((import_name("siv3dResumeTextToSpeechLanguages")))
		extern void siv3dResumeTextToSpeechLanguages();
	}

	CTextToSpeech::CTextToSpeech() {}

	CTextToSpeech::~CTextToSpeech()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::~CTextToSpeech()");
	}

	void CTextToSpeech::init()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::init()");

		auto list = detail::siv3dEnumerateAvailableTextToSpeechLanguages();

		if (list.length > 0) 
		{
			LOG_INFO(U"ℹ️ TextToSpeech available");
		}
		else
		{
			LOG_WARNING(U"⚠️ TextToSpeech unavailable");
		}

		for (uint32 i = 0; i < list.length; ++i)
		{
			auto& item = list.data[i];

			m_AvailableLanguages << item.languageCode;

			if (item.isDefault)
			{
				m_DefaultLanguage = item.languageCode;
				
				LOG_INFO(U"LanguageCode: {} - Default"_fmt(item.languageCode));
			}
			else
			{
				LOG_INFO(U"LanguageCode: {}"_fmt(item.languageCode));
			}
		}

		::free(list.data);
	}

	bool CTextToSpeech::hasLanguage(const LanguageCode languageCode)
	{
		return m_AvailableLanguages.includes(languageCode);
	}

	void CTextToSpeech::setDefaultLanguage(const LanguageCode languageCode)
	{
		m_DefaultLanguage = languageCode;
	}

	LanguageCode CTextToSpeech::getDefaultLanguage() const
	{
		return m_DefaultLanguage;
	}

	bool CTextToSpeech::speak(const StringView text, const LanguageCode languageCode)
	{
		const LanguageCode lang = (languageCode == LanguageCode::Unspecified) ? m_DefaultLanguage : languageCode;

		detail::siv3dStartTextToSpeechLanguages(text.toUTF8().c_str(), m_Speed, m_Volume, lang);
		return (true);
	}

	bool CTextToSpeech::isSpeaking() const
	{
		return detail::siv3dIsSpeakingTextToSpeechLanguages();
	}

	void CTextToSpeech::pause()
	{
		detail::siv3dPauseTextToSpeechLanguages();
	}

	void CTextToSpeech::resume()
	{
		detail::siv3dResumeTextToSpeechLanguages();
	}

	void CTextToSpeech::setVolume(const double volume)
	{
		m_Volume = volume;
	}

	double CTextToSpeech::getVolume() const
	{
		return m_Volume;
	}

	void CTextToSpeech::setSpeed(const double speed)
	{
		m_Speed = speed;
	}

	double CTextToSpeech::getSpeed() const
	{
		// [Siv3D ToDo]
		return m_Speed;
	}
}
