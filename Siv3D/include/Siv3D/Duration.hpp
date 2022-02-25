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
# include <chrono>
# include "Common.hpp"
# include "Fwd.hpp"
# include "StringView.hpp"

namespace s3d
{
	/// @brief 日数 | Days
	using Days			= std::chrono::duration<int32, std::ratio<86400>>;

	/// @brief 日数 | Days
	using DaysF			= std::chrono::duration<double, std::ratio<86400>>;

	/// @brief 時間 | Hours
	using Hours			= std::chrono::hours;

	/// @brief 時間 | Hours
	using HoursF		= std::chrono::duration<double, std::ratio<3600>>;

	/// @brief 分 | Minutes
	using Minutes		= std::chrono::minutes;

	/// @brief 分 | Minutes
	using MinutesF		= std::chrono::duration<double, std::ratio<60>>;

	/// @brief 秒 | Seconds
	using Seconds		= std::chrono::seconds;

	/// @brief 秒 | Seconds
	using SecondsF		= std::chrono::duration<double>;

	/// @brief ミリ秒 | Milliseconds
	using Milliseconds	= std::chrono::milliseconds;

	/// @brief ミリ秒 | Milliseconds
	using MillisecondsF	= std::chrono::duration<double, std::milli>;

	/// @brief マイクロ秒 | Microseconds
	using Microseconds	= std::chrono::microseconds;

	/// @brief マイクロ秒 | Microseconds
	using MicrosecondsF	= std::chrono::duration<double, std::micro>;

	/// @brief ナノ秒 | Nanoseconds
	using Nanoseconds	= std::chrono::nanoseconds;

	/// @brief ナノ秒 | Nanoseconds
	using NanosecondsF	= std::chrono::duration<double, std::nano>;

	/// @brief 秒 | Seconds
	using Duration		= SecondsF;

	/// @brief 時間の単位を変換します。
	/// @tparam DurationTo 変換前の時間の型
	/// @tparam DurationFrom 変換後の時間の型
	/// @param duration 変換前の時間
	/// @return 変換後の時間
	template <class DurationTo, class DurationFrom>
	[[nodiscard]]
	inline constexpr DurationTo DurationCast(const DurationFrom& duration) noexcept;

	inline namespace Literals
	{
		inline namespace DurationLiterals
		{
			/// @brief Days 型の値を得るユーザ定義リテラル
			/// @param days 日数
			/// @return 日数
			[[nodiscard]]
			inline constexpr Days operator ""_d(unsigned long long days);

			/// @brief DaysF 型の値を得るユーザ定義リテラル
			/// @param days 日数
			/// @return 日数
			[[nodiscard]]
			inline constexpr DaysF operator ""_d(long double days);
		}
	}

	/// @brief 時間を文字列に変換します。
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
	/// @param duration 時間
	/// @param format フォーマット指定
	/// @return フォーマットされた時間
	[[nodiscard]]
	String FormatTime(const Duration& duration, StringView format = U"HH:mm:ss.xxx"_sv);

	/// @brief 日数をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param days 日数
	void Formatter(FormatData& formatData, const Days& days);

	/// @brief 日数をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param days 日数
	void Formatter(FormatData& formatData, const DaysF& days);

	/// @brief 時間をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param hours 時間
	void Formatter(FormatData& formatData, const Hours& hours);

	/// @brief 時間をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param hours 時間
	void Formatter(FormatData& formatData, const HoursF& hours);

	/// @brief 分をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param minutes 分
	void Formatter(FormatData& formatData, const Minutes& minutes);

	/// @brief 分をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param minutes 分
	void Formatter(FormatData& formatData, const MinutesF& minutes);

	/// @brief 秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param seconds 秒
	void Formatter(FormatData& formatData, const Seconds& seconds);

	/// @brief 秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param seconds 秒
	void Formatter(FormatData& formatData, const SecondsF& seconds);

	/// @brief ミリ秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param milliseconds ミリ秒
	void Formatter(FormatData& formatData, const Milliseconds& milliseconds);

	/// @brief ミリ秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param milliseconds ミリ秒
	void Formatter(FormatData& formatData, const MillisecondsF& milliseconds);

	/// @brief マイクロ秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param microseconds マイクロ秒
	void Formatter(FormatData& formatData, const Microseconds& microseconds);

	/// @brief マイクロ秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param microseconds マイクロ秒
	void Formatter(FormatData& formatData, const MicrosecondsF& microseconds);

	/// @brief ナノ秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param nanoseconds ナノ秒
	void Formatter(FormatData& formatData, const Nanoseconds& nanoseconds);

	/// @brief ナノ秒をフォーマットします。
	/// @param formatData フォーマットデータ
	/// @param nanoseconds ナノ秒
	void Formatter(FormatData& formatData, const NanosecondsF& nanoseconds);
}

# include "detail/Duration.ipp"
