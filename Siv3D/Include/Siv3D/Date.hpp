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
# include <string.h>
# include "Fwd.hpp"
# include "String.hpp"
# include "Duration.hpp"
# include "Hash.hpp"

namespace s3d
{
	Date operator +(const Date& date, const Days& days);
	Date operator -(const Date& date, const Days& days);

	namespace detail
	{
		constexpr int32 DaysInMonth[2][12]
		{
			{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	// common year
			{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	// leap year
		};
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
		/// 曜日
		/// </summary>
		enum DayOfWeek : int32
		{
			/// <summary>
			/// 日曜日
			/// </summary>
			Sunday,

			/// <summary>
			/// 月曜日
			/// </summary>
			Monday,

			/// <summary>
			/// 火曜日
			/// </summary>
			Tuesday,

			/// <summary>
			/// 水曜日
			/// </summary>
			Wednesday,

			/// <summary>
			/// 木曜日
			/// </summary>
			Thursday,

			/// <summary>
			/// 金曜日
			/// </summary>
			Friday,

			/// <summary>
			/// 土曜日
			/// </summary>
			Saturday
		};

		/// <summary>
		/// 曜日を返します。
		/// </summary>
		/// <returns>
		/// 曜日
		/// </returns>
		constexpr DayOfWeek dayOfWeek() const noexcept
		{
			return static_cast<DayOfWeek>((month == 1 || month == 2) ?
				((year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + (13 * (month + 12) + 8) / 5 + day) % 7
				: (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7);
		}

		/// <summary>
		/// 曜日を日本語で返します。
		/// </summary>
		/// <returns>
		/// 日本語の曜日
		/// </returns>
		const String& dayOfWeekJP() const;

		/// <summary>
		/// 曜日を英語で返します。
		/// </summary>
		/// <returns>
		/// 英語の曜日
		/// </returns>
		const String& dayOfWeekEN() const;

		/// <summary>
		/// 現在のローカルの年月日と一致するかを返します。
		/// </summary>
		/// <returns>
		/// 現在のローカルの年月日と一致する場合は true, それ以外の場合は false
		/// </returns>
		bool isToday() const;

		/// <summary>
		/// うるう年であるかを返します。
		/// </summary>
		/// <returns>
		/// うるう年である場合は true, それ以外の場合は false
		/// </returns>
		constexpr bool isLeapYear() const noexcept
		{
			return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
		}

		/// <summary>
		/// 月の日数を返します。
		/// </summary>
		/// <returns>
		/// 月の日数
		/// </returns>
		constexpr int32 daysInMonth() const noexcept
		{
			return (month < 1 || 13 <= month) ? 0 : detail::DaysInMonth[isLeapYear()][month - 1];
		}

		/// <summary>
		/// 1 年の日数を返します。
		/// </summary>
		/// <returns>
		/// 1 年の日数
		/// </returns>
		constexpr int32 daysInYear() const noexcept
		{
			return isLeapYear() ? 366 : 365;
		}

		/// <summary>
		/// 日付の妥当性を返します。
		/// </summary>
		/// <returns>
		/// 日付が正しい範囲の値であれば true, それ以外の場合は false
		/// </returns>
		constexpr bool isValid() const noexcept
		{
			return (1 <= month && month <= 12)
				&& (1 <= day && day <= daysInMonth());
		}

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
		String format(const String& format = S3DSTR("yyyy/M/d")) const;

		/// <summary>
		/// 昨日のローカルの日付を返します。
		/// </summary>
		/// <returns>
		/// 昨日のローカルの日付
		/// </returns>
		static Date Yesterday()
		{
			return Today() - Days(1);
		}

		/// <summary>
		/// 現在のローカルの日付を返します。
		/// </summary>
		/// <returns>
		/// 現在のローカルの日付
		/// </returns>
		static Date Today();

		/// <summary>
		/// 明日のローカルの日付を返します。
		/// </summary>
		/// <returns>
		/// 明日のローカルの日付
		/// </returns>
		static Date Tomorrow()
		{
			return Today() + Days(1);
		}

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
		Date& operator -=(const Days& days)
		{
			return *this += (-days);
		}
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
	Date operator +(const Date& date, const Days& days);

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
	inline Date operator -(const Date& date, const Days& days)
	{
		return date + (-days);
	}

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
	Days operator -(const Date& to, const Date& from);

	/// <summary>
	/// 2 つの日付が等しいかを調べます。
	/// </summary>
	/// <param name="a">
	/// 比較する日付
	/// </param>
	/// <param name="b">
	/// 比較する日付
	/// </param>
	/// <returns>
	/// 2 つの日付が等しい場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool operator ==(const Date& a, const Date& b) noexcept
	{
		return a.year == b.year && a.month == b.month && a.day == b.day;
	}

	/// <summary>
	/// 2 つの日付が異なるかを調べます。
	/// </summary>
	/// <param name="a">
	/// 比較する日付
	/// </param>
	/// <param name="b">
	/// 比較する日付
	/// </param>
	/// <returns>
	/// 2 つの日付が異なる場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool operator !=(const Date& a, const Date& b) noexcept
	{
		return !(a == b);
	}

	/// <summary>
	/// 日付の &lt; 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付
	/// </param>
	/// <param name="b">
	/// 比較する日付
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator <(const Date& a, const Date& b)
	{
		return ::memcmp(&a, &b, sizeof(Date)) < 0;
	}

	/// <summary>
	/// 日付の &gt; 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付
	/// </param>
	/// <param name="b">
	/// 比較する日付
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator >(const Date& a, const Date& b)
	{
		return ::memcmp(&a, &b, sizeof(Date)) > 0;
	}

	/// <summary>
	/// 日付の &lt;= 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付
	/// </param>
	/// <param name="b">
	/// 比較する日付
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator <=(const Date& a, const Date& b)
	{
		return !(a > b);
	}

	/// <summary>
	/// 日付の &gt;= 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付
	/// </param>
	/// <param name="b">
	/// 比較する日付
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator >=(const Date& a, const Date& b)
	{
		return !(a < b);
	}
}

namespace std
{
	template <>
	struct hash<s3d::Date>
	{
		size_t operator()(const s3d::Date& date) const
		{
			return s3d::Hash::FNV1a(date);
		}
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Date
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const Date& date)
	{
		formatData.string.append(date.format());
	}

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> os, const Date& date)
	{
		return os << date.format();
	}
}
//
//////////////////////////////////////////////////////////////////////////////
