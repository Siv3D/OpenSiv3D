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
# include "SIMDMath.hpp"
# include "SIMD_Float4.hpp"

namespace s3d
{
	struct alignas(16) Mat4x4
	{
		SIMD_Float4 r[4];

		Mat4x4() = default;

		Mat4x4(const Mat4x4&) = default;

		Mat4x4& operator=(const Mat4x4&) = default;

		Mat4x4(Mat4x4&&) = default;

		Mat4x4& operator=(Mat4x4&&) = default;

		constexpr Mat4x4(SIMD_Float4 r0, SIMD_Float4 r1, SIMD_Float4 r2, SIMD_Float4 r3) noexcept
			: r{ r0, r1, r2, r3 } {}

		Mat4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		) noexcept
			: r{
				{ m00, m01, m02, m03 },
				{ m10, m11, m12, m13 },
				{ m20, m21, m22, m23 },
				{ m30, m31, m32, m33 } } {}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator -() const noexcept
		{
			return{ -r[0], -r[1], -r[2], -r[3] };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator +(Mat4x4 m) const noexcept
		{
			return{ r[0] + m.r[0], r[1] + m.r[1], r[2] + m.r[2], r[3] + m.r[3] };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator -(Mat4x4 m) const noexcept
		{
			return{ r[0] - m.r[0], r[1] - m.r[1], r[2] - m.r[2], r[3] - m.r[3] };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator *(float s) const noexcept
		{
			return{ r[0] * s, r[1] * s, r[2] * s, r[3] * s };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator *(Mat4x4 m) const noexcept
		{
			return Multiply(*this, m);
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator /(float s) const noexcept
		{
			return{ r[0] / s, r[1] / s, r[2] / s, r[3] / s };
		}

		Mat4x4& SIV3D_VECTOR_CALL operator +=(Mat4x4 v) noexcept
		{
			r[0] += v.r[0];
			r[1] += v.r[1];
			r[2] += v.r[2];
			r[3] += v.r[3];
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator -=(Mat4x4 v) noexcept
		{
			r[0] -= v.r[0];
			r[1] -= v.r[1];
			r[2] -= v.r[2];
			r[3] -= v.r[3];
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator *=(float s) noexcept
		{
			r[0] *= s;
			r[1] *= s;
			r[2] *= s;
			r[3] *= s;
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator *=(Mat4x4 m) noexcept
		{
			*this = Multiply(*this, m);
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator /=(float s) noexcept
		{
			r[0] /= s;
			r[1] /= s;
			r[2] /= s;
			r[3] /= s;
			return *this;
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL transposed() const noexcept
		{
			return Transpose(*this);
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL inverse() const noexcept
		{
			return Inverse(*this);
		}

		[[nodiscard]] float SIV3D_VECTOR_CALL determinant() const noexcept
		{
			return Determinant(*this);
		}

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

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Identity() noexcept
		{
			return Mat4x4{
				SIMD::constants::m128_MIdentityR0,
				SIMD::constants::m128_MIdentityR1,
				SIMD::constants::m128_MIdentityR2,
				SIMD::constants::m128_MIdentityR3
			};
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Set(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33) noexcept
		{
			return Mat4x4{
				SIMD::Set(m00, m01, m02, m03),
				SIMD::Set(m10, m11, m12, m13),
				SIMD::Set(m20, m21, m22, m23),
				SIMD::Set(m30, m31, m32, m33)
			};
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Multiply(Mat4x4 m1, Mat4x4 m2) noexcept
		{
			Mat4x4 mResult;

			// Use vW to hold the original row
			__m128 vW = m1.r[0];
			__m128 vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			// Perform the operation on the first row
			vX = _mm_mul_ps(vX, m2.r[0]);
			vY = _mm_mul_ps(vY, m2.r[1]);
			vZ = _mm_mul_ps(vZ, m2.r[2]);
			vW = _mm_mul_ps(vW, m2.r[3]);
			// Perform a binary add to reduce cumulative errors
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[0] = vX;

			vW = m1.r[1];
			vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			vX = _mm_mul_ps(vX, m2.r[0]);
			vY = _mm_mul_ps(vY, m2.r[1]);
			vZ = _mm_mul_ps(vZ, m2.r[2]);
			vW = _mm_mul_ps(vW, m2.r[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[1] = vX;

			vW = m1.r[2];
			vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			vX = _mm_mul_ps(vX, m2.r[0]);
			vY = _mm_mul_ps(vY, m2.r[1]);
			vZ = _mm_mul_ps(vZ, m2.r[2]);
			vW = _mm_mul_ps(vW, m2.r[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[2] = vX;

			vW = m1.r[3];
			vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			vX = _mm_mul_ps(vX, m2.r[0]);
			vY = _mm_mul_ps(vY, m2.r[1]);
			vZ = _mm_mul_ps(vZ, m2.r[2]);
			vW = _mm_mul_ps(vW, m2.r[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[3] = vX;

			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Transpose(Mat4x4 m) noexcept
		{
			// x.x,x.y,y.x,y.y
			const __m128 temp1 = _mm_shuffle_ps(m.r[0], m.r[1], _MM_SHUFFLE(1, 0, 1, 0));
			// x.z,x.w,y.z,y.w
			const __m128 temp3 = _mm_shuffle_ps(m.r[0], m.r[1], _MM_SHUFFLE(3, 2, 3, 2));
			// z.x,z.y,w.x,w.y
			const __m128 temp2 = _mm_shuffle_ps(m.r[2], m.r[3], _MM_SHUFFLE(1, 0, 1, 0));
			// z.z,z.w,w.z,w.w
			const __m128 temp4 = _mm_shuffle_ps(m.r[2], m.r[3], _MM_SHUFFLE(3, 2, 3, 2));

			Mat4x4 mResult;
			// x.x,y.x,z.x,w.x
			mResult.r[0] = _mm_shuffle_ps(temp1, temp2, _MM_SHUFFLE(2, 0, 2, 0));
			// x.y,y.y,z.y,w.y
			mResult.r[1] = _mm_shuffle_ps(temp1, temp2, _MM_SHUFFLE(3, 1, 3, 1));
			// x.z,y.z,z.z,w.z
			mResult.r[2] = _mm_shuffle_ps(temp3, temp4, _MM_SHUFFLE(2, 0, 2, 0));
			// x.w,y.w,z.w,w.w
			mResult.r[3] = _mm_shuffle_ps(temp3, temp4, _MM_SHUFFLE(3, 1, 3, 1));

			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Inverse(Mat4x4 m) noexcept
		{
			Mat4x4 MT = Transpose(m);
			__m128 V00 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(1, 1, 0, 0));
			__m128 V10 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(3, 2, 3, 2));
			__m128 V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(1, 1, 0, 0));
			__m128 V11 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(3, 2, 3, 2));
			__m128 V02 = _mm_shuffle_ps(MT.r[2], MT.r[0], _MM_SHUFFLE(2, 0, 2, 0));
			__m128 V12 = _mm_shuffle_ps(MT.r[3], MT.r[1], _MM_SHUFFLE(3, 1, 3, 1));

			__m128 D0 = _mm_mul_ps(V00, V10);
			__m128 D1 = _mm_mul_ps(V01, V11);
			__m128 D2 = _mm_mul_ps(V02, V12);

			V00 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(3, 2, 3, 2));
			V10 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(1, 1, 0, 0));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(3, 2, 3, 2));
			V11 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(1, 1, 0, 0));
			V02 = _mm_shuffle_ps(MT.r[2], MT.r[0], _MM_SHUFFLE(3, 1, 3, 1));
			V12 = _mm_shuffle_ps(MT.r[3], MT.r[1], _MM_SHUFFLE(2, 0, 2, 0));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			D0 = _mm_sub_ps(D0, V00);
			D1 = _mm_sub_ps(D1, V01);
			D2 = _mm_sub_ps(D2, V02);
			// V11 = D0Y,D0W,D2Y,D2Y
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 1, 3, 1));
			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(1, 0, 2, 1));
			V10 = _mm_shuffle_ps(V11, D0, _MM_SHUFFLE(0, 3, 0, 2));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(0, 1, 0, 2));
			V11 = _mm_shuffle_ps(V11, D0, _MM_SHUFFLE(2, 1, 2, 1));
			// V13 = D1Y,D1W,D2W,D2W
			__m128 V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 3, 3, 1));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(1, 0, 2, 1));
			V12 = _mm_shuffle_ps(V13, D1, _MM_SHUFFLE(0, 3, 0, 2));
			__m128 V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(0, 1, 0, 2));
			V13 = _mm_shuffle_ps(V13, D1, _MM_SHUFFLE(2, 1, 2, 1));

			__m128 C0 = _mm_mul_ps(V00, V10);
			__m128 C2 = _mm_mul_ps(V01, V11);
			__m128 C4 = _mm_mul_ps(V02, V12);
			__m128 C6 = _mm_mul_ps(V03, V13);

			// V11 = D0X,D0Y,D2X,D2X
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(0, 0, 1, 0));
			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(2, 1, 3, 2));
			V10 = _mm_shuffle_ps(D0, V11, _MM_SHUFFLE(2, 1, 0, 3));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(1, 3, 2, 3));
			V11 = _mm_shuffle_ps(D0, V11, _MM_SHUFFLE(0, 2, 1, 2));
			// V13 = D1X,D1Y,D2Z,D2Z
			V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(2, 2, 1, 0));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(2, 1, 3, 2));
			V12 = _mm_shuffle_ps(D1, V13, _MM_SHUFFLE(2, 1, 0, 3));
			V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(1, 3, 2, 3));
			V13 = _mm_shuffle_ps(D1, V13, _MM_SHUFFLE(0, 2, 1, 2));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			V03 = _mm_mul_ps(V03, V13);
			C0 = _mm_sub_ps(C0, V00);
			C2 = _mm_sub_ps(C2, V01);
			C4 = _mm_sub_ps(C4, V02);
			C6 = _mm_sub_ps(C6, V03);

			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(0, 3, 0, 3));
			// V10 = D0Z,D0Z,D2X,D2Y
			V10 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 0, 2, 2));
			V10 = SIV3D_PERMUTE_PS(V10, _MM_SHUFFLE(0, 2, 3, 0));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(2, 0, 3, 1));
			// V11 = D0X,D0W,D2X,D2Y
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 0, 3, 0));
			V11 = SIV3D_PERMUTE_PS(V11, _MM_SHUFFLE(2, 1, 0, 3));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(0, 3, 0, 3));
			// V12 = D1Z,D1Z,D2Z,D2W
			V12 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 2, 2, 2));
			V12 = SIV3D_PERMUTE_PS(V12, _MM_SHUFFLE(0, 2, 3, 0));
			V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(2, 0, 3, 1));
			// V13 = D1X,D1W,D2Z,D2W
			V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 2, 3, 0));
			V13 = SIV3D_PERMUTE_PS(V13, _MM_SHUFFLE(2, 1, 0, 3));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			V03 = _mm_mul_ps(V03, V13);
			__m128 C1 = _mm_sub_ps(C0, V00);
			C0 = _mm_add_ps(C0, V00);
			__m128 C3 = _mm_add_ps(C2, V01);
			C2 = _mm_sub_ps(C2, V01);
			__m128 C5 = _mm_sub_ps(C4, V02);
			C4 = _mm_add_ps(C4, V02);
			__m128 C7 = _mm_add_ps(C6, V03);
			C6 = _mm_sub_ps(C6, V03);

			C0 = _mm_shuffle_ps(C0, C1, _MM_SHUFFLE(3, 1, 2, 0));
			C2 = _mm_shuffle_ps(C2, C3, _MM_SHUFFLE(3, 1, 2, 0));
			C4 = _mm_shuffle_ps(C4, C5, _MM_SHUFFLE(3, 1, 2, 0));
			C6 = _mm_shuffle_ps(C6, C7, _MM_SHUFFLE(3, 1, 2, 0));
			C0 = SIV3D_PERMUTE_PS(C0, _MM_SHUFFLE(3, 1, 2, 0));
			C2 = SIV3D_PERMUTE_PS(C2, _MM_SHUFFLE(3, 1, 2, 0));
			C4 = SIV3D_PERMUTE_PS(C4, _MM_SHUFFLE(3, 1, 2, 0));
			C6 = SIV3D_PERMUTE_PS(C6, _MM_SHUFFLE(3, 1, 2, 0));

			// Get the determinate
			__m128 vTemp = SIMD::Vector4Dot(C0, MT.r[0]);
			vTemp = _mm_div_ps(SIMD::constants::m128_One, vTemp);
			Mat4x4 mResult;
			mResult.r[0] = _mm_mul_ps(C0, vTemp);
			mResult.r[1] = _mm_mul_ps(C2, vTemp);
			mResult.r[2] = _mm_mul_ps(C4, vTemp);
			mResult.r[3] = _mm_mul_ps(C6, vTemp);
			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Inverse(float& determinant, Mat4x4 m) noexcept
		{
			Mat4x4 MT = Transpose(m);
			__m128 V00 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(1, 1, 0, 0));
			__m128 V10 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(3, 2, 3, 2));
			__m128 V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(1, 1, 0, 0));
			__m128 V11 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(3, 2, 3, 2));
			__m128 V02 = _mm_shuffle_ps(MT.r[2], MT.r[0], _MM_SHUFFLE(2, 0, 2, 0));
			__m128 V12 = _mm_shuffle_ps(MT.r[3], MT.r[1], _MM_SHUFFLE(3, 1, 3, 1));

			__m128 D0 = _mm_mul_ps(V00, V10);
			__m128 D1 = _mm_mul_ps(V01, V11);
			__m128 D2 = _mm_mul_ps(V02, V12);

			V00 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(3, 2, 3, 2));
			V10 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(1, 1, 0, 0));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(3, 2, 3, 2));
			V11 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(1, 1, 0, 0));
			V02 = _mm_shuffle_ps(MT.r[2], MT.r[0], _MM_SHUFFLE(3, 1, 3, 1));
			V12 = _mm_shuffle_ps(MT.r[3], MT.r[1], _MM_SHUFFLE(2, 0, 2, 0));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			D0 = _mm_sub_ps(D0, V00);
			D1 = _mm_sub_ps(D1, V01);
			D2 = _mm_sub_ps(D2, V02);
			// V11 = D0Y,D0W,D2Y,D2Y
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 1, 3, 1));
			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(1, 0, 2, 1));
			V10 = _mm_shuffle_ps(V11, D0, _MM_SHUFFLE(0, 3, 0, 2));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(0, 1, 0, 2));
			V11 = _mm_shuffle_ps(V11, D0, _MM_SHUFFLE(2, 1, 2, 1));
			// V13 = D1Y,D1W,D2W,D2W
			__m128 V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 3, 3, 1));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(1, 0, 2, 1));
			V12 = _mm_shuffle_ps(V13, D1, _MM_SHUFFLE(0, 3, 0, 2));
			__m128 V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(0, 1, 0, 2));
			V13 = _mm_shuffle_ps(V13, D1, _MM_SHUFFLE(2, 1, 2, 1));

			__m128 C0 = _mm_mul_ps(V00, V10);
			__m128 C2 = _mm_mul_ps(V01, V11);
			__m128 C4 = _mm_mul_ps(V02, V12);
			__m128 C6 = _mm_mul_ps(V03, V13);

			// V11 = D0X,D0Y,D2X,D2X
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(0, 0, 1, 0));
			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(2, 1, 3, 2));
			V10 = _mm_shuffle_ps(D0, V11, _MM_SHUFFLE(2, 1, 0, 3));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(1, 3, 2, 3));
			V11 = _mm_shuffle_ps(D0, V11, _MM_SHUFFLE(0, 2, 1, 2));
			// V13 = D1X,D1Y,D2Z,D2Z
			V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(2, 2, 1, 0));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(2, 1, 3, 2));
			V12 = _mm_shuffle_ps(D1, V13, _MM_SHUFFLE(2, 1, 0, 3));
			V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(1, 3, 2, 3));
			V13 = _mm_shuffle_ps(D1, V13, _MM_SHUFFLE(0, 2, 1, 2));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			V03 = _mm_mul_ps(V03, V13);
			C0 = _mm_sub_ps(C0, V00);
			C2 = _mm_sub_ps(C2, V01);
			C4 = _mm_sub_ps(C4, V02);
			C6 = _mm_sub_ps(C6, V03);

			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(0, 3, 0, 3));
			// V10 = D0Z,D0Z,D2X,D2Y
			V10 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 0, 2, 2));
			V10 = SIV3D_PERMUTE_PS(V10, _MM_SHUFFLE(0, 2, 3, 0));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(2, 0, 3, 1));
			// V11 = D0X,D0W,D2X,D2Y
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 0, 3, 0));
			V11 = SIV3D_PERMUTE_PS(V11, _MM_SHUFFLE(2, 1, 0, 3));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(0, 3, 0, 3));
			// V12 = D1Z,D1Z,D2Z,D2W
			V12 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 2, 2, 2));
			V12 = SIV3D_PERMUTE_PS(V12, _MM_SHUFFLE(0, 2, 3, 0));
			V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(2, 0, 3, 1));
			// V13 = D1X,D1W,D2Z,D2W
			V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 2, 3, 0));
			V13 = SIV3D_PERMUTE_PS(V13, _MM_SHUFFLE(2, 1, 0, 3));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			V03 = _mm_mul_ps(V03, V13);
			__m128 C1 = _mm_sub_ps(C0, V00);
			C0 = _mm_add_ps(C0, V00);
			__m128 C3 = _mm_add_ps(C2, V01);
			C2 = _mm_sub_ps(C2, V01);
			__m128 C5 = _mm_sub_ps(C4, V02);
			C4 = _mm_add_ps(C4, V02);
			__m128 C7 = _mm_add_ps(C6, V03);
			C6 = _mm_sub_ps(C6, V03);

			C0 = _mm_shuffle_ps(C0, C1, _MM_SHUFFLE(3, 1, 2, 0));
			C2 = _mm_shuffle_ps(C2, C3, _MM_SHUFFLE(3, 1, 2, 0));
			C4 = _mm_shuffle_ps(C4, C5, _MM_SHUFFLE(3, 1, 2, 0));
			C6 = _mm_shuffle_ps(C6, C7, _MM_SHUFFLE(3, 1, 2, 0));
			C0 = SIV3D_PERMUTE_PS(C0, _MM_SHUFFLE(3, 1, 2, 0));
			C2 = SIV3D_PERMUTE_PS(C2, _MM_SHUFFLE(3, 1, 2, 0));
			C4 = SIV3D_PERMUTE_PS(C4, _MM_SHUFFLE(3, 1, 2, 0));
			C6 = SIV3D_PERMUTE_PS(C6, _MM_SHUFFLE(3, 1, 2, 0));

			// Get the determinate
			__m128 vTemp = SIMD::Vector4Dot(C0, MT.r[0]);

			determinant = SIMD::GetX(vTemp);

			vTemp = _mm_div_ps(SIMD::constants::m128_One, vTemp);
			Mat4x4 mResult;
			mResult.r[0] = _mm_mul_ps(C0, vTemp);
			mResult.r[1] = _mm_mul_ps(C2, vTemp);
			mResult.r[2] = _mm_mul_ps(C4, vTemp);
			mResult.r[3] = _mm_mul_ps(C6, vTemp);
			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Inverse(SIMD_Float4 & determinant, Mat4x4 m) noexcept
		{
			Mat4x4 MT = Transpose(m);
			__m128 V00 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(1, 1, 0, 0));
			__m128 V10 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(3, 2, 3, 2));
			__m128 V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(1, 1, 0, 0));
			__m128 V11 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(3, 2, 3, 2));
			__m128 V02 = _mm_shuffle_ps(MT.r[2], MT.r[0], _MM_SHUFFLE(2, 0, 2, 0));
			__m128 V12 = _mm_shuffle_ps(MT.r[3], MT.r[1], _MM_SHUFFLE(3, 1, 3, 1));

			__m128 D0 = _mm_mul_ps(V00, V10);
			__m128 D1 = _mm_mul_ps(V01, V11);
			__m128 D2 = _mm_mul_ps(V02, V12);

			V00 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(3, 2, 3, 2));
			V10 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(1, 1, 0, 0));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(3, 2, 3, 2));
			V11 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(1, 1, 0, 0));
			V02 = _mm_shuffle_ps(MT.r[2], MT.r[0], _MM_SHUFFLE(3, 1, 3, 1));
			V12 = _mm_shuffle_ps(MT.r[3], MT.r[1], _MM_SHUFFLE(2, 0, 2, 0));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			D0 = _mm_sub_ps(D0, V00);
			D1 = _mm_sub_ps(D1, V01);
			D2 = _mm_sub_ps(D2, V02);
			// V11 = D0Y,D0W,D2Y,D2Y
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 1, 3, 1));
			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(1, 0, 2, 1));
			V10 = _mm_shuffle_ps(V11, D0, _MM_SHUFFLE(0, 3, 0, 2));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(0, 1, 0, 2));
			V11 = _mm_shuffle_ps(V11, D0, _MM_SHUFFLE(2, 1, 2, 1));
			// V13 = D1Y,D1W,D2W,D2W
			__m128 V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 3, 3, 1));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(1, 0, 2, 1));
			V12 = _mm_shuffle_ps(V13, D1, _MM_SHUFFLE(0, 3, 0, 2));
			__m128 V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(0, 1, 0, 2));
			V13 = _mm_shuffle_ps(V13, D1, _MM_SHUFFLE(2, 1, 2, 1));

			__m128 C0 = _mm_mul_ps(V00, V10);
			__m128 C2 = _mm_mul_ps(V01, V11);
			__m128 C4 = _mm_mul_ps(V02, V12);
			__m128 C6 = _mm_mul_ps(V03, V13);

			// V11 = D0X,D0Y,D2X,D2X
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(0, 0, 1, 0));
			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(2, 1, 3, 2));
			V10 = _mm_shuffle_ps(D0, V11, _MM_SHUFFLE(2, 1, 0, 3));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(1, 3, 2, 3));
			V11 = _mm_shuffle_ps(D0, V11, _MM_SHUFFLE(0, 2, 1, 2));
			// V13 = D1X,D1Y,D2Z,D2Z
			V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(2, 2, 1, 0));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(2, 1, 3, 2));
			V12 = _mm_shuffle_ps(D1, V13, _MM_SHUFFLE(2, 1, 0, 3));
			V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(1, 3, 2, 3));
			V13 = _mm_shuffle_ps(D1, V13, _MM_SHUFFLE(0, 2, 1, 2));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			V03 = _mm_mul_ps(V03, V13);
			C0 = _mm_sub_ps(C0, V00);
			C2 = _mm_sub_ps(C2, V01);
			C4 = _mm_sub_ps(C4, V02);
			C6 = _mm_sub_ps(C6, V03);

			V00 = SIV3D_PERMUTE_PS(MT.r[1], _MM_SHUFFLE(0, 3, 0, 3));
			// V10 = D0Z,D0Z,D2X,D2Y
			V10 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 0, 2, 2));
			V10 = SIV3D_PERMUTE_PS(V10, _MM_SHUFFLE(0, 2, 3, 0));
			V01 = SIV3D_PERMUTE_PS(MT.r[0], _MM_SHUFFLE(2, 0, 3, 1));
			// V11 = D0X,D0W,D2X,D2Y
			V11 = _mm_shuffle_ps(D0, D2, _MM_SHUFFLE(1, 0, 3, 0));
			V11 = SIV3D_PERMUTE_PS(V11, _MM_SHUFFLE(2, 1, 0, 3));
			V02 = SIV3D_PERMUTE_PS(MT.r[3], _MM_SHUFFLE(0, 3, 0, 3));
			// V12 = D1Z,D1Z,D2Z,D2W
			V12 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 2, 2, 2));
			V12 = SIV3D_PERMUTE_PS(V12, _MM_SHUFFLE(0, 2, 3, 0));
			V03 = SIV3D_PERMUTE_PS(MT.r[2], _MM_SHUFFLE(2, 0, 3, 1));
			// V13 = D1X,D1W,D2Z,D2W
			V13 = _mm_shuffle_ps(D1, D2, _MM_SHUFFLE(3, 2, 3, 0));
			V13 = SIV3D_PERMUTE_PS(V13, _MM_SHUFFLE(2, 1, 0, 3));

			V00 = _mm_mul_ps(V00, V10);
			V01 = _mm_mul_ps(V01, V11);
			V02 = _mm_mul_ps(V02, V12);
			V03 = _mm_mul_ps(V03, V13);
			__m128 C1 = _mm_sub_ps(C0, V00);
			C0 = _mm_add_ps(C0, V00);
			__m128 C3 = _mm_add_ps(C2, V01);
			C2 = _mm_sub_ps(C2, V01);
			__m128 C5 = _mm_sub_ps(C4, V02);
			C4 = _mm_add_ps(C4, V02);
			__m128 C7 = _mm_add_ps(C6, V03);
			C6 = _mm_sub_ps(C6, V03);

			C0 = _mm_shuffle_ps(C0, C1, _MM_SHUFFLE(3, 1, 2, 0));
			C2 = _mm_shuffle_ps(C2, C3, _MM_SHUFFLE(3, 1, 2, 0));
			C4 = _mm_shuffle_ps(C4, C5, _MM_SHUFFLE(3, 1, 2, 0));
			C6 = _mm_shuffle_ps(C6, C7, _MM_SHUFFLE(3, 1, 2, 0));
			C0 = SIV3D_PERMUTE_PS(C0, _MM_SHUFFLE(3, 1, 2, 0));
			C2 = SIV3D_PERMUTE_PS(C2, _MM_SHUFFLE(3, 1, 2, 0));
			C4 = SIV3D_PERMUTE_PS(C4, _MM_SHUFFLE(3, 1, 2, 0));
			C6 = SIV3D_PERMUTE_PS(C6, _MM_SHUFFLE(3, 1, 2, 0));

			// Get the determinate
			__m128 vTemp = SIMD::Vector4Dot(C0, MT.r[0]);

			determinant = vTemp;

			vTemp = _mm_div_ps(SIMD::constants::m128_One, vTemp);
			Mat4x4 mResult;
			mResult.r[0] = _mm_mul_ps(C0, vTemp);
			mResult.r[1] = _mm_mul_ps(C2, vTemp);
			mResult.r[2] = _mm_mul_ps(C4, vTemp);
			mResult.r[3] = _mm_mul_ps(C6, vTemp);
			return mResult;
		}

		[[nodiscard]] static float SIV3D_VECTOR_CALL Determinant(Mat4x4 m) noexcept
		{
			static const __m128 sign{ 1.0f, -1.0f, 1.0f, -1.0f };

			using namespace SIMD::constants;
			__m128 V0 = SIMD::Swizzle<SwizzleY, SwizzleX, SwizzleX, SwizzleX>(m.r[2]);
			__m128 V1 = SIMD::Swizzle<SwizzleZ, SwizzleZ, SwizzleY, SwizzleY>(m.r[3]);
			__m128 V2 = SIMD::Swizzle<SwizzleY, SwizzleX, SwizzleX, SwizzleX>(m.r[2]);
			__m128 V3 = SIMD::Swizzle<SwizzleW, SwizzleW, SwizzleW, SwizzleZ>(m.r[3]);
			__m128 V4 = SIMD::Swizzle<SwizzleZ, SwizzleZ, SwizzleY, SwizzleY>(m.r[2]);
			__m128 V5 = SIMD::Swizzle<SwizzleW, SwizzleW, SwizzleW, SwizzleZ>(m.r[3]);

			__m128 P0 = SIMD::Multiply(V0, V1);
			__m128 P1 = SIMD::Multiply(V2, V3);
			__m128 P2 = SIMD::Multiply(V4, V5);

			V0 = SIMD::Swizzle<SwizzleZ, SwizzleZ, SwizzleY, SwizzleY>(m.r[2]);
			V1 = SIMD::Swizzle<SwizzleY, SwizzleX, SwizzleX, SwizzleX>(m.r[3]);
			V2 = SIMD::Swizzle<SwizzleW, SwizzleW, SwizzleW, SwizzleZ>(m.r[2]);
			V3 = SIMD::Swizzle<SwizzleY, SwizzleX, SwizzleX, SwizzleX>(m.r[3]);
			V4 = SIMD::Swizzle<SwizzleW, SwizzleW, SwizzleW, SwizzleZ>(m.r[2]);
			V5 = SIMD::Swizzle<SwizzleZ, SwizzleZ, SwizzleY, SwizzleY>(m.r[3]);

			P0 = SIMD::NegativeMultiplySubtract(V0, V1, P0);
			P1 = SIMD::NegativeMultiplySubtract(V2, V3, P1);
			P2 = SIMD::NegativeMultiplySubtract(V4, V5, P2);

			V0 = SIMD::Swizzle<SwizzleW, SwizzleW, SwizzleW, SwizzleZ>(m.r[1]);
			V1 = SIMD::Swizzle<SwizzleZ, SwizzleZ, SwizzleY, SwizzleY>(m.r[1]);
			V2 = SIMD::Swizzle<SwizzleY, SwizzleX, SwizzleX, SwizzleX>(m.r[1]);

			__m128 S = SIMD::Multiply(m.r[0], sign);
			__m128 R = SIMD::Multiply(V0, P0);
			R = SIMD::NegativeMultiplySubtract(V1, P1, R);
			R = SIMD::MultiplyAdd(V2, P2, R);

			return SIMD::GetX(SIMD::Vector4Dot(S, R));
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Translation(float x, float y, float z) noexcept
		{
			return Mat4x4{
				SIMD::constants::m128_MIdentityR0,
				SIMD::constants::m128_MIdentityR1,
				SIMD::constants::m128_MIdentityR2,
				SIMD::Set(x, y, z, 1.0f)
			};
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL Scaling(float sx, float sy, float sz) noexcept
		{
			return Mat4x4{
				SIMD::Set(sx, 0.0f, 0.0f, 0.0f),
				SIMD::Set(0.0f, sy, 0.0f, 0.0f),
				SIMD::Set(0.0f, 0.0f, sz, 0.0f),
				SIMD::constants::m128_MIdentityR3
			};
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL RotationX(float angle) noexcept
		{
			const auto [sinAngle, cosAngle] = SIMD::ScalarSinCos(angle);

			__m128 vSin = _mm_set_ss(sinAngle);
			__m128 vCos = _mm_set_ss(cosAngle);
			// x = 0,y = cos,z = sin, w = 0
			vCos = _mm_shuffle_ps(vCos, vSin, _MM_SHUFFLE(3, 0, 0, 3));

			Mat4x4 mResult;
			mResult.r[0] = SIMD::constants::m128_MIdentityR0;
			mResult.r[1] = vCos;
			// x = 0,y = sin,z = cos, w = 0
			vCos = SIV3D_PERMUTE_PS(vCos, _MM_SHUFFLE(3, 1, 2, 0));
			// x = 0,y = -sin,z = cos, w = 0
			vCos = _mm_mul_ps(vCos, SIMD::constants::m128_NegateY);
			mResult.r[2] = vCos;
			mResult.r[3] = SIMD::constants::m128_MIdentityR3;
			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL RotationY(float angle) noexcept
		{
			const auto [sinAngle, cosAngle] = SIMD::ScalarSinCos(angle);

			__m128 vSin = _mm_set_ss(sinAngle);
			__m128 vCos = _mm_set_ss(cosAngle);
			// x = sin,y = 0,z = cos, w = 0
			vSin = _mm_shuffle_ps(vSin, vCos, _MM_SHUFFLE(3, 0, 3, 0));

			Mat4x4 mResult;
			mResult.r[2] = vSin;
			mResult.r[1] = SIMD::constants::m128_MIdentityR1;
			// x = cos,y = 0,z = sin, w = 0
			vSin = SIV3D_PERMUTE_PS(vSin, _MM_SHUFFLE(3, 0, 1, 2));
			// x = cos,y = 0,z = -sin, w = 0
			vSin = _mm_mul_ps(vSin, SIMD::constants::m128_NegateZ);
			mResult.r[0] = vSin;
			mResult.r[3] = SIMD::constants::m128_MIdentityR3;
			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL RotationZ(float angle) noexcept
		{
			const auto [sinAngle, cosAngle] = SIMD::ScalarSinCos(angle);

			__m128 vSin = _mm_set_ss(sinAngle);
			__m128 vCos = _mm_set_ss(cosAngle);
			// x = cos,y = sin,z = 0, w = 0
			vCos = _mm_unpacklo_ps(vCos, vSin);

			Mat4x4 mResult;
			mResult.r[0] = vCos;
			// x = sin,y = cos,z = 0, w = 0
			vCos = SIV3D_PERMUTE_PS(vCos, _MM_SHUFFLE(3, 2, 0, 1));
			// x = cos,y = -sin,z = 0, w = 0
			vCos = _mm_mul_ps(vCos, SIMD::constants::m128_NegateX);
			mResult.r[1] = vCos;
			mResult.r[2] = SIMD::constants::m128_MIdentityR2;
			mResult.r[3] = SIMD::constants::m128_MIdentityR3;
			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL PerspectiveFovLH_ZO(float fov, float aspectRatio, float nearClip, float farClip) noexcept
		{
			assert(0.0f < nearClip && 0.0f < farClip);
			assert(0.00001f <= aspectRatio);

			const auto [sinFov, cosFov] = SIMD::ScalarSinCos(0.5f * fov);
			const float height = cosFov / sinFov;
			const float width = height / aspectRatio;
			const float fRange = farClip / (farClip - nearClip);

			Mat4x4 mResult;
			mResult.r[0] = SIMD_Float4(width, 0.0f, 0.0f, 0.0f);
			mResult.r[1] = SIMD_Float4(0.0f, height, 0.0f, 0.0f);
			mResult.r[2] = SIMD_Float4(0.0f, 0.0f, fRange, 1.0f);
			mResult.r[3] = SIMD_Float4(0.0f, 0.0f, -fRange * nearClip, 0.0f);

			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL PerspectiveFovLH_NO(float fov, float aspectRatio, float nearClip, float farClip) noexcept
		{
			assert(0.0f < nearClip && 0.0f < farClip);
			assert(0.00001f <= aspectRatio);

			const auto [sinFov, cosFov] = SIMD::ScalarSinCos(0.5f * fov);
			const float height = cosFov / sinFov;
			const float width = height / aspectRatio;
			const float f_n = farClip - nearClip;

			Mat4x4 mResult;
			mResult.r[0] = SIMD_Float4(width, 0.0f, 0.0f, 0.0f);
			mResult.r[1] = SIMD_Float4(0.0f, height, 0.0f, 0.0f);
			mResult.r[2] = SIMD_Float4(0.0f, 0.0f, (farClip + nearClip) / f_n, 1.0f);
			mResult.r[3] = SIMD_Float4(0.0f, 0.0f, (-2 * farClip * nearClip) / f_n, 0.0f);

			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL PerspectiveFovRH_ZO(float fov, float aspectRatio, float nearClip, float farClip) noexcept
		{
			assert(0.0f < nearClip && 0.0f < farClip);
			assert(0.00001f <= aspectRatio);

			const auto [sinFov, cosFov] = SIMD::ScalarSinCos(0.5f * fov);
			const float height = cosFov / sinFov;
			const float width = height / aspectRatio;
			const float fRange = farClip / (farClip - nearClip);

			Mat4x4 mResult;
			mResult.r[0] = SIMD_Float4(width, 0.0f, 0.0f, 0.0f);
			mResult.r[1] = SIMD_Float4(0.0f, height, 0.0f, 0.0f);
			mResult.r[2] = SIMD_Float4(0.0f, 0.0f, -fRange, -1.0f);
			mResult.r[3] = SIMD_Float4(0.0f, 0.0f, -fRange * nearClip, 0.0f);

			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL PerspectiveFovRH_NO(float fov, float aspectRatio, float nearClip, float farClip) noexcept
		{
			assert(0.0f < nearClip && 0.0f < farClip);
			assert(0.00001f <= aspectRatio);

			const auto [sinFov, cosFov] = SIMD::ScalarSinCos(0.5f * fov);
			const float height = cosFov / sinFov;
			const float width = height / aspectRatio;
			const float f_n = farClip - nearClip;

			Mat4x4 mResult;
			mResult.r[0] = SIMD_Float4(width, 0.0f, 0.0f, 0.0f);
			mResult.r[1] = SIMD_Float4(0.0f, height, 0.0f, 0.0f);
			mResult.r[2] = SIMD_Float4(0.0f, 0.0f, -(farClip + nearClip) / f_n, -1.0f);
			mResult.r[3] = SIMD_Float4(0.0f, 0.0f, (-2 * farClip * nearClip) / f_n, 0.0f);

			return mResult;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL LookAtLH(SIMD_Float4 eyePosition, SIMD_Float4 focusPosition, SIMD_Float4 upDirection) noexcept
		{
			const __m128 eyeDirection = SIMD::Subtract(focusPosition.vec, eyePosition.vec);

			assert(!SIMD::Vector3IsZero(eyeDirection));
			assert(!SIMD::Vector3IsInfinite(eyeDirection));
			assert(!SIMD::Vector3IsZero(upDirection));
			assert(!SIMD::Vector3IsInfinite(upDirection));

			const __m128 R2 = SIMD::Vector3Normalize(eyeDirection);

			__m128 R0 = SIMD::Vector3Cross(upDirection, R2);
			R0 = SIMD::Vector3Normalize(R0);

			const __m128 R1 = SIMD::Vector3Cross(R2, R0);
			const __m128 negEyePosition = SIMD::Negate(eyePosition.vec);
			const __m128 D0 = SIMD::Vector3Dot(R0, negEyePosition);
			const __m128 D1 = SIMD::Vector3Dot(R1, negEyePosition);
			const __m128 D2 = SIMD::Vector3Dot(R2, negEyePosition);

			Mat4x4 mResult;
			mResult.r[0] = SIMD::Select(D0, R0, SIMD::constants::m128_Select1110.vec);
			mResult.r[1] = SIMD::Select(D1, R1, SIMD::constants::m128_Select1110.vec);
			mResult.r[2] = SIMD::Select(D2, R2, SIMD::constants::m128_Select1110.vec);
			mResult.r[3] = SIMD::constants::m128_MIdentityR3;

			return Transpose(mResult);
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL LookAtRH(SIMD_Float4 eyePosition, SIMD_Float4 focusPosition, SIMD_Float4 upDirection) noexcept
		{
			const __m128 negEyeDirection = SIMD::Subtract(eyePosition.vec, focusPosition.vec);

			assert(!SIMD::Vector3IsZero(negEyeDirection));
			assert(!SIMD::Vector3IsInfinite(negEyeDirection));
			assert(!SIMD::Vector3IsZero(upDirection));
			assert(!SIMD::Vector3IsInfinite(upDirection));

			const __m128 R2 = SIMD::Vector3Normalize(negEyeDirection);

			__m128 R0 = SIMD::Vector3Cross(upDirection, R2);
			R0 = SIMD::Vector3Normalize(R0);

			const __m128 R1 = SIMD::Vector3Cross(R2, R0);
			const __m128 negEyePosition = SIMD::Negate(eyePosition.vec);
			const __m128 D0 = SIMD::Vector3Dot(R0, negEyePosition);
			const __m128 D1 = SIMD::Vector3Dot(R1, negEyePosition);
			const __m128 D2 = SIMD::Vector3Dot(R2, negEyePosition);

			Mat4x4 mResult;
			mResult.r[0] = SIMD::Select(D0, R0, SIMD::constants::m128_Select1110.vec);
			mResult.r[1] = SIMD::Select(D1, R1, SIMD::constants::m128_Select1110.vec);
			mResult.r[2] = SIMD::Select(D2, R2, SIMD::constants::m128_Select1110.vec);
			mResult.r[3] = SIMD::constants::m128_MIdentityR3;

			return Transpose(mResult);
		}
		//
		//
		///////////////////////////////////////////////////////////////
	};

	[[nodiscard]] inline Mat4x4 SIV3D_VECTOR_CALL operator *(float s, Mat4x4 m) noexcept
	{
		return{ s * m.r[0], s * m.r[1], s * m.r[2], s * m.r[3] };
	}

	void Formatter(FormatData& formatData, const Mat4x4& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Mat4x4& value)
	{
		return output << CharType('(')
			<< value.r[0] << CharType(',') << CharType('\n') << CharType(' ')
			<< value.r[1] << CharType(',') << CharType('\n') << CharType(' ')
			<< value.r[2] << CharType(',') << CharType('\n') << CharType(' ')
			<< value.r[3] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Mat4x4& value)
	{
		CharType unused;
		input >> unused
			>> value.r[0] >> unused
			>> value.r[1] >> unused
			>> value.r[2] >> unused
			>> value.r[3] >> unused;
		return input;
	}

	namespace SIMD
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

		[[nodiscard]] inline SIMD_Float4 SIV3D_VECTOR_CALL Vector3TransformCoord(SIMD_Float4 v, Mat4x4 m)
		{
			const __m128 zzzz = SplatZ(v.vec);
			const __m128 yyyy = SplatY(v.vec);
			const __m128 xxxx = SplatX(v.vec);

			__m128 result = MultiplyAdd(zzzz, m.r[2], m.r[3]);
			result = MultiplyAdd(yyyy, m.r[1], result);
			result = MultiplyAdd(xxxx, m.r[0], result);

			const __m128 wwww = SplatW(result);
			return Divide(result, wwww);
		}

		[[nodiscard]] inline SIMD_Float4 SIV3D_VECTOR_CALL Vector4Transform(SIMD_Float4 v, Mat4x4 m)
		{
			// Splat x,y,z and w
			__m128 vTempX = SplatX(v.vec);
			__m128 vTempY = SplatY(v.vec);
			__m128 vTempZ = SplatZ(v.vec);
			__m128 vTempW = SplatW(v.vec);
			// Mul by the matrix
			vTempX = _mm_mul_ps(vTempX, m.r[0]);
			vTempY = _mm_mul_ps(vTempY, m.r[1]);
			vTempZ = _mm_mul_ps(vTempZ, m.r[2]);
			vTempW = _mm_mul_ps(vTempW, m.r[3]);
			// Add them all together
			vTempX = _mm_add_ps(vTempX, vTempY);
			vTempZ = _mm_add_ps(vTempZ, vTempW);
			vTempX = _mm_add_ps(vTempX, vTempZ);
			return vTempX;
		}

		namespace Internal
		{
			inline Float3* SIV3D_VECTOR_CALL Vector3TransformCoordStream(
				Float3* pOutputStream,
				size_t OutputStride,
				const Float3* pInputStream,
				size_t InputStride,
				size_t VectorCount,
				Mat4x4 m)
			{
				assert(pOutputStream != nullptr);
				assert(pInputStream != nullptr);
				assert(InputStride >= sizeof(Float3));
				assert(OutputStride >= sizeof(Float3));

				auto pInputVector = reinterpret_cast<const uint8_t*>(pInputStream);
				auto pOutputVector = reinterpret_cast<uint8_t*>(pOutputStream);

				const __m128 row0 = m.r[0];
				const __m128 row1 = m.r[1];
				const __m128 row2 = m.r[2];
				const __m128 row3 = m.r[3];

				size_t i = 0;
				size_t four = VectorCount >> 2;
				if (four > 0)
				{
					if (InputStride == sizeof(Float3))
					{
						if (OutputStride == sizeof(Float3))
						{
							if (!(reinterpret_cast<uintptr_t>(pOutputStream) & 0xF))
							{
								// Packed input, aligned & packed output
								for (size_t j = 0; j < four; ++j)
								{
									__m128 V1 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector));
									__m128 L2 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector + 16));
									__m128 L3 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector + 32));
									pInputVector += sizeof(Float3) * 4;

									// Unpack the 4 vectors (.w components are junk)
									SIV3D_3UNPACK3INTO4(V1, L2, L3);

									// Result 1
									__m128 Z = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(2, 2, 2, 2));
									__m128 Y = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(1, 1, 1, 1));
									__m128 X = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(0, 0, 0, 0));

									__m128 vTemp = _mm_mul_ps(Z, row2);
									__m128 vTemp2 = _mm_mul_ps(Y, row1);
									__m128 vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									__m128 W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V1 = _mm_div_ps(vTemp, W);

									// Result 2
									Z = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(2, 2, 2, 2));
									Y = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(1, 1, 1, 1));
									X = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(0, 0, 0, 0));

									vTemp = _mm_mul_ps(Z, row2);
									vTemp2 = _mm_mul_ps(Y, row1);
									vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V2 = _mm_div_ps(vTemp, W);

									// Result 3
									Z = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(2, 2, 2, 2));
									Y = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(1, 1, 1, 1));
									X = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(0, 0, 0, 0));

									vTemp = _mm_mul_ps(Z, row2);
									vTemp2 = _mm_mul_ps(Y, row1);
									vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V3 = _mm_div_ps(vTemp, W);

									// Result 4
									Z = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(2, 2, 2, 2));
									Y = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(1, 1, 1, 1));
									X = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(0, 0, 0, 0));

									vTemp = _mm_mul_ps(Z, row2);
									vTemp2 = _mm_mul_ps(Y, row1);
									vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V4 = _mm_div_ps(vTemp, W);

									// Pack and store the vectors
									SIV3D_3PACK4INTO3(vTemp);
									SIV3D_STREAM_PS(reinterpret_cast<float*>(pOutputVector), V1);
									SIV3D_STREAM_PS(reinterpret_cast<float*>(pOutputVector + 16), vTemp);
									SIV3D_STREAM_PS(reinterpret_cast<float*>(pOutputVector + 32), V3);
									pOutputVector += sizeof(Float3) * 4;
									i += 4;
								}
							}
							else
							{
								// Packed input, unaligned & packed output
								for (size_t j = 0; j < four; ++j)
								{
									__m128 V1 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector));
									__m128 L2 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector + 16));
									__m128 L3 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector + 32));
									pInputVector += sizeof(Float3) * 4;

									// Unpack the 4 vectors (.w components are junk)
									SIV3D_3UNPACK3INTO4(V1, L2, L3);

									// Result 1
									__m128 Z = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(2, 2, 2, 2));
									__m128 Y = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(1, 1, 1, 1));
									__m128 X = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(0, 0, 0, 0));

									__m128 vTemp = _mm_mul_ps(Z, row2);
									__m128 vTemp2 = _mm_mul_ps(Y, row1);
									__m128 vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									__m128 W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V1 = _mm_div_ps(vTemp, W);

									// Result 2
									Z = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(2, 2, 2, 2));
									Y = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(1, 1, 1, 1));
									X = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(0, 0, 0, 0));

									vTemp = _mm_mul_ps(Z, row2);
									vTemp2 = _mm_mul_ps(Y, row1);
									vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V2 = _mm_div_ps(vTemp, W);

									// Result 3
									Z = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(2, 2, 2, 2));
									Y = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(1, 1, 1, 1));
									X = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(0, 0, 0, 0));

									vTemp = _mm_mul_ps(Z, row2);
									vTemp2 = _mm_mul_ps(Y, row1);
									vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V3 = _mm_div_ps(vTemp, W);

									// Result 4
									Z = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(2, 2, 2, 2));
									Y = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(1, 1, 1, 1));
									X = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(0, 0, 0, 0));

									vTemp = _mm_mul_ps(Z, row2);
									vTemp2 = _mm_mul_ps(Y, row1);
									vTemp3 = _mm_mul_ps(X, row0);
									vTemp = _mm_add_ps(vTemp, row3);
									vTemp = _mm_add_ps(vTemp, vTemp2);
									vTemp = _mm_add_ps(vTemp, vTemp3);

									W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

									V4 = _mm_div_ps(vTemp, W);

									// Pack and store the vectors
									SIV3D_3PACK4INTO3(vTemp);
									_mm_storeu_ps(reinterpret_cast<float*>(pOutputVector), V1);
									_mm_storeu_ps(reinterpret_cast<float*>(pOutputVector + 16), vTemp);
									_mm_storeu_ps(reinterpret_cast<float*>(pOutputVector + 32), V3);
									pOutputVector += sizeof(Float3) * 4;
									i += 4;
								}
							}
						}
						else
						{
							// Packed input, unpacked output
							for (size_t j = 0; j < four; ++j)
							{
								__m128 V1 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector));
								__m128 L2 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector + 16));
								__m128 L3 = _mm_loadu_ps(reinterpret_cast<const float*>(pInputVector + 32));
								pInputVector += sizeof(Float3) * 4;

								// Unpack the 4 vectors (.w components are junk)
								SIV3D_3UNPACK3INTO4(V1, L2, L3);

								// Result 1
								__m128 Z = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(2, 2, 2, 2));
								__m128 Y = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(1, 1, 1, 1));
								__m128 X = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(0, 0, 0, 0));

								__m128 vTemp = _mm_mul_ps(Z, row2);
								__m128 vTemp2 = _mm_mul_ps(Y, row1);
								__m128 vTemp3 = _mm_mul_ps(X, row0);
								vTemp = _mm_add_ps(vTemp, row3);
								vTemp = _mm_add_ps(vTemp, vTemp2);
								vTemp = _mm_add_ps(vTemp, vTemp3);

								__m128 W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

								vTemp = _mm_div_ps(vTemp, W);
								SIMD::StoreFloat3(reinterpret_cast<Float3*>(pOutputVector), vTemp);
								pOutputVector += OutputStride;

								// Result 2
								Z = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(2, 2, 2, 2));
								Y = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(1, 1, 1, 1));
								X = SIV3D_PERMUTE_PS(V2, _MM_SHUFFLE(0, 0, 0, 0));

								vTemp = _mm_mul_ps(Z, row2);
								vTemp2 = _mm_mul_ps(Y, row1);
								vTemp3 = _mm_mul_ps(X, row0);
								vTemp = _mm_add_ps(vTemp, row3);
								vTemp = _mm_add_ps(vTemp, vTemp2);
								vTemp = _mm_add_ps(vTemp, vTemp3);

								W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

								vTemp = _mm_div_ps(vTemp, W);
								SIMD::StoreFloat3(reinterpret_cast<Float3*>(pOutputVector), vTemp);
								pOutputVector += OutputStride;

								// Result 3
								Z = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(2, 2, 2, 2));
								Y = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(1, 1, 1, 1));
								X = SIV3D_PERMUTE_PS(V3, _MM_SHUFFLE(0, 0, 0, 0));

								vTemp = _mm_mul_ps(Z, row2);
								vTemp2 = _mm_mul_ps(Y, row1);
								vTemp3 = _mm_mul_ps(X, row0);
								vTemp = _mm_add_ps(vTemp, row3);
								vTemp = _mm_add_ps(vTemp, vTemp2);
								vTemp = _mm_add_ps(vTemp, vTemp3);

								W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

								vTemp = _mm_div_ps(vTemp, W);
								SIMD::StoreFloat3(reinterpret_cast<Float3*>(pOutputVector), vTemp);
								pOutputVector += OutputStride;

								// Result 4
								Z = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(2, 2, 2, 2));
								Y = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(1, 1, 1, 1));
								X = SIV3D_PERMUTE_PS(V4, _MM_SHUFFLE(0, 0, 0, 0));

								vTemp = _mm_mul_ps(Z, row2);
								vTemp2 = _mm_mul_ps(Y, row1);
								vTemp3 = _mm_mul_ps(X, row0);
								vTemp = _mm_add_ps(vTemp, row3);
								vTemp = _mm_add_ps(vTemp, vTemp2);
								vTemp = _mm_add_ps(vTemp, vTemp3);

								W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

								vTemp = _mm_div_ps(vTemp, W);
								SIMD::StoreFloat3(reinterpret_cast<Float3*>(pOutputVector), vTemp);
								pOutputVector += OutputStride;

								i += 4;
							}
						}
					}
				}

				for (; i < VectorCount; i++)
				{
					__m128 V = SIMD::LoadFloat3(reinterpret_cast<const Float3*>(pInputVector));
					pInputVector += InputStride;

					__m128 Z = SIV3D_PERMUTE_PS(V, _MM_SHUFFLE(2, 2, 2, 2));
					__m128 Y = SIV3D_PERMUTE_PS(V, _MM_SHUFFLE(1, 1, 1, 1));
					__m128 X = SIV3D_PERMUTE_PS(V, _MM_SHUFFLE(0, 0, 0, 0));

					__m128 vTemp = _mm_mul_ps(Z, row2);
					__m128 vTemp2 = _mm_mul_ps(Y, row1);
					__m128 vTemp3 = _mm_mul_ps(X, row0);
					vTemp = _mm_add_ps(vTemp, row3);
					vTemp = _mm_add_ps(vTemp, vTemp2);
					vTemp = _mm_add_ps(vTemp, vTemp3);

					__m128 W = SIV3D_PERMUTE_PS(vTemp, _MM_SHUFFLE(3, 3, 3, 3));

					vTemp = _mm_div_ps(vTemp, W);

					SIMD::StoreFloat3(reinterpret_cast<Float3*>(pOutputVector), vTemp);
					pOutputVector += OutputStride;
				}

				SIV3D_SFENCE();

				return pOutputStream;
			}
		}

		inline Float3* SIV3D_VECTOR_CALL Vector3TransformCoordStream(
			Float3* pOutputStream,
			const Float3* pInputStream,
			size_t vertexCount,
			Mat4x4 m)
		{
			return Internal::Vector3TransformCoordStream(
				pOutputStream, sizeof(Float3),
				pInputStream, sizeof(Float3),
				vertexCount, m);
		}

		inline Float3* SIV3D_VECTOR_CALL Vector3TransformCoordStream(
			Float3* pOutputStream,
			const SIMD_Float4* pInputStream,
			size_t vertexCount,
			Mat4x4 m)
		{
			return Internal::Vector3TransformCoordStream(
				pOutputStream, sizeof(Float3),
				reinterpret_cast<const Float3*>(pInputStream), sizeof(SIMD_Float4),
				vertexCount, m);
		}

		[[nodiscard]] inline __m128 SIV3D_VECTOR_CALL QuaternionRotationMatrix(Mat4x4 m)
		{
			static const __m128 XMPMMP{ +1.0f, -1.0f, -1.0f, +1.0f };
			static const __m128 XMMPMP{ -1.0f, +1.0f, -1.0f, +1.0f };
			static const __m128 XMMMPP{ -1.0f, -1.0f, +1.0f, +1.0f };

			__m128 r0 = m.r[0];  // (r00, r01, r02, 0)
			__m128 r1 = m.r[1];  // (r10, r11, r12, 0)
			__m128 r2 = m.r[2];  // (r20, r21, r22, 0)

			// (r00, r00, r00, r00)
			__m128 r00 = SIV3D_PERMUTE_PS(r0, _MM_SHUFFLE(0, 0, 0, 0));
			// (r11, r11, r11, r11)
			__m128 r11 = SIV3D_PERMUTE_PS(r1, _MM_SHUFFLE(1, 1, 1, 1));
			// (r22, r22, r22, r22)
			__m128 r22 = SIV3D_PERMUTE_PS(r2, _MM_SHUFFLE(2, 2, 2, 2));

			// x^2 >= y^2 equivalent to r11 - r00 <= 0
			// (r11 - r00, r11 - r00, r11 - r00, r11 - r00)
			__m128 r11mr00 = _mm_sub_ps(r11, r00);
			__m128 x2gey2 = _mm_cmple_ps(r11mr00, constants::m128_Zero);

			// z^2 >= w^2 equivalent to r11 + r00 <= 0
			// (r11 + r00, r11 + r00, r11 + r00, r11 + r00)
			__m128 r11pr00 = _mm_add_ps(r11, r00);
			__m128 z2gew2 = _mm_cmple_ps(r11pr00, constants::m128_Zero);

			// x^2 + y^2 >= z^2 + w^2 equivalent to r22 <= 0
			__m128 x2py2gez2pw2 = _mm_cmple_ps(r22, constants::m128_Zero);

			// (+r00, -r00, -r00, +r00)
			__m128 t0 = _mm_mul_ps(XMPMMP, r00);

			// (-r11, +r11, -r11, +r11)
			__m128 t1 = _mm_mul_ps(XMMPMP, r11);

			// (-r22, -r22, +r22, +r22)
			__m128 t2 = _mm_mul_ps(XMMMPP, r22);

			// (4*x^2, 4*y^2, 4*z^2, 4*w^2)
			__m128 x2y2z2w2 = _mm_add_ps(t0, t1);
			x2y2z2w2 = _mm_add_ps(t2, x2y2z2w2);
			x2y2z2w2 = _mm_add_ps(x2y2z2w2, constants::m128_One);

			// (r01, r02, r12, r11)
			t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 2, 2, 1));
			// (r10, r10, r20, r21)
			t1 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 0, 0));
			// (r10, r20, r21, r10)
			t1 = SIV3D_PERMUTE_PS(t1, _MM_SHUFFLE(1, 3, 2, 0));
			// (4*x*y, 4*x*z, 4*y*z, unused)
			__m128 xyxzyz = _mm_add_ps(t0, t1);

			// (r21, r20, r10, r10)
			t0 = _mm_shuffle_ps(r2, r1, _MM_SHUFFLE(0, 0, 0, 1));
			// (r12, r12, r02, r01)
			t1 = _mm_shuffle_ps(r1, r0, _MM_SHUFFLE(1, 2, 2, 2));
			// (r12, r02, r01, r12)
			t1 = SIV3D_PERMUTE_PS(t1, _MM_SHUFFLE(1, 3, 2, 0));
			// (4*x*w, 4*y*w, 4*z*w, unused)
			__m128 xwywzw = _mm_sub_ps(t0, t1);
			xwywzw = _mm_mul_ps(XMMPMP, xwywzw);

			// (4*x^2, 4*y^2, 4*x*y, unused)
			t0 = _mm_shuffle_ps(x2y2z2w2, xyxzyz, _MM_SHUFFLE(0, 0, 1, 0));
			// (4*z^2, 4*w^2, 4*z*w, unused)
			t1 = _mm_shuffle_ps(x2y2z2w2, xwywzw, _MM_SHUFFLE(0, 2, 3, 2));
			// (4*x*z, 4*y*z, 4*x*w, 4*y*w)
			t2 = _mm_shuffle_ps(xyxzyz, xwywzw, _MM_SHUFFLE(1, 0, 2, 1));

			// (4*x*x, 4*x*y, 4*x*z, 4*x*w)
			__m128 tensor0 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(2, 0, 2, 0));
			// (4*y*x, 4*y*y, 4*y*z, 4*y*w)
			__m128 tensor1 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(3, 1, 1, 2));
			// (4*z*x, 4*z*y, 4*z*z, 4*z*w)
			__m128 tensor2 = _mm_shuffle_ps(t2, t1, _MM_SHUFFLE(2, 0, 1, 0));
			// (4*w*x, 4*w*y, 4*w*z, 4*w*w)
			__m128 tensor3 = _mm_shuffle_ps(t2, t1, _MM_SHUFFLE(1, 2, 3, 2));

			// Select the row of the tensor-product matrix that has the largest
			// magnitude.
			t0 = _mm_and_ps(x2gey2, tensor0);
			t1 = _mm_andnot_ps(x2gey2, tensor1);
			t0 = _mm_or_ps(t0, t1);
			t1 = _mm_and_ps(z2gew2, tensor2);
			t2 = _mm_andnot_ps(z2gew2, tensor3);
			t1 = _mm_or_ps(t1, t2);
			t0 = _mm_and_ps(x2py2gez2pw2, t0);
			t1 = _mm_andnot_ps(x2py2gez2pw2, t1);
			t2 = _mm_or_ps(t0, t1);

			// Normalize the row.  No division by zero is possible because the
			// quaternion is unit-length (and the row is a nonzero multiple of
			// the quaternion).
			t0 = Vector4Length(t2);
			return _mm_div_ps(t2, t0);
		}

		[[nodiscard]] inline Mat4x4 SIV3D_VECTOR_CALL MatrixRotationQuaternion(__m128 quaternion)
		{
			static const __m128 Constant1110{ 1.0f, 1.0f, 1.0f, 0.0f };

			__m128 Q0 = _mm_add_ps(quaternion, quaternion);
			__m128 Q1 = _mm_mul_ps(quaternion, Q0);

			__m128 V0 = SIV3D_PERMUTE_PS(Q1, _MM_SHUFFLE(3, 0, 0, 1));
			V0 = _mm_and_ps(V0, constants::m128_Mask3.vec);
			__m128 V1 = SIV3D_PERMUTE_PS(Q1, _MM_SHUFFLE(3, 1, 2, 2));
			V1 = _mm_and_ps(V1, constants::m128_Mask3.vec);
			__m128 R0 = _mm_sub_ps(Constant1110, V0);
			R0 = _mm_sub_ps(R0, V1);

			V0 = SIV3D_PERMUTE_PS(quaternion, _MM_SHUFFLE(3, 1, 0, 0));
			V1 = SIV3D_PERMUTE_PS(Q0, _MM_SHUFFLE(3, 2, 1, 2));
			V0 = _mm_mul_ps(V0, V1);

			V1 = SIV3D_PERMUTE_PS(quaternion, _MM_SHUFFLE(3, 3, 3, 3));
			__m128 V2 = SIV3D_PERMUTE_PS(Q0, _MM_SHUFFLE(3, 0, 2, 1));
			V1 = _mm_mul_ps(V1, V2);

			__m128 R1 = _mm_add_ps(V0, V1);
			__m128 R2 = _mm_sub_ps(V0, V1);

			V0 = _mm_shuffle_ps(R1, R2, _MM_SHUFFLE(1, 0, 2, 1));
			V0 = SIV3D_PERMUTE_PS(V0, _MM_SHUFFLE(1, 3, 2, 0));
			V1 = _mm_shuffle_ps(R1, R2, _MM_SHUFFLE(2, 2, 0, 0));
			V1 = SIV3D_PERMUTE_PS(V1, _MM_SHUFFLE(2, 0, 2, 0));

			Q1 = _mm_shuffle_ps(R0, V0, _MM_SHUFFLE(1, 0, 3, 0));
			Q1 = SIV3D_PERMUTE_PS(Q1, _MM_SHUFFLE(1, 3, 2, 0));

			Mat4x4 M;
			M.r[0] = Q1;

			Q1 = _mm_shuffle_ps(R0, V0, _MM_SHUFFLE(3, 2, 3, 1));
			Q1 = SIV3D_PERMUTE_PS(Q1, _MM_SHUFFLE(1, 3, 0, 2));
			M.r[1] = Q1;

			Q1 = _mm_shuffle_ps(V1, R0, _MM_SHUFFLE(3, 2, 1, 0));
			M.r[2] = Q1;
			M.r[3] = constants::m128_MIdentityR3;
			return M;
		}

		//
		//
		///////////////////////////////////////////////////////////////
	}
}
