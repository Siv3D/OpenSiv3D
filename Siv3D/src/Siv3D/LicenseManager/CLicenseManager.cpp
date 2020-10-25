//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CLicenseManager.hpp"
# include "LicenseList.hpp"

namespace s3d
{
	CLicenseManager::CLicenseManager()
		: m_licenses(std::begin(detail::licenses), std::end(detail::licenses))
	{

	}

	CLicenseManager::~CLicenseManager() = default;

	void CLicenseManager::update()
	{
		if (!m_openLicenseWithF1Key)
		{
			return;
		}

		//if (KeyF1.down())
		//{
		//	LicenseManager::ShowInBrowser();
		//}
	}

	void CLicenseManager::setApplicationLicense(const String& applicationName, const LicenseInfo& license)
	{
		if (!m_hasApplicationLicense)
		{
			const LicenseInfo info
			{
				.title		= license.title,
				.copyright	= license.copyright,
				.text		= license.text.xml_escaped()
			};
			m_licenses.push_front(info);

			++m_num_customLicenses;
			m_hasApplicationLicense = true;
		}
		else
		{
			m_licenses.front() = license;
		}

		if (const auto name = applicationName.removed_if([](char32 c)
			{
				return (c != U'\\')
					&& (c != U'/')
					&& (c != U',')
					&& (c != U'.')
					&& (c != U';')
					&& (c != U':')
					&& (c != U'*')
					&& (c != U'?')
					&& (c != U'\"')
					&& (c != U'<')
					&& (c != U'>')
					&& (c != U'|')
					;
			}))
		{
			m_normalizedApplicationName = name;
		}
	}

	void CLicenseManager::addLicense(const LicenseInfo& license)
	{
		m_licenses.insert((m_licenses.begin() + m_num_customLicenses), license);

		++m_num_customLicenses;
	}

	const Array<LicenseInfo>& CLicenseManager::enumLicenses() const noexcept
	{
		return m_licenses;
	}

	const String& CLicenseManager::getNormalizedApplicationName() const noexcept
	{
		return m_normalizedApplicationName;
	}

	void CLicenseManager::setDefaultTriggerRnabled(const bool enabled) noexcept
	{
		m_openLicenseWithF1Key = enabled;
	}
}
