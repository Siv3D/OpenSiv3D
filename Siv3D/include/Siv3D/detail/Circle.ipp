//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr Circle::Circle(const size_type _r) noexcept
		: center(0.0, 0.0)
		, r(_r) {}

	inline constexpr Circle::Circle(const value_type _x, const value_type _y, const size_type _r) noexcept
		: center(_x, _y)
		, r(_r) {}

	inline constexpr Circle::Circle(const position_type _center, const size_type _r) noexcept
		: center(_center)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::center_<position_type> _center, const size_type _r) noexcept
		: center(_center.value())
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::topLeft_<position_type> topLeft, const size_type _r) noexcept
		: center(topLeft->x + _r, topLeft->y + _r)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::topCenter_<position_type> topCenter, const size_type _r) noexcept
		: center(topCenter->x, topCenter->y + _r)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::topRight_<position_type> topRight, const size_type _r) noexcept
		: center(topRight->x - _r, topRight->y + _r)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::rightCenter_<position_type> rightCenter, const size_type _r) noexcept
		: center(rightCenter->x - _r, rightCenter->y)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::bottomRight_<position_type> bottomRight, const size_type _r) noexcept
		: center(bottomRight->x - _r, bottomRight->y - _r)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::bottomCenter_<position_type> bottomCenter, const size_type _r) noexcept
		: center(bottomCenter->x, bottomCenter->y - _r)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::bottomLeft_<position_type> bottomLeft, const size_type _r) noexcept
		: center(bottomLeft->x + _r, bottomLeft->y - _r)
		, r(_r) {}

	inline constexpr Circle::Circle(const Arg::leftCenter_<position_type> leftCenter, const size_type _r) noexcept
		: center(leftCenter->x + _r, leftCenter->y)
		, r(_r) {}

	inline Circle::Circle(const position_type p0, const position_type p1) noexcept
		: center((p0 + p1) / 2.0)
		, r(p0.distanceFrom(p1) / 2.0) {}

	inline Circle::Circle(const Line& diameter) noexcept
		: Circle(diameter.begin, diameter.end) {}

	inline Circle::Circle(const Arg::center_<position_type> _center, const position_type& p) noexcept
		: center(_center.value())
		, r(p.distanceFrom(_center.value())) {}




	inline size_t Circle::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
