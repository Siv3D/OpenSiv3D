//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/LicenseManager.hpp>

namespace s3d
{
	class ISiv3DLicenseManager
	{
	public:

		static ISiv3DLicenseManager* Create();

		virtual ~ISiv3DLicenseManager() = default;

		virtual void setApplicationLicense(const LicenseInfo& license) = 0;

		virtual void addLicense(const LicenseInfo& license) = 0;

		virtual const Array<LicenseInfo>& enumLicenses() const = 0;
	};
}
