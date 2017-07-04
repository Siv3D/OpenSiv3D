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
# include "Date.hpp"

namespace s3d
{
	/// <summary>
	/// 日付と時刻
	/// </summary>
	struct DateTime : Date
	{
		/// <summary>
		/// 時 [0-23]
		/// </summary>
		int32 hour;

		/// <summary>
		/// 分 [0-59]
		/// </summary>
		int32 minute;

		/// <summary>
		/// 秒 [0-59]
		/// </summary>
		int32 second;

		/// <summary>
		/// ミリ秒 [0-999]
		/// </summary>
		int32 milliseconds;

		/// <summary>
		/// 日付と時刻の妥当性を返します。
		/// </summary>
		/// <remarks>
		/// 日付と時刻が正しい範囲の値であれば true, それ以外の場合は false
		/// </remarks>
		constexpr bool isValid() const noexcept
		{
			return Date::isValid()
				&& (0 <= hour && hour <= 23)
				&& (0 <= minute && minute <= 59)
				&& (0 <= second && second <= 59)
				&& (0 <= milliseconds && milliseconds <= 999);
		}

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		DateTime() noexcept = default;

		/// <summary>
		/// 日付と時刻を作成します。
		/// </summary>
		/// <param name="_year">
		/// 年
		/// </param>
		/// <param name="_month">
		/// 月 [1-12]
		/// </param>
		/// <param name="_day">
		/// 日 [1-31]
		/// </param>
		/// <param name="_hour">
		/// 時 [0-23]、デフォルトでは 0
		/// </param>
		/// <param name="_minute">
		/// 分 [0-59]、デフォルトでは 0
		/// </param>
		/// <param name="_second">
		/// 秒 [0-59]、デフォルトでは 0
		/// </param>
		/// <param name="_milliseconds">
		/// ミリ秒 [0-999]、デフォルトでは 0
		/// </param>
		/// <remarks>
		/// 指定された時刻や日付が存在するかはチェックされません。
		/// </remarks>
		constexpr DateTime(
			int32 _year,
			int32 _month,
			int32 _day,
			int32 _hour = 0,
			int32 _minute = 0,
			int32 _second = 0,
			int32 _milliseconds = 0) noexcept
			: Date(_year, _month, _day)
			, hour(_hour)
			, minute(_minute)
			, second(_second)
			, milliseconds(_milliseconds) {}

		/// <summary>
		/// 日付と時刻を作成します。
		/// </summary>
		/// <param name="date">
		/// 年月日
		/// </param>
		/// <param name="_hour">
		/// 時 [0-23]、デフォルトでは 0
		/// </param>
		/// <param name="_minute">
		/// 分 [0-59]、デフォルトでは 0
		/// </param>
		/// <param name="_second">
		/// 秒 [0-59]、デフォルトでは 0
		/// </param>
		/// <param name="_milliseconds">
		/// ミリ秒 [0-999]、デフォルトでは 0
		/// </param>
		/// <remarks>
		/// 指定された時刻や日付が存在するかはチェックされません。
		/// </remarks>
		constexpr DateTime(
			const Date& date,
			int32 _hour = 0,
			int32 _minute = 0,
			int32 _second = 0,
			int32 _milliseconds = 0) noexcept
			: Date(date)
			, hour(_hour)
			, minute(_minute)
			, second(_second)
			, milliseconds(_milliseconds) {}

		/// <summary>
		/// 現在のローカルの日付と時刻を返します。
		/// </summary>
		/// <returns>
		/// 現在のローカルの日付と時刻
		/// </returns>
		static DateTime Now();

		/// <summary>
		/// 現在の協定世界時刻 (UTC) の日付と時刻を返します。
		/// </summary>
		/// <returns>
		/// 現在の協定世界時刻 (UTC) の日付と時刻
		/// </returns>
		static DateTime NowUTC();

		/// <summary>
		/// 日付と時刻を指定したフォーマットの文字列で返します。
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
		///
		/// 引用符で囲まれていないアルファベットはパターン文字として解釈されます。
		/// '' は単一引用符を表します。
		/// </summary>
		/// <param name="format">
		/// フォーマット指定
		/// </param>
		/// <returns>
		/// フォーマットされた日付と時刻
		/// </returns>
		String format(const String& pattern = S3DSTR("yyyy/M/d HH:mm:ss")) const;

		/// <summary>
		/// 日付と時刻を進めます。
		/// </summary>
		/// <param name="days">
		/// 進める日数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		DateTime& operator +=(const Days& days)
		{
			Date::operator +=(days);
			return *this;
		}

		/// <summary>
		/// 日付と時刻を戻します。
		/// </summary>
		/// <param name="days">
		/// 戻す日数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		DateTime& operator -=(const Days& days)
		{
			Date::operator -=(days);
			return *this;
		}

		/// <summary>
		/// 日付と時刻を進めます。
		/// </summary>
		/// <param name="days">
		/// 進める時間（ミリ秒）
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		DateTime& operator +=(const Milliseconds& _milliseconds);

		/// <summary>
		/// 日付と時刻を戻します
		/// </summary>
		/// <param name="days">
		/// 戻す時間（ミリ秒）
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		DateTime& operator -= (const Milliseconds& _milliseconds)
		{
			return *this += (-_milliseconds);
		}
	};

	/// <summary>
	/// 日付と時刻を進めます。
	/// </summary>
	/// <param name="dateTime">
	/// 日付と時刻
	/// </param>
	/// <param name="days">
	/// 進める日数
	/// </param>
	/// <returns>
	/// 進めた結果の日付と時刻
	/// </returns>
	inline DateTime operator +(const DateTime& dateTime, const Days& days)
	{
		return DateTime(dateTime) += days;
	}

	/// <summary>
	/// 日付と時刻を戻します。
	/// </summary>
	/// <param name="dateTime">
	/// 日付と時刻
	/// </param>
	/// <param name="days">
	/// 戻す日数
	/// </param>
	/// <returns>
	/// 戻した結果の日付と時刻
	/// </returns>
	inline DateTime operator -(const DateTime& dateTime, const Days& days)
	{
		return DateTime(dateTime) -= days;
	}

	/// <summary>
	/// 日付と時刻を進めます。
	/// </summary>
	/// <param name="dateTime">
	/// 日付と時刻
	/// </param>
	/// <param name="milliseconds">
	/// 進める時間（ミリ秒）
	/// </param>
	/// <returns>
	/// 進めた結果の時刻と日付
	/// </returns>
	inline DateTime operator +(const DateTime& dateTime, const Milliseconds& milliseconds)
	{
		return DateTime(dateTime) += milliseconds;
	}

	/// <summary>
	/// 日付と時刻を戻します
	/// </summary>
	/// <param name="dateTime">
	/// 日付と時刻
	/// </param>
	/// <param name="milliseconds">
	/// 戻す時間（ミリ秒）
	/// </param>
	/// <returns>
	/// 戻した結果の時刻と日付
	/// </returns>
	inline DateTime operator -(const DateTime& dateTime, const Milliseconds& milliseconds)
	{
		return DateTime(dateTime) -= milliseconds;
	}

	/// <summary>
	/// 2 つの日付と時刻の間の時間を計算します。
	/// </summary>
	/// <param name="to">
	/// 終わりの日付と時刻
	/// </param>
	/// <param name="from">
	/// はじめの日付と時刻
	/// </param>
	/// <returns>
	/// 2 つの日付の間の時間（ミリ秒）
	/// </returns>
	Milliseconds operator -(const DateTime& a, const DateTime& b);

	/// <summary>
	/// 2 つの日付と時刻が等しいかを調べます。
	/// </summary>
	/// <param name="a">
	/// 比較する日付と時刻
	/// </param>
	/// <param name="b">
	/// 比較する日付と時刻
	/// </param>
	/// <returns>
	/// 2 つの日付と時刻が等しい場合 true, それ以外の場合は false
	/// </returns>
	inline bool operator ==(const DateTime& a, const DateTime& b)
	{
		return ::memcmp(&a, &b, sizeof(DateTime)) == 0;
	}

	/// <summary>
	/// 2 つの日付と時刻が異なるかを調べます。
	/// </summary>
	/// <param name="a">
	/// 比較する日付と時刻
	/// </param>
	/// <param name="b">
	/// 比較する日付と時刻
	/// </param>
	/// <returns>
	/// 2 つの日付と時刻が異なる場合 true, それ以外の場合は false
	/// </returns>
	inline bool operator !=(const DateTime& a, const DateTime& b)
	{
		return !(a == b);
	}

	/// <summary>
	/// 日付と時刻の &lt; 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付と時刻
	/// </param>
	/// <param name="b">
	/// 比較する日付と時刻
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator <(const DateTime& a, const DateTime& b)
	{
		return ::memcmp(&a, &b, sizeof(DateTime)) < 0;
	}

	/// <summary>
	/// 日付と時刻の &gt; 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付と時刻
	/// </param>
	/// <param name="b">
	/// 比較する日付と時刻
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator >(const DateTime& a, const DateTime& b)
	{
		return ::memcmp(&a, &b, sizeof(DateTime)) > 0;
	}

	/// <summary>
	/// 日付と時刻の &lt;= 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付と時刻
	/// </param>
	/// <param name="b">
	/// 比較する日付と時刻
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator <=(const DateTime& a, const DateTime& b)
	{
		return !(a > b);
	}

	/// <summary>
	/// 日付と時刻の &gt;= 比較を行います。
	/// </summary>
	/// <param name="a">
	/// 比較する日付と時刻
	/// </param>
	/// <param name="b">
	/// 比較する日付と時刻
	/// </param>
	/// <returns>
	/// 比較結果
	/// </returns>
	inline bool operator >=(const DateTime& a, const DateTime& b)
	{
		return !(a < b);
	}
}

namespace std
{
	template <>
	struct hash<s3d::DateTime>
	{
		size_t operator()(const s3d::DateTime& dateTime) const
		{
			return s3d::Hash::FNV1a(dateTime);
		}
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting DateTime
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
	inline void Formatter(FormatData& formatData, const DateTime& dateTime)
	{
		formatData.string.append(dateTime.format());
	}

	/// <summary>
	/// 出力ストリームに日付と時刻を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="dateTime">
	/// 日付と時刻
	/// </param>
	/// <remarks>
	/// "yyyy/M/d HH:mm:ss" 形式でフォーマットされます。
	/// </remarks>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> os, const DateTime& dateTime)
	{
		return os << dateTime.format();
	}
}
//
//////////////////////////////////////////////////////////////////////////////
