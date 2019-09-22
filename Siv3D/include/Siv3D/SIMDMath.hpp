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
# include "Fwd.hpp"

# define SIV3D_PERMUTE_PS(v, c) _mm_shuffle_ps(v, v, c)

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

			inline constexpr Int4A m128_Infinity{ 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 };
			inline constexpr Int4A m128_QNaN{ 0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000 };
			inline constexpr Uint4A m128_Mask3{ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };

			inline constexpr uint32 u_SELECT_0 = 0x00000000;
			inline constexpr uint32 u_SELECT_1 = 0xFFFFFFFF;
			inline constexpr Uint4A m128_Select1110{ u_SELECT_1, u_SELECT_1, u_SELECT_1, u_SELECT_0 };
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
			__m128i temp = _mm_set_epi32(static_cast<int>(w), static_cast<int>(z), static_cast<int>(y), static_cast<int>(x));

			return _mm_castsi128_ps(temp);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetAll(float value)
		{
			return _mm_set_ps1(value);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetAllUint(uint32 value)
		{
			__m128i temp = _mm_set1_epi32(static_cast<int>(value));

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
			__m128i yyyy = _mm_shuffle_epi32(_mm_castps_si128(v), _MM_SHUFFLE(1, 1, 1, 1));

			return static_cast<uint32>(_mm_cvtsi128_si32(yyyy));
		}

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL GetUintZ(__m128 v)
		{
			__m128i zzzz = _mm_shuffle_epi32(_mm_castps_si128(v), _MM_SHUFFLE(2, 2, 2, 2));

			return static_cast<uint32>(_mm_cvtsi128_si32(zzzz));
		}

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL GetUintW(__m128 v)
		{
			__m128i wwww = _mm_shuffle_epi32(_mm_castps_si128(v), _MM_SHUFFLE(3, 3, 3, 3));

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
			__m128i x000 = _mm_cvtsi32_si128(static_cast<int>(x));

			return _mm_move_ss(v, _mm_castsi128_ps(x000));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintY(__m128 v, uint32 y)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 2, 0, 1));

			__m128i y000 = _mm_cvtsi32_si128(static_cast<int>(y));

			result = _mm_move_ss(result, _mm_castsi128_ps(y000));

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(3, 2, 0, 1));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintZ(__m128 v, uint32 z)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(3, 0, 1, 2));

			__m128i z000 = _mm_cvtsi32_si128(static_cast<int>(z));

			result = _mm_move_ss(result, _mm_castsi128_ps(z000));

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(3, 0, 1, 2));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUintW(__m128 v, uint32 w)
		{
			__m128 result = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(0, 2, 1, 3));

			__m128i w000 = _mm_cvtsi32_si128(static_cast<int>(w));

			result = _mm_move_ss(result, _mm_castsi128_ps(w000));

			return SIV3D_PERMUTE_PS(result, _MM_SHUFFLE(0, 2, 1, 3));
		}


		//
		// その他の操作
		//

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Select(__m128 v1, __m128 v2, __m128 control)
		{
			__m128 t1 = _mm_andnot_ps(control, v1);

			__m128 t2 = _mm_and_ps(v2, control);

			return _mm_or_ps(t1, t2);
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
			__m128 mul = _mm_mul_ps(v1, v2);

			return _mm_add_ps(mul, v3);
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

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector3Normalize(__m128 v)
		{
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
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector3Dot(__m128 v1, __m128 v2)
		{
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
		//
		//
		///////////////////////////////////////////////////////////////
	}
}
