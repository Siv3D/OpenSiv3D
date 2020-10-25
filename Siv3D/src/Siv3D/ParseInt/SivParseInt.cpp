﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ParseInt.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/FormatLiteral.hpp>

namespace s3d
{
	namespace detail
	{
		// Copyright 2017 The Abseil Authors.
		//
		// Licensed under the Apache License, Version 2.0 (the "License");
		// you may not use this file except in compliance with the License.
		// You may obtain a copy of the License at
		//
		//      http://www.apache.org/licenses/LICENSE-2.0
		//
		// Unless required by applicable law or agreed to in writing, software
		// distributed under the License is distributed on an "AS IS" BASIS,
		// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
		// See the License for the specific language governing permissions and
		// limitations under the License.

		// Lookup tables per IntType:
		// vmax/base and vmin/base are precomputed because division costs at least 8ns.
		// TODO(junyer): Doing this per base instead (i.e. an array of structs, not a
		// struct of arrays) would probably be better in terms of d-cache for the most
		// commonly used bases.
		template <typename IntType>
		struct LookupTables {
			static const IntType kVmaxOverBase[];
			static const IntType kVminOverBase[];
		};

		// An array initializer macro for X/base where base in [0, 36].
		// However, note that lookups for base in [0, 1] should never happen because
		// base has been validated to be in [2, 36] by safe_parse_sign_and_base().
		#define X_OVER_BASE_INITIALIZER(X)                                        \
		  {                                                                       \
			0, 0, X / 2, X / 3, X / 4, X / 5, X / 6, X / 7, X / 8, X / 9, X / 10, \
				X / 11, X / 12, X / 13, X / 14, X / 15, X / 16, X / 17, X / 18,   \
				X / 19, X / 20, X / 21, X / 22, X / 23, X / 24, X / 25, X / 26,   \
				X / 27, X / 28, X / 29, X / 30, X / 31, X / 32, X / 33, X / 34,   \
				X / 35, X / 36,                                                   \
		  }

		template <typename IntType>
		const IntType LookupTables<IntType>::kVmaxOverBase[] =
			X_OVER_BASE_INITIALIZER(std::numeric_limits<IntType>::max());

		template <typename IntType>
		const IntType LookupTables<IntType>::kVminOverBase[] =
			X_OVER_BASE_INITIALIZER(std::numeric_limits<IntType>::min());

		#undef X_OVER_BASE_INITIALIZER

		// Represents integer values of digits.
		// Uses 36 to indicate an invalid character since we support
		// bases up to 36.
		constexpr int8_t kAsciiToInt[256] = {
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,  // 16 36s.
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 0,  1,  2,  3,  4,  5,
			6,  7,  8,  9,  36, 36, 36, 36, 36, 36, 36, 10, 11, 12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
			36, 36, 36, 36, 36, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
			36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36 };

		// Parse the sign and optional hex or oct prefix in text.
		inline bool safe_parse_sign_and_base(StringView* text /*inout*/, int* base_ptr /*inout*/, bool* negative_ptr /*output*/)
		{
			if (text->data() == nullptr) {
				return false;
			}

			const char32* start = text->data();
			const char32* end = start + text->size();
			int base = *base_ptr;

			// Consume whitespace.
			while (start < end && IsSpace(start[0])) {
				++start;
			}
			while (start < end && IsSpace(end[-1])) {
				--end;
			}
			if (start >= end) {
				return false;
			}

			// Consume sign.
			*negative_ptr = (start[0] == '-');
			if (*negative_ptr || start[0] == '+') {
				++start;
				if (start >= end) {
					return false;
				}
			}

			// Consume base-dependent prefix.
			//  base 0: "0x" -> base 16, "0" -> base 8, default -> base 10
			//  base 16: "0x" -> base 16
			// Also validate the base.
			if (base == 0) {
				if (end - start >= 2 && start[0] == '0' &&
					(start[1] == 'x' || start[1] == 'X')) {
					base = 16;
					start += 2;
					if (start >= end) {
						// "0x" with no digits after is invalid.
						return false;
					}
				}
				else if (end - start >= 1 && start[0] == '0') {
					base = 8;
					start += 1;
				}
				else {
					base = 10;
				}
			}
			else if (base == 16) {
				if (end - start >= 2 && start[0] == '0' &&
					(start[1] == 'x' || start[1] == 'X')) {
					start += 2;
					if (start >= end) {
						// "0x" with no digits after is invalid.
						return false;
					}
				}
			}
			else if (base >= 2 && base <= 36) {
				// okay
			}
			else {
				return false;
			}
			*text = StringView(start, end - start);
			*base_ptr = base;
			return true;
		}

		template <typename IntType>
		inline bool safe_parse_positive_int(StringView text, int base, IntType* value_p)
		{
			IntType value = 0;
			const IntType vmax = std::numeric_limits<IntType>::max();
			assert(vmax > 0);
			assert(base >= 0);
			assert(vmax >= static_cast<IntType>(base));
			const IntType vmax_over_base = LookupTables<IntType>::kVmaxOverBase[base];
			assert(base < 2 ||
				std::numeric_limits<IntType>::max() / base == vmax_over_base);
			const char32* start = text.data();
			const char32* end = start + text.size();
			// loop over digits
			for (; start < end; ++start) {
				unsigned char c = static_cast<unsigned char>(start[0]);
				int digit = kAsciiToInt[c];
				if (digit >= base) {
					*value_p = value;
					return false;
				}
				if (value > vmax_over_base) {
					*value_p = vmax;
					return false;
				}
				value *= base;
				if (value > vmax - digit) {
					*value_p = vmax;
					return false;
				}
				value += digit;
			}
			*value_p = value;
			return true;
		}

		template <typename IntType>
		inline bool safe_parse_negative_int(StringView text, int base, IntType* value_p)
		{
			IntType value = 0;
			const IntType vmin = std::numeric_limits<IntType>::min();
			assert(vmin < 0);
			assert(vmin <= 0 - base);
			IntType vmin_over_base = LookupTables<IntType>::kVminOverBase[base];
			assert(base < 2 ||
				std::numeric_limits<IntType>::min() / base == vmin_over_base);
			// 2003 c++ standard [expr.mul]
			// "... the sign of the remainder is implementation-defined."
			// Although (vmin/base)*base + vmin%base is always vmin.
			// 2011 c++ standard tightens the spec but we cannot rely on it.
			// TODO(junyer): Handle this in the lookup table generation.
			if (vmin % base > 0) {
				vmin_over_base += 1;
			}
			const char32* start = text.data();
			const char32* end = start + text.size();
			// loop over digits
			for (; start < end; ++start) {
				unsigned char c = static_cast<unsigned char>(start[0]);
				int digit = kAsciiToInt[c];
				if (digit >= base) {
					*value_p = value;
					return false;
				}
				if (value < vmin_over_base) {
					*value_p = vmin;
					return false;
				}
				value *= base;
				if (value < vmin + digit) {
					*value_p = vmin;
					return false;
				}
				value -= digit;
			}
			*value_p = value;
			return true;
		}

		// Input format based on POSIX.1-2008 strtol
		// http://pubs.opengroup.org/onlinepubs/9699919799/functions/strtol.html
		template <typename IntType>
		inline bool safe_int_internal(StringView text, IntType* value_p, int base)
		{
			*value_p = 0;
			bool negative;
			if (!safe_parse_sign_and_base(&text, &base, &negative)) {
				return false;
			}
			if (!negative) {
				return safe_parse_positive_int(text, base, value_p);
			}
			else {
				return safe_parse_negative_int(text, base, value_p);
			}
		}

		template <typename IntType>
		inline bool safe_uint_internal(StringView text, IntType* value_p, int base)
		{
			*value_p = 0;
			bool negative;
			if (!safe_parse_sign_and_base(&text, &base, &negative) || negative) {
				return false;
			}
			return safe_parse_positive_int(text, base, value_p);
		}
	}

	template <>
	int8 ParseInt<int8>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<int8>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<int8>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	uint8 ParseInt<uint8>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<uint8>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<uint8>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	int16 ParseInt<int16>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<int16>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<int16>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	uint16 ParseInt<uint16>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<uint16>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<uint16>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	int32 ParseInt<int32>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<int32>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<int32>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	uint32 ParseInt<uint32>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<uint32>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<uint32>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	long ParseInt<long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	unsigned long ParseInt<unsigned long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<unsigned long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<unsigned long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	long long ParseInt<long long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<long long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<long long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	unsigned long long ParseInt<unsigned long long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<unsigned long long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<unsigned long long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	Optional<int8> ParseIntOpt<int8>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		int32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (!InRange<int32>(result, INT8_MIN, INT8_MAX))
		{
			return none;
		}

		return static_cast<int8>(result);
	}

	template <>
	Optional<uint8> ParseIntOpt<uint8>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		uint32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (UINT8_MAX < result)
		{
			return none;
		}

		return static_cast<uint8>(result);
	}

	template <>
	Optional<int16> ParseIntOpt<int16>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		int32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (!InRange<int32>(result, INT16_MIN, INT16_MAX))
		{
			return none;
		}

		return static_cast<int16>(result);
	}

	template <>
	Optional<uint16> ParseIntOpt<uint16>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		uint32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (UINT16_MAX < result)
		{
			return none;
		}

		return static_cast<uint16>(result);
	}

	template <>
	Optional<int32> ParseIntOpt<int32>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		int32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<uint32> ParseIntOpt<uint32>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		uint32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<long> ParseIntOpt<long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<unsigned long> ParseIntOpt<unsigned long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		unsigned long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<long long> ParseIntOpt<long long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		long long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<unsigned long long> ParseIntOpt<unsigned long long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		unsigned long long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}
}
