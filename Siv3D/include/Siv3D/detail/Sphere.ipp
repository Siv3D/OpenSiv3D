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
	inline constexpr Sphere::Sphere(const double _r) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, r{ _r } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Sphere::Sphere(const Arithmetic _r) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, r{ static_cast<double>(_r) } {}

	inline constexpr Sphere::Sphere(const double _x, const double _y, const double _z, const double _r) noexcept
		: center{ _x, _y, _z }
		, r{ _r } {}

	template <class X, class Y, class Z, class R>
	inline constexpr Sphere::Sphere(const X _x, const Y _y, const Z _z, const R _r) noexcept
		: center{ static_cast<double>(_x), static_cast<double>(_y), static_cast<double>(_z) }
		, r{ static_cast<double>(_r) } {}

	inline constexpr Sphere::Sphere(const Vec3& _center, const double _r) noexcept
		: center{ _center }
		, r{ _r } {}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr Sphere::Sphere(const Vec3& _center, const Arithmetic _r) noexcept
		: center{ _center }
		, r{ static_cast<double>(_r) } {}
}
