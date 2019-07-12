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
# include <sstream>
# include "Fwd.hpp"
# include "Error.hpp"
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
	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <class Type>
	[[nodiscard]] inline Type Parse(StringView text)
	{
		if constexpr (std::is_integral_v<Type>)
		{
			return ParseInt<Type>(text);
		}
		else if constexpr (std::is_floating_point_v<Type>)
		{
			return ParseFloat<Type>(text);
		}
		else
		{
			Type to;

			if (!(std::wistringstream{ Unicode::ToWString(text) } >> to))
			{
				throw ParseError(U"Parse({}) failed"_fmt(text));
			}

			return to;
		}
	}

	template <>
	[[nodiscard]] bool Parse<bool>(StringView text);

	template <>
	[[nodiscard]] char Parse<char>(StringView text);

	template <>
	[[nodiscard]] char32 Parse<char32>(StringView text);

	template <>
	[[nodiscard]] String Parse<String>(StringView text);

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
	template <class Type>
	[[nodiscard]] inline Optional<Type> ParseOpt(StringView text)
	{
		if constexpr (std::is_integral_v<Type>)
		{
			return ParseIntOpt<Type>(text);
		}
		else if constexpr (std::is_floating_point_v<Type>)
		{
			// ParseFloat does not retrun none
			return ParseFloat<Type>(text);
		}
		else
		{
			Type to;

			if (std::wistringstream{ Unicode::ToWString(text) } >> to)
			{
				return Optional<Type>(std::move(to));
			}

			return none;
		}
	}

	template <>
	[[nodiscard]] Optional<bool> ParseOpt<bool>(StringView text);

	template <>
	[[nodiscard]] Optional<char> ParseOpt<char>(StringView text);

	template <>
	[[nodiscard]] Optional<char32> ParseOpt<char32>(StringView text);

	template <>
	[[nodiscard]] Optional<String> ParseOpt<String>(StringView text);

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
	[[nodiscard]] Type ParseOr(StringView text, U&& defaultValue)
	{
		return ParseOpt<Type>(text).value_or(std::forward<U>(defaultValue));
	}
}
