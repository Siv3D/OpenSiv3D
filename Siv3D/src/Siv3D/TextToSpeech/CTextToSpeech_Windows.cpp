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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "CTextToSpeech_Windows.hpp"
# include <Siv3D/Math.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static HRESULT GetCategoryFromId(
			const WCHAR* pszCategoryId,
			ISpObjectTokenCategory** ppCategory)
		{
			ComPtr<ISpObjectTokenCategory> cpTokenCategory;
			HRESULT hr = ::CoCreateInstance(CLSID_SpObjectTokenCategory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(cpTokenCategory.GetAddressOf()));

			if (SUCCEEDED(hr))
			{
				hr = cpTokenCategory->SetId(pszCategoryId, FALSE);
			}

			if (SUCCEEDED(hr))
			{
				*ppCategory = cpTokenCategory.Detach();
			}

			return hr;
		}


		static HRESULT EnumTokens(
			const WCHAR* pszCategoryId,
			const WCHAR* pszReqAttribs,
			const WCHAR* pszOptAttribs,
			IEnumSpObjectTokens** ppEnum)
		{
			ComPtr<ISpObjectTokenCategory> cpCategory;
			HRESULT hr = GetCategoryFromId(pszCategoryId, &cpCategory);

			if (SUCCEEDED(hr))
			{
				hr = cpCategory->EnumTokens(pszReqAttribs, pszOptAttribs, ppEnum);
			}

			return hr;
		}

		static bool GetEnumTokens(const WCHAR* pszCategoryId, const std::wstring& languageID, ComPtr<IEnumSpObjectTokens>& pEnum)
		{
			ULONG count = 0;

			return SUCCEEDED(EnumTokens(pszCategoryId, languageID.c_str(), nullptr, &pEnum))
				&& SUCCEEDED(pEnum->GetCount(&count)) && count != 0;
		}

		static bool IsAllAscii(const StringView text)
		{
			for (const auto& ch : text)
			{
				if (ch > 127)
				{
					return false;
				}
			}

			return true;
		}

		static bool IsNumber(const StringView text)
		{
			for (const auto& ch : text)
			{
				if (!InRange(ch, U'0', U'9')
					&& (ch != U'-')
					&& (ch != U'.')
					&& (ch != U','))
				{
					return false;
				}
			}

			return true;
		}

		inline constexpr uint16 ConvertVolume(const double volume)
		{
			return static_cast<uint16>(Clamp(volume * 100, 0.0, 100.0));
		}

		inline constexpr int32 ConvertSpeed(const double speed)
		{
			return static_cast<int32>(Clamp(10.0 * (speed - 1.0), -10.0, 10.0));
		}
	}

	CTextToSpeech_Windows::CTextToSpeech_Windows()
	{
		
	}

	CTextToSpeech_Windows::~CTextToSpeech_Windows()
	{

	}

	bool CTextToSpeech_Windows::init()
	{
		if (FAILED(::CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&m_voice)))
		{
			LOG_WARNING(U"⚠️ TextToSpeech unavailable");
			return true;
		}
		else
		{
			LOG_INFO(U"ℹ️ TextToSpeech available");
		}

		LOG_INFO(U"ℹ️ TextToSpeech initialized");

		return true;
	}

	bool CTextToSpeech_Windows::hasLanguage(const int32 languageCode)
	{
		if (!m_voice)
		{
			return false;
		}

		return loadLanguage(languageCode);
	}

	void CTextToSpeech_Windows::setDefaultLanguage(const int32 languageCode)
	{
		m_defaultLanguageCode = languageCode;
	}

	int32 CTextToSpeech_Windows::getDefaultLanguage() const
	{
		return m_defaultLanguageCode;
	}

	bool CTextToSpeech_Windows::speak(const StringView text, int32 languageCode)
	{
		if (!m_voice)
		{
			return false;
		}

		if (languageCode == SpeechLanguage::Unspecified)
		{
			if (!detail::IsAllAscii(text) || detail::IsNumber(text))
			{
				languageCode = m_defaultLanguageCode;
			}
			else
			{
				languageCode = SpeechLanguage::English;
			}
		}

		if (!hasLanguage(languageCode) && (m_currentLanguageCode != SpeechLanguage::Unspecified))
		{
			if (FAILED(m_voice->SetVoice(nullptr)))
			{
				return false;
			}

			m_currentLanguageCode = SpeechLanguage::Unspecified;
		}
		else if (m_currentLanguageCode != languageCode)
		{
			if (FAILED(m_voice->SetVoice(m_tokenTable[languageCode].Get())))
			{
				return false;
			}

			m_currentLanguageCode = languageCode;
		}

		if (FAILED(m_voice->SetVolume(detail::ConvertVolume(m_volume))))
		{
			return false;
		}

		if (FAILED(m_voice->SetRate(detail::ConvertSpeed(m_speed))))
		{
			return false;
		}
		
		const std::wstring textW = Unicode::ToWString(text);
	
		return SUCCEEDED(m_voice->Speak(textW.c_str(), SPF_ASYNC | SPF_PURGEBEFORESPEAK | SPF_IS_NOT_XML, nullptr));
	}

	bool CTextToSpeech_Windows::isSpeaking() const
	{
		if (!m_voice)
		{
			return false;
		}

		SPVOICESTATUS status = {};

		if (FAILED(m_voice->GetStatus(&status, nullptr)))
		{
			return false;
		}

		return status.dwRunningState == SPRS_IS_SPEAKING;
	}

	void CTextToSpeech_Windows::pause()
	{
		if (!m_voice)
		{
			return;
		}

		m_voice->Pause();
	}

	void CTextToSpeech_Windows::resume()
	{
		if (!m_voice)
		{
			return;
		}

		m_voice->Resume();
	}

	void CTextToSpeech_Windows::setVolume(const double volume)
	{
		m_volume = Math::Saturate(volume);

		if (m_voice)
		{
			m_voice->SetVolume(detail::ConvertVolume(volume));
		}
	}

	double CTextToSpeech_Windows::getVolume() const
	{
		return m_volume;
	}

	void CTextToSpeech_Windows::setSpeed(const double speed)
	{
		m_speed = Clamp(speed, 0.0, 2.0);

		if (m_voice)
		{
			m_voice->SetRate(detail::ConvertSpeed(speed));
		}
	}

	double CTextToSpeech_Windows::getSpeed() const
	{
		return m_speed;
	}

	bool CTextToSpeech_Windows::loadLanguage(const int32 languageCode)
	{
		if (languageCode == SpeechLanguage::Unspecified)
		{
			if (m_tokenTable.find(languageCode) == m_tokenTable.end())
			{
				m_tokenTable.emplace(SpeechLanguage::Unspecified, nullptr);
			}

			return true;
		}

		if (const auto it = m_tokenTable.find(languageCode); it != m_tokenTable.end())
		{
			return !!it->second;
		}

		const std::wstring languageID = (U"Language = " + ToHex(languageCode)).toWstr();

		ComPtr<IEnumSpObjectTokens> pEnum;

		if (SUCCEEDED(detail::GetEnumTokens(SPCAT_VOICES, languageID, pEnum)))
		{

		}
		else if (pEnum.Reset(); SUCCEEDED(detail::GetEnumTokens(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech Server\\v11.0\\Voices", languageID, pEnum)))
		{

		}
		else if (pEnum.Reset(); SUCCEEDED(detail::GetEnumTokens(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices", languageID, pEnum)))
		{

		}
		else
		{
			return false;
		}

		return SUCCEEDED(pEnum->Item(0, m_tokenTable[languageCode].GetAddressOf()));
	}
}

# endif
