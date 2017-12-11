﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Fwd.hpp>
# include <Siv3D/Intersection.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Line.hpp>
# include <Siv3D/Bezier2.hpp>
# include <Siv3D/Bezier3.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Triangle.hpp>
# include <Siv3D/Quad.hpp>
# include <Siv3D/RoundRect.hpp>
# include <Siv3D/Polygon.hpp>
# include "Polynomial.hpp"

namespace s3d
{
	namespace detail
	{
		//
		//	http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
		//
		static double DistanceSq(const Vec2& begin, const Vec2& end, const Vec2& p) noexcept
		{
			const double l2 = begin.distanceFromSq(end);

			if (l2 == 0.0)
			{
				return begin.distanceFromSq(p);
			}

			const double t = std::max(0.0, std::min(1.0, (p - begin).dot(end - begin) / l2));

			const Vec2 projection = begin + t * (end - begin);

			return p.distanceFromSq(projection);
		}

		//
		// http://www.gamedev.net/topic/295943-is-this-a-better-point-in-triangle-test-2d/
		//
		static double Sign(const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
		{
			return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
		}

		static bool IsZero(const double x) noexcept
		{
			return std::abs(x) < 1e-10;
		}

		//
		//	http://www.phatcode.net/articles.php?id=459
		//
		static bool CircleTriangleIntersection(const Circle& circle, const Triangle& triangle) noexcept
		{
			const double centrex = circle.x;
			const double centrey = circle.y;
			const double radius = circle.r;
			const double v1x = triangle.p0.x;
			const double v1y = triangle.p0.y;
			const double v2x = triangle.p1.x;
			const double v2y = triangle.p1.y;
			const double v3x = triangle.p2.x;
			const double v3y = triangle.p2.y;

			//
			// TEST 1: Vertex within circle
			//
			const double c1x = centrex - v1x;
			const double c1y = centrey - v1y;

			const double radiusSqr = radius*radius;
			const double c1sqr = c1x*c1x + c1y*c1y - radiusSqr;

			if (c1sqr <= 0)
			{
				return true;
			}

			const double c2x = centrex - v2x;
			const double c2y = centrey - v2y;
			const double c2sqr = c2x*c2x + c2y*c2y - radiusSqr;

			if (c2sqr <= 0)
			{
				return true;
			}

			const double c3x = centrex - v3x;
			const double c3y = centrey - v3y;

			//const double &c3sqr = radiusSqr;//; reference to radiusSqr
			const double c3sqr = c3x*c3x + c3y*c3y - radiusSqr;

			if (c3sqr <= 0)
			{
				return true;
			}

			//;
			//; TEST 2: Circle centre within triangle
			//;

			//;
			//; Calculate edges
			//;
			const double e1x = v2x - v1x;
			const double e1y = v2y - v1y;

			const double e2x = v3x - v2x;
			const double e2y = v3y - v2y;

			const double e3x = v1x - v3x;
			const double e3y = v1y - v3y;

			if (e1y*c1x >= e1x*c1y
				&& e2y*c2x >= e2x*c2y
				&& e3y*c3x >= e3x*c3y)
			{
				return true;
			}

			//;
			//; TEST 3: Circle intersects edge
			//;
			double k = c1x*e1x + c1y*e1y;

			if (k > 0)
			{
				const double len = e1x*e1x + e1y*e1y;//; squared len

				if (k < len)
				{
					if (c1sqr * len <= k*k)
					{
						return true;
					}
				}
			}

			//; Second edge
			k = c2x*e2x + c2y*e2y;

			if (k > 0)
			{
				const double len = e2x*e2x + e2y*e2y;

				if (k < len)
				{
					if (c2sqr * len <= k*k)
					{
						return true;
					}
				}
			}

			//; Third edge
			k = c3x*e3x + c3y*e3y;

			if (k > 0)
			{
				const double len = e3x*e3x + e3y*e3y;

				if (k < len)
				{
					if (c3sqr * len <= k*k)
					{
						return true;
					}
				}
			}

			// Within
			if (circle.center.intersects(triangle))
			{
				return true;
			}

			//; We're done, no intersection
			return false;
		}

		struct RoundRectParts
		{
			RectF boundingRect;
			RectF rectA;
			RectF rectB;
			Circle circleTL;
			Circle circleTR;
			Circle circleBR;
			Circle circleBL;

			RoundRectParts(const RoundRect& roundRect) noexcept
			{
				const RectF& rect = roundRect.rect;
				const double rr = std::min({ rect.w * 0.5, rect.h * 0.5, roundRect.r });
				const double x0 = rect.x;
				const double x1 = rect.x + rr;
				const double x2 = rect.x + rect.w - rr;
				const double y0 = rect.y;
				const double y1 = rect.y + rr;
				const double y2 = rect.y + rect.h - rr;
				boundingRect = roundRect.rect;
				rectA.set(x0, y1, rect.w, y2 - y1);
				rectB.set(x1, y0, x2 - x1, rect.h);
				circleTL.set(x1, y1, rr);
				circleTR.set(x2, y1, rr);
				circleBR.set(x2, y2, rr);
				circleBL.set(x1, y2, rr);
			}

			template <class Shape>
			bool intersects(const Shape& shape) const noexcept
			{
				return boundingRect.intersects(shape)
					&& (rectA.intersects(shape)
					|| rectB.intersects(shape)
					|| circleTL.intersects(shape)
					|| circleTR.intersects(shape)
					|| circleBR.intersects(shape)
					|| circleBL.intersects(shape));
			}
		};

		Array<Vec2> RemoveDuplication(Array<Vec2> points)
		{
			if (points.size() >= 2)
			{
				for (auto it = points.begin();;)
				{
					if ((it + 1) == points.end())
					{
						break;
					}

					if (*it == *(it + 1))
					{
						it = points.erase(it);
					}
					else
					{
						++it;
					}
				}

				if (points.size() >= 2
					&& (points.front() == points.back()))
				{
					points.pop_back();
				}
			}

			return points;
		}

		static constexpr RectF RoughBoundingRect(const Bezier2& bezier)
		{
			const double minX = std::min({ bezier.p0.x, bezier.p1.x, bezier.p2.x });
			const double maxX = std::max({ bezier.p0.x, bezier.p1.x, bezier.p2.x });
			const double minY = std::min({ bezier.p0.x, bezier.p1.y, bezier.p2.y });
			const double maxY = std::max({ bezier.p0.y, bezier.p1.y, bezier.p2.y });
			return{ minX, minY, maxX - minX,maxY - minY };
		}

		static constexpr RectF RoughBoundingRect(const Bezier3& bezier)
		{
			const double minX = std::min({ bezier.p0.x, bezier.p1.x, bezier.p2.x, bezier.p3.x });
			const double maxX = std::max({ bezier.p0.x, bezier.p1.x, bezier.p2.x, bezier.p3.x });
			const double minY = std::min({ bezier.p0.x, bezier.p1.y, bezier.p2.y, bezier.p3.y });
			const double maxY = std::max({ bezier.p0.y, bezier.p1.y, bezier.p2.y, bezier.p3.y });
			return{ minX, minY, maxX - minX,maxY - minY };
		}
	}

	namespace Geometry2D
	{
		////////////////////////////////////////////////////////////////////
		//
		//	Point vs
		//
		bool Intersect(const Point& a, const Point& b) noexcept
		{
			return a == b;
		}

		bool Intersect(const Point& a, const Vec2& b) noexcept
		{
			return b.distanceFromSq(a) < 1.0;
		}

		bool Intersect(const Point& a, const Line& b) noexcept
		{
			return detail::DistanceSq(b.begin, b.end, a) < 1.0;
		}

		bool Intersect(const Point& a, const Rect& b) noexcept
		{
			return b.x <= a.x && a.x < (b.x + b.w) && b.y <= a.y && a.y < (b.y + b.h);
		}

		bool Intersect(const Point& a, const RectF& b) noexcept
		{
			return b.x <= a.x && a.x < (b.x + b.w) && b.y <= a.y && a.y < (b.y + b.h);
		}

		bool Intersect(const Point& a, const Circle& b) noexcept
		{
			return a.distanceFromSq(b.center) <= (b.r * b.r);
		}

		bool Intersect(const Point& a, const Ellipse& b) noexcept
		{
			if (b.a == 0.0 || b.b == 0.0)
			{
				return false;
			}

			const double xh = (b.x - a.x);
			const double yk = (b.y - a.y);

			return (xh * xh) / (b.a * b.a) + (yk * yk) / (b.b * b.b) <= 1.0;
		}

		bool Intersect(const Point& a, const Triangle& b) noexcept
		{
			const bool b1 = detail::Sign(a, b.p0, b.p1) < 0.0;
			const bool b2 = detail::Sign(a, b.p1, b.p2) < 0.0;
			const bool b3 = detail::Sign(a, b.p2, b.p0) < 0.0;

			return ((b1 == b2) && (b2 == b3));
		}

		bool Intersect(const Point& a, const Quad& b) noexcept
		{
			return Intersect(a, Triangle{ b.p0, b.p1, b.p3 }) || Intersect(a, Triangle{ b.p1, b.p2, b.p3 });
		}

		bool Intersect(const Point& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Point& a, const Polygon& b) noexcept
		{
			return Intersect(Vec2(a), b);
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Vec2 vs
		//
		bool Intersect(const Vec2& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Vec2& a, const Vec2& b) noexcept
		{
			return a.distanceFromSq(b) < 1.0;
		}

		bool Intersect(const Vec2& a, const Line& b) noexcept
		{
			return detail::DistanceSq(b.begin, b.end, a) < 1.0;
		}

		bool Intersect(const Vec2& a, const Rect& b) noexcept
		{
			return b.x <= a.x && a.x < (b.x + b.w) && b.y <= a.y && a.y < (b.y + b.h);
		}

		bool Intersect(const Vec2& a, const RectF& b) noexcept
		{
			return b.x <= a.x && a.x < (b.x + b.w) && b.y <= a.y && a.y < (b.y + b.h);
		}

		bool Intersect(const Vec2& a, const Circle& b) noexcept
		{
			return a.distanceFromSq(b.center) <= (b.r * b.r);
		}

		bool Intersect(const Vec2& a, const Ellipse& b) noexcept
		{
			if (b.a == 0.0 || b.b == 0.0)
			{
				return false;
			}

			const double xh = (b.x - a.x);
			const double yk = (b.y - a.y);

			return (xh * xh) / (b.a * b.a) + (yk * yk) / (b.b * b.b) <= 1.0;
		}

		bool Intersect(const Vec2& a, const Triangle& b) noexcept
		{
			const bool b1 = detail::Sign(a, b.p0, b.p1) < 0.0;
			const bool b2 = detail::Sign(a, b.p1, b.p2) < 0.0;
			const bool b3 = detail::Sign(a, b.p2, b.p0) < 0.0;

			return ((b1 == b2) && (b2 == b3));
		}

		bool Intersect(const Vec2& a, const Quad& b) noexcept
		{
			return Intersect(a, Triangle{ b.p0, b.p1, b.p3 }) || Intersect(a, Triangle{ b.p1, b.p2, b.p3 });
		}

		bool Intersect(const Vec2& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Vec2& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				if (Intersect(a, b.triangle(i)))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Line vs
		//
		bool Intersect(const Line& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Line& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		//
		// `Line::intersectsAt()` is based on
		// https://www.codeproject.com/Tips/862988/Find-the-Intersection-Point-of-Two-Line-Segments
		//
		// Licenced with the Code Project Open Licence (CPOL)
		// http://www.codeproject.com/info/cpol10.aspx
		//
		bool Intersect(const Line& a, const Line& b) noexcept
		{
			const Vec2 r = a.end - a.begin;
			const Vec2 s = b.end - b.begin;
			const Vec2 qp = b.begin - a.begin;
			const double rxs = r.x * s.y - r.y * s.x;
			const double qpxr = qp.x * r.y - qp.y * r.x;
			const double qpxs = qp.x * s.y - qp.y * s.x;
			const bool rxsIsZero = detail::IsZero(rxs);

			if (rxsIsZero && detail::IsZero(qpxr))
			{
				const double qpr = qp.dot(r);
				const double pqs = (a.begin - b.begin).dot(s);

				if ((0 <= qpr && qpr <= r.dot(r)) || (0 <= pqs && pqs <= s.dot(s)))
				{
					// Two lines are overlapping			
					return true;
				}

				// Two lines are collinear but disjoint.
				return false;
			}

			if (rxsIsZero && !detail::IsZero(qpxr))
			{
				// Two lines are parallel and non-intersecting.
				return false;
			}

			const double t = qpxs / rxs;
			const double u = qpxr / rxs;

			if (!rxsIsZero && (0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0))
			{
				// An intersection was found
				return true;
			}

			// Two line segments are not parallel but do not intersect
			return false;
		}

		bool Intersect(const Line& a, const Rect& b) noexcept
		{
			if (Intersect(a.begin, b) || Intersect(a.end, b))
			{
				return true;
			}

			const Vec2 tl = b.tl(), tr = b.tr(), br = b.br(), bl = b.bl();

			return Intersect(a, Line(tl, tr))
				|| Intersect(a, Line(tr, br))
				|| Intersect(a, Line(br, bl))
				|| Intersect(a, Line(bl, tl));
		}

		bool Intersect(const Line& a, const RectF& b) noexcept
		{
			if (Intersect(a.begin, b) || Intersect(a.end, b))
			{
				return true;
			}

			const Vec2 tl = b.tl(), tr = b.tr(), br = b.br(), bl = b.bl();

			return Intersect(a, Line(tl, tr))
				|| Intersect(a, Line(tr, br))
				|| Intersect(a, Line(br, bl))
				|| Intersect(a, Line(bl, tl));
		}

		bool Intersect(const Line& a, const Circle& b) noexcept
		{
			const Vec2 ab = a.end - a.begin;
			const Vec2 ac = b.center - a.begin;
			const Vec2 bc = b.center - a.end;
			const double e = ac.dot(ab);
			const double rr = b.r * b.r;

			if (e <= 0.0)
			{
				return ac.dot(ac) <= rr;
			}

			const double f = ab.dot(ab);

			if (e >= f)
			{
				return bc.dot(bc) <= rr;
			}

			return (ac.dot(ac) - e * e / f) <= rr;
		}

		//
		//	https://github.com/thelonious/kld-intersections/blob/development/lib/Intersection.js
		//
		bool Intersect(const Line& a, const Ellipse& b) noexcept
		{
			const double rx = b.a;
			const double ry = b.b;
			const Vec2 dir(a.vector());
			const Vec2 diff(a.begin - b.center);
			const Vec2 mDir(dir.x / (rx*rx), dir.y / (ry*ry));
			const Vec2 mDiff(diff.x / (rx*rx), diff.y / (ry*ry));

			const double va = dir.dot(mDir);
			const double vb = dir.dot(mDiff);
			const double vc = diff.dot(mDiff) - 1.0;
			double vd = vb*vb - va*vc;

			const double ERRF = 1e-15;
			const double ZEROepsilon = 10 * std::max({ std::abs(va), std::abs(vb), std::abs(vc) }) * ERRF;		
			if (std::abs(vd) < ZEROepsilon)
			{
				vd = 0;
			}

			if (vd < 0)
			{
				return false;
			}
			else if (vd > 0)
			{
				const double root = std::sqrt(vd);
				double t_a = (-vb - root) / va;
				double t_b = (-vb + root) / va;
				t_b = (t_b > 1) ? t_b - ERRF : (t_b < 0) ? t_b + ERRF : t_b;
				t_a = (t_a > 1) ? t_a - ERRF : (t_a < 0) ? t_a + ERRF : t_a;

				if ((t_a < 0 || 1 < t_a) && (t_b < 0 || 1 < t_b))
				{
					return !((t_a < 0 && t_b < 0) || (t_a > 1 && t_b > 1));
				}
				else
				{
					return true;
				}
			}
			else
			{
				const double t = -vb / va;
				return  (0 <= t && t <= 1);
			}
		}

		bool Intersect(const Line& a, const Triangle& b) noexcept
		{
			if (Intersect(a.begin, b) || Intersect(a.end, b))
			{
				return true;
			}

			return Intersect(a, Line(b.p0, b.p1))
				|| Intersect(a, Line(b.p1, b.p2))
				|| Intersect(a, Line(b.p2, b.p0));
		}

		bool Intersect(const Line& a, const Quad& b) noexcept
		{
			if (Intersect(a.begin, b) || Intersect(a.end, b))
			{
				return true;
			}

			return Intersect(a, Line(b.p0, b.p1))
				|| Intersect(a, Line(b.p1, b.p2))
				|| Intersect(a, Line(b.p2, b.p3))
				|| Intersect(a, Line(b.p3, b.p0));
		}

		bool Intersect(const Line& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Line& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				if (Intersect(a, b.triangle(i)))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Bezier2 vs
		//
		bool Intersect(const Bezier2& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse(b)).has_value();
		}

		bool Intersect(const Bezier2& a, const Ellipse& b)
		{
			return IntersectAt(a, b).has_value();
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Bezier3 vs
		//
		bool Intersect(const Bezier3& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse(b)).has_value();
		}

		bool Intersect(const Bezier3& a, const Ellipse& b)
		{
			return IntersectAt(a, b).has_value();
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Rect vs
		//
		bool Intersect(const Rect& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Rect& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Rect& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Rect& a, const Rect& b) noexcept
		{
			return (a.x < b.x + b.w) && (b.x < a.x + a.w) && (a.y < b.y + b.h) && (b.y < a.y + a.h);
		}

		bool Intersect(const Rect& a, const RectF& b) noexcept
		{
			return (a.x < b.x + b.w) && (b.x < a.x + a.w) && (a.y < b.y + b.h) && (b.y < a.y + a.h);
		}

		bool Intersect(const Rect& a, const Circle& b) noexcept
		{
			const double aw = a.w * 0.5;
			const double ah = a.h * 0.5;
			const double cX = std::abs(b.x - a.x - aw);
			const double cY = std::abs(b.y - a.y - ah);

			if (cX > (aw + b.r) || cY > (ah + b.r))
			{
				return false;
			}

			if (cX <= (aw) || cY <= (ah))
			{
				return true;
			}

			return (cX - aw) * (cX - aw) + (cY - ah) * (cY - ah) <= (b.r * b.r);
		}

		bool Intersect(const Rect& a, const Triangle& b) noexcept
		{
			return Intersect(Triangle(a.tl(), a.tr(), a.bl()), b)
				|| Intersect(Triangle(a.bl(), a.tr(), a.br()), b);
		}

		bool Intersect(const Rect& a, const Quad& b) noexcept
		{
			return Intersect(a, Triangle(b.p0, b.p1, b.p2))
				|| Intersect(a, Triangle(b.p0, b.p2, b.p3));
		}

		bool Intersect(const Rect& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Rect& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				if (Intersect(a, b.triangle(i)))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	RectF vs
		//
		bool Intersect(const RectF& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RectF& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RectF& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RectF& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RectF& a, const RectF& b) noexcept
		{
			return (a.x < b.x + b.w) && (b.x < a.x + a.w) && (a.y < b.y + b.h) && (b.y < a.y + a.h);
		}

		bool Intersect(const RectF& a, const Circle& b) noexcept
		{
			const double aw = a.w * 0.5;
			const double ah = a.h * 0.5;
			const double cX = std::abs(b.x - a.x - aw);
			const double cY = std::abs(b.y - a.y - ah);

			if (cX >(aw + b.r) || cY >(ah + b.r))
			{
				return false;
			}

			if (cX <= (aw) || cY <= (ah))
			{
				return true;
			}

			return (cX - aw) * (cX - aw) + (cY - ah) * (cY - ah) <= (b.r * b.r);
		}

		bool Intersect(const RectF& a, const Triangle& b) noexcept
		{
			return Intersect(Triangle(a.tl(), a.tr(), a.bl()), b)
				|| Intersect(Triangle(a.bl(), a.tr(), a.br()), b);
		}

		bool Intersect(const RectF& a, const Quad& b) noexcept
		{
			return Intersect(a, Triangle(b.p0, b.p1, b.p2))
				|| Intersect(a, Triangle(b.p0, b.p2, b.p3));
		}

		bool Intersect(const RectF& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const RectF& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				if (Intersect(a, b.triangle(i)))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Circle vs
		//
		bool Intersect(const Circle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const Bezier2& b)
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const Bezier3& b)
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const Circle& b) noexcept
		{
			return ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)) <= ((a.r + b.r)*(a.r + b.r));
		}

		bool Intersect(const Circle& a, const Triangle& b) noexcept
		{
			return detail::CircleTriangleIntersection(a, b);
		}

		bool Intersect(const Circle& a, const Quad& b) noexcept
		{
			return detail::CircleTriangleIntersection(a, Triangle{ b.p0, b.p1, b.p3 })
				|| detail::CircleTriangleIntersection(a, Triangle{ b.p1, b.p2, b.p3 });
		}

		bool Intersect(const Circle& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Circle& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				if (Intersect(a, b.triangle(i)))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Ellipse vs
		//
		bool Intersect(const Ellipse& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Ellipse& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Ellipse& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Ellipse& a, const Bezier2& b)
		{
			return Intersect(b, a);
		}

		bool Intersect(const Ellipse& a, const Bezier3& b)
		{
			return Intersect(b, a);
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Triangle vs
		//
		bool Intersect(const Triangle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Triangle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Triangle& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Triangle& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Triangle& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Triangle& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		//
		//	http://marupeke296.com/COL_2D_TriTri.html
		//
		bool Intersect(const Triangle& a, const Triangle& b) noexcept
		{
			const int32 other[3] = { 1, 2, 0 };
			const int32 pindex[4] = { 1, 2, 0, 1 };
			const Triangle* tri[3] = { &a, &b, &a };

			for (int32 t = 0; t < 2; ++t)
			{
				const Triangle& ta = *tri[t];
				const Triangle& tb = *tri[t + 1];

				for (int32 i = 0; i < 3; ++i)
				{
					const Float2 vec = (ta.p(pindex[i + 1]) - ta.p(pindex[i])).normalized();
					const Float2 sepVec(vec.y, -vec.x);

					float s1min = sepVec.dot(ta.p(i));
					float s1max = sepVec.dot(ta.p(other[i]));
					
					if (s1min > s1max)
					{
						std::swap(s1min, s1max);
					}

					float s2min = sepVec.dot(tb.p(0));
					float s2max = sepVec.dot(tb.p(1));
					
					if (s2min > s2max)
					{
						std::swap(s2min, s2max);
					}

					const float d3 = sepVec.dot(tb.p(2));

					if (d3 < s2min)
					{
						s2min = d3;
					}
					else if (d3 > s2max)
					{
						s2max = d3;
					}

					if (   (s2min <= s1min && s1min <= s2max)
						|| (s2min <= s1max && s1max <= s2max)
						|| (s1min <= s2min && s2min <= s1max)
						|| (s1min <= s2max && s2max <= s1max))
					{
						continue;
					}

					return false;
				}
			}

			return true;
		}

		bool Intersect(const Triangle& a, const Quad& b) noexcept
		{
			return Intersect(a, Triangle(b.p0, b.p1, b.p2))
				 || Intersect(a, Triangle(b.p0, b.p2, b.p3));
		}

		bool Intersect(const Triangle& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Triangle& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				if (Intersect(a, b.triangle(i)))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Quad vs
		//
		bool Intersect(const Quad& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Quad& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Quad& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Quad& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Quad& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Quad& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Quad& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Quad& a, const Quad& b) noexcept
		{
			return Intersect(Triangle(a.p0, a.p1, a.p2), b)
				|| Intersect(Triangle(a.p0, a.p2, a.p3), b);
		}

		bool Intersect(const Quad& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Quad& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const Triangle a0(a.p0, a.p1, a.p2);
			const Triangle a1(a.p0, a.p2, a.p3);

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				const Triangle b0 = b.triangle(i);

				if (Intersect(a0, b0) || Intersect(a1, b0))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	RoundRect vs
		//
		bool Intersect(const RoundRect& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const Quad& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const RoundRect& a, const RoundRect& b) noexcept
		{
			if (!Intersect(a.rect, b.rect))
			{
				return false;
			}

			const detail::RoundRectParts partsA(a);
			const detail::RoundRectParts partsB(b);

			return partsA.intersects(partsB.rectA)
				|| partsA.intersects(partsB.rectB)
				|| partsA.intersects(partsB.circleTL)
				|| partsA.intersects(partsB.circleTR)
				|| partsA.intersects(partsB.circleBR)
				|| partsA.intersects(partsB.circleBL);
		}

		bool Intersect(const RoundRect& a, const Polygon& b) noexcept
		{
			if (!b || !Intersect(a, b.boundingRect()))
			{
				return false;
			}

			const detail::RoundRectParts partsA(a);

			const size_t num_triangles = b.num_triangles();

			for (size_t i = 0; i < num_triangles; ++i)
			{
				if (partsA.intersects(b.triangle(i)))
				{
					return true;
				}
			}

			return false;
		}

		////////////////////////////////////////////////////////////////////
		//
		//	Polygon vs
		//
		bool Intersect(const Polygon& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const Line& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const Rect& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const RectF& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const Circle& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const Triangle& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const Quad& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const RoundRect& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Polygon& a, const Polygon&	b)
		{
			return a.intersects(b);
		}
		
		////////////////////////////////////////////////////////////////////
		//
		//	IntersectAt
		//
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Rect& b)
		{
			return IntersectAt(a, RectF(b));
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const RectF& b)
		{
			if (!a.intersects(b))
			{
				return none;
			}

			const Line linesB[4] = { b.top(), b.right(), b.bottom(), b.left() };

			Array<Vec2> points;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto at = a.intersectsAt(linesB[i]))
				{
					points.push_back(at.value());
				}
			}

			return detail::RemoveDuplication(std::move(points));
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse(b));
		}

		//
		//	https://github.com/thelonious/kld-intersections/blob/development/lib/Intersection.js
		//
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Ellipse& b)
		{
			const double rx = b.a;
			const double ry = b.b;
			const Vec2 dir(a.vector());
			const Vec2 diff(a.begin - b.center);
			const Vec2 mDir(dir.x / (rx*rx), dir.y / (ry*ry));
			const Vec2 mDiff(diff.x / (rx*rx), diff.y / (ry*ry));

			const double va = dir.dot(mDir);
			const double vb = dir.dot(mDiff);
			const double vc = diff.dot(mDiff) - 1.0;
			double vd = vb*vb - va*vc;

			const double ERRF = 1e-15;
			const double ZEROepsilon = 10 * std::max({ std::abs(va), std::abs(vb), std::abs(vc) }) * ERRF;
			if (std::abs(vd) < ZEROepsilon)
			{
				vd = 0;
			}

			Array<Vec2> results;

			if (vd < 0)
			{
				return none;
			}
			else if (vd > 0)
			{
				const double root = std::sqrt(vd);
				double t_a = (-vb - root) / va;
				double t_b = (-vb + root) / va;
				t_b = (t_b > 1) ? t_b - ERRF : (t_b < 0) ? t_b + ERRF : t_b;
				t_a = (t_a > 1) ? t_a - ERRF : (t_a < 0) ? t_a + ERRF : t_a;

				if ((t_a < 0 || 1 < t_a) && (t_b < 0 || 1 < t_b))
				{
					if ((t_a < 0 && t_b < 0) || (t_a > 1 && t_b > 1))
					{
						return none;
					}
					else
					{
						return Array<Vec2>();
					}
				}
				else
				{
					if (0 <= t_a && t_a <= 1)
					{
						results.emplace_back(a.begin.lerp(a.end, t_a));
					}

					if (0 <= t_b && t_b <= 1)
					{
						results.emplace_back(a.begin.lerp(a.end, t_b));
					}
				}
			}
			else
			{
				const double t = -vb / va;
				
				if (0 <= t && t <= 1)
				{	
					results.emplace_back(a.begin.lerp(a.end, t));
				}
				else
				{
					return none;
				}
			}

			return results;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse(b));
		}

		//
		//	https://github.com/thelonious/kld-intersections/blob/development/lib/Intersection.js
		//
		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Ellipse& b)
		{
			if (!Intersect(detail::RoughBoundingRect(a), b.boundingRect()))
			{
				return none;
			}

			const Vec2 t1 = a.p1 * -2;
			const Vec2 c2 = a.p0 + (t1 + a.p2);
			const Vec2 t2 = a.p0 * -2;
			const Vec2 t3 = a.p1 * 2;
			const Vec2 c1 = t2 + t3;
			const Vec2 c0 = a.p0;
			const double rxrx = b.a * b.a;
			const double ryry = b.b * b.b;

			const Array<double> roots = Polynomial({
				ryry*c2.x*c2.x + rxrx*c2.y*c2.y,
				2 * (ryry*c2.x*c1.x + rxrx*c2.y*c1.y),
				ryry*(2 * c2.x*c0.x + c1.x*c1.x) + rxrx*(2 * c2.y*c0.y + c1.y*c1.y) - 2 * (ryry*b.x*c2.x + rxrx*b.y*c2.y),
				2 * (ryry*c1.x*(c0.x - b.x) + rxrx*c1.y*(c0.y - b.y)),
				ryry*(c0.x*c0.x + b.x*b.x) + rxrx*(c0.y*c0.y + b.y*b.y) - 2 * (ryry*b.x*c0.x + rxrx*b.y*c0.y) - rxrx*ryry,
			}).getRoots();

			Array<Vec2> points;

			for (size_t i = 0; i < roots.size(); ++i)
			{
				const double t = roots[i];

				if (0 <= t && t <= 1)
				{
					points.push_back(c2 * (t*t) + (c1 * t + c0));
				}
			}

			if (points)
			{
				return points;
			}
			else if (Intersect(a.p0, b) || Intersect(a.p2, b))
			{
				return Array<Vec2>();
			}
			else
			{
				return none;
			}
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse(b));
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Ellipse& b)
		{
			if (!Intersect(detail::RoughBoundingRect(a), b.boundingRect()))
			{
				return none;
			}

			const Vec2 t1 = -a.p0;
			const Vec2 t2 = a.p1 * 3.0;
			const Vec2 t3 = a.p2 * -3.0;
			const Vec2 t4 = t1 + (t2 + (t3 + a.p3));
			const Vec2 c3 = t4;

			const Vec2 u1 = a.p0 * 3.0;
			const Vec2 u2 = a.p1 * -6.0;
			const Vec2 u3 = a.p2 * 3.0;
			const Vec2 u4 = u1 + (u2 + u3);
			const Vec2 c2 = u4;

			const Vec2 v1 = a.p0 * -3.0;
			const Vec2 v2 = a.p1 * 3.0;
			const Vec2 v3 = v1 + v2;
			const Vec2 c1 = v3;

			const Vec2 c0 = a.p0;

			const double rxrx = b.a*b.a;
			const double ryry = b.b*b.b;

			Polynomial poly({
				c3.x*c3.x*ryry + c3.y*c3.y*rxrx,
				2 * (c3.x*c2.x*ryry + c3.y*c2.y*rxrx),
				2 * (c3.x*c1.x*ryry + c3.y*c1.y*rxrx) + c2.x*c2.x*ryry + c2.y*c2.y*rxrx,
				2 * c3.x*ryry*(c0.x - b.x) + 2 * c3.y*rxrx*(c0.y - b.y) +
				2 * (c2.x*c1.x*ryry + c2.y*c1.y*rxrx),
				2 * c2.x*ryry*(c0.x - b.x) + 2 * c2.y*rxrx*(c0.y - b.y) +
				c1.x*c1.x*ryry + c1.y*c1.y*rxrx,
				2 * c1.x*ryry*(c0.x - b.x) + 2 * c1.y*rxrx*(c0.y - b.y),
				c0.x*c0.x*ryry - 2 * c0.y*b.y*rxrx - 2 * c0.x*b.x*ryry +
				c0.y*c0.y*rxrx + b.x*b.x*ryry + b.y*b.y*rxrx - rxrx*ryry
			});
			
			Array<double> roots = poly.getRootsInInterval(0, 1);
			{
				const double ZEROepsilon = 1e-15;
				roots.sort_by([](double a, double b) { return a < b; });
		
				for (size_t i = 1; i < roots.size();)
				{
					if (std::abs(roots[i] - roots[i - 1]) < ZEROepsilon)
					{
						roots.remove_at(i);
					}
					else
					{
						++i;
					}
				}
			}

			Array<Vec2> points;

			for (size_t i = 0; i < roots.size(); ++i)
			{
				const double t = roots[i];
				const Vec2 v = c3 * (t * t * t) + (c2 * (t * t) + (c1 * t + c0));
				points.push_back(v);
			}

			if (points)
			{
				return points;
			}
			else if (Intersect(a.p0, b) || Intersect(a.p3, b))
			{
				return Array<Vec2>();
			}
			else
			{
				return none;
			}
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse(b));
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Line& b)
		{
			return IntersectAt(b, RectF(a));
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b)
		{
			return IntersectAt(RectF(a), RectF(b));
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b)
		{
			return IntersectAt(RectF(a), b);
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Ellipse& b)
		{
			return IntersectAt(RectF(a), b);
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse(b));
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b)
		{
			return IntersectAt(a, RectF(b));
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b)
		{
			if (!a.intersects(b))
			{
				return none;
			}

			const Line linesA[4] = { a.top(), a.right(), a.bottom(), a.left() };
			const Line linesB[4] = { b.top(), b.right(), b.bottom(), b.left() };

			Array<Vec2> points;

			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t k = 0; k < 4; ++k)
				{
					if (const auto at = linesA[i].intersectsAt(linesB[k]))
					{
						points.push_back(at.value());
					}
				}
			}

			return detail::RemoveDuplication(std::move(points));
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Ellipse& b)
		{
			Array<Vec2> points;

			const Optional<Array<Vec2>> r[4] =
			{
				IntersectAt(a.top(), b),
				IntersectAt(a.right(), b),
				IntersectAt(a.bottom(), b),
				IntersectAt(a.left(), b),
			};

			bool hasIntersection = false;

			for (const auto& intersections : r)
			{
				if (intersections)
				{
					hasIntersection = true;

					points.append(intersections.value());
				}
			}

			if (!hasIntersection)
			{
				return none;
			}

			return detail::RemoveDuplication(std::move(points));
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Line& b)
		{
			return IntersectAt(b, Ellipse(a));
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier2& b)
		{
			return IntersectAt(b, Ellipse(a));
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier3& b)
		{
			return IntersectAt(b, Ellipse(a));
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Rect& b)
		{
			return IntersectAt(b, Ellipse(a));
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const RectF& b)
		{
			return IntersectAt(b, Ellipse(a));
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Line& b)
		{
			return IntersectAt(b, a);
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier2& b)
		{
			return IntersectAt(b, a);
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier3& b)
		{
			return IntersectAt(b, a);
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Rect& b)
		{
			return IntersectAt(b, a);
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RectF& b)
		{
			return IntersectAt(b, a);
		}
	}
}
