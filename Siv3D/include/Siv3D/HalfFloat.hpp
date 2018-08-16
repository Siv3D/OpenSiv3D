//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "SIMDMath.hpp"
# include "Format.hpp"

namespace s3d
{
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
	inline void Formatter(FormatData& formatData, const HalfFloat& value)
	{
		return Formatter(formatData, static_cast<float>(value));
	}

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

namespace fmt
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
