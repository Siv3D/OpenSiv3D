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
	struct Triangle3D;
	struct Plane;
	struct Sphere;
	struct AABB;
	struct OBB;

	struct Ray
	{
		SIMD_Float4 origin;

		SIMD_Float4 direction;

		SIV3D_NODISCARD_CXX20
		Ray() = default;

		SIV3D_NODISCARD_CXX20
		Ray(Float3 _origin, Float3 normalizedDirection) noexcept;

		template <class X, class Y, class Z>
		SIV3D_NODISCARD_CXX20
		Ray(X ox, Y oy, Z oz, Float3 normalizedDirection) noexcept;

		template <class X, class Y, class Z>
		SIV3D_NODISCARD_CXX20
		Ray(Float3 _origin, X ndx, Y ndy, Z ndz) noexcept;

		[[nodiscard]]
		Vec3 SIV3D_VECTOR_CALL point_at(double distance) const noexcept
		{
			return (origin.xyz() + (distance * direction.xyz()));
		}

		Ray& SIV3D_VECTOR_CALL setOrigin(Float3 _origin) noexcept
		{
			origin.set(_origin.x, _origin.y, _origin.z, 0.0f);
		}

		Ray& SIV3D_VECTOR_CALL setDirection(Float3 _direction) noexcept
		{
			direction.set(_direction.x, _direction.y, _direction.z, 0.0f);
		}

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Triangle3D& triangle) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Plane& plane) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const Sphere& sphere) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const AABB& aabb) const;

		[[nodiscard]]
		Optional<float> SIV3D_VECTOR_CALL intersects(const OBB& obb) const;
	};
}

# include "detail/Ray.ipp"
