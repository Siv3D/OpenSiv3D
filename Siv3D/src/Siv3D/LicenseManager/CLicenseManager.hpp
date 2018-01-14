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

# pragma once
# include "ILicenseManager.hpp"

namespace s3d
{
	class CLicenseManager : public ISiv3DLicenseManager
	{
	private:

		Array<LicenseInfo> m_licenses;

		bool m_hasApplicationLicense = false;

		size_t m_num_customLicenes = 0;

	public:

		CLicenseManager();

		~CLicenseManager() override;

		void setApplicationLicense(const LicenseInfo& license) override;

		void addLicense(const LicenseInfo& license) override;

		const Array<LicenseInfo>& enumLicenses() const override;
	};
}
