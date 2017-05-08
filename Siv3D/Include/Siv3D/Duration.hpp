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

# pragma once
# include <iostream>
# include <chrono>
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// 日数
	/// </summary>
	using Days = std::chrono::duration<int32, std::ratio<86400>>;

	/// <summary>
	/// 日数
	/// </summary>
	using DaysF = std::chrono::duration<long double, std::ratio<86400>>;


	/// <summary>
	/// 時間
	/// </summary>
	using Hours = std::chrono::hours;

	/// <summary>
	/// 時間
	/// </summary>
	using HoursF = std::chrono::duration<long double, std::ratio<3600>>;


	/// <summary>
	/// 分
	/// </summary>
	using Minutes = std::chrono::minutes;

	/// <summary>
	/// 分
	/// </summary>
	using MinutesF = std::chrono::duration<long double, std::ratio<60>>;


	/// <summary>
	/// 秒
	/// </summary>
	using Seconds = std::chrono::seconds;

	/// <summary>
	/// 秒
	/// </summary>
	using SecondsF = std::chrono::duration<long double>;


	/// <summary>
	/// ミリ秒
	/// </summary>
	using Milliseconds = std::chrono::milliseconds;

	/// <summary>
	/// ミリ秒
	/// </summary>
	using MillisecondsF = std::chrono::duration<long double, std::milli>;


	/// <summary>
	/// マイクロ秒
	/// </summary>
	using Microseconds = std::chrono::microseconds;

	/// <summary>
	/// マイクロ秒
	/// </summary>
	using MicrosecondsF = std::chrono::duration<long double, std::micro>;


	/// <summary>
	/// ナノ秒
	/// </summary>
	using Nanoseconds = std::chrono::nanoseconds;

	/// <summary>
	/// ナノ秒
	/// </summary>
	using NanosecondsF = std::chrono::duration<long double, std::nano>;

	/// <summary>
	/// 時間の単位を変換します。
	/// </summary>
	/// <param name="duration">
	/// 変換する時間
	/// </param>
	/// <returns>
	/// DurationTo 型に変換された時間
	/// </returns>
	template <class DurationTo, class DurationFrom>
	inline constexpr DurationTo DurationCast(const DurationFrom& duration)
	{
		return std::chrono::duration_cast<DurationTo>(duration);
	}

	inline namespace literals
	{
		inline namespace chrono_literals
		{
			inline constexpr Days operator ""_d(unsigned long long days)
			{
				return Days(days);
			}

			inline constexpr DaysF operator ""_d(long double days)
			{
				return DaysF(days);
			}
		}
	}

	inline void Formatter(FormatData& formatData, const Days& days)
	{
		Formatter(formatData, days.count());

		formatData.string.push_back(S3DCHAR('d'));
	}

	inline void Formatter(FormatData& formatData, const DaysF& days)
	{
		Formatter(formatData, days.count());

		formatData.string.push_back(S3DCHAR('d'));
	}

	inline void Formatter(FormatData& formatData, const Hours& hours)
	{
		Formatter(formatData, hours.count());

		formatData.string.push_back(S3DCHAR('h'));
	}

	inline void Formatter(FormatData& formatData, const HoursF& hours)
	{
		Formatter(formatData, hours.count());

		formatData.string.push_back(S3DCHAR('h'));
	}

	inline void Formatter(FormatData& formatData, const Minutes& minutes)
	{
		Formatter(formatData, minutes.count());

		formatData.string.append(S3DSTR("min"), 3);
	}

	inline void Formatter(FormatData& formatData, const MinutesF& minutes)
	{
		Formatter(formatData, minutes.count());

		formatData.string.append(S3DSTR("min"), 3);
	}

	inline void Formatter(FormatData& formatData, const Seconds& seconds)
	{
		Formatter(formatData, seconds.count());

		formatData.string.push_back(S3DCHAR('s'));
	}

	inline void Formatter(FormatData& formatData, const SecondsF& seconds)
	{
		Formatter(formatData, seconds.count());

		formatData.string.push_back(S3DCHAR('s'));
	}

	inline void Formatter(FormatData& formatData, const Milliseconds& milliseconds)
	{
		Formatter(formatData, milliseconds.count());

		formatData.string.append(S3DSTR("ms"), 2);
	}

	inline void Formatter(FormatData& formatData, const MillisecondsF& milliseconds)
	{
		Formatter(formatData, milliseconds.count());

		formatData.string.append(S3DSTR("ms"), 2);
	}

	inline void Formatter(FormatData& formatData, const Microseconds& microseconds)
	{
		Formatter(formatData, microseconds.count());

		formatData.string.append(S3DSTR("us"), 2);
	}

	inline void Formatter(FormatData& formatData, const MicrosecondsF& microseconds)
	{
		Formatter(formatData, microseconds.count());

		formatData.string.append(S3DSTR("us"), 2);
	}

	inline void Formatter(FormatData& formatData, const Nanoseconds& nanoseconds)
	{
		Formatter(formatData, nanoseconds.count());

		formatData.string.append(S3DSTR("ns"), 2);
	}

	inline void Formatter(FormatData& formatData, const NanosecondsF& nanoseconds)
	{
		Formatter(formatData, nanoseconds.count());

		formatData.string.append(S3DSTR("ns"), 2);
	}
}
