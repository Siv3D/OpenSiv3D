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

# include <Siv3D/Keyboard.hpp>
# include <Siv3D/FileSystem.hpp>
# include "CLicenseManager.hpp"

namespace s3d
{
	CLicenseManager::CLicenseManager()
		: m_licenses()
	{
		m_applicationName = FileSystem::BaseName(FileSystem::ModulePath());
	}

	CLicenseManager::~CLicenseManager()
	{

	}

	void CLicenseManager::update()
	{
		if (m_openLicenseWithF1Key
			&& KeyF1.down())
		{
			LicenseManager::ShowInBrowser();
		}
	}

	void CLicenseManager::setApplicationLicense(const String& applicationName, const LicenseInfo& license)
	{

	}

	void CLicenseManager::addLicense(const LicenseInfo& license)
	{

	}

	const Array<LicenseInfo>& CLicenseManager::enumLicenses() const noexcept
	{
		return m_licenses;
	}

	const String& CLicenseManager::getApplicationName() const noexcept
	{
		return m_applicationName;
	}

	void CLicenseManager::setDefaultTriggerRnabled(const bool enabled) noexcept
	{
		m_openLicenseWithF1Key = enabled;
	}
}
