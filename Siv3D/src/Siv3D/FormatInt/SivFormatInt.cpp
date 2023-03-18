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

# include <cstring>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/IntFormatter.hpp>

namespace s3d
{
	namespace detail
	{
		void AppendUint32(char32** const p, const uint32 value)
		{
			uint32 val = value;

			char32 buffer[12];
			char32* pos = &buffer[11];
			*pos = U'\0';

			do
			{
				*(--pos) = U'0' + static_cast<char32>(val % 10);

				val = val / 10;

			} while (val != 0);

			const size_t length = &buffer[11] - pos;

			std::memcpy(*p, pos, length * sizeof(char32));

			*p += length;
		}

		void AppendInt32(char32** const p, const int32 value)
		{
			bool negative;
			uint32 val;

			if (value < 0)
			{
				negative = true;
				val = -value;
			}
			else
			{
				negative = false;
				val = value;
			}

			char32 buffer[12];
			char32* pos = &buffer[11];
			*pos = U'\0';

			do
			{
				*(--pos) = U'0' + static_cast<char32>(val % 10);

				val = val / 10;

			} while (val != 0);

			if (negative)
			{
				*(--pos) = U'-';
			}

			const size_t length = &buffer[11] - pos;

			std::memcpy(*p, pos, length * sizeof(char32));

			*p += length;
		}

		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		inline String ItoW(const UnsignedInt value, const unsigned radix, const bool isNegative, const LetterCase letterCase)
		{
			if (radix < 2 || 36 < radix)
			{
				return{};
			}

			char32 buffer[std::numeric_limits<UnsignedInt>::digits];
			char32* p = buffer;
			size_t length = 0;
			UnsignedInt remaining = value;

			if (isNegative)
			{
				*p++ = '-';
				++length;
				remaining = static_cast<UnsignedInt>(-static_cast<std::make_signed_t<UnsignedInt>>(remaining));
			}

			char32* first_digit = p;
			const char32 a = (letterCase == LetterCase::Upper) ? U'A' : U'a';

			do
			{
				const UnsignedInt digit = static_cast<UnsignedInt>(remaining % static_cast<UnsignedInt>(radix));
				remaining /= static_cast<UnsignedInt>(radix);
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
		return detail::IntFormatter{ static_cast<int32>(value) }.str();
	}

	String ToString(const uint8 value)
	{
		return detail::IntFormatter{ static_cast<uint32>(value) }.str();
	}

	String ToString(const int16 value)
	{
		return detail::IntFormatter{ static_cast<int32>(value) }.str();
	}

	String ToString(const uint16 value)
	{
		return detail::IntFormatter{ static_cast<uint32>(value) }.str();
	}

	String ToString(const int32 value)
	{
		return detail::IntFormatter{ value }.str();
	}

	String ToString(const uint32 value)
	{
		return detail::IntFormatter{ value }.str();
	}

	String ToString(const long value)
	{
		if constexpr (sizeof(long) == sizeof(int32))
		{
			return detail::IntFormatter{ static_cast<int32>(value) }.str();
		}
		else
		{
			return detail::IntFormatter{ static_cast<int64>(value) }.str();
		}
	}

	String ToString(const unsigned long value)
	{
		if constexpr (sizeof(unsigned long) == sizeof(uint32))
		{
			return detail::IntFormatter{ static_cast<uint32>(value) }.str();
		}
		else
		{
			return detail::IntFormatter{ static_cast<uint64>(value) }.str();
		}
	}

	String ToString(const long long value)
	{
		return detail::IntFormatter{ static_cast<int64>(value) }.str();
	}

	String ToString(const unsigned long long value)
	{
		return detail::IntFormatter{ static_cast<uint64>(value) }.str();
	}


	String ToString(const char value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint8>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const int8 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint8>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const uint8 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
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
}
