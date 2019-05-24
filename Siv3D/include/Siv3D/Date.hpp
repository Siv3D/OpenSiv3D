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
# include "Fwd.hpp"
# include "String.hpp"
# include "Duration.hpp"
# include "DayOfWeek.hpp"

namespace s3d
{
	[[nodiscard]] Date operator +(const Date& date, const Days& days);
	[[nodiscard]] Date operator -(const Date& date, const Days& days);

	namespace detail
	{
		inline constexpr int32 DaysInMonth[2][12]
		{
			{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	// common year
			{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	// leap year
		};

		inline constexpr int32 GetDayOfWeek(int32 year, int32 month, int32 day) noexcept
		{
			return ((month == 1 || month == 2) ?
				((year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + (13 * (month + 12) + 8) / 5 + day) % 7
				: (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7);
		}
	}

	/// <summary>
	/// 日付
	/// </summary>
	struct Date
	{
		/// <summary>
		/// 西暦
		/// </summary>
		int32 year;

		/// <summary>
		/// 月 [1-12]
		/// </summary>
		int32 month;

		/// <summary>
		/// 日 [1-31]
		/// </summary>
		int32 day;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Date() noexcept = default;

		/// <summary>
		/// 日付を作成します。
		/// </summary>
		/// <param name="_year">
		/// 西暦
		/// </param>
		/// <param name="_month">
		/// 月
		/// </param>
		/// <param name="_day">
		/// 日
		/// </param>
		explicit constexpr Date(int32 _year, int32 _month = 1, int32 _day = 1) noexcept
			: year(_year)
			, month(_month)
			, day(_day) {}

		/// <summary>
		/// 曜日を返します。
		/// </summary>
		/// <returns>
		/// 曜日
		/// </returns>
		[[nodiscard]] constexpr DayOfWeek dayOfWeek() const noexcept
		{
			return DayOfWeek{ detail::GetDayOfWeek(year, month, day) };
		}

		/// <summary>
		/// 曜日を日本語で返します。
		/// </summary>
		/// <returns>
		/// 日本語の曜日
		/// </returns>
		[[nodiscard]] String dayOfWeekJP() const;

		/// <summary>
		/// 曜日を英語で返します。
		/// </summary>
		/// <returns>
		/// 英語の曜日
		/// </returns>
		[[nodiscard]] String dayOfWeekEN() const;

		/// <summary>
		/// 現在のローカルの年月日と一致するかを返します。
		/// </summary>
		/// <returns>
		/// 現在のローカルの年月日と一致する場合は true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool isToday() const;

		/// <summary>
		/// うるう年であるかを返します。
		/// </summary>
		/// <returns>
		/// うるう年である場合は true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] constexpr bool isLeapYear() const noexcept
		{
			return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
		}

		/// <summary>
		/// 月の日数を返します。
		/// </summary>
		/// <returns>
		/// 月の日数
		/// </returns>
		[[nodiscard]] constexpr int32 daysInMonth() const noexcept
		{
			return (month < 1 || 13 <= month) ? 0 : detail::DaysInMonth[isLeapYear()][month - 1];
		}

		/// <summary>
		/// 1 年の日数を返します。
		/// </summary>
		/// <returns>
		/// 1 年の日数
		/// </returns>
		[[nodiscard]] constexpr int32 daysInYear() const noexcept
		{
			return isLeapYear() ? 366 : 365;
		}

		/// <summary>
		/// 日付の妥当性を返します。
		/// </summary>
		/// <returns>
		/// 日付が正しい範囲の値であれば true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] constexpr bool isValid() const noexcept
		{
			return (1 <= month && month <= 12)
				&& (1 <= day && day <= daysInMonth());
		}

		/// <summary>
		/// 日付を指定したフォーマットの文字列で返します。
		/// フォーマット指定のパターンは以下の通りです。
		///
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
		///
		/// 引用符で囲まれていないアルファベットはパターン文字として解釈されます。
		/// '' は単一引用符を表します。
		/// </summary>
		/// <param name="format">
		/// フォーマット指定
		/// </param>
		/// <returns>
		/// フォーマットされた日付
		/// </returns>
		[[nodiscard]] String format(StringView format = U"yyyy/M/d"_sv) const;

		/// <summary>
		/// 日付を進めます。
		/// </summary>
		/// <param name="days">
		/// 進める日数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Date& operator +=(const Days& days);

		/// <summary>
		/// 日付を戻します。
		/// </summary>
		/// <param name="days">
		/// 戻す日数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Date& operator -=(const Days& days);

		/// <summary>
		/// 2 つの日付が等しいかを調べます。
		/// </summary>
		/// <param name="other">
		/// 比較する日付
		/// </param>
		/// <returns>
		/// 2 つの日付が等しい場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] constexpr bool operator ==(const Date& other) const noexcept
		{
			return (year == other.year) && (month == other.month) && (day == other.day);
		}

		/// <summary>
		/// 2 つの日付が異なるかを調べます。
		/// </summary>
		/// <param name="other">
		/// 比較する日付
		/// </param>
		/// <returns>
		/// 2 つの日付が異なる場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] constexpr bool operator !=(const Date& other) const noexcept
		{
			return (year != other.year) || (month != other.month) || (day != other.day);
		}

		/// <summary>
		/// 日付の &lt; 比較を行います。
		/// </summary>
		/// <param name="other">
		/// 比較する日付
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator <(const Date& other) const noexcept;

		/// <summary>
		/// 日付の &gt; 比較を行います。
		/// </summary>
		/// <param name="other">
		/// 比較する日付
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator >(const Date& other) const noexcept;

		/// <summary>
		/// 日付の &lt;= 比較を行います。
		/// </summary>
		/// <param name="other">
		/// 比較する日付
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator <=(const Date& other) const noexcept;

		/// <summary>
		/// 日付の &gt;= 比較を行います。
		/// </summary>
		/// <param name="other">
		/// 比較する日付
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator >=(const Date& other) const noexcept;

		[[nodiscard]] size_t hash() const noexcept;

		/// <summary>
		/// 昨日のローカルの日付を返します。
		/// </summary>
		/// <returns>
		/// 昨日のローカルの日付
		/// </returns>
		[[nodiscard]] static Date Yesterday();

		/// <summary>
		/// 現在のローカルの日付を返します。
		/// </summary>
		/// <returns>
		/// 現在のローカルの日付
		/// </returns>
		[[nodiscard]] static Date Today();

		/// <summary>
		/// 明日のローカルの日付を返します。
		/// </summary>
		/// <returns>
		/// 明日のローカルの日付
		/// </returns>
		[[nodiscard]] static Date Tomorrow();
	};

	/// <summary>
	/// 日付を進めます。
	/// </summary>
	/// <param name="date">
	/// 日付
	/// </param>
	/// <param name="days">
	/// 進める日数
	/// </param>
	/// <returns>
	/// 進めた結果の日付
	/// </returns>
	[[nodiscard]] Date operator +(const Date& date, const Days& days);

	/// <summary>
	/// 日付を戻します。
	/// </summary>
	/// <param name="date">
	/// 日付
	/// </param>
	/// <param name="days">
	/// 戻す日数
	/// </param>
	/// <returns>
	/// 戻した結果の日付
	/// </returns>
	[[nodiscard]] Date operator -(const Date& date, const Days& days);

	/// <summary>
	/// 2 つの日付の間の日数を計算します。
	/// </summary>
	/// <param name="to">
	/// 終わりの日付
	/// </param>
	/// <param name="from">
	/// はじめの日付
	/// </param>
	/// <returns>
	/// 2 つの日付の間の日数
	/// </returns>
	[[nodiscard]] Days operator -(const Date& to, const Date& from);
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Date& value);

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> output, const Date& value)
	{
		return output << value.format();
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Date>
	{
		[[nodiscard]] size_t operator()(const s3d::Date& value) const noexcept
		{
			return value.hash();
		}
	};
}
