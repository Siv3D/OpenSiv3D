//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/IntFormatter.hpp>

namespace s3d
{
	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////////
		//
		//	Copyright (c) 2012 - present, Victor Zverovich
		//
		//	Permission is hereby granted, free of charge, to any person obtaining
		//	a copy of this software and associated documentation files (the
		//	"Software"), to deal in the Software without restriction, including
		//	without limitation the rights to use, copy, modify, merge, publish,
		//	distribute, sublicense, and/or sell copies of the Software, and to
		//	permit persons to whom the Software is furnished to do so, subject to
		//	the following conditions:
		//
		//	The above copyright notice and this permission notice shall be
		//	included in all copies or substantial portions of the Software.
		//
		//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
		//	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
		//	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
		//	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
		//	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
		//	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
		//	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
		//
		//	--- Optional exception to the license ---
		//
		//	As an exception, if, as a result of your compiling your source code, portions
		//	of this Software are embedded into a machine-executable object form of such
		//	source code, you may redistribute such embedded portions in such object form
		//	without including the above copyright and permission notices.

		static constexpr char DIGITS[] =
			"0001020304050607080910111213141516171819"
			"2021222324252627282930313233343536373839"
			"4041424344454647484950515253545556575859"
			"6061626364656667686970717273747576777879"
			"8081828384858687888990919293949596979899";

		IntFormatter::IntFormatter(const int32 value) noexcept
		{
			format_signed(value);
		}

		IntFormatter::IntFormatter(const int64 value) noexcept
		{
			format_signed(value);
		}

		IntFormatter::IntFormatter(const uint32 value) noexcept
			: str_{ format_decimal(value) }
		{

		}

		IntFormatter::IntFormatter(const uint64 value) noexcept
			: str_{ format_decimal(value) }
		{

		}

		char32* IntFormatter::format_decimal(uint64 value) noexcept
		{
			char32* buffer_end = buffer_ + BUFFER_SIZE - 1;

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

		void IntFormatter::format_signed(int64 value) noexcept
		{
			uint64 abs_value = static_cast<uint64>(value);
			bool negative = value < 0;
			if (negative)
				abs_value = 0 - abs_value;
			str_ = format_decimal(abs_value);
			if (negative)
				*--str_ = '-';
		}
		//
		//////////////////////////////////////////////////////////////////////////////
	}
}

