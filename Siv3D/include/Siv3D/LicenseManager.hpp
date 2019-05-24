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
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	struct LicenseInfo
	{
		String name;

		String copyright;

		String text;
	};

	namespace LicenseManager
	{
		void SetApplicationLicense(const String& uniqueID, const LicenseInfo& license);

		void AddLicense(const LicenseInfo& license);

		[[nodiscard]] const Array<LicenseInfo>& EnumLicenses();

		void ShowInBrowser();

		void DisableDefaultTrigger();
	}
}
