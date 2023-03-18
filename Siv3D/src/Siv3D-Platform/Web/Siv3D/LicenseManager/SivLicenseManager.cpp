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

# include <Siv3D/LicenseManager.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/Version.hpp>
# include <Siv3D/LicenseManager/ILicenseManager.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/CacheDirectory/CacheDirectory.hpp>

namespace s3d
{
	namespace LicenseManager
	{
		void SetApplicationLicense(const String& applicationName, const LicenseInfo& license)
		{
			SIV3D_ENGINE(LicenseManager)->setApplicationLicense(applicationName, license);
		}

		void AddLicense(const LicenseInfo& license)
		{
			SIV3D_ENGINE(LicenseManager)->addLicense(license);
		}

		const Array<LicenseInfo>& EnumLicenses()
		{
			return SIV3D_ENGINE(LicenseManager)->enumLicenses();
		}

		void EnableDefaultTrigger()
		{
			SIV3D_ENGINE(LicenseManager)->setDefaultTriggerRnabled(true);
		}

		void DisableDefaultTrigger()
		{
			SIV3D_ENGINE(LicenseManager)->setDefaultTriggerRnabled(false);
		}

		void ShowInBrowser()
		{
			const String& licenseUrl = U"https://siv3d.jp/web/license/" SIV3D_VERSION_SHORT_STRING U"/license.html";
			System::LaunchBrowser(licenseUrl);
		}
	}
}
