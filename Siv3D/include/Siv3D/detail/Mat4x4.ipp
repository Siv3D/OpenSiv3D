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
	inline Mat4x4::Mat4x4(const DirectX::XMMATRIX m) noexcept
		: value{ m } {}

	inline Mat4x4::Mat4x4(const SIMD_Float4 r0, const SIMD_Float4 r1, const SIMD_Float4 r2, const SIMD_Float4 r3) noexcept
		: value{ r0, r1, r2, r3 } {}

	inline Mat4x4::Mat4x4(const Float4 r0, const Float4 r1, const Float4 r2, const Float4 r3) noexcept
		: Mat4x4{ SIMD_Float4{ r0 }, SIMD_Float4{ r1 }, SIMD_Float4{ r2 }, SIMD_Float4{ r3 } } {}

	inline Mat4x4::Mat4x4(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23,
		const float m30, const float m31, const float m32, const float m33) noexcept
		: value{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 } {}

	inline Mat4x4::Mat4x4(const Quaternion q) noexcept
		: value{ DirectX::XMMatrixRotationQuaternion(q) } {}

	inline Mat4x4 Mat4x4::operator +() const noexcept
	{
		return *this;
	}

	inline Mat4x4 Mat4x4::operator -() const noexcept
	{
		return -value;
	}

	inline Mat4x4 Mat4x4::operator +(const Mat4x4 m) const noexcept
	{
		return (value + m.value);
	}

	inline Mat4x4 Mat4x4::operator -(const Mat4x4 m) const noexcept
	{
		return (value - m.value);
	}

	inline Mat4x4 Mat4x4::operator *(const float s) const noexcept
	{
		return (value * s);
	}

	inline Mat4x4 Mat4x4::operator *(const Mat4x4 m) const noexcept
	{
		return (value * m.value);
	}

	inline Mat4x4 Mat4x4::operator /(const float s) const noexcept
	{
		return (value / s);
	}

	inline Mat4x4& Mat4x4::operator +=(const Mat4x4 m) noexcept
	{
		value += m.value;

		return *this;
	}

	inline Mat4x4& Mat4x4::operator -=(const Mat4x4 m) noexcept
	{
		value -= m.value;

		return *this;
	}

	inline Mat4x4& Mat4x4::operator *=(const float s) noexcept
	{
		value *= s;

		return *this;
	}

	inline Mat4x4& Mat4x4::operator *=(const Mat4x4 m) noexcept
	{
		value *= m.value;

		return *this;
	}

	inline Mat4x4& Mat4x4::operator /=(const float s) noexcept
	{
		value /= s;

		return *this;
	}

	inline Mat4x4::operator DirectX::XMMATRIX() const noexcept
	{
		return value;
	}

	inline bool Mat4x4::hasNaN() const noexcept
	{
		return DirectX::XMMatrixIsNaN(value);
	}
	 
	inline bool Mat4x4::isIdentity() const noexcept
	{
		return DirectX::XMMatrixIsIdentity(value);
	}

	inline bool Mat4x4::decompose(Float3& scale, Quaternion& quaternion, Float3& translate) const noexcept
	{
		SIMD_Float4 s, t;
		
		const bool result = DirectX::XMMatrixDecompose(&s.vec, &quaternion.value.vec, &t.vec, value);
		
		scale = s.xyz();
		
		translate = t.xyz();

		return result;
	}
	 
	inline Mat4x4 Mat4x4::transposed() const noexcept
	{
		return DirectX::XMMatrixTranspose(value);
	}
	 
	inline Mat4x4 Mat4x4::inverse() const noexcept
	{
		return DirectX::XMMatrixInverse(nullptr, value);
	}

	inline Mat4x4 Mat4x4::inverse(float& determinant) const noexcept
	{
		SIMD_Float4 det;

		const auto result = DirectX::XMMatrixInverse(&det.vec, value);

		determinant = det.getX();

		return result;
	}

	inline float Mat4x4::determinant() const noexcept
	{
		return DirectX::XMVectorGetX(DirectX::XMMatrixDeterminant(value));
	}

	template<class X, class Y, class Z>
	inline Mat4x4 Mat4x4::translated(const X x, const Y y, const Z z) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixTranslation(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)));
	}

	inline Mat4x4 Mat4x4::translated(const Float3 v) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixTranslation(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z)));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::scaled(const Arithmetic s) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(static_cast<float>(s))));
	}

	inline Mat4x4 Mat4x4::scaled(const Float3 s) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixScaling(static_cast<float>(s.x), static_cast<float>(s.y), static_cast<float>(s.z)));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::rotatedX(const Arithmetic angle) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixRotationX(static_cast<float>(angle)));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::rotatedY(const Arithmetic angle) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixRotationY(static_cast<float>(angle)));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::rotatedZ(const Arithmetic angle) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixRotationZ(static_cast<float>(angle)));
	}

	template<class X, class Y, class Z>
	inline Mat4x4 Mat4x4::rollPitchYaw(const X pitch, const Y yaw, const Z roll) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(pitch), static_cast<float>(yaw), static_cast<float>(roll)));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::rotated(const Float3 axis, const Arithmetic angle) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixRotationNormal(SIMD_Float4{ axis, 0.0f }, static_cast<float>(angle)));
	}
	 
	inline Mat4x4 Mat4x4::rotated(const Quaternion quaternion) const noexcept
	{
		return DirectX::XMMatrixMultiply(value,
			DirectX::XMMatrixRotationQuaternion(quaternion));
	}

	inline Float3 Mat4x4::transformPoint(const Float3 pos) const noexcept
	{
		return SIMD_Float4{ DirectX::XMVector3TransformCoord(SIMD_Float4{ pos, 0.0f }, value) }.xyz();
	}

	inline void Mat4x4::transformPoints(Float3* pOutputStream, const Float3* pInputStream, const size_t vectorCount) const noexcept
	{
		return transformPoints(pOutputStream, sizeof(Float3), pInputStream, sizeof(Float3), vectorCount);
	}

	inline void Mat4x4::transformPoints(Float3* pOutputStream, const size_t outputStrideBytes,
		const Float3* pInputStream, const size_t inputStrideBytes, const size_t vectorCount) const noexcept
	{
		DirectX::XMVector3TransformCoordStream(
			static_cast<DirectX::XMFLOAT3*>(static_cast<void*>(pOutputStream)),
			outputStrideBytes,
			static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(pInputStream)),
			inputStrideBytes, vectorCount, value);
	}

	inline Mat4x4 Mat4x4::Identity() noexcept
	{
		return DirectX::XMMatrixIdentity();
	}

	inline Mat4x4 Mat4x4::Set(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23,
		const float m30, const float m31, const float m32, const float m33) noexcept
	{
		return DirectX::XMMatrixSet(
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		);
	}

	template<class X, class Y, class Z>
	inline Mat4x4 Mat4x4::Translate(const X x, const Y y, const Z z) noexcept
	{
		return DirectX::XMMatrixTranslation(
			static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
	}

	inline Mat4x4 Mat4x4::Translate(const Float3 v) noexcept
	{
		return DirectX::XMMatrixTranslation(v.x, v.y, v.z);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::Scale(const Arithmetic s) noexcept
	{
		return DirectX::XMMatrixScalingFromVector(
			DirectX::XMVectorReplicate(static_cast<float>(s)));
	}
	
	inline Mat4x4 Mat4x4::Scale(const Float3 s) noexcept
	{
		return DirectX::XMMatrixScaling(s.x, s.y, s.z);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::Scale(const Arithmetic s, const Float3 center) noexcept
	{
		const auto t0 = DirectX::XMMatrixTranslation(-center.x, -center.y, -center.z);
		const auto r = DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(static_cast<float>(s)));
		const auto t1 = DirectX::XMMatrixTranslation(center.x, center.y, center.z);
		return (t0 * r * t1);
	}
	
	inline Mat4x4 Mat4x4::Scale(const Float3 s, const Float3 center) noexcept
	{
		const auto t0	= DirectX::XMMatrixTranslation(-center.x, -center.y, -center.z);
		const auto r	= DirectX::XMMatrixScaling(s.x, s.y, s.z);
		const auto t1	= DirectX::XMMatrixTranslation(center.x, center.y, center.z);
		return (t0 * r * t1);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::RotateX(const Arithmetic angle) noexcept
	{
		return DirectX::XMMatrixRotationX(static_cast<float>(angle));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::RotateY(const Arithmetic angle) noexcept
	{
		return DirectX::XMMatrixRotationY(static_cast<float>(angle));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::RotateZ(const Arithmetic angle) noexcept
	{
		return DirectX::XMMatrixRotationZ(static_cast<float>(angle));
	}

	template<class X, class Y, class Z>
	inline Mat4x4 Mat4x4::RollPitchYaw(const X pitch, const Y yaw, const Z roll) noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw(
			static_cast<float>(pitch), static_cast<float>(yaw), static_cast<float>(roll));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::Rotate(const Float3 axis, const Arithmetic angle) noexcept
	{
		return DirectX::XMMatrixRotationNormal(
			SIMD_Float4{ axis, 0.0f }, static_cast<float>(angle));
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Mat4x4 Mat4x4::Rotate(const Float3 axis, const Arithmetic angle, const Float3 center) noexcept
	{
		const auto t0	= DirectX::XMMatrixTranslation(-center.x, -center.y, -center.z);
		const auto r	= DirectX::XMMatrixRotationNormal(
			SIMD_Float4{ axis, 0.0f }, static_cast<float>(angle));
		const auto t1	= DirectX::XMMatrixTranslation(center.x, center.y, center.z);
		return (t0 * r * t1);
	}

	inline Mat4x4 Mat4x4::Rotate(const Quaternion quaternion) noexcept
	{
		return DirectX::XMMatrixRotationQuaternion(quaternion);
	}

	inline Mat4x4 Mat4x4::Rotate(const Quaternion quaternion, const Float3 center) noexcept
	{
		const auto t0	= DirectX::XMMatrixTranslation(-center.x, -center.y, -center.z);
		const auto r	= DirectX::XMMatrixRotationQuaternion(quaternion);
		const auto t1	= DirectX::XMMatrixTranslation(center.x, center.y, center.z);
		return (t0 * r * t1);
	}

	inline Mat4x4 Mat4x4::Reflect(const InfinitePlane plane) noexcept
	{
		return DirectX::XMMatrixReflect(plane);
	}

	inline Mat4x4 Mat4x4::Shadow(const InfinitePlane plane, const Float3 lightPos) noexcept
	{
		return DirectX::XMMatrixShadow(plane, SIMD_Float4{ lightPos, 0.0f });
	}
}
