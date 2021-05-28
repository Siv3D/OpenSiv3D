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

namespace s3d
{
	inline SIMD_Float4::SIMD_Float4(const float xyzw) noexcept
		: vec{ DirectX::XMVectorReplicate(xyzw) } {}

	inline SIMD_Float4::SIMD_Float4(const float x, const float y, const float z, const float w) noexcept
		: vec{ DirectX::XMVectorSet(x, y, z, w) } {}

	template <class X, class Y, class Z, class W>
	inline SIMD_Float4::SIMD_Float4(const X x, const Y y, const Z z, const W w) noexcept
		: vec{ DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)) } {}

	template <class U, class V, class Z, class W>
	inline SIMD_Float4::SIMD_Float4(const Vector2D<U>& xy, const Z z, const W w) noexcept
		: vec{ DirectX::XMVectorSet(static_cast<float>(xy.x), static_cast<float>(xy.y), static_cast<float>(z), static_cast<float>(w)) } {}

	template <class U, class V>
	inline SIMD_Float4::SIMD_Float4(const Vector2D<U>& xy, const Vector2D<V>& zw) noexcept
		: vec{ DirectX::XMVectorSet(static_cast<float>(xy.x), static_cast<float>(xy.y), static_cast<float>(zw.x), static_cast<float>(zw.y)) } {}

	template <class U, class W>
	inline SIMD_Float4::SIMD_Float4(const Vector3D<U>& xyz, const W w) noexcept
		: vec{ DirectX::XMVectorSet(static_cast<float>(xyz.x), static_cast<float>(xyz.y), static_cast<float>(xyz.z), static_cast<float>(w)) } {}

	template <class U>
	inline SIMD_Float4::SIMD_Float4(const Float4 v) noexcept
		: vec{ DirectX::XMVectorSet(v.x, v.y, v.z, v.w) } {}

	template <class U>
	inline SIMD_Float4::SIMD_Float4(const Vec4 v) noexcept
		: vec{ DirectX::XMVectorSet(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z), static_cast<float>(v.w)) } {}

	inline SIMD_Float4::SIMD_Float4(const aligned_float4 _vec) noexcept
		: vec{ _vec } {}

	inline SIMD_Float4& SIMD_Float4::operator =(const aligned_float4 other) noexcept
	{
		vec = other;
		
		return *this;
	}

	inline SIMD_Float4 SIMD_Float4::operator +() const noexcept
	{
		return vec;
	}

	inline SIMD_Float4 SIMD_Float4::operator -() const noexcept
	{
		return DirectX::XMVectorNegate(vec);
	}

	/*
	SIMD_Float4 operator +(SIMD_Float4 v) const noexcept;

	SIMD_Float4 operator -(SIMD_Float4 v) const noexcept;

	SIMD_Float4 operator *(float s) const noexcept;

	SIMD_Float4 operator *(SIMD_Float4 v) const noexcept;

	SIMD_Float4 operator /(float s) const noexcept;

	SIMD_Float4 operator /(SIMD_Float4 v) const noexcept;

	SIMD_Float4& operator +=(SIMD_Float4 v) noexcept;

	SIMD_Float4& operator -=(SIMD_Float4 v) noexcept;

	SIMD_Float4& operator *=(float s) noexcept;

	SIMD_Float4& operator *=(SIMD_Float4 v) noexcept;

	SIMD_Float4& operator /=(float s) noexcept;

	SIMD_Float4& operator /=(SIMD_Float4 v) noexcept;

	constexpr operator aligned_float4() const noexcept;

	Float4 toFloat4() const noexcept;

	float elem(size_t index) const noexcept;

	float getX() const noexcept;

	float getY() const noexcept;

	float getZ() const noexcept;

	float getW() const noexcept;

	void setX(float x) noexcept;

	void setY(float y) noexcept;

	void setZ(float z) noexcept;

	void setW(float w) noexcept;

	bool isZero() const noexcept;

	bool hasNaN() const noexcept;

	float length() const noexcept;

	SIMD_Float4 fastReciprocal() const noexcept;

	SIMD_Float4 reciprocal() const noexcept;

	SIMD_Float4 sqrt() const noexcept;

	SIMD_Float4 fastRsqrt() const noexcept;

	SIMD_Float4 rsqrt() const noexcept;

	Float2 xy() const noexcept;

	Float3 xyz() const noexcept;

	SIMD_Float4 Zero() noexcept;

	SIMD_Float4 One() noexcept;

	SIMD_Float4 All(float value = 1.0f) noexcept;
	*/
}
