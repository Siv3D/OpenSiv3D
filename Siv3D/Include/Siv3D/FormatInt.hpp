//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cstdint>
# include <limits>
# include "String.hpp"
# include "Radix.hpp"

namespace s3d
{
	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////////
		//
		//	Formatting library for C++
		//	Copyright (c) 2012 - 2015, Victor Zverovich
		//	All rights reserved.
		//	Redistribution and use in source and binary forms, with or without
		//	modification, are permitted provided that the following conditions are met:
		//	1. Redistributions of source code must retain the above copyright notice, this
		//	  list of conditions and the following disclaimer.
		//	2. Redistributions in binary form must reproduce the above copyright notice,
		//	  this list of conditions and the following disclaimer in the documentation
		//	  and/or other materials provided with the distribution.
		//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
		//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
		//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
		//	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
		//	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
		//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
		//	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
		//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
		//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
		//

		class FormatInt
		{
		private:

			static const char DIGITS[];

			enum { BUFFER_SIZE = std::numeric_limits<std::uint64_t>::digits10 + 3 };

			mutable wchar_t buffer_[BUFFER_SIZE];

			wchar_t* str_;

			wchar_t* format_decimal(std::uint64_t value)
			{
				wchar_t *buffer_end = buffer_ + BUFFER_SIZE - 1;

				while (value >= 100)
				{
					unsigned index = (value % 100) * 2;
					value /= 100;
					*--buffer_end = DIGITS[index + 1];
					*--buffer_end = DIGITS[index];
				}

				if (value < 10)
				{
					*--buffer_end = static_cast<char>('0' + value);
					return buffer_end;
				}

				unsigned index = static_cast<unsigned>(value * 2);
				*--buffer_end = DIGITS[index + 1];
				*--buffer_end = DIGITS[index];
				return buffer_end;
			}

			void formatSigned(std::int64_t value)
			{
				std::uint64_t abs_value = static_cast<std::uint64_t>(value);
				bool negative = value < 0;
				if (negative)
					abs_value = 0 - abs_value;
				str_ = format_decimal(abs_value);
				if (negative)
					*--str_ = '-';
			}

		public:

			explicit FormatInt(const std::int32_t value) { formatSigned(value); }

			explicit FormatInt(const std::int64_t value) { formatSigned(value); }

			explicit FormatInt(const std::uint32_t value) : str_(format_decimal(value)) {}

			explicit FormatInt(const std::uint64_t value) : str_(format_decimal(value)) {}

			std::size_t size() const { return buffer_ - str_ + BUFFER_SIZE - 1; }

			const wchar_t *data() const { return str_; }

			const wchar_t *c_str() const
			{
				buffer_[BUFFER_SIZE - 1] = '\0';
				return str_;
			}

			String str() const { return String(str_, size()); }
		};

		//
		//////////////////////////////////////////////////////////////////////////////

		template <class UnsignedInteger>
		inline String ItoW(const UnsignedInteger value, const unsigned radix, const bool isNegative, const bool upperCase)
		{
			if (radix < 2 || 36 < radix)
			{
				return String();
			}

			wchar_t buffer[std::numeric_limits<UnsignedInteger>::digits];
			wchar_t* p = buffer;
			size_t length = 0;
			UnsignedInteger remaining = value;

			if (isNegative)
			{
				*p++ = '-';
				++length;
				remaining = static_cast<UnsignedInteger>(-static_cast<typename std::make_signed<UnsignedInteger>::type>(remaining));
			}

			wchar_t* first_digit = p;
			const wchar_t a = upperCase ? L'A' : L'a';

			do
			{
				const UnsignedInteger digit = static_cast<UnsignedInteger>(remaining % static_cast<UnsignedInteger>(radix));
				remaining /= static_cast<UnsignedInteger>(radix);
				*p++ = static_cast<wchar_t>(digit < 10 ? (L'0' + digit) : (a + digit - 10));
				++length;
			} while (remaining > 0);

			--p;

			do
			{
				std::swap(*p, *first_digit);
				--p;
				++first_digit;
			} while (first_digit < p);

			return String(buffer, length);
		}
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const int8 value)
	{
		return detail::FormatInt(static_cast<int32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const uint8 value)
	{
		return detail::FormatInt(static_cast<uint32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const int16 value)
	{
		return detail::FormatInt(static_cast<int32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const uint16 value)
	{
		return detail::FormatInt(static_cast<uint32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const int32 value)
	{
		return detail::FormatInt(value).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const uint32 value)
	{
		return detail::FormatInt(value).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const int64 value)
	{
		return detail::FormatInt(value).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	inline String ToString(const uint64 value)
	{
		return detail::FormatInt(value).str();
	}

	inline String ToString(const char value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(static_cast<int8>(value), radix.value(), (radix.is10() && value < 0), upperCase);
	}

	inline String ToString(const int8 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(static_cast<uint8>(value), radix.value(), (radix.is10() && value < 0), upperCase);
	}

	inline String ToString(const uint8 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(value, radix.value(), false, upperCase);
	}

	inline String ToString(const int16 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(static_cast<uint16>(value), radix.value(), (radix.is10() && value < 0), upperCase);
	}

	inline String ToString(const uint16 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(value, radix.value(), false, upperCase);
	}

	inline String ToString(const int32 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(static_cast<uint32>(value), radix.value(), (radix.is10() && value < 0), upperCase);
	}

	inline String ToString(const uint32 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(value, radix.value(), false, upperCase);
	}

	inline String ToString(const int64 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(static_cast<uint64>(value), radix.value(), (radix.is10() && value < 0), upperCase);
	}

	inline String ToString(const uint64 value, const Radix& radix, const bool upperCase = false)
	{
		return detail::ItoW(value, radix.value(), false, upperCase);
	}
}
