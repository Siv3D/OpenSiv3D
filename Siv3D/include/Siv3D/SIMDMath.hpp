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

			[[nodiscard]] operator __m128i() const noexcept
			{
				return _mm_castps_si128(vec);
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
			inline constexpr __m128 m128_Zero{ 0.0f, 0.0f, 0.0f, 0.0f };
			inline constexpr __m128 m128_One{ 1.0f, 1.0f, 1.0f, 1.0f };
			inline constexpr __m128 m128_OneHalf{ 0.5f, 0.5f, 0.5f, 0.5f };
			inline constexpr __m128 m128_NegativeOne{ -1.0f, -1.0f, -1.0f, -1.0f };

			inline constexpr __m128 m128_SinCoefficients0{ -0.16666667f, +0.0083333310f, -0.00019840874f, +2.7525562e-06f };
			inline constexpr __m128 m128_SinCoefficients1{ -2.3889859e-08f, -0.16665852f /*Est1*/, +0.0083139502f /*Est2*/, -0.00018524670f /*Est3*/ };
			inline constexpr __m128 m128_CosCoefficients0{ -0.5f, +0.041666638f, -0.0013888378f, +2.4760495e-05f };
			inline constexpr __m128 m128_CosCoefficients1{ -2.6051615e-07f, -0.49992746f /*Est1*/, +0.041493919f /*Est2*/, -0.0012712436f /*Est3*/ };
			inline constexpr __m128 m128_ATanCoefficients0{ -0.3333314528f, +0.1999355085f, -0.1420889944f, +0.1065626393f };
			inline constexpr __m128 m128_ATanCoefficients1{ -0.0752896400f, +0.0429096138f, -0.0161657367f, +0.0028662257f };

			inline constexpr __m128 m128_MIdentityR0{ 1.0f, 0.0f, 0.0f, 0.0f };
			inline constexpr __m128 m128_MIdentityR1{ 0.0f, 1.0f, 0.0f, 0.0f };
			inline constexpr __m128 m128_MIdentityR2{ 0.0f, 0.0f, 1.0f, 0.0f };
			inline constexpr __m128 m128_MIdentityR3{ 0.0f, 0.0f, 0.0f, 1.0f };

			inline constexpr __m128 m128_NegateX{ -1.0f, 1.0f, 1.0f, 1.0f };
			inline constexpr __m128 m128_NegateY{ 1.0f, -1.0f, 1.0f, 1.0f };
			inline constexpr __m128 m128_NegateZ{ 1.0f, 1.0f, -1.0f, 1.0f };
			inline constexpr __m128 m128_NegateW{ 1.0f, 1.0f, 1.0f, -1.0f };

			inline constexpr __m128 m128_NoFraction{ 8388608.0f, 8388608.0f, 8388608.0f, 8388608.0f };

			inline constexpr __m128 m128_Epsilon{ 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f };
			inline constexpr Int4A m128_Infinity{ { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } } };
			inline constexpr Int4A m128_QNaN{ { { 0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000 } } };
			inline constexpr Int4A m128_AbsMask{ { { 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF } } };
			
			inline constexpr Uint4A m128_MaskXY{ { { 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000 } } };
			inline constexpr Uint4A m128_Mask3{ { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 } } };
			inline constexpr Uint4A m128_MaskX{ { { 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000 } } };
			inline constexpr Uint4A m128_MaskY{ { { 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000 } } };
			inline constexpr Uint4A m128_MaskZ{ { { 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000 } } };
			inline constexpr Uint4A m128_MaskW{ { { 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF } } };

			inline constexpr Uint4A m128_NegativeZero{ { { 0x80000000, 0x80000000, 0x80000000, 0x80000000 } } };
			inline constexpr Uint4A m128_NegOneMask{ { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF } } };

			inline constexpr uint32 u_SELECT_0 = 0x00000000;
			inline constexpr uint32 u_SELECT_1 = 0xFFFFFFFF;
			inline constexpr Uint4A m128_Select1110{ { { u_SELECT_1, u_SELECT_1, u_SELECT_1, u_SELECT_0 } } };

			inline constexpr uint32 SwizzleX = 0;
			inline constexpr uint32 SwizzleY = 1;
			inline constexpr uint32 SwizzleZ = 2;
			inline constexpr uint32 SwizzleW = 3;

			inline constexpr float f_PI			= 3.141592654f;
			inline constexpr float f_2PI		= 6.283185307f;
			inline constexpr float f_1DIVPI		= 0.318309886f;
			inline constexpr float f_1DIV2PI	= 0.159154943f;
			inline constexpr float f_PIDIV2		= 1.570796327f;
			inline constexpr float f_PIDIV4		= 0.785398163f;

			inline constexpr __m128 m128_HalfPi{ f_PIDIV2, f_PIDIV2, f_PIDIV2, f_PIDIV2 };
			inline constexpr __m128 m128_Pi{ f_PI, f_PI, f_PI, f_PI };
			inline constexpr __m128 m128_TwoPi{ f_2PI, f_2PI, f_2PI, f_2PI };
			inline constexpr __m128 m128_ReciprocalTwoPi{ f_1DIV2PI, f_1DIV2PI, f_1DIV2PI, f_1DIV2PI };
		}

		inline constexpr uint32 u_PERMUTE_0X = 0;
		inline constexpr uint32 u_PERMUTE_0Y = 1;
		inline constexpr uint32 u_PERMUTE_0Z = 2;
		inline constexpr uint32 u_PERMUTE_0W = 3;
		inline constexpr uint32 u_PERMUTE_1X = 4;
		inline constexpr uint32 u_PERMUTE_1Y = 5;
		inline constexpr uint32 u_PERMUTE_1Z = 6;
		inline constexpr uint32 u_PERMUTE_1W = 7;

		inline constexpr uint32 u_CRMASK_CR6TRUE = 0x00000080;
		inline constexpr uint32 u_CRMASK_CR6FALSE = 0x00000020;

		// PermuteHelper internal template (SSE only)
		namespace Internal
		{
			// Slow path fallback for permutes that do not map to a single SSE shuffle opcode.
			template <uint32 Shuffle, bool WhichX, bool WhichY, bool WhichZ, bool WhichW>
			struct PermuteHelper
			{
				static __m128 SIV3D_VECTOR_CALL Permute(__m128 v1, __m128 v2)
				{
					static const Uint4A selectMask
					{{{
						WhichX ? 0xFFFFFFFF : 0,
						WhichY ? 0xFFFFFFFF : 0,
						WhichZ ? 0xFFFFFFFF : 0,
						WhichW ? 0xFFFFFFFF : 0,
					}}};

					__m128 shuffled1 = SIV3D_PERMUTE_PS(v1, Shuffle);
					__m128 shuffled2 = SIV3D_PERMUTE_PS(v2, Shuffle);

					__m128 masked1 = _mm_andnot_ps(selectMask, shuffled1);
					__m128 masked2 = _mm_and_ps(selectMask, shuffled2);

					return _mm_or_ps(masked1, masked2);
				}
			};

			// Fast path for permutes that only read from the first vector.
			template <uint32 Shuffle>
			struct PermuteHelper<Shuffle, false, false, false, false>
			{
				static __m128 SIV3D_VECTOR_CALL Permute(__m128 v1, __m128) { return SIV3D_PERMUTE_PS(v1, Shuffle); }
			};

			// Fast path for permutes that only read from the second vector.
			template <uint32 Shuffle>
			struct PermuteHelper<Shuffle, true, true, true, true>
			{
				static __m128 SIV3D_VECTOR_CALL Permute(__m128, __m128 v2) { return SIV3D_PERMUTE_PS(v2, Shuffle); }
			};

			// Fast path for permutes that read XY from the first vector, ZW from the second.
			template<uint32 Shuffle>
			struct PermuteHelper<Shuffle, false, false, true, true>
			{
				static __m128 SIV3D_VECTOR_CALL Permute(__m128 v1, __m128 v2) { return _mm_shuffle_ps(v1, v2, Shuffle); }
			};

			// Fast path for permutes that read XY from the second vector, ZW from the first.
			template<uint32_t Shuffle> struct PermuteHelper<Shuffle, true, true, false, false>
			{
				static __m128 SIV3D_VECTOR_CALL Permute(__m128 v1, __m128 v2) { return _mm_shuffle_ps(v2, v1, Shuffle); }
			};
		}

		[[nodiscard]] inline bool ComparisonAnyTrue(uint32 CR)
		{
			return (((CR)&u_CRMASK_CR6FALSE) != u_CRMASK_CR6FALSE);
		}

		// General permute template
		template <uint32 PermuteX, uint32 PermuteY, uint32 PermuteZ, uint32 PermuteW>
		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Permute(__m128 v1, __m128 v2)
		{
			static_assert(PermuteX <= 7, "PermuteX template parameter out of range");
			static_assert(PermuteY <= 7, "PermuteY template parameter out of range");
			static_assert(PermuteZ <= 7, "PermuteZ template parameter out of range");
			static_assert(PermuteW <= 7, "PermuteW template parameter out of range");

			const uint32 Shuffle = _MM_SHUFFLE(PermuteW & 3, PermuteZ & 3, PermuteY & 3, PermuteX & 3);

			const bool WhichX = PermuteX > 3;
			const bool WhichY = PermuteY > 3;
			const bool WhichZ = PermuteZ > 3;
			const bool WhichW = PermuteW > 3;

			return Internal::PermuteHelper<Shuffle, WhichX, WhichY, WhichZ, WhichW>::Permute(v1, v2);
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

		[[nodiscard]] inline float ScalarACos(float value)
		{
			// Clamp input to [-1,1].
			bool nonnegative = (value >= 0.0f);
			float x = fabsf(value);
			float omx = 1.0f - x;
			if (omx < 0.0f)
			{
				omx = 0.0f;
			}
			float root = sqrtf(omx);

			// 7-degree minimax approximation
			float result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + 1.5707963050f;
			result *= root;

			// acos(x) = pi - acos(-x) when x < 0
			return (nonnegative ? result : constants::f_PI - result);
		}

		///////////////////////////////////////////////////////////////
		//
		//	Load
		//
		///////////////////////////////////////////////////////////////

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL LoadFloat3(const Float3* pSource)
		{
			const __m128 x000 = _mm_load_ss(&pSource->x);

			const __m128 y000 = _mm_load_ss(&pSource->y);

			const __m128 z000 = _mm_load_ss(&pSource->z);

			const __m128 xy00 = _mm_unpacklo_ps(x000, y000);

			return _mm_movelh_ps(xy00, z000); // xyz0
		}

		///////////////////////////////////////////////////////////////
		//
		//	Store
		//
		///////////////////////////////////////////////////////////////

		inline void SIV3D_VECTOR_CALL StoreFloat(float* pDestination, __m128 v)
		{
			_mm_store_ss(pDestination, v);
		}

		inline void SIV3D_VECTOR_CALL StoreFloat2(Float2* pDestination, __m128 v)
		{
			const __m128 t1 = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(1, 1, 1, 1));

			_mm_store_ss(&pDestination->x, v);

			_mm_store_ss(&pDestination->y, t1);
		}

		inline void SIV3D_VECTOR_CALL StoreFloat3(Float3* pDestination, __m128 v)
		{
			const __m128 t1 = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(1, 1, 1, 1));

			const __m128 t2 = SIV3D_PERMUTE_PS(v, _MM_SHUFFLE(2, 2, 2, 2));

			_mm_store_ss(&pDestination->x, v);

			_mm_store_ss(&pDestination->y, t1);

			_mm_store_ss(&pDestination->z, t2);
		}

		inline void SIV3D_VECTOR_CALL StoreFloat4(Float4* pDestination, __m128 v)
		{
			_mm_storeu_ps(&pDestination->x, v);
		}

		///////////////////////////////////////////////////////////////
		//
		//	Value
		//
		///////////////////////////////////////////////////////////////

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

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL TrueInt()
		{
			const __m128i temp = _mm_set1_epi32(-1);

			return _mm_castsi128_ps(temp);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL FalseInt()
		{
			return _mm_setzero_ps();
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Set(float x, float y, float z, float w)
		{
			return _mm_set_ps(w, z, y, x);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetUint(uint32 x, uint32 y, uint32 z, uint32 w)
		{
			const __m128i temp = _mm_set_epi32(static_cast<int32>(w), static_cast<int32>(z), static_cast<int32>(y), static_cast<int32>(x));

			return _mm_castsi128_ps(temp);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetAll(float value)
		{
			return _mm_set_ps1(value);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL SetAllUint(uint32 value)
		{
			const __m128i temp = _mm_set1_epi32(static_cast<int32>(value));

			return _mm_castsi128_ps(temp);
		}

		///////////////////////////////////////////////////////////////
		//
		//	Splat
		//
		///////////////////////////////////////////////////////////////

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

		///////////////////////////////////////////////////////////////
		//
		//	Get (float)
		//
		///////////////////////////////////////////////////////////////

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

		///////////////////////////////////////////////////////////////
		//
		//	Get (uint32)
		//
		///////////////////////////////////////////////////////////////

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

		///////////////////////////////////////////////////////////////
		//
		//	Set X/Y/Z/W (float)
		//
		///////////////////////////////////////////////////////////////

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

		///////////////////////////////////////////////////////////////
		//
		//	Set X/Y/Z/W (uint32)
		//
		///////////////////////////////////////////////////////////////

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

		///////////////////////////////////////////////////////////////
		//
		//	Swizzle
		//
		///////////////////////////////////////////////////////////////

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

		///////////////////////////////////////////////////////////////
		//
		//	Select
		//
		///////////////////////////////////////////////////////////////

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Select(__m128 v1, __m128 v2, __m128 control)
		{
			const __m128 t1 = _mm_andnot_ps(control, v1);

			const __m128 t2 = _mm_and_ps(v2, control);

			return _mm_or_ps(t1, t2);
		}

		///////////////////////////////////////////////////////////////
		//
		//	Comparison
		//
		///////////////////////////////////////////////////////////////

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Equal(__m128 v1, __m128 v2)
		{
			return _mm_cmpeq_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL EqualInt(__m128 v1, __m128 v2)
		{
			const __m128i v = _mm_cmpeq_epi32(_mm_castps_si128(v1), _mm_castps_si128(v2));
			
			return _mm_castsi128_ps(v);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Greater(__m128 v1, __m128 v2)
		{
			return _mm_cmpgt_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL GreaterOrEqual(__m128 v1, __m128 v2)
		{
			return _mm_cmpge_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Less(__m128 v1, __m128 v2)
		{
			return _mm_cmplt_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL LessOrEqual(__m128 v1, __m128 v2)
		{
			return _mm_cmple_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL InBounds(__m128 v, __m128 bounds)
		{
			// Test if less than or equal
			__m128 temp1 = _mm_cmple_ps(v, bounds);
			
			// Negate the bounds
			__m128 temp2 = _mm_mul_ps(bounds, constants::m128_NegativeOne);
			
			// Test if greater or equal (Reversed)
			temp2 = _mm_cmple_ps(temp2, v);
			
			// Blend answers
			temp1 = _mm_and_ps(temp1, temp2);
			
			return temp1;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL IsNaN(__m128 v)
		{
			return _mm_cmpneq_ps(v, v);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL IsInfinite(__m128 v)
		{
			// Mask off the sign bit
			__m128 temp = _mm_and_ps(v, constants::m128_AbsMask);
			
			// Compare to infinity
			temp = _mm_cmpeq_ps(temp, constants::m128_Infinity);
			
			// If any are infinity, the signs are true.
			return temp;
		}

		///////////////////////////////////////////////////////////////
		//
		//	Math
		//
		///////////////////////////////////////////////////////////////

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Min(__m128 v1, __m128 v2)
		{
			return _mm_min_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Max(__m128 v1, __m128 v2)
		{
			return _mm_max_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Round(__m128 v)
		{
			const __m128 sign = _mm_and_ps(v, constants::m128_NegativeZero.vec);
			
			const __m128 sMagic = _mm_or_ps(constants::m128_NoFraction, sign);
			
			__m128 r1 = _mm_add_ps(v, sMagic);
			
			r1 = _mm_sub_ps(r1, sMagic);
			
			__m128 r2 = _mm_and_ps(v, constants::m128_AbsMask.vec);
			
			const __m128 mask = _mm_cmple_ps(r2, constants::m128_NoFraction);
			
			r2 = _mm_andnot_ps(mask, v);
			
			r1 = _mm_and_ps(r1, mask);
			
			const __m128 vResult = _mm_xor_ps(r1, r2);
			
			return vResult;
		}

		///////////////////////////////////////////////////////////////
		//
		//	Bits
		//
		///////////////////////////////////////////////////////////////

		[[nodiscard]] inline __m128 AndInt(__m128 v1, __m128 v2)
		{
			return _mm_and_ps(v1, v2);
		}

		[[nodiscard]] inline __m128 AndCInt(__m128 v1, __m128 v2)
		{
			const __m128i v = _mm_andnot_si128(_mm_castps_si128(v2), _mm_castps_si128(v1));
			
			return _mm_castsi128_ps(v);
		}

		[[nodiscard]] inline __m128 OrInt(__m128 v1, __m128 v2)
		{
			const __m128i v = _mm_or_si128(_mm_castps_si128(v1), _mm_castps_si128(v2));
			
			return _mm_castsi128_ps(v);
		}

		[[nodiscard]] inline __m128 NorInt(__m128 v1, __m128 v2)
		{
			__m128i v = _mm_or_si128(_mm_castps_si128(v1), _mm_castps_si128(v2));
			
			v = _mm_andnot_si128(v, constants::m128_NegOneMask);
			
			return _mm_castsi128_ps(v);
		}

		[[nodiscard]] inline __m128 XorInt(__m128 v1, __m128 v2)
		{
			const __m128i v = _mm_xor_si128(_mm_castps_si128(v1), _mm_castps_si128(v2));
			
			return _mm_castsi128_ps(v);
		}

		///////////////////////////////////////////////////////////////
		//
		//	+-*/
		//
		///////////////////////////////////////////////////////////////

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

		///////////////////////////////////////////////////////////////
		//
		//	Math
		//
		///////////////////////////////////////////////////////////////

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL FastSqrt(__m128 v)
		{
			return _mm_sqrt_ps(v);
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

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Abs(__m128 v)
		{
			__m128 vResult = _mm_setzero_ps();
			
			vResult = _mm_sub_ps(vResult, v);
			
			vResult = _mm_max_ps(vResult, v);
			
			return vResult;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL ModAngles(__m128 angles)
		{
			// Modulo the range of the given angles such that -XM_PI <= Angles < XM_PI
			__m128 vResult = _mm_mul_ps(angles, constants::m128_ReciprocalTwoPi);
			
			// Use the inline function due to complexity for rounding
			vResult = Round(vResult);
			
			vResult = _mm_mul_ps(vResult, constants::m128_TwoPi);
			
			vResult = _mm_sub_ps(angles, vResult);
			
			return vResult;
		}

		inline void SIV3D_VECTOR_CALL SinCos(__m128* pSin, __m128* pCos, __m128 v)
		{
			assert(pSin != nullptr);
			assert(pCos != nullptr);

			// 11/10-degree minimax approximation

			// Force the value within the bounds of pi
			__m128 x = ModAngles(v);

			// Map in [-pi/2,pi/2] with sin(y) = sin(x), cos(y) = sign*cos(x).
			__m128 sign = _mm_and_ps(x, constants::m128_NegativeZero.vec);
			__m128 c = _mm_or_ps(constants::m128_Pi, sign);  // pi when x >= 0, -pi when x < 0
			__m128 absx = _mm_andnot_ps(sign, x);  // |x|
			__m128 rflx = _mm_sub_ps(c, x);
			__m128 comp = _mm_cmple_ps(absx, constants::m128_HalfPi);
			__m128 select0 = _mm_and_ps(comp, x);
			__m128 select1 = _mm_andnot_ps(comp, rflx);
			x = _mm_or_ps(select0, select1);
			select0 = _mm_and_ps(comp, constants::m128_One);
			select1 = _mm_andnot_ps(comp, constants::m128_NegativeOne);
			sign = _mm_or_ps(select0, select1);

			__m128 x2 = _mm_mul_ps(x, x);

			// Compute polynomial approximation of sine
			const __m128 SC1 = constants::m128_SinCoefficients1;
			__m128 vConstants = SIV3D_PERMUTE_PS(SC1, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Result = _mm_mul_ps(vConstants, x2);

			const __m128 SC0 = constants::m128_SinCoefficients0;
			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(3, 3, 3, 3));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(2, 2, 2, 2));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(1, 1, 1, 1));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(0, 0, 0, 0));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);
			Result = _mm_add_ps(Result, constants::m128_One);
			Result = _mm_mul_ps(Result, x);
			*pSin = Result;

			// Compute polynomial approximation of cosine
			const __m128 CC1 = constants::m128_CosCoefficients1;
			vConstants = SIV3D_PERMUTE_PS(CC1, _MM_SHUFFLE(0, 0, 0, 0));
			Result = _mm_mul_ps(vConstants, x2);

			const __m128 CC0 = constants::m128_CosCoefficients0;
			vConstants = SIV3D_PERMUTE_PS(CC0, _MM_SHUFFLE(3, 3, 3, 3));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(CC0, _MM_SHUFFLE(2, 2, 2, 2));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(CC0, _MM_SHUFFLE(1, 1, 1, 1));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(CC0, _MM_SHUFFLE(0, 0, 0, 0));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);
			Result = _mm_add_ps(Result, constants::m128_One);
			Result = _mm_mul_ps(Result, sign);
			*pCos = Result;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Sin(__m128 v)
		{
			// 11-degree minimax approximation

			// Force the value within the bounds of pi
			__m128 x = ModAngles(v);

			// Map in [-pi/2,pi/2] with sin(y) = sin(x).
			__m128 sign = _mm_and_ps(x, constants::m128_NegativeZero);
			__m128 c = _mm_or_ps(constants::m128_Pi, sign);  // pi when x >= 0, -pi when x < 0
			__m128 absx = _mm_andnot_ps(sign, x);  // |x|
			__m128 rflx = _mm_sub_ps(c, x);
			__m128 comp = _mm_cmple_ps(absx, constants::m128_HalfPi);
			__m128 select0 = _mm_and_ps(comp, x);
			__m128 select1 = _mm_andnot_ps(comp, rflx);
			x = _mm_or_ps(select0, select1);

			__m128 x2 = _mm_mul_ps(x, x);

			// Compute polynomial approximation
			const __m128 SC1 = constants::m128_SinCoefficients1;
			__m128 vConstants = SIV3D_PERMUTE_PS(SC1, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 Result = _mm_mul_ps(vConstants, x2);

			const __m128 SC0 = constants::m128_SinCoefficients0;
			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(3, 3, 3, 3));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(2, 2, 2, 2));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(1, 1, 1, 1));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(SC0, _MM_SHUFFLE(0, 0, 0, 0));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);
			Result = _mm_add_ps(Result, constants::m128_One);
			Result = _mm_mul_ps(Result, x);
			return Result;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL ATan(__m128 v)
		{
			__m128 absV = Abs(v);
			__m128 invV = _mm_div_ps(constants::m128_One, v);
			__m128 comp = _mm_cmpgt_ps(v, constants::m128_One);
			__m128 select0 = _mm_and_ps(comp, constants::m128_One);
			__m128 select1 = _mm_andnot_ps(comp, constants::m128_NegativeOne);
			__m128 sign = _mm_or_ps(select0, select1);
			comp = _mm_cmple_ps(absV, constants::m128_One);
			select0 = _mm_and_ps(comp, constants::m128_Zero);
			select1 = _mm_andnot_ps(comp, sign);
			sign = _mm_or_ps(select0, select1);
			select0 = _mm_and_ps(comp, v);
			select1 = _mm_andnot_ps(comp, invV);
			__m128 x = _mm_or_ps(select0, select1);

			__m128 x2 = _mm_mul_ps(x, x);

			// Compute polynomial approximation
			const __m128 TC1 = constants::m128_ATanCoefficients1;
			__m128 vConstants = SIV3D_PERMUTE_PS(TC1, _MM_SHUFFLE(3, 3, 3, 3));
			__m128 Result = _mm_mul_ps(vConstants, x2);

			vConstants = SIV3D_PERMUTE_PS(TC1, _MM_SHUFFLE(2, 2, 2, 2));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(TC1, _MM_SHUFFLE(1, 1, 1, 1));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(TC1, _MM_SHUFFLE(0, 0, 0, 0));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			const __m128 TC0 = constants::m128_ATanCoefficients0;
			vConstants = SIV3D_PERMUTE_PS(TC0, _MM_SHUFFLE(3, 3, 3, 3));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(TC0, _MM_SHUFFLE(2, 2, 2, 2));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(TC0, _MM_SHUFFLE(1, 1, 1, 1));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);

			vConstants = SIV3D_PERMUTE_PS(TC0, _MM_SHUFFLE(0, 0, 0, 0));
			Result = _mm_add_ps(Result, vConstants);
			Result = _mm_mul_ps(Result, x2);
			Result = _mm_add_ps(Result, constants::m128_One);
			Result = _mm_mul_ps(Result, x);
			__m128 result1 = _mm_mul_ps(sign, constants::m128_HalfPi);
			result1 = _mm_sub_ps(result1, Result);

			comp = _mm_cmpeq_ps(sign, constants::m128_Zero);
			select0 = _mm_and_ps(comp, Result);
			select1 = _mm_andnot_ps(comp, result1);
			Result = _mm_or_ps(select0, select1);
			return Result;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL ATan2(__m128 y, __m128 x)
		{
			// Return the inverse tangent of Y / X in the range of -Pi to Pi with the following exceptions:

			 //     Y == 0 and X is Negative         -> Pi with the sign of Y
			 //     y == 0 and x is positive         -> 0 with the sign of y
			 //     Y != 0 and X == 0                -> Pi / 2 with the sign of Y
			 //     Y != 0 and X is Negative         -> atan(y/x) + (PI with the sign of Y)
			 //     X == -Infinity and Finite Y      -> Pi with the sign of Y
			 //     X == +Infinity and Finite Y      -> 0 with the sign of Y
			 //     Y == Infinity and X is Finite    -> Pi / 2 with the sign of Y
			 //     Y == Infinity and X == -Infinity -> 3Pi / 4 with the sign of Y
			 //     Y == Infinity and X == +Infinity -> Pi / 4 with the sign of Y

			static const __m128 ATan2Constants{ constants::f_PI, constants::f_PIDIV2, constants::f_PIDIV4, constants::f_PI * 3.0f / 4.0f };

			__m128 zero = Zero();
			__m128 ATanResultValid = TrueInt();

			__m128 Pi = SplatX(ATan2Constants);
			__m128 PiOverTwo = SplatY(ATan2Constants);
			__m128 PiOverFour = SplatZ(ATan2Constants);
			__m128 ThreePiOverFour = SplatW(ATan2Constants);

			__m128 YEqualsZero = Equal(y, zero);
			__m128 XEqualsZero = Equal(x, zero);
			__m128 XIsPositive = AndInt(x, constants::m128_NegativeZero);
			XIsPositive = EqualInt(XIsPositive, zero);
			__m128 YEqualsInfinity = IsInfinite(y);
			__m128 XEqualsInfinity = IsInfinite(x);

			__m128 YSign = AndInt(y, constants::m128_NegativeZero);
			Pi = OrInt(Pi, YSign);
			PiOverTwo = OrInt(PiOverTwo, YSign);
			PiOverFour = OrInt(PiOverFour, YSign);
			ThreePiOverFour = OrInt(ThreePiOverFour, YSign);

			__m128 R1 = Select(Pi, YSign, XIsPositive);
			__m128 R2 = Select(ATanResultValid, PiOverTwo, XEqualsZero);
			__m128 R3 = Select(R2, R1, YEqualsZero);
			__m128 R4 = Select(ThreePiOverFour, PiOverFour, XIsPositive);
			__m128 R5 = Select(PiOverTwo, R4, XEqualsInfinity);
			__m128 Result = Select(R3, R5, YEqualsInfinity);
			ATanResultValid = EqualInt(Result, ATanResultValid);

			__m128 V = Divide(y, x);

			__m128 R0 = ATan(V);

			R1 = Select(Pi, constants::m128_NegativeZero, XIsPositive);
			R2 = Add(R0, R1);

			return Select(Result, R2, ATanResultValid);
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

		inline __m128 SIV3D_VECTOR_CALL QuaternionConjugate(__m128 q);
		inline __m128 SIV3D_VECTOR_CALL QuaternionMultiply(__m128 q1, __m128 q2);

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector3Rotate(__m128 v, __m128 rotationQuaternion)
		{
			__m128 A = Select(constants::m128_Select1110.vec, v, constants::m128_Select1110.vec);
			__m128 Q = QuaternionConjugate(rotationQuaternion);
			__m128 Result = QuaternionMultiply(Q, A);
			return QuaternionMultiply(Result, rotationQuaternion);
		}

		//
		// 4D-Vector 計算
		//
		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector4Equal(__m128 v1, __m128 v2)
		{
			__m128 vTemp = _mm_cmpeq_ps(v1, v2);
			
			return ((_mm_movemask_ps(vTemp) == 0x0f) != 0);
		}

		[[nodiscard]] inline uint32 SIV3D_VECTOR_CALL Vector4EqualIntR(__m128 v1, __m128 v2)
		{
			__m128i vTemp = _mm_cmpeq_epi32(_mm_castps_si128(v1), _mm_castps_si128(v2));
			int iTest = _mm_movemask_ps(_mm_castsi128_ps(vTemp));
			uint32_t CR = 0;
			if (iTest == 0xf)     // All equal?
			{
				CR = u_CRMASK_CR6TRUE;
			}
			else if (iTest == 0)  // All not equal?
			{
				CR = u_CRMASK_CR6FALSE;
			}
			return CR;
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector4NotEqualInt(__m128 v1, __m128 v2)
		{
			const __m128i vTemp = _mm_cmpeq_epi32(_mm_castps_si128(v1), _mm_castps_si128(v2));
			
			return ((_mm_movemask_ps(_mm_castsi128_ps(vTemp)) != 0xF) != 0);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector4Less(__m128 v1, __m128 v2)
		{
			const __m128 vTemp = _mm_cmplt_ps(v1, v2);
			
			return ((_mm_movemask_ps(vTemp) == 0x0f) != 0);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector4IsNaN(__m128 v)
		{
			// Test against itself. NaN is always not equal
			__m128 vTempNan = _mm_cmpneq_ps(v, v);
			// If any are NaN, the mask is non-zero
			return (_mm_movemask_ps(vTempNan) != 0);
		}

		[[nodiscard]] inline bool SIV3D_VECTOR_CALL Vector4IsInfinite(__m128 v)
		{
			// Mask off the sign bit
			__m128 vTemp = _mm_and_ps(v, constants::m128_AbsMask);
			// Compare to infinity
			vTemp = _mm_cmpeq_ps(vTemp, constants::m128_Infinity);
			// If any are infinity, the signs are true.
			return (_mm_movemask_ps(vTemp) != 0);
		}

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

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector4LengthSq(__m128 v)
		{
			return Vector4Dot(v, v);
		}

		inline __m128 SIV3D_VECTOR_CALL Vector4Normalize(__m128 v)
		{
		# ifdef SIV3D_USE_SSE3

			// Perform the dot product on x,y,z and w
			__m128 vLengthSq = _mm_mul_ps(v, v);
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
			vLengthSq = _mm_cmpneq_ps(vLengthSq, constants::m128_Infinity.vec);
			// Divide to perform the normalization
			vResult = _mm_div_ps(v, vResult);
			// Any that are infinity, set to zero
			vResult = _mm_and_ps(vResult, vZeroMask);
			// Select qnan or result based on infinite length
			__m128 vTemp1 = _mm_andnot_ps(vLengthSq, constants::m128_QNaN.vec);
			__m128 vTemp2 = _mm_and_ps(vResult, vLengthSq);
			vResult = _mm_or_ps(vTemp1, vTemp2);
			return vResult;

		# else

			// Perform the dot product on x,y,z and w
			__m128 vLengthSq = _mm_mul_ps(v, v);
			// vTemp has z and w
			__m128 vTemp = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(3, 2, 3, 2));
			// x+z, y+w
			vLengthSq = _mm_add_ps(vLengthSq, vTemp);
			// x+z,x+z,x+z,y+w
			vLengthSq = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(1, 0, 0, 0));
			// ??,??,y+w,y+w
			vTemp = _mm_shuffle_ps(vTemp, vLengthSq, _MM_SHUFFLE(3, 3, 0, 0));
			// ??,??,x+z+y+w,??
			vLengthSq = _mm_add_ps(vLengthSq, vTemp);
			// Splat the length
			vLengthSq = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(2, 2, 2, 2));
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

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL Vector4Length(__m128 v)
		{
		# if defined(SIV3D_USE_SSE3)
			__m128 vLengthSq = _mm_mul_ps(v, v);
			vLengthSq = _mm_hadd_ps(vLengthSq, vLengthSq);
			vLengthSq = _mm_hadd_ps(vLengthSq, vLengthSq);
			vLengthSq = _mm_sqrt_ps(vLengthSq);
			return vLengthSq;
		# else
			// Perform the dot product on x,y,z and w
			__m128 vLengthSq = _mm_mul_ps(v,v);
			// vTemp has z and w
			__m128 vTemp = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(3,2,3,2));
			// x+z, y+w
			vLengthSq = _mm_add_ps(vLengthSq, vTemp);
			// x+z,x+z,x+z,y+w
			vLengthSq = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(1,0,0,0));
			// ??,??,y+w,y+w
			vTemp = _mm_shuffle_ps(vTemp, vLengthSq, _MM_SHUFFLE(3,3,0,0));
			// ??,??,x+z+y+w,??
			vLengthSq = _mm_add_ps(vLengthSq, vTemp);
			// Splat the length
			vLengthSq = SIV3D_PERMUTE_PS(vLengthSq, _MM_SHUFFLE(2,2,2,2));
			// Get the length
			vLengthSq = _mm_sqrt_ps(vLengthSq);
			return vLengthSq;
		# endif
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionDot(__m128 q0, __m128 q1)
		{
			return Vector4Dot(q0, q1);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionMultiply(__m128 q1, __m128 q2)
		{
			static const __m128 ControlWZYX{ 1.0f, -1.0f, 1.0f, -1.0f };
			static const __m128 ControlZWXY{ 1.0f, 1.0f, -1.0f, -1.0f };
			static const __m128 ControlYXWZ{ -1.0f, 1.0f, 1.0f, -1.0f };
			// Copy to SSE registers and use as few as possible for x86
			__m128 Q2X = q2;
			__m128 Q2Y = q2;
			__m128 Q2Z = q2;
			__m128 vResult = q2;
			// Splat with one instruction
			vResult = SIV3D_PERMUTE_PS(vResult, _MM_SHUFFLE(3, 3, 3, 3));
			Q2X = SIV3D_PERMUTE_PS(Q2X, _MM_SHUFFLE(0, 0, 0, 0));
			Q2Y = SIV3D_PERMUTE_PS(Q2Y, _MM_SHUFFLE(1, 1, 1, 1));
			Q2Z = SIV3D_PERMUTE_PS(Q2Z, _MM_SHUFFLE(2, 2, 2, 2));
			// Retire Q1 and perform Q1*Q2W
			vResult = _mm_mul_ps(vResult, q1);
			__m128 Q1Shuffle = q1;
			// Shuffle the copies of Q1
			Q1Shuffle = SIV3D_PERMUTE_PS(Q1Shuffle, _MM_SHUFFLE(0, 1, 2, 3));
			// Mul by Q1WZYX
			Q2X = _mm_mul_ps(Q2X, Q1Shuffle);
			Q1Shuffle = SIV3D_PERMUTE_PS(Q1Shuffle, _MM_SHUFFLE(2, 3, 0, 1));
			// Flip the signs on y and z
			Q2X = _mm_mul_ps(Q2X, ControlWZYX);
			// Mul by Q1ZWXY
			Q2Y = _mm_mul_ps(Q2Y, Q1Shuffle);
			Q1Shuffle = SIV3D_PERMUTE_PS(Q1Shuffle, _MM_SHUFFLE(0, 1, 2, 3));
			// Flip the signs on z and w
			Q2Y = _mm_mul_ps(Q2Y, ControlZWXY);
			// Mul by Q1YXWZ
			Q2Z = _mm_mul_ps(Q2Z, Q1Shuffle);
			vResult = _mm_add_ps(vResult, Q2X);
			// Flip the signs on x and w
			Q2Z = _mm_mul_ps(Q2Z, ControlYXWZ);
			Q2Y = _mm_add_ps(Q2Y, Q2Z);
			vResult = _mm_add_ps(vResult, Q2Y);
			return vResult;
		}

		inline __m128 SIV3D_VECTOR_CALL QuaternionNormalize(__m128 q)
		{
			return Vector4Normalize(q);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionConjugate(__m128 q)
		{
			static const __m128 NegativeOne3{ -1.0f, -1.0f, -1.0f, 1.0f };
			return _mm_mul_ps(q, NegativeOne3);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionInverse(__m128 q)
		{
			const __m128 zero = Zero();

			__m128 L = Vector4LengthSq(q);
			__m128 Conjugate = QuaternionConjugate(q);

			__m128 Control = LessOrEqual(L, constants::m128_Epsilon);

			__m128 Result = Divide(Conjugate, L);

			Result = Select(Result, zero, Control);

			return Result;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionSlerpV(__m128 q0, __m128 q1, __m128 t)
		{
			static const __m128 OneMinusEpsilon{ 1.0f - 0.00001f, 1.0f - 0.00001f, 1.0f - 0.00001f, 1.0f - 0.00001f };
			static const Uint4A SignMask2{{{ 0x80000000, 0x00000000, 0x00000000, 0x00000000 }}};

			__m128 CosOmega = QuaternionDot(q0, q1);

			const __m128 zero = Zero();
			__m128 Control = Less(CosOmega, zero);
			__m128 sign = Select(constants::m128_One, constants::m128_NegativeOne, Control);

			CosOmega = _mm_mul_ps(CosOmega, sign);

			Control = Less(CosOmega, OneMinusEpsilon);

			__m128 SinOmega = _mm_mul_ps(CosOmega, CosOmega);
			SinOmega = _mm_sub_ps(constants::m128_One, SinOmega);
			SinOmega = _mm_sqrt_ps(SinOmega);

			__m128 Omega = ATan2(SinOmega, CosOmega);

			__m128 V01 = SIV3D_PERMUTE_PS(t, _MM_SHUFFLE(2, 3, 0, 1));
			V01 = _mm_and_ps(V01, constants::m128_MaskXY);
			V01 = _mm_xor_ps(V01, SignMask2);
			V01 = _mm_add_ps(constants::m128_MIdentityR0, V01);

			__m128 S0 = _mm_mul_ps(V01, Omega);
			S0 = Sin(S0);
			S0 = _mm_div_ps(S0, SinOmega);

			S0 = Select(V01, S0, Control);

			__m128 S1 = SplatY(S0);
			S0 = SplatX(S0);

			S1 = _mm_mul_ps(S1, sign);
			__m128 Result = _mm_mul_ps(q0, S0);
			S1 = _mm_mul_ps(S1, q1);
			Result = _mm_add_ps(Result, S1);
			return Result;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionSlerp(__m128 q0, __m128 q1, float t)
		{
			return QuaternionSlerpV(q0, q1, SetAll(t));
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionRotationRollPitchYawFromVector(__m128 angles)
		{
			static const __m128 sign = SIMD::Set(1.0f, -1.0f, -1.0f, 1.0f);

			__m128 halfAngles = Multiply(angles, constants::m128_OneHalf);

			__m128 sinAngles, cosAngles;
			SinCos(&sinAngles, &cosAngles, halfAngles);

			__m128 P0 = Permute<u_PERMUTE_0X, u_PERMUTE_1X, u_PERMUTE_1X, u_PERMUTE_1X>(sinAngles, cosAngles);
			__m128 Y0 = Permute<u_PERMUTE_1Y, u_PERMUTE_0Y, u_PERMUTE_1Y, u_PERMUTE_1Y>(sinAngles, cosAngles);
			__m128 R0 = Permute<u_PERMUTE_1Z, u_PERMUTE_1Z, u_PERMUTE_0Z, u_PERMUTE_1Z>(sinAngles, cosAngles);
			__m128 P1 = Permute<u_PERMUTE_0X, u_PERMUTE_1X, u_PERMUTE_1X, u_PERMUTE_1X>(cosAngles, sinAngles);
			__m128 Y1 = Permute<u_PERMUTE_1Y, u_PERMUTE_0Y, u_PERMUTE_1Y, u_PERMUTE_1Y>(cosAngles, sinAngles);
			__m128 R1 = Permute<u_PERMUTE_1Z, u_PERMUTE_1Z, u_PERMUTE_0Z, u_PERMUTE_1Z>(cosAngles, sinAngles);

			__m128 Q1 = Multiply(P1, sign);
			__m128 Q0 = Multiply(P0, Y0);
			Q1 = Multiply(Q1, Y1);
			Q0 = Multiply(Q0, R0);
			__m128 Q = MultiplyAdd(Q1, R1, Q0);

			return Q;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionRotationNormal(__m128 normalAxis, float angle)
		{
			__m128 N		= _mm_and_ps(normalAxis, constants::m128_Mask3);
			N				= _mm_or_ps(N, constants::m128_MIdentityR3);
			__m128 Scale	= _mm_set_ps1(0.5f * angle);
			__m128 vSine;
			__m128 vCosine;
			SIMD::SinCos(&vSine, &vCosine, Scale);
			Scale			= _mm_and_ps(vSine, constants::m128_Mask3);
			vCosine			= _mm_and_ps(vCosine, constants::m128_MaskW);
			Scale			= _mm_or_ps(Scale, vCosine);
			N				= _mm_mul_ps(N, Scale);
			return N;
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionRotationAxis(__m128 axis, float angle)
		{
			assert(!Vector3Equal(axis, Zero()));
			assert(!Vector3IsInfinite(axis));

			__m128 Normal = Vector3Normalize(axis);
			__m128 Q = QuaternionRotationNormal(Normal, angle);
			return Q;
		}

		inline void SIV3D_VECTOR_CALL QuaternionToAxisAngle(__m128* pAxis, float* pAngle, __m128 q)
		{
			assert(pAxis);
			assert(pAngle);

			*pAxis = q;

			*pAngle = 2.0f * ScalarACos(GetW(q));
		}

		//
		//
		///////////////////////////////////////////////////////////////
	}
}
