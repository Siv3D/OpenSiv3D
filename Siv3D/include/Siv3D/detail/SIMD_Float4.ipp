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

	inline SIMD_Float4::SIMD_Float4(const Float4 v) noexcept
		: vec{ DirectX::XMVectorSet(v.x, v.y, v.z, v.w) } {}

	inline SIMD_Float4::SIMD_Float4(const Vec4 v) noexcept
		: vec{ DirectX::XMVectorSet(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z), static_cast<float>(v.w)) } {}

	inline SIMD_Float4::SIMD_Float4(const aligned_float4 _vec) noexcept
		: vec{ _vec } {}

	inline SIMD_Float4& SIMD_Float4::operator =(const aligned_float4 other) noexcept
	{
		vec = other;

		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::operator =(const Float3 other) noexcept
	{
		vec = DirectX::XMVectorSet(static_cast<float>(other.x), static_cast<float>(other.y), static_cast<float>(other.z), 0.0f);

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

	inline SIMD_Float4 SIMD_Float4::operator +(const SIMD_Float4 v) const noexcept
	{
		return DirectX::XMVectorAdd(vec, v);
	}

	inline SIMD_Float4 SIMD_Float4::operator -(const SIMD_Float4 v) const noexcept
	{
		return DirectX::XMVectorSubtract(vec, v);
	}

	inline SIMD_Float4 SIMD_Float4::operator *(const float s) const noexcept
	{
		return DirectX::XMVectorScale(vec, s);
	}

	inline SIMD_Float4 SIMD_Float4::operator *(const SIMD_Float4 v) const noexcept
	{
		return DirectX::XMVectorMultiply(vec, v);
	}

	inline SIMD_Float4 SIMD_Float4::operator /(const float s) const noexcept
	{
		return DirectX::XMVectorDivide(vec, DirectX::XMVectorReplicate(s));
	}

	inline SIMD_Float4 SIMD_Float4::operator /(const SIMD_Float4 v) const noexcept
	{
		return DirectX::XMVectorDivide(vec, v);
	}

	inline SIMD_Float4& SIMD_Float4::operator +=(const SIMD_Float4 v) noexcept
	{
		vec = DirectX::XMVectorAdd(vec, v);

		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::operator -=(const SIMD_Float4 v) noexcept
	{
		vec = DirectX::XMVectorSubtract(vec, v);

		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::operator *=(const float s) noexcept
	{
		vec = DirectX::XMVectorScale(vec, s);

		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::operator *=(const SIMD_Float4 v) noexcept
	{
		vec = DirectX::XMVectorMultiply(vec, v);

		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::operator /=(const float s) noexcept
	{
		vec = DirectX::XMVectorDivide(vec, DirectX::XMVectorReplicate(s));

		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::operator /=(const SIMD_Float4 v) noexcept
	{
		vec = DirectX::XMVectorDivide(vec, v);

		return *this;
	}

	inline SIMD_Float4::operator aligned_float4() const noexcept
	{
		return vec;
	}

	inline SIMD_Float4::operator Float3() const noexcept
	{
		DirectX::XMFLOAT4A t;

		DirectX::XMStoreFloat4A(&t, vec);

		return{ t.x, t.y, t.z };
	}

	inline Float4 SIMD_Float4::toFloat4() const noexcept
	{
		DirectX::XMFLOAT4A t;

		DirectX::XMStoreFloat4A(&t, vec);

		return{ t.x, t.y, t.z, t.w };
	}

	inline float SIMD_Float4::elem(const size_t index) const noexcept
	{
		return DirectX::XMVectorGetByIndex(vec, index);
	}

	inline float SIMD_Float4::getX() const noexcept
	{
		return DirectX::XMVectorGetX(vec);
	}

	inline float SIMD_Float4::getY() const noexcept
	{
		return DirectX::XMVectorGetY(vec);
	}

	inline float SIMD_Float4::getZ() const noexcept
	{
		return DirectX::XMVectorGetZ(vec);
	}

	inline float SIMD_Float4::getW() const noexcept
	{
		return DirectX::XMVectorGetW(vec);
	}

	inline SIMD_Float4& SIMD_Float4::setX(const float x) noexcept
	{
		vec = DirectX::XMVectorSetX(vec, x);
		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::setY(const float y) noexcept
	{
		vec = DirectX::XMVectorSetY(vec, y);
		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::setZ(const float z) noexcept
	{
		vec = DirectX::XMVectorSetZ(vec, z);
		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::setW(const float w) noexcept
	{
		vec = DirectX::XMVectorSetW(vec, w);
		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::set(const float x, const float y, const float z, const float w) noexcept
	{
		vec = DirectX::XMVectorSet(x, y, z, w);
		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::set(const Float2 xy, const Float2 zw) noexcept
	{
		vec = DirectX::XMVectorSet(xy.x, xy.y, zw.x, zw.y);
		return *this;
	}

	inline SIMD_Float4& SIMD_Float4::set(const Float3 xyz, const float w) noexcept
	{
		vec = DirectX::XMVectorSet(xyz.x, xyz.y, xyz.z, w);
		return *this;
	}

	inline bool SIMD_Float4::isZero() const noexcept
	{
		return DirectX::XMVector4Equal(vec, DirectX::XMVectorZero());
	}

	inline bool SIMD_Float4::hasNaN() const noexcept
	{
		return DirectX::XMVector4IsNaN(vec);
	}

	inline bool SIMD_Float4::hasInf() const noexcept
	{
		return DirectX::XMVector4IsInfinite(vec);
	}

	inline float SIMD_Float4::length() const noexcept
	{
		return DirectX::XMVectorGetX(DirectX::XMVector4Length(vec));
	}

	inline float SIMD_Float4::lengthSq() const noexcept
	{
		return DirectX::XMVectorGetX(DirectX::XMVector4LengthSq(vec));
	}

	inline SIMD_Float4 SIMD_Float4::reciprocal() const noexcept
	{
		return DirectX::XMVectorReciprocal(vec);
	}

	inline SIMD_Float4 SIMD_Float4::fastReciprocal() const noexcept
	{
		return DirectX::XMVectorReciprocalEst(vec);
	}

	inline SIMD_Float4 SIMD_Float4::sqrt() const noexcept
	{
		return DirectX::XMVectorSqrt(vec);
	}
	inline SIMD_Float4 SIMD_Float4::fastSqrt() const noexcept
	{
		return DirectX::XMVectorSqrtEst(vec);
	}

	inline SIMD_Float4 SIMD_Float4::rsqrt() const noexcept
	{
		return DirectX::XMVectorReciprocalSqrt(vec);
	}

	inline SIMD_Float4 SIMD_Float4::fastRsqrt() const noexcept
	{
		return DirectX::XMVectorReciprocalSqrtEst(vec);
	}

	inline SIMD_Float4& SIMD_Float4::normalize() noexcept
	{
		vec = DirectX::XMVector4Normalize(vec);

		return *this;
	}

	inline SIMD_Float4 SIMD_Float4::normalized() const noexcept
	{
		return DirectX::XMVector4Normalize(vec);
	}

	inline SIMD_Float4 SIMD_Float4::lerp(SIMD_Float4 other, const float f) const noexcept
	{
		return DirectX::XMVectorLerp(vec, other.vec, static_cast<float>(f));
	}

	inline Float2 SIMD_Float4::xy() const noexcept
	{
		DirectX::XMFLOAT4A t;

		DirectX::XMStoreFloat4A(&t, vec);

		return{ t.x, t.y };
	}

	inline Float3 SIMD_Float4::xyz() const noexcept
	{
		DirectX::XMFLOAT4A t;

		DirectX::XMStoreFloat4A(&t, vec);

		return{ t.x, t.y, t.z };
	}

	inline SIMD_Float4 SIMD_Float4::Zero() noexcept
	{
		return DirectX::XMVectorZero();
	}

	inline SIMD_Float4 SIMD_Float4::One() noexcept
	{
		return DirectX::XMVectorReplicate(1.0f);
	}

	inline SIMD_Float4 SIMD_Float4::All(const float value) noexcept
	{
		return DirectX::XMVectorReplicate(value);
	}
}
