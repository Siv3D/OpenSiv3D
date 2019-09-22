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
				{ m30, m31, m32, m33 }} {}

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

		[[nodiscard]] static Mat4x4 Identity() noexcept
		{
			return Mat4x4{
				SIMD::constants::m128_MIdentityR0,
				SIMD::constants::m128_MIdentityR1,
				SIMD::constants::m128_MIdentityR2,
				SIMD::constants::m128_MIdentityR3
			};
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

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL PerspectiveFovLH(float fov, float aspectRatio, float nearClip, float farClip) noexcept
		{
			assert(0.0f < nearClip && 0.0f < farClip);
			assert(0.00001f <= aspectRatio);

			const float sinFov = std::sin(0.5f * fov);
			const float cosFov = std::cos(0.5f * fov);

			const float height = cosFov / sinFov;
			const float width = height / aspectRatio;
			const float fRange = farClip / (farClip - nearClip);

			Mat4x4 m;
			m.r[0] = SIMD_Float4(width, 0.0f, 0.0f, 0.0f);
			m.r[1] = SIMD_Float4(0.0f, height, 0.0f, 0.0f);
			m.r[2] = SIMD_Float4(0.0f, 0.0f, fRange, 1.0f);
			m.r[3] = SIMD_Float4(0.0f, 0.0f, -fRange * nearClip, 0.0f);

			return m;
		}

		[[nodiscard]] static Mat4x4 SIV3D_VECTOR_CALL LookAtLH(SIMD_Float4 eyePosition, SIMD_Float4 focusPosition, SIMD_Float4 upDirection) noexcept
		{
			const __m128 eyeDirection = focusPosition - eyePosition;

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
		//
		//
		///////////////////////////////////////////////////////////////
	}
}
