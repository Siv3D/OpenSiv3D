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

# include <Siv3D/LicenseManager.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/LicenseManager/ILicenseManager.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/CacheDirectory/CacheDirectory.hpp>

# if !defined(SIV3D_SHORT_VERSION_STRING)
#   define SIV3D_SHORT_VERSION_STRING U"0.6.3"
# endif

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
			const String& licenseUrl = U"siv3d.jp/web/license/" SIV3D_SHORT_VERSION_STRING U"/license.html";
			System::LaunchBrowser(licenseUrl);
		}
	}
}
