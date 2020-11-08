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
# include "Common.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 三角形
	struct Triangle
	{
		using position_type	= Vec2;

		using value_type	= position_type::value_type;

		position_type p0;

		position_type p1;

		position_type p2;

		SIV3D_NODISCARD_CXX20
		Triangle() = default;

		explicit constexpr Triangle(value_type sides) noexcept;

		Triangle(value_type sides, value_type angle) noexcept;

		constexpr Triangle(value_type x, value_type y, value_type sides) noexcept;

		constexpr Triangle(const position_type& pos, value_type sides) noexcept;

		Triangle(value_type x, value_type y, value_type sides, value_type angle) noexcept;

		Triangle(const position_type& pos, value_type sides, value_type angle) noexcept;

		constexpr Triangle(value_type x0, value_type y0, value_type x1, value_type y1, value_type x2, value_type y2) noexcept;

		constexpr Triangle(const position_type& _p0, const position_type& _p1, const position_type& _p2) noexcept;
	};
}
