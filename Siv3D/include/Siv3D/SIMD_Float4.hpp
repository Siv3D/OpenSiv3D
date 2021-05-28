//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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

		template <class U>
		SIV3D_NODISCARD_CXX20
		SIMD_Float4(Float4 v) noexcept;

		template <class U>
		SIV3D_NODISCARD_CXX20
		SIMD_Float4(Vec4 v) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr SIMD_Float4(aligned_float4 _vec) noexcept;

		SIMD_Float4& operator =(const SIMD_Float4&) = default;

		SIMD_Float4& SIV3D_VECTOR_CALL operator =(aligned_float4 other) noexcept;

		[[nodiscard]]
		constexpr SIMD_Float4 SIV3D_VECTOR_CALL operator +() const noexcept;

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
		friend SIMD_Float4 SIV3D_VECTOR_CALL operator *(float s, const SIMD_Float4& v) noexcept
		{
			return (v * s);
		}

		[[nodiscard]]
		constexpr SIV3D_VECTOR_CALL operator aligned_float4() const noexcept;

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

		void SIV3D_VECTOR_CALL setX(float x) noexcept;

		void SIV3D_VECTOR_CALL setY(float y) noexcept;

		void SIV3D_VECTOR_CALL setZ(float z) noexcept;

		void SIV3D_VECTOR_CALL setW(float w) noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL isZero() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasNaN() const noexcept;

		[[nodiscard]]
		float SIV3D_VECTOR_CALL length() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL fastReciprocal() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL reciprocal() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL sqrt() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL fastRsqrt() const noexcept;

		[[nodiscard]]
		SIMD_Float4 SIV3D_VECTOR_CALL rsqrt() const noexcept;

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
	};
}

# include "detail/SIMD_Float4.ipp"
