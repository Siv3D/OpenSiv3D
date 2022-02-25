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
	inline Cone::Cone(const double _r, const double _h, const Quaternion& _orientation) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, r{ _r }
		, h{ _h }
		, orientation{ _orientation } {}

	inline Cone::Cone(const double cx, const double cy, const double cz, const double _r, const double _h, const Quaternion& _orientation) noexcept
		: center{ cx, cy, cz }
		, r{ _r }
		, h{ _h }
		, orientation{ _orientation } {}

	inline Cone::Cone(const Vec3& _center, const double _r, const double _h, const Quaternion& _orientation) noexcept
		: center{ _center }
		, r{ _r }
		, h{ _h }
		, orientation{ _orientation } {}

	inline Cone& Cone::setPos(const value_type cx, const value_type cy, const value_type cz) noexcept
	{
		center.set(cx, cy, cz);
		return *this;
	}

	inline Cone& Cone::setPos(const position_type _center) noexcept
	{
		center = _center;
		return *this;
	}

	inline Cone& Cone::setSize(const value_type _r, const value_type _h) noexcept
	{
		r = _r;
		h = _h;
		return *this;
	}

	inline Cone& Cone::setOrientation(const Quaternion _orientation) noexcept
	{
		orientation = _orientation;
		return *this;
	}

	inline Cone Cone::movedBy(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return{ center.movedBy(_x, _y, _z), r, h, orientation };
	}

	inline Cone Cone::movedBy(const position_type v) const noexcept
	{
		return{ center.movedBy(v), r, h, orientation };
	}

	inline Cone& Cone::moveBy(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		center.moveBy(_x, _y, _z);
		return *this;
	}

	inline Cone& Cone::moveBy(const position_type v) noexcept
	{
		center.moveBy(v);
		return *this;
	}

	inline Cone Cone::stretched(const double _r, const double _h) const noexcept
	{
		return{ center, (r + _r), (h + _h), orientation };
	}

	inline Cone Cone::scaled(const double sr, const double sh) const noexcept
	{
		return{ center, (r * sr), (h * sh), orientation };
	}

	inline bool Cone::hasVolume() const noexcept
	{
		return ((r != 0.0) && (h != 0.0));
	}

	inline Cone Cone::lerp(const Cone& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), (r + (other.r - r) * f), (h + (other.h - h) * f), orientation.slerp(other.orientation, f) };
	}

	inline Vec3 Cone::vector() const noexcept
	{
		return (orientation * Vec3::Up());
	}

	inline Cone::position_type Cone::top() const noexcept
	{
		return (center + (orientation * Vec3::Up(h)));
	}

	inline Cone::position_type Cone::bottomCenter() const noexcept
	{
		return center;
	}
}
