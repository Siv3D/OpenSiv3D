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
	inline constexpr Disc::Disc(const double _r) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, r{ _r } {}

	inline constexpr Disc::Disc(const double cx, const double cy, const double cz, const double _r) noexcept
		: center{ cx, cy, cz }
		, r{ _r } {}

	inline constexpr Disc::Disc(const Vec3& _center, const double _r) noexcept
		: center{ _center }
		, r{ _r } {}

	inline constexpr Disc& Disc::setPos(const value_type cx, const value_type cy, const value_type cz) noexcept
	{
		center.set(cx, cy, cz);
		return *this;
	}

	inline constexpr Disc& Disc::setPos(const position_type _center) noexcept
	{
		center = _center;
		return *this;
	}

	inline constexpr Disc& Disc::setR(const size_type _r) noexcept
	{
		r = _r;
		return *this;
	}

	inline constexpr Disc Disc::movedBy(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return{ center.movedBy(_x, _y, _z), r };
	}

	inline constexpr Disc Disc::movedBy(const position_type v) const noexcept
	{
		return{ center.movedBy(v), r };
	}

	inline constexpr Disc& Disc::moveBy(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		center.moveBy(_x, _y, _z);
		return *this;
	}

	inline constexpr Disc& Disc::moveBy(const position_type v) noexcept
	{
		center.moveBy(v);
		return *this;
	}

	inline constexpr Disc Disc::stretched(const value_type _r) const noexcept
	{
		return{ center, (r + _r) };
	}

	inline constexpr Disc Disc::scaled(const double s) const noexcept
	{
		return{ center, (r * s) };
	}

	inline constexpr bool Disc::hasArea() const noexcept
	{
		return (r != 0.0);
	}

	inline constexpr Disc Disc::lerp(const Disc& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), (r + (other.r - r) * f) };
	}
}
