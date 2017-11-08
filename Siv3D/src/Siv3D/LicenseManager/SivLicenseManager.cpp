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
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/System.hpp>
# include "../Siv3DEngine.hpp"
# include "ILicenseManager.hpp"
# include "../EngineDirectory/EngineDirectory.hpp"

namespace s3d
{
constexpr static char8 header[] =
u8R"(<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8" />
<title>Licenses</title>
<style>
body		{ background-color: #f9f9f9; font-family: 'Segoe UI','メイリオ','Meiryo','ヒラギノ角ゴ Pro W3','Hiragino Kaku Gothic Pro','Osaka','ＭＳ Ｐゴシック','MS PGothic','Arial',sans-serif; }
h3			{ color: #333333; text-align: center; font-size: 28px; }
div			{ font-size: 14px; line-height: 2; word-wrap: break-word; }
div.c0		{ color: #333333; text-align: center; font-size: 20px; }
div.c1		{ padding-bottom: 8px; color: #555555; text-align: center; font-size: 12px; }
div.c2		{ padding-bottom: 24px; color: #888888; text-align: center; font-size: 9px; }
</style>
</head>
<body>
<h3>Licenses</h3>)";

constexpr static char8 footer[] =
u8R"-(<br>
</body>
</html>)-";

constexpr static char8 divEnd[] = u8"</div>\n";

constexpr static char8 licenseC0[] = u8R"-(<div class="c0">)-";

constexpr static char8 licenseC1[] = u8R"-(<div class="c1">)-";

constexpr static char8 licenseC2[] = u8R"-(<div class="c2">)-";

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
			const FilePath path = EngineDirectory::LicensePath();

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
	}
}
