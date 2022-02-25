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
# include "SIMDMath.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct alignas(16) SIMD_Float4
	{
		aligned_float4 vec;

		SIV3D_NODISCARD_CXX20
		SIMD_Float4() = default;

		SIV3D_NODISCARD_CXX20
		SIMD_Float4(const SIMD_Float4&) = default;

		SIV3D_NODISCARD_CXX20
		explicit SIMD_Float4(float xyzw) noexcept;

		SIV3D_NODISCARD_CXX20
		SIMD_Float4(float x, float y, float z, float w) noexcept;

		template <class X, class Y, class Z, class W>
		SIV3D_NODISCARD_CXX20
		SIMD_Float4(X x, Y y, Z z, W w) noexcept;

		template <class U, class V, class Z, class W>
		SIV3D_NODISCARD_CXX20
		SIMD_Float4(const Vector2D<U>& xy, Z z, W w) noexcept;

		template <class U, class V>
		SIV3D_NODISCARD_CXX20
		SIMD_Float4(const Vector2D<U>& xy, const Vector2D<V>& zw) noexcept;

		template <class U, class W>
		SIV3D_NODISCARD_CXX20
		SIMD_Float4(const Vector3D<U>& xyz, W w) noexcept;

		SIV3D_NODISCARD_CXX20
		SIMD_Float4(Float4 v) noexcept;

		SIV3D_NODISCARD_CXX20
		SIMD_Float4(Vec4 v) noexcept;

		SIV3D_NODISCARD_CXX20
		SIMD_Float4(aligned_float4 _vec) noexcept;


		[[nodiscard]]
		friend bool SIV3D_VECTOR_CALL operator ==(const SIMD_Float4& lhs, const SIMD_Float4& rhs) noexcept
		{
			return DirectX::XMVector4Equal(lhs.vec, rhs.vec);
		}

		[[nodiscard]]
		friend bool SIV3D_VECTOR_CALL operator !=(const SIMD_Float4& lhs, const SIMD_Float4& rhs) noexcept
		{
			return DirectX::XMVector4NotEqual(lhs.vec, rhs.vec);
		}


		SIMD_Float4& operator =(const SIMD_Float4&) = default;

		SIMD_Float4& SIV3D_VECTOR_CALL operator =(aligned_float4 other) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL operator =(Float3 other) noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator +() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator -() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator +(SIMD_Float4 v) const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator -(SIMD_Float4 v) const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator *(float s) const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator *(SIMD_Float4 v) const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator /(float s) const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL operator /(SIMD_Float4 v) const noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL operator +=(SIMD_Float4 v) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL operator -=(SIMD_Float4 v) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL operator *=(float s) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL operator *=(SIMD_Float4 v) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL operator /=(float s) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL operator /=(SIMD_Float4 v) noexcept;

		[[nodiscard]]
		friend SIMD_Float4 SIV3D_VECTOR_CALL operator *(float s, SIMD_Float4 v) noexcept
		{
			return (v * s);
		}

		[[nodiscard]]
		SIV3D_VECTOR_CALL operator aligned_float4() const noexcept;

		[[nodiscard]]
		SIV3D_VECTOR_CALL operator Float3() const noexcept;

		[[nodiscard]]
		Float4 SIV3D_VECTOR_CALL toFloat4() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL elem(size_t index) const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getX() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getY() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getZ() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL getW() const noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL setX(float x) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL setY(float y) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL setZ(float z) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL setW(float w) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL set(float x, float y, float z, float w) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL set(Float2 xy, Float2 zw) noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL set(Float3 xyz, float w = 0.0f) noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL isZero() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasNaN() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasInf() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL length() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL lengthSq() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL reciprocal() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL fastReciprocal() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL sqrt() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL fastSqrt() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL rsqrt() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL fastRsqrt() const noexcept;

		SIMD_Float4& SIV3D_VECTOR_CALL normalize() noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL normalized() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL lerp(SIMD_Float4 other, float f) const noexcept;

		[[nodiscard]]
		Float2 SIV3D_VECTOR_CALL xy() const noexcept;

		[[nodiscard]]
		Float3 SIV3D_VECTOR_CALL xyz() const noexcept;

		[[nodiscard]]
		static SIMD_Float4 SIV3D_VECTOR_CALL Zero() noexcept;

		[[nodiscard]]
		static SIMD_Float4 SIV3D_VECTOR_CALL One() noexcept;

		[[nodiscard]]
		static SIMD_Float4 SIV3D_VECTOR_CALL All(float value = 1.0f) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const SIMD_Float4& value)
		{
			return output << value.toFloat4();
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, SIMD_Float4& value)
		{
			Float4 t;
			input >> t;
			value = SIMD_Float4{ t };
			return input;
		}

		friend void Formatter(FormatData& formatData, const SIMD_Float4& value)
		{
			Formatter(formatData, value.vec);
		}
	};
}

# include "detail/SIMD_Float4.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::SIMD_Float4, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::SIMD_Float4& value, FormatContext& ctx)
	{
		const s3d::Float4 v = value.toFloat4();

		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", v.x, v.y, v.z, v.w);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, v.x, v.y, v.z, v.w);
		}
	}
};
