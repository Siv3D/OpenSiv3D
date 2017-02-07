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
# include "Fwd.hpp"
# include "ParseInt.hpp"
# include "ParseFloat.hpp"
# include "ParseBool.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		Parse
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <class Type, std::enable_if_t<!std::is_arithmetic<Type>::value>* = nullptr>
	inline Type Parse(const String& str)
	{
		Type to;

		std::wistringstream ws(str.str());

		if (ws >> to)
		{
			return to;
		}

		return to;
	}

	template <class IntegerType, std::enable_if_t<std::is_integral<IntegerType>::value>* = nullptr>
	inline IntegerType Parse(const String& str)
	{
		return ParseInt<IntegerType>(str);
	}

	template <class FloatType, std::enable_if_t<std::is_floating_point<FloatType>::value>* = nullptr>
	inline FloatType Parse(const String& str)
	{
		return ParseFloat<FloatType>(str);
	}

	template <>
	inline bool Parse<bool>(const String& str)
	{
		return ParseBool(str);
	}

	template <>
	inline char Parse<char>(const String& str)
	{
		const String t = str.trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	inline wchar Parse<wchar>(const String& str)
	{
		const String t = str.trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return t[0];
	}

	template <>
	inline String Parse<String>(const String& str)
	{
		return str.trimmed();
	}

	////////////////////////////////////////////////////////////////
	//
	//		ParseOpt
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <class Type, std::enable_if_t<!std::is_arithmetic<Type>::value>* = nullptr>
	inline Optional<Type> ParseOpt(const String& str)
	{
		Type to;

		if (std::wistringstream{ str.str() } >> to)
		{
			return Optional<Type>(std::move(to));
		}

		return none;
	}

	template <class IntegerType, std::enable_if_t<std::is_integral<IntegerType>::value>* = nullptr>
	inline Optional<IntegerType> ParseOpt(const String& str)
	{
		return ParseIntOpt<IntegerType>(str);
	}

	template <class FloatType, std::enable_if_t<std::is_floating_point<FloatType>::value>* = nullptr>
	inline Optional<FloatType> ParseOpt(const String& str)
	{
		return ParseFloatOpt<FloatType>(str);
	}

	template <>
	inline Optional<bool> ParseOpt<bool>(const String& str)
	{
		return ParseBoolOpt(str);
	}

	template <>
	inline Optional<char> ParseOpt<char>(const String& str)
	{
		const String t = str.trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	inline Optional<wchar> ParseOpt<wchar>(const String& str)
	{
		const String t = str.trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return t[0];
	}

	template <>
	inline Optional<String> ParseOpt<String>(const String& str)
	{
		String t = str.trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return Optional<String>(std::move(t));
	}

	////////////////////////////////////////////////////////////////
	//
	//		ParseOr
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <param name="defaultValue">
	/// 変換に失敗した場合に返す値
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの, 失敗した場合は defaultValue
	/// </returns>
	template <class Type, class U>
	Type ParseOr(const String& str, U&& defaultValue)
	{
		return ParseOpt<Type>(str).value_or(std::forward<U>(defaultValue));
	}
}
