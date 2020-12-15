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
	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const value_type _size) noexcept
		: pos{ 0, 0 }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const value_type _w, const value_type _h) noexcept
		: pos{ 0, 0 }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const size_type _size) noexcept
		: pos{ 0, 0 }
		, size{ _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const value_type _x, const value_type _y, const value_type _size) noexcept
		: pos{ _x, _y }
		, size{ _size, _size } {}

	template <class SizeType>
	template <class Type>
	inline constexpr Rectangle<SizeType>::Rectangle(const Rectangle<Type>& r) noexcept
		: pos{ static_cast<value_type>(r.x), static_cast<value_type>(r.y) }
		, size{ static_cast<value_type>(r.w), static_cast<value_type>(r.h) } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topLeft_<position_type> topLeft, const value_type _size) noexcept
		: pos{ topLeft->x, topLeft->y }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topLeft_<position_type> topLeft, const value_type _w, const value_type _h) noexcept
		: pos{ topLeft->x, topLeft->y }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topLeft_<position_type> topLeft, const size_type _size) noexcept
		: pos{ topLeft->x, topLeft->y }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topCenter_<position_type> topCenter, const value_type _size) noexcept
		: pos{ (topCenter->x - _size / 2), topCenter->y }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topCenter_<position_type> topCenter, const value_type _w, const value_type _h) noexcept
		: pos{ (topCenter->x - _w / 2), topCenter->y }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topCenter_<position_type> topCenter, const size_type _size) noexcept
		: pos{ (topCenter->x - _size.x / 2), topCenter->y }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topRight_<position_type> topRight, const value_type _size) noexcept
		: pos{ (topRight->x - _size), topRight->y }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topRight_<position_type> topRight, const value_type _w, const value_type _h) noexcept
		: pos{ (topRight->x - _w), topRight->y }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::topRight_<position_type> topRight, const size_type _size) noexcept
		: pos{ (topRight->x - _size.x), topRight->y }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::rightCenter_<position_type> rightCenter, const value_type _size) noexcept
		: pos{ (rightCenter->x - _size), (rightCenter->y - _size / 2) }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::rightCenter_<position_type> rightCenter, const value_type _w, const value_type _h) noexcept
		: pos{ (rightCenter->x - _w), (rightCenter->y - _h / 2) }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::rightCenter_<position_type> rightCenter, const size_type _size) noexcept
		: pos{ (rightCenter->x - _size.x), (rightCenter->y - _size.y / 2) }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomRight_<position_type> bottomRight, const value_type _size) noexcept
		: pos{ (bottomRight->x - _size), (bottomRight->y - _size) }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomRight_<position_type> bottomRight, const value_type _w, const value_type _h) noexcept
		: pos{ (bottomRight->x - _w), (bottomRight->y - _h) }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomRight_<position_type> bottomRight, const size_type _size) noexcept
		: pos{ (bottomRight->x - _size.x), (bottomRight->y - _size.y) }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _size) noexcept
		: pos{ (bottomCenter->x - _size / 2), (bottomCenter->y - _size) }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _w, const value_type _h) noexcept
		: pos{ (bottomCenter->x - _w / 2), (bottomCenter->y - _h) }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomCenter_<position_type> bottomCenter, const size_type _size) noexcept
		: pos{ (bottomCenter->x - _size.x / 2), (bottomCenter->y - _size.y) }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _size) noexcept
		: pos{ bottomLeft->x, (bottomLeft->y - _size) }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _w, const value_type _h) noexcept
		: pos{ bottomLeft->x, (bottomLeft->y - _h) }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::bottomLeft_<position_type> bottomLeft, const size_type _size) noexcept
		: pos{ bottomLeft->x, (bottomLeft->y - _size.y) }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::leftCenter_<position_type> leftCenter, const value_type _size) noexcept
		: pos{ leftCenter->x, (leftCenter->y - _size / 2) }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::leftCenter_<position_type> leftCenter, const value_type _w, const value_type _h) noexcept
		: pos{ leftCenter->x, (leftCenter->y - _h / 2) }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::leftCenter_<position_type> leftCenter, const size_type _size) noexcept
		: pos{ leftCenter->x, (leftCenter->y - _size.y / 2) }
		, size{ _size.x, _size.y } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const value_type _x, const value_type _y) noexcept
	{
		pos.set(_x, _y);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const position_type _pos) noexcept
	{
		pos.set(_pos);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::center_<position_type> _center) noexcept
	{
		return setCenter(_center.value());
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::topLeft_<position_type> topLeft) noexcept
	{
		return setPos(topLeft.value());
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::topCenter_<position_type> topCenter) noexcept
	{
		pos.set((topCenter->x - w / 2), topCenter->y);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::topRight_<position_type> topRight) noexcept
	{
		pos.set(topRight->x - w, topRight->y);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::rightCenter_<position_type> rightCenter) noexcept
	{
		pos.set((rightCenter->x - w), (rightCenter->y - h / 2));
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::bottomRight_<position_type> bottomRight) noexcept
	{
		pos.set((bottomRight->x - w), (bottomRight->y - h));
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::bottomCenter_<position_type> bottomCenter) noexcept
	{
		pos.set((bottomCenter->x - w / 2), (bottomCenter->y - h));
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::bottomLeft_<position_type> bottomLeft) noexcept
	{
		pos.set(bottomLeft->x, bottomLeft->y - h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setPos(const Arg::leftCenter_<position_type> leftCenter) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - h / 2));
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setCenter(const value_type _x, const value_type _y) noexcept
	{
		pos.set((_x - w / 2), (_y - h / 2));
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setCenter(const position_type _pos) noexcept
	{
		pos.set((_pos.x - w / 2), (_pos.y - h / 2));
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setSize(const value_type _size) noexcept
	{
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setSize(const value_type _w, const value_type _h) noexcept
	{
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::setSize(const size_type _size) noexcept
	{
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const value_type _x, const value_type _y, const value_type _w, const value_type _h) noexcept
	{
		pos.set(_x, _y);
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const value_type _x, const value_type _y, const value_type _size) noexcept
	{
		pos.set(_x, _y);
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const value_type _x, const value_type _y, const size_type _size) noexcept
	{
		pos.set(_x, _y);
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(position_type _pos, const value_type _size) noexcept
	{
		pos.set(_pos);
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(position_type _pos, const value_type _w, const value_type _h) noexcept
	{
		pos.set(_pos);
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(position_type _pos, const size_type _size) noexcept
	{
		pos.set(_pos);
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	template <class Type>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Rectangle<Type>& r) noexcept
	{
		pos.set(static_cast<value_type>(r.x), static_cast<value_type>(r.y));
		size.set(static_cast<value_type>(r.w), static_cast<value_type>(r.h));
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::center_<position_type> _center, const value_type _size) noexcept
	{
		pos.set((_center->x - _size / 2), (_center->y - _size / 2));
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::center_<position_type> _center, const value_type _w, const value_type _h) noexcept
	{
		pos.set((_center->x - _w / 2), (_center->y - _h / 2));
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::center_<position_type> _center, const size_type _size) noexcept
	{
		pos.set((_center->x - _size.x / 2), (_center->y - _size.y / 2));
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topLeft_<position_type> topLeft, const value_type _size) noexcept
	{
		pos.set(topLeft.value());
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topLeft_<position_type> topLeft, const value_type _w, const value_type _h) noexcept
	{
		pos.set(topLeft.value());
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topLeft_<position_type> topLeft, const size_type _size) noexcept
	{
		pos.set(topLeft.value());
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topCenter_<position_type> topCenter, const value_type _size) noexcept
	{
		pos.set((topCenter->x - _size / 2), topCenter->y);
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topCenter_<position_type> topCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set((topCenter->x - _w / 2), topCenter->y);
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topCenter_<position_type> topCenter, const size_type _size) noexcept
	{
		pos.set((topCenter->x - _size.x / 2), topCenter->y);
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topRight_<position_type> topRight, const value_type _size) noexcept
	{
		pos.set((topRight->x - _size), topRight->y);
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topRight_<position_type> topRight, const value_type _w, const value_type _h) noexcept
	{
		pos.set((topRight->x - _w), topRight->y);
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::topRight_<position_type> topRight, const size_type _size) noexcept
	{
		pos.set((topRight->x - _size.x), topRight->y);
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::rightCenter_<position_type> rightCenter, const value_type _size) noexcept
	{
		pos.set((rightCenter->x - _size), (rightCenter->y - _size / 2));
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::rightCenter_<position_type> rightCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set((rightCenter->x - _w), (rightCenter->y - _h / 2));
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::rightCenter_<position_type> rightCenter, const size_type _size) noexcept
	{
		pos.set(rightCenter->x - _size.x, rightCenter->y - _size.y / 2);
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomRight_<position_type> bottomRight, const value_type _size) noexcept
	{
		pos.set((bottomRight->x - _size), (bottomRight->y - _size));
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomRight_<position_type> bottomRight, const value_type _w, const value_type _h) noexcept
	{
		pos.set((bottomRight->x - _w), (bottomRight->y - _h));
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomRight_<position_type> bottomRight, const size_type _size) noexcept
	{
		pos.set((bottomRight->x - _size.x), (bottomRight->y - _size.y));
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _size) noexcept
	{
		pos.set((bottomCenter->x - _size / 2), (bottomCenter->y - _size));
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomCenter_<position_type> bottomCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set((bottomCenter->x - _w / 2), (bottomCenter->y - _h));
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomCenter_<position_type> bottomCenter, const size_type _size) noexcept
	{
		pos.set((bottomCenter->x - _size.x / 2), (bottomCenter->y - _size.y));
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _size) noexcept
	{
		pos.set(bottomLeft->x, (bottomLeft->y - _size));
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomLeft_<position_type> bottomLeft, const value_type _w, const value_type _h) noexcept
	{
		pos.set(bottomLeft->x, (bottomLeft->y - _h));
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::bottomLeft_<position_type> bottomLeft, const size_type _size) noexcept
	{
		pos.set(bottomLeft->x, (bottomLeft->y - _size.y));
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::leftCenter_<position_type> leftCenter, const value_type _size) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - _size / 2));
		size.set(_size, _size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::leftCenter_<position_type> leftCenter, const value_type _w, const value_type _h) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - _h / 2));
		size.set(_w, _h);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::set(const Arg::leftCenter_<position_type> leftCenter, const size_type _size) noexcept
	{
		pos.set(leftCenter->x, (leftCenter->y - _size.y / 2));
		size.set(_size);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType> Rectangle<SizeType>::movedBy(const value_type _x, const value_type _y) const noexcept
	{
		return{ pos.movedBy(_x, _y), size };
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType> Rectangle<SizeType>::movedBy(const size_type v) const noexcept
	{
		return{ pos.movedBy(v), size };
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::moveBy(const value_type _x, const value_type _y) noexcept
	{
		pos.moveBy(_x, _y);
		return *this;
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>& Rectangle<SizeType>::moveBy(const size_type v) noexcept
	{
		pos.moveBy(v);
		return *this;
	}

	template <class SizeType>
	constexpr Rectangle<SizeType> Rectangle<SizeType>::stretched(const value_type xy) const noexcept
	{
		return stretched({ xy, xy });
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType> Rectangle<SizeType>::stretched(const value_type _x, const value_type _y) const noexcept
	{
		return stretched({ _x, _y });
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType> Rectangle<SizeType>::stretched(const size_type xy) const noexcept
	{
		return{ (pos - xy), (size + xy * 2) };
	}

	template <class SizeType>
	inline constexpr Rectangle<SizeType> Rectangle<SizeType>::stretched(const value_type top, const value_type right, const value_type bottom, const value_type left) const noexcept
	{
		return{ (pos.x - left), (pos.y - top), (size.x + left + right), (size.y + top + bottom) };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaled(const double s) const noexcept
	{
		return{ Arg::center((x + w * 0.5), (y + h * 0.5)), (w * s), (h * s) };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaled(const double sx, const double sy) const noexcept
	{
		return{ Arg::center((x + w * 0.5), (y + h * 0.5)), (w * sx), (h * sy) };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaled(const Vec2 s) const noexcept
	{
		return{ Arg::center((x + w * 0.5), (y + h * 0.5)), (w * s.x), (h * s.y) };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaledAt(const double _x, const double _y, const double s) const noexcept
	{
		return{ (_x + (x - _x) * s), (_y + (y - _y) * s), (w * s), (h * s) };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaledAt(const double _x, const double _y, const double sx, const double sy) const noexcept
	{
		return{ (_x + (x - _x) * sx), (_y + (y - _y) * sy), (w * sx), (h * sy) };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaledAt(const double _x, const double _y, const Vec2 s) const noexcept
	{
		return{ (_x + (x - _x) * s.x), (_y + (y - _y) * s.y), (w * s.x), (h * s.y) };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaledAt(const Vec2 _pos, const double s) const noexcept
	{
		return scaledAt(_pos.x, _pos.y, s);
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaledAt(const Vec2 _pos, const double sx, const double sy) const noexcept
	{
		return scaledAt(_pos.x, _pos.y, sx, sy);
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::scaledAt(const Vec2 _pos, const Vec2 s) const noexcept
	{
		return scaledAt(_pos.x, _pos.y, s);
	}

	template <class SizeType>
	inline constexpr typename Rectangle<SizeType>::size_type Rectangle<SizeType>::tl() const noexcept
	{
		return pos;
	}

	template <class SizeType>
	inline constexpr typename Rectangle<SizeType>::size_type Rectangle<SizeType>::tr() const noexcept
	{
		return{ (x + w), y };
	}

	template <class SizeType>
	inline constexpr typename Rectangle<SizeType>::size_type Rectangle<SizeType>::bl() const noexcept
	{
		return{ x, (y + h) };
	}

	template <class SizeType>
	inline constexpr typename Rectangle<SizeType>::size_type Rectangle<SizeType>::br() const noexcept
	{
		return{ (x + w), (y + h) };
	}

	template <class SizeType>
	inline constexpr Vec2 Rectangle<SizeType>::topCenter() const noexcept
	{
		return{ (x + w * 0.5), y };
	}

	template <class SizeType>
	inline constexpr Vec2 Rectangle<SizeType>::bottomCenter() const noexcept
	{
		return{ (x + w), (y + h) };
	}

	template <class SizeType>
	inline constexpr Vec2 Rectangle<SizeType>::leftCenter() const noexcept
	{
		return{ x, (y + h * 0.5) };
	}

	template <class SizeType>
	inline constexpr Vec2 Rectangle<SizeType>::rightCenter() const noexcept
	{
		return{ (x + w), (y + h * 0.5) };
	}

	template <class SizeType>
	inline constexpr Vec2 Rectangle<SizeType>::center() const noexcept
	{
		return{ (x + w * 0.5), (y + h * 0.5) };
	}

	template <class SizeType>
	inline constexpr Line Rectangle<SizeType>::top() const noexcept
	{
		return{ tl(), tr() };
	}

	template <class SizeType>
	inline constexpr Line Rectangle<SizeType>::right() const noexcept
	{
		return{ tr(), br() };
	}

	template <class SizeType>
	inline constexpr Line Rectangle<SizeType>::bottom() const noexcept
	{
		return{ br(), bl() };
	}

	template <class SizeType>
	inline constexpr Line Rectangle<SizeType>::left() const noexcept
	{
		return{ bl(), tl() };
	}

	template <class SizeType>
	inline constexpr typename Rectangle<SizeType>::position_type Rectangle<SizeType>::point(const size_t index)
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
			throw std::out_of_range("Rectangle::point() index out of range");
		}
	}

	template <class SizeType>
	inline constexpr Line Rectangle<SizeType>::side(const size_t index)
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
			throw std::out_of_range("Rectangle::side() index out of range");
		}
	}

	template <class SizeType>
	inline constexpr typename Rectangle<SizeType>::value_type Rectangle<SizeType>::area() const noexcept
	{
		return (w * h);
	}

	template <class SizeType>
	inline constexpr typename Rectangle<SizeType>::value_type Rectangle<SizeType>::perimeter() const noexcept
	{
		return ((w + h) * 2);
	}

	template <class SizeType>
	inline constexpr Quad Rectangle<SizeType>::shearedX(const double vx) const noexcept
	{
		return{ {(x + vx), y}, {(x + w + vx), y}, {(x + w - vx), (y + h)}, {(x - vx), (y + h)} };
	}

	template <class SizeType>
	inline constexpr Quad Rectangle<SizeType>::shearedY(const double vy) const noexcept
	{
		return{ {x, (y - vy)}, {(x + w), (y + vy)}, {(x + w), (y + h + vy)}, {x, (y + h - vy)} };
	}

	template <class SizeType>
	inline constexpr RoundRect Rectangle<SizeType>::rounded(const double r) const noexcept
	{
		return{ *this, r };
	}

	template <class SizeType>
	inline constexpr Quad Rectangle<SizeType>::asQuad() const noexcept
	{
		return{ tl(), tr(), br(), bl() };
	}

	template <class SizeType>
	inline constexpr Rectangle<Vec2> Rectangle<SizeType>::lerp(const Rectangle& other, const double f) const noexcept
	{
		return{ pos.lerp(other.pos, f), size.lerp(other.size, f) };
	}

	template <class SizeType>
	inline size_t Rectangle<SizeType>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class SizeType>
	template <class Shape2DType>
	inline bool Rectangle<SizeType>::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class SizeType>
	template <class Shape2DType>
	inline Optional<Array<Vec2>> Rectangle<SizeType>::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class SizeType>
	template <class Shape2DType>
	inline bool Rectangle<SizeType>::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}
}
