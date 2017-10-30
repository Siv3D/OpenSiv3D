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
# include <sstream>
# include "Fwd.hpp"
# include "ParseBool.hpp"
# include "ParseInt.hpp"
# include "ParseFloat.hpp"

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
	/// <param name="text">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>* = nullptr>
	[[nodiscard]] inline Type Parse(const String& text)
	{
		Type to;

		std::wistringstream ws(text.str());

		if (ws >> to)
		{
			return to;
		}

		return to;
	}

	template <class IntegerType, std::enable_if_t<std::is_integral_v<IntegerType>>* = nullptr>
	[[nodiscard]] inline IntegerType Parse(const String& text)
	{
		return ParseInt<IntegerType>(text);
	}

	template <class FloatType, std::enable_if_t<std::is_floating_point_v<FloatType>>* = nullptr>
	[[nodiscard]] inline FloatType Parse(const String& text)
	{
		return ParseFloat<FloatType>(text);
	}

	template <>
	[[nodiscard]] inline bool Parse<bool>(const String& text)
	{
		return ParseBool(text);
	}

	template <>
	[[nodiscard]] inline char Parse<char>(const String& text)
	{
		const String t = text.trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	[[nodiscard]] inline char32 Parse<char32>(const String& text)
	{
		const String t = text.trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return t[0];
	}

	template <>
	[[nodiscard]] inline String Parse<String>(const String& text)
	{
		return text.trimmed();
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
	template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>* = nullptr>
	[[nodiscard]] inline Optional<Type> ParseOpt(const String& text)
	{
		Type to;

		if (std::wistringstream{ text.str() } >> to)
		{
			return Optional<Type>(std::move(to));
		}

		return none;
	}

	template <class IntegerType, std::enable_if_t<std::is_integral_v<IntegerType>>* = nullptr>
	[[nodiscard]] inline Optional<IntegerType> ParseOpt(const String& text)
	{
		return ParseIntOpt<IntegerType>(text);
	}

	template <class FloatType, std::enable_if_t<std::is_floating_point_v<FloatType>>* = nullptr>
	[[nodiscard]] inline Optional<FloatType> ParseOpt(const String& text)
	{
		return ParseFloatOpt<FloatType>(text);
	}

	template <>
	[[nodiscard]] inline Optional<bool> ParseOpt<bool>(const String& text)
	{
		return ParseBoolOpt(text);
	}

	template <>
	[[nodiscard]] inline Optional<char> ParseOpt<char>(const String& text)
	{
		const String t = text.trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	[[nodiscard]] inline Optional<char32> ParseOpt<char32>(const String& text)
	{
		const String t = text.trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return t[0];
	}

	template <>
	[[nodiscard]] inline Optional<String> ParseOpt<String>(const String& text)
	{
		String t = text.trimmed();

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
	/// <param name="text">
	/// 変換する文字列
	/// </param>
	/// <param name="defaultValue">
	/// 変換に失敗した場合に返す値
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの, 失敗した場合は defaultValue
	/// </returns>
	template <class Type, class U>
	[[nodiscard]] Type ParseOr(const String& text, U&& defaultValue)
	{
		return ParseOpt<Type>(text).value_or(std::forward<U>(defaultValue));
	}
}
