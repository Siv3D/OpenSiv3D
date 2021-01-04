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
	namespace detail
	{
		template <class PointType>
		[[nodiscard]]
		bool IsClockwise(const PointType* points, const size_t size)
		{
			// 頂点数が 2 以下の場合は判定できないため false を返す
			if (size <= 2)
			{
				return false;
			}

			const auto* const pSrcBegin = points;
			const auto* const pSrcEnd = points + size;
			double sum = 0.0;

			// 最初の頂点 -> ... -> 最後の頂点
			for (const auto* pSrc = pSrcBegin; pSrc != (pSrcEnd - 1); ++pSrc)
			{
				const auto* p0 = pSrc;
				const auto* p1 = (pSrc + 1);
				sum += (p1->x - p0->x) * (p1->y + p0->y);
			}

			// 最後の頂点 -> 最初の頂点
			{
				const auto* p0 = (pSrcEnd - 1);
				const auto* p1 = pSrcBegin;
				sum += (p1->x - p0->x) * (p1->y + p0->y);
			}

			return (sum < 0.0);
		}
	}

	namespace Geometry2D
	{
		inline constexpr bool Intersect(const Point& a, const Circle& b) noexcept
		{
			return (a.distanceFromSq(b.center) <= (b.r * b.r));
		}

		inline constexpr bool Intersect(const Vec2& a, const Rect& b) noexcept
		{
			return (b.x <= a.x) && (a.x < (b.x + b.w))
				&& (b.y <= a.y) && (a.y < (b.y + b.h));
		}

		inline constexpr bool Intersect(const Vec2& a, const RectF& b) noexcept
		{
			return (b.x <= a.x) && (a.x < (b.x + b.w))
				&& (b.y <= a.y) && (a.y < (b.y + b.h));
		}

		inline constexpr bool Intersect(const Vec2& a, const Circle& b) noexcept
		{
			return (a.distanceFromSq(b.center) <= (b.r * b.r));
		}

		inline constexpr bool Intersect(const Vec2& a, const Ellipse& b) noexcept
		{
			if ((b.a == 0.0) || (b.b == 0.0))
			{
				return false;
			}

			const double xh = (b.x - a.x);
			const double yk = (b.y - a.y);
			return (((xh * xh) / (b.a * b.a) + (yk * yk) / (b.b * b.b)) <= 1.0);
		}


		inline constexpr bool Intersect(const Rect& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Rect& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}


		inline constexpr bool Intersect(const RectF& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const RectF& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Circle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Circle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}


		inline bool IsClockwise(const Array<Point>& points) noexcept
		{
			return detail::IsClockwise(points.data(), points.size());
		}

		inline bool IsClockwise(const Point* points, const size_t size) noexcept
		{
			return detail::IsClockwise(points, size);
		}

		inline bool IsClockwise(const Array<Float2>& points) noexcept
		{
			return detail::IsClockwise(points.data(), points.size());
		}

		inline bool IsClockwise(const Float2* points, const size_t size) noexcept
		{
			return detail::IsClockwise(points, size);
		}

		inline bool IsClockwise(const Array<Vec2>& points) noexcept
		{
			return detail::IsClockwise(points.data(), points.size());
		}

		inline bool IsClockwise(const Vec2* points, const size_t size) noexcept
		{
			return detail::IsClockwise(points, size);
		}
	}
}
