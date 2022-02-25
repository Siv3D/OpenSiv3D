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
	inline Cylinder::Cylinder(const double _r, const double _h, const Quaternion& _orientation) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, r{ _r }
		, h{ _h }
		, orientation{ _orientation } {}

	inline Cylinder::Cylinder(const double cx, const double cy, const double cz, const double _r, const double _h, const Quaternion& _orientation) noexcept
		: center{ cx, cy, cz }
		, r{ _r }
		, h{ _h }
		, orientation{ _orientation } {}

	inline Cylinder::Cylinder(const Vec3& _center, const double _r, const double _h, const Quaternion& _orientation) noexcept
		: center{ _center }
		, r{ _r }
		, h{ _h }
		, orientation{ _orientation } {}

	inline Cylinder& Cylinder::setPos(const value_type cx, const value_type cy, const value_type cz) noexcept
	{
		center.set(cx, cy, cz);
		return *this;
	}

	inline Cylinder& Cylinder::setPos(const position_type _center) noexcept
	{
		center = _center;
		return *this;
	}

	inline Cylinder& Cylinder::setSize(const value_type _r, const value_type _h) noexcept
	{
		r = _r;
		h = _h;
		return *this;
	}

	inline Cylinder& Cylinder::setOrientation(const Quaternion _orientation) noexcept
	{
		orientation = _orientation;
		return *this;
	}

	inline Cylinder Cylinder::movedBy(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return{ center.movedBy(_x, _y, _z), r, h, orientation };
	}

	inline Cylinder Cylinder::movedBy(const position_type v) const noexcept
	{
		return{ center.movedBy(v), r, h, orientation };
	}

	inline Cylinder& Cylinder::moveBy(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		center.moveBy(_x, _y, _z);
		return *this;
	}

	inline Cylinder& Cylinder::moveBy(const position_type v) noexcept
	{
		center.moveBy(v);
		return *this;
	}

	inline Cylinder Cylinder::stretched(const double _r, const double _h) const noexcept
	{
		return{ center, (r + _r), (h + _h), orientation };
	}

	inline Cylinder Cylinder::scaled(const double sr, const double sh) const noexcept
	{
		return{ center, (r * sr), (h * sh), orientation };
	}

	inline bool Cylinder::hasVolume() const noexcept
	{
		return ((r != 0.0) && (h != 0.0));
	}

	inline Cylinder Cylinder::lerp(const Cylinder& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), (r + (other.r - r) * f), (h + (other.h - h) * f), orientation.slerp(other.orientation, f) };
	}

	inline Vec3 Cylinder::vector() const noexcept
	{
		return (orientation * Vec3::Up());
	}

	inline Cylinder::position_type Cylinder::topCenter() const noexcept
	{
		return (center + (orientation * Vec3::Up(h * 0.5)));
	}

	inline Cylinder::position_type Cylinder::bottomCenter() const noexcept
	{
		return (center + (orientation * Vec3::Down(h * 0.5)));
	}
}
