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
# include "PointVector.hpp"
# include "SIMD_Float4.hpp"

namespace s3d
{
	struct Mat4x4;

	struct alignas(16) Quaternion
	{
		SIMD_Float4 value = { 0.0f, 0.0f, 0.0f, 1.0f };

		SIV3D_NODISCARD_CXX20
		Quaternion() = default;

		SIV3D_NODISCARD_CXX20
		Quaternion(float x, float y, float z, float w) noexcept;

		template <class X, class Y, class Z, class W>
		SIV3D_NODISCARD_CXX20
		Quaternion(X x, Y y, Z z, W w) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_NODISCARD_CXX20
		Quaternion(const Float3& axis, Arithmetic angle) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Quaternion(const Mat4x4& m) noexcept;
		
		SIV3D_NODISCARD_CXX20
		Quaternion(Float4 _vec) noexcept;

		SIV3D_NODISCARD_CXX20
		Quaternion(aligned_float4 _vec) noexcept;

		[[nodiscard]] Quaternion SIV3D_VECTOR_CALL operator *(const Quaternion& q) const noexcept;

		Quaternion& SIV3D_VECTOR_CALL operator *=(const Quaternion& q) noexcept;

		[[nodiscard]] Float3 operator *(const Float3& v) const noexcept;

		[[nodiscard]]
		SIV3D_VECTOR_CALL operator aligned_float4() const noexcept
		{
			return value.vec;
		}

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

		void SIV3D_VECTOR_CALL set(float x, float y, float z, float w) noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL isZero() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL isIdentity() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasNaN() const noexcept;

		[[nodiscard]]
		bool SIV3D_VECTOR_CALL hasInf() const noexcept;

		Quaternion& SIV3D_VECTOR_CALL normalize() noexcept;

		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL normalized() const noexcept;

		Quaternion& SIV3D_VECTOR_CALL conjugate() noexcept;

		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL conjugated() const noexcept;

		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL inverse() const noexcept;

		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		Quaternion SIV3D_VECTOR_CALL slerp(Quaternion q, Float t) const noexcept;

		[[nodiscard]]
		std::pair<Float3, float> SIV3D_VECTOR_CALL toAxisAngle() const noexcept;

		[[nodiscard]]
		static constexpr Quaternion SIV3D_VECTOR_CALL Identity() noexcept;

		[[nodiscard]]
		static constexpr Quaternion SIV3D_VECTOR_CALL Zero() noexcept;

		template <class X, class Y, class Z>
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RollPitchYaw(X pitch, Y yaw, Z roll) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RotationNormal(const Float3& normalAxis, Arithmetic angle);

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL RotationAxis(const Float3& axis, Arithmetic angle);

		[[nodiscard]]
		static Quaternion SIV3D_VECTOR_CALL Rotate(Mat4x4 m);
	};
}

# include "detail/Quaternion.ipp"
