﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
//	Authors (OpenSiv3D challenge participants)
//	- Ebishu
//	- fal_rnd
//	- きつねび
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr std::tuple<double, double, double, double> GetLRTB(const Rect& rect) noexcept
		{
			return{ rect.pos.x, (rect.pos.x + rect.size.x), rect.pos.y, (rect.pos.y + rect.size.y) };
		}

		[[nodiscard]]
		inline constexpr std::tuple<double, double, double, double> GetLRTB(const RectF& rect) noexcept
		{
			return{ rect.pos.x, (rect.pos.x + rect.size.x), rect.pos.y, (rect.pos.y + rect.size.y) };
		}

		[[nodiscard]]
		inline constexpr bool Contains(const Vec2& point, const double left, const double right, const double top, const double bottom) noexcept
		{
			return (left <= point.x)
				&& (point.x < right)
				&& (top <= point.y)
				&& (point.y < bottom);
		}

		/// @brief 点 p が円 c に含まれているかを判定します。
		/// @param c 円
		/// @param p 点
		/// @param tolerance 許容誤差（相対誤差または絶対誤差のいずれかが許容誤差以下であれば許容）
		/// @return 点 p が円 c に含まれている場合 true, それ以外の場合は false
		[[nodiscard]]
		inline bool Contains(const Circle& c, const Vec2& p, const double tolerance = 1e-8)
		{
			const double dSquared = (c.center - p).lengthSq();
			const double rSquared = (c.r * c.r);
			const double err = Max(0.0, (dSquared - rSquared));

			if (rSquared == 0)
			{
				return (err <= tolerance);
			}
			
			return (((err / rSquared) <= tolerance) || (err <= tolerance));
		}

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
			const auto* const pSrcEnd = (points + size);
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

		[[nodiscard]]
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
			return (b.pos.x <= a.x)
				&& (a.x < (b.pos.x + b.size.x))
				&& (b.pos.y <= a.y)
				&& (a.y < (b.pos.y + b.size.y));
		}

		inline constexpr bool Intersect(const Point& a, const RectF& b) noexcept
		{
			return (b.pos.x <= a.x)
				&& (a.x < (b.pos.x + b.size.x))
				&& (b.pos.y <= a.y)
				&& (a.y < (b.pos.y + b.size.y));
		}

		inline constexpr bool Intersect(const Point& a, const Circle& b) noexcept
		{
			return (a.distanceFromSq(b.center) <= (b.r * b.r));
		}

		inline constexpr bool Intersect(const Point& a, const Ellipse& b) noexcept
		{
			if ((b.axes.x == 0.0)
				|| (b.axes.y == 0.0))
			{
				return false;
			}

			const double xh = (b.center.x - a.x);
			const double yk = (b.center.y - a.y);

			return (((xh * xh) / (b.axes.x * b.axes.x) + (yk * yk) / (b.axes.y * b.axes.y)) <= 1.0);
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
			return (b.pos.x <= a.x) && (a.x < (b.pos.x + b.size.x))
				&& (b.pos.y <= a.y) && (a.y < (b.pos.y + b.size.y));
		}

		inline constexpr bool Intersect(const Vec2& a, const RectF& b) noexcept
		{
			return (b.pos.x <= a.x) && (a.x < (b.pos.x + b.size.x))
				&& (b.pos.y <= a.y) && (a.y < (b.pos.y + b.size.y));
		}

		inline constexpr bool Intersect(const Vec2& a, const Circle& b) noexcept
		{
			return (a.distanceFromSq(b.center) <= (b.r * b.r));
		}

		inline constexpr bool Intersect(const Vec2& a, const Ellipse& b) noexcept
		{
			if ((b.axes.x == 0.0) || (b.axes.y == 0.0))
			{
				return false;
			}

			const double xh = (b.center.x - a.x);
			const double yk = (b.center.y - a.y);
			return (((xh * xh) / (b.axes.x * b.axes.x) + (yk * yk) / (b.axes.y * b.axes.y)) <= 1.0);
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

		inline bool Intersect(const Bezier2& a, const Point& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Bezier2& a, const Vec2& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Bezier2& a, const Line& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Bezier3& a, const Line& b) noexcept
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

		inline bool Intersect(const Rect& a, const Bezier2& b)
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Rect& a, const Rect& b) noexcept
		{
			return (a.pos.x < (b.pos.x + b.size.x))
				&& (b.pos.x < (a.pos.x + a.size.x))
				&& (a.pos.y < (b.pos.y + b.size.y))
				&& (b.pos.y < (a.pos.y + a.size.y));
		}

		inline constexpr bool Intersect(const Rect& a, const RectF& b) noexcept
		{
			return (a.pos.x < (b.pos.x + b.size.x))
				&& (b.pos.x < (a.pos.x + a.size.x))
				&& (a.pos.y < (b.pos.y + b.size.y))
				&& (b.pos.y < (a.pos.y + a.size.y));
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

		inline bool Intersect(const RectF& a, const Bezier2& b)
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const RectF& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const RectF& a, const RectF& b) noexcept
		{
			return (a.pos.x < (b.pos.x + b.size.x))
				&& (b.pos.x < (a.pos.x + a.size.x))
				&& (a.pos.y < (b.pos.y + b.size.y))
				&& (b.pos.y < (a.pos.y + a.size.y));
		}

		inline constexpr bool Intersect(const Rect& a, const Circle& b) noexcept
		{
			return Intersect(RectF{ a }, b);
		}

		inline bool Intersect(const Rect& a, const LineString& b) noexcept
		{
			return Intersect(RectF{ a }, b);
		}

		inline constexpr bool Intersect(const RectF& a, const Circle& b) noexcept
		{
			const double aw = (a.size.x * 0.5);
			const double ah = (a.size.y * 0.5);
			const double cX = Abs(b.center.x - a.pos.x - aw);
			const double cY = Abs(b.center.y - a.pos.y - ah);

			if ((cX > (aw + b.r))
				|| (cY > (ah + b.r)))
			{
				return false;
			}

			if ((cX <= aw)
				|| (cY <= ah))
			{
				return true;
			}

			return ((cX - aw) * (cX - aw) + (cY - ah) * (cY - ah) <= (b.r * b.r));
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

		inline bool Intersect(const Circle& a, const Bezier2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Circle& a, const Bezier3& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Circle& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Circle& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Circle& a, const Circle& b) noexcept
		{
			return (((a.center.x - b.center.x) * (a.center.x - b.center.x) + (a.center.y - b.center.y) * (a.center.y - b.center.y)) <= ((a.r + b.r) * (a.r + b.r)));
		}

		inline constexpr bool Intersect(const Ellipse& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Ellipse& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Ellipse& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Ellipse& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Ellipse& a, const Circle& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Ellipse& a, const Bezier2& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Ellipse& a, const Bezier3& b)
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Triangle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Triangle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Triangle& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Triangle& a, const Bezier2& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Triangle& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Triangle& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Triangle& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Triangle& a, const Ellipse& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Quad& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Intersect(const Quad& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Quad& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Quad& a, const Bezier2& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Quad& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Quad& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Quad& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Quad& a, const Ellipse& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Quad& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Quad& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const RoundRect& a, const Ellipse& b)
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Ellipse& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const Quad& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const Polygon& a, const RoundRect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Ellipse& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Quad& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const RoundRect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const MultiPolygon& a, const Polygon& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Ellipse& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Quad& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const RoundRect& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const Polygon& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Intersect(const LineString& a, const MultiPolygon& b) noexcept
		{
			return Intersect(b, a);
		}

		//////////////////////////////////////////////////
		//
		//	IntersectAt
		//
		//////////////////////////////////////////////////

		inline Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Rect& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Rect& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Rect& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b)
		{
			return IntersectAt(RectF{ a }, b);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RectF& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RectF& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RectF& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b)
		{
			return IntersectAt(a, RectF{ b });
		}

		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Circle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Circle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Ellipse& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const Circle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const Ellipse& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Quad& a, const Triangle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Circle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Ellipse& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Triangle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Quad& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Circle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Ellipse& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Triangle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Quad& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Circle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Ellipse& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Triangle& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Quad& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const RoundRect& b)
		{
			return IntersectAt(b, a);
		}

		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Polygon& b)
		{
			return IntersectAt(b, a);
		}

		//////////////////////////////////////////////////
		//
		//	Contains
		//
		//////////////////////////////////////////////////

		inline constexpr bool Contains(const Rect& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Rect& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Rect& a, const Line& b) noexcept
		{
			return Contains(a, b.begin)
				&& Contains(a, b.end);
		}

		inline constexpr bool Contains(const Rect& a, const Rect& b) noexcept
		{
			return (a.pos.x <= b.pos.x)
				&& (a.pos.y <= b.pos.y)
				&& ((b.pos.x + b.size.x) <= (a.pos.x + a.size.x))
				&& ((b.pos.y + b.size.y) <= (a.pos.y + a.size.y));
		}

		inline constexpr bool Contains(const Rect& a, const RectF& b) noexcept
		{
			return (a.pos.x <= b.pos.x)
				&& (a.pos.y <= b.pos.y)
				&& ((b.pos.x + b.size.x) <= (a.pos.x + a.size.x))
				&& ((b.pos.y + b.size.y) <= (a.pos.y + a.size.y));
		}

		inline constexpr bool Contains(const Rect& a, const Circle& b) noexcept
		{
			return Intersect(b.center, RectF{ a }.stretched(-b.r));
		}

		inline constexpr bool Contains(const Rect& a, const Ellipse& b) noexcept
		{
			return Contains(a, b.boundingRect());
		}

		inline constexpr bool Contains(const Rect& a, const Triangle& b) noexcept
		{
			const auto [left, right, top, bottom] = detail::GetLRTB(a);
			return detail::Contains(b.p0, left, right, top, bottom)
				&& detail::Contains(b.p1, left, right, top, bottom)
				&& detail::Contains(b.p2, left, right, top, bottom);
		}

		inline constexpr bool Contains(const Rect& a, const Quad& b) noexcept
		{
			const auto [left, right, top, bottom] = detail::GetLRTB(a);
			return detail::Contains(b.p0, left, right, top, bottom)
				&& detail::Contains(b.p1, left, right, top, bottom)
				&& detail::Contains(b.p2, left, right, top, bottom)
				&& detail::Contains(b.p3, left, right, top, bottom);
		}

		inline constexpr bool Contains(const Rect& a, const RoundRect& b) noexcept
		{
			return Contains(a, b.rect);
		}

		inline constexpr bool Contains(const RectF& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const RectF& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const RectF& a, const Line& b) noexcept
		{
			return Contains(a, b.begin)
				&& Contains(a, b.end);
		}

		inline constexpr bool Contains(const RectF& a, const Rect& b) noexcept
		{
			return (a.pos.x <= b.pos.x)
				&& (a.pos.y <= b.pos.y)
				&& ((b.pos.x + b.size.x) <= (a.pos.x + a.size.x))
				&& ((b.pos.y + b.size.y) <= (a.pos.y + a.size.y));
		}

		inline constexpr bool Contains(const RectF& a, const RectF& b) noexcept
		{
			return (a.pos.x <= b.pos.x)
				&& (a.pos.y <= b.pos.y)
				&& ((b.pos.x + b.size.x) <= (a.pos.x + a.size.x))
				&& ((b.pos.y + b.size.y) <= (a.pos.y + a.size.y));
		}

		inline constexpr bool Contains(const RectF& a, const Circle& b) noexcept
		{
			return Intersect(b.center, a.stretched(-b.r));
		}

		inline constexpr bool Contains(const RectF& a, const Ellipse& b) noexcept
		{
			return Contains(a, b.boundingRect());
		}

		inline constexpr bool Contains(const RectF& a, const Triangle& b) noexcept
		{
			const auto [left, right, top, bottom] = detail::GetLRTB(a);
			return detail::Contains(b.p0, left, right, top, bottom)
				&& detail::Contains(b.p1, left, right, top, bottom)
				&& detail::Contains(b.p2, left, right, top, bottom);
		}

		inline constexpr bool Contains(const RectF& a, const Quad& b) noexcept
		{
			const auto [left, right, top, bottom] = detail::GetLRTB(a);
			return detail::Contains(b.p0, left, right, top, bottom)
				&& detail::Contains(b.p1, left, right, top, bottom)
				&& detail::Contains(b.p2, left, right, top, bottom)
				&& detail::Contains(b.p3, left, right, top, bottom);
		}

		inline constexpr bool Contains(const RectF& a, const RoundRect& b) noexcept
		{
			return Contains(a, b.rect);
		}

		inline constexpr bool Contains(const Circle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Circle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Circle& a, const Line& b) noexcept
		{
			return Contains(a, b.begin)
				&& Contains(a, b.end);
		}

		inline constexpr bool Contains(const Circle& a, const Rect& b) noexcept
		{
			const double squareR = (a.r * a.r);
			return (b.tl().distanceFromSq(a.center) <= squareR)
				&& (b.br().distanceFromSq(a.center) <= squareR)
				&& (b.tr().distanceFromSq(a.center) <= squareR)
				&& (b.bl().distanceFromSq(a.center) <= squareR);
		}

		inline constexpr bool Contains(const Circle& a, const RectF& b) noexcept
		{
			const double squareR = (a.r * a.r);
			return (b.tl().distanceFromSq(a.center) <= squareR)
				&& (b.br().distanceFromSq(a.center) <= squareR)
				&& (b.tr().distanceFromSq(a.center) <= squareR)
				&& (b.bl().distanceFromSq(a.center) <= squareR);
		}

		inline constexpr bool Contains(const Circle& a, const Circle& b) noexcept
		{
			return (b.r <= a.r)
				&& (b.center.distanceFromSq(a.center) <= ((a.r - b.r) * (a.r - b.r)));
		}

		inline constexpr bool Contains(const Circle& a, const Triangle& b) noexcept
		{
			return Contains(a, b.p0)
				&& Contains(a, b.p1)
				&& Contains(a, b.p2);
		}

		inline constexpr bool Contains(const Circle& a, const Quad& b) noexcept
		{
			return Contains(a, b.p0)
				&& Contains(a, b.p1)
				&& Contains(a, b.p2)
				&& Contains(a, b.p3);
		}

		inline constexpr bool Contains(const Ellipse& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Ellipse& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Ellipse& a, const Line& b) noexcept
		{
			return Intersect(b.begin, a)
				&& Intersect(b.end, a);
		}

		inline constexpr bool Contains(const Ellipse& a, const Rect& b) noexcept
		{
			return Intersect(b.tl(), a)
				&& Intersect(b.tr(), a)
				&& Intersect(b.bl(), a)
				&& Intersect(b.br(), a);
		}

		inline constexpr bool Contains(const Ellipse& a, const RectF& b) noexcept
		{
			return Intersect(b.tl(), a)
				&& Intersect(b.tr(), a)
				&& Intersect(b.bl(), a)
				&& Intersect(b.br(), a);
		}

		inline constexpr bool Contains(const Ellipse& a, const Triangle& b) noexcept
		{
			return Intersect(b.p0, a)
				&& Intersect(b.p1, a)
				&& Intersect(b.p2, a);
		}

		inline constexpr bool Contains(const Ellipse& a, const Quad& b) noexcept
		{
			return Intersect(b.p0, a)
				&& Intersect(b.p1, a)
				&& Intersect(b.p2, a)
				&& Intersect(b.p3, a);
		}

		inline constexpr bool Contains(const Triangle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Triangle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Triangle& a, const Line& b) noexcept
		{
			return Intersect(b.begin, a)
				&& Intersect(b.end, a);
		}

		inline constexpr bool Contains(const Triangle& a, const Rect& b) noexcept
		{
			return Intersect(b.tl(), a)
				&& Intersect(b.tr(), a)
				&& Intersect(b.bl(), a)
				&& Intersect(b.br(), a);
		}

		inline constexpr bool Contains(const Triangle& a, const RectF& b) noexcept
		{
			return Intersect(b.tl(), a)
				&& Intersect(b.tr(), a)
				&& Intersect(b.bl(), a)
				&& Intersect(b.br(), a);
		}

		inline constexpr bool Contains(const Triangle& a, const Triangle& b) noexcept
		{
			return Intersect(b.p0, a)
				&& Intersect(b.p1, a)
				&& Intersect(b.p2, a);
		}

		inline constexpr bool Contains(const Triangle& a, const Quad& b) noexcept
		{
			return Intersect(b.p0, a)
				&& Intersect(b.p1, a)
				&& Intersect(b.p2, a)
				&& Intersect(b.p3, a);
		}

		inline constexpr bool Contains(const Quad& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Quad& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		inline constexpr bool Contains(const Quad& a, const Line& b) noexcept
		{
			return Intersect(b.begin, a)
				&& Intersect(b.end, a);
		}

		inline constexpr bool Contains(const Quad& a, const Rect& b) noexcept
		{
			return Intersect(b.tl(), a)
				&& Intersect(b.tr(), a)
				&& Intersect(b.bl(), a)
				&& Intersect(b.br(), a);
		}

		inline constexpr bool Contains(const Quad& a, const RectF& b) noexcept
		{
			return Intersect(b.tl(), a)
				&& Intersect(b.tr(), a)
				&& Intersect(b.bl(), a)
				&& Intersect(b.br(), a);
		}

		inline constexpr bool Contains(const Quad& a, const Triangle& b) noexcept
		{
			return Intersect(b.p0, a)
				&& Intersect(b.p1, a)
				&& Intersect(b.p2, a);
		}

		inline constexpr bool Contains(const Quad& a, const Quad& b) noexcept
		{
			return Intersect(b.p0, a)
				&& Intersect(b.p1, a)
				&& Intersect(b.p2, a)
				&& Intersect(b.p3, a);
		}

		inline bool Contains(const Polygon& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		inline bool Contains(const Polygon& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		//////////////////////////////////////////////////
		//
		//	Distance
		//
		//////////////////////////////////////////////////

		inline double Distance(const Point& a, const Point& b) noexcept
		{
			return a.distanceFrom(b);
		}

		inline double Distance(const Point& a, const Vec2& b) noexcept
		{
			return a.distanceFrom(b);
		}

		inline double Distance(const Vec2& a, const Point& b) noexcept
		{
			return a.distanceFrom(b);
		}

		inline double Distance(const Vec2& a, const Vec2& b) noexcept
		{
			return a.distanceFrom(b);
		}

		inline double Distance(const Vec2& a, const Circle& b) noexcept
		{
			return Max(0.0, a.distanceFrom(b.center) - b.r);
		}

		inline double Distance(const Line& a, const Point& b)
		{
			return Distance(Vec2{ b }, a);
		}

		inline double Distance(const Line& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Bezier2& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Bezier2& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Bezier2& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Rect& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Rect& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Rect& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const RectF& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const RectF& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const RectF& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const RectF& a, const Bezier2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Circle& a, const Point& b) noexcept
		{
			return Distance(b, a);
		}

		inline double Distance(const Circle& a, const Vec2& b) noexcept
		{
			return Distance(b, a);
		}

		inline double Distance(const Circle& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Circle& a, const Rect& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Circle& a, const RectF& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Circle& a, const Circle& b)
		{
			return Max(0.0, a.center.distanceFrom(b.center) - a.r - b.r);
		}

		inline double Distance(const Triangle& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Triangle& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Triangle& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Triangle& a, const Rect& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Triangle& a, const RectF& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Triangle& a, const Circle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Quad& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Quad& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Quad& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Quad& a, const Rect& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Quad& a, const RectF& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Quad& a, const Circle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Quad& a, const Triangle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const RoundRect& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const RoundRect& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const RoundRect& a, const Circle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const Rect& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const RectF& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const Circle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const Triangle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const Polygon& a, const Quad& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Point& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Vec2& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Line& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Rect& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const RectF& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Circle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Triangle& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Quad& b)
		{
			return Distance(b, a);
		}

		inline double Distance(const LineString& a, const Polygon& b)
		{
			return Distance(b, a);
		}

		//////////////////////////////////////////////////
		//
		//	Center
		//
		//////////////////////////////////////////////////

		inline constexpr Vec2 Center(const Point& a) noexcept
		{
			return a;
		}

		inline constexpr Vec2 Center(const Vec2& a) noexcept
		{
			return a;
		}

		inline constexpr Vec2 Center(const Line& a) noexcept
		{
			return a.center();
		}

		inline constexpr Vec2 Center(const Rect& a) noexcept
		{
			return a.center();
		}

		inline constexpr Vec2 Center(const RectF& a) noexcept
		{
			return a.center();
		}

		inline constexpr Vec2 Center(const Circle& a) noexcept
		{
			return a.center;
		}

		inline constexpr Vec2 Center(const Ellipse& a) noexcept
		{
			return a.center;
		}

		//////////////////////////////////////////////////
		//
		//	IsClockwise
		//
		//////////////////////////////////////////////////

		template <class PointType>
		inline constexpr bool IsClockwise(const PointType& p0, const PointType& p1, const PointType& p2) noexcept
		{
			if constexpr (std::is_same_v<typename PointType::value_type, int32>)
			{
				return (0 < (static_cast<int64>(p1.x - p0.x) * static_cast<int64>(p2.y - p0.y) - static_cast<int64>(p2.x - p0.x) * static_cast<int64>(p1.y - p0.y)));
			}
			else
			{
				return (0 < ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y)));
			}
		}

		template <class PointType>
		inline constexpr bool IsClockwise(const PointType& p0, const PointType& p1, const PointType& p2, const PointType& p3) noexcept
		{
			typename PointType::value_type sum = 0;
			sum += ((p1.x - p0.x) * (p1.y + p0.y));
			sum += ((p2.x - p1.x) * (p2.y + p1.y));
			sum += ((p3.x - p2.x) * (p3.y + p2.y));
			sum += ((p0.x - p3.x) * (p0.y + p3.y));
			return (sum < 0);
		}
		
		//////////////////////////////////////////////////
		//
		//	SmallestEnclosingCircle
		//
		//////////////////////////////////////////////////
	        //-----------------------------------------------
	        //    Authors (OpenSiv3D challenge #19)
	        //    - あぷりばーど
	        //    - Nachia
	        //    - Luke256
	        //    - ラクラムシ
	        //    - polyester
	        //    - sasa
	        //-----------------------------------------------

		SIV3D_CONCEPT_URBG_
		Circle SmallestEnclosingCircle(Array<Vec2> points, const double tolerance, URBG&& urbg)
		{
			if (points.size() == 0)
			{
				return Circle{};
			}

			if (points.size() == 1)
			{
				return Circle{ points[0], 0.0 };
			}

			if (points.size() == 2)
			{
				return Circle{ points[0], points[1] };
			}

			if (points.size() == 3)
			{
				return SmallestEnclosingCircle(points[0], points[1], points[2]);
			}

			if (points.size() == 4)
			{
				return SmallestEnclosingCircle(points[0], points[1], points[2], points[3], tolerance);
			}

			points.shuffle(std::forward<URBG>(urbg));

			// 適当な 1 点を含む最小包含円から始めて、少しずつ広げていく戦略を取る。
			// 含まれない点があったら、それが境界上になるように新たに取り直す。
			Circle circle{ points[0], 0.0 };

			for (size_t i = 1; i < points.size(); ++i)
			{
				const Vec2& p0 = points[i];

				if (not detail::Contains(circle, p0, tolerance))
				{
					circle = Circle{ p0, 0.0 };

					for (size_t j = 0; j < i; ++j)
					{
						const Vec2& p1 = points[j];
						
						if (not detail::Contains(circle, p1, tolerance))
						{
							circle = Circle{ p0, p1 };

							for (size_t k = 0; k < j; ++k)
							{
								const Vec2& p2 = points[k];
								
								if (not detail::Contains(circle, p2, tolerance))
								{
									circle = Triangle(p0, p1, p2).getCircumscribedCircle();
								}
							}
						}
					}
				}
			}

			return circle;
		}

		SIV3D_CONCEPT_URBG_
		Circle SmallestEnclosingCircle(Array<Vec2> points, URBG&& urbg, double tolerance)
		{
			return SmallestEnclosingCircle(std::move(points), tolerance, std::forward<URBG>(urbg));
		}
	}
}
