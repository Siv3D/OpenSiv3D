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

# include <Siv3D/LicenseManager.hpp>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/System.hpp>
# include <Siv3DEngine.hpp>
# include <EngineDirectory/EngineDirectory.hpp>
# include "ILicenseManager.hpp"

namespace s3d
{
constexpr static char header[] =
R"(<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8" />
<title>Licenses</title>
<style>
body		{ background-color: #f9f9f9; font-family: 'Segoe UI','Meiryo','Hiragino Kaku Gothic Pro','Osaka','MS PGothic','Arial',sans-serif; }
h3			{ color: #333333; text-align: center; font-size: 28px; }
div			{ font-size: 14px; line-height: 2; word-wrap: break-word; }
div.c0		{ color: #333333; text-align: center; font-size: 20px; }
div.c1		{ padding-bottom: 8px; color: #555555; text-align: center; font-size: 12px; }
div.c2		{ padding-bottom: 24px; color: #888888; text-align: center; font-size: 9px; }
</style>
</head>
<body>
<h3>Licenses</h3>)";

constexpr static char footer[] =
R"-(<br>
</body>
</html>)-";

constexpr static char divEnd[] = "</div>\n";

constexpr static char licenseC0[] = R"-(<div class="c0">)-";

constexpr static char licenseC1[] = R"-(<div class="c1">)-";

constexpr static char licenseC2[] = R"-(<div class="c2">)-";

	namespace LicenseManager
	{
		void SetApplicationLicense(const String& uniqueID, const LicenseInfo& license)
		{
			Siv3DEngine::Get<ISiv3DLicenseManager>()->setApplicationLicense(uniqueID, license);
		}

		void AddLicense(const LicenseInfo& license)
		{
			Siv3DEngine::Get<ISiv3DLicenseManager>()->addLicense(license);
		}

		const Array<LicenseInfo>& EnumLicenses()
		{
			return Siv3DEngine::Get<ISiv3DLicenseManager>()->enumLicenses();
		}

		void ShowInBrowser()
		{
			const String& uniqueID = Siv3DEngine::Get<ISiv3DLicenseManager>()->getUniqueID();

			const FilePath path = uniqueID ? EngineDirectory::ApplicationLicensePath(uniqueID)
				: EngineDirectory::DefaultLicensePath();
			{
				TextWriter writer(path);
				writer.writeUTF8(header);

				for (const auto& license : EnumLicenses())
				{
					writer.writelnUTF8(licenseC0);
					writer.writeln(license.name);
					writer.writelnUTF8(divEnd);

					writer.writelnUTF8(licenseC1);
					writer.writeln(license.copyright.replaced(U"\n", U"<br>"));
					writer.writelnUTF8(divEnd);

					writer.writelnUTF8(licenseC2);
					writer.writeln(license.text.replaced(U"\n", U"<br>"));
					writer.writelnUTF8(divEnd);
				}

				writer.writeUTF8(footer);
			}
			
			System::LaunchBrowser(path);
		}

		void DisableDefaultTrigger()
		{
			Siv3DEngine::Get<ISiv3DLicenseManager>()->disableDefaultTrigger();
		}
	}
}
