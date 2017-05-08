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

# include <Siv3D/Fwd.hpp>

# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <sys/time.h>

# endif

# include <Siv3D/DateTime.hpp>
# include <Siv3D/FormatUtility.hpp>

namespace s3d
{
	namespace detail
	{
		# if defined(SIV3D_TARGET_WINDOWS)

			static constexpr DateTime ToDateTime(const SYSTEMTIME& in)
			{
				return{ in.wYear, in.wMonth, in.wDay, in.wHour, in.wMinute, in.wSecond, in.wMilliseconds };
			}

		# endif

		static constexpr int32 TimeToMillisecCount(const int32 hour, const int32 minute, const int32 second, const int32 milliseconds)
		{
			return hour * (60 * 60 * 1000)
				+ minute * (60 * 1000)
				+ second * (1000)
				+ milliseconds;
		}

		static const String MonthEnglish[12]
		{
			S3DSTR("January"),
			S3DSTR("February"),
			S3DSTR("March"),
			S3DSTR("April"),
			S3DSTR("May"),
			S3DSTR("June"),
			S3DSTR("July"),
			S3DSTR("August"),
			S3DSTR("September"),
			S3DSTR("October"),
			S3DSTR("November"),
			S3DSTR("December"),
		};

		static const String AMPM[2]
		{
			S3DSTR("AM"),
			S3DSTR("PM"),
		};

		static const String FormatPatterns[22]
		{
			S3DSTR("yyyy"),
			S3DSTR("yy"),
			S3DSTR("y"),
			S3DSTR("MMMM"),
			S3DSTR("MMM"),
			S3DSTR("MM"),
			S3DSTR("M"),
			S3DSTR("dd"),
			S3DSTR("d"),
			S3DSTR("EEEE"),
			S3DSTR("EEE"),
			S3DSTR("E"),
			S3DSTR("a"),
			S3DSTR("HH"),
			S3DSTR("H"),
			S3DSTR("hh"),
			S3DSTR("h"),
			S3DSTR("mm"),
			S3DSTR("ss"),
			S3DSTR("S"),
			S3DSTR("SS"),
			S3DSTR("SSS")
		};
	}

	static String GetFormattedElement(const DateTime& date, const String& format, const bool isCalendar)
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
			return Pad(date.year, { 4, L'0' });
		case 1:	// yy	2 桁の年 (00-99)
			return Pad(date.year % 100, { 2, L'0' });
		case 2:	// y	年 (1-)
			return ToString(date.year);
		case 3:	// MMMM	英語の月 (January-December)
			return detail::MonthEnglish[date.month - 1];
		case 4:	// MMM	英語の月の略称 (Jan-Dec)
			return detail::MonthEnglish[date.month - 1].substr(0, 3);
		case 5:	// MM	2 桁の月 (01-12)
			return Pad(date.month, { 2, L'0' });
		case 6:	// M	1-2 桁の月 (1-12)
			return ToString(date.month);
		case 7:	// dd	2 桁の日 (01-31)
			return Pad(date.day, { 2, L'0' });
		case 8:	// d	1-2 桁の日 (1-31)
			return ToString(date.day);
		case 9:	// EEEE 英語の曜日 (Sunday-Satueday)
			return date.dayOfWeekEN();
		case 10: // EEE	英語の曜日の略称 (Sun-Sat)
			return date.dayOfWeekEN().substr(0, 3);
		case 11: // E	日本語の曜日 (日-土)
			return date.dayOfWeekJP();
		case 12: // a	午前/午後 (AM/PM)
			return detail::AMPM[date.hour > 11];
		case 13: // HH	24 時間表記の 2 桁の時 (00-23)
			return Pad(date.hour, { 2, L'0' });
		case 14: // H	24 時間表記の時 (0-23)
			return ToString(date.hour);
		case 15: // hh	12 時間表記の 2 桁の時 (00-11)
			return Pad(date.hour % 12, { 2, L'0' });
		case 16: // h	12 時間表記の時 (0-11)
			return ToString(date.hour % 12);
		case 17: // mm	2 桁の分 (00-59)
			return Pad(date.minute, { 2, L'0' });
		case 18: // ss	2 桁の秒 (00-59)
			return Pad(date.second, { 2, L'0' });
		case 19: // S	小数点以下 1 桁の秒 (0-9)
			return ToString(date.milliseconds / 100);
		case 20: // SS	小数点以下 2 桁の秒 (00-99)
			return Pad(date.milliseconds / 10, { 2, L'0' });
		case 21: // SSS	小数点以下 3 桁の秒 (000-999)
			return Pad(date.milliseconds, { 3, L'0' });
		default:
			return String();
		}
	}

	static String FormatDateTime(const DateTime& date, const String& format, const bool isCalendar)
	{
		String formattedDateTime, keyPattern;

		bool inQuot = false;

		wchar previousChar = L'\0';

		for (size_t i = 0; i < format.length(); ++i)
		{
			const wchar ch = format[i];

			if (IsAlpha(ch))
			{
				if (inQuot)
				{
					formattedDateTime += ch;
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

				if (ch == L'\'')
				{
					if (format[i + 1] == L'\'')
					{
						formattedDateTime += L'\'';

						++i;

						continue;
					}

					inQuot = !inQuot;
				}
				else
				{
					formattedDateTime += ch;
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

	String Date::format(const String& format) const
	{
		return FormatDateTime(*this, format, true);
	}

	String DateTime::format(const String& format) const
	{
		return FormatDateTime(*this, format, false);
	}

	DateTime DateTime::Now()
	{
		# if defined(SIV3D_TARGET_WINDOWS)

			SYSTEMTIME sysTime;
			::GetLocalTime(&sysTime);
			return detail::ToDateTime(sysTime);

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

            ::timeval tv;
            ::tm lt;
            ::gettimeofday(&tv, nullptr);
            ::localtime_r(&tv.tv_sec, &lt);
            return DateTime((1900 + lt.tm_year), (1 + lt.tm_mon), (lt.tm_mday),
                lt.tm_hour, lt.tm_min, lt.tm_sec, tv.tv_usec / 1000);

		# endif
	}

	DateTime DateTime::NowUTC()
	{
		# if defined(SIV3D_TARGET_WINDOWS)

			SYSTEMTIME sysTime;
			::GetSystemTime(&sysTime);
			return detail::ToDateTime(sysTime);

		# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

            ::timeval tv;
            ::tm gt;
            ::gettimeofday(&tv, nullptr);
            ::gmtime_r(&tv.tv_sec, &gt);
            return DateTime((1900 + gt.tm_year), (1 + gt.tm_mon), (gt.tm_mday),
                gt.tm_hour, gt.tm_min, gt.tm_sec, tv.tv_usec / 1000);

		# endif
	}

	DateTime& DateTime::operator +=(const Milliseconds& _milliseconds)
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

	Milliseconds operator -(const DateTime& a, const DateTime& b)
	{
		const auto diffDays = Date(a) - Date(b);
		const auto aMillisec = detail::TimeToMillisecCount(a.hour, a.minute, a.second, a.milliseconds);
		const auto bMillisec = detail::TimeToMillisecCount(b.hour, b.minute, b.second, b.milliseconds);

		return Milliseconds(diffDays.count() * (86400 * 1000) + (aMillisec - bMillisec));
	}
}

