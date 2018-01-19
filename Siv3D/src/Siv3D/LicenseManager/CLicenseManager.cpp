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

# include "CLicenseManager.hpp"
# include "LicenseList.hpp"

namespace s3d
{
	CLicenseManager::CLicenseManager()
		: m_licenses(licenses)
	{

	}

	CLicenseManager::~CLicenseManager()
	{

	}

	void CLicenseManager::setApplicationLicense(const LicenseInfo& license)
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
}
