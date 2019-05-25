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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/ByteArrayViewAdapter.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr int32 TimeToMillisecCount(const int32 hour, const int32 minute, const int32 second, const int32 milliseconds)
		{
			return hour * (60 * 60 * 1000)
				+ minute * (60 * 1000)
				+ second * (1000)
				+ milliseconds;
		}

		static constexpr StringView MonthEnglish[12]
		{
			U"January"_sv,
			U"February"_sv,
			U"March"_sv,
			U"April"_sv,
			U"May"_sv,
			U"June"_sv,
			U"July"_sv,
			U"August"_sv,
			U"September"_sv,
			U"October"_sv,
			U"November"_sv,
			U"December"_sv,
		};

		static constexpr StringView AMPM[2]
		{
			U"AM"_sv,
			U"PM"_sv,
		};

		static constexpr StringView FormatPatterns[22]
		{
			U"yyyy"_sv,
			U"yy"_sv,
			U"y"_sv,
			U"MMMM"_sv,
			U"MMM"_sv,
			U"MM"_sv,
			U"M"_sv,
			U"dd"_sv,
			U"d"_sv,
			U"EEEE"_sv,
			U"EEE"_sv,
			U"E"_sv,
			U"a"_sv,
			U"HH"_sv,
			U"H"_sv,
			U"hh"_sv,
			U"h"_sv,
			U"mm"_sv,
			U"ss"_sv,
			U"S"_sv,
			U"SS"_sv,
			U"SSS"_sv,
		};
	}

	static String GetFormattedElement(const DateTime& date, const StringView format, const bool isCalendar)
	{
		const size_t formatIndex = std::distance(
			std::begin(detail::FormatPatterns),
			std::find(std::begin(detail::FormatPatterns),
				isCalendar ? std::begin(detail::FormatPatterns) + 12 : std::end(detail::FormatPatterns),
				format)
		);

		if (isCalendar && formatIndex >= 12)
		{
			return String();
		}

		switch (formatIndex)
		{
		case 0:	// yyyy	4 桁の年 (0001-)
			return Pad(date.year, { 4, U'0' });
		case 1:	// yy	2 桁の年 (00-99)
			return Pad(date.year % 100, { 2, U'0' });
		case 2:	// y	年 (1-)
			return ToString(date.year);
		case 3:	// MMMM	英語の月 (January-December)
			return String(detail::MonthEnglish[date.month - 1]);
		case 4:	// MMM	英語の月の略称 (Jan-Dec)
			return String(detail::MonthEnglish[date.month - 1].substr(0, 3));
		case 5:	// MM	2 桁の月 (01-12)
			return Pad(date.month, { 2, U'0' });
		case 6:	// M	1-2 桁の月 (1-12)
			return ToString(date.month);
		case 7:	// dd	2 桁の日 (01-31)
			return Pad(date.day, { 2, U'0' });
		case 8:	// d	1-2 桁の日 (1-31)
			return ToString(date.day);
		case 9:	// EEEE 英語の曜日 (Sunday-Satueday)
			return date.dayOfWeekEN();
		case 10: // EEE	英語の曜日の略称 (Sun-Sat)
			return date.dayOfWeekEN().substr(0, 3);
		case 11: // E	日本語の曜日 (日-土)
			return date.dayOfWeekJP();
		case 12: // a	午前/午後 (AM/PM)
			return String(detail::AMPM[date.hour > 11]);
		case 13: // HH	24 時間表記の 2 桁の時 (00-23)
			return Pad(date.hour, { 2, U'0' });
		case 14: // H	24 時間表記の時 (0-23)
			return ToString(date.hour);
		case 15: // hh	12 時間表記の 2 桁の時 (00-11)
			return Pad(date.hour % 12, { 2, U'0' });
		case 16: // h	12 時間表記の時 (0-11)
			return ToString(date.hour % 12);
		case 17: // mm	2 桁の分 (00-59)
			return Pad(date.minute, { 2, U'0' });
		case 18: // ss	2 桁の秒 (00-59)
			return Pad(date.second, { 2, U'0' });
		case 19: // S	小数点以下 1 桁の秒 (0-9)
			return ToString(date.milliseconds / 100);
		case 20: // SS	小数点以下 2 桁の秒 (00-99)
			return Pad(date.milliseconds / 10, { 2, U'0' });
		case 21: // SSS	小数点以下 3 桁の秒 (000-999)
			return Pad(date.milliseconds, { 3, U'0' });
		default:
			return String();
		}
	}

	static String FormatDateTime(const DateTime & date, const StringView format, const bool isCalendar)
	{
		String formattedDateTime, keyPattern;

		bool inQuot = false;

		char32 previousChar = U'\0';

		for (size_t i = 0; i < format.length(); ++i)
		{
			const char32 ch = format[i];

			if (IsAlpha(ch))
			{
				if (inQuot)
				{
					formattedDateTime << ch;
				}
				else
				{
					if (keyPattern.isEmpty() || ch == previousChar)
					{
						keyPattern.push_back(ch);
					}
					else
					{
						formattedDateTime += GetFormattedElement(date, keyPattern, isCalendar);
						keyPattern.clear();
						keyPattern.push_back(ch);
					}
				}
			}
			else
			{
				if (!keyPattern.isEmpty())
				{
					formattedDateTime += GetFormattedElement(date, keyPattern, isCalendar);
					keyPattern.clear();
				}

				if (ch == U'\'')
				{
					if (format[i + 1] == U'\'')
					{
						formattedDateTime << U'\'';

						++i;

						continue;
					}

					inQuot = !inQuot;
				}
				else
				{
					formattedDateTime << ch;
				}
			}

			previousChar = ch;
		}

		if (!keyPattern.isEmpty())
		{
			formattedDateTime += GetFormattedElement(date, keyPattern, isCalendar);
		}

		return formattedDateTime;
	}

	String Date::format(const StringView format) const
	{
		return FormatDateTime(*this, format, true);
	}

	String DateTime::format(const StringView format) const
	{
		return FormatDateTime(*this, format, false);
	}

	DateTime& DateTime::operator +=(const Days & days)
	{
		Date::operator +=(days);
		return *this;
	}

	DateTime& DateTime::operator -=(const Days & days)
	{
		Date::operator -=(days);
		return *this;
	}

	DateTime& DateTime::operator +=(const Milliseconds & _milliseconds)
	{
		const int64 millisecIn1Day = 86400 * 1000;

		int64 count = _milliseconds.count();

		if (const int64 days = count / millisecIn1Day)
		{
			Date::operator +=(Days(days));

			count -= days * millisecIn1Day;
		}

		int64 newCount = detail::TimeToMillisecCount(hour, minute, second, milliseconds) + count;

		if (newCount >= millisecIn1Day)
		{
			Date::operator +=(Days(1));

			newCount -= millisecIn1Day;
		}
		else if (newCount < 0)
		{
			Date::operator -=(Days(1));

			newCount += millisecIn1Day;
		}

		hour = static_cast<int32>(newCount / (60 * 60 * 1000));
		minute = static_cast<int32>(newCount / (60 * 1000) % 60);
		second = static_cast<int32>(newCount / (1000) % 60);
		milliseconds = static_cast<int32>(newCount % 1000);

		return *this;
	}

	DateTime & DateTime::operator -=(const Milliseconds & _milliseconds)
	{
		return *this += (-_milliseconds);
	}

	bool DateTime::operator ==(const DateTime & other) const noexcept
	{
		return std::memcmp(this, &other, sizeof(DateTime)) == 0;
	}

	bool DateTime::operator !=(const DateTime & other) const noexcept
	{
		return std::memcmp(this, &other, sizeof(DateTime)) != 0;
	}

	bool DateTime::operator <(const DateTime & other) const noexcept
	{
		return std::memcmp(this, &other, sizeof(DateTime)) < 0;
	}

	bool DateTime::operator >(const DateTime & other) const noexcept
	{
		return std::memcmp(this, &other, sizeof(DateTime)) > 0;
	}

	bool DateTime::operator <=(const DateTime & other) const noexcept
	{
		return !(*this > other);
	}

	bool DateTime::operator >=(const DateTime & other) const noexcept
	{
		return !(*this < other);
	}

	size_t DateTime::hash() const noexcept
	{
		return s3d::Hash::FNV1a(*this);
	}

	DateTime operator +(const DateTime & dateTime, const Days & days)
	{
		return DateTime(dateTime) += days;
	}

	DateTime operator -(const DateTime & dateTime, const Days & days)
	{
		return DateTime(dateTime) -= days;
	}

	DateTime operator +(const DateTime & dateTime, const Milliseconds & milliseconds)
	{
		return DateTime(dateTime) += milliseconds;
	}

	DateTime operator -(const DateTime & dateTime, const Milliseconds & milliseconds)
	{
		return DateTime(dateTime) -= milliseconds;
	}

	Duration operator -(const DateTime & a, const DateTime & b)
	{
		const auto diffDays = Date(a) - Date(b);
		const auto aMillisec = detail::TimeToMillisecCount(a.hour, a.minute, a.second, a.milliseconds);
		const auto bMillisec = detail::TimeToMillisecCount(b.hour, b.minute, b.second, b.milliseconds);

		return Duration((static_cast<int64>(diffDays.count()) * (86400 * 1000) + (aMillisec - bMillisec)) / 1000.0);
	}

	void Formatter(FormatData & formatData, const DateTime & value)
	{
		formatData.string.append(value.format());
	}
}
