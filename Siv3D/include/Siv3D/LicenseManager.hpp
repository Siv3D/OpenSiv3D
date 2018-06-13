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
		void SetApplicationLicense(const LicenseInfo& license);

		void AddLicense(const LicenseInfo& license);

		[[nodiscard]] const Array<LicenseInfo>& EnumLicenses();

		void ShowInBrowser();
	}
}
