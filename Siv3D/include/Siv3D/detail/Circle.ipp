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

	inline constexpr Circle& Circle::set(const value_type _x, const value_type _y, size_type _r) noexcept
	{
		center.set(_x, _y);
		r = _r;
		return *this;
	}

	inline constexpr Circle& Circle::set(const position_type& _center, size_type _r) noexcept
	{
		return set(_center.x, _center.y, _r);
	}

	inline constexpr Circle& Circle::set(const Arg::center_<position_type> _center, size_type _r) noexcept
	{
		return set(_center->x, _center->y, _r);
	}

	inline constexpr Circle& Circle::set(const Arg::topLeft_<position_type> topLeft, size_type _r) noexcept
	{
		return set((topLeft->x + _r), (topLeft->y + _r), _r);
	}

	inline constexpr Circle& Circle::set(const Arg::topCenter_<position_type> topCenter, size_type _r) noexcept
	{
		return set(topCenter->x, (topCenter->y + _r), _r);
	}

	inline constexpr Circle& Circle::set(const Arg::topRight_<position_type> topRight, size_type _r) noexcept
	{
		return set((topRight->x - _r), (topRight->y + _r), _r);
	}

	inline constexpr Circle& Circle::set(const Arg::rightCenter_<position_type> rightCenter, size_type _r) noexcept
	{
		return set((rightCenter->x - _r), rightCenter->y, _r);
	}

	inline constexpr Circle& Circle::set(const Arg::bottomRight_<position_type> bottomRight, size_type _r) noexcept
	{
		return set((bottomRight->x - _r), (bottomRight->y - _r), _r);
	}

	inline constexpr Circle& Circle::set(const Arg::bottomCenter_<position_type> bottomCenter, size_type _r) noexcept
	{
		return set(bottomCenter->x, (bottomCenter->y - _r), _r);
	}

	inline constexpr Circle& Circle::set(const Arg::bottomLeft_<position_type> bottomLeft, size_type _r) noexcept
	{
		return set((bottomLeft->x + _r), (bottomLeft->y - _r), _r);
	}

	inline constexpr Circle& Circle::set(const Arg::leftCenter_<position_type> leftCenter, size_type _r) noexcept
	{
		return set((leftCenter->x + _r), leftCenter->y, _r);
	}

	inline constexpr Circle& Circle::set(const Circle& circle) noexcept
	{
		return *this = circle;
	}

	inline constexpr Circle& Circle::setCenter(const value_type _x, const value_type _y) noexcept
	{
		center.set(_x, _y);
		return *this;
	}

	inline constexpr Circle& Circle::setCenter(const position_type& _center) noexcept
	{
		return setCenter(_center.x, _center.y);
	}

	inline constexpr Circle& Circle::setPos(const value_type _x, const value_type _y) noexcept
	{
		return setCenter(_x, _y);
	}

	inline constexpr Circle& Circle::setPos(const position_type& _center) noexcept
	{
		return setCenter(_center.x, _center.y);
	}

	inline constexpr Circle& Circle::setPos(const Arg::center_<position_type> _center) noexcept
	{
		return setCenter(_center->x, _center->y);
	}

	inline constexpr Circle& Circle::setPos(const Arg::topLeft_<position_type> topLeft) noexcept
	{
		return setCenter(topLeft->x + r, topLeft->y + r);
	}

	inline constexpr Circle& Circle::setPos(const Arg::topCenter_<position_type> topCenter) noexcept
	{
		return setCenter(topCenter->x, topCenter->y + r);
	}

	inline constexpr Circle& Circle::setPos(const Arg::topRight_<position_type> topRight) noexcept
	{
		return setCenter(topRight->x - r, topRight->y + r);
	}

	inline constexpr Circle& Circle::setPos(const Arg::rightCenter_<position_type> rightCenter) noexcept
	{
		return setCenter(rightCenter->x - r, rightCenter->y);
	}

	inline constexpr Circle& Circle::setPos(const Arg::bottomRight_<position_type> bottomRight) noexcept
	{
		return setCenter(bottomRight->x - r, bottomRight->y - r);
	}

	inline constexpr Circle& Circle::setPos(const Arg::bottomCenter_<position_type> bottomCenter) noexcept
	{
		return setCenter(bottomCenter->x, bottomCenter->y - r);
	}

	inline constexpr Circle& Circle::setPos(const Arg::bottomLeft_<position_type> bottomLeft) noexcept
	{
		return setCenter(bottomLeft->x + r, bottomLeft->y - r);
	}

	inline constexpr Circle& Circle::setPos(const Arg::leftCenter_<position_type> leftCenter) noexcept
	{
		return setCenter(leftCenter->x + r, leftCenter->y);
	}

	inline constexpr Circle& Circle::setR(const value_type _r) noexcept
	{
		r = _r;
		return *this;
	}

	inline constexpr Circle Circle::lerp(const Circle& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), (r + (other.r - r) * f) };
	}

	inline size_t Circle::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
