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

# include <Siv3D/Logger.hpp>
# include "CLogger.hpp"
# include "../Siv3DEngine.hpp"
# include "../LicenseManager/ILicenseManager.hpp"

namespace s3d
{
constexpr static char headerA[] =
u8R"(<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8" />
<title>)";

constexpr static char headerB[] =
u8R"(</title>
<style>
body		{ background-color: #f9f9f9; font-family: 'Segoe UI','メイリオ','Meiryo','ヒラギノ角ゴ Pro W3','Hiragino Kaku Gothic Pro','Osaka','ＭＳ Ｐゴシック','MS PGothic','Arial',sans-serif; }
h2			{ color: #333333; text-align: center; font-size: 28px; }
h3			{ color: #333333; text-align: center; font-size: 24px; }
div			{ font-size: 14px; line-height: 2; word-wrap: break-word; }
div.error	{ padding-left: 14px; background: #f44336; color: #ffffff; }
div.fail	{ padding-left: 14px; background: #ff9800; color: #ffffff; }
div.warning	{ padding-left: 14px; background: #ff9800; color: #ffffff; }
div.script	{ padding-left: 14px; background: #d9eeda; color: #333333; }
div.app		{ padding-left: 14px; background: #ffffff; color: #333333; }
div.info	{ padding-left: 14px; background: #e3f2fd; color: #333333; }
div.debug	{ padding-left: 14px; background: #f5f5f5; color: #333333; }
div.c0		{ color: #333333; text-align: center; font-size: 20px; }
div.c1		{ padding-bottom: 8px; color: #555555; text-align: center; font-size: 12px; }
div.c2		{ padding-bottom: 24px; color: #888888; text-align: center; font-size: 9px; }
div.messages { margin: 0 10% 28px; padding 0 0 28px; border: 1px solid; border-color: #dddddd; border-radius: 2px; box-shadow: 0 1px 1px rgba(0,0,0,.05); }
</style>
</head>
<body>
<h2>)";

constexpr static char headerC[] =
u8R"(</h2>
<div class="messages">
)";

constexpr static char headerD[] =
u8R"(Licenses</title>
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
<div>)";

const static std::string logLevel[]{
	u8R"(<div class="error">)",
	u8R"(<div class="fail">)",
	u8R"(<div class="warning">)",
	u8R"(<div class="script">)",
	u8R"(<div class="app">)",
	u8R"(<div class="info">)",
	u8R"(<div class="debug">)",
};

constexpr static char8 divEnd[] = u8"</div>\n";

constexpr static char8 licenseC0[] = u8R"-(<div class="c0">)-";

constexpr static char8 licenseC1[] = u8R"-(<div class="c1">)-";

constexpr static char8 licenseC2[] = u8R"-(<div class="c2">)-";

constexpr static char8 footerA[] =
u8R"-(</div><br>
<h3>Licenses</h3>)-";

constexpr static char8 footerB[] =
u8R"-(</body>
</html>)-";
}

# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>

namespace s3d
{
	namespace detail
	{
		const static std::wstring logLevelStr[] =
		{
			L"[error] ",
			L"[fail] ",
			L"[warning] ",
			L"[script] ",
			L"",
			L"[info] ",
			L"[debug] ",
		};

		static void OutputDebug(const LogDescription desc, const String& text)
		{
			const std::wstring textW = text.toWstr();
			
			std::wstring output;
			output.reserve(logLevelStr[static_cast<size_t>(desc)].length() + textW.length() + 1);
			output.append(logLevelStr[static_cast<size_t>(desc)]);
			output.append(textW);
			output.push_back(L'\n');

			::OutputDebugStringW(output.c_str());
		}
	}
}

# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <iostream>
# include <locale>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace detail
	{
		const static std::string logLevelStr[] =
		{
			"[error]",
			"[fail]",
			"[warning]",
			"[script]",
			"",
			"[info]",
			"[debug]",
		};

		static void OutputDebug(const LogDescription desc, const String& text)
		{
			if (desc != LogDescription::App)
			{
				std::cout << logLevelStr[static_cast<size_t>(desc)];
			}

			std::cout << Unicode::ToUTF8(text) << '\n';
		}
	}
}

# endif

namespace s3d
{
	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
		m_initialized = false;

		m_writer.writeUTF8(footerA);

		outputLicenses();

		m_writer.writeUTF8(footerB);

		const FilePath path = m_writer.path();

		m_writer.close();

		if (m_removeFileOnExit && !m_hasImportantLog)
		{
			FileSystem::Remove(path);
		}
	}

	bool CLogger::init()
	{
		const String fileName = FileSystem::BaseName(FileSystem::ModulePath()).xml_escaped();
		const std::string titleUTF8 = Unicode::ToUTF8(fileName) + " Log";

		m_writer.open(fileName + U"_log.html", TextEncoding::UTF8);
		m_writer.writeUTF8(headerA);
		m_writer.writeUTF8(titleUTF8);
		m_writer.writeUTF8(headerB);
		m_writer.writeUTF8(titleUTF8);
		m_writer.writeUTF8(headerC);

		//write(LogDescription::App, L"App Message");
		//write(LogDescription::Debug, L"Debug Message");
		//write(LogDescription::Error , L"Error Message");
		//write(LogDescription::Fail, L"Fail Message");
		//write(LogDescription::Info, L"Info Message");
		//write(LogDescription::Script, L"Script Message");
		//write(LogDescription::Warning, L"Warning Message");

		m_initialized = true;

		return true;
	}

	void CLogger::setOutputLevel(const OutputLevel level)
	{
		m_outputLevel = level;
	}

	void CLogger::write(const LogDescription desc, const String& text)
	{
		if (suppressed(desc))
		{
			return;
		}

		std::lock_guard<std::mutex> lock(m_mutex);

		detail::OutputDebug(desc, text);

		m_writer.writeUTF8(logLevel[static_cast<size_t>(desc)]);

		m_writer.write(text.xml_escaped());

		m_writer.writeUTF8(divEnd);

		if (desc == LogDescription::Error)
		{
			m_hasImportantLog = true;
		}
	}

	void CLogger::writeRawHTML(const String& htmlText)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_writer.writeln(htmlText);
	}

	void CLogger::writeRawHTML_UTF8(const std::string_view htmlText)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_writer.writelnUTF8(htmlText);
	}

	void CLogger::removeOnExit()
	{
		m_removeFileOnExit = true;
	}

	void CLogger::outputLicenses()
	{
		if (m_removeFileOnExit)
		{
			return;
		}

		for (const auto& license : Siv3DEngine::GetLicenseManager()->enumLicenses())
		{
			m_writer.writelnUTF8(licenseC0);
			m_writer.writeln(license.name);
			m_writer.writelnUTF8(divEnd);

			m_writer.writelnUTF8(licenseC1);
			m_writer.writeln(license.copyright.replaced(U"\n", U"<br>"));
			m_writer.writelnUTF8(divEnd);

			m_writer.writelnUTF8(licenseC2);
			m_writer.writeln(license.text.replaced(U"\n", U"<br>"));
			m_writer.writelnUTF8(divEnd);
		}
	}

	bool CLogger::suppressed(const LogDescription desc) const
	{
		if (m_outputLevel == OutputLevel::More)
		{
			return false;
		}
		else if (m_outputLevel == OutputLevel::Normal)
		{
			return desc > LogDescription::Info;
		}
		else
		{
			return desc > LogDescription::Script;
		}
	}
}
