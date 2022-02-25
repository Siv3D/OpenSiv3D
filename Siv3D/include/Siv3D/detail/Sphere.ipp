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

	inline constexpr Sphere& Sphere::set(const value_type _x, const value_type _y, const size_type _z, const size_type _r) noexcept
	{
		center.set(_x, _y, _z);
		r = _r;
		return *this;
	}

	inline constexpr Sphere& Sphere::set(const position_type _center, const size_type _r) noexcept
	{
		center = _center;
		r = _r;
		return *this;
	}

	inline constexpr Sphere& Sphere::set(const Sphere& sphere) noexcept
	{
		return (*this = sphere);
	}

	inline constexpr Sphere& Sphere::setPos(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		center.set(_x, _y, _z);
		return *this;
	}

	inline constexpr Sphere& Sphere::setPos(const position_type _center) noexcept
	{
		center = _center;
		return *this;
	}

	inline constexpr Sphere& Sphere::setR(const value_type _r) noexcept
	{
		r = _r;
		return *this;
	}

	inline constexpr Sphere Sphere::movedBy(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return{ center.movedBy(_x, _y, _z), r };
	}

	inline constexpr Sphere Sphere::movedBy(const position_type v) const noexcept
	{
		return{ center.movedBy(v), r };
	}

	inline constexpr Sphere& Sphere::moveBy(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		center.moveBy(_x, _y, _z);
		return *this;
	}

	inline constexpr Sphere& Sphere::moveBy(const position_type v) noexcept
	{
		center.moveBy(v);
		return *this;
	}

	constexpr Sphere Sphere::stretched(const value_type size) const noexcept
	{
		return{ center, (r + size) };
	}

	constexpr Sphere Sphere::scaled(const double s) const noexcept
	{
		return{ center, (r * s) };
	}

	constexpr Sphere::position_type Sphere::top() const noexcept
	{
		return{ center.x, (center.y + r), center.z };
	}

	constexpr Sphere::position_type Sphere::bottom() const noexcept
	{
		return{ center.x, (center.y - r), center.z };
	}

	constexpr Sphere::position_type Sphere::left() const noexcept
	{
		return{ (center.x - r), center.y, center.z };
	}

	constexpr Sphere::position_type Sphere::right() const noexcept
	{
		return{ (center.x + r), center.y, center.z };
	}

	constexpr Sphere::position_type Sphere::forward() const noexcept
	{
		return{ center.x, center.y, (center.z + r) };
	}

	constexpr Sphere::position_type Sphere::backward() const noexcept
	{
		return{ center.x, center.y, (center.z - r) };
	}

	constexpr Sphere Sphere::lerp(const Sphere& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), (r + (other.r - r) * f) };
	}
}
