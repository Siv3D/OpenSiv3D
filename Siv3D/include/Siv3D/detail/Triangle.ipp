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
	inline constexpr Triangle::Triangle(const value_type sides) noexcept
		: p0(0.0, -Math::InvSqrt3 * sides)
		, p1(sides * 0.5, sides / (2.0 * Math::Sqrt3))
		, p2(-p1.x, p1.y) {}

	inline Triangle::Triangle(const value_type sides, const value_type angle) noexcept
		: p0(Circular(Math::InvSqrt3* sides, angle))
		, p1(Circular(Math::InvSqrt3* sides, 2.0 * Math::OneThirdPi + angle))
		, p2(Circular(Math::InvSqrt3* sides, 4.0 * Math::OneThirdPi + angle)) {}

	inline constexpr Triangle::Triangle(const value_type x, const value_type y, const value_type sides) noexcept
		: Triangle(Triangle(sides).moveBy(x, y)) {}

	inline constexpr Triangle::Triangle(const position_type& pos, const value_type sides) noexcept
		: Triangle(pos.x, pos.y, sides) {}

	inline Triangle::Triangle(const value_type x, const value_type y, const value_type sides, const value_type angle) noexcept
		: Triangle(Triangle(sides, angle).moveBy(x, y)) {}

	inline Triangle::Triangle(const position_type& pos, const value_type sides, const value_type angle) noexcept
		: Triangle(pos.x, pos.y, sides, angle) {}

	inline constexpr Triangle::Triangle(const value_type x0, const value_type y0, const value_type x1, const value_type y1, const value_type x2, const value_type y2) noexcept
		: p0(x0, y0)
		, p1(x1, y1)
		, p2(x2, y2) {}

	inline constexpr Triangle::Triangle(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept
		: p0(_p0)
		, p1(_p1)
		, p2(_p2) {}




	inline size_t Triangle::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
