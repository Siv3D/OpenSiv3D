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
	inline constexpr Ellipse::Ellipse(const double _r) noexcept
		: center(0, 0)
		, a(_r)
		, b(_r) {}

	inline constexpr Ellipse::Ellipse(const double _a, const double _b) noexcept
		: center(0, 0)
		, a(_a)
		, b(_b) {}

	inline constexpr Ellipse::Ellipse(const double _x, const double _y, const double _r) noexcept
		: center(_x, _y)
		, a(_r)
		, b(_r) {}

	inline constexpr Ellipse::Ellipse(const double _x, const double _y, const double _a, const double _b) noexcept
		: center(_x, _y)
		, a(_a)
		, b(_b) {}

	inline constexpr Ellipse::Ellipse(const Vec2 _center) noexcept
		: center(_center)
		, a(0)
		, b(0) {}

	inline constexpr Ellipse::Ellipse(const Vec2& _center, const double _r) noexcept
		: center(_center)
		, a(_r)
		, b(_r) {}

	inline constexpr Ellipse::Ellipse(const Vec2& _center, const double _a, const double _b) noexcept
		: center(_center)
		, a(_a)
		, b(_b) {}

	inline constexpr Ellipse::Ellipse(const double _x, const double _y, const Vec2& _axis) noexcept
		: center(_x, _y)
		, a(_axis.x)
		, b(_axis.y) {}

	inline constexpr Ellipse::Ellipse(const Vec2& _center, const Vec2& _axis) noexcept
		: center(_center)
		, a(_axis.x)
		, b(_axis.y) {}

	inline constexpr Ellipse::Ellipse(const Circle& circle) noexcept
		: center(circle.center)
		, a(circle.r)
		, b(circle.r) {}

	inline constexpr Ellipse::Ellipse(const RectF& rect) noexcept
		: center(rect.center())
		, a(rect.w * 0.5)
		, b(rect.h * 0.5) {}




	inline size_t Ellipse::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}
}
