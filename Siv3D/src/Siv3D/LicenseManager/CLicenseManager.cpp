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

# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Char.hpp>
# include <LicenseManager/LicenseList.hpp>
# include "CLicenseManager.hpp"

namespace s3d
{
	CLicenseManager::CLicenseManager()
		: m_licenses(licenses)
	{

	}

	CLicenseManager::~CLicenseManager()
	{

	}

	void CLicenseManager::update()
	{
		if (!m_openIfF1KeyPressed)
		{
			return;
		}

		if (KeyF1.down())
		{
			LicenseManager::ShowInBrowser();
		}
	}

	void CLicenseManager::setApplicationLicense(const String& uniqueID, const LicenseInfo& license)
	{
		if (!m_hasApplicationLicense)
		{
			m_licenses.push_front(license);

			++m_num_customLicenes;

			m_hasApplicationLicense = true;
		}
		else
		{
			m_licenses[0] = license;
		}

		m_uniqueID = uniqueID.removed_if([](char32 c)
			{
				return !IsAlnum(c) && (c != '-') && (c != '_');
			});
	}

	void CLicenseManager::addLicense(const LicenseInfo& license)
	{
		m_licenses.insert(m_licenses.begin() + m_num_customLicenes, license);

		++m_num_customLicenes;
	}

	const Array<LicenseInfo>& CLicenseManager::enumLicenses() const
	{
		return m_licenses;
	}

	const String& CLicenseManager::getUniqueID() const
	{
		return m_uniqueID;
	}

	void CLicenseManager::disableDefaultTrigger()
	{
		m_openIfF1KeyPressed = false;
	}
}
