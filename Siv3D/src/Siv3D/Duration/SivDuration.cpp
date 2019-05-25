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

# include <Siv3D/Duration.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/Char.hpp>

namespace s3d
{
	static constexpr StringView FormatPatterns[]
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
			std::begin(FormatPatterns),
			std::find(std::begin(FormatPatterns), std::end(FormatPatterns), format)
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
						result.append(GetFormattedElement(us, keyPattern));
						keyPattern.clear();
						keyPattern.push_back(ch);
					}
				}
			}
			else
			{
				if (!keyPattern.isEmpty())
				{
					result.append(GetFormattedElement(us, keyPattern));
					keyPattern.clear();
				}

				if (ch == U'\'')
				{
					if (format[i + 1] == U'\'')
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

		if (!keyPattern.isEmpty())
		{
			result.append(GetFormattedElement(us, keyPattern));
		}

		return result;
	}

	void Formatter(FormatData& formatData, const Days& days)
	{
		Formatter(formatData, days.count());

		formatData.string.push_back(U'd');
	}

	void Formatter(FormatData& formatData, const DaysF& days)
	{
		Formatter(formatData, days.count());

		formatData.string.push_back(U'd');
	}

	void Formatter(FormatData& formatData, const Hours& hours)
	{
		Formatter(formatData, hours.count());

		formatData.string.push_back(U'h');
	}

	void Formatter(FormatData& formatData, const HoursF& hours)
	{
		Formatter(formatData, hours.count());

		formatData.string.push_back(U'h');
	}

	void Formatter(FormatData& formatData, const Minutes& minutes)
	{
		Formatter(formatData, minutes.count());

		formatData.string.append(U"min"_sv);
	}

	void Formatter(FormatData& formatData, const MinutesF& minutes)
	{
		Formatter(formatData, minutes.count());

		formatData.string.append(U"min"_sv);
	}

	void Formatter(FormatData& formatData, const Seconds& seconds)
	{
		Formatter(formatData, seconds.count());

		formatData.string.push_back(U's');
	}

	void Formatter(FormatData& formatData, const SecondsF& seconds)
	{
		Formatter(formatData, seconds.count());

		formatData.string.push_back(U's');
	}

	void Formatter(FormatData& formatData, const Milliseconds& milliseconds)
	{
		Formatter(formatData, milliseconds.count());

		formatData.string.append(U"ms"_sv);
	}

	void Formatter(FormatData& formatData, const MillisecondsF& milliseconds)
	{
		Formatter(formatData, milliseconds.count());

		formatData.string.append(U"ms"_sv);
	}

	void Formatter(FormatData& formatData, const Microseconds& microseconds)
	{
		Formatter(formatData, microseconds.count());

		formatData.string.append(U"us"_sv);
	}

	void Formatter(FormatData& formatData, const MicrosecondsF& microseconds)
	{
		Formatter(formatData, microseconds.count());

		formatData.string.append(U"us"_sv);
	}

	void Formatter(FormatData& formatData, const Nanoseconds& nanoseconds)
	{
		Formatter(formatData, nanoseconds.count());

		formatData.string.append(U"ns"_sv);
	}

	void Formatter(FormatData& formatData, const NanosecondsF& nanoseconds)
	{
		Formatter(formatData, nanoseconds.count());

		formatData.string.append(U"ns"_sv);
	}
}
