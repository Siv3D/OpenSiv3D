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
# include "Vector3D.hpp"

namespace s3d
{
	struct Ray
	{
		Vec3 origin;

		Vec3 direction;



		Ray() = default;

		Ray(const Ray&) = default;

		Ray& operator=(const Ray&) = default;

		Ray(Ray&&) = default;

		Ray& operator=(Ray&&) = default;

		constexpr Ray(const Vec3& _origin, const Vec3& normalizedDirection) noexcept
			: origin(_origin)
			, direction(normalizedDirection) {}

		constexpr Ray(double ox, double oy, double oz, const Vec3& normalizedDirection) noexcept
			: origin(ox, oy, oz)
			, direction(normalizedDirection) {}

		constexpr Vec3 point_at(double distance) const noexcept
		{
			return Vec3(
				origin.x + distance * direction.x,
				origin.y + distance * direction.y,
				origin.z + distance * direction.z
				);
		}

		constexpr Ray& setOrigin(const Vec3& _origin) noexcept
		{
			origin.set(_origin);
			return *this;
		}

		constexpr Ray& setDirection(const Vec3& _direction) noexcept
		{
			direction.set(_direction);
			return *this;
		}

		[[nodiscard]] Optional<float> intersects(const experimental::AABB& aabb) const;
	};
}
