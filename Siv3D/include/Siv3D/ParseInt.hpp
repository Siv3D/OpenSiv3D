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
# include "PredefinedNamedParameter.hpp"
# include "String.hpp"

namespace s3d
{
	template <class Integer>
	[[nodiscard]] Integer ParseInt(StringView view, Arg::radix_<uint32> radix = 0);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]] int8 ParseInt<int8>(StringView view, Arg::radix_<uint32> radix);
	
	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]] uint8 ParseInt<uint8>(StringView view, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]] int16 ParseInt<int16>(StringView view, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>	
	template <>
	[[nodiscard]] uint16 ParseInt<uint16>(StringView view, Arg::radix_<uint32> radix);
	template <>

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>	
	[[nodiscard]] int32 ParseInt<int32>(StringView view, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>	
	template <>
	[[nodiscard]] uint32 ParseInt<uint32>(StringView view, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>	
	template <>
	[[nodiscard]] long ParseInt<long>(StringView view, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]] unsigned long ParseInt<unsigned long>(StringView view, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]] long long ParseInt<long long>(StringView view, Arg::radix_<uint32> radix);

	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	template <>
	[[nodiscard]] unsigned long long ParseInt<unsigned long long>(StringView view, Arg::radix_<uint32> radix);

	template <class Integer>
	[[nodiscard]] Optional<Integer> ParseIntOpt(StringView view, Arg::radix_<uint32> radix = (Arg::radix = 0));

	template <>
	[[nodiscard]] Optional<int8> ParseIntOpt<int8>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<uint8> ParseIntOpt<uint8>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<int16> ParseIntOpt<int16>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<uint16> ParseIntOpt<uint16>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<int32> ParseIntOpt<int32>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<uint32> ParseIntOpt<uint32>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<long> ParseIntOpt<long>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<unsigned long> ParseIntOpt<unsigned long>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<long long> ParseIntOpt<long long>(StringView view, Arg::radix_<uint32> radix);

	template <>
	[[nodiscard]] Optional<unsigned long long> ParseIntOpt<unsigned long long>(StringView view, Arg::radix_<uint32> radix);
}
