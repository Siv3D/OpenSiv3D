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
# include <cassert>
# include <xmmintrin.h>
# include <emmintrin.h>
# include <utility>
# include "Fwd.hpp"
# include "PointVector.hpp"

# define SIV3D_USE_SSE3

# ifdef SIV3D_USE_SSE3
#	include <pmmintrin.h>
# endif

# define SIV3D_PERMUTE_PS(v, c) _mm_shuffle_ps(v, v, c)

#define SIV3D_3UNPACK3INTO4(l1,l2,l3) \
    __m128 V3 = _mm_shuffle_ps(l2,l3,_MM_SHUFFLE(0,0,3,2));\
    __m128 V2 = _mm_shuffle_ps(l2,l1,_MM_SHUFFLE(3,3,1,0));\
    V2 = SIV3D_PERMUTE_PS(V2,_MM_SHUFFLE(1,1,0,2));\
    __m128 V4 = _mm_castsi128_ps( _mm_srli_si128(_mm_castps_si128(L3),32/8) );

#define SIV3D_3PACK4INTO3(v2x) \
    v2x = _mm_shuffle_ps(V2,V3,_MM_SHUFFLE(1,0,2,1));\
    V2 = _mm_shuffle_ps(V2,V1,_MM_SHUFFLE(2,2,0,0));\
    V1 = _mm_shuffle_ps(V1,V2,_MM_SHUFFLE(0,2,1,0));\
    V3 = _mm_shuffle_ps(V3,V4,_MM_SHUFFLE(0,0,2,2));\
    V3 = _mm_shuffle_ps(V3,V4,_MM_SHUFFLE(2,1,2,0));\

#define SIV3D_STREAM_PS(p, a) _mm_stream_ps( p, a )
#define SIV3D_SFENCE() _mm_sfence()

namespace s3d
{
	namespace SIMD
	{
		struct alignas(16) Int4A
		{
			union
			{
				int32 i[4];
				__m128 vec;
			};

			[[nodiscard]] operator __m128() const noexcept
			{
				return vec;
			}
		};

		struct alignas(16) Uint4A
		{
			union
			{
				uint32 u[4];
				__m128 vec;
			};

			[[nodiscard]] operator __m128() const noexcept
			{
				return vec;
			}
		};

		struct alignas(16) Float4A
		{
			union
			{
				float f[4];
				__m128 vec;
			};

			[[nodiscard]] operator __m128() const noexcept
			{
				return vec;
			}
		};

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

		namespace constants
		{
			inline constexpr __m128 m128_One{ 1.0f, 1.0f, 1.0f, 1.0f };

			inline constexpr __m128 m128_MIdentityR0{ 1.0f, 0.0f, 0.0f, 0.0f };
			inline constexpr __m128 m128_MIdentityR1{ 0.0f, 1.0f, 0.0f, 0.0f };
			inline constexpr __m128 m128_MIdentityR2{ 0.0f, 0.0f, 1.0f, 0.0f };
			inline constexpr __m128 m128_MIdentityR3{ 0.0f, 0.0f, 0.0f, 1.0f };

			inline constexpr __m128 m128_NegateX{ -1.0f, 1.0f, 1.0f, 1.0f };
			inline constexpr __m128 m128_NegateY{ 1.0f, -1.0f, 1.0f, 1.0f };
			inline constexpr __m128 m128_NegateZ{ 1.0f, 1.0f, -1.0f, 1.0f };
			inline constexpr __m128 m128_NegateW{ 1.0f, 1.0f, 1.0f, -1.0f };

			inline constexpr Int4A m128_Infinity{ { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } };
			inline constexpr Int4A m128_QNaN{ { 0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000 } };
			inline constexpr Int4A m128_AbsMask{ { 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF } };
			inline constexpr Uint4A m128_Mask3{ { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 } };

			inline constexpr uint32 u_SELECT_0 = 0x00000000;
			inline constexpr uint32 u_SELECT_1 = 0xFFFFFFFF;
			inline constexpr Uint4A m128_Select1110{ { u_SELECT_1, u_SELECT_1, u_SELECT_1, u_SELECT_0 } };

			inline constexpr uint32 SwizzleX = 0;
			inline constexpr uint32 SwizzleY = 1;
			inline constexpr uint32 SwizzleZ = 2;
			inline constexpr uint32 SwizzleW = 3;

			inline constexpr float f_PI = 3.141592654f;
			inline constexpr float f_2PI = 6.283185307f;
			inline constexpr float f_1DIVPI = 0.318309886f;
			inline constexpr float f_1DIV2PI = 0.159154943f;
			inline constexpr float f_PIDIV2 = 1.570796327f;
			inline constexpr float f_PIDIV4 = 0.785398163f;
		}

		[[nodiscard]] inline std::pair<float, float> ScalarSinCos(float Value)
		{
			// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
			float quotient = constants::f_1DIV2PI * Value;
			if (Value >= 0.0f)
			{
				quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
			}
			else
			{
				quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
			}
			float y = Value - constants::f_2PI * quotient;

			// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
			float sign;
			if (y > constants::f_PIDIV2)
			{
				y = constants::f_PI - y;
				sign = -1.0f;
			}
			else if (y < -constants::f_PIDIV2)
			{
				y = -constants::f_PI - y;
				sign = -1.0f;
			}
			else
			{
				sign = +1.0f;
			}

			float y2 = y * y;

			// 11-degree minimax approximation
			const float sin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

			// 10-degree minimax approximation
			float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
			const float cos = sign * p;

			return{ sin, cos };
		}


		//
		// 値の作成
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Zero()
		{
			return _mm_setzero_ps();
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL One()
		{
			return constants::m128_One;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Infinity()
		{
			return constants::m128_Infinity.vec;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QNaN()
		{
			return constants::m128_QNaN.vec;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Set(float x, float y, float z, float w)
		{
			return _mm_set_ps(w, z, y, x);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUint(uint32 x, uint32 y, uint32 z, uint32 w)
		{
			const __m128i temp = _mm_set_epi32(static_cast<int>(w), static_cast<int>(z), static_cast<int>(y), static_cast<int>(x));

			return _mm_castsi128_ps(temp);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetAll(float value)
		{
			return _mm_set_ps1(value);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetAllUint(uint32 value)
		{
			const __m128i temp = _mm_set1_epi32(static_cast<int>(value));

			return _mm_castsi128_ps(temp);
		}


		//
		// 指定した成分を全要素に
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SplatX(__m128 v)
		{
			return SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(0, 0, 0, 0));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SplatY(__m128 v)
		{
			return SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(1, 1, 1, 1));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SplatZ(__m128 v)
		{
			return SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(2, 2, 2, 2));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SplatW(__m128 v)
		{
			return SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 3, 3, 3));
		}


		//
		// 要素の Get (float)
		//

		[[nodiscard]] inline float SIV3D_VECTOR_CALL GetByIndex(__m128 v, size_t index)
		{
			assert(index < 4);

			Float4A fv;

			fv.vec = v;

			return fv.f[index];
		}
		
		[[nodiscard]] inline float SIV3D_VECTOR_CALL GetX(__m128 v)
		{
			return _mm_cvtss_f32(v);
		}
		
		[[nodiscard]] inline float SIV3D_VECTOR_CALL GetY(__m128 v)
		{
			const __m128 yyyy = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(1, 1, 1, 1));

			return _mm_cvtss_f32(yyyy);
		}

		[[nodiscard]] inline float SIV3D_VECTOR_CALL GetZ(__m128 v)
		{
			const __m128 zzzz = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(2, 2, 2, 2));

			return _mm_cvtss_f32(zzzz);
		}
		
		[[nodiscard]] inline float SIV3D_VECTOR_CALL GetW(__m128 v)
		{
			const __m128 wwww = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 3, 3, 3));

			return _mm_cvtss_f32(wwww);
		}


		//
		// 要素の Get (uint32)
		//

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL GetUintByIndex(__m128 v, size_t index)
		{
			assert(index < 4);

			Uint4A uv;

			uv.vec = v;

			return uv.u[index];
		}

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL GetUintX(__m128 v)
		{
			return static_cast<uint32>(_mm_cvtsi128_si32(_mm_castps_si128(v)));
		}

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL GetUintY(__m128 v)
		{
			const __m128i yyyy = _mm_shuffle_epi32(_mm_castps_si128(v), _MM_SHUFFLE(1, 1, 1, 1));

			return static_cast<uint32>(_mm_cvtsi128_si32(yyyy));
		}

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL GetUintZ(__m128 v)
		{
			const __m128i zzzz = _mm_shuffle_epi32(_mm_castps_si128(v), _MM_SHUFFLE(2, 2, 2, 2));

			return static_cast<uint32>(_mm_cvtsi128_si32(zzzz));
		}

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL GetUintW(__m128 v)
		{
			const __m128i wwww = _mm_shuffle_epi32(_mm_castps_si128(v), _MM_SHUFFLE(3, 3, 3, 3));

			return static_cast<uint32>(_mm_cvtsi128_si32(wwww));
		}


		//
		// 要素の Set (float)
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetByIndex(__m128 v, float value, size_t index)
		{
			assert(index < 4);

			Float4A fv;

			fv.vec = v;

			fv.f[index] = value;

			return fv.vec;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetX(__m128 v, float x)
		{
			const __m128 x000 = _mm_set_ss(x);

			return _mm_move_ss(v, x000);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetY(__m128 v, float y)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 2, 0, 1));

			const __m128 y000 = _mm_set_ss(y);

			result = _mm_move_ss(result, y000);

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(3, 2, 0, 1));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetZ(__m128 v, float z)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 0, 1, 2));

			const __m128 z000 = _mm_set_ss(z);

			result = _mm_move_ss(result, z000);

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(3, 0, 1, 2));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetW(__m128 v, float w)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(0, 2, 1, 3));

			const __m128 w000 = _mm_set_ss(w);

			result = _mm_move_ss(result, w000);

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(0, 2, 1, 3));
		}


		//
		// 要素の Set (uint32)
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintByIndex(__m128 v, uint32 value, size_t index)
		{
			assert(index < 4);

			Uint4A uv;

			uv.vec = v;

			uv.u[index] = value;

			return uv.vec;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintX(__m128 v, uint32 x)
		{
			const __m128i x000 = _mm_cvtsi32_si128(static_cast<int>(x));

			return _mm_move_ss(v, _mm_castsi128_ps(x000));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintY(__m128 v, uint32 y)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 2, 0, 1));

			const __m128i y000 = _mm_cvtsi32_si128(static_cast<int>(y));

			result = _mm_move_ss(result, _mm_castsi128_ps(y000));

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(3, 2, 0, 1));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintZ(__m128 v, uint32 z)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 0, 1, 2));

			const __m128i z000 = _mm_cvtsi32_si128(static_cast<int>(z));

			result = _mm_move_ss(result, _mm_castsi128_ps(z000));

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(3, 0, 1, 2));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintW(__m128 v, uint32 w)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(0, 2, 1, 3));

			const __m128i w000 = _mm_cvtsi32_si128(static_cast<int>(w));

			result = _mm_move_ss(result, _mm_castsi128_ps(w000));

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(0, 2, 1, 3));
		}

		//
		// Load
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL LoadFloat3(const Float3* pSource)
		{
			const __m128 x000 = _mm_load_ss(&pSource->x);
			
			const __m128 y000 = _mm_load_ss(&pSource->y);
			
			const __m128 z000 = _mm_load_ss(&pSource->z);
			
			const __m128 xy00 = _mm_unpacklo_ps(x000, y000);
			
			return _mm_movelh_ps(xy00, z000); // xyz0
		}


		//
		// Store
		//

		inline void SIV3D_VECTOR_CALL StoreFloat3(Float3* pDestination, __m128 v)
		{
			const __m128 T1 = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(1, 1, 1, 1));
			
			const __m128 T2 = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(2, 2, 2, 2));
			
			_mm_store_ss(&pDestination->x, v);
			
			_mm_store_ss(&pDestination->y, T1);
			
			_mm_store_ss(&pDestination->z, T2);
		}

		//
		// その他の操作
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Select(__m128 v1, __m128 v2, __m128 control)
		{
			const __m128 t1 = _mm_andnot_ps(control, v1);

			const __m128 t2 = _mm_and_ps(v2, control);

			return _mm_or_ps(t1, t2);
		}

		template <uint32 SwizzleX, uint32 SwizzleY, uint32 SwizzleZ, uint32 SwizzleW>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle(__m128 v)
		{
			static_assert(SwizzleX <= 3 && SwizzleY <= 3 && SwizzleZ <= 3 && SwizzleW <= 3);

			return SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(SwizzleW, SwizzleZ, SwizzleY, SwizzleX));
		}

		template<>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle<0, 1, 0, 1>(__m128 v)
		{
			return v;
		}

		template<>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle<0, 1, 2, 3>(__m128 v)
		{
			return _mm_movelh_ps(v, v);
		}

		template<>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle<2, 3, 2, 3>(__m128 v)
		{
			return _mm_movehl_ps(v, v);
		}

		template<>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle<0, 0, 1, 1>(__m128 v)
		{
			return _mm_unpacklo_ps(v, v);
		}

		template<>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle<2, 2, 3, 3>(__m128 v)
		{
			return _mm_unpackhi_ps(v, v);
		}

	# ifdef SIV3D_USE_SSE3

		template<>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle<0, 0, 2, 2>(__m128 v)
		{
			return _mm_moveldup_ps(v);
		}

		template<>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Swizzle<1, 1, 3, 3>(__m128 v)
		{
			return _mm_movehdup_ps(v);
		}

	# endif

		//
		// 比較
		//

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL IsZero(__m128 v)
		{
			const __m128 zeros = _mm_setzero_ps();

			const __m128 temp = _mm_cmpeq_ps(v, zeros);

			return (_mm_movemask_ps(temp) == 0x0f);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL IsNaN(__m128 v)
		{
			const __m128 temp = _mm_cmpneq_ps(v, v);

			return (_mm_movemask_ps(temp) != 0);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL IsInfinite(__m128 v)
		{
			__m128 temp = _mm_and_ps(v, constants::m128_AbsMask);

			temp = _mm_cmpeq_ps(temp, constants::m128_Infinity);

			return (_mm_movemask_ps(temp) != 0);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Equal(__m128 v1, __m128 v2)
		{
			const __m128 temp = _mm_cmpeq_ps(v1, v2);
			
			return (_mm_movemask_ps(temp) == 0x0f);
		}


		//
		// 計算
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Negate(__m128 v)
		{
			const __m128 zeros = _mm_setzero_ps();

			return _mm_sub_ps(zeros, v);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Add(__m128 v1, __m128 v2)
		{
			return _mm_add_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Subtract(__m128 v1, __m128 v2)
		{
			return _mm_sub_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Multiply(__m128 v, float s)
		{
			const __m128 ssss = _mm_set_ps1(s);

			return _mm_mul_ps(v, ssss);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Multiply(__m128 v1, __m128 v2)
		{
			return _mm_mul_ps(v1, v2);
		}
		
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL MultiplyAdd(__m128 v1, __m128 v2, __m128 v3)
		{
			const __m128 mul = _mm_mul_ps(v1, v2);

			return _mm_add_ps(mul, v3);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL NegativeMultiplySubtract(__m128 v1, __m128 v2, __m128 v3)
		{
			const __m128 mul = _mm_mul_ps(v1, v2);

			return _mm_sub_ps(v3, mul);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Divide(__m128 v, float s)
		{
			const __m128 ssss = _mm_set_ps1(s);

			return _mm_div_ps(v, ssss);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Divide(__m128 v1, __m128 v2)
		{
			return _mm_div_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL FastReciprocal(__m128 v)
		{
			return _mm_rcp_ps(v);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Reciprocal(__m128 v)
		{
			return _mm_div_ps(constants::m128_One, v);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Sqrt(__m128 v)
		{
			return _mm_sqrt_ps(v);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL FastRsqrt(__m128 v)
		{
			return _mm_rsqrt_ps(v);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Rsqrt(__m128 v)
		{
			const __m128 sqrts = _mm_sqrt_ps(v);

			return _mm_div_ps(constants::m128_One, sqrts);
		}

		//
		// 3D-Vector 計算
		//

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector3IsZero(__m128 v)
		{
			const __m128 zeros = _mm_setzero_ps();

			const __m128 temp = _mm_cmpeq_ps(v, zeros);

			return ((_mm_movemask_ps(temp) & 7) == 7);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector3IsNaN(__m128 v)
		{
			const __m128 temp = _mm_cmpneq_ps(v, v);

			return ((_mm_movemask_ps(temp) & 7) != 0);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector3IsInfinite(__m128 v)
		{
			__m128 temp = _mm_and_ps(v, constants::m128_AbsMask);

			temp = _mm_cmpeq_ps(temp, constants::m128_Infinity);

			return ((_mm_movemask_ps(temp) & 7) != 0);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector3Equal(__m128 v1, __m128 v2)
		{
			const __m128 temp = _mm_cmpeq_ps(v1, v2);

			return ((_mm_movemask_ps(temp) & 7) == 7);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector3Dot(__m128 v1, __m128 v2)
		{
		# ifdef SIV3D_USE_SSE3

			__m128 vTemp = _mm_mul_ps(v1, v2);

			vTemp = _mm_and_ps(vTemp, constants::m128_Mask3);

			vTemp = _mm_hadd_ps(vTemp, vTemp);

			return _mm_hadd_ps(vTemp, vTemp);

		# else

			// Perform the dot product
			__m128 vDot = _mm_mul_ps(v1, v2);
			// x=Dot.vector4_f32[1], y=Dot.vector4_f32[2]
			__m128 vTemp = SIV3D_PERMUTE_PS(vDot, _MM_SHUFFLE(2, 1, 2, 1));
			// Result.vector4_f32[0] = x+y
			vDot = _mm_add_ss(vDot, vTemp);
			// x=Dot.vector4_f32[2]
			vTemp = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(1, 1, 1, 1));
			// Result.vector4_f32[0] = (x+y)+z
			vDot = _mm_add_ss(vDot, vTemp);
			// Splat x
			return SIV3D_PERMUTE_PS(vDot, _MM_SHUFFLE(0, 0, 0, 0));

		# endif
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector3Cross(__m128 v1, __m128 v2)
		{
			// y1,z1,x1,w1
			__m128 vTemp1 = SIV3D_PERMUTE_PS(v1, _MM_SHUFFLE(3, 0, 2, 1));
			// z2,x2,y2,w2
			__m128 vTemp2 = SIV3D_PERMUTE_PS(v2, _MM_SHUFFLE(3, 1, 0, 2));
			// Perform the left operation
			__m128 vResult = _mm_mul_ps(vTemp1, vTemp2);
			// z1,x1,y1,w1
			vTemp1 = SIV3D_PERMUTE_PS(vTemp1, _MM_SHUFFLE(3, 0, 2, 1));
			// y2,z2,x2,w2
			vTemp2 = SIV3D_PERMUTE_PS(vTemp2, _MM_SHUFFLE(3, 1, 0, 2));
			// Perform the right operation
			vTemp1 = _mm_mul_ps(vTemp1, vTemp2);
			// Subract the right from left, and return answer
			vResult = _mm_sub_ps(vResult, vTemp1);
			// Set w to zero
			return _mm_and_ps(vResult, constants::m128_Mask3);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector3Normalize(__m128 v)
		{
		# ifdef SIV3D_USE_SSE3

			// Perform the dot product on x,y and z only
			__m128 vLengthSq = _mm_mul_ps(v, v);
			vLengthSq = _mm_and_ps(vLengthSq, constants::m128_Mask3);
			vLengthSq = _mm_hadd_ps(vLengthSq, vLengthSq);
			vLengthSq = _mm_hadd_ps(vLengthSq, vLengthSq);
			// Prepare for the division
			__m128 vResult = _mm_sqrt_ps(vLengthSq);
			// Create zero with a single instruction
			__m128 vZeroMask = _mm_setzero_ps();
			// Test for a divide by zero (Must be FP to detect -0.0)
			vZeroMask = _mm_cmpneq_ps(vZeroMask, vResult);
			// Failsafe on zero (Or epsilon) length planes
			// If the length is infinity, set the elements to zero
			vLengthSq = _mm_cmpneq_ps(vLengthSq, constants::m128_Infinity);
			// Divide to perform the normalization
			vResult = _mm_div_ps(v, vResult);
			// Any that are infinity, set to zero
			vResult = _mm_and_ps(vResult, vZeroMask);
			// Select qnan or result based on infinite length
			__m128 vTemp1 = _mm_andnot_ps(vLengthSq, constants::m128_QNaN);
			__m128 vTemp2 = _mm_and_ps(vResult, vLengthSq);
			vResult = _mm_or_ps(vTemp1, vTemp2);
			return vResult;

		# else

			// Perform the dot product on x,y and z only
			__m128 vLengthSq = _mm_mul_ps(v, v);
			__m128 vTemp = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(2, 1, 2, 1));
			vLengthSq = _mm_add_ss(vLengthSq, vTemp);
			vTemp = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(1, 1, 1, 1));
			vLengthSq = _mm_add_ss(vLengthSq, vTemp);
			vLengthSq = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(0, 0, 0, 0));
			// Prepare for the division
			__m128 vResult = _mm_sqrt_ps(vLengthSq);
			// Create zero with a single instruction
			__m128 vZeroMask = _mm_setzero_ps();
			// Test for a divide by zero (Must be FP to detect -0.0)
			vZeroMask = _mm_cmpneq_ps(vZeroMask, vResult);
			// Failsafe on zero (Or epsilon) length planes
			// If the length is infinity, set the elements to zero
			vLengthSq = _mm_cmpneq_ps(vLengthSq, constants::m128_Infinity);
			// Divide to perform the normalization
			vResult = _mm_div_ps(v, vResult);
			// Any that are infinity, set to zero
			vResult = _mm_and_ps(vResult, vZeroMask);
			// Select qnan or result based on infinite length
			__m128 vTemp1 = _mm_andnot_ps(vLengthSq, constants::m128_QNaN);
			__m128 vTemp2 = _mm_and_ps(vResult, vLengthSq);
			vResult = _mm_or_ps(vTemp1, vTemp2);
			return vResult;

		# endif
		}

		//
		// 4D-Vector 計算
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector4Dot(__m128 v1, __m128 v2)
		{
		# ifdef SIV3D_USE_SSE3
		
			__m128 vTemp = _mm_mul_ps(v1, v2);
			
			vTemp = _mm_hadd_ps(vTemp, vTemp);
			
			return _mm_hadd_ps(vTemp, vTemp);

		# else

			__m128 vTemp2 = v2;
			__m128 vTemp = _mm_mul_ps(v1, vTemp2);
			vTemp2 = _mm_shuffle_ps(vTemp2, vTemp, _MM_SHUFFLE(1, 0, 0, 0)); // Copy X to the Z position and Y to the W position
			vTemp2 = _mm_add_ps(vTemp2, vTemp);          // Add Z = X+Z; W = Y+W;
			vTemp = _mm_shuffle_ps(vTemp, vTemp2, _MM_SHUFFLE(0, 3, 0, 0));  // Copy W to the Z position
			vTemp = _mm_add_ps(vTemp, vTemp2);           // Add Z and W together
			return SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(2, 2, 2, 2));    // Splat Z and return

		# endif
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector4Cross(__m128 v1, __m128 v2, __m128 v3)
		{
			// V2zwyz * V3wzwy
			__m128 vResult = SIV3D_PERMUTE_PS(v2, _MM_SHUFFLE(2, 1, 3, 2));
			__m128 vTemp3 = SIV3D_PERMUTE_PS(v3, _MM_SHUFFLE(1, 3, 2, 3));
			vResult = _mm_mul_ps(vResult, vTemp3);
			// - V2wzwy * V3zwyz
			__m128 vTemp2 = SIV3D_PERMUTE_PS(v2, _MM_SHUFFLE(1, 3, 2, 3));
			vTemp3 = SIV3D_PERMUTE_PS(vTemp3, _MM_SHUFFLE(1, 3, 0, 1));
			vTemp2 = _mm_mul_ps(vTemp2, vTemp3);
			vResult = _mm_sub_ps(vResult, vTemp2);
			// term1 * V1yxxx
			__m128 vTemp1 = SIV3D_PERMUTE_PS(v1, _MM_SHUFFLE(0, 0, 0, 1));
			vResult = _mm_mul_ps(vResult, vTemp1);

			// V2ywxz * V3wxwx
			vTemp2 = SIV3D_PERMUTE_PS(v2, _MM_SHUFFLE(2, 0, 3, 1));
			vTemp3 = SIV3D_PERMUTE_PS(v3, _MM_SHUFFLE(0, 3, 0, 3));
			vTemp3 = _mm_mul_ps(vTemp3, vTemp2);
			// - V2wxwx * V3ywxz
			vTemp2 = SIV3D_PERMUTE_PS(vTemp2, _MM_SHUFFLE(2, 1, 2, 1));
			vTemp1 = SIV3D_PERMUTE_PS(v3, _MM_SHUFFLE(2, 0, 3, 1));
			vTemp2 = _mm_mul_ps(vTemp2, vTemp1);
			vTemp3 = _mm_sub_ps(vTemp3, vTemp2);
			// vResult - temp * V1zzyy
			vTemp1 = SIV3D_PERMUTE_PS(v1, _MM_SHUFFLE(1, 1, 2, 2));
			vTemp1 = _mm_mul_ps(vTemp1, vTemp3);
			vResult = _mm_sub_ps(vResult, vTemp1);

			// V2yzxy * V3zxyx
			vTemp2 = SIV3D_PERMUTE_PS(v2, _MM_SHUFFLE(1, 0, 2, 1));
			vTemp3 = SIV3D_PERMUTE_PS(v3, _MM_SHUFFLE(0, 1, 0, 2));
			vTemp3 = _mm_mul_ps(vTemp3, vTemp2);
			// - V2zxyx * V3yzxy
			vTemp2 = SIV3D_PERMUTE_PS(vTemp2, _MM_SHUFFLE(2, 0, 2, 1));
			vTemp1 = SIV3D_PERMUTE_PS(v3, _MM_SHUFFLE(1, 0, 2, 1));
			vTemp1 = _mm_mul_ps(vTemp1, vTemp2);
			vTemp3 = _mm_sub_ps(vTemp3, vTemp1);
			// vResult + term * V1wwwz
			vTemp1 = SIV3D_PERMUTE_PS(v1, _MM_SHUFFLE(2, 3, 3, 3));
			vTemp3 = _mm_mul_ps(vTemp3, vTemp1);
			vResult = _mm_add_ps(vResult, vTemp3);
			return vResult;
		}

		//
		//
		///////////////////////////////////////////////////////////////
	}
}
