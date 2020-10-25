﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Version.hpp>
# include "ILicenseManager.hpp"

namespace s3d
{
	class CLicenseManager final : public ISiv3DLicenseManager
	{
	private:

		Array<LicenseInfo> m_licenses;

		bool m_hasApplicationLicense = false;

		size_t m_num_customLicenses = 0;

		String m_normalizedApplicationName = SIV3D_VERSION;

		bool m_openLicenseWithF1Key = true;

	public:

		CLicenseManager();

		~CLicenseManager() override;

		void update() override;

		void setApplicationLicense(const String& applicationName, const LicenseInfo& license) override;

		void addLicense(const LicenseInfo& license) override;

		const Array<LicenseInfo>& enumLicenses() const noexcept override;

		const String& getNormalizedApplicationName() const noexcept override;

		void setDefaultTriggerRnabled(bool enabled) noexcept override;
	};
}
