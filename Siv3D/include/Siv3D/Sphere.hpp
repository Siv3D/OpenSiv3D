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
	struct Sphere
	{
		Vec3 center;

		double r;

		Sphere() = default;

		Sphere(const Sphere&) = default;

		Sphere& operator=(const Sphere&) = default;

		Sphere(Sphere&&) = default;

		Sphere& operator=(Sphere&&) = default;

		constexpr Sphere(const Vec3& _center, double _r) noexcept
			: center(_center)
			, r(_r) {}

		constexpr Sphere(double x, double y, double z, double _r) noexcept
			: center(x, y, z)
			, r(_r) {}

		void draw(const Mat4x4& vp, const ColorF& color) const;
	};
}
