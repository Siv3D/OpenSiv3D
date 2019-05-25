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

		virtual void update() = 0;

		virtual void setApplicationLicense(const String& uniqueID, const LicenseInfo& license) = 0;

		virtual void addLicense(const LicenseInfo& license) = 0;

		virtual const Array<LicenseInfo>& enumLicenses() const = 0;

		virtual const String& getUniqueID() const = 0;

		virtual void disableDefaultTrigger() = 0;
	};
}
