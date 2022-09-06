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

# include <Siv3D/String.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/Duration.hpp>
# include <Siv3D/Date.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FormatUtility.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr StringView DurationFormatPatterns[]
		{
			U"DD"_sv,
			U"D"_sv,
			U"dd"_sv,
			U"d"_sv,
			U"HH"_sv,
			U"H"_sv,
			U"hh"_sv,
			U"h"_sv,
			U"MM"_sv,
			U"M"_sv,
			U"mm"_sv,
			U"m"_sv,
			U"SS"_sv,
			U"S"_sv,
			U"ss"_sv,
			U"s"_sv,
			U"X"_sv,
			U"x"_sv,
			U"xx"_sv,
			U"xxx"_sv,
		};

		static String GetFormattedElement(const int64 us, const StringView format)
		{
			const size_t formatIndex = std::distance(
				std::begin(DurationFormatPatterns),
				std::find(std::begin(DurationFormatPatterns), std::end(DurationFormatPatterns), format)
			);

			switch (formatIndex)
			{
			case 0:	// DD		日 (00-)
			case 2:	// dd		日 (00-)
				return Pad(us / (1000LL * 1000LL * 60LL * 60LL * 24LL), { 2, U'0' });
			case 1:	// D		日 (0-)
			case 3:	// d		日 (0-)
				return ToString(us / (1000LL * 1000LL * 60LL * 60LL * 24LL));
			case 4:	// HH		時 (00-)
				return Pad(us / (1000LL * 1000LL * 60LL * 60LL), { 2, U'0' });
			case 5:	// H		時 (0-)
				return ToString(us / (1000LL * 1000LL * 60LL * 60LL));
			case 6:	// hh		時 (00-24)
				return Pad(us / (1000LL * 1000LL * 60LL * 60LL) % 24, { 2, U'0' });
			case 7:	// h		時 (0-24)
				return ToString(us / (1000LL * 1000LL * 60LL * 60LL) % 24);
			case 8:	// MM		分 (00-)
				return Pad(us / (1000LL * 1000LL * 60LL), { 2, U'0' });
			case 9:	// M		分 (0-)
				return ToString(us / (1000LL * 1000LL * 60LL));
			case 10: // mm		分 (00-59)
				return Pad(us / (1000LL * 1000LL * 60LL) % 60, { 2, U'0' });
			case 11: // m		分 (0-59)
				return ToString(us / (1000LL * 1000LL * 60LL) % 60);
			case 12: // SS		秒 (00-)
				return Pad(us / (1000LL * 1000LL), { 2, U'0' });
			case 13: // S		秒 (0-)
				return ToString(us / (1000LL * 1000LL));
			case 14: // ss		秒 (00-59)
				return Pad(us / (1000LL * 1000LL) % 60, { 2, U'0' });
			case 15: // s		秒 (0-59)
				return ToString(us / (1000LL * 1000LL) % 60);
			case 16: // X		ミリ秒 (0-)
				return ToString(us / (1000LL));
			case 17: // x		小数点以下 1 桁秒 (0-9)
				return ToString(us / (1000LL * 100L) % 10);
			case 18: // xx		小数点以下 2 桁秒 (00-99)
				return Pad(us / (1000LL * 10LL) % 100, { 2, U'0' });
			case 19: // xxx		小数点以下 3 桁秒 (000-999)
				return Pad(us / (1000LL) % 1000, { 3, U'0' });
			default:
				return String();
			}
		}

		template <class DurationType>
		inline void FormatDuration(FormatData& formatData, const DurationType& d, char32 unit)
		{
			Formatter(formatData, d.count());

			formatData.string.push_back(unit);
		}

		template <class DurationType>
		inline void FormatDuration(FormatData& formatData, const DurationType& d, StringView unit)
		{
			Formatter(formatData, d.count());

			formatData.string.append(unit);
		}
	}

	String FormatTime(const Duration& duration, const StringView format)
	{
		int64 us = DurationCast<Microseconds>(duration).count();

		String result, keyPattern;

		if (us < 0)
		{
			result.push_back(U'-');

			us = -us;
		}

		bool inQuot = false;

		char32 previousChar = U'\0';

		for (size_t i = 0; i < format.length(); ++i)
		{
			const char32 ch = format[i];

			if (IsAlpha(ch))
			{
				if (inQuot)
				{
					result.push_back(ch);
				}
				else
				{
					if (keyPattern.isEmpty() || ch == previousChar)
					{
						keyPattern.push_back(ch);
					}
					else
					{
						result.append(detail::GetFormattedElement(us, keyPattern));
						keyPattern.clear();
						keyPattern.push_back(ch);
					}
				}
			}
			else
			{
				if (keyPattern)
				{
					result.append(detail::GetFormattedElement(us, keyPattern));
					keyPattern.clear();
				}

				if (ch == U'\'')
				{
					if (((i + 1) < format.length()) &&
						(format[i + 1] == U'\''))
					{
						result.push_back(U'\'');

						++i;

						continue;
					}

					inQuot = !inQuot;
				}
				else
				{
					result.push_back(ch);
				}
			}

			previousChar = ch;
		}

		if (keyPattern)
		{
			result.append(detail::GetFormattedElement(us, keyPattern));
		}

		return result;
	}

	void Formatter(FormatData& formatData, const Days& days)
	{
		detail::FormatDuration(formatData, days, U'd');
	}

	void Formatter(FormatData& formatData, const DaysF& days)
	{
		detail::FormatDuration(formatData, days, U'd');
	}

	void Formatter(FormatData& formatData, const Hours& hours)
	{
		detail::FormatDuration(formatData, hours, U'h');
	}

	void Formatter(FormatData& formatData, const HoursF& hours)
	{
		detail::FormatDuration(formatData, hours, U'h');
	}

	void Formatter(FormatData& formatData, const Minutes& minutes)
	{
		detail::FormatDuration(formatData, minutes, U"min");
	}

	void Formatter(FormatData& formatData, const MinutesF& minutes)
	{
		detail::FormatDuration(formatData, minutes, U"min");
	}

	void Formatter(FormatData& formatData, const Seconds& seconds)
	{
		detail::FormatDuration(formatData, seconds, U's');
	}

	void Formatter(FormatData& formatData, const SecondsF& seconds)
	{
		detail::FormatDuration(formatData, seconds, U's');
	}

	void Formatter(FormatData& formatData, const Milliseconds& milliseconds)
	{
		detail::FormatDuration(formatData, milliseconds, U"ms");
	}

	void Formatter(FormatData& formatData, const MillisecondsF& milliseconds)
	{
		detail::FormatDuration(formatData, milliseconds, U"ms");
	}

	void Formatter(FormatData& formatData, const Microseconds& microseconds)
	{
		detail::FormatDuration(formatData, microseconds, U"us");
	}

	void Formatter(FormatData& formatData, const MicrosecondsF& microseconds)
	{
		detail::FormatDuration(formatData, microseconds, U"us");
	}

	void Formatter(FormatData& formatData, const Nanoseconds& nanoseconds)
	{
		detail::FormatDuration(formatData, nanoseconds, U"ns");
	}

	void Formatter(FormatData& formatData, const NanosecondsF& nanoseconds)
	{
		detail::FormatDuration(formatData, nanoseconds, U"ns");
	}
}
