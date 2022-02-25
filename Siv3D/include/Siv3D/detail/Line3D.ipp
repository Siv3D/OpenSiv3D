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
	inline constexpr Line3D::Line3D(const value_type bx, const value_type by, const value_type bz, const value_type ex, const value_type ey, const value_type ez) noexcept
		: begin{ bx, by, bz }
		, end{ ex, ey, ez } {}

	inline constexpr Line3D::Line3D(const position_type& _begin, const value_type ex, const value_type ey, const value_type ez) noexcept
		: begin{ _begin }
		, end{ ex, ey, ez } {}

	inline constexpr Line3D::Line3D(const value_type bx, const value_type by, const value_type bz, const position_type& _end) noexcept
		: begin{ bx, by, bz }
		, end{ _end } {}

	inline constexpr Line3D::Line3D(const position_type& _begin, const position_type& _end) noexcept
		: begin{ _begin }
		, end{ _end } {}

	inline constexpr Line3D::Line3D(const position_type& origin, const Arg::direction_<position_type> direction) noexcept
		: begin{ origin }
		, end{ (origin + *direction) } {}

	inline constexpr Line3D& Line3D::set(const value_type x0, const value_type y0, const value_type z0, const value_type x1, const value_type y1, const value_type z1) noexcept
	{
		begin.set(x0, y0, z0);
		end.set(x1, y1, z1);
		return *this;
	}

	inline constexpr Line3D& Line3D::set(const position_type p0, const value_type x1, const value_type y1, const value_type z1) noexcept
	{
		return set(p0.x, p0.y, p0.z, x1, y1, z1);
	}

	inline constexpr Line3D& Line3D::set(const value_type x0, const value_type y0, const value_type z0, const position_type p1) noexcept
	{
		return set(x0, y0, z0, p1.x, p1.y, p1.z);
	}

	inline constexpr Line3D& Line3D::set(const position_type p0, const position_type p1) noexcept
	{
		return set(p0.x, p0.y, p0.z, p1.x, p1.y, p1.z);
	}

	inline constexpr Line3D& Line3D::set(const Line3D& line) noexcept
	{
		return (*this = line);
	}

	inline constexpr Line3D Line3D::movedBy(const value_type x, const value_type y, const value_type z) const noexcept
	{
		return{ begin.movedBy(x, y, z), end.movedBy(x, y, z) };
	}

	inline constexpr Line3D Line3D::movedBy(const position_type v) const noexcept
	{
		return movedBy(v.x, v.y, v.z);
	}

	inline constexpr Line3D& Line3D::moveBy(const value_type x, const value_type y, const value_type z) noexcept
	{
		begin.moveBy(x, y, z);
		end.moveBy(x, y, z);
		return *this;
	}

	inline constexpr Line3D& Line3D::moveBy(const position_type v) noexcept
	{
		return moveBy(v.x, v.y, v.z);
	}

	inline Line3D Line3D::stretched(const value_type length) const noexcept
	{
		const position_type v = vector().setLength(length);

		return{ (begin - v), (end + v) };
	}

	inline Line3D Line3D::stretched(const value_type lengthBegin, const value_type lengthEnd) const noexcept
	{
		const position_type v = vector().normalized();

		return{ (begin - v * lengthBegin), (end + v * lengthEnd) };
	}

	inline constexpr Line3D::position_type Line3D::vector() const noexcept
	{
		return (end - begin);
	}

	inline constexpr Line3D Line3D::reversed() const noexcept
	{
		return{ end, begin };
	}

	inline constexpr Line3D& Line3D::reverse() noexcept
	{
		const position_type t = begin;

		begin = end;

		end = t;

		return *this;
	}

	inline constexpr bool Line3D::hasLength() const noexcept
	{
		return (begin != end);
	}

	inline Line3D::value_type Line3D::length() const noexcept
	{
		return begin.distanceFrom(end);
	}

	inline constexpr Line3D::value_type Line3D::lengthSq() const noexcept
	{
		return begin.distanceFromSq(end);
	}

	inline Line3D::position_type& Line3D::p(const size_t index) noexcept
	{
		return (&begin)[index];
	}

	inline const Line3D::position_type& Line3D::p(const size_t index) const noexcept
	{
		return (&begin)[index];
	}

	inline constexpr Line3D::position_type Line3D::point(const size_t index)
	{
		if (index == 0)
		{
			return begin;
		}
		else if (index == 1)
		{
			return end;
		}
		else
		{
			throw std::out_of_range("Line3D::point() index out of range");
		}
	}

	inline constexpr Line3D::position_type Line3D::position(const double t) const noexcept
	{
		return begin.lerp(end, t);
	}

	inline constexpr Line3D::position_type Line3D::center() const noexcept
	{
		return position_type((begin.x + end.x) * 0.5, (begin.y + end.y) * 0.5, (begin.z + end.z) * 0.5);
	}

	inline constexpr Line3D Line3D::lerp(const Line3D& other, const double f) const noexcept
	{
		return{ begin.lerp(other.begin, f), end.lerp(other.end, f) };
	}
}
