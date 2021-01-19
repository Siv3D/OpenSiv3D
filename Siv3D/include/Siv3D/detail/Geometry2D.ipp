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
		//
		//	http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
		//
		inline constexpr double DistanceSq(const Vec2& begin, const Vec2& end, const Vec2& p) noexcept
		{
			const double l2 = begin.distanceFromSq(end);

			if (l2 == 0.0)
			{
				return begin.distanceFromSq(p);
			}

			const double t = Max(0.0, Min(1.0, (p - begin).dot(end - begin) / l2));

			const Vec2 projection = begin + t * (end - begin);

			return p.distanceFromSq(projection);
		}

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

		inline constexpr double Sign(const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
		{
			return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
		}
	}

	namespace Geometry2D
	{
		inline constexpr bool Intersect(const Point& a, const Point& b) noexcept
		{
			return (a == b);
		}

		inline constexpr bool Intersect(const Point& a, const Vec2& b) noexcept
		{
			return (b.distanceFromSq(a) < 1.0);
		}

		inline constexpr bool Intersect(const Point& a, const Line& b) noexcept
		{
			return (detail::DistanceSq(b.begin, b.end, a) < 1.0);
		}

		inline constexpr bool Intersect(const Point& a, const Rect& b) noexcept
		{
			return (b.x <= a.x)
				&& (a.x < (b.x + b.w))
				&& (b.y <= a.y)
				&& (a.y < (b.y + b.h));
		}

		inline constexpr bool Intersect(const Point& a, const RectF& b) noexcept
		{
			return (b.x <= a.x)
				&& (a.x < (b.x + b.w))
				&& (b.y <= a.y)
				&& (a.y < (b.y + b.h));
		}

		inline constexpr bool Intersect(const Point& a, const Circle& b) noexcept
		{
			return (a.distanceFromSq(b.center) <= (b.r * b.r));
		}

		inline constexpr bool Intersect(const Point& a, const Ellipse& b) noexcept
		{
			if ((b.a == 0.0)
				|| (b.b == 0.0))
			{
				return false;
			}

			const double xh = (b.x - a.x);
			const double yk = (b.y - a.y);

			return (((xh * xh) / (b.a * b.a) + (yk * yk) / (b.b * b.b)) <= 1.0);
		}

		inline constexpr bool Intersect(const Point& a, const Triangle& b) noexcept
		{
			const bool b1 = (detail::Sign(a, b.p0, b.p1) < 0.0);
			const bool b2 = (detail::Sign(a, b.p1, b.p2) < 0.0);
			const bool b3 = (detail::Sign(a, b.p2, b.p0) < 0.0);

			return ((b1 == b2) && (b2 == b3));
		}

		inline constexpr bool Intersect(const Point& a, const Quad& b) noexcept
		{
			return Intersect(a, b.triangle(0))
				|| Intersect(a, b.triangle(1));
		}

		inline bool Intersect(const Point& a, const RoundRect& b) noexcept
		{
			return Intersect(Vec2{ a }, b);
		}

		inline bool Intersect(const Point& a, const Polygon& b) noexcept
		{
			return Intersect(Vec2{ a }, b);
		}

		inline bool Intersect(const Point& a, const MultiPolygon& b) noexcept
		{
			return Intersect(Vec2{ a }, b);
		}

		inline bool Intersect(const Point& a, const LineString& b) noexcept
		{
			return Intersect(Vec2{ a }, b);
		}

		inline constexpr bool Intersect(const Vec2& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Vec2& a, const Vec2& b) noexcept
		{
			return (a.distanceFromSq(b) < 1.0);
		}

		inline constexpr bool Intersect(const Vec2& a, const Line& b) noexcept
		{
			return (detail::DistanceSq(b.begin, b.end, a) < 1.0);
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

		inline constexpr bool Intersect(const Vec2& a, const Triangle& b) noexcept
		{
			const bool b1 = (detail::Sign(a, b.p0, b.p1) < 0.0);
			const bool b2 = (detail::Sign(a, b.p1, b.p2) < 0.0);
			const bool b3 = (detail::Sign(a, b.p2, b.p0) < 0.0);
			return ((b1 == b2) && (b2 == b3));
		}

		inline constexpr bool Intersect(const Vec2& a, const Quad& b) noexcept
		{
			return (Intersect(a, b.triangle(0))
				|| Intersect(a, b.triangle(1)));
		}

		inline constexpr bool Intersect(const Line& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Line& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Rect& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Rect& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Rect& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Rect& a, const Rect& b) noexcept
		{
			return (a.x < (b.x + b.w))
				&& (b.x < (a.x + a.w))
				&& (a.y < (b.y + b.h))
				&& (b.y < (a.y + a.h));
		}

		inline constexpr bool Intersect(const Rect& a, const RectF& b) noexcept
		{
			return (a.x < (b.x + b.w))
				&& (b.x < (a.x + a.w))
				&& (a.y < (b.y + b.h))
				&& (b.y < (a.y + a.h));
		}

		inline constexpr bool Intersect(const RectF& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const RectF& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RectF& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const RectF& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const RectF& a, const RectF& b) noexcept
		{
			return (a.x < (b.x + b.w))
				&& (b.x < (a.x + a.w))
				&& (a.y < (b.y + b.h))
				&& (b.y < (a.y + a.h));
		}


		inline constexpr bool Intersect(const Circle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Circle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Circle& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Triangle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Quad& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}




		inline constexpr bool Contains(const Rect& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Rect& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}



		inline constexpr bool Contains(const RectF& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const RectF& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		//////////////////////////////////////////////////
		//
		//	IsClockwise
		//
		//////////////////////////////////////////////////

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
