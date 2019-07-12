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
# include "LetterCase.hpp"

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
		class IntFormatter
		{
		private:

			enum { BUFFER_SIZE = std::numeric_limits<std::uint64_t>::digits10 + 3 };

			mutable char32 buffer_[BUFFER_SIZE];

			char32* str_;

			char32* format_decimal(std::uint64_t value);

			void formatSigned(std::int64_t value);

		public:

			explicit IntFormatter(std::int32_t value);

			explicit IntFormatter(std::int64_t value);

			explicit IntFormatter(std::uint32_t value);

			explicit IntFormatter(std::uint64_t value);

			std::size_t size() const noexcept;

			const char32* data() const  noexcept;

			const char32* c_str() const noexcept;

			String str() const;
		};
		//
		//////////////////////////////////////////////////////////////////////////////
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
	[[nodiscard]] String ToString(const int8 value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const uint8 value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const int16 value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const uint16 value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const int32 value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const uint32 value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const long value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const unsigned long value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const long long value);

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	/// 整数
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	[[nodiscard]] String ToString(const unsigned long long value);

	[[nodiscard]] String ToString(const char value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const int8 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const uint8 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const int16 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const uint16 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const int32 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const uint32 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const unsigned long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const long long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToString(const unsigned long long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);



	[[nodiscard]] String ToBinary(const char value);

	[[nodiscard]] String ToBinary(const int8 value);

	[[nodiscard]] String ToBinary(const uint8 value);

	[[nodiscard]] String ToBinary(const int16 value);

	[[nodiscard]] String ToBinary(const uint16 value);

	[[nodiscard]] String ToBinary(const int32 value);

	[[nodiscard]] String ToBinary(const uint32 value);

	[[nodiscard]] String ToBinary(const long value);

	[[nodiscard]] String ToBinary(const unsigned long value);

	[[nodiscard]] String ToBinary(const long long value);

	[[nodiscard]] String ToBinary(const unsigned long long value);


	[[nodiscard]] String ToOctal(const char value);

	[[nodiscard]] String ToOctal(const int8 value);

	[[nodiscard]] String ToOctal(const uint8 value);

	[[nodiscard]] String ToOctal(const int16 value);

	[[nodiscard]] String ToOctal(const uint16 value);

	[[nodiscard]] String ToOctal(const int32 value);

	[[nodiscard]] String ToOctal(const uint32 value);

	[[nodiscard]] String ToOctal(const long value);

	[[nodiscard]] String ToOctal(const unsigned long value);

	[[nodiscard]] String ToOctal(const long long value);

	[[nodiscard]] String ToOctal(const unsigned long long value);


	[[nodiscard]] String ToHex(const char value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const int8 value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const uint8 value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const int16 value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const uint16 value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const int32 value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const uint32 value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const long value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const unsigned long value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const long long value, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]] String ToHex(const unsigned long long value, LetterCase letterCase = LetterCase::Upper);
}
