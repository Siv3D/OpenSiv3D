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
	inline constexpr Rectangle<SizeType>::Rectangle(const value_type _x, const value_type _y, const value_type _w, const value_type _h) noexcept
		: pos{ _x, _y }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const value_type _x, const value_type _y, const size_type _size) noexcept
		: pos{ _x, _y }
		, size{ _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const position_type _pos, const value_type _size) noexcept
		: pos{ _pos }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const position_type _pos, const value_type _w, const value_type _h) noexcept
		: pos{ _pos }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const position_type _pos, const size_type _size) noexcept
		: pos{ _pos }
		, size{ _size } {}

	template <class SizeType>
	template <class Type>
	inline constexpr Rectangle<SizeType>::Rectangle(const Rectangle<Type>& r) noexcept
		: pos{ static_cast<value_type>(r.x), static_cast<value_type>(r.y) }
		, size{ static_cast<value_type>(r.w), static_cast<value_type>(r.h) } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::center_<position_type> _center, const value_type _size) noexcept
		: pos{ (_center->x - _size / 2), (_center->y - _size / 2) }
		, size{ _size, _size } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::center_<position_type> _center, const value_type _w, const value_type _h) noexcept
		: pos{ (_center->x - _w / 2), (_center->y - _h / 2) }
		, size{ _w, _h } {}

	template <class SizeType>
	inline constexpr Rectangle<SizeType>::Rectangle(const Arg::center_<position_type> _center, const size_type _size) noexcept
		: pos{ (_center->x - _size.x / 2), (_center->y - _size.y / 2) }
		, size{ _size.x, _size.y } {}

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
	inline size_t Rectangle<SizeType>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
