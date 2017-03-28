//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr double Sqrt3 = 1.73205080756887729353; // std::sqrt(3.0)
	}

	struct Triangle
	{
		using position_type = Vec2;

		using value_type = position_type::value_type;

		Vec2 p0, p1, p2;

		Triangle() = default;

		explicit Triangle(double sides) noexcept
			: p0(0.0, -1.0 / detail::Sqrt3 * sides)
			, p1(sides * 0.5, sides / (2.0 * detail::Sqrt3))
			, p2(-p1.x, p1.y) {}

		Triangle(double sides, double angle) noexcept;

		Triangle(double x, double y, double sides) noexcept;

		Triangle(const Vec2& pos, double sides) noexcept
			: Triangle(pos.x, pos.y, sides) {}

		Triangle(double x, double y, double sides, double angle) noexcept;
			
		Triangle(const Vec2& pos, double sides, double angle) noexcept
			: Triangle(pos.x, pos.y, sides, angle) {}

		constexpr Triangle(double x0, double y0, double x1, double y1, double x2, double y2) noexcept
			: p0(x0, y0)
			, p1(x1, y1)
			, p2(x2, y2) {}

		constexpr Triangle(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		constexpr Triangle& set(double x0, double y0, double x1, double y1, double x2, double y2) noexcept
		{
			p0.set(x0, y0);
			p1.set(x1, y1);
			p2.set(x2, y2);
			return *this;
		}

		constexpr Triangle& set(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2) noexcept
		{
			p0.set(_p0);
			p1.set(_p1);
			p2.set(_p2);
			return *this;
		}

		constexpr Triangle& set(const Triangle& triangle) noexcept
		{
			return *this = triangle;
		}
	};
}
