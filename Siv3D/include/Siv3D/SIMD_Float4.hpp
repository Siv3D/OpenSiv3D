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
# include <xmmintrin.h>
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "SIMDMath.hpp"

namespace s3d
{
	struct alignas(16) SIMD_Float4
	{
		__m128 vec;

		SIMD_Float4() = default;

		SIMD_Float4(const SIMD_Float4&) = default;
		
		SIMD_Float4& operator=(const SIMD_Float4&) = default;

		SIMD_Float4(SIMD_Float4&&) = default;
		
		SIMD_Float4& operator=(SIMD_Float4&&) = default;

		explicit SIMD_Float4(float _xyzw) noexcept
			: vec(SIMD::SetAll(_xyzw)) {}

		SIMD_Float4(float _x, float _y, float _z, float _w) noexcept
			: vec(SIMD::Set(_x, _y, _z, _w)) {}

		template <class X, class Y, class Z, class W>
		SIMD_Float4(X _x, Y _y, Z _z, W _w) noexcept
			: SIMD_Float4(static_cast<float>(_x), static_cast<float>(_y), static_cast<float>(_z), static_cast<float>(_w)) {}

		template <class U, class V>
		SIMD_Float4(const Vector2D<U>& xy, const Vector2D<V>& zw) noexcept
			: SIMD_Float4(static_cast<float>(xy.x), static_cast<float>(xy.y), static_cast<float>(zw.x), static_cast<float>(zw.y)) {}

		template <class U, class W>
		SIMD_Float4(const Vector3D<U>& xyz, W w) noexcept
			: SIMD_Float4(static_cast<float>(xyz.x), static_cast<float>(xyz.y), static_cast<float>(xyz.z), static_cast<float>(w)) {}

		template <class U>
		SIMD_Float4(const Vector4D<U>& v) noexcept
			: SIMD_Float4(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z), static_cast<float>(v.w)) {}

		constexpr SIMD_Float4(__m128 _vec) noexcept
			: vec(_vec) {}

		[[nodiscard]] constexpr SIV3D_VECTOR_CALL operator __m128() const noexcept
		{
			return vec;
		}

		[[nodiscard]] Float4 SIV3D_VECTOR_CALL toFloat4() const noexcept
		{
			Float4 result;

			SIMD::StoreFloat4(&result, vec);

			return result;
		}

		[[nodiscard]] float elem(size_t index) const noexcept
		{
			return SIMD::GetByIndex(vec, index);
		}

		[[nodiscard]] float getX() const noexcept
		{
			return SIMD::GetX(vec);
		}

		[[nodiscard]] float getY() const noexcept
		{
			return SIMD::GetY(vec);
		}

		[[nodiscard]] float getZ() const noexcept
		{
			return SIMD::GetZ(vec);
		}

		[[nodiscard]] float getW() const noexcept
		{
			return SIMD::GetW(vec);
		}

		void SIV3D_VECTOR_CALL setX(float x) noexcept
		{
			vec = SIMD::SetX(vec, x);
		}

		void SIV3D_VECTOR_CALL setY(float y) noexcept
		{
			vec = SIMD::SetY(vec, y);
		}

		void SIV3D_VECTOR_CALL setZ(float z) noexcept
		{
			vec = SIMD::SetZ(vec, z);
		}

		void SIV3D_VECTOR_CALL setW(float w) noexcept
		{
			vec = SIMD::SetW(vec, w);
		}

		[[nodiscard]] constexpr SIMD_Float4 SIV3D_VECTOR_CALL operator +() const noexcept
		{
			return vec;
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator -() const noexcept
		{
			return SIMD::Negate(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator +(SIMD_Float4 v) const noexcept
		{
			return SIMD::Add(vec, v.vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator -(SIMD_Float4 v) const noexcept
		{
			return SIMD::Subtract(vec, v.vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator *(float s) const noexcept
		{
			return SIMD::Multiply(vec, s);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator *(SIMD_Float4 v) const noexcept
		{
			return SIMD::Multiply(vec, v.vec);
		}
		
		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator /(float s) const noexcept
		{
			return SIMD::Divide(vec, s);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator /(SIMD_Float4 v) const noexcept
		{
			return SIMD::Divide(vec, v.vec);
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator +=(SIMD_Float4 v) noexcept
		{
			vec = SIMD::Add(vec, v.vec);
			
			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator -=(SIMD_Float4 v) noexcept
		{
			vec = SIMD::Subtract(vec, v.vec);
			
			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator *=(float s) noexcept
		{
			vec = SIMD::Multiply(vec, s);
			
			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator *=(SIMD_Float4 v) noexcept
		{
			vec = SIMD::Multiply(vec, v.vec);

			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator /=(float s) noexcept
		{
			vec = SIMD::Divide(vec, s);

			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator /=(SIMD_Float4 v) noexcept
		{
			vec = SIMD::Divide(vec, v.vec);

			return *this;
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL fastReciprocal() const noexcept
		{
			return SIMD::FastReciprocal(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL reciprocal() const noexcept
		{
			return SIMD::Reciprocal(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL sqrt() const noexcept
		{
			return SIMD::Sqrt(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL fastRsqrt() const noexcept
		{
			return SIMD::FastRsqrt(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL rsqrt() const noexcept
		{
			return SIMD::Rsqrt(vec);
		}

		[[nodiscard]] Float2 xy() const noexcept
		{
			SIMD::Float4A fv;

			fv.vec = vec;
			
			return{ fv.f[0],  fv.f[1] };
		}

		[[nodiscard]] Float3 xyz() const noexcept
		{
			SIMD::Float4A fv;

			fv.vec = vec;
			
			return{ fv.f[0], fv.f[1], fv.f[2] };
		}

		[[nodiscard]] static SIMD_Float4 SIV3D_VECTOR_CALL Zero() noexcept
		{
			return SIMD::Zero();
		}

		[[nodiscard]] static SIMD_Float4 SIV3D_VECTOR_CALL One() noexcept
		{
			return SIMD::One();
		}

		[[nodiscard]] static SIMD_Float4 SIV3D_VECTOR_CALL All(float value = 1.0f) noexcept
		{
			return SIMD::SetAll(value);
		}
	};

	[[nodiscard]] inline SIMD_Float4 SIV3D_VECTOR_CALL operator *(float s, SIMD_Float4 v) noexcept
	{
		return SIMD::Multiply(v.vec, s);
	}
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const SIMD_Float4& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const SIMD_Float4& value)
	{
		SIMD::Float4A fv;

		fv.vec = value;

		return output << CharType('(')
			<< fv.f[0] << CharType(',') << CharType(' ')
			<< fv.f[1] << CharType(',') << CharType(' ')
			<< fv.f[2] << CharType(',') << CharType(' ')
			<< fv.f[3] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, SIMD_Float4& value)
	{
		SIMD::Float4A fv;

		CharType unused;
		input >> unused
			>> fv.f[0] >> unused
			>> fv.f[1] >> unused
			>> fv.f[2] >> unused
			>> fv.f[3] >> unused;

		value.vec = fv.vec;

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
	struct hash<s3d::SIMD_Float4>
	{
		[[nodiscard]] size_t operator()(const s3d::SIMD_Float4& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
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
	struct formatter<s3d::SIMD_Float4, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::SIMD_Float4& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			const s3d::Float4 v = value.toFloat4();

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), v.x, v.y, v.z, v.w);
		}
	};
}
