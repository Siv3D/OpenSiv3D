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
	inline constexpr Line::Line(const value_type x0, const value_type y0, const value_type x1, const value_type y1) noexcept
		: begin{ x0, y0 }
		, end{ x1, y1 } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X0, Concept::Arithmetic Y0, Concept::Arithmetic X1, Concept::Arithmetic Y1>
# else
	template <class X0, class Y0, class X1, class Y1, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X0>, std::is_arithmetic<Y0>, std::is_arithmetic<X1>, std::is_arithmetic<Y1>>>*>
# endif
	inline constexpr Line::Line(const X0 x0, const Y0 y0, const X1 x1, const Y1 y1) noexcept
		: begin{ static_cast<value_type>(x0), static_cast<value_type>(y0) }
		, end{ static_cast<value_type>(x1), static_cast<value_type>(y1) } {}

	inline constexpr Line::Line(const position_type p0, const value_type x1, const value_type y1) noexcept
		: begin{ p0 }
		, end{ x1, y1 } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X1, Concept::Arithmetic Y1>
# else
	template <class X1, class Y1, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X1>, std::is_arithmetic<Y1>>>*>
# endif
	inline constexpr Line::Line(const position_type p0, const X1 x1, const Y1 y1) noexcept
		: begin{ p0 }
		, end{ static_cast<value_type>(x1), static_cast<value_type>(y1) } {}

	inline constexpr Line::Line(const value_type x0, const value_type y0, const position_type p1) noexcept
		: begin{ x0, y0 }
		, end{ p1 } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X0, Concept::Arithmetic Y0>
# else
	template <class X0, class Y0, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X0>, std::is_arithmetic<Y0>>>*>
# endif
	inline constexpr Line::Line(const X0 x0, const Y0 y0, const position_type p1) noexcept
		: begin{ static_cast<value_type>(x0), static_cast<value_type>(y0) }
		, end{ p1 } {}

	inline constexpr Line::Line(const position_type p0, const position_type p1) noexcept
		: begin{ p0 }
		, end{ p1 } {}

	inline constexpr Line::Line(const value_type x0, const value_type y0, const Arg::direction_<position_type> direction) noexcept
		: begin{ x0, y0 }
		, end{ begin + direction.value() } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X0, Concept::Arithmetic Y0>
# else
	template <class X0, class Y0, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X0>, std::is_arithmetic<Y0>>>*>
# endif
	inline constexpr Line::Line(const X0 x0, const Y0 y0, const Arg::direction_<position_type> direction) noexcept
		: begin{ static_cast<value_type>(x0), static_cast<value_type>(y0) }
		, end{ begin + direction.value() } {}

	inline constexpr Line::Line(const position_type origin, const Arg::direction_<position_type> direction) noexcept
		: begin{ origin }
		, end{ origin + direction.value() } {}

	inline constexpr Line& Line::set(const value_type x0, const value_type y0, const value_type x1, const value_type y1) noexcept
	{
		begin.set(x0, y0);
		
		end.set(x1, y1);
		
		return *this;
	}

	inline constexpr Line& Line::set(const position_type p0, const value_type x1, const value_type y1) noexcept
	{
		return set(p0.x, p0.y, x1, y1);
	}

	inline constexpr Line& Line::set(const value_type x0, const value_type y0, const position_type p1) noexcept
	{
		return set(x0, y0, p1.x, p1.y);
	}

	inline constexpr Line& Line::set(const position_type p0, const position_type p1) noexcept
	{
		return set(p0.x, p0.y, p1.x, p1.y);
	}

	inline constexpr Line& Line::set(const Line& line) noexcept
	{
		return (*this = line);
	}

	inline constexpr Line Line::movedBy(const value_type x, const value_type y) const noexcept
	{
		return{ begin.movedBy(x, y), end.movedBy(x, y) };
	}

	inline constexpr Line Line::movedBy(const position_type v) const noexcept
	{
		return movedBy(v.x, v.y);
	}

	inline constexpr Line& Line::moveBy(const value_type x, const value_type y) noexcept
	{
		begin.moveBy(x, y);
		
		end.moveBy(x, y);
		
		return *this;
	}

	inline constexpr Line& Line::moveBy(const position_type v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	inline Line Line::stretched(const value_type length) const noexcept
	{
		const position_type v = vector().setLength(length);

		return{ (begin - v), (end + v) };
	}

	inline Line Line::stretched(const value_type lengthBegin, const value_type lengthEnd) const noexcept
	{
		const position_type v = vector().normalized();

		return{ (begin - v * lengthBegin), (end + v * lengthEnd) };
	}

	inline constexpr Line::position_type Line::vector() const noexcept
	{
		return (end - begin);
	}

	inline Line::position_type Line::normal() const noexcept
	{
		return Vec2{ (end.y - begin.y), (begin.x - end.x) }.normalized();
	}

	inline constexpr Line Line::reversed() const noexcept
	{
		return{ end, begin };
	}

	inline constexpr Line& Line::reverse() noexcept
	{
		const position_type t = begin;
		
		begin = end;
		
		end = t;
		
		return *this;
	}

	inline constexpr bool Line::hasLength() const noexcept
	{
		return (begin != end);
	}

	inline Line::value_type Line::length() const noexcept
	{
		return begin.distanceFrom(end);
	}

	inline constexpr Line::value_type Line::lengthSq() const noexcept
	{
		return begin.distanceFromSq(end);
	}

	inline Line::position_type& Line::p(const size_t index) noexcept
	{
		return (&begin)[index];
	}

	inline const Line::position_type& Line::p(const size_t index) const noexcept
	{
		return (&begin)[index];
	}

	inline constexpr Line::position_type Line::point(const size_t index) const
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
			throw std::out_of_range("Line::point() index out of range");
		}
	}

	inline constexpr Line::position_type Line::position(const double t) const noexcept
	{
		return begin.lerp(end, t);
	}

	inline constexpr Line::position_type Line::center() const noexcept
	{
		return position_type((begin.x + end.x) * 0.5, (begin.y + end.y) * 0.5);
	}

	inline constexpr Line Line::lerp(const Line& other, const double f) const noexcept
	{
		return{ begin.lerp(other.begin, f), end.lerp(other.end, f) };
	}

	inline size_t Line::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	[[nodiscard]]
	inline constexpr bool Line::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	[[nodiscard]]
	inline Optional<Array<Vec2>> Line::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}
}
