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

# include <Siv3D/Logger.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CLogger.hpp"

namespace s3d
{
	using namespace std::literals;

	const int64 g_applicationTime = Time::GetMillisec();

	namespace detail
	{
		static constexpr std::string_view HeaderA =
			"<!DOCTYPE html>\n<html lang=\"ja\">\n<head>\n<meta charset=\"UTF-8\" />\n<title>"sv;

		static constexpr std::string_view HeaderB =
u8R"(</title>
<style>
body		{ background-color: #f9f9f9; font-family: 'Segoe UI','メイリオ','Meiryo','ヒラギノ角ゴ Pro W3','Hiragino Kaku Gothic Pro','Osaka','ＭＳ Ｐゴシック','MS PGothic','Arial',sans-serif; }
h2			{ color: #333333; text-align: center; font-size: 28px; }
div			{ font-size: 14px; line-height: 2; word-wrap: break-word; }
div.error	{ padding-left: 14px; background: #f44336; color: #ffffff; }
div.fail	{ padding-left: 14px; background: #ff9800; color: #ffffff; }
div.warning	{ padding-left: 14px; background: #ff9800; color: #ffffff; }
div.script	{ padding-left: 14px; background: #d9eeda; color: #333333; }
div.app		{ padding-left: 14px; background: #ffffff; color: #333333; }
div.info	{ padding-left: 14px; background: #e3f2fd; color: #333333; }
div.debug	{ padding-left: 14px; background: #f5f5f5; color: #333333; }
div.trace	{ padding-left: 14px; background: #f5f5f5; color: #333333; }
div.messages { margin: 0 10% 28px; padding 0 0 28px; border: 1px solid; border-color: #dddddd; border-radius: 2px; box-shadow: 0 1px 1px rgba(0,0,0,.05); }
</style>
</head>
<body>
<h2>)"sv;

		static constexpr std::string_view HeaderC = "</h2>\n<div class=\"messages\">\n";

		static constexpr std::string_view DivEnd = "</div>\n"sv;

		static constexpr std::string_view Footer = "</div>\n</body>\n</html>"sv;

		static constexpr std::array<StringView, 8> LogLevelStr =
		{
			U"[error] "_sv,
			U"[fail] "_sv,
			U"[warning] "_sv,
			U"[script] "_sv,
			U""_sv,
			U"[info] "_sv,
			U"[debug] "_sv,
			U"[trace] "_sv,
		};

		static constexpr std::array<std::string_view, 8> LogLevelDiv =
		{
			u8R"(<div class="error">)"sv,
			u8R"(<div class="fail">)"sv,
			u8R"(<div class="warning">)"sv,
			u8R"(<div class="script">)"sv,
			u8R"(<div class="app">)"sv,
			u8R"(<div class="info">)"sv,
			u8R"(<div class="debug">)"sv,
			u8R"(<div class="trace">)"sv,
		};

		static void OutputDebug(const int64 timeStamp, const LogDescription desc, const String& text)
		{
			const String output = U"{}: {}{}\n"_fmt(timeStamp, LogLevelStr[FromEnum(desc)], text);
			std::cout << output.narrow();
		}

		[[nodiscard]] static constexpr bool Suppressed(const OutputLevel outputLevel, const LogDescription desc)
		{
			if (outputLevel == OutputLevel::More)
			{
				return false;
			}
			else if (outputLevel == OutputLevel::Normal)
			{
				return desc > LogDescription::Info;
			}
			else
			{
				return desc > LogDescription::Script;
			}
		}
	}

	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
		m_active = false;

		if constexpr (SIV3D_BUILD_TYPE(RELEASE))
		{
			if (!m_hasImportantLog)
			{
				return;
			}
		}

		const String fileName = FileSystem::BaseName(FileSystem::ModulePath()).xml_escaped();
		const std::string titleUTF8 = Unicode::ToUTF8(fileName) + " Log";
		FilePath path;
		
		if (FileSystem::IsSandBoxed())
		{
			path = FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData) + fileName + U"_log.html";
		}
		else
		{
			path = fileName + U"_log.html";
		}

		if (TextWriter writer{ path, TextEncoding::UTF8 })
		{
			writer.writeUTF8(detail::HeaderA);
			writer.writeUTF8(titleUTF8);
			writer.writeUTF8(detail::HeaderB);
			writer.writeUTF8(titleUTF8);
			writer.writeUTF8(detail::HeaderC);
			
			std::lock_guard lock(m_mutex);
			{
				writer.writeUTF8(m_buffer);
				m_buffer.clear();
			}

			writer.writeUTF8(detail::Footer);
		}
	}

	void CLogger::setOutputLevel(const OutputLevel level)
	{
		m_outputLevel = level;
	}

	void CLogger::write(const LogDescription desc, const String& text)
	{
		if (!m_active || detail::Suppressed(m_outputLevel, desc))
		{
			return;
		}

		const int64 timeStamp = Time::GetMillisec() - g_applicationTime;

		std::lock_guard lock(m_mutex);
		{
			detail::OutputDebug(timeStamp, desc, text);

			m_buffer.append(detail::LogLevelDiv[FromEnum(desc)]);
			m_buffer.append(std::to_string(timeStamp) + ": ");
			m_buffer.append(text.xml_escaped().toUTF8());
			m_buffer.append(detail::DivEnd);

			m_hasImportantLog |= (desc == LogDescription::Error);
		}
	}

	void CLogger::writeOnce(const LogDescription desc, const uint32 id, const String& text)
	{
		if (!m_active || detail::Suppressed(m_outputLevel, desc))
		{
			return;
		}

		const int64 timeStamp = Time::GetMillisec() - g_applicationTime;

		std::lock_guard lock(m_mutex);
		{
			if (m_onceFlags.find(id) != m_onceFlags.end())
			{
				return;
			}

			m_onceFlags.insert(id);

			detail::OutputDebug(timeStamp, desc, text);

			m_buffer.append(detail::LogLevelDiv[FromEnum(desc)]);
			m_buffer.append(std::to_string(timeStamp) + ": ");
			m_buffer.append(text.xml_escaped().toUTF8());
			m_buffer.append(detail::DivEnd);

			m_hasImportantLog |= (desc == LogDescription::Error);
		}
	}

	void CLogger::writeRawHTML_UTF8(const std::string_view htmlText)
	{
		if (!m_active)
		{
			return;
		}

		std::lock_guard lock(m_mutex);
		{
			m_buffer.append(htmlText);
		}
	}
}
