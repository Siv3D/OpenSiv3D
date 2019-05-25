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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatInt.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr char DIGITS[] =
			"0001020304050607080910111213141516171819"
			"2021222324252627282930313233343536373839"
			"4041424344454647484950515253545556575859"
			"6061626364656667686970717273747576777879"
			"8081828384858687888990919293949596979899";

		IntFormatter::IntFormatter(const std::int32_t value)
		{
			formatSigned(value);
		}

		IntFormatter::IntFormatter(const std::int64_t value)
		{
			formatSigned(value);
		}

		IntFormatter::IntFormatter(const std::uint32_t value)
			: str_(format_decimal(value))
		{
		
		}

		IntFormatter::IntFormatter(const std::uint64_t value)
			: str_(format_decimal(value))
		{
		
		}

		std::size_t IntFormatter::size() const noexcept
		{
			return buffer_ - str_ + BUFFER_SIZE - 1;
		}

		const char32* IntFormatter::data() const noexcept
		{
			return str_;
		}

		const char32* IntFormatter::c_str() const noexcept
		{
			buffer_[BUFFER_SIZE - 1] = '\0';
			return str_;
		}

		String IntFormatter::str() const
		{
			return String(str_, size());
		}

		char32* IntFormatter::format_decimal(std::uint64_t value)
		{
			char32 *buffer_end = buffer_ + BUFFER_SIZE - 1;

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

		void IntFormatter::formatSigned(std::int64_t value)
		{
			std::uint64_t abs_value = static_cast<std::uint64_t>(value);
			bool negative = value < 0;
			if (negative)
				abs_value = 0 - abs_value;
			str_ = format_decimal(abs_value);
			if (negative)
				*--str_ = '-';
		}


		template <class UnsignedInteger>
		[[nodiscard]] inline String ItoW(const UnsignedInteger value, const unsigned radix, const bool isNegative, const LetterCase letterCase)
		{
			if (radix < 2 || 36 < radix)
			{
				return String();
			}

			char32 buffer[std::numeric_limits<UnsignedInteger>::digits];
			char32* p = buffer;
			size_t length = 0;
			UnsignedInteger remaining = value;

			if (isNegative)
			{
				*p++ = '-';
				++length;
				remaining = static_cast<UnsignedInteger>(-static_cast<typename std::make_signed<UnsignedInteger>::type>(remaining));
			}

			char32* first_digit = p;
			const char32 a = (letterCase == LetterCase::Upper) ? U'A' : U'a';

			do
			{
				const UnsignedInteger digit = static_cast<UnsignedInteger>(remaining % static_cast<UnsignedInteger>(radix));
				remaining /= static_cast<UnsignedInteger>(radix);
				*p++ = static_cast<char32>(digit < 10 ? (U'0' + digit) : (a + digit - 10));
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

	String ToString(const int8 value)
	{
		return detail::IntFormatter(static_cast<int32>(value)).str();
	}

	String ToString(const uint8 value)
	{
		return detail::IntFormatter(static_cast<uint32>(value)).str();
	}

	String ToString(const int16 value)
	{
		return detail::IntFormatter(static_cast<int32>(value)).str();
	}

	String ToString(const uint16 value)
	{
		return detail::IntFormatter(static_cast<uint32>(value)).str();
	}

	String ToString(const int32 value)
	{
		return detail::IntFormatter(value).str();
	}

	String ToString(const uint32 value)
	{
		return detail::IntFormatter(value).str();
	}

	String ToString(const long value)
	{
		return detail::IntFormatter(static_cast<int64>(value)).str();
	}

	String ToString(const unsigned long value)
	{
		return detail::IntFormatter(static_cast<uint64>(value)).str();
	}

	String ToString(const long long value)
	{
		return detail::IntFormatter(static_cast<int64>(value)).str();
	}

	String ToString(const unsigned long long value)
	{
		return detail::IntFormatter(static_cast<uint64>(value)).str();
	}

	String ToString(const char value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW<uint8>(static_cast<uint8>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const int8 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW<uint8>(static_cast<uint8>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const uint8 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW<uint8>(value, radix.value(), false, letterCase);
	}

	String ToString(const int16 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint16>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const uint16 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}

	String ToString(const int32 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint32>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const uint32 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}

	String ToString(const long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint32>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const unsigned long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}

	String ToString(const long long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint64>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const unsigned long long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}



	String ToBinary(const char value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const int8 value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const uint8 value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const int16 value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const uint16 value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const int32 value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const uint32 value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const long value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const unsigned long value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const long long value)
	{
		return ToString(value, Arg::radix = 2);
	}

	String ToBinary(const unsigned long long value)
	{
		return ToString(value, Arg::radix = 2);
	}


	String ToOctal(const char value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const int8 value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const uint8 value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const int16 value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const uint16 value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const int32 value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const uint32 value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const long value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const unsigned long value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const long long value)
	{
		return ToString(value, Arg::radix = 8);
	}

	String ToOctal(const unsigned long long value)
	{
		return ToString(value, Arg::radix = 8);
	}


	String ToHex(const char value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const int8 value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const uint8 value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const int16 value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const uint16 value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const int32 value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const uint32 value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const long value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const unsigned long value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const long long value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}

	String ToHex(const unsigned long long value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}
}
