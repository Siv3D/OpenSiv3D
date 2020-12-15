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
# include "Array.hpp"
# include "Optional.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	namespace Geometry2D
	{
		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const RectF& b) noexcept;


		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const Vec2& b) noexcept;


		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const Vec2& b) noexcept;




		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b);



		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b);

		[[nodiscard]] bool Contains(const Rect& a, const Point& b) noexcept;
		[[nodiscard]] bool Contains(const Rect& a, const Vec2& b) noexcept;

		[[nodiscard]] bool Contains(const RectF& a, const Point& b) noexcept;
		[[nodiscard]] bool Contains(const RectF& a, const Vec2& b) noexcept;
	}
}

# include "detail/Geometry2D.ipp"
