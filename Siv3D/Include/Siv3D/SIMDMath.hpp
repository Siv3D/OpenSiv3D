//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

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
		//	Copyright(c) 2017 Microsoft Corp
		//
		//	Permission is hereby granted, free of charge, to any person obtaining a copy of this
		//	software and associated documentation files(the "Software"), to deal in the Software
		//	without restriction, including without limitation the rights to use, copy, modify,
		//	merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
		//	permit persons to whom the Software is furnished to do so, subject to the following
		//	conditions :
		//
		//	The above copyright notice and this permission notice shall be included in all copies
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
			uint32 Result;

			uint32 IValue = reinterpret_cast<const uint32*>(&value)[0];
			uint32 Sign = (IValue & 0x80000000U) >> 16U;
			IValue = IValue & 0x7FFFFFFFU;      // Hack off the sign

			if (IValue > 0x477FE000U)
			{
				// The number is too large to be represented as a half.  Saturate to infinity.
				if (((IValue & 0x7F800000) == 0x7F800000) && ((IValue & 0x7FFFFF) != 0))
				{
					Result = 0x7FFF; // NAN
				}
				else
				{
					Result = 0x7C00U; // INF
				}
			}
			else
			{
				if (IValue < 0x38800000U)
				{
					// The number is too small to be represented as a normalized half.
					// Convert it to a denormalized value.
					uint32_t Shift = 113U - (IValue >> 23U);
					IValue = (0x800000U | (IValue & 0x7FFFFFU)) >> Shift;
				}
				else
				{
					// Rebias the exponent to represent the value as a normalized half.
					IValue += 0xC8000000U;
				}

				Result = ((IValue + 0x0FFFU + ((IValue >> 13U) & 1U)) >> 13U) & 0x7FFFU;
			}

			return static_cast<uint16>(Result | Sign);
		}

		inline float HalfToFloat(const uint16 value) noexcept
		{
			uint32 Mantissa = (uint32)(value & 0x03FF);

			uint32 Exponent = (value & 0x7C00);
			if (Exponent == 0x7C00) // INF/NAN
			{
				Exponent = (uint32)0x8f;
			}
			else if (Exponent != 0)  // The value is normalized
			{
				Exponent = (uint32)((value >> 10) & 0x1F);
			}
			else if (Mantissa != 0)     // The value is denormalized
			{
				// Normalize the value in the resulting float
				Exponent = 1;

				do
				{
					Exponent--;
					Mantissa <<= 1;
				} while ((Mantissa & 0x0400) == 0);

				Mantissa &= 0x03FF;
			}
			else                        // The value is zero
			{
				Exponent = (uint32)-112;
			}

			uint32 Result = ((value & 0x8000) << 16) | // Sign
				((Exponent + 112) << 23) | // Exponent
				(Mantissa << 13);          // Mantissa

			return reinterpret_cast<float*>(&Result)[0];
		}
		//
		//
		///////////////////////////////////////////////////////////////
	}
}
