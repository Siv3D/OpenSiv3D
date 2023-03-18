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
# include <Siv3D/LicenseManager/ILicenseManager.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/CacheDirectory/CacheDirectory.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr static std::string_view header =
			R"(<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Licenses</title>
<style>
body		{ background-color: #f9f9f9; font-family: 'Segoe UI','Helvetica Neue','Arial','Hiragino Kaku Gothic ProN','Hiragino Sans','Meiryo',sans-serif; }
h3			{ color: #333333; text-align: center; font-size: 28px; }
div			{ font-size: 14px; line-height: 2; word-wrap: break-word; }
div.c0		{ color: #333333; text-align: center; font-size: 20px; }
div.c1		{ padding-bottom: 8px; color: #555555; text-align: center; font-size: 12px; }
div.c2		{ padding-bottom: 24px; color: #888888; text-align: center; font-size: 9px; }
</style>
</head>
<body>
<h3>Licenses</h3>)";

		constexpr static std::string_view footer =
			R"-(<br>
</body>
</html>)-";

		constexpr static std::string_view divEnd = "</div>\n";

		constexpr static std::string_view licenseC0 = R"-(<div class="c0">)-";

		constexpr static std::string_view licenseC1 = R"-(<div class="c1">)-";

		constexpr static std::string_view licenseC2 = R"-(<div class="c2">)-";
	}

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
			const String& applicationName = SIV3D_ENGINE(LicenseManager)->getApplicationName();
			const FilePath path = (CacheDirectory::Apps(applicationName) + U"Licenses.html");
			{
				TextWriter writer(path);
				writer.writeUTF8(detail::header);

				for (const auto& license : EnumLicenses())
				{
					writer.writelnUTF8(detail::licenseC0);
					writer.writeln(license.title.xml_escaped());
					writer.writelnUTF8(detail::divEnd);

					writer.writelnUTF8(detail::licenseC1);
					writer.writeln(license.copyright.xml_escaped().replaced(U"\n", U"<br>"));
					writer.writelnUTF8(detail::divEnd);

					writer.writelnUTF8(detail::licenseC2);
					writer.writeln(license.text.replaced(U"\n", U"<br>"));
					writer.writelnUTF8(detail::divEnd);
				}

				writer.writeUTF8(detail::footer);
			}

			System::LaunchBrowser(path);
		}
	}
}
