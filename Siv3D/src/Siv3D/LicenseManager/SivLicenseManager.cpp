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

# include <Siv3D/LicenseManager.hpp>
# include "../Siv3DEngine.hpp"
# include "ILicenseManager.hpp"

namespace s3d
{
	namespace LicenseManager
	{
		void SetApplicationLicense(const LicenseInfo& license)
		{
			Siv3DEngine::GetLicenseManager()->setApplicationLicense(license);
		}

		void AddLicense(const LicenseInfo& license)
		{
			Siv3DEngine::GetLicenseManager()->addLicense(license);
		}

		const Array<LicenseInfo>& EnumLicenses()
		{
			return Siv3DEngine::GetLicenseManager()->enumLicenses();
		}

		void ShowInBrowser()
		{

		}
	}
}
