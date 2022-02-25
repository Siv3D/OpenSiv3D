//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "SIMD_Float4.hpp"

namespace s3d
{
	struct Triangle3D
	{
		SIMD_Float4 p0;

		SIMD_Float4 p1;

		SIMD_Float4 p2;


		SIV3D_NODISCARD_CXX20
		Triangle3D() = default;

		SIV3D_NODISCARD_CXX20
		Triangle3D(SIMD_Float4 _p0, SIMD_Float4 _p1, SIMD_Float4 _p2) noexcept;

		SIV3D_NODISCARD_CXX20
		Triangle3D(const Float3& _p0, const Float3& _p1, const Float3& _p2) noexcept;


		[[nodiscard]]
		friend bool SIV3D_VECTOR_CALL operator ==(const Triangle3D& lhs, const Triangle3D& rhs) noexcept
		{
			return (lhs.p0 == rhs.p0)
				&& (lhs.p1 == rhs.p1)
				&& (lhs.p2 == rhs.p2);
		}

		[[nodiscard]]
		friend bool SIV3D_VECTOR_CALL operator !=(const Triangle3D& lhs, const Triangle3D& rhs) noexcept
		{
			return (lhs.p0 != rhs.p0)
				|| (lhs.p1 != rhs.p1)
				|| (lhs.p2 != rhs.p2);
		}


		Triangle3D& SIV3D_VECTOR_CALL set(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float zy2) noexcept;

		Triangle3D& SIV3D_VECTOR_CALL set(const Float3& _p0, const Float3& _p1, const Float3& _p2) noexcept;

		Triangle3D& SIV3D_VECTOR_CALL set(SIMD_Float4 _p0, SIMD_Float4 _p1, SIMD_Float4 _p2) noexcept;

		Triangle3D& SIV3D_VECTOR_CALL set(const Triangle3D& triangle) noexcept;


		[[nodiscard]]
		Triangle3D SIV3D_VECTOR_CALL movedBy(float x, float y, float z) const noexcept;

		[[nodiscard]]
		Triangle3D SIV3D_VECTOR_CALL movedBy(Float3 v) const noexcept;

		Triangle3D& SIV3D_VECTOR_CALL moveBy(float x, float y, float z) noexcept;

		Triangle3D& SIV3D_VECTOR_CALL moveBy(Float3 v) noexcept;


		[[nodiscard]]
		Triangle3D SIV3D_VECTOR_CALL lerp(const Triangle3D& other, double f) const noexcept;


		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Triangle3D& value)
		{
			return output << CharType('(')
				<< value.p0.xyz() << CharType(',') << CharType(' ')
				<< value.p1.xyz() << CharType(',') << CharType(' ')
				<< value.p2.xyz() << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Triangle3D& value)
		{
			Float3 p0, p1, p2;
			CharType unused;
			input >> unused
				>> p0 >> unused
				>> p1 >> unused
				>> p2 >> unused;

			value.p0 = p0;
			value.p1 = p1;
			value.p2 = p2;

			return input;
		}

		friend void Formatter(FormatData& formatData, const Triangle3D& value);
	};
}

# include "detail/Triangle3D.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Triangle3D, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Triangle3D& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {})", value.p0.xyz(), value.p1.xyz(), value.p2.xyz());
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.p0.xyz(), value.p1.xyz(), value.p2.xyz());
		}
	}
};
