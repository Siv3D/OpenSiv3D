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

# include <ctime>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Date.hpp>
# include <Siv3D/ByteArrayViewAdapter.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr StringView DayOfWeekJapanese[8]
		{
			U"日"_sv,
			U"月"_sv,
			U"火"_sv,
			U"水"_sv,
			U"木"_sv,
			U"金"_sv,
			U"土"_sv,
			U"null"_sv,
		};

		static constexpr StringView DayOfWeekEnglish[8]
		{
			U"Sunday"_sv,
			U"Monday"_sv,
			U"Tuesday"_sv,
			U"Wednesday"_sv,
			U"Thursday"_sv,
			U"Friday"_sv,
			U"Saturday"_sv,
			U"null"_sv,
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

	String Date::dayOfWeekJP() const
	{
		const int32 dow = FromEnum(dayOfWeek());
		return String(detail::DayOfWeekJapanese[dow < 0 ? 7 : dow]);
	}

	String Date::dayOfWeekEN() const
	{
		const int32 dow = FromEnum(dayOfWeek());
		return String(detail::DayOfWeekEnglish[dow < 0 ? 7 : dow]);
	}

	Date Date::Yesterday()
	{
		return Today() - Days(1);
	}

	Date Date::Tomorrow()
	{
		return Today() + Days(1);
	}

	Date& Date::operator +=(const Days& days)
	{
		return *this = detail::EpochDaysToDate(detail::DateToEpochDays(*this) + days.count());
	}

	Date& Date::operator -=(const Days& days)
	{
		return *this += (-days);
	}

	bool Date::operator <(const Date& other) const noexcept
	{
		return std::memcmp(this, &other, sizeof(Date)) < 0;
	}

	bool Date::operator >(const Date& other) const noexcept
	{
		return std::memcmp(this, &other, sizeof(Date)) > 0;
	}

	bool Date::operator <=(const Date& other) const noexcept
	{
		return !(*this > other);
	}

	bool Date::operator >=(const Date& other) const noexcept
	{
		return !(*this < other);
	}

	size_t Date::hash() const noexcept
	{
		return s3d::Hash::FNV1a(*this);
	}

	Date operator +(const Date& date, const Days& days)
	{
		return detail::EpochDaysToDate(detail::DateToEpochDays(date) + days.count());
	}

	Date operator -(const Date& date, const Days& days)
	{
		return date + (-days);
	}

	Days operator -(const Date& to, const Date& from)
	{
		return Days(detail::DateToEpochDays(to) - detail::DateToEpochDays(from));
	}

	void Formatter(FormatData& formatData, const Date& value)
	{
		formatData.string.append(value.format());
	}
}
