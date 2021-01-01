//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "LicenseInfo.hpp"
# include "Array.hpp"

namespace s3d
{
	namespace LicenseManager
	{
		void SetApplicationLicense(const String& applicationName, const LicenseInfo& license);

		void AddLicense(const LicenseInfo& license);

		[[nodiscard]]
		const Array<LicenseInfo>& EnumLicenses();

		void EnableDefaultTrigger();

		void DisableDefaultTrigger();

		void ShowInBrowser();
	}
}
