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
# include <sstream>
# include <typeinfo>
# include "Common.hpp"
# include "Error.hpp"
# include "Unicode.hpp"
# include "ParseBool.hpp"
# include "ParseInt.hpp"
# include "ParseFloat.hpp"
# include "Demangle.hpp"

namespace s3d
{
	/// @brief 文字列をパースしてデータ型に変換します。
	/// @tparam Type 変換先のデータ型
	/// @param s 変換する文字列
	/// @throw ParseError パースに失敗した場合
	/// @return 文字列から変換されたデータ
	template <class Type>
	[[nodiscard]]
	inline Type Parse(StringView s);

	/// @brief 文字列をパースして bool 型に変換します。
	/// @param s 変換する文字列
	/// @throw ParseError パースに失敗した場合
	/// @return 文字列から変換されたデータ
	template <>
	[[nodiscard]]
	inline bool Parse<bool>(StringView s);

	/// @brief 文字列をパースして char 型に変換します。
	/// @param s 変換する文字列
	/// @throw ParseError パースに失敗した場合
	/// @return 文字列から変換されたデータ
	template <>
	[[nodiscard]]
	inline char Parse<char>(StringView s);

	/// @brief 文字列をパースして char32 型に変換します。
	/// @param s 変換する文字列
	/// @throw ParseError パースに失敗した場合
	/// @return 文字列から変換されたデータ
	template <>
	[[nodiscard]]
	inline char32 Parse<char32>(StringView s);

	/// @brief 文字列をパースして返します。
	/// @param s 変換する文字列
	/// @remark 前後の空白文字は除去されます。
	/// @return 文字列から変換されたデータ
	template <>
	[[nodiscard]]
	inline String Parse<String>(StringView s);

	/// @brief 文字列をパースしてデータ型に変換します。
	/// @tparam Type 変換先のデータ型
	/// @param s 変換する文字列
	/// @remark この関数はパースに失敗しても例外を投げません。
	/// @return 文字列から変換されたデータの Optional, 失敗した場合は none
	template <class Type>
	[[nodiscard]]
	inline Optional<Type> ParseOpt(StringView s);

	/// @brief 文字列をパースして bool 型に変換します。
	/// @param s 変換する文字列
	/// @remark この関数はパースに失敗しても例外を投げません。
	/// @return 文字列から変換されたデータの Optional, 失敗した場合は none
	template <>
	[[nodiscard]]
	inline Optional<bool> ParseOpt<bool>(StringView s);

	/// @brief 文字列をパースして char 型に変換します。
	/// @param s 変換する文字列
	/// @remark この関数はパースに失敗しても例外を投げません。
	/// @return 文字列から変換されたデータの Optional, 失敗した場合は none
	template <>
	[[nodiscard]]
	inline Optional<char> ParseOpt<char>(StringView s);

	/// @brief 文字列をパースして char32 型に変換します。
	/// @param s 変換する文字列
	/// @remark この関数はパースに失敗しても例外を投げません。
	/// @return 文字列から変換されたデータの Optional, 失敗した場合は none
	template <>
	[[nodiscard]]
	inline Optional<char32> ParseOpt<char32>(StringView s);

	/// @brief 文字列をパースして返します。
	/// @param s 変換する文字列
	/// @remark 前後の空白文字は除去されます。
	/// @return 文字列から変換されたデータの Optional, 文字列が空だった場合は none
	template <>
	[[nodiscard]]
	inline Optional<String> ParseOpt<String>(StringView s);

	/// @brief 文字列をパースしてデータ型に変換します。
	/// @tparam Type 変換先のデータ型
	/// @tparam U パースに失敗したときに代わりに返す値を構築する引数の型
	/// @param s 変換する文字列
	/// @param defaultValue パースに失敗したときに代わりに返す値を構築する引数
	/// @remark この関数はパースに失敗しても例外を投げません。
	/// @return 文字列から変換されたデータ、失敗した場合は defaultValue から構築した Type 型の値
	template <class Type, class U>
	[[nodiscard]]
	Type ParseOr(StringView s, U&& defaultValue);
}

# include "detail/Parse.ipp"
