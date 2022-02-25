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
	inline constexpr Quad::Quad(const value_type x0, const value_type y0, const value_type x1, const value_type y1, const value_type x2, const value_type y2, const value_type x3, const value_type y3) noexcept
		: p0{ x0, y0 }
		, p1{ x1, y1 }
		, p2{ x2, y2 }
		, p3{ x3, y3 } {}

	inline constexpr Quad::Quad(const position_type& _p0, const position_type& _p1, const position_type& _p2, const position_type& _p3) noexcept
		: p0{ _p0 }
		, p1{ _p1 }
		, p2{ _p2 }
		, p3{ _p3 } {}

	inline constexpr Quad::Quad(const Rect& rect) noexcept
		: p0{ rect.x, rect.y }
		, p1{ (rect.x + rect.w), rect.y }
		, p2{ (rect.x + rect.w), (rect.y + rect.h) }
		, p3{ rect.x, (rect.y + rect.h) } {}

	inline constexpr Quad::Quad(const RectF& rect) noexcept
		: p0{ rect.x, rect.y }
		, p1{ (rect.x + rect.w), rect.y }
		, p2{ (rect.x + rect.w), (rect.y + rect.h) }
		, p3{ rect.x, (rect.y + rect.h) } {}

	inline constexpr Quad& Quad::set(const value_type x0, const value_type y0, const value_type x1, const value_type y1, const value_type x2, const value_type y2, const value_type x3, const value_type y3) noexcept
	{
		p0.set(x0, y0);
		p1.set(x1, y1);
		p2.set(x2, y2);
		p3.set(x3, y3);
		return *this;
	}

	inline constexpr Quad& Quad::set(const position_type& _p0, const position_type& _p1, const position_type& _p2, const position_type& _p3) noexcept
	{
		p0.set(_p0);
		p1.set(_p1);
		p2.set(_p2);
		p3.set(_p3);
		return *this;
	}

	inline constexpr Quad& Quad::set(const Quad& quad) noexcept
	{
		return *this = quad;
	}

	inline constexpr Quad Quad::movedBy(const value_type x, const value_type y) const noexcept
	{
		return{ p0.movedBy(x, y), p1.movedBy(x, y), p2.movedBy(x, y), p3.movedBy(x, y) };
	}

	inline constexpr Quad Quad::movedBy(const position_type v) const noexcept
	{
		return movedBy(v.x, v.y);
	}

	inline constexpr Quad& Quad::moveBy(const value_type x, const value_type y) noexcept
	{
		p0.moveBy(x, y);
		p1.moveBy(x, y);
		p2.moveBy(x, y);
		p3.moveBy(x, y);
		return *this;
	}

	inline constexpr Quad& Quad::moveBy(const position_type v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	inline Quad Quad::rotatedAt(const value_type x, const value_type y, const value_type angle) const noexcept
	{
		return rotatedAt({ x, y }, angle);
	}

	inline constexpr Quad Quad::scaled(const double s) const noexcept
	{
		return{ (p0 * s), (p1 * s), (p2 * s), (p3 * s) };
	}

	inline constexpr Quad Quad::scaled(const double sx, const double sy) const noexcept
	{
		return scaled(Vec2{ sx, sy });
	}

	inline constexpr Quad Quad::scaled(const Vec2 s) const noexcept
	{
		return{ (p0 * s), (p1 * s), (p2 * s), (p3 * s) };
	}

	inline constexpr Quad& Quad::scale(const double s) noexcept
	{
		p0 *= s;
		p1 *= s;
		p2 *= s;
		p3 *= s;
		return *this;
	}

	inline constexpr Quad& Quad::scale(const double sx, const double sy) noexcept
	{
		return scale(Vec2{ sx, sy });
	}

	inline constexpr Quad& Quad::scale(const Vec2 s) noexcept
	{
		p0 *= s;
		p1 *= s;
		p2 *= s;
		p3 *= s;
		return *this;
	}

	inline constexpr Quad Quad::scaledAt(const Vec2 pos, const double s) const noexcept
	{
		return{ (pos + (p0 - pos) * s), (pos + (p1 - pos) * s), (pos + (p2 - pos) * s), (pos + (p3 - pos) * s) };
	}

	inline constexpr Quad Quad::scaledAt(const Vec2 pos, const double sx, const double sy) const noexcept
	{
		return scaledAt(pos, Vec2{ sx, sy });
	}

	inline constexpr Quad Quad::scaledAt(const Vec2 pos, const Vec2 s) const noexcept
	{
		return{ (pos + (p0 - pos) * s), (pos + (p1 - pos) * s), (pos + (p2 - pos) * s), (pos + (p3 - pos) * s) };
	}

	inline constexpr Quad& Quad::scaleAt(const Vec2 pos, const double s) noexcept
	{
		p0 = (pos + (p0 - pos) * s);
		p1 = (pos + (p1 - pos) * s);
		p2 = (pos + (p2 - pos) * s);
		p3 = (pos + (p3 - pos) * s);
		return *this;
	}

	inline constexpr Quad& Quad::scaleAt(const Vec2 pos, const double sx, const double sy) noexcept
	{
		return scaleAt(pos, Vec2{ sx, sy });
	}

	inline constexpr Quad& Quad::scaleAt(const Vec2 pos, const Vec2 s) noexcept
	{
		p0 = (pos + (p0 - pos) * s);
		p1 = (pos + (p1 - pos) * s);
		p2 = (pos + (p2 - pos) * s);
		p3 = (pos + (p3 - pos) * s);
		return *this;
	}

	inline Quad::position_type& Quad::p(const size_t index) noexcept
	{
		return (&p0)[index];
	}

	inline const Quad::position_type& Quad::p(const size_t index) const noexcept
	{
		return (&p0)[index];
	}

	inline constexpr Quad::position_type Quad::point(const size_t index) const
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
		else if (index == 3)
		{
			return p3;
		}
		else
		{
			throw std::out_of_range("Quad::point() index out of range");
		}
	}

	inline constexpr Line Quad::side(const size_t index) const
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
			return{ p2, p3 };
		}
		else if (index == 3)
		{
			return{ p3, p0 };
		}
		else
		{
			throw std::out_of_range("Quad::side() index out of range");
		}
	}

	constexpr Triangle Quad::triangle(const size_t index) const
	{
		if (index == 0)
		{
			return{ p0, p1, p3 };
		}
		else if (index == 1)
		{
			return{ p3, p1, p2 };
		}
		else
		{
			throw std::out_of_range("Quad::triangle() index out of range");
		}
	}

	inline constexpr Quad::value_type Quad::area() const noexcept
	{
		const value_type s0 = Abs((p0.x - p2.x) * (p1.y - p0.y) - (p0.x - p1.x) * (p2.y - p0.y));
		const value_type s1 = Abs((p2.x - p0.x) * (p3.y - p2.y) - (p2.x - p3.x) * (p0.y - p2.y));
		return ((s0 + s1) * 0.5);
	}

	inline constexpr RectF Quad::boundingRect() const noexcept
	{
		const auto [xMin, xMax] = std::minmax({ p0.x, p1.x, p2.x, p3.x });
		const auto [yMin, yMax] = std::minmax({ p0.y, p1.y, p2.y, p3.y });
		return{ xMin, yMin, (xMax - xMin), (yMax - yMin) };
	}

	inline constexpr Quad Quad::lerp(const Quad& other, double f) const noexcept
	{
		return{ p0.lerp(other.p0, f), p1.lerp(other.p1, f), p2.lerp(other.p2, f), p3.lerp(other.p3, f) };
	}

	inline size_t Quad::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	inline constexpr bool Quad::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> Quad::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class Shape2DType>
	inline bool Quad::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}
}
