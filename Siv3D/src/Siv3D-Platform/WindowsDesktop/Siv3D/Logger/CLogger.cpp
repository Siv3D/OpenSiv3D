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

# include <array>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/Time.hpp>
# include "CLogger.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr std::array<StringView, 7> LogTypeNames =
		{
			U"[error]   "_sv,
			U"[fail]    "_sv,
			U"[warning] "_sv,
			U""_sv,
			U"[info]    "_sv,
			U"[trace]   "_sv,
			U"[verbose] "_sv,
		};
	}

	CLogger::CLogger() = default;

	CLogger::~CLogger() = default;

	void CLogger::write(const LogType type, const StringView s)
	{
		if (not m_enabled)
		{
			return;
		}

		const int64 timeStamp = Time::GetMillisec();
		const StringView logTypeName = detail::LogTypeNames[FromEnum(type)];
		const String text = U"{}: {}"_fmt(timeStamp, logTypeName) + s + U'\n';
		const std::wstring output = text.toWstr();

		std::lock_guard lock{ m_mutex };
		{
			::OutputDebugStringW(output.c_str());
		}
	}

	void CLogger::setEnabled(const bool enabled)
	{
		m_enabled = enabled;
	}
}
