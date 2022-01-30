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

# include <array>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatLiteral.hpp>
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

	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
	
	}

	void CLogger::write(const LogType type, const StringView s)
	{
		if (not m_enabled)
		{
			return;
		}

		const int64 timeStamp = Time::GetMillisec();
		const StringView logTypeName = detail::LogTypeNames[FromEnum(type)];
		const String text = U"{}: {}"_fmt(timeStamp, logTypeName) + s;
		const std::string output = text.narrow();

		std::lock_guard lock{ m_mutex };
		{
		# if SIV3D_PLATFORM(WEB)
			std::cout << output << std::endl;
		# else
			std::clog << output << std::endl;
		# endif
		}
	}

	void CLogger::setEnabled(const bool enabled)
	{
		m_enabled = enabled;
	}	
}
