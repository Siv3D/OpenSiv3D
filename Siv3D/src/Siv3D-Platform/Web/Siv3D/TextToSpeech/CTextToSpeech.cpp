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
# include <emscripten/html5.h>

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

		__attribute__((import_name("siv3dRegisterTextToSpeechLanguagesUpdateHander")))
		extern void siv3dRegisterTextToSpeechLanguagesUpdateHander(void (*callback)(void*), void* callbackArg);

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
			updateLanguageList();
		}
		else
		{
			detail::siv3dRegisterTextToSpeechLanguagesUpdateHander(&CTextToSpeech::delayedInit, this);
			::emscripten_set_timeout(&CTextToSpeech::delayedInit, 2000, this);
		}

		::free(list.data);
	}

	void CTextToSpeech::delayedInit(void* callbackArg)
	{
		const auto that = static_cast<CTextToSpeech*>(callbackArg);

		that->updateLanguageList();
	}

	void CTextToSpeech::updateLanguageList()
	{
		auto list = detail::siv3dEnumerateAvailableTextToSpeechLanguages();

		if (list.length > 0) 
		{
			LOG_INFO(U"ℹ️ TextToSpeech available");
		}
		else
		{
			LOG_WARNING(U"⚠️ TextToSpeech unavailable");
			return;
		}

		m_AvailableLanguages.clear();

		for (uint32 i = 0; i < list.length; ++i)
		{
			auto& item = list.data[i];

			m_AvailableLanguages << item.languageCode;

			if (item.isDefault)
			{
				m_DefaultLanguage = item.languageCode;
				
				LOG_TRACE(U"LanguageCode: {} - Default"_fmt(FromEnum(item.languageCode)));
			}
			else
			{
				LOG_TRACE(U"LanguageCode: {}"_fmt(FromEnum(item.languageCode)));
			}
		}

		::free(list.data);
	}

	bool CTextToSpeech::hasLanguage(const LanguageCode languageCode)
	{
		return m_AvailableLanguages.contains(languageCode);
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
