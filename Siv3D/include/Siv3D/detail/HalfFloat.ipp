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

# pragma once

namespace s3d
{
	namespace detail
	{
		///////////////////////////////////////////////////////////////
		//
		//

		//
		//	DirectXMath
		//
		//	The MIT License(MIT)
		//
		//	Copyright(c) 2011 - 2020 Microsoft Corp
		//
		//	Permission is hereby granted, free of charge, to any person obtaining a copy of this
		//	softwareand associated documentation files(the "Software"), to deal in the Software
		//	without restriction, including without limitation the rights to use, copy, modify,
		//	merge, publish, distribute, sublicense, and /or sell copies of the Software, and to
		//	permit persons to whom the Software is furnished to do so, subject to the following
		//	conditions :
		//
		//	The above copyright noticeand this permission notice shall be included in all copies
		//	or substantial portions of the Software.
		//
		//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
		//	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
		//	PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
		//	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
		//	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
		//	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

		inline uint16 FloatToHalf(const float value) noexcept
		{
			uint32 result;

		# if __cpp_lib_bit_cast
			uint32 iValue = std::bit_cast<uint32>(value);
		# else
			uint32 iValue = reinterpret_cast<const uint32*>(&value)[0];
		# endif

			uint32 sign = (iValue & 0x80000000U) >> 16U;
			iValue = iValue & 0x7FFFFFFFU;      // Hack off the sign

			if (iValue > 0x477FE000U)
			{
				// The number is too large to be represented as a half.  Saturate to infinity.
				if (((iValue & 0x7F800000) == 0x7F800000) && ((iValue & 0x7FFFFF) != 0))
				{
					result = 0x7FFF; // NAN
				}
				else
				{
					result = 0x7C00U; // INF
				}
			}
			else if (!iValue)
			{
				result = 0;
			}
			else
			{
				if (iValue < 0x38800000U)
				{
					// The number is too small to be represented as a normalized half.
					// Convert it to a denormalized value.
					uint32_t Shift = 113U - (iValue >> 23U);
					iValue = (0x800000U | (iValue & 0x7FFFFFU)) >> Shift;
				}
				else
				{
					// Rebias the exponent to represent the value as a normalized half.
					iValue += 0xC8000000U;
				}

				result = ((iValue + 0x0FFFU + ((iValue >> 13U) & 1U)) >> 13U) & 0x7FFFU;
			}
			return static_cast<uint16>(result | sign);
		}

		inline float HalfToFloat(const uint16 value) noexcept
		{
			uint32 mantissa = static_cast<uint32>(value & 0x03FF);

			uint32 exponent = (value & 0x7C00);
			if (exponent == 0x7C00) // INF/NAN
			{
				exponent = 0x8f;
			}
			else if (exponent != 0)  // The value is normalized
			{
				exponent = static_cast<uint32>((static_cast<int32>(value) >> 10) & 0x1F);
			}
			else if (mantissa != 0)     // The value is denormalized
			{
				// Normalize the value in the resulting float
				exponent = 1;

				do
				{
					exponent--;
					mantissa <<= 1;
				} while ((mantissa & 0x0400) == 0);

				mantissa &= 0x03FF;
			}
			else                        // The value is zero
			{
				exponent = static_cast<uint32>(-112);
			}

			uint32 result =
				((static_cast<uint32>(value) & 0x8000) << 16) // Sign
				| ((exponent + 112) << 23)                      // Exponent
				| (mantissa << 13);                             // Mantissa

		# if __cpp_lib_bit_cast
			return std::bit_cast<float>(result);
		# else
			return reinterpret_cast<float*>(&result)[0];
		# endif
		}
		//
		//
		///////////////////////////////////////////////////////////////
	}

	inline HalfFloat::HalfFloat(const float value) noexcept
		: m_bits(detail::FloatToHalf(value)) {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline HalfFloat::HalfFloat(const Arithmetic value) noexcept
		: HalfFloat(static_cast<float>(value)) {}

	inline HalfFloat& HalfFloat::operator =(const float value) noexcept
	{
		return (*this = HalfFloat(value));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline HalfFloat& HalfFloat::operator =(const Arithmetic value)
	{
		return (*this = HalfFloat(value));
	}

	inline HalfFloat::operator float() const noexcept
	{
		return detail::HalfToFloat(m_bits);
	}

	inline bool HalfFloat::operator ==(const HalfFloat other) const noexcept
	{
		if (((m_bits << 1u) == 0)
			&& ((other.m_bits << 1u) == 0))
		{
			return true;
		}

		return ((m_bits == other.m_bits) && (not isNaN()));
	}

	inline bool HalfFloat::operator !=(const HalfFloat other) const noexcept
	{
		return !(operator ==(other));
	}

	inline uint16 HalfFloat::getBits() const noexcept
	{
		return m_bits;
	}

	inline void HalfFloat::setBits(const uint16 bits) noexcept
	{
		m_bits = bits;
	}

	inline bool HalfFloat::isNaN() const noexcept
	{
		return ((m_bits & 0x7FFFU) == 0x7FFFU);
	}

	inline bool HalfFloat::isInfinity() const noexcept
	{
		return ((m_bits & 0x7FFFU) == 0x7C00U);
	}

	inline int32 HalfFloat::getSign() const noexcept
	{
		return ((m_bits & 0x8000U) ? -1 : 1);
	}
}
