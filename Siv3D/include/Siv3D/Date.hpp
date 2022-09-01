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
# include <cstring>
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Common.hpp"
# include "DayOfWeek.hpp"
# include "String.hpp"
# include "Duration.hpp"
# include "FormatData.hpp"
# include "FormatLiteral.hpp"

namespace s3d
{
	/// @brief 日付 | Date
	struct Date
	{
		/// @brief 西暦
		int32 year;

		/// @brief 月 [1-12]
		int32 month;

		/// @brief 日 [1-31]
		int32 day;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Date() noexcept = default;

		/// @brief 日付を作成します。
		/// @param _year 西暦
		/// @param _month 月
		/// @param _day 日
		/// @remark 指定された日付が存在するかはチェックされません。
		SIV3D_NODISCARD_CXX20
		explicit constexpr Date(int32 _year, int32 _month = 1, int32 _day = 1) noexcept;

		/// @brief 曜日を返します。
		/// @return 曜日
		[[nodiscard]]
		constexpr DayOfWeek dayOfWeek() const noexcept;

		/// @brief 現在のローカルの年月日と一致するかを返します。
		/// @return 現在のローカルの年月日と一致する場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isToday() const noexcept;

		/// @brief うるう年であるかを返します。
		/// @return うるう年である場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isLeapYear() const noexcept;

		/// @brief 1 年の日数を返します。
		/// @return 1 年の日数
		[[nodiscard]]
		constexpr int32 daysInYear() const noexcept;

		/// @brief 月の日数を返します。
		/// @return 月の日数
		[[nodiscard]]
		constexpr int32 daysInMonth() const noexcept;

		/// @brief 日付の妥当性を返します。
		/// @return 日付が正しい範囲の値であれば true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isValid() const noexcept;

		/// @brief 日付を指定したフォーマットの文字列で返します。
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
		/// E		日本語の曜日 (日-土)
		/// @param format フォーマット指定
		/// @return フォーマットされた日付
		[[nodiscard]]
		String format(StringView format = U"yyyy-MM-dd"_sv) const;

		/// @brief 指定した日数だけ進めた日付を返します。
		/// @param days 日数
		/// @return 指定した日数だけ進めた日付
		Date operator +(const Days& days) const noexcept;

		/// @brief 指定した日数だけ戻した日付を返します。
		/// @param days 日数
		/// @return 指定した日数だけ戻した日付
		Date operator -(const Days& days) const noexcept;

		/// @brief 日付の差を計算します。
		/// @param to 日付
		/// @param from 日付
		/// @return `from` から `to` までの日数
		[[nodiscard]]
		friend constexpr Days operator -(const Date& to, const Date& from) noexcept
		{
			return Subtract(to, from);
		}

		/// @brief 日付を進めます
		/// @param days 進める日数
		/// @return *this
		Date& operator +=(const Days& days) noexcept;

		/// @brief 日付を戻します
		/// @param days 戻す日数
		/// @return *this
		Date& operator -=(const Days& days) noexcept;

	# if __cpp_impl_three_way_comparison

		friend constexpr auto operator <=>(const Date&, const Date&) = default;

	# else

		/// @brief 日付が等しいかを返します。
		/// @param lhs 比較する日付
		/// @param rhs 比較する日付
		/// @return 2 つの日付が等しい場合 true, それ以外の場合は false
		[[nodiscard]]
		friend bool operator ==(const Date& lhs, const Date& rhs) noexcept
		{
			return (lhs.year == rhs.year) && (lhs.month == rhs.month) && (lhs.day == rhs.day);
		}

		/// @brief 日付が異なるかを返します。
		/// @param lhs 比較する日付
		/// @param rhs 比較する日付
		/// @return 2 つの日付が異なる場合 true, それ以外の場合は false
		[[nodiscard]]
		friend bool operator !=(const Date& lhs, const Date& rhs) noexcept
		{
			return (lhs.year != rhs.year) || (lhs.month != rhs.month) || (lhs.day != rhs.day);
		}

		/// @brief 日付の &lt; 比較を行います。
		/// @param lhs 比較する日付
		/// @param rhs 比較する日付
		/// @return 比較結果
		[[nodiscard]]
		friend bool operator <(const Date& lhs, const Date& rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(Date)) < 0;
		}

		/// @brief 日付の &gt; 比較を行います。
		/// @param lhs 比較する日付
		/// @param rhs 比較する日付
		/// @return 比較結果
		[[nodiscard]]
		friend bool operator >(const Date& lhs, const Date& rhs) noexcept
		{
			return std::memcmp(&lhs, &rhs, sizeof(Date)) > 0;
		}

		/// @brief 日付の &lt;= 比較を行います。
		/// @param lhs 比較する日付
		/// @param rhs 比較する日付
		/// @return 比較結果
		[[nodiscard]]
		friend bool operator <=(const Date& lhs, const Date& rhs) noexcept
		{
			return !(lhs > rhs);
		}

		/// @brief 日付の &gt;= 比較を行います。
		/// @param lhs 比較する日付
		/// @param rhs 比較する日付
		/// @return 比較結果
		[[nodiscard]]
		friend bool operator >=(const Date& lhs, const Date& rhs) noexcept
		{
			return !(lhs < rhs);
		}

	# endif

		/// @brief 日付のハッシュ値を返します
		/// @return 日付のハッシュ値
		[[nodiscard]]
		size_t hash() const noexcept;

		/// @brief 昨日の日付（ローカルタイム）を返します。
		/// @return 昨日の日付（ローカルタイム）
		[[nodiscard]]
		static Date Yesterday() noexcept;

		/// @brief 現在の日付（ローカルタイム）を返します。
		/// @return 現在の日付（ローカルタイム）
		[[nodiscard]]
		static Date Today() noexcept;

		/// @brief 明日の日付（ローカルタイム）を返します。
		/// @return 明日の日付（ローカルタイム）
		[[nodiscard]]
		static Date Tomorrow() noexcept;

		/// @brief 
		/// @param year 
		/// @return 
		[[nodiscard]]
		static constexpr bool IsLeapYear(int32 year) noexcept;

		/// @brief 
		/// @param year 
		/// @return 
		[[nodiscard]]
		static constexpr int32 DaysInYear(int32 year) noexcept;

		/// @brief 
		/// @param year 
		/// @param month 
		/// @return 
		[[nodiscard]]
		static constexpr int32 DaysInMonth(int32 year, int32 month) noexcept;

		/// @brief 
		/// @param a 
		/// @param b 
		/// @return 
		[[nodiscard]]
		static constexpr Days Subtract(const Date& a, const Date& b) noexcept;

		/// @brief 
		/// @tparam CharType 
		/// @param output 
		/// @param value 
		/// @return 
		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Date& value)
		{
			return output << value.format();
		}

		/// @brief 
		/// @param formatData 
		/// @param value 
		friend void Formatter(FormatData& formatData, const Date& value)
		{
			formatData.string.append(value.format());
		}
	};

	/// @brief 日付を文字列に変換します。
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
	/// @param date 日付
	/// @param format フォーマット指定
	/// @return フォーマットされた日付
	[[nodiscard]]
	String FormatDate(const Date& date, StringView format = U"yyyy-MM-dd"_sv);
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Date, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Date& value, FormatContext& ctx)
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
struct std::hash<s3d::Date>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Date& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/Date.ipp"
