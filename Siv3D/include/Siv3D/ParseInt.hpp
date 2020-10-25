//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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
	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	Int ParseInt(StringView s, Arg::radix_<uint32> radix = 0);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]]
	int8 ParseInt<int8>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]]
	uint8 ParseInt<uint8>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]]
	int16 ParseInt<int16>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>	
	template <>
	[[nodiscard]]
	uint16 ParseInt<uint16>(StringView s, Arg::radix_<uint32> radix);
	

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]]
	int32 ParseInt<int32>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>	
	template <>
	[[nodiscard]]
	uint32 ParseInt<uint32>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>	
	template <>
	[[nodiscard]]
	long ParseInt<long>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]]
	unsigned long ParseInt<unsigned long>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]]
	long long ParseInt<long long>(StringView s, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]]
	unsigned long long ParseInt<unsigned long long>(StringView s, Arg::radix_<uint32> radix);

	SIV3D_CONCEPT_INTEGRAL
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
