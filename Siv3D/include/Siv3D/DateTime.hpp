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
# include "Common.hpp"
# include "Date.hpp"

namespace s3d
{
	/// @brief 日付と時刻 | Date and time
	struct DateTime : Date
	{
		/// @brief 時 [0-23]
		int32 hour;

		/// @brief 分 [0-59]
		int32 minute;

		/// @brief 秒 [0-59]
		int32 second;

		/// @brief ミリ秒 [0-999]
		int32 milliseconds;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		DateTime() noexcept = default;

		/// @brief 日付と時刻を作成します。
		/// @param _year 年
		/// @param _month 月 [1-12]
		/// @param _day 日 [1-31]
		/// @param _hour 時 [0-23]、デフォルトでは 0
		/// @param _minute 分 [0-59]、デフォルトでは 0
		/// @param _second 秒 [0-59]、デフォルトでは 0
		/// @param _milliseconds ミリ秒 [0-999]、デフォルトでは 0
		/// @remark 指定された時刻や日付が存在するかはチェックされません。
		SIV3D_NODISCARD_CXX20
		constexpr DateTime(
			int32 _year,
			int32 _month,
			int32 _day,
			int32 _hour = 0,
			int32 _minute = 0,
			int32 _second = 0,
			int32 _milliseconds = 0) noexcept;

		/// @brief 日付と時刻を作成します。
		/// @param date 日付
		/// @param _hour 時 [0-23]、デフォルトでは 0
		/// @param _minute 分 [0-59]、デフォルトでは 0
		/// @param _second 秒 [0-59]、デフォルトでは 0
		/// @param _milliseconds ミリ秒 [0-999]、デフォルトでは 0
		/// @remark 指定された時刻や日付が存在するかはチェックされません。
		SIV3D_NODISCARD_CXX20
		constexpr DateTime(
			const Date& date,
			int32 _hour = 0,
			int32 _minute = 0,
			int32 _second = 0,
			int32 _milliseconds = 0) noexcept;

		/// @brief 日付と時刻の妥当性を返します。
		/// @return 日付と時刻が正しい範囲の値であれば true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isValid() const noexcept;

		/// @brief 日付と時刻を指定したフォーマットの文字列で返します。
		/// yyyy	4 桁の年 (0001-)
		/// yy		2 桁の年 (00-99)
		/// y		年 (1-)
		/// MMMM	英語の月 (January-December)
		/// MMM		英語の月の略称 (Jan-Dec)
		/// MM		2 桁の月 (01-12)
		/// M		1-2 桁の月 (1-12)
		/// dd		2 桁の日 (01-31)
		/// d		1-2 桁の日 (1-31)
		/// EEEE	英語の曜日 (Sunday-Saturday)
		/// EEE		英語の曜日の略称 (Sun-Sat)
		/// a		午前/午後 (AM/PM)
		/// HH		24 時間表記の 2 桁の時 (00-23)
		/// H		24 時間表記の時 (0-23)
		/// hh		12 時間表記の 2 桁の時 (00-11)
		/// h		12 時間表記の時 (0-11)
		/// mm		2 桁の分 (00-59)
		/// ss		2 桁の秒 (00-59)
		/// S		小数点以下 1 桁の秒 (0-9)
		/// SS		小数点以下 2 桁の秒 (00-99)
		/// SSS		小数点以下 3 桁の秒 (000-999)
		/// @param format フォーマット指定
		/// @return フォーマットされた日付と時刻
		[[nodiscard]]
		String format(StringView format = U"yyyy-MM-dd HH:mm:ss"_sv) const;

		[[nodiscard]]
		DateTime operator +(const Days& days) const noexcept;

		[[nodiscard]]
		DateTime operator +(const Milliseconds& _milliseconds) const noexcept;

		[[nodiscard]]
		DateTime operator -(const Days& days) const noexcept;

		[[nodiscard]]
		DateTime operator -(const Milliseconds& _milliseconds) const noexcept;

		DateTime& operator +=(const Days& days) noexcept;

		DateTime& operator +=(const Milliseconds& _milliseconds) noexcept;

		DateTime& operator -=(const Days& days) noexcept;

		DateTime& operator -=(const Milliseconds & _milliseconds) noexcept;

		[[nodiscard]]
		friend constexpr Duration operator -(const DateTime& to, const DateTime& from) noexcept
		{
			return Subtract(to, from);
		}

	# if __cpp_impl_three_way_comparison

		friend constexpr auto operator <=>(const DateTime&, const DateTime&) = default;

	# else

		[[nodiscard]]
		friend bool operator ==(const DateTime & lhs, const DateTime & rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(DateTime)) == 0;
		}

		[[nodiscard]]
		friend bool operator !=(const DateTime & lhs, const DateTime & rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(DateTime)) != 0;
		}

		[[nodiscard]]
		friend bool operator <(const DateTime & lhs, const DateTime & rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(DateTime)) < 0;
		}

		[[nodiscard]]
		friend bool operator >(const DateTime & lhs, const DateTime & rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(DateTime)) > 0;
		}

		[[nodiscard]]
		friend bool operator <=(const DateTime & lhs, const DateTime & rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(DateTime)) <= 0;
		}

		[[nodiscard]]
		friend bool operator >=(const DateTime& lhs, const DateTime& rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(DateTime)) >= 0;
		}

	# endif

		/// @brief 日付と時刻のハッシュ値を返します
		/// @return 日付と時刻のハッシュ値
		[[nodiscard]]
		size_t hash() const noexcept;

		/// @brief 昨日の日付と時刻（ローカルタイム）を返します。
		/// @remark 時刻は午前 0 時 0 分にセットされます
		/// @return 昨日の午前 0 時 0 分の日付と時刻（ローカルタイム）
		[[nodiscard]]
		static DateTime Yesterday() noexcept;

		/// @brief 今日の日付と時刻（ローカルタイム）を返します。
		/// @remark 時刻は午前 0 時 0 分にセットされます
		/// @return 今日の午前 0 時 0 分の日付と時刻（ローカルタイム）
		[[nodiscard]]
		static DateTime Today() noexcept;

		/// @brief 明日の日付と時刻（ローカルタイム）を返します。
		/// @remark 時刻は午前 0 時 0 分にセットされます
		/// @return 明日の午前 0 時 0 分の日付と時刻（ローカルタイム）
		[[nodiscard]]
		static DateTime Tomorrow() noexcept;

		/// @brief 現在の日付と時刻（ローカルタイム）を返します。
		/// @return 現在の日付と時刻（ローカルタイム）
		[[nodiscard]]
		static DateTime Now() noexcept;
		
		/// @brief 現在の日付と時刻（協定世界時刻（UTC））を返します。
		/// @return 現在の日付と時刻（協定世界時刻（UTC））
		[[nodiscard]]
		static DateTime NowUTC() noexcept;

		/// @brief 
		/// @param a 
		/// @param b 
		/// @return 
		[[nodiscard]]
		static constexpr Duration Subtract(const DateTime& a, const DateTime& b) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const DateTime& value)
		{
			return output << value.format();
		}

		friend void Formatter(FormatData& formatData, const DateTime& value)
		{
			formatData.string.append(value.format());
		}
	};

	/// @brief 日付と時刻を文字列に変換します。
	/// yyyy	4 桁の年 (0001-)
	/// yy		2 桁の年 (00-99)
	/// y		年 (1-)
	/// MMMM	英語の月 (January-December)
	/// MMM		英語の月の略称 (Jan-Dec)
	/// MM		2 桁の月 (01-12)
	/// M		1-2 桁の月 (1-12)
	/// dd		2 桁の日 (01-31)
	/// d		1-2 桁の日 (1-31)
	/// EEEE	英語の曜日 (Sunday-Saturday)
	/// EEE		英語の曜日の略称 (Sun-Sat)
	/// a		午前/午後 (AM/PM)
	/// HH		24 時間表記の 2 桁の時 (00-23)
	/// H		24 時間表記の時 (0-23)
	/// hh		12 時間表記の 2 桁の時 (00-11)
	/// h		12 時間表記の時 (0-11)
	/// mm		2 桁の分 (00-59)
	/// ss		2 桁の秒 (00-59)
	/// S		小数点以下 1 桁の秒 (0-9)
	/// SS		小数点以下 2 桁の秒 (00-99)
	/// SSS		小数点以下 3 桁の秒 (000-999)
	/// @param dateTime 日付と時刻
	/// @param format フォーマット指定
	/// @return フォーマットされた日付と時刻
	[[nodiscard]]
	String FormatDateTime(const DateTime& dateTime, StringView format = U"yyyy-MM-dd HH:mm:ss"_sv);
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::DateTime, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::DateTime& value, FormatContext& ctx)
	{
		const s3d::String dateTime = value.format();
		const basic_string_view<s3d::char32> sv(dateTime.data(), dateTime.size());

		if (tag.empty())
		{
			return format_to(ctx.out(), U"{}", sv);
		}
		else
		{
			const std::u32string format = (U"{:" + tag + U'}');
			return format_to(ctx.out(), format, sv);
		}
	}
};

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::DateTime>
{
	[[nodiscard]]
	size_t operator ()(const s3d::DateTime& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/DateTime.ipp"
