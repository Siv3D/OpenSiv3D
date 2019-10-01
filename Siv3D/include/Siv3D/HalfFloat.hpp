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
# include "Format.hpp"

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
		//	Copyright(c) 2011 - 2019 Microsoft Corp
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

			uint32 iValue = reinterpret_cast<const uint32*>(&value)[0];
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

			return reinterpret_cast<float*>(&result)[0];
		}
		//
		//
		///////////////////////////////////////////////////////////////
	}

	/// <summary>
	/// 半精度浮動小数点数
	/// </summary>
	struct HalfFloat
	{
	private:

		uint16 m_bits;

	public:

		HalfFloat() = default;

		HalfFloat(float value) noexcept
			: m_bits(detail::FloatToHalf(value)) {}

		[[nodiscard]] operator float() const noexcept
		{
			return detail::HalfToFloat(m_bits);
		}

		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		HalfFloat(Type value)
			: HalfFloat(static_cast<float>(value)) {}

		HalfFloat& operator= (float value) noexcept
		{
			return (*this = HalfFloat(value));
		}

		template <class Type>
		HalfFloat& operator= (Type value)
		{
			return (*this = HalfFloat(value));
		}

		[[nodiscard]] bool operator ==(const HalfFloat other) const noexcept
		{
			if ((m_bits << 1u) == 0 && (other.m_bits << 1u) == 0)
			{
				return true;
			}

			return m_bits == other.m_bits && !isNaN();
		}

		[[nodiscard]] bool operator !=(const HalfFloat other) const noexcept
		{
			return !(operator ==(other));
		}

		[[nodiscard]] uint16 getBits() const noexcept
		{
			return m_bits;
		}

		void setBits(const uint16 bits) noexcept
		{
			m_bits = bits;
		}

		[[nodiscard]] bool isNaN() const noexcept
		{
			return (m_bits & 0x7FFFU) == 0x7FFFU;
		}

		[[nodiscard]] bool isInfinity() const noexcept
		{
			return (m_bits & 0x7FFFU) == 0x7C00U;
		}

		[[nodiscard]] int32 getSign() const noexcept
		{
			return (m_bits & 0x8000U) ? -1 : 1;
		}
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const HalfFloat& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& ouput, const HalfFloat& value)
	{
		return ouput << static_cast<float>(value);
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, HalfFloat& value)
	{
		float t;

		if (input >> t)
		{
			value = t;
		}

		return input;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::HalfFloat>
	{
		[[nodiscard]] size_t operator()(const s3d::HalfFloat& value) const noexcept
		{
			return hash<s3d::uint16>()(value.getBits());
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt_s3d
{
	template <>
	struct formatter<s3d::HalfFloat, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::HalfFloat value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"{:", tag, U"}"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), static_cast<float>(value));
		}
	};
}
