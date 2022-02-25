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
	inline constexpr Ellipse::Ellipse(const size_type r) noexcept
		: center{ 0, 0 }
		, axes{ r, r } {}

	inline constexpr Ellipse::Ellipse(const size_type _a, const size_type _b) noexcept
		: center{ 0, 0 }
		, axes{ _a, _b } {}

	inline constexpr Ellipse::Ellipse(const value_type _x, const value_type _y, const size_type r) noexcept
		: center{ _x, _y }
		, axes{ r, r } {}

	inline constexpr Ellipse::Ellipse(const value_type _x, const value_type _y, const size_type _a, const size_type _b) noexcept
		: center{ _x, _y }
		, axes{ _a, _b } {}

	inline constexpr Ellipse::Ellipse(const position_type _center) noexcept
		: center{ _center }
		, axes{ 0, 0 } {}

	inline constexpr Ellipse::Ellipse(const position_type& _center, const size_type r) noexcept
		: center{ _center }
		, axes{ r, r } {}

	inline constexpr Ellipse::Ellipse(const position_type& _center, const size_type _a, const size_type _b) noexcept
		: center{ _center }
		, axes{ _a, _b } {}

	inline constexpr Ellipse::Ellipse(const value_type _x, const value_type _y, const Vec2& _axes) noexcept
		: center{ _x, _y }
		, axes{ _axes } {}

	inline constexpr Ellipse::Ellipse(const position_type& _center, const Vec2& _axes) noexcept
		: center{ _center }
		, axes{ _axes } {}

	inline constexpr Ellipse::Ellipse(const Circle& circle) noexcept
		: center{ circle.center }
		, axes{ circle.r, circle.r } {}

	inline constexpr Ellipse::Ellipse(const RectF& rect) noexcept
		: center{ rect.center() }
		, axes{ (rect.w * 0.5), (rect.h * 0.5) } {}

	inline constexpr Ellipse& Ellipse::set(const value_type _x, const value_type _y, const size_type _a, const size_type _b) noexcept
	{
		center.set(_x, _y);
		axes.set(_a, _b);
		return *this;
	}

	inline constexpr Ellipse& Ellipse::set(const value_type _x, const value_type _y, const size_type _r) noexcept
	{
		return set(_x, _y, _r, _r);
	}

	inline constexpr Ellipse& Ellipse::set(const position_type& _center, const size_type _r) noexcept
	{
		return set(_center.x, _center.y, _r, _r);
	}

	inline constexpr Ellipse& Ellipse::set(const position_type& _center, const size_type _a, const size_type _b) noexcept
	{
		return set(_center.x, _center.y, _a, _b);
	}

	inline constexpr Ellipse& Ellipse::set(const value_type _x, const value_type _y, const Vec2& _axes) noexcept
	{
		return set(_x, _y, _axes.x, _axes.y);
	}

	inline constexpr Ellipse& Ellipse::set(const position_type& _center, const Vec2& _axes) noexcept
	{
		return set(_center.x, _center.y, _axes.x, _axes.y);
	}

	inline constexpr Ellipse& Ellipse::set(const Circle& circle) noexcept
	{
		return set(circle.x, circle.y, circle.r, circle.r);
	}

	inline constexpr Ellipse& Ellipse::set(const RectF& rect) noexcept
	{
		return set(rect.center(), (rect.w * 0.5), (rect.h * 0.5));
	}

	inline constexpr Ellipse& Ellipse::set(const Ellipse& ellipse) noexcept
	{
		return *this = ellipse;
	}

	inline constexpr Ellipse& Ellipse::setCenter(const value_type _x, const value_type _y) noexcept
	{
		center.set(_x, _y);
		return *this;
	}

	inline constexpr Ellipse& Ellipse::setCenter(const position_type& _center) noexcept
	{
		return setCenter(_center.x, _center.y);
	}

	inline constexpr Ellipse& Ellipse::setPos(const value_type _x, const value_type _y) noexcept
	{
		return setCenter(_x, _y);
	}

	inline constexpr Ellipse& Ellipse::setPos(const position_type& _center) noexcept
	{
		return setCenter(_center.x, _center.y);
	}

	inline constexpr Ellipse& Ellipse::setAxes(const value_type _r) noexcept
	{
		return setAxes(_r, _r);
	}

	inline constexpr Ellipse& Ellipse::setAxes(const size_type _a, const size_type _b) noexcept
	{
		axes.set(_a, _b);
		return *this;
	}

	inline constexpr Ellipse& Ellipse::setAxes(const Vec2& _axes) noexcept
	{
		return setAxes(_axes.x, _axes.y);
	}

	inline constexpr Ellipse Ellipse::movedBy(const value_type _x, const value_type _y) const noexcept
	{
		return{ center.movedBy(_x, _y), axes };
	}

	inline constexpr Ellipse Ellipse::movedBy(const position_type& v) const noexcept
	{
		return movedBy(v.x, v.y);
	}

	inline constexpr Ellipse& Ellipse::moveBy(const value_type _x, const value_type _y) noexcept
	{
		center.moveBy(_x, _y);
		return *this;
	}

	inline constexpr Ellipse& Ellipse::moveBy(const position_type& v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	inline constexpr Ellipse Ellipse::stretched(const value_type size) const noexcept
	{
		return{ center, (a + size), (b + size) };
	}

	inline constexpr Ellipse Ellipse::stretched(const double _x, const double _y) const noexcept
	{
		return{ center, (a + _x), (b + _y) };
	}

	inline constexpr Ellipse Ellipse::scaled(const double s) const noexcept
	{
		return{ center, (a * s), (b * s) };
	}

	inline constexpr Ellipse Ellipse::scaled(const double sx, const double sy) const noexcept
	{
		return{ center, (a * sx), (b * sy) };
	}

	inline constexpr Ellipse::position_type Ellipse::top() const noexcept
	{
		return{ x, (y - b) };
	}

	inline constexpr Ellipse::position_type Ellipse::right() const noexcept
	{
		return{ (x + a), y };
	}

	inline constexpr Ellipse::position_type Ellipse::bottom() const noexcept
	{
		return{ x, (y + b) };
	}

	inline constexpr Ellipse::position_type Ellipse::left() const noexcept
	{
		return{ (x - a), y };
	}

	inline constexpr Line Ellipse::horizontalDiameter() const noexcept
	{
		return{ left(), right() };
	}

	inline constexpr Line Ellipse::verticalDiameter() const noexcept
	{
		return{ top(), bottom() };
	}

	inline constexpr Ellipse::value_type Ellipse::area() const noexcept
	{
		return (a * b * Math::Pi);
	}

	inline constexpr Circle Ellipse::boundingCircle() const noexcept
	{
		return{ center, Max(a, b) };
	}

	inline constexpr RectF Ellipse::boundingRect() const noexcept
	{
		return{ Arg::center = center, (a * 2), (b * 2) };
	}

	inline constexpr Ellipse Ellipse::lerp(const Ellipse& other, const double f) const noexcept
	{
		return{ center.lerp(other.center, f), axes.lerp(other.axes, f) };
	}

	inline size_t Ellipse::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	inline constexpr bool Ellipse::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> Ellipse::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class Shape2DType>
	inline bool Ellipse::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}
}
