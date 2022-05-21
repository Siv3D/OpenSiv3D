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
# include "Optional.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	template <class Int>
	[[nodiscard]]
	Int ParseInt(StringView s, Arg::radix_<uint32> radix = 0);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	int8 ParseInt<int8>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	uint8 ParseInt<uint8>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	int16 ParseInt<int16>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	uint16 ParseInt<uint16>(StringView s, Arg::radix_<uint32> radix);
	
	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	int32 ParseInt<int32>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	uint32 ParseInt<uint32>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	long ParseInt<long>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	unsigned long ParseInt<unsigned long>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	long long ParseInt<long long>(StringView s, Arg::radix_<uint32> radix);

	/// @brief 文字列をパースして整数を返します。
	/// @param s 文字列
	/// @param radix 基数
	/// @throw ParseError パースに失敗した場合
	/// @return パースした結果
	template <>
	[[nodiscard]]
	unsigned long long ParseInt<unsigned long long>(StringView s, Arg::radix_<uint32> radix);

	template <class Int>
	[[nodiscard]]
	Optional<Int> ParseIntOpt(StringView s, Arg::radix_<uint32> radix = (Arg::radix = 0)) noexcept;

	template <>
	[[nodiscard]]
	Optional<int8> ParseIntOpt<int8>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<uint8> ParseIntOpt<uint8>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<int16> ParseIntOpt<int16>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<uint16> ParseIntOpt<uint16>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<int32> ParseIntOpt<int32>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<uint32> ParseIntOpt<uint32>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<long> ParseIntOpt<long>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<unsigned long> ParseIntOpt<unsigned long>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<long long> ParseIntOpt<long long>(StringView s, Arg::radix_<uint32> radix) noexcept;

	template <>
	[[nodiscard]]
	Optional<unsigned long long> ParseIntOpt<unsigned long long>(StringView s, Arg::radix_<uint32> radix) noexcept;
}
