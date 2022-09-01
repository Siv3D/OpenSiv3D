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
	inline constexpr Rect::Rect(const value_type _size) noexcept
		: pos{ 0, 0 }
		, size{ _size, _size } {}

	SIV3D_CONCEPT_INTEGRAL_
	inline constexpr Rect::Rect(const Int _size) noexcept
		: pos{ 0, 0 }
		, size{ static_cast<value_type>(_size), static_cast<value_type>(_size) } {}

	inline constexpr Rect::Rect(const value_type _w, const value_type _h) noexcept
		: pos{ 0, 0 }
		, size{ _w, _h } {}

# if __cpp_lib_concepts
	template <Concept::Integral W, Concept::Integral H>
# else
	template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_integral<W>, std::is_integral<H>>>*>
# endif
	inline constexpr Rect::Rect(const W _w, const H _h) noexcept
		: pos{ 0, 0 }
		, size{ static_cast<value_type>(_w), static_cast<value_type>(_h) } {}

	inline constexpr Rect::Rect(const size_type _size) noexcept
		: pos{ 0, 0 }
		, size{ _size } {}

	inline constexpr Rect::Rect(const value_type _x, const value_type _y, const value_type _size) noexcept
		: pos{ _x, _y }
		, size{ _size, _size } {}

# if __cpp_lib_concepts
	template <Concept::Integral X, Concept::Integral Y, Concept::Integral S>
# else
	template <class X, class Y, class S, std::enable_if_t<std::conjunction_v<std::is_integral<X>, std::is_integral<Y>, std::is_integral<S>>>*>
# endif	
	inline constexpr Rect::Rect(const X _x, const Y _y, const S _size) noexcept
		: pos{ static_cast<value_type>(_x), static_cast<value_type>(_y) }
		, size{ static_cast<value_type>(_size), static_cast<value_type>(_size) } {}

	inline constexpr Rect::Rect(const value_type _x, const value_type _y, const value_type _w, const value_type _h) noexcept
		: pos{ _x, _y }
		, size{ _w, _h } {}

# if __cpp_lib_concepts
	template <Concept::Integral X, Concept::Integral Y, Concept::Integral W, Concept::Integral H>
# else
	template <class X, class Y, class W, class H, std::enable_if_t<std::conjunction_v<std::is_integral<X>, std::is_integral<Y>, std::is_integral<W>, std::is_integral<H>>>*>
# endif
	inline constexpr Rect::Rect(const X _x, const Y _y, const W _w, const H _h) noexcept
		: pos{ static_cast<value_type>(_x), static_cast<value_type>(_y) }
		, size{ static_cast<value_type>(_w), static_cast<value_type>(_h) } {}

	inline constexpr Rect::Rect(const value_type _x, const value_type _y, const size_type _size) noexcept
		: pos{ _x, _y }
		, size{ _size } {}

# if __cpp_lib_concepts
	template <Concept::Integral X, Concept::Integral Y>
# else
	template <class X, class Y, std::enable_if_t<std::conjunction_v<std::is_integral<X>, std::is_integral<Y>>>*>
# endif
	inline constexpr Rect::Rect(const X _x, const Y _y, const size_type _size) noexcept
		: pos{ static_cast<value_type>(_x), static_cast<value_type>(_y) }
		, size{ _size } {}

	inline constexpr Rect::Rect(const position_type _pos, const value_type _size) noexcept
		: pos{ _pos }
		, size{ _size, _size } {}

	SIV3D_CONCEPT_INTEGRAL_
	inline constexpr Rect::Rect(const position_type _pos, const Int _size) noexcept
		: pos{ _pos }
		, size{ static_cast<value_type>(_size), static_cast<value_type>(_size) } {}

	inline constexpr Rect::Rect(const position_type _pos, const value_type _w, const value_type _h) noexcept
		: pos{ _pos }
		, size{ _w, _h } {}

# if __cpp_lib_concepts
	template <Concept::Integral W, Concept::Integral H>
# else
	template <class W, class H, std::enable_if_t<std::conjunction_v<std::is_integral<W>, std::is_integral<H>>>*>
# endif
	inline constexpr Rect::Rect(const position_type _pos, const W _w, const H _h) noexcept
		: pos{ _pos }
		, size{ static_cast<value_type>(_w), static_cast<value_type>(_h) } {}

	inline constexpr Rect::Rect(const position_type _pos, const size_type _size) noexcept
		: pos{ _pos }
		, size{ _size } {}

	inline constexpr Rect::Rect(const Arg::center_<position_type> _center, const value_type _size) noexcept
		: pos{ (_center->x - _size / 2), (_center->y - _size / 2) }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::center_<position_type> _center, const value_type _w, const value_type _h) noexcept
		: pos{ (_center->x - _w / 2), (_center->y - _h / 2) }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::center_<position_type> _center, const size_type _size) noexcept
		: pos{ (_center->x - _size.x / 2), (_center->y - _size.y / 2) }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::topLeft_<position_type> topLeft, const value_type _size) noexcept
		: pos{ topLeft->x, topLeft->y }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::topLeft_<position_type> topLeft, const value_type _w, const value_type _h) noexcept
		: pos{ topLeft->x, topLeft->y }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::topLeft_<position_type> topLeft, const size_type _size) noexcept
		: pos{ topLeft->x, topLeft->y }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::topCenter_<position_type> topCenter, const value_type _size) noexcept
		: pos{ (topCenter->x - _size / 2), topCenter->y }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::topCenter_<position_type> topCenter, const value_type _w, const value_type _h) noexcept
		: pos{ (topCenter->x - _w / 2), topCenter->y }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::topCenter_<position_type> topCenter, const size_type _size) noexcept
		: pos{ (topCenter->x - _size.x / 2), topCenter->y }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::topRight_<position_type> topRight, const value_type _size) noexcept
		: pos{ (topRight->x - _size), topRight->y }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::topRight_<position_type> topRight, const value_type _w, const value_type _h) noexcept
		: pos{ (topRight->x - _w), topRight->y }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::topRight_<position_type> topRight, const size_type _size) noexcept
		: pos{ (topRight->x - _size.x), topRight->y }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::rightCenter_<position_type> rightCenter, const value_type _size) noexcept
		: pos{ (rightCenter->x - _size), (rightCenter->y - _size / 2) }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::rightCenter_<position_type> rightCenter, const value_type _w, const value_type _h) noexcept
		: pos{ (rightCenter->x - _w), (rightCenter->y - _h / 2) }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::rightCenter_<position_type> rightCenter, const size_type _size) noexcept
		: pos{ (rightCenter->x - _size.x), (rightCenter->y - _size.y / 2) }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::bottomRight_<position_type> bottomRight, const value_type _size) noexcept
		: pos{ (bottomRight->x - _size), (bottomRight->y - _size) }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::bottomRight_<position_type> bottomRight, const value_type _w, const value_type _h) noexcept
		: pos{ (bottomRight->x - _w), (bottomRight->y - _h) }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::bottomRight_<position_type> bottomRight, const size_type _size) noexcept
		: pos{ (bottomRight->x - _size.x), (bottomRight->y - _size.y) }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _size) noexcept
		: pos{ (bottomCenter->x - _size / 2), (bottomCenter->y - _size) }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _w, const value_type _h) noexcept
		: pos{ (bottomCenter->x - _w / 2), (bottomCenter->y - _h) }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::bottomCenter_<position_type> bottomCenter, const size_type _size) noexcept
		: pos{ (bottomCenter->x - _size.x / 2), (bottomCenter->y - _size.y) }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _size) noexcept
		: pos{ bottomLeft->x, (bottomLeft->y - _size) }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _w, const value_type _h) noexcept
		: pos{ bottomLeft->x, (bottomLeft->y - _h) }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::bottomLeft_<position_type> bottomLeft, const size_type _size) noexcept
		: pos{ bottomLeft->x, (bottomLeft->y - _size.y) }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect::Rect(const Arg::leftCenter_<position_type> leftCenter, const value_type _size) noexcept
		: pos{ leftCenter->x, (leftCenter->y - _size / 2) }
		, size{ _size, _size } {}

	inline constexpr Rect::Rect(const Arg::leftCenter_<position_type> leftCenter, const value_type _w, const value_type _h) noexcept
		: pos{ leftCenter->x, (leftCenter->y - _h / 2) }
		, size{ _w, _h } {}

	inline constexpr Rect::Rect(const Arg::leftCenter_<position_type> leftCenter, const size_type _size) noexcept
		: pos{ leftCenter->x, (leftCenter->y - _size.y / 2) }
		, size{ _size.x, _size.y } {}

	inline constexpr Rect& Rect::setPos(const value_type _x, const value_type _y) noexcept
	{
		pos.set(_x, _y);
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const position_type _pos) noexcept
	{
		pos.set(_pos);
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const Arg::center_<position_type> _center) noexcept
	{
		return setCenter(_center.value());
	}

	inline constexpr Rect& Rect::setPos(const Arg::topLeft_<position_type> topLeft) noexcept
	{
		return setPos(topLeft.value());
	}

	inline constexpr Rect& Rect::setPos(const Arg::topCenter_<position_type> topCenter) noexcept
	{
		pos.set((topCenter->x - w / 2), topCenter->y);
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const Arg::topRight_<position_type> topRight) noexcept
	{
		pos.set(topRight->x - w, topRight->y);
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const Arg::rightCenter_<position_type> rightCenter) noexcept
	{
		pos.set((rightCenter->x - w), (rightCenter->y - h / 2));
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const Arg::bottomRight_<position_type> bottomRight) noexcept
	{
		pos.set((bottomRight->x - w), (bottomRight->y - h));
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const Arg::bottomCenter_<position_type> bottomCenter) noexcept
	{
		pos.set((bottomCenter->x - w / 2), (bottomCenter->y - h));
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const Arg::bottomLeft_<position_type> bottomLeft) noexcept
	{
		pos.set(bottomLeft->x, bottomLeft->y - h);
		return *this;
	}

	inline constexpr Rect& Rect::setPos(const Arg::leftCenter_<position_type> leftCenter) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - h / 2));
		return *this;
	}

	inline constexpr Rect& Rect::setCenter(const value_type _x, const value_type _y) noexcept
	{
		pos.set((_x - w / 2), (_y - h / 2));
		return *this;
	}

	inline constexpr Rect& Rect::setCenter(const position_type _pos) noexcept
	{
		pos.set((_pos.x - w / 2), (_pos.y - h / 2));
		return *this;
	}

	inline constexpr Rect& Rect::setSize(const value_type _size) noexcept
	{
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::setSize(const value_type _w, const value_type _h) noexcept
	{
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::setSize(const size_type _size) noexcept
	{
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const value_type _x, const value_type _y, const value_type _w, const value_type _h) noexcept
	{
		pos.set(_x, _y);
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const value_type _x, const value_type _y, const value_type _size) noexcept
	{
		pos.set(_x, _y);
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const value_type _x, const value_type _y, const size_type _size) noexcept
	{
		pos.set(_x, _y);
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(position_type _pos, const value_type _size) noexcept
	{
		pos.set(_pos);
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(position_type _pos, const value_type _w, const value_type _h) noexcept
	{
		pos.set(_pos);
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(position_type _pos, const size_type _size) noexcept
	{
		pos.set(_pos);
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Rect& r) noexcept
	{
		pos.set(r.pos);
		size.set(r.size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::center_<position_type> _center, const value_type _size) noexcept
	{
		pos.set((_center->x - _size / 2), (_center->y - _size / 2));
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::center_<position_type> _center, const value_type _w, const value_type _h) noexcept
	{
		pos.set((_center->x - _w / 2), (_center->y - _h / 2));
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::center_<position_type> _center, const size_type _size) noexcept
	{
		pos.set((_center->x - _size.x / 2), (_center->y - _size.y / 2));
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topLeft_<position_type> topLeft, const value_type _size) noexcept
	{
		pos.set(topLeft.value());
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topLeft_<position_type> topLeft, const value_type _w, const value_type _h) noexcept
	{
		pos.set(topLeft.value());
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topLeft_<position_type> topLeft, const size_type _size) noexcept
	{
		pos.set(topLeft.value());
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topCenter_<position_type> topCenter, const value_type _size) noexcept
	{
		pos.set((topCenter->x - _size / 2), topCenter->y);
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topCenter_<position_type> topCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set((topCenter->x - _w / 2), topCenter->y);
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topCenter_<position_type> topCenter, const size_type _size) noexcept
	{
		pos.set((topCenter->x - _size.x / 2), topCenter->y);
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topRight_<position_type> topRight, const value_type _size) noexcept
	{
		pos.set((topRight->x - _size), topRight->y);
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topRight_<position_type> topRight, const value_type _w, const value_type _h) noexcept
	{
		pos.set((topRight->x - _w), topRight->y);
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::topRight_<position_type> topRight, const size_type _size) noexcept
	{
		pos.set((topRight->x - _size.x), topRight->y);
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::rightCenter_<position_type> rightCenter, const value_type _size) noexcept
	{
		pos.set((rightCenter->x - _size), (rightCenter->y - _size / 2));
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::rightCenter_<position_type> rightCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set((rightCenter->x - _w), (rightCenter->y - _h / 2));
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::rightCenter_<position_type> rightCenter, const size_type _size) noexcept
	{
		pos.set(rightCenter->x - _size.x, rightCenter->y - _size.y / 2);
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomRight_<position_type> bottomRight, const value_type _size) noexcept
	{
		pos.set((bottomRight->x - _size), (bottomRight->y - _size));
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomRight_<position_type> bottomRight, const value_type _w, const value_type _h) noexcept
	{
		pos.set((bottomRight->x - _w), (bottomRight->y - _h));
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomRight_<position_type> bottomRight, const size_type _size) noexcept
	{
		pos.set((bottomRight->x - _size.x), (bottomRight->y - _size.y));
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _size) noexcept
	{
		pos.set((bottomCenter->x - _size / 2), (bottomCenter->y - _size));
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set((bottomCenter->x - _w / 2), (bottomCenter->y - _h));
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomCenter_<position_type> bottomCenter, const size_type _size) noexcept
	{
		pos.set((bottomCenter->x - _size.x / 2), (bottomCenter->y - _size.y));
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _size) noexcept
	{
		pos.set(bottomLeft->x, (bottomLeft->y - _size));
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _w, const value_type _h) noexcept
	{
		pos.set(bottomLeft->x, (bottomLeft->y - _h));
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::bottomLeft_<position_type> bottomLeft, const size_type _size) noexcept
	{
		pos.set(bottomLeft->x, (bottomLeft->y - _size.y));
		size.set(_size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::leftCenter_<position_type> leftCenter, const value_type _size) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - _size / 2));
		size.set(_size, _size);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::leftCenter_<position_type> leftCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - _h / 2));
		size.set(_w, _h);
		return *this;
	}

	inline constexpr Rect& Rect::set(const Arg::leftCenter_<position_type> leftCenter, const size_type _size) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - _size.y / 2));
		size.set(_size);
		return *this;
	}

	inline constexpr Rect Rect::movedBy(const value_type _x, const value_type _y) const noexcept
	{
		return{ pos.movedBy(_x, _y), size };
	}

	inline constexpr Rect Rect::movedBy(const size_type v) const noexcept
	{
		return{ pos.movedBy(v), size };
	}

	inline constexpr Rect& Rect::moveBy(const value_type _x, const value_type _y) noexcept
	{
		pos.moveBy(_x, _y);
		return *this;
	}

	inline constexpr Rect& Rect::moveBy(const size_type v) noexcept
	{
		pos.moveBy(v);
		return *this;
	}

	constexpr Rect Rect::stretched(const value_type xy) const noexcept
	{
		return stretched({ xy, xy });
	}

	inline constexpr Rect Rect::stretched(const value_type _x, const value_type _y) const noexcept
	{
		return stretched({ _x, _y });
	}

	inline constexpr Rect Rect::stretched(const size_type xy) const noexcept
	{
		return{ (pos - xy), (size + xy * 2) };
	}

	inline constexpr Rect Rect::stretched(const value_type top, const value_type right, const value_type bottom, const value_type left) const noexcept
	{
		return{ (pos.x - left), (pos.y - top), (size.x + left + right), (size.y + top + bottom) };
	}

	inline constexpr RectF Rect::scaled(const double s) const noexcept
	{
		return{ Arg::center((pos.x + size.x * 0.5), (pos.y + size.y * 0.5)), (size.x * s), (size.y * s) };
	}

	inline constexpr RectF Rect::scaled(const double sx, const double sy) const noexcept
	{
		return{ Arg::center((pos.x + size.x * 0.5), (pos.y + size.y * 0.5)), (size.x * sx), (size.y * sy) };
	}

	inline constexpr RectF Rect::scaled(const Vec2 s) const noexcept
	{
		return{ Arg::center((pos.x + size.x * 0.5), (pos.y + size.y * 0.5)), (size.x * s.x), (size.y * s.y) };
	}

	inline constexpr RectF Rect::scaledAt(const Vec2 _pos, const double s) const noexcept
	{
		return{ (_pos.x + (pos.x - _pos.x) * s), (_pos.y + (pos.y - _pos.y) * s), (size.x * s), (size.y * s) };
	}

	inline constexpr RectF Rect::scaledAt(const Vec2 _pos, const double sx, const double sy) const noexcept
	{
		return{ (_pos.x + (pos.x - _pos.x) * sx), (_pos.y + (pos.y - _pos.y) * sy), (size.x * sx), (size.y * sy) };
	}

	inline constexpr RectF Rect::scaledAt(const Vec2 _pos, const Vec2 s) const noexcept
	{
		return{ (_pos.x + (pos.x - _pos.x) * s.x), (_pos.y + (pos.y - _pos.y) * s.y), (size.x * s.x), (size.y * s.y) };
	}

	inline constexpr Rect::operator bool() const noexcept
	{
		return hasArea();
	}

	inline constexpr bool Rect::isEmpty() const noexcept
	{
		return ((size.x == 0) || (size.y == 0));
	}

	inline constexpr bool Rect::hasArea() const noexcept
	{
		return ((size.x != 0) && (size.y != 0));
	}

	inline constexpr Rect::value_type Rect::leftX() const noexcept
	{
		return x;
	}

	inline constexpr Rect::value_type Rect::rightX() const noexcept
	{
		return (x + w);
	}

	inline constexpr Rect::value_type Rect::topY() const noexcept
	{
		return y;
	}

	inline constexpr Rect::value_type Rect::bottomY() const noexcept
	{
		return (y + h);
	}

	inline constexpr double Rect::centerX() const noexcept
	{
		return (x + w * 0.5);
	}

	inline constexpr double Rect::centerY() const noexcept
	{
		return (y + h * 0.5);
	}

	inline constexpr Rect::size_type Rect::tl() const noexcept
	{
		return pos;
	}

	inline constexpr Rect::size_type Rect::tr() const noexcept
	{
		return{ (pos.x + size.x), pos.y };
	}

	inline constexpr Rect::size_type Rect::br() const noexcept
	{
		return{ (pos.x + size.x), (pos.y + size.y) };
	}

	inline constexpr Rect::size_type Rect::bl() const noexcept
	{
		return{ pos.x, (pos.y + size.y) };
	}

	inline constexpr Vec2 Rect::topCenter() const noexcept
	{
		return{ (pos.x + size.x * 0.5), pos.y };
	}

	inline constexpr Vec2 Rect::rightCenter() const noexcept
	{
		return{ (pos.x + size.x), (pos.y + size.y * 0.5) };
	}

	inline constexpr Vec2 Rect::bottomCenter() const noexcept
	{
		return{ (pos.x + size.x * 0.5), (pos.y + size.y) };
	}

	inline constexpr Vec2 Rect::leftCenter() const noexcept
	{
		return{ pos.x, (pos.y + size.y * 0.5) };
	}

	inline constexpr Vec2 Rect::center() const noexcept
	{
		return{ (pos.x + size.x * 0.5), (pos.y + size.y * 0.5) };
	}

	inline constexpr Vec2 Rect::getRelativePoint(const double relativeX, const double relativeY) const noexcept
	{
		return{ (x + w * relativeX), (y + h * relativeY) };
	}

	inline constexpr Line Rect::top() const noexcept
	{
		return{ tl(), tr() };
	}

	inline constexpr Line Rect::right() const noexcept
	{
		return{ tr(), br() };
	}

	inline constexpr Line Rect::bottom() const noexcept
	{
		return{ br(), bl() };
	}

	inline constexpr Line Rect::left() const noexcept
	{
		return{ bl(), tl() };
	}

	inline constexpr Rect::position_type Rect::point(const size_t index) const
	{
		if (index == 0)
		{
			return tl();
		}
		else if (index == 1)
		{
			return tr();
		}
		else if (index == 2)
		{
			return br();
		}
		else if (index == 3)
		{
			return bl();
		}
		else
		{
			throw std::out_of_range("Rect::point() index out of range");
		}
	}

	inline constexpr Line Rect::side(const size_t index) const
	{
		if (index == 0)
		{
			return top();
		}
		else if (index == 1)
		{
			return right();
		}
		else if (index == 2)
		{
			return bottom();
		}
		else if (index == 3)
		{
			return left();
		}
		else
		{
			throw std::out_of_range("Rect::side() index out of range");
		}
	}

	inline constexpr Triangle Rect::triangle(const size_t index) const
	{
		if (index == 0)
		{
			return{ pos, tr(), bl() };
		}
		else if (index == 1)
		{
			return{ bl(), tr(), br() };
		}
		else
		{
			throw std::out_of_range("Rect::triangle() index out of range");
		}
	}

	inline constexpr Rect::value_type Rect::area() const noexcept
	{
		return (size.x * size.y);
	}

	inline constexpr Rect::value_type Rect::perimeter() const noexcept
	{
		return ((size.x + size.y) * 2);
	}

	template <class Type>
	inline constexpr Type Rect::horizontalAspectRatio() const noexcept
	{
		if (size.y == 0)
		{
			return 0;
		}

		return (static_cast<Type>(size.x) / size.y);
	}

	inline constexpr Quad Rect::shearedX(const double vx) const noexcept
	{
		return{ {(pos.x + vx), pos.y}, {(pos.x + size.x + vx), pos.y}, {(pos.x + size.x - vx), (pos.y + size.y)}, {(pos.x - vx), (pos.y + size.y)} };
	}

	inline constexpr Quad Rect::shearedY(const double vy) const noexcept
	{
		return{ {pos.x, (pos.y - vy)}, {(pos.x + size.x), (pos.y + vy)}, {(pos.x + size.x), (pos.y + size.y + vy)}, {pos.x, (pos.y + size.y - vy)} };
	}

	inline constexpr RoundRect Rect::rounded(const double r) const noexcept
	{
		return{ *this, r };
	}

	inline constexpr Quad Rect::asQuad() const noexcept
	{
		return{ tl(), tr(), br(), bl() };
	}

	inline constexpr RectF Rect::lerp(const Rect& other, const double f) const noexcept
	{
		return{ pos.lerp(other.pos, f), size.lerp(other.size, f) };
	}

	inline constexpr RectF Rect::lerp(const RectF& other, const double f) const noexcept
	{
		return{ pos.lerp(other.pos, f), size.lerp(other.size, f) };
	}

	inline constexpr Rect Rect::getOverlap(const Rect& other) const noexcept
	{
		const auto ox = std::max(pos.x, other.pos.x);
		const auto oy = std::max(pos.y, other.pos.y);
		const auto ow = (std::min((pos.x + w), (other.pos.x + other.w)) - ox);

		if (0 <= ow)
		{
			const auto oh = (std::min((pos.y + h), (other.pos.y + other.h)) - oy);

			if (0 <= oh)
			{
				return{ ox, oy, ow, oh };
			}
		}

		return Empty();
	}

	inline constexpr RectF Rect::getOverlap(const RectF& other) const noexcept
	{
		return other.getOverlap(*this);
	}

	inline size_t Rect::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	inline constexpr bool Rect::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> Rect::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class Shape2DType>
	inline bool Rect::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}

	inline constexpr Rect Rect::Empty() noexcept
	{
		return{ 0, 0, 0, 0 };
	}

	inline constexpr Rect Rect::FromPoints(const position_type a, const position_type b) noexcept
	{
		const auto [x0, x1] = std::minmax(a.x, b.x);
		const auto [y0, y1] = std::minmax(a.y, b.y);
		return{ x0, y0, (x1 - x0), (y1- y0) };
	}
}
