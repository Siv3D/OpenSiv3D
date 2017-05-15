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

		operator float() const noexcept
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

		bool operator ==(const HalfFloat other) const noexcept
		{
			if ((m_bits << 1u) == 0 && (other.m_bits << 1u) == 0)
			{
				return true;
			}

			return m_bits == other.m_bits && !isNaN();
		}

		bool operator !=(const HalfFloat other) const noexcept
		{
			return !(operator ==(other));
		}

		uint16 getBits() const noexcept
		{
			return m_bits;
		}

		void setBits(const uint16 bits) noexcept
		{
			m_bits = bits;
		}

		bool isNaN() const noexcept
		{
			return (m_bits & 0x7FFFU) == 0x7FFFU;
		}

		bool isInfinity() const noexcept
		{
			return (m_bits & 0x7FFFU) == 0x7C00U;
		}

		int32 getSign() const noexcept
		{
			return (m_bits & 0x8000U) ? -1 : 1;
		}
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting HalfFloat
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const HalfFloat& value)
	{
		return Formatter(formatData, static_cast<float>(value));
	}

	/// <summary>
	/// 出力ストリームに値を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="value">
	/// 値
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const HalfFloat& value)
	{
		return os << static_cast<float>(value);
	}

	/// <summary>
	/// 入力ストリームに値を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="value">
	/// 値
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, HalfFloat& value)
	{
		float t;

		if (is >> t)
		{
			value = t;
		}

		return is;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::HalfFloat& value)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("{") + tag + S3DSTR("}");

		f.writer().write(fmt, static_cast<float>(value));
	}
}
//
//////////////////////////////////////////////////////////////////////////////
