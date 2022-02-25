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
	inline Quaternion::Quaternion(const float x, const float y, const float z, const float w) noexcept
		: value{ x, y, z, w } {}

	template <class X, class Y, class Z, class W>
	inline Quaternion::Quaternion(const X x, const Y y, const Z z, const W w) noexcept
		: value{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w) } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Quaternion::Quaternion(const Float3& axis, const Arithmetic angle) noexcept
		: value{ DirectX::XMQuaternionRotationNormal(SIMD_Float4{ axis, 0.0f }, static_cast<float>(angle)) } {}

	inline Quaternion::Quaternion(const Float4 _vec) noexcept
		: value{ _vec } {}

	inline Quaternion::Quaternion(const aligned_float4 _vec) noexcept
		: value{ _vec } {}

	inline Quaternion& Quaternion::operator =(const aligned_float4 other) noexcept
	{
		value = other;
		return *this;
	}

	inline Quaternion& Quaternion::operator =(const SIMD_Float4 other) noexcept
	{
		value = other;
		return *this;
	}

	inline Quaternion Quaternion::operator *(const Quaternion q) const noexcept
	{
		return DirectX::XMQuaternionMultiply(value, q);
	}

	inline Quaternion& Quaternion::operator *=(const Quaternion q) noexcept
	{
		value = DirectX::XMQuaternionMultiply(value, q);

		return *this;
	}

	inline Float3 Quaternion::operator *(const Float3 v) const noexcept
	{
		const SIMD_Float4 result = DirectX::XMVector3Rotate(SIMD_Float4{ v, 0.0f }, value);

		return result.xyz();
	}

	inline Quaternion::operator aligned_float4() const noexcept
	{
		return value.vec;
	}

	inline Float4 Quaternion::toFloat4() const noexcept
	{
		return value.toFloat4();
	}

	inline float Quaternion::elem(const size_t index) const noexcept
	{
		return DirectX::XMVectorGetByIndex(value, index);
	}

	inline float Quaternion::getX() const noexcept
	{
		return DirectX::XMVectorGetX(value);
	}

	inline float Quaternion::getY() const noexcept
	{
		return DirectX::XMVectorGetY(value);
	}

	inline float Quaternion::getZ() const noexcept
	{
		return DirectX::XMVectorGetZ(value);
	}

	inline float Quaternion::getW() const noexcept
	{
		return DirectX::XMVectorGetW(value);
	}

	inline void Quaternion::setX(const float x) noexcept
	{
		value = DirectX::XMVectorSetX(value, x);
	}

	inline void Quaternion::setY(const float y) noexcept
	{
		value = DirectX::XMVectorSetY(value, y);
	}

	inline void Quaternion::setZ(const float z) noexcept
	{
		value = DirectX::XMVectorSetZ(value, z);
	}

	inline void Quaternion::setW(const float w) noexcept
	{
		value = DirectX::XMVectorSetW(value, w);
	}

	inline void Quaternion::set(const float x, const float y, const float z, const float w) noexcept
	{
		value = DirectX::XMVectorSet(x, y, z, w);
	}

	inline bool Quaternion::isZero() const noexcept
	{
		return DirectX::XMVector4Equal(value, DirectX::XMVectorZero());
	}

	inline bool Quaternion::isIdentity() const noexcept
	{
		return DirectX::XMQuaternionIsIdentity(value);
	}

	inline bool Quaternion::hasNaN() const noexcept
	{
		return DirectX::XMVector4IsNaN(value);
	}

	inline bool Quaternion::hasInf() const noexcept
	{
		return DirectX::XMVector4IsInfinite(value);
	}

	inline Quaternion& Quaternion::normalize() noexcept
	{
		value = DirectX::XMQuaternionNormalize(value);

		return *this;
	}

	inline Quaternion Quaternion::normalized() const noexcept
	{
		return DirectX::XMQuaternionNormalize(value);
	}

	inline Quaternion& Quaternion::conjugate() noexcept
	{
		value = DirectX::XMQuaternionConjugate(value);

		return *this;
	}

	inline Quaternion Quaternion::conjugated() const noexcept
	{
		return DirectX::XMQuaternionConjugate(value);
	}

	inline Quaternion Quaternion::inverse() const noexcept
	{
		return DirectX::XMQuaternionInverse(value);
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline Quaternion Quaternion::slerp(const Quaternion q, const Float t) const noexcept
	{
		return DirectX::XMQuaternionSlerp(value, q, static_cast<float>(t));
	}

	inline std::pair<Float3, float> Quaternion::toAxisAngle() const noexcept
	{
		SIMD_Float4 axis;
		float angle;
		DirectX::XMQuaternionToAxisAngle(&axis.vec, &angle, value);

		return{ axis.xyz(), angle };
	}

	inline Quaternion Quaternion::Identity() noexcept
	{
		return DirectX::XMQuaternionIdentity();
	}

	inline Quaternion Quaternion::Zero() noexcept
	{
		return DirectX::XMVectorZero();
	}

	inline Quaternion Quaternion::FromUnitVectors(const Vec3& from, const Vec3& to) noexcept
	{
		Vec4 q;

		if (const double r = (from.dot(to) + 1.0); 
			(r < 0.0000001))
		{
			if (std::abs(from.z) < std::abs(from.x))
			{
				q.x = -from.y;
				q.y = from.x;
				q.z = 0.0;
				q.w = 0.0;
			}
			else
			{
				q.x = 0.0;
				q.y = -from.z;
				q.z = from.y;
				q.w = 0.0;
			}
		}
		else
		{
			q = Vec4{ from.cross(to), r };
		}

		return Quaternion{ q.normalized() };
	}

	template <class X, class Y, class Z>
	inline Quaternion Quaternion::RollPitchYaw(const X pitch, const Y yaw, const Z roll) noexcept
	{
		return DirectX::XMQuaternionRotationRollPitchYaw(static_cast<float>(pitch), static_cast<float>(yaw), static_cast<float>(roll));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Quaternion Quaternion::RotationNormal(const Float3 normalAxis, const Arithmetic angle) noexcept
	{
		return DirectX::XMQuaternionRotationNormal(SIMD_Float4{ normalAxis, 0.0f }, static_cast<float>(angle));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Quaternion Quaternion::RotationAxis(const Float3 axis, const Arithmetic angle) noexcept
	{
		return DirectX::XMQuaternionRotationAxis(SIMD_Float4{ axis, 0.0f }, static_cast<float>(angle));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Quaternion Quaternion::RotateX(const Arithmetic angle) noexcept
	{
		return DirectX::XMQuaternionRotationNormal(DirectX::g_XMIdentityR0, static_cast<float>(angle));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Quaternion Quaternion::RotateY(const Arithmetic angle) noexcept
	{
		return DirectX::XMQuaternionRotationNormal(DirectX::g_XMIdentityR1, static_cast<float>(angle));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Quaternion Quaternion::RotateZ(const Arithmetic angle) noexcept
	{
		return DirectX::XMQuaternionRotationNormal(DirectX::g_XMIdentityR2, static_cast<float>(angle));
	}
}
