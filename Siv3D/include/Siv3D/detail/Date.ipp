//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "../Utility.hpp"
# include "../Hash.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr int32 DaysInMonth[2][12]
		{
			{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	// common year
			{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	// leap year
		};

		inline constexpr uint8 GetDayOfWeek(const int32 year, const int32 month, const int32 day) noexcept
		{
			return static_cast<uint8>(((month == 1 || month == 2) ?
				((year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + (13 * (month + 12) + 8) / 5 + day) % 7
				: (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7));
		}

		inline constexpr int32 YearsToDays(const int32 years)
		{
			return (365 * years + years / 4 - years / 100 + years / 400);
		}

		inline constexpr int32 DaysAtEndOfMonth[2][12]
		{
			{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 }, // normal year
			{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }  // leap year
		};

		inline constexpr int32 DateToEpochDays(const Date& date)
		{
			return YearsToDays(date.year - 1)
				+ DaysAtEndOfMonth[Date::IsLeapYear(date.year)][date.month - 1]
				+ (date.day - 1);
		}

		inline constexpr int32 DaysToYears(const int32 days)
		{
			const int32 daysIn1Year			= 365;
			const int32 daysIn4Years		= daysIn1Year * 4 + 1;
			const int32 daysIn100Years		= daysIn4Years * 25 - 1;
			const int32 daysIn400Years		= daysIn100Years * 4 + 1;
			const int32 days400YearsPeriod	= Min(days % daysIn400Years, daysIn100Years * 4 - 1);
			const int32 days100YearsPeriod	= days400YearsPeriod % daysIn100Years;
			const int32 days4YearsPeriod	= Min(days100YearsPeriod % daysIn4Years, daysIn1Year * 4 - 1);

			return (days / daysIn400Years * 400)
				+ (days400YearsPeriod / daysIn100Years * 100)
				+ (days100YearsPeriod / daysIn4Years * 4)
				+ (days4YearsPeriod / daysIn1Year);
		}

		inline Date EpochDaysToDate(const int32 epochDays)
		{
			const int32 years			= DaysToYears(epochDays) + 1;
			const bool isLeapYear		= Date::IsLeapYear(years);
			const int32 daysAYearPeriod	= epochDays - YearsToDays(years - 1);
			const auto january			= std::begin(DaysAtEndOfMonth[isLeapYear]);
			const int32 months			= static_cast<int32>(std::distance(january, std::upper_bound(january, january + 12, daysAYearPeriod)));
			const int32 days			= daysAYearPeriod - (DaysAtEndOfMonth[isLeapYear][(months - 1)]) + 1;

			return Date(years, months, days);
		}
	}

	inline constexpr Date::Date(const int32 _year, const int32 _month, const int32 _day) noexcept
		: year{ _year }
		, month{ _month }
		, day{ _day } {}

	inline constexpr DayOfWeek Date::dayOfWeek() const noexcept
	{
		return DayOfWeek{ detail::GetDayOfWeek(year, month, day) };
	}

	inline bool Date::isToday() const noexcept
	{
		return (*this == Date::Today());
	}

	inline constexpr bool Date::isLeapYear() const noexcept
	{
		return IsLeapYear(year);
	}

	inline constexpr int32 Date::daysInYear() const noexcept
	{
		return DaysInYear(year);
	}

	inline constexpr int32 Date::daysInMonth() const noexcept
	{
		return DaysInMonth(year, month);
	}

	inline constexpr bool Date::isValid() const noexcept
	{
		return InRange(month, 1, 12)
			&& InRange(day, 1, daysInMonth());
	}

	inline String Date::format(const StringView format) const
	{
		return FormatDate(*this, format);
	}

	inline Date Date::operator +(const Days& days) const noexcept
	{
		return detail::EpochDaysToDate(detail::DateToEpochDays(*this) + days.count());
	}

	inline Date Date::operator -(const Days& days) const noexcept
	{
		return *this + (-days);
	}

	inline Date& Date::operator +=(const Days& days) noexcept
	{
		return *this = detail::EpochDaysToDate(detail::DateToEpochDays(*this) + days.count());
	}

	inline Date& Date::operator -=(const Days& days) noexcept
	{
		return *this += (-days);
	}

	inline size_t Date::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline Date Date::Yesterday() noexcept
	{
		return Today() - Days{ 1 };
	}

	inline Date Date::Tomorrow() noexcept
	{
		return Today() + Days{ 1 };
	}

	inline constexpr bool Date::IsLeapYear(const int32 year) noexcept
	{
		return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	inline constexpr int32 Date::DaysInYear(const int32 year) noexcept
	{
		return IsLeapYear(year) ? 366 : 365;
	}

	inline constexpr int32 Date::DaysInMonth(const int32 year, const int32 month) noexcept
	{
		if (not InRange(month, 1, 12))
		{
			return 0;
		}

		return detail::DaysInMonth[IsLeapYear(year)][month - 1];
	}

	inline constexpr Days Date::Subtract(const Date& a, const Date& b) noexcept
	{
		return Days(detail::DateToEpochDays(a) - detail::DateToEpochDays(b));
	}
}
