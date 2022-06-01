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
	inline constexpr RoundRect::RoundRect(const value_type _x, const value_type _y, const value_type _w, const value_type _h, const value_type _r) noexcept
		: rect{ _x, _y, _w, _h }
		, r{ _r } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic R>
# else
	template <class X, class Y, class W, class H, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<R>>>*>
# endif
	inline constexpr RoundRect::RoundRect(const X _x, const Y _y, const W _w, const H _h, const R _r) noexcept
		: rect{ static_cast<value_type>(_x), static_cast<value_type>(_y), static_cast<value_type>(_w), static_cast<value_type>(_h) }
		, r{ static_cast<value_type>(_r) } {}

	inline constexpr RoundRect::RoundRect(const position_type pos, const value_type _w, const value_type _h, const value_type _r) noexcept
		: rect{ pos, _w, _h }
		, r{ _r } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic W, Concept::Arithmetic H, Concept::Arithmetic R>
# else
	template <class W, class H, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<W>, std::is_arithmetic<H>, std::is_arithmetic<R>>>*>
# endif
	inline constexpr RoundRect::RoundRect(const position_type pos, const W _w, const H _h, const R _r) noexcept
		: rect{ pos, static_cast<value_type>(_w), static_cast<value_type>(_h) }
		, r{ static_cast<value_type>(_r) } {}

	inline constexpr RoundRect::RoundRect(const value_type _x, const value_type _y, const size_type size, const value_type _r) noexcept
		: rect{ _x, _y, size }
		, r{ _r } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic X, Concept::Arithmetic Y, Concept::Arithmetic R>
# else
	template <class X, class Y, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<X>, std::is_arithmetic<Y>, std::is_arithmetic<R>>>*>
# endif
	inline constexpr RoundRect::RoundRect(const X _x, const Y _y, const size_type size, const R _r) noexcept
		: rect{ static_cast<value_type>(_x), static_cast<value_type>(_y), size }
		, r{ static_cast<value_type>(_r) } {}

	inline constexpr RoundRect::RoundRect(const position_type pos, const value_type size, const value_type _r) noexcept
		: rect{ pos, size }
		, r{ _r } {}

# if __cpp_lib_concepts
	template <Concept::Arithmetic S, Concept::Arithmetic R>
# else
	template <class S, class R, std::enable_if_t<std::conjunction_v<std::is_arithmetic<S>, std::is_arithmetic<R>>>*>
# endif
	inline constexpr RoundRect::RoundRect(const position_type pos, const S size, const R _r) noexcept
		: rect{ pos, static_cast<value_type>(size), static_cast<value_type>(size) }
		, r{ static_cast<value_type>(_r) } {}

	inline constexpr RoundRect::RoundRect(const position_type pos, const size_type size, const value_type _r) noexcept
		: rect{ pos, size }
		, r{ _r } {}

	inline constexpr RoundRect::RoundRect(const Arg::center_<position_type> _center, const value_type _w, const value_type _h, const value_type _r) noexcept
		: rect{ _center, _w, _h }
		, r{ _r } {}

	inline constexpr RoundRect::RoundRect(const Arg::center_<position_type> _center, const size_type size, const value_type _r) noexcept
		: rect{ _center, size }
		, r{ _r } {}

	inline constexpr RoundRect::RoundRect(const RectF& _rect, const value_type _r) noexcept
		: rect{ _rect }
		, r{ _r } {}

	inline constexpr RoundRect& RoundRect::set(const value_type _x, const value_type _y, const value_type _w, const value_type _h, const value_type _r) noexcept
	{
		rect.set(_x, _y, _w, _h);
		r = _r;
		return *this;
	}

	inline constexpr RoundRect& RoundRect::set(const position_type& pos, const value_type _w, const value_type _h, const value_type _r) noexcept
	{
		return set(pos.x, pos.y, _w, _h, _r);
	}

	inline constexpr RoundRect& RoundRect::set(const value_type _x, const value_type _y, const size_type& size, const value_type _r) noexcept
	{
		return set(_x, _y, size.x, size.y, _r);
	}

	inline constexpr RoundRect& RoundRect::set(const position_type& pos, const size_type& size, const value_type _r) noexcept
	{
		return set(pos.x, pos.y, size.x, size.y, _r);
	}

	inline constexpr RoundRect& RoundRect::set(const RectF& _rect, const value_type _r) noexcept
	{
		return set(_rect.x, _rect.y, _rect.w, _rect.h, _r);
	}

	inline constexpr RoundRect& RoundRect::set(const RoundRect& roundRect) noexcept
	{
		return *this = roundRect;
	}

	inline constexpr RoundRect& RoundRect::setPos(const value_type _x, const value_type _y) noexcept
	{
		rect.setPos(_x, _y);
		return *this;
	}

	inline constexpr RoundRect& RoundRect::setPos(const position_type _pos) noexcept
	{
		return setPos(_pos.x, _pos.y);
	}

	inline constexpr RoundRect& RoundRect::setCenter(const value_type _x, const value_type _y) noexcept
	{
		rect.setCenter(_x, _y);
		return *this;
	}

	inline constexpr RoundRect& RoundRect::setCenter(const position_type _center) noexcept
	{
		return setCenter(_center.x, _center.y);
	}

	inline constexpr RoundRect& RoundRect::setSize(const value_type _w, const value_type _h) noexcept
	{
		rect.setSize(_w, _h);
		return *this;
	}

	inline constexpr RoundRect& RoundRect::setSize(const size_type _size) noexcept
	{
		return setSize(_size.x, _size.y);
	}

	inline constexpr RoundRect RoundRect::movedBy(const value_type _x, const value_type _y) const noexcept
	{
		return{ rect.movedBy(_x, _y), r };
	}

	inline constexpr RoundRect RoundRect::movedBy(const position_type v) const noexcept
	{
		return movedBy(v.x, v.y);
	}

	inline constexpr RoundRect& RoundRect::moveBy(const value_type _x, const value_type _y) noexcept
	{
		rect.moveBy(_x, _y);
		return *this;
	}

	inline constexpr RoundRect& RoundRect::moveBy(const position_type v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	inline constexpr RoundRect RoundRect::stretched(const value_type size) const noexcept
	{
		return RoundRect{ rect.stretched(size), r };
	}

	inline constexpr RoundRect RoundRect::stretched(const value_type _x, const value_type _y) const noexcept
	{
		return RoundRect{ rect.stretched(_x, _y), r };
	}

	inline constexpr RoundRect RoundRect::stretched(const size_type xy) const noexcept
	{
		return RoundRect{ rect.stretched(xy.x, xy.y), r };
	}

	inline constexpr RoundRect RoundRect::stretched(const value_type top, const value_type right, const value_type bottom, const value_type left) const noexcept
	{
		return RoundRect{ rect.stretched(top, right, bottom, left), r };
	}

	inline constexpr RoundRect::position_type RoundRect::topCenter() const noexcept
	{
		return rect.topCenter();
	}

	inline constexpr RoundRect::position_type RoundRect::bottomCenter() const noexcept
	{
		return rect.bottomCenter();
	}

	inline constexpr RoundRect::position_type RoundRect::leftCenter() const noexcept
	{
		return rect.leftCenter();
	}

	inline constexpr RoundRect::position_type RoundRect::rightCenter() const noexcept
	{
		return rect.rightCenter();
	}

	inline constexpr RoundRect::position_type RoundRect::center() const noexcept
	{
		return rect.center();
	}

	inline constexpr RoundRect::value_type RoundRect::area() const noexcept
	{
		return (rect.area() - (4 - Math::Pi) * r * r);
	}

	inline constexpr RoundRect::value_type RoundRect::perimeter() const noexcept
	{
		return (rect.perimeter() + r * (2 * Math::Pi - 8));
	}

	inline constexpr RoundRect::value_type RoundRect::horizontalAspectRatio() const noexcept
	{
		return rect.horizontalAspectRatio();
	}

	inline constexpr RoundRect RoundRect::lerp(const RoundRect& other, const double f) const noexcept
	{
		return{ rect.lerp(other.rect, f), (r + (other.r - r) * f) };
	}

	inline size_t RoundRect::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	inline constexpr bool RoundRect::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> RoundRect::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class Shape2DType>
	inline bool RoundRect::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}
}
