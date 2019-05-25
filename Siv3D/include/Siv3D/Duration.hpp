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

# pragma once
# include <iostream>
# include <chrono>
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// 日数 (int32)
	/// Days (int32)
	/// </summary>
	using Days = std::chrono::duration<int32, std::ratio<86400>>;

	/// <summary>
	/// 日数 (double)
	/// Days (double)
	/// </summary>
	using DaysF = std::chrono::duration<double, std::ratio<86400>>;


	/// <summary>
	/// 時間 (int32)
	/// Hours (int32)
	/// </summary>
	using Hours = std::chrono::hours;

	/// <summary>
	/// 時間 (double)
	/// Hours (double)
	/// </summary>
	using HoursF = std::chrono::duration<double, std::ratio<3600>>;


	/// <summary>
	/// 分 (int32)
	/// Minutes (int32)
	/// </summary>
	using Minutes = std::chrono::minutes;

	/// <summary>
	/// 分 (double)
	/// Minutes (double)
	/// </summary>
	using MinutesF = std::chrono::duration<double, std::ratio<60>>;


	/// <summary>
	/// 秒 (int64)
	/// Seconds (int64)
	/// </summary>
	using Seconds = std::chrono::seconds;

	/// <summary>
	/// 秒 (double)
	/// Seconds (double)
	/// </summary>
	using SecondsF = std::chrono::duration<double>;


	/// <summary>
	/// ミリ秒 (int64)
	/// Milliseconds (int64)
	/// </summary>
	using Milliseconds = std::chrono::milliseconds;

	/// <summary>
	/// ミリ秒 (double)
	/// Milliseconds (double)
	/// </summary>
	using MillisecondsF = std::chrono::duration<double, std::milli>;


	/// <summary>
	/// マイクロ秒 (int64)
	/// Microseconds (int64)
	/// </summary>
	using Microseconds = std::chrono::microseconds;

	/// <summary>
	/// マイクロ秒 (double)
	/// Microseconds (double)
	/// </summary>
	using MicrosecondsF = std::chrono::duration<double, std::micro>;


	/// <summary>
	/// ナノ秒 (int64)
	/// Nanoseconds (int64)
	/// </summary>
	using Nanoseconds = std::chrono::nanoseconds;

	/// <summary>
	/// ナノ秒 (double)
	/// Nanoseconds (double)
	/// </summary>
	using NanosecondsF = std::chrono::duration<double, std::nano>;

	using Duration = SecondsF;

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
	[[nodiscard]] inline constexpr DurationTo DurationCast(const DurationFrom& duration)
	{
		return std::chrono::duration_cast<DurationTo>(duration);
	}

	inline namespace Literals
	{
		inline namespace DurationLiterals
		{
			[[nodiscard]] inline constexpr Days operator ""_d(unsigned long long days)
			{
				return Days(days);
			}

			[[nodiscard]] inline constexpr DaysF operator ""_d(long double days)
			{
				return DaysF(days);
			}
		}
	}

	/// <summary>
	/// DD		日 (00-)
	/// D		日 (0-)
	/// dd		日 (00-)
	/// d		日 (0-)
	/// HH		時 (00-)
	/// H		時 (0-)
	/// hh		時 (00-24)
	/// h		時 (0-24)
	/// MM		分 (00-)
	/// M		分 (0-)
	/// mm		分 (00-59)
	/// m		分 (0-59)
	/// SS		秒 (00-)
	/// S		秒 (0-)
	/// ss		秒 (00-59)
	/// s		秒 (0-59)
	/// X		ミリ秒 (0-)
	/// x		小数点以下 1 桁秒 (0-9)
	/// xx		小数点以下 2 桁秒 (00-99)
	/// xxx		小数点以下 3 桁秒 (000-999)
	/// </summary>
	/// <param name="duration">
	/// 時間
	/// </param>
	/// <param name="format">
	/// フォーマット指定
	/// </param>
	/// <returns>
	/// フォーマットされた時間
	/// </returns>
	[[nodiscard]] String FormatTime(const Duration& duration, StringView format);
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Days& days);

	void Formatter(FormatData& formatData, const DaysF& days);

	void Formatter(FormatData& formatData, const Hours& hours);

	void Formatter(FormatData& formatData, const HoursF& hours);

	void Formatter(FormatData& formatData, const Minutes& minutes);

	void Formatter(FormatData& formatData, const MinutesF& minutes);

	void Formatter(FormatData& formatData, const Seconds& seconds);

	void Formatter(FormatData& formatData, const SecondsF& seconds);

	void Formatter(FormatData& formatData, const Milliseconds& milliseconds);

	void Formatter(FormatData& formatData, const MillisecondsF& milliseconds);

	void Formatter(FormatData& formatData, const Microseconds& microseconds);

	void Formatter(FormatData& formatData, const MicrosecondsF& microseconds);

	void Formatter(FormatData& formatData, const Nanoseconds& nanoseconds);

	void Formatter(FormatData& formatData, const NanosecondsF& nanoseconds);
}
