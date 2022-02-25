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
	inline constexpr Triangle::Triangle(const value_type sides) noexcept
		: p0{ 0.0, -Math::InvSqrt3 * sides }
		, p1{ sides * 0.5, sides / (2.0 * Math::Sqrt3) }
		, p2{ -p1.x, p1.y } {}

	inline constexpr Triangle::Triangle(const value_type x, const value_type y, const value_type sides) noexcept
		: Triangle{ Triangle{ sides }.moveBy(x, y) } {}

	inline constexpr Triangle::Triangle(const position_type& pos, const value_type sides) noexcept
		: Triangle{ pos.x, pos.y, sides } {}

	inline Triangle::Triangle(const value_type x, const value_type y, const value_type sides, const value_type angle) noexcept
		: Triangle{ Triangle{ sides, angle }.moveBy(x, y) } {}

	inline Triangle::Triangle(const position_type& pos, const value_type sides, const value_type angle) noexcept
		: Triangle{ pos.x, pos.y, sides, angle } {}

	inline constexpr Triangle::Triangle(const value_type x0, const value_type y0, const value_type x1, const value_type y1, const value_type x2, const value_type y2) noexcept
		: p0{ x0, y0 }
		, p1{ x1, y1 }
		, p2{ x2, y2 } {}

	inline constexpr Triangle::Triangle(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept
		: p0{ _p0 }
		, p1{ _p1 }
		, p2{ _p2 } {}

	inline constexpr Triangle& Triangle::set(const value_type x0, const value_type y0, const value_type x1, const value_type y1, const value_type x2, const value_type y2) noexcept
	{
		p0.set(x0, y0);
		p1.set(x1, y1);
		p2.set(x2, y2);
		return *this;
	}

	inline constexpr Triangle& Triangle::set(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept
	{
		p0.set(_p0);
		p1.set(_p1);
		p2.set(_p2);
		return *this;
	}

	inline constexpr Triangle& Triangle::set(const Triangle& triangle) noexcept
	{
		return *this = triangle;
	}

	inline constexpr Triangle Triangle::movedBy(const value_type x, const value_type y) const noexcept
	{
		return{ p0.movedBy(x, y), p1.movedBy(x, y), p2.movedBy(x, y) };
	}

	inline constexpr Triangle Triangle::movedBy(const position_type v) const noexcept
	{
		return movedBy(v.x, v.y);
	}

	inline constexpr Triangle& Triangle::moveBy(const value_type x, const value_type y) noexcept
	{
		p0.moveBy(x, y);
		p1.moveBy(x, y);
		p2.moveBy(x, y);
		return *this;
	}

	inline constexpr Triangle& Triangle::moveBy(const position_type v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	inline constexpr Triangle& Triangle::setCentroid(const value_type x, const value_type y) noexcept
	{
		return moveBy(position_type(x, y) - centroid());
	}

	inline constexpr Triangle& Triangle::setCentroid(position_type pos) noexcept
	{
		return setCentroid(pos.x, pos.y);
	}

	inline constexpr Triangle::position_type Triangle::centroid() const noexcept
	{
		return position_type((p0.x + p1.x + p2.x) / 3.0, (p0.y + p1.y + p2.y) / 3.0);
	}

	inline Triangle Triangle::rotated(const value_type angle) const noexcept
	{
		return rotatedAt(centroid(), angle);
	}

	inline Triangle Triangle::rotatedAt(const value_type x, const value_type y, const value_type angle) const noexcept
	{
		return rotatedAt({ x, y }, angle);
	}

	inline constexpr Triangle Triangle::scaled(const double s) const noexcept
	{
		return{ (p0 * s), (p1 * s), (p2 * s) };
	}

	inline constexpr Triangle Triangle::scaled(const double sx, const double sy) const noexcept
	{
		return scaled(Vec2{ sx, sy });
	}

	inline constexpr Triangle Triangle::scaled(const Vec2 s) const noexcept
	{
		return{ (p0 * s), (p1 * s), (p2 * s) };
	}

	inline constexpr Triangle& Triangle::scale(const double s) noexcept
	{
		p0 *= s;
		p1 *= s;
		p2 *= s;
		return *this;
	}

	inline constexpr Triangle& Triangle::scale(const double sx, const double sy) noexcept
	{
		return scale(Vec2{ sx, sy });
	}

	inline constexpr Triangle& Triangle::scale(const Vec2 s) noexcept
	{
		p0 *= s;
		p1 *= s;
		p2 *= s;
		return *this;
	}

	inline constexpr Triangle Triangle::scaledAt(const Vec2 pos, const double s) const noexcept
	{
		return{ (pos + (p0 - pos) * s), (pos + (p1 - pos) * s), (pos + (p2 - pos) * s) };
	}

	inline constexpr Triangle Triangle::scaledAt(const Vec2 pos, const double sx, const double sy) const noexcept
	{
		return scaledAt(pos, Vec2{ sx, sy });
	}

	inline constexpr Triangle Triangle::scaledAt(const Vec2 pos, const Vec2 s) const noexcept
	{
		return{ (pos + (p0 - pos) * s), (pos + (p1 - pos) * s), (pos + (p2 - pos) * s) };
	}

	inline constexpr Triangle& Triangle::scaleAt(const Vec2 pos, const double s) noexcept
	{
		p0 = (pos + (p0 - pos) * s);
		p1 = (pos + (p1 - pos) * s);
		p2 = (pos + (p2 - pos) * s);
		return *this;
	}

	inline constexpr Triangle& Triangle::scaleAt(const Vec2 pos, const double sx, const double sy) noexcept
	{
		return scaleAt(pos, Vec2{ sx, sy });
	}

	inline constexpr Triangle& Triangle::scaleAt(const Vec2 pos, const Vec2 s) noexcept
	{
		p0 = (pos + (p0 - pos) * s);
		p1 = (pos + (p1 - pos) * s);
		p2 = (pos + (p2 - pos) * s);
		return *this;
	}

	inline constexpr Triangle::position_type& Triangle::p(const size_t index) noexcept
	{
		return (&p0)[index];
	}

	inline constexpr const Triangle::position_type& Triangle::p(const size_t index) const noexcept
	{
		return (&p0)[index];
	}

	inline constexpr Triangle::position_type Triangle::point(const size_t index) const
	{
		if (index == 0)
		{
			return p0;
		}
		else if (index == 1)
		{
			return p1;
		}
		else if (index == 2)
		{
			return p2;
		}
		else
		{
			throw std::out_of_range("Triangle::point() index out of range");
		}
	}

	inline constexpr Line Triangle::side(size_t index) const
	{
		if (index == 0)
		{
			return{ p0, p1 };
		}
		else if (index == 1)
		{
			return{ p1, p2 };
		}
		else if (index == 2)
		{
			return{ p2, p0 };
		}
		else
		{
			throw std::out_of_range("Triangle::side() index out of range");
		}
	}

	inline Triangle::value_type Triangle::area() const noexcept
	{
		return std::abs((p0.x - p2.x) * (p1.y - p0.y) - (p0.x - p1.x) * (p2.y - p0.y)) * 0.5;
	}

	inline Triangle::value_type Triangle::perimeter() const noexcept
	{
		return (p0.distanceFrom(p1) + p1.distanceFrom(p2) + p2.distanceFrom(p0));
	}

	inline constexpr RectF Triangle::boundingRect() const noexcept
	{
		auto [xMin, xMax] = std::minmax({ p0.x, p1.x, p2.x });
		auto [yMin, yMax] = std::minmax({ p0.y, p1.y, p2.y });
		return{ xMin, yMin, (xMax - xMin), (yMax - yMin) };
	}
	
	inline constexpr Triangle Triangle::lerp(const Triangle& other, const double f) const noexcept
	{
		return{ p0.lerp(other.p0, f), p1.lerp(other.p1, f), p2.lerp(other.p2, f) };
	}

	inline size_t Triangle::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	inline constexpr bool Triangle::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> Triangle::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class Shape2DType>
	inline bool Triangle::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}
}
