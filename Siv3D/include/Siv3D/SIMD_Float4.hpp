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
# include <xmmintrin.h>
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	# define SIV3D_PERMUTE_PS(v, c) _mm_shuffle_ps(v, v, c)

	namespace detail
	{
		inline constexpr __m128 cM128_One{ 1.0f, 1.0f, 1.0f, 1.0f };
	}

	struct alignas(16) SIMD_Float4
	{
		__m128 vec;

		SIMD_Float4() = default;

		SIMD_Float4(const SIMD_Float4&) = default;
		
		SIMD_Float4& operator=(const SIMD_Float4&) = default;

		SIMD_Float4(SIMD_Float4&&) = default;
		
		SIMD_Float4& operator=(SIMD_Float4&&) = default;

		explicit SIMD_Float4(float _xyzw) noexcept
			: vec(_mm_set_ps1(_xyzw)) {}

		SIMD_Float4(float _x, float _y, float _z, float _w) noexcept
			: vec(_mm_set_ps(_w, _z, _y, _x)) {}

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

		constexpr SIV3D_VECTOR_CALL operator __m128() const noexcept
		{
			return vec;
		}

		[[nodiscard]] float elem(size_t index) const noexcept
		{
			assert(index < 4);
			
			alignas(16) float values[4];
			_mm_store_ps(values, vec);

			return values[index];
		}

		[[nodiscard]] float getX() const noexcept
		{
			return _mm_cvtss_f32(vec);
		}

		[[nodiscard]] float getY() const noexcept
		{
			const __m128 temp = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(1, 1, 1, 1));
			
			return _mm_cvtss_f32(temp);
		}

		[[nodiscard]] float getZ() const noexcept
		{
			const __m128 temp = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(2, 2, 2, 2));

			return _mm_cvtss_f32(temp);
		}

		[[nodiscard]] float getW() const noexcept
		{
			const __m128 temp = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(3, 3, 3, 3));

			return _mm_cvtss_f32(temp);
		}

		void SIV3D_VECTOR_CALL setX(float x) noexcept
		{
			const __m128 x000 = _mm_set_ss(x);
			
			vec = _mm_move_ss(vec, x000);
		}

		void SIV3D_VECTOR_CALL setY(float y) noexcept
		{
			const __m128 swapped = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(3, 2, 0, 1));

			const __m128 y000 = _mm_set_ss(y);

			vec = _mm_move_ss(swapped, y000);

			vec = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(3, 2, 0, 1));
		}

		void SIV3D_VECTOR_CALL setZ(float z) noexcept
		{
			const __m128 swapped = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(3, 0, 1, 2));

			const __m128 z000 = _mm_set_ss(z);

			vec = _mm_move_ss(swapped, z000);

			vec = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(3, 0, 1, 2));
		}

		void SIV3D_VECTOR_CALL setW(float w) noexcept
		{
			const __m128 swapped = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(0, 2, 1, 3));

			const __m128 w000 = _mm_set_ss(w);

			vec = _mm_move_ss(swapped, w000);

			vec = SIV3D_PERMUTE_PS(vec, _MM_SHUFFLE(0, 2, 1, 3));
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator +() const noexcept
		{
			return vec;
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator -() const noexcept
		{
			const __m128 zeros = _mm_setzero_ps();

			return _mm_sub_ps(zeros, vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator +(SIMD_Float4 v) const noexcept
		{
			return _mm_add_ps(vec, v.vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator -(SIMD_Float4 v) const noexcept
		{
			return _mm_sub_ps(vec, v.vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator *(float s) const noexcept
		{
			const __m128 ss = _mm_set_ps1(s);
			
			return _mm_mul_ps(vec, ss);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator *(SIMD_Float4 v) const noexcept
		{
			return _mm_mul_ps(vec, v.vec);
		}
		
		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator /(float s) const noexcept
		{
			const __m128 ss = _mm_set_ps1(s);

			return _mm_div_ps(vec, ss);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL operator /(SIMD_Float4 v) const noexcept
		{
			return _mm_div_ps(vec, v.vec);
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator +=(SIMD_Float4 v) noexcept
		{
			vec = _mm_add_ps(vec, v.vec);
			
			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator -=(SIMD_Float4 v) noexcept
		{
			vec = _mm_sub_ps(vec, v.vec);
			
			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator *=(float s) noexcept
		{
			const __m128 ss = _mm_set_ps1(s);

			vec = _mm_mul_ps(vec, ss);
			
			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator *=(SIMD_Float4 v) noexcept
		{
			vec = _mm_mul_ps(vec, v.vec);

			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator /=(float s) noexcept
		{
			const __m128 ss = _mm_set_ps1(s);

			vec = _mm_div_ps(vec, ss);

			return *this;
		}

		SIMD_Float4& SIV3D_VECTOR_CALL operator /=(SIMD_Float4 v) noexcept
		{
			vec = _mm_div_ps(vec, v.vec);

			return *this;
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL fastReciprocal() const noexcept
		{
			return _mm_rcp_ps(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL reciprocal() const noexcept
		{
			return _mm_div_ps(detail::cM128_One, vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL sqrt() const noexcept
		{
			return _mm_sqrt_ps(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL fastRsqrt() const noexcept
		{
			return _mm_rsqrt_ps(vec);
		}

		[[nodiscard]] SIMD_Float4 SIV3D_VECTOR_CALL rsqrt() const noexcept
		{
			const __m128 sqrts = _mm_sqrt_ps(vec);

			return _mm_div_ps(detail::cM128_One, sqrts);
		}

		[[nodiscard]] Float2 xy() const noexcept
		{
			alignas(16) float values[4];
			_mm_store_ps(values, vec);
			return{ values[0], values[1] };
		}

		[[nodiscard]] Float3 xyz() const noexcept
		{
			alignas(16) float values[4];
			_mm_store_ps(values, vec);
			return{ values[0], values[1], values[2] };
		}

		[[nodiscard]] static SIMD_Float4 SIV3D_VECTOR_CALL Zero() noexcept
		{
			return _mm_setzero_ps();
		}

		[[nodiscard]] static SIMD_Float4 SIV3D_VECTOR_CALL One() noexcept
		{
			return _mm_set_ps1(1.0f);
		}

		[[nodiscard]] static SIMD_Float4 SIV3D_VECTOR_CALL All(float value = 1.0f) noexcept
		{
			return _mm_set_ps1(value);
		}
	};

	[[nodiscard]] inline SIMD_Float4 SIV3D_VECTOR_CALL operator *(float s, SIMD_Float4 v) noexcept
	{
		const __m128 ss = _mm_set_ps1(s);

		return _mm_mul_ps(v.vec, ss);
	}

	void Formatter(FormatData& formatData, const SIMD_Float4& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const SIMD_Float4& value)
	{
		alignas(16) float values[4];
		_mm_store_ps(values, value.vec);
		return output << CharType('(')
			<< values[0] << CharType(',') << CharType(' ')
			<< values[1] << CharType(',') << CharType(' ')
			<< values[2] << CharType(',') << CharType(' ')
			<< values[3] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, SIMD_Float4& value)
	{
		alignas(16) float values[4];
		CharType unused;
		input >> unused
			>> values[0] >> unused
			>> values[1] >> unused
			>> values[2] >> unused
			>> values[3] >> unused;
		value.vec = _mm_load_ps(values);
		return input;
	}
}
