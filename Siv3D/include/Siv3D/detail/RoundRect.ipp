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
	inline constexpr RoundRect::RoundRect(const value_type _x, const value_type _y, const value_type _w, const value_type _h, const value_type _r) noexcept
		: rect{ _x, _y, _w, _h }
		, r{ _r } {}

	inline constexpr RoundRect::RoundRect(const position_type pos, const value_type _w, const value_type _h, const value_type _r) noexcept
		: rect{ pos, _w, _h }
		, r{ _r } {}

	inline constexpr RoundRect::RoundRect(const value_type _x, const value_type _y, const size_type size, const value_type _r) noexcept
		: rect{ _x, _y, size }
		, r{ _r } {}

	inline constexpr RoundRect::RoundRect(const position_type pos, const value_type size, const value_type _r) noexcept
		: rect{ pos, size }
		, r{ _r } {}

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
}
