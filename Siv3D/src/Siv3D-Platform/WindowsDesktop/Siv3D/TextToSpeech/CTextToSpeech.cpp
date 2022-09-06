//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FormatInt.hpp>
# include "CTextToSpeech.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
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

		[[nodiscard]]
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

		[[nodiscard]]
		static bool GetEnumTokens(const WCHAR* pszCategoryId, const std::wstring& languageID, ComPtr<IEnumSpObjectTokens>& pEnum)
		{
			ULONG count = 0;

			return SUCCEEDED(EnumTokens(pszCategoryId, languageID.c_str(), nullptr, &pEnum))
				&& SUCCEEDED(pEnum->GetCount(&count)) && count != 0;
		}

		[[nodiscard]]
		inline constexpr uint16 ConvertVolume(const double volume)
		{
			return static_cast<uint16>(Clamp(volume * 100, 0.0, 100.0));
		}

		[[nodiscard]]
		inline constexpr int32 ConvertSpeed(const double speed)
		{
			return static_cast<int32>(Clamp(8.0 * (speed - 1.0), -8.0, 8.0));
		}
	}

	CTextToSpeech::CTextToSpeech() {}

	CTextToSpeech::~CTextToSpeech()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::~CTextToSpeech()");
	}

	void CTextToSpeech::init()
	{
		LOG_SCOPED_TRACE(U"CTextToSpeech::init()");
	}

	bool CTextToSpeech::hasLanguage(const LanguageCode languageCode)
	{
		if (not m_initialized)
		{
			initVoice();
		}

		if (not m_voice)
		{
			return false;
		}

		return loadLanguage(languageCode);
	}

	void CTextToSpeech::setDefaultLanguage(const LanguageCode languageCode)
	{
		m_defaultLanguageCode = languageCode;
	}

	LanguageCode CTextToSpeech::getDefaultLanguage() const
	{
		return m_defaultLanguageCode;
	}

	bool CTextToSpeech::speak(const StringView text, LanguageCode languageCode)
	{
		if (not m_initialized)
		{
			initVoice();
		}

		if (not m_voice)
		{
			return false;
		}

		if (languageCode == LanguageCode::Unspecified)
		{
			languageCode = m_defaultLanguageCode;
		}

		if (not hasLanguage(languageCode))
		{
			if (FAILED(m_voice->SetVoice(nullptr)))
			{
				return false;
			}
		}
		else
		{
			if (FAILED(m_voice->SetVoice(m_tokenTable[languageCode].Get())))
			{
				return false;
			}
		}

		if (FAILED(m_voice->SetVolume(detail::ConvertVolume(m_volume))))
		{
			return false;
		}

		if (FAILED(m_voice->SetRate(detail::ConvertSpeed(m_speed))))
		{
			return false;
		}

		const std::wstring textW = Unicode::ToWstring(text);

		return SUCCEEDED(m_voice->Speak(textW.c_str(), SPF_ASYNC | SPF_PURGEBEFORESPEAK | SPF_IS_NOT_XML, nullptr));
	}

	bool CTextToSpeech::isSpeaking() const
	{
		if (not m_initialized)
		{
			initVoice();
		}

		if (not m_voice)
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

	void CTextToSpeech::pause()
	{
		if (not m_initialized)
		{
			initVoice();
		}

		if (not m_voice)
		{
			return;
		}

		m_voice->Pause();
	}

	void CTextToSpeech::resume()
	{
		if (not m_initialized)
		{
			initVoice();
		}

		if (not m_voice)
		{
			return;
		}

		m_voice->Resume();
	}

	void CTextToSpeech::setVolume(const double volume)
	{
		if (not m_initialized)
		{
			initVoice();
		}

		if (not m_voice)
		{
			return;
		}

		m_volume = Clamp(volume, 0.0, 1.0);

		m_voice->SetVolume(detail::ConvertVolume(volume));
	}

	double CTextToSpeech::getVolume() const
	{
		return m_volume;
	}

	void CTextToSpeech::setSpeed(const double speed)
	{
		if (not m_initialized)
		{
			initVoice();
		}

		if (not m_voice)
		{
			return;
		}

		m_speed = Clamp(speed, 0.0, 2.0);

		m_voice->SetRate(detail::ConvertSpeed(speed));
	}

	double CTextToSpeech::getSpeed() const
	{
		return m_speed;
	}

	void CTextToSpeech::initVoice() const
	{
		assert(not m_initialized);

		LOG_SCOPED_TRACE(U"CTextToSpeech::initVoice()");

		m_initialized = true;

		if (FAILED(::CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&m_voice)))
		{
			LOG_WARNING(U"⚠️ TextToSpeech unavailable");
		}
		else
		{
			LOG_INFO(U"ℹ️ TextToSpeech available");
		}
	}

	bool CTextToSpeech::loadLanguage(const LanguageCode languageCode)
	{
		if (languageCode == LanguageCode::Unspecified)
		{
			if (m_tokenTable.find(languageCode) == m_tokenTable.end())
			{
				m_tokenTable.emplace(LanguageCode::Unspecified, nullptr);
			}

			return true;
		}

		if (const auto it = m_tokenTable.find(languageCode); it != m_tokenTable.end())
		{
			return !!it->second;
		}

		const std::wstring languageID = (U"Language = " + ToHex(FromEnum(languageCode))).toWstr();

		ComPtr<IEnumSpObjectTokens> pEnum;

		if (detail::GetEnumTokens(SPCAT_VOICES, languageID, pEnum))
		{

		}
		else if (pEnum.Reset(); detail::GetEnumTokens(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech Server\\v11.0\\Voices", languageID, pEnum))
		{

		}
		else if (pEnum.Reset(); detail::GetEnumTokens(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices", languageID, pEnum))
		{

		}
		else
		{
			return false;
		}

		return SUCCEEDED(pEnum->Item(0, m_tokenTable[languageCode].GetAddressOf()));
	}
}
