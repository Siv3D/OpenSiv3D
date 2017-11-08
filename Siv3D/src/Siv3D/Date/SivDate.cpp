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

# include <ctime>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Windows.hpp>
# include <Siv3D/Date.hpp>

namespace s3d
{
	namespace detail
	{
		static const String DayOfWeekJapanese[8]
		{
			U"日",
			U"月",
			U"火",
			U"水",
			U"木",
			U"金",
			U"土",
			U"null",
		};

		static const String DayOfWeekEnglish[8]
		{
			U"Sunday",
			U"Monday",
			U"Tuesday",
			U"Wednesday",
			U"Thursday",
			U"Friday",
			U"Saturday",
			U"null",
		};

		static constexpr bool IsLeapYear(const int32 year)
		{
			return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
		}

		static constexpr int daysAtEndOfMonth[2][12]
		{
			{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 }, // normal year
			{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }  // leap year
		};

		static constexpr int32 YearsToDays(const int32 years)
		{
			return 365 * years + years / 4 - years / 100 + years / 400;
		}

		static int32 DaysToYears(const int32 days)
		{
			const int32 daysIn1Year = 365;
			const int32 daysIn4Years = daysIn1Year * 4 + 1;
			const int32 daysIn100Years = daysIn4Years * 25 - 1;
			const int32 daysIn400Years = daysIn100Years * 4 + 1;
			const int32 days400YearsPeriod = std::min(days%daysIn400Years, daysIn100Years * 4 - 1);
			const int32 days100YearsPeriod = days400YearsPeriod % daysIn100Years;
			const int32 days4YearsPeriod = std::min(days100YearsPeriod%daysIn4Years, daysIn1Year * 4 - 1);

			return days / daysIn400Years * 400
				+ days400YearsPeriod / daysIn100Years * 100
				+ days100YearsPeriod / daysIn4Years * 4
				+ days4YearsPeriod / daysIn1Year;
		}

		static int32 DateToEpochDays(const Date& Date)
		{
			return YearsToDays(Date.year - 1)
				+ daysAtEndOfMonth[IsLeapYear(Date.year)][Date.month - 1]
				+ Date.day - 1;
		}

		static Date EpochDaysToDate(const int32 epochDays)
		{
			const int32 years = DaysToYears(epochDays) + 1;
			const int32 daysAYearPeriod = epochDays - YearsToDays(years - 1);
			const auto january = std::begin(daysAtEndOfMonth[IsLeapYear(years)]);
			const auto months = std::distance(january, std::upper_bound(january, january + 12, daysAYearPeriod));
			const auto days = daysAYearPeriod - (daysAtEndOfMonth[IsLeapYear(years)][months - 1]) + 1;

			return Date(years, static_cast<int32>(months), static_cast<int32>(days));
		}
	}

	const String& Date::dayOfWeekJP() const
	{
		const int32 dow = dayOfWeek();
		return detail::DayOfWeekJapanese[dow < 0 ? 7 : dow];
	}

	const String& Date::dayOfWeekEN() const
	{
		const int32 dow = dayOfWeek();
		return detail::DayOfWeekEnglish[dow < 0 ? 7 : dow];
	}

	bool Date::isToday() const
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		SYSTEMTIME sysTime;
		::GetLocalTime(&sysTime);
		return (day == sysTime.wDay && month == sysTime.wMonth && year == sysTime.wYear);

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		::time_t t = ::time(nullptr);
        ::tm lt;
        ::localtime_r(&t, &lt);
		return (day == lt.tm_mday && month == (1 + lt.tm_mon) && year == (1900 + lt.tm_year));

	# endif
	}

	Date Date::Today()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		SYSTEMTIME sysTime;
		::GetLocalTime(&sysTime);
		return Date(sysTime.wYear, sysTime.wMonth, sysTime.wDay);

	# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

		::time_t t = ::time(nullptr);
		::tm* lt = ::localtime(&t);
		return Date(1900 + lt->tm_year, lt->tm_mon + 1, lt->tm_mday);

	# endif
	}

	Date& Date::operator +=(const Days& days)
	{
		return *this = detail::EpochDaysToDate(detail::DateToEpochDays(*this) + days.count());
	}

	Date operator +(const Date& date, const Days& days)
	{
		return detail::EpochDaysToDate(detail::DateToEpochDays(date) + days.count());
	}

	Days operator -(const Date& to, const Date& from)
	{
		return Days(detail::DateToEpochDays(to) - detail::DateToEpochDays(from));
	}
}
