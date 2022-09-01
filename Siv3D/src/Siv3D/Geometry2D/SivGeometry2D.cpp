//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
//	Authors (OpenSiv3D challenge participants)
//	- Ebishu
//	- fal_rnd
//	- きつねび
//-----------------------------------------------

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Bezier2.hpp>
# include <Siv3D/Bezier3.hpp>
# include <Siv3D/MultiPolygon.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Polygon/PolygonDetail.hpp>

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
# include <ThirdParty/concaveman-cpp/concaveman.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

# include "Polynomial.hpp"

namespace s3d
{
	using GVec2 = boost::geometry::model::d2::point_xy<double>;
	using GSegment = boost::geometry::model::segment<Vec2>;
	using GBox = boost::geometry::model::box<Vec2>;

	namespace detail
	{
		[[nodiscard]]
		static bool IsZero(const double x) noexcept
		{
			return (std::abs(x) < 1e-10);
		}

		//
		//	http://www.phatcode.net/articles.php?id=459
		//
		[[nodiscard]]
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

			const double radiusSqr = radius * radius;
			const double c1sqr = c1x * c1x + c1y * c1y - radiusSqr;

			if (c1sqr <= 0)
			{
				return true;
			}

			const double c2x = centrex - v2x;
			const double c2y = centrey - v2y;
			const double c2sqr = c2x * c2x + c2y * c2y - radiusSqr;

			if (c2sqr <= 0)
			{
				return true;
			}

			const double c3x = centrex - v3x;
			const double c3y = centrey - v3y;

			//const double &c3sqr = radiusSqr;//; reference to radiusSqr
			const double c3sqr = c3x * c3x + c3y * c3y - radiusSqr;

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

			if (e1y * c1x >= e1x * c1y
				&& e2y * c2x >= e2x * c2y
				&& e3y * c3x >= e3x * c3y)
			{
				return true;
			}

			//;
			//; TEST 3: Circle intersects edge
			//;
			double k = c1x * e1x + c1y * e1y;

			if (k > 0)
			{
				const double len = e1x * e1x + e1y * e1y;//; squared len

				if (k < len)
				{
					if (c1sqr * len <= k * k)
					{
						return true;
					}
				}
			}

			//; Second edge
			k = c2x * e2x + c2y * e2y;

			if (k > 0)
			{
				const double len = e2x * e2x + e2y * e2y;

				if (k < len)
				{
					if (c2sqr * len <= k * k)
					{
						return true;
					}
				}
			}

			//; Third edge
			k = c3x * e3x + c3y * e3y;

			if (k > 0)
			{
				const double len = e3x * e3x + e3y * e3y;

				if (k < len)
				{
					if (c3sqr * len <= k * k)
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

		[[nodiscard]]
		static constexpr RectF RoughBoundingRect(const Bezier2& bezier) noexcept
		{
			const double minX = Min({ bezier.p0.x, bezier.p1.x, bezier.p2.x });
			const double maxX = Max({ bezier.p0.x, bezier.p1.x, bezier.p2.x });
			const double minY = Min({ bezier.p0.y, bezier.p1.y, bezier.p2.y });
			const double maxY = Max({ bezier.p0.y, bezier.p1.y, bezier.p2.y });
			return{ minX, minY, (maxX - minX), (maxY - minY) };
		}

		[[nodiscard]]
		static constexpr RectF RoughBoundingRect(const Bezier3& bezier) noexcept
		{
			const double minX = Min({ bezier.p0.x, bezier.p1.x, bezier.p2.x, bezier.p3.x });
			const double maxX = Max({ bezier.p0.x, bezier.p1.x, bezier.p2.x, bezier.p3.x });
			const double minY = Min({ bezier.p0.y, bezier.p1.y, bezier.p2.y, bezier.p3.y });
			const double maxY = Max({ bezier.p0.y, bezier.p1.y, bezier.p2.y, bezier.p3.y });
			return{ minX, minY, (maxX - minX), (maxY - minY) };
		}

		[[nodiscard]]
		static Array<Vec2> RemoveDuplication(Array<Vec2> points)
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

		[[nodiscard]]
		inline constexpr bool AxisAlignedLineIntersect(const Point& vp, int32 vl, const Point& hp, int32 hl)
		{
			return InOpenRange(vp.x, hp.x, hp.x + hl)
				&& InOpenRange(hp.y, vp.y, vp.y + vl);
		}

		[[nodiscard]]
		inline constexpr bool AxisAlignedLineIntersect(const Vec2& vp, double vl, const Vec2& hp, double hl)
		{
			return InOpenRange(vp.x, hp.x, hp.x + hl)
				&& InOpenRange(hp.y, vp.y, vp.y + vl);
		}

		[[nodiscard]]
		static CwOpenPolygon MakeTriangle(const Triangle& t)
		{
			CwOpenPolygon poly;

			const Vec2* pPoints = &t.p0;

			poly.outer().assign(pPoints, (pPoints + 3));

			return poly;
		}

		[[nodiscard]]
		static CwOpenPolygon MakeQuad(const Quad& q)
		{
			CwOpenPolygon poly;

			const Vec2* pPoints = &q.p0;

			poly.outer().assign(pPoints, (pPoints + 4));

			return poly;
		}

		[[nodiscard]]
		static GLineString MakeLineString(const LineString& lines)
		{
			return GLineString(lines.begin(), lines.end());
		}

		[[nodiscard]]
		static std::array<Vec2, 4> RectPoints(const RectF& a) noexcept
		{
			return { a.tl(), a.tr(), a.br(), a.bl() };
		}

		[[nodiscard]]
		static std::array<Line, 4> DivideToLines(const RoundRect& a)
		{
			const std::array<Line, 4> lines =
			{
				a.rect.side(0).stretched(-a.r),
				a.rect.side(1).stretched(-a.r),
				a.rect.side(2).stretched(-a.r),
				a.rect.side(3).stretched(-a.r)
			};

			return lines;
		}

		[[nodiscard]]
		static std::array<Circle, 4> DivideToCircles(const RoundRect& a)
		{
			const std::array<Vec2, 4> points = RectPoints(a.rect);
			const std::array<Vec2, 4> add = { Vec2{ a.r, 0 }, Vec2{ 0, a.r }, Vec2{ -a.r, 0 }, Vec2{ 0, -a.r } };

			std::array<Circle, 4> circles;

			for (size_t i = 0; i < 4; ++i)
			{
				const Vec2 begin = points[i];
				const Vec2 center = begin + add[i] + add[(i + 1) % 4];
				circles[i] = Circle{ center, a.r };
			}

			return circles;
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
				const double rr = Min({ (rect.w * 0.5), (rect.h * 0.5), roundRect.r });
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

		enum class RoundRectRegion
		{
			TL, T, TR,
			L, C, R,
			BL, B, BR
		};

		RoundRectRegion FindRoundRectRegion(const Vec2& p, const detail::RoundRectParts& r)
		{
			//top
			if (p.y < r.circleTL.center.y)
			{
				if (p.x < r.circleTL.center.x)
					return RoundRectRegion::TL;
				else if (p.x > r.circleTR.center.x)
					return RoundRectRegion::TR;
				else
					return RoundRectRegion::T;

			}
			//bottom
			else if (p.y > r.circleBL.center.y)
			{
				if (p.x < r.circleTL.center.x)
					return RoundRectRegion::BL;
				else if (p.x > r.circleTR.center.x)
					return RoundRectRegion::BR;
				else
					return RoundRectRegion::B;
			}
			//center
			else
			{
				if (p.x < r.circleTL.center.x)
					return RoundRectRegion::L;
				else if (p.x > r.circleTR.center.x)
					return RoundRectRegion::R;
				else
					return RoundRectRegion::C;
			}
		}

		// x 軸に平行な線分
		struct LineSegmentParallelToXAxis
		{
			double xLeft, xRight, y;

			constexpr LineSegmentParallelToXAxis(double _xLeft, double xRight, double y) noexcept
				: xLeft(_xLeft)
				, xRight(xRight)
				, y(y) {}
		};

		// y 軸に平行な線分
		struct LineSegmentParallelToYAxis
		{
			double yBottom, yTop, x;

			constexpr LineSegmentParallelToYAxis(double _yBottom, double yTop, double x) noexcept
				: yBottom(_yBottom)
				, yTop(yTop)
				, x(x) {}
		};

		[[nodiscard]]
		static Optional<Vec2> IntersectAt(const LineSegmentParallelToXAxis& a, const Line& b) noexcept
		{
			if (const auto [bMinY, bMaxY] = std::minmax(b.begin.y, b.end.y);
				not InRange(a.y, bMinY, bMaxY))
			{
				return none;
			}
			else if (b.begin.y == b.end.y)
			{
				if (Min(b.begin.x, b.end.x) < a.xLeft || a.xRight < Max(b.begin.x, b.end.x))
				{
					return none;
				}
				else
				{
					return Vec2{ Math::QNaN, Math::QNaN };
				}
			}
			else
			{
				const double x = (Abs(b.end.y - a.y) * b.begin.x + Abs(b.begin.y - a.y) * b.end.x) / Abs(b.begin.y - b.end.y);

				if (InRange(x, a.xLeft, a.xRight))
				{
					return Vec2{ x, a.y };
				}
				else
				{
					return none;
				}
			}
		}

		[[nodiscard]]
		Optional<Vec2> IntersectAt(const LineSegmentParallelToYAxis& a, const Line& b) noexcept
		{
			if (const auto [bMinX, bMaxX] = std::minmax(b.begin.x, b.end.x);
				not InRange(a.x, bMinX, bMaxX))
			{
				return none;
			}
			else if (b.begin.x == b.end.x)
			{
				if (Min(b.begin.y, b.end.y) < a.yBottom || a.yTop < Max(b.begin.y, b.end.y))
				{
					return none;
				}
				else
				{
					return Vec2{ Math::QNaN, Math::QNaN };
				}
			}
			else
			{
				const double y = (Abs(b.end.x - a.x) * b.begin.y + Abs(b.begin.x - a.x) * b.end.y) / Abs(b.begin.x - b.end.x);

				if (InRange(y, a.yBottom, a.yTop))
				{
					return Vec2{ a.x, y };
				}
				else
				{
					return none;
				}
			}
		}

		template <class PointType>
		inline Polygon ConvexHull(const PointType* points, const size_t size)
		{
			if (size < 3)
			{
				return{};
			}

			CWOpenRing result;

			boost::geometry::convex_hull(boost::geometry::model::multi_point<PointType>(points, (points + size)), result);

			return Polygon{ result };
		}

		template <class PointType>
		inline Polygon ConcaveHull(const PointType* points, const size_t size, const double concavity, const double lengthThreshold)
		{
			if (size < 3)
			{
				return{};
			}

			std::vector<std::array<double, 2>> pts;
			{
				pts.reserve(size);

				for (size_t i = 0; i < size; ++i)
				{
					const auto& point = points[i];
					pts.push_back(std::array<double, 2>{ static_cast<double>(point.x), static_cast<double>(point.y) });
				}
			}

			HashTable<Vec2, int> table;
			{
				table.reserve(size);

				for (size_t i = 0; i < size; ++i)
				{
					table.emplace(points[i], static_cast<int32>(i));
				}
			}

			CWOpenRing convexHull;
			{
				boost::geometry::convex_hull(boost::geometry::model::multi_point<PointType>(points, (points + size)), convexHull);
			}

			std::vector<int> hull;
			{
				hull.reserve(convexHull.size());

				for (const auto& point : convexHull)
				{
					hull.push_back(table[point]);
				}
			}

			const auto concave = concaveman<double, 16>(pts, hull, concavity, lengthThreshold);

			Array<Vec2> results(Arg::reserve = concave.size());
			{
				for (const auto& point : concave)
				{
					results.emplace_back(point[0], point[1]);
				}
			}

			return Polygon{ results };
		}

		inline Rect BoundingRect(const Point* points, const size_t size)
		{
			if (size == 0)
			{
				return Rect::Empty();
			}

			const Point* it = points;
			const Point* itEnd = (it + size);

			using value_type = Point::value_type;
			value_type left = it->x;
			value_type top = it->y;
			value_type right = left;
			value_type bottom = top;
			++it;

			while (it != itEnd)
			{
				if (it->x < left)
				{
					left = it->x;
				}
				else if (right < it->x)
				{
					right = it->x;
				}

				if (it->y < top)
				{
					top = it->y;
				}
				else if (bottom < it->y)
				{
					bottom = it->y;
				}

				++it;
			}

			return{ left, top, (right - left), (bottom - top) };
		}

		template <class PointType>
		inline RectF BoundingRectF(const PointType* points, const size_t size)
		{
			if (size == 0)
			{
				return RectF::Empty();
			}

			const PointType* it = points;
			const PointType* itEnd = (it + size);

			using value_type = typename PointType::value_type;
			value_type left = it->x;
			value_type top = it->y;
			value_type right = left;
			value_type bottom = top;
			++it;

			while (it != itEnd)
			{
				if (it->x < left)
				{
					left = it->x;
				}
				else if (right < it->x)
				{
					right = it->x;
				}

				if (it->y < top)
				{
					top = it->y;
				}
				else if (bottom < it->y)
				{
					bottom = it->y;
				}

				++it;
			}

			return{ left, top, (right - left), (bottom - top) };
		}

		static Polygon ToPolygon(const CwOpenPolygon& polygon)
		{
			auto& outer = polygon.outer();

			const auto& inners = polygon.inners();

			Array<Array<Vec2>> holes(inners.size());

			for (size_t i = 0; i < holes.size(); ++i)
			{
				const auto& resultHole = inners[i];

				holes[i].assign(resultHole.begin(), resultHole.end());
			}

			return Polygon{ outer, holes, SkipValidation::Yes };
		}
	}

	namespace detail
	{
		// References:
		// - https://github.com/onihusube/AlgebraicEequationSolver/tree/master/AlgebraicEequationSolver/Include
		// - https://onihusube.hatenablog.com/entry/2019/02/17/115721

		// ax + b = 0
		[[nodiscard]]
		Optional<Array<double>> SolveLinearEquation(double a, double b)
		{
			if (a == 0.0) {
				if (b == 0.0) return Array<double>{};
				return none;
			}
			return Array<double>{ -b / a };
		}

		// ax^2 + bx + c = 0
		[[nodiscard]]
		Optional<Array<double>> SolveQuadraticEquation(double a, double b, double c)
		{
			if (a == 0.0) return SolveLinearEquation(b, c);

			const double d = b * b - 4 * a * c;

			Array<double> res;

			if (c == 0.0)
			{
				res << 0.0;

				if (const auto opt = SolveLinearEquation(a, b))
				{
					for (const double x : *opt)
					{
						res << x;
					}
				}
			}
			else if (std::abs(d) <= 1e-12)
			{
				const double x = -0.5 * b / a;
				res << x;
			}
			else if (-1e12 < d)
			{
				double x1, x2, t;

				if (0.0 < b) t = -b - std::sqrt(Max(0.0, d));
				else t = -b + std::sqrt(Max(0.0, d));

				x1 = 2 * c / t;
				x2 = 0.5 * t / a;

				if (x1 > x2) std::swap(x1, x2);

				res << x1 << x2;
			}

			if (res.empty()) return none;
			return res;
		}

		// ax^4 + bx^2 + c = 0
		[[nodiscard]]
		Optional<Array<double>> SolveBiquadraticEquation(double a, double b, double c)
		{
			Array<double> res;

			if (const auto opt = SolveQuadraticEquation(a, b, c))
			{
				for (const double x : *opt)
				{
					if (-1e-12 < x)
					{
						const double sqrt_x = std::sqrt(Max(0.0, x));
						res << sqrt_x << -sqrt_x;
					}
				}
			}

			res.sort();

			if (res.empty()) return none;
			return res;
		}

		// x^3 + px + q = 0
		[[nodiscard]]
		Optional<Array<double>> SolveCubicEquation(double p, double q)
		{
			Array<double> res;

			if (fabs(q) < 1e-12)
			{ // x^3 + px = 0 <=> x = 0, x^2 = -p
				res << 0;

				if (0 <= -p)
				{
					res << std::sqrt(-p) << -std::sqrt(-p);
				}
			}
			else if (p == 0)
			{ // x^3 + q = 0 <=> x = cbrt(-q)
				res << cbrt(-q);
			}
			else
			{
				const double
					p_third = p / 3,
					q_half = 0.5 * q,
					d = q_half * q_half + p_third * p_third * p_third;

				if (fabs(d) < 1e-12)
				{
					const double tmp = cbrt(q_half);

					res << -2 * tmp << tmp;
				}
				else if (0 < d)
				{
					const double
						d_sqrt = std::sqrt(d),
						u = cbrt(-q_half + d_sqrt),
						v = cbrt(-q_half - d_sqrt);

					res << u + v;
				}
				else
				{
					const double
						r = 2.0 * std::sqrt(-p_third),
						arg = std::arg(std::complex<double>(-q, 2 * std::sqrt(-d))) / 3;

					// 2π/3
					constexpr double TwoThirdPi = 2 * Math::OneThirdPi;

					const double
						x1 = r * cos(arg),
						x2 = r * cos(arg + TwoThirdPi);

					double x3;

					if (x1 != 0 && x2 != 0)
					{
						x3 = -q / (x1 * x2);
					}
					else
					{
						x3 = -x1 - x2;
					}

					res << x1 << x2 << x3;
				}
			}

			res.sort();

			return res;
		}

		// x^3 + ax^2 + bx + c = 0
		[[nodiscard]]
		Optional<Array<double>> SolveCubicEquation(double a, double b, double c)
		{
			Array<double> res;

			// x^3 + ax^2 + bx = 0
			if (fabs(c) < 1e-12)
			{
				res << 0.0;
				if (const auto opt = SolveQuadraticEquation(1, a, b))
				{
					for (const double x : *opt)
					{
						res << x;
					}
				}
			}

			const double
				p = fma(-a / 3, a, b),
				q = fma(fma(a / 13.5, a, -b / 3), a, c);

			if (const auto opt = SolveCubicEquation(p, q))
			{
				//少なくとも1つの実数解を持つ
				for (const double x : *opt)
				{
					res << fma(-a, 1.0 / 3, x);
				}
			}

			res.sort();

			return res;
		}

		// ax^3 + bx^2 + cx + d = 0
		[[nodiscard]]
		Optional<Array<double>> SolveCubicEquation(double a, double b, double c, double d)
		{
			if (a == 0.0) return SolveQuadraticEquation(b, c, d);
			return SolveCubicEquation(b / a, c / a, d / a);
		}

		// x^4 + px^2 + qx + r = 0
		[[nodiscard]]
		Optional<Array<double>> SolveQuarticEquation(double p, double q, double r)
		{
			if (q == 0.0) return SolveBiquadraticEquation(1, p, r);

			Array<double> res;

			if (r == 0.0)
			{
				res << 0.0;

				if (const auto opt = SolveCubicEquation(p, q))
				{
					for (const double x : *opt)
					{
						res << x;
					}
				}
			}
			else
			{
				const double t = SolveCubicEquation(-p, -4 * r, 4 * p * r - q * q).value()[0];

				if (-1e-12 < t - p)
				{
					const double
						m = std::sqrt(Max(0.0, t - p)),
						n = -0.5 * q / m;

					if (const auto opt = SolveQuadraticEquation(1.0, m, fma(0.5, t, n)))
					{
						for (const double x : *opt)
						{
							res << x;
						}
					}

					if (const auto opt = SolveQuadraticEquation(1.0, -m, fma(0.5, t, -n)))
					{
						for (const double x : *opt)
						{
							res << x;
						}
					}
				}
			}

			if (res.empty()) return none;

			res.sort();

			return res;
		}

		// x^4 + ax^3 + bx^2 + cx + d = 0
		[[nodiscard]]
		Optional<Array<double>> SolveQuarticEquation(double a, double b, double c, double d)
		{
			const double
				p = fma(-0.375 * a, a, b),
				q = fma(fma(0.125 * a, a, -0.5 * b), a, c),
				r = fma(fma(fma(-0.01171875 * a, a, 0.0625 * b), a, -0.25 * c), a, d);

			Array<double> res;

			if (const auto opt = SolveQuarticEquation(p, q, r))
			{
				for (const double x : *opt)
				{
					res << fma(-0.25, a, x);
				}
			}

			if (res.empty()) return none;
			return res;
		}

		// ax^4 + bx^3 + cx^2 + dx + e = 0
		[[nodiscard]]
		Optional<Array<double>> SolveQuarticEquation(double a, double b, double c, double d, double e)
		{
			if (a == 0.0) return SolveCubicEquation(b, c, d, e);
			if (b == 0.0 && d == 0.0) {
				return SolveBiquadraticEquation(a, c, e);
			}
			return SolveQuarticEquation(b / a, c / a, d / a, e / a);
		}
	}

	namespace Geometry2D
	{
		bool Intersect(const Point& a, const Bezier2& b)
		{
			return Intersect(Vec2{ a }, b);
		}

		bool Intersect(const Vec2& a, const Bezier2& b)
		{
			// [memo] 1px 未満なら交差と判定
			return (Distance(a, b) < 1.0);
		}

		bool Intersect(const Vec2& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Vec2& a, const Polygon& b) noexcept
		{
			if ((not b)
				|| (not Intersect(a, b.boundingRect())))
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

		bool Intersect(const Vec2& a, const MultiPolygon& b) noexcept
		{
			for (const auto& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Vec2& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(a, Line{ pPoints[i], pPoints[i + 1] }))
				{
					return true;
				}
			}

			return false;
		}

		//
		// `Intersect(const Line& a, const Line& b)` is based on
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

			if (detail::IsZero(rxs))
			{
				if (detail::IsZero(qpxr) && detail::IsZero(qpxs))
				{
					const double qpr = qp.dot(r);
					const double q2pr = (b.end - a.begin).dot(r);
					const double pqs = (a.begin - b.begin).dot(s);
					const double p2qs = (a.end - b.begin).dot(s);

					const double rr = r.dot(r);
					const bool rrIsZero = detail::IsZero(rr);
					const double ss = s.dot(s);
					const bool ssIsZero = detail::IsZero(ss);

					if (rrIsZero && ssIsZero && detail::IsZero(qp.dot(qp)))
					{
						// The two lines are both zero length and in the same position
						return true;
					}

					if (((not rrIsZero) && ((0 <= qpr && qpr <= rr) || (0 <= q2pr && q2pr <= rr)))
						|| ((not ssIsZero) && ((0 <= pqs && pqs <= ss) || (0 <= p2qs && p2qs <= ss))))
					{
						// Two lines are overlapping
						return true;
					}

					// Two lines are collinear but disjoint.
					return false;
				}

				// Two lines are parallel and non-intersecting.
				return false;
			}
			else
			{
				const double t = qpxs / rxs;
				const double u = qpxr / rxs;
				if ((0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0))
				{
					// An intersection was found
					return true;
				}

				// Two line segments are not parallel but do not intersect
				return false;
			}
		}

		bool Intersect(const Line& a, const Bezier2& b)
		{
			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Line& a, const Bezier3& b)
		{
			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Line& a, const Rect& b) noexcept
		{
			if (Intersect(a.begin, b) || Intersect(a.end, b))
			{
				return true;
			}

			const Vec2 tl = b.tl(), tr = b.tr(), br = b.br(), bl = b.bl();

			return Intersect(a, Line{ tl, tr })
				|| Intersect(a, Line{ tr, br })
				|| Intersect(a, Line{ br, bl })
				|| Intersect(a, Line{ bl, tl });
		}

		bool Intersect(const Line& a, const RectF& b) noexcept
		{
			if (Intersect(a.begin, b) || Intersect(a.end, b))
			{
				return true;
			}

			const Vec2 tl = b.tl(), tr = b.tr(), br = b.br(), bl = b.bl();

			return Intersect(a, Line{ tl, tr })
				|| Intersect(a, Line{ tr, br })
				|| Intersect(a, Line{ br, bl })
				|| Intersect(a, Line{ bl, tl });
		}

		bool Intersect(const Line& a, const Circle& b) noexcept
		{
			const Vec2 ab = a.end - a.begin;
			const Vec2 ac = b.center - a.begin;
			const double e = ac.dot(ab);
			const double rr = b.r * b.r;

			if (e <= 0.0)
			{
				return ac.dot(ac) <= rr;
			}

			const double f = ab.dot(ab);

			if (e >= f)
			{
				const Vec2 bc = b.center - a.end;
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
			const Vec2 mDir(dir.x / (rx * rx), dir.y / (ry * ry));
			const Vec2 mDiff(diff.x / (rx * rx), diff.y / (ry * ry));

			const double va = dir.dot(mDir);
			const double vb = dir.dot(mDiff);
			const double vc = diff.dot(mDiff) - 1.0;
			double vd = vb * vb - va * vc;

			const double ERRF = 1e-15;
			const double ZEROepsilon = 10 * Max({ std::abs(va), std::abs(vb), std::abs(vc) }) * ERRF;
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

			return Intersect(a, Line{ b.p0, b.p1 })
				|| Intersect(a, Line{ b.p1, b.p2 })
				|| Intersect(a, Line{ b.p2, b.p0 });
		}

		bool Intersect(const Line& a, const Quad& b) noexcept
		{
			if (Intersect(a.begin, b) || Intersect(a.end, b))
			{
				return true;
			}

			return Intersect(a, Line{ b.p0, b.p1 })
				|| Intersect(a, Line{ b.p1, b.p2 })
				|| Intersect(a, Line{ b.p2, b.p3 })
				|| Intersect(a, Line{ b.p3, b.p0 });
		}

		bool Intersect(const Line& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Line& a, const Polygon& b) noexcept
		{
			return b.intersects(a);
		}

		bool Intersect(const Line& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Line& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Bezier2& a, const Rect& b)
		{
			return Intersect(a, RectF{ b });
		}

		bool Intersect(const Bezier2& a, const RectF& b)
		{
			if (Intersect(a.p0, b)
				|| Intersect(a.p2, b))
			{
				return true;
			}

			const std::array<Line, 4> linesB = { b.top(), b.right(), b.bottom(), b.left() };

			for (const Line& lineB : linesB)
			{
				if (Intersect(a, lineB))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Bezier2& a, const Circle& b)
		{
			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Bezier2& a, const Ellipse& b)
		{
			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Bezier2& a, const Triangle& b)
		{
			if (Intersect(a.p0, b)
				|| Intersect(a.p2, b))
			{
				return true;
			}

			for (size_t i = 0; i < 3; ++i)
			{
				if (Intersect(a, b.side(i)))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Bezier2& a, const Quad& b)
		{
			if (Intersect(a.p0, b)
				|| Intersect(a.p2, b))
			{
				return true;
			}

			for (size_t i = 0; i < 4; ++i)
			{
				if (Intersect(a, b.side(i)))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Bezier3& a, const Circle& b)
		{
			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Bezier3& a, const Ellipse& b)
		{
			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Rect& a, const Ellipse& b) noexcept
		{
			return Intersect(RectF{ a }, b);
		}

		bool Intersect(const Rect& a, const Triangle& b) noexcept
		{
			return Intersect(a.triangle(0), b)
				|| Intersect(a.triangle(1), b);
		}

		bool Intersect(const Rect& a, const Quad& b) noexcept
		{
			return Intersect(a, b.triangle(0))
				|| Intersect(a, b.triangle(1));
		}

		bool Intersect(const Rect& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Rect& a, const Polygon& b) noexcept
		{
			return b.intersects(a);
		}

		bool Intersect(const Rect& a, const MultiPolygon& b) noexcept
		{
			return Intersect(RectF{ a }, b);
		}

		bool Intersect(const RectF& a, const Ellipse& b) noexcept
		{
			RectF rect = a.movedBy(-b.center);

			const double v = b.a / b.b;
			rect.y *= v; rect.h *= v;

			return Intersect(Circle{ b.a }, rect);
		}

		bool Intersect(const RectF& a, const Triangle& b) noexcept
		{
			return Intersect(a.triangle(0), b)
				|| Intersect(a.triangle(1), b);
		}

		bool Intersect(const RectF& a, const Quad& b) noexcept
		{
			return Intersect(a, b.triangle(0))
				|| Intersect(a, b.triangle(1));
		}

		bool Intersect(const RectF& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const RectF& a, const Polygon& b) noexcept
		{
			return b.intersects(a);
		}

		bool Intersect(const RectF& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const RectF& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Circle& a, const Ellipse& b) noexcept
		{
			return IntersectAt(a, b).has_value();
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
			if ((not b)
				|| (not Intersect(a, b.boundingRect())))
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

		bool Intersect(const Circle& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Circle& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Ellipse& a, const Rect& b) noexcept
		{
			return Intersect(RectF{ b }, a);
		}

		bool Intersect(const Ellipse& a, const Ellipse& b)
		{
			if ((not Intersect(a, b.boundingRect()))
				|| (not Intersect(a.boundingRect(), b)))
			{
				return false;
			}

			constexpr std::array<double, 4> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };

			//内包
			for (size_t index = 0; index < 4; ++index)
			{
				if (Intersect(a, Vec2{ b.x + b.a * dx[index], b.y + b.b * dy[index] }))
				{
					return true;
				}

				if (Intersect(b, Vec2{ a.x + a.a * dx[index], a.y + a.b * dy[index] }))
				{
					return true;
				}
			}

			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Ellipse& a, const Triangle& b) noexcept
		{
			Triangle triangle = b.movedBy(-a.center);

			const double v = (a.a / a.b);

			for (size_t i = 0; i < 3; ++i)
			{
				triangle.p(i).y *= v;
			}

			return Intersect(Circle{ a.a }, triangle);
		}

		bool Intersect(const Ellipse& a, const Quad& b) noexcept
		{
			Quad quad = b.movedBy(-a.center);

			const double v = (a.a / a.b);

			for (size_t i = 0; i < 4; ++i)
			{
				quad.p(i).y *= v;
			}

			return Intersect(Circle{ a.a }, quad);
		}

		bool Intersect(const Ellipse& a, const RoundRect& b)
		{
			const std::array<Vec2, 4> add = { Vec2{ a.a, 0 }, Vec2{ 0, a.b }, Vec2{ -a.a, 0}, Vec2{ 0, -a.b } };

			// RoundRect が Ellipse を内包
			for (const Vec2& vec : add)
			{
				if (Intersect(a.center + vec, b))
				{
					return true;
				}
			}

			// Ellipse が RoundRect を内包
			const std::array<Line, 4> lines = detail::DivideToLines(b);

			for (const Line& line : lines)
			{
				if (Intersect(a, line))
				{
					return true;
				}
			}

			const std::array<Circle, 4> circles = detail::DivideToCircles(b);

			for (const Circle& circle : circles)
			{
				if (Intersect(a, circle))
				{
					return true;
				}
			}

			return IntersectAt(a, b).has_value();
		}

		bool Intersect(const Ellipse& a, const Polygon& b) noexcept
		{
			if (not Intersect(a, b.boundingRect()))
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

		bool Intersect(const Ellipse& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Ellipse& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		//
		//	http://marupeke296.com/COL_2D_TriTri.html
		//
		bool Intersect(const Triangle& a, const Triangle& b) noexcept
		{
			constexpr size_t other[3] = { 1, 2, 0 };
			constexpr size_t pindex[4] = { 1, 2, 0, 1 };
			const Triangle* tri[3] = { &a, &b, &a };

			for (int32 t = 0; t < 2; ++t)
			{
				const Triangle& ta = *tri[t];
				const Triangle& tb = *tri[t + 1];

				for (int32 i = 0; i < 3; ++i)
				{
					const Vec2 vec = (ta.p(pindex[i + 1]) - ta.p(pindex[i])).normalized();
					const Vec2 sepVec(vec.y, -vec.x);

					double s1min = sepVec.dot(ta.p(i));
					double s1max = sepVec.dot(ta.p(other[i]));

					if (s1min > s1max)
					{
						std::swap(s1min, s1max);
					}

					double s2min = sepVec.dot(tb.p(0));
					double s2max = sepVec.dot(tb.p(1));

					if (s2min > s2max)
					{
						std::swap(s2min, s2max);
					}

					const double d3 = sepVec.dot(tb.p(2));

					if (d3 < s2min)
					{
						s2min = d3;
					}
					else if (d3 > s2max)
					{
						s2max = d3;
					}

					if ((s2min <= s1min && s1min <= s2max)
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
			return Intersect(a, b.triangle(0))
				|| Intersect(a, b.triangle(1));
		}

		bool Intersect(const Triangle& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Triangle& a, const Polygon& b) noexcept
		{
			if ((not b)
				|| (not Intersect(a, b.boundingRect())))
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

		bool Intersect(const Triangle& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Triangle& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Quad& a, const Quad& b) noexcept
		{
			return Intersect(a.triangle(0), b)
				|| Intersect(a.triangle(1), b);
		}

		bool Intersect(const Quad& a, const RoundRect& b) noexcept
		{
			return detail::RoundRectParts(b).intersects(a);
		}

		bool Intersect(const Quad& a, const Polygon& b) noexcept
		{
			if ((not b)
				|| (not Intersect(a, b.boundingRect())))
			{
				return false;
			}

			const Triangle a0 = a.triangle(0);
			const Triangle a1 = a.triangle(1);

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

		bool Intersect(const Quad& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Quad& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const RoundRect& a, const RoundRect& b) noexcept
		{
			if (not Intersect(a.rect, b.rect))
			{
				return false;
			}

			const detail::RoundRectParts partsA{ a };
			const detail::RoundRectParts partsB{ b };

			return partsA.intersects(partsB.rectA)
				|| partsA.intersects(partsB.rectB)
				|| partsA.intersects(partsB.circleTL)
				|| partsA.intersects(partsB.circleTR)
				|| partsA.intersects(partsB.circleBR)
				|| partsA.intersects(partsB.circleBL);
		}

		bool Intersect(const RoundRect& a, const Polygon& b) noexcept
		{
			if ((not b)
				|| (not Intersect(a, b.boundingRect())))
			{
				return false;
			}

			const detail::RoundRectParts partsA{ a };

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

		bool Intersect(const RoundRect& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (Intersect(a, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const RoundRect& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Polygon& a, const Rect& b) noexcept
		{
			return a.intersects(b);
		}

		bool Intersect(const Polygon& a, const RectF& b) noexcept
		{
			return a.intersects(b);
		}

		bool Intersect(const Polygon& a, const Polygon& b) noexcept
		{
			return a.intersects(b);
		}

		bool Intersect(const Polygon& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygon : b)
			{
				if (a.intersects(polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const Polygon& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const MultiPolygon& a, const MultiPolygon& b) noexcept
		{
			for (const Polygon& polygonA : a)
			{
				for (const Polygon& polygonB : b)
				{
					if (polygonA.intersects(polygonB))
					{
						return true;
					}
				}
			}

			return false;
		}

		bool Intersect(const MultiPolygon& a, const LineString& b) noexcept
		{
			for (const Polygon& polygon : a)
			{
				if (Intersect(b, polygon))
				{
					return true;
				}
			}

			return false;
		}

		bool Intersect(const LineString& a, const Bezier2& b)
		{
			return IntersectAt(b, a).has_value();
		}

		bool Intersect(const LineString& a, const Bezier3& b)
		{
			return IntersectAt(b, a).has_value();
		}

		bool Intersect(const LineString& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					return true;
				}
			}

			return false;
		}

		//////////////////////////////////////////////////
		//
		//	IntersectAt
		//
		//////////////////////////////////////////////////

		//
		// `IntersectAt(const Line& a, const Line& b)` is based on
		// https://www.codeproject.com/Tips/862988/Find-the-Intersection-Point-of-Two-Line-Segments
		//
		// Licenced with the Code Project Open Licence (CPOL)
		// http://www.codeproject.com/info/cpol10.aspx
		//
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Line& b)
		{
			const Vec2 r = a.end - a.begin;
			const Vec2 s = b.end - b.begin;
			const Vec2 qp = b.begin - a.begin;
			const double rxs = r.x * s.y - r.y * s.x;
			const double qpxr = qp.x * r.y - qp.y * r.x;
			const double qpxs = qp.x * s.y - qp.y * s.x;

			if (detail::IsZero(rxs))
			{
				if (detail::IsZero(qpxr) && detail::IsZero(qpxs))
				{
					const double qpr = qp.dot(r);
					const double q2pr = (b.end - a.begin).dot(r);
					const double pqs = (a.begin - b.begin).dot(s);
					const double p2qs = (a.end - b.begin).dot(s);

					const double rr = r.dot(r);
					const bool rrIsZero = detail::IsZero(rr);
					const double ss = s.dot(s);
					const bool ssIsZero = detail::IsZero(ss);

					if (rrIsZero && ssIsZero && detail::IsZero(qp.dot(qp)))
					{
						// The two lines are both zero length and in the same position
						return Array<Vec2>{ a.begin };
					}

					if ((not rrIsZero) && ((0 <= qpr && qpr <= rr) || (0 <= q2pr && q2pr <= rr)))
					{
						// Two lines are overlapping
						if (ssIsZero)
						{
							return Array<Vec2>{ b.begin };
						}
						else
						{
							return Array<Vec2>{};
						}
					}

					if ((not ssIsZero) && ((0 <= pqs && pqs <= ss) || (0 <= p2qs && p2qs <= ss)))
					{
						// Two lines are overlapping
						if (rrIsZero)
						{
							return Array<Vec2>{ a.begin };
						}
						else
						{
							return Array<Vec2>{};
						}
					}

					// Two lines are collinear but disjoint.
					return none;
				}

				// Two lines are parallel and non-intersecting.
				return none;
			}
			else
			{
				const double t = qpxs / rxs;
				const double u = qpxr / rxs;
				if ((0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0))
				{
					// An intersection was found
					return Array<Vec2>{ (a.begin + t * r) };
				}

				// Two line segments are not parallel but do not intersect
				return none;
			}
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Bezier2& b)
		{
			// 計算
			// https://www.desmos.com/calculator/mdvk4fcisq

			Array<Vec2> results;

			// Line a: a1 x + b1 y + c1 = 0
			const double
				a1 = a.begin.y - a.end.y,
				b1 = a.end.x - a.begin.x,
				c1 = a.begin.cross(a.end);

			const double
				a2 = a1 * (b.p0.x - 2 * b.p1.x + b.p2.x) + b1 * (b.p0.y - 2 * b.p1.y + b.p2.y),
				b2 = 2 * (a1 * (b.p1 - b.p0).x + b1 * (b.p1 - b.p0).y),
				c2 = fma(a1, b.p0.x, fma(b1, b.p0.y, c1));

			if (const auto opt = detail::SolveQuadraticEquation(a2, b2, c2))
			{
				for (const double x : *opt)
				{
					if ((-1e-12 < x) && x < (1 + 1e-12))
					{
						const Vec2& intersection = b.getPos(Clamp(x, 0.0, 1.0));

						// 線分 a 上にあるか
						if (Intersect(a, intersection))
						{
							results << intersection;
						}
					}
				}
			}

			if (results)
			{
				return results;
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Bezier3& b)
		{
			Array<Vec2> results;

			const Vec2 p0 = b.p0, p1 = b.p1, p2 = b.p2, p3 = b.p3;

			//Line a: a1 x + b1 y + c1 = 0
			const double
				a1 = a.begin.y - a.end.y,
				b1 = a.end.x - a.begin.x,
				c1 = a.begin.cross(a.end);

			std::array<Vec2, 4> v = { -p0 + 3 * p1 - 3 * p2 + p3, 3 * p0 - 6 * p1 + 3 * p2, -3 * p0 + 3 * p1, p0 };
			std::array<double, 4> t;

			for (size_t i = 0; i < 4; ++i)
			{
				t[i] = (a1 * v[i].x + b1 * v[i].y);
			}

			t[3] += c1;

			if (const auto opt = detail::SolveCubicEquation(t[0], t[1], t[2], t[3]))
			{
				for (const double x : *opt)
				{
					if ((-1e-12 < x)
						&& (x < 1 + 1e-12))
					{
						const Vec2 intersection = b.getPos(Clamp(x, 0.0, 1.0));

						// 線分 a 上にあるか
						if (Intersect(a, intersection))
						{
							results << intersection;
						}
					}
				}
			}

			if (results)
			{
				return results;
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Rect& b)
		{
			return IntersectAt(a, RectF{ b });
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const RectF& b)
		{
			const detail::LineSegmentParallelToXAxis lines_x[2] = { {b.x, (b.x + b.w), b.y}, {b.x, (b.x + b.w), b.y + b.h } };
			const detail::LineSegmentParallelToYAxis lines_y[2] = { {b.y, (b.y + b.h), b.x}, {b.y, (b.y + b.h), b.x + b.w } };

			bool hasIntersection = false;

			Array<Vec2> results;

			for (const auto& lineX : lines_x)
			{
				if (const auto& point = detail::IntersectAt(lineX, a))
				{
					hasIntersection = true;

					if (not point->hasNaN())
					{
						results << *point;
					}
				}
			}

			for (const auto& lineY : lines_y)
			{
				if (const auto& point = detail::IntersectAt(lineY, a))
				{
					hasIntersection = true;

					if (not point->hasNaN())
					{
						results << *point;
					}
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a.begin, b) && Intersect(a.end, b)) // [memo] 完全に含まれている場合空の配列を返す
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse{ b });
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
			const Vec2 mDir(dir.x / (rx * rx), dir.y / (ry * ry));
			const Vec2 mDiff(diff.x / (rx * rx), diff.y / (ry * ry));

			const double va = dir.dot(mDir);
			const double vb = dir.dot(mDiff);
			const double vc = diff.dot(mDiff) - 1.0;
			double vd = vb * vb - va * vc;

			const double ERRF = 1e-15;
			const double ZEROepsilon = 10 * Max({ std::abs(va), std::abs(vb), std::abs(vc) }) * ERRF;
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

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Triangle& b)
		{
			if (Intersect(a.begin, b)
				&& Intersect(a.end, b))
			{
				return Array<Vec2>{};
			}

			bool hasIntersection = false;
			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto point = b.side(i).intersectsAt(a))
				{
					hasIntersection = true;

					if (not point->hasNaN())
					{
						results << *point;
					}
				}
			}

			if (not hasIntersection)
			{
				return none;
			}

			return results;
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Quad& b)
		{
			if (Intersect(a.begin, b)
				&& Intersect(a.end, b))
			{
				return Array<Vec2>{};
			}

			bool hasIntersection = false;
			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto point = b.side(i).intersectsAt(a))
				{
					hasIntersection = true;

					if (not point->hasNaN())
					{
						results << *point;
					}
				}
			}

			if (not hasIntersection)
			{
				return none;
			}

			return results;
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const RoundRect& b)
		{
			if (b.r == 0.0)
			{
				return IntersectAt(a, b.rect);
			}

			if (const auto parts = detail::RoundRectParts(b);
				(parts.intersects(a.begin) && parts.intersects(a.end)))
			{
				return Array<Vec2>{};
			}

			const std::array<Vec2, 4> rectPoints = detail::RectPoints(b.rect);
			const std::array<Vec2, 4> add = { Vec2{ b.r, 0}, Vec2{ 0, b.r}, Vec2{ -b.r, 0 }, Vec2{ 0, -b.r } };

			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t index = 0; index < 4; ++index)
			{
				const Vec2 begin = rectPoints[index];
				const Vec2 end = rectPoints[(index + 1) % 4];
				const Vec2 center = begin + add[index] + add[(index + 1) % 4];

				if (const Line line{ (begin + add[index]), (end + add[(index + 2) % 4]) };
					line.hasLength())
				{
					if (const auto& point = a.intersectsAt(line))
					{
						hasIntersection = true;

						if (not point->hasNaN())
						{
							results << *point;
						}
					}
				}

				// 四分円
				if (const auto& points = IntersectAt(a, Circle{ center, b.r }))
				{
					for (const auto& point : *points)
					{
						if (Intersect(point, RectF{ Arg::center(0.5 * (begin + center)), b.r }))
						{
							hasIntersection = true;

							results << point;
						}
					}
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const Polygon& b)
		{
			if (not Intersect(a, b.boundingRect()))
			{
				return none;
			}

			bool hasIntersection = false;

			Array<Vec2> results;

			for (const Array<Vec2>& inner : b.inners())
			{
				const size_t inner_size = inner.size();

				for (size_t i = 0; i < inner_size; ++i)
				{
					if (const auto& point = a.intersectsAt(Line{ inner[i], inner[(i + 1) % inner_size] }))
					{
						hasIntersection = true;

						if (not point->hasNaN())
						{
							results << *point;
						}
					}
				}
			}

			const Array<Vec2>& outer = b.outer();

			const size_t outer_size = outer.size();

			for (size_t i = 0; i < outer_size; ++i)
			{
				if (const auto& point = a.intersectsAt(Line{ outer[i], outer[(i + 1) % outer_size] }))
				{
					hasIntersection = true;

					if (not point->hasNaN())
					{
						results << *point;
					}
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Line& a, const LineString& b)
		{
			if (not b)
			{
				return none;
			}

			bool hasIntersection = false;
			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto at = a.intersectsAt(Line{ pPoints[i], pPoints[i + 1] }))
				{
					hasIntersection = true;

					if (not at->hasNaN())
					{
						results.push_back(*at);
					}
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse{ b });
		}

		//
		//	https://github.com/thelonious/kld-intersections/blob/development/lib/Intersection.js
		//
		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Ellipse& b)
		{
			if (not Intersect(detail::RoughBoundingRect(a), b.boundingRect()))
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
				ryry * c2.x * c2.x + rxrx * c2.y * c2.y,
				2 * (ryry * c2.x * c1.x + rxrx * c2.y * c1.y),
				ryry * (2 * c2.x * c0.x + c1.x * c1.x) + rxrx * (2 * c2.y * c0.y + c1.y * c1.y) - 2 * (ryry * b.x * c2.x + rxrx * b.y * c2.y),
				2 * (ryry * c1.x * (c0.x - b.x) + rxrx * c1.y * (c0.y - b.y)),
				ryry * (c0.x * c0.x + b.x * b.x) + rxrx * (c0.y * c0.y + b.y * b.y) - 2 * (ryry * b.x * c0.x + rxrx * b.y * c0.y) - rxrx * ryry,
				}).getRoots();

			Array<Vec2> points;

			for (size_t i = 0; i < roots.size(); ++i)
			{
				const double t = roots[i];

				if (0 <= t && t <= 1)
				{
					points.push_back(c2 * (t * t) + (c1 * t + c0));
				}
			}

			if (points)
			{
				return points;
			}
			else if (Intersect(a.p0, b)
				|| Intersect(a.p2, b))
			{
				return Array<Vec2>{};
			}
			else
			{
				return none;
			}
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Rect& b)
		{
			return IntersectAt(a, b.asQuad());
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const RectF& b)
		{
			return IntersectAt(a, b.asQuad());
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Circle& b)
		{
			return IntersectAt(a, Ellipse{ b });
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Ellipse& b)
		{
			if (not Intersect(detail::RoughBoundingRect(a), b.boundingRect()))
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

			const double rxrx = b.a * b.a;
			const double ryry = b.b * b.b;

			Polynomial poly({
				c3.x * c3.x * ryry + c3.y * c3.y * rxrx,
				2 * (c3.x * c2.x * ryry + c3.y * c2.y * rxrx),
				2 * (c3.x * c1.x * ryry + c3.y * c1.y * rxrx) + c2.x * c2.x * ryry + c2.y * c2.y * rxrx,
				2 * c3.x * ryry * (c0.x - b.x) + 2 * c3.y * rxrx * (c0.y - b.y) +
				2 * (c2.x * c1.x * ryry + c2.y * c1.y * rxrx),
				2 * c2.x * ryry * (c0.x - b.x) + 2 * c2.y * rxrx * (c0.y - b.y) +
				c1.x * c1.x * ryry + c1.y * c1.y * rxrx,
				2 * c1.x * ryry * (c0.x - b.x) + 2 * c1.y * rxrx * (c0.y - b.y),
				c0.x * c0.x * ryry - 2 * c0.y * b.y * rxrx - 2 * c0.x * b.x * ryry +
				c0.y * c0.y * rxrx + b.x * b.x * ryry + b.y * b.y * rxrx - rxrx * ryry
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
			else if (Intersect(a.p0, b)
				|| Intersect(a.p3, b))
			{
				return Array<Vec2>{};
			}
			else
			{
				return none;
			}
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Triangle& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a, b.side(i)))
				{
					for (const auto& point : *points)
					{
						results << point;
					}
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Quad& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(b.side(i), a))
				{
					for (const Vec2& point : *points)
					{
						results << point;
					}
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const RoundRect& b)
		{
			if (b.r == 0.0)
			{
				return IntersectAt(a, b.rect);
			}

			Array<Vec2> results;

			const std::array<Vec2, 4> rectPoints = detail::RectPoints(b.rect);
			const std::array<Line, 4> lines = detail::DivideToLines(b);

			for (size_t i = 0; i < 4; ++i)
			{
				const Line& line = lines[i];

				if (const auto& points = IntersectAt(line, a))
				{
					for (const Vec2& point : *points)
					{
						results << point;
					}
				}

				Vec2 center;

				if (i % 2 == 0)
				{
					center = Vec2{ line.begin.x, lines[(i + 3) % 4].end.y };
				}
				else
				{
					center = Vec2{ lines[(i + 3) % 4].end.x, line.begin.y };
				}

				// 四分円
				if (const auto& points = IntersectAt(a, Circle{ center, b.r }))
				{
					for (const Vec2& point : *points)
					{
						if (Intersect(point, RectF{ Arg::center(0.5 * (center + rectPoints[i])), b.r }))
						{
							results << point;
						}
					}
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Polygon& b)
		{
			if (not Intersect(a, b.boundingRect()))
			{
				return none;
			}

			Array<Vec2> results;

			for (const Array<Vec2>& inner : b.inners())
			{
				const size_t inner_size = inner.size();

				for (size_t i = 0; i < inner_size; ++i)
				{
					if (const auto& points = a.intersectsAt(Line{ inner[i], inner[(i + 1) % inner_size] }))
					{
						results.append(*points);
					}
				}
			}

			const Array<Vec2>& outer = b.outer();

			const size_t outer_size = outer.size();

			for (size_t i = 0; i < outer_size; ++i)
			{
				if (const auto& points = a.intersectsAt(Line{ outer[i], outer[(i + 1) % outer_size] }))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const LineString& b)
		{
			if (not b)
			{
				return none;
			}

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto& points = IntersectAt(a, Line{ pPoints[i], pPoints[i + 1] }))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Rect& b)
		{
			return IntersectAt(a, b.asQuad());
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const RectF& b)
		{
			return IntersectAt(a, b.asQuad());
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Triangle& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(b.side(i), a))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Quad& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(b.side(i), a))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const LineString& b)
		{
			if (not b)
			{
				return none;
			}

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto& points = IntersectAt(a, Line{ pPoints[i], pPoints[i + 1] }))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b)
		{
			if (not Intersect(a, b))
			{
				return none;
			}

			Array<Vec2> points;

			const auto add = [&](const Point& vp, int32 vl, const Point& hp, int32 hl)
			{
				if (detail::AxisAlignedLineIntersect(vp, vl, hp, hl))
				{
					points.emplace_back(vp.x, hp.y);
				}
			};

			add(a.tl(), a.h, b.tl(), b.w); // a.left  vs. b.top
			add(a.tl(), a.h, b.bl(), b.w); // a.left  vs. b.bottom
			add(a.tr(), a.h, b.bl(), b.w); // a.right vs. b.bottom
			add(a.tr(), a.h, b.tl(), b.w); // a.right vs. b.top

			add(b.tl(), b.h, a.tl(), a.w); // b.left  vs. a.top
			add(b.tl(), b.h, a.bl(), a.w); // b.left  vs. a.bottom
			add(b.tr(), b.h, a.bl(), a.w); // b.right vs. a.bottom
			add(b.tr(), b.h, a.tl(), a.w); // b.right vs. a.top

			return detail::RemoveDuplication(std::move(points));
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Circle& b)
		{
			return IntersectAt(RectF{ a }, Ellipse{ b });
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Ellipse& b)
		{
			return IntersectAt(RectF{ a }, b);
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Triangle& b)
		{
			return IntersectAt(RectF{ a }, b);
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Quad& b)
		{
			return IntersectAt(RectF{ a }, b);
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const RoundRect& b)
		{
			return IntersectAt(RectF{ a }, b);
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Polygon& b)
		{
			return IntersectAt(RectF{ a }, b);
		}

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const LineString& b)
		{
			return IntersectAt(RectF{ a }, b);
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b)
		{
			if (not Intersect(a, b))
			{
				return none;
			}

			Array<Vec2> points;

			const auto add = [&](const Vec2& vp, double vl, const Vec2& hp, double hl)
			{
				if (detail::AxisAlignedLineIntersect(vp, vl, hp, hl))
				{
					points.emplace_back(vp.x, hp.y);
				}
			};

			add(a.tl(), a.h, b.tl(), b.w); // a.left  vs. b.top
			add(a.tl(), a.h, b.bl(), b.w); // a.left  vs. b.bottom
			add(a.tr(), a.h, b.bl(), b.w); // a.right vs. b.bottom
			add(a.tr(), a.h, b.tl(), b.w); // a.right vs. b.top

			add(b.tl(), b.h, a.tl(), a.w); // b.left  vs. a.top
			add(b.tl(), b.h, a.bl(), a.w); // b.left  vs. a.bottom
			add(b.tr(), b.h, a.bl(), a.w); // b.right vs. a.bottom
			add(b.tr(), b.h, a.tl(), a.w); // b.right vs. a.top

			return detail::RemoveDuplication(std::move(points));
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Circle& b)
		{
			Array<Vec2> results;

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

					results.append(*intersections);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Ellipse& b)
		{
			Array<Vec2> results;

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

					results.append(*intersections);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Triangle& b)
		{
			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a, b.side(i)))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Quad& b)
		{
			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a, b.side(i)))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RoundRect& b)
		{
			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Polygon& b)
		{
			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (b.intersects(a))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const LineString& b)
		{
			if (not b)
			{
				return none;
			}

			bool hasIntersection = false;
			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto at = IntersectAt(Line{ pPoints[i], pPoints[i + 1] }, a))
				{
					hasIntersection = true;

					if (at.has_value())
					{
						results.append(*at);
					}
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		//
		//	https://stackoverflow.com/a/14146166
		//
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Circle& b)
		{
			if (const double d = a.center.distanceFrom(b.center);
				((d + a.r) <= b.r) || ((d + b.r) <= a.r))
			{
				return Array<Vec2>{};
			}

			const Vec2 ac = a.center, bc = b.center;
			const double d = ac.distanceFrom(bc);

			if (((a.r + b.r) < d)
				|| (d < std::abs(a.r - b.r)))
			{
				return none;
			}

			const double tA = (a.r * a.r - b.r * b.r + d * d) / (2 * d);
			const double tH = std::sqrt(a.r * a.r - tA * tA);

			const Vec2 p = (bc - ac) / d * tA + ac;
			const Vec2 o = (bc - ac) / d * tH;

			return { {{ (p.x + o.y), (p.y - o.x) }, { (p.x - o.y), (p.y + o.x) }} };
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Ellipse& b)
		{
			return IntersectAt(Ellipse{ a }, b);
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Triangle& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a, b.side(i)))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Quad& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a, b.side(i)))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const RoundRect& b)
		{
			if (b.r == 0.0)
			{
				return IntersectAt(a, b.rect);
			}

			const std::array<Vec2, 4> rectPoints = detail::RectPoints(b.rect);
			const std::array<Vec2, 4> vs = { Vec2{ b.r, 0 }, Vec2{ 0, b.r }, Vec2{ -b.r, 0 }, Vec2{ 0, -b.r } };

			Array<Vec2> results;

			for (size_t index = 0; index < 4; ++index)
			{
				const Vec2 begin = rectPoints[index];
				const Vec2 end = rectPoints[(index + 1) % 4];
				const Vec2 center = begin + vs[index] + vs[(index + 1) % 4];

				if (const auto& points = IntersectAt(a, Line{ begin + vs[index], end + vs[(index + 2) % 4] }))
				{
					for (const Vec2& point : *points)
					{
						results << point;
					}
				}

				// 四分円
				if (const auto& points = IntersectAt(a, Circle{ center, b.r }))
				{
					for (const Vec2& point : *points)
					{
						if (RectF{ Arg::center(0.5 * (begin + center)), b.r }.contains(point))
						{
							results << point;
						}
					}
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Polygon& b)
		{
			bool hasIntersection = false;
			Array<Vec2> results;

			const Ellipse e{ a };

			const auto& outer = b.outer();
			const size_t num_outer = outer.size();

			for (size_t i = 0; i < num_outer; ++i)
			{
				const Line line(outer[i], outer[(i + 1) % num_outer]);

				if (const auto intersections = IntersectAt(line, e))
				{
					hasIntersection = true;

					results.append(*intersections);
				}
			}

			for (const auto& inner : b.inners())
			{
				const size_t num_inner = inner.size();

				for (size_t i = 0; i < num_inner; ++i)
				{
					const Line line(inner[i], inner[(i + 1) % num_inner]);

					if (const auto intersections = IntersectAt(line, e))
					{
						hasIntersection = true;

						results.append(*intersections);
					}
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const LineString& b)
		{
			if (not a.intersects(b))
			{
				return none;
			}

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto at = IntersectAt(Line{ pPoints[i], pPoints[i + 1] }, a);
					at.has_value())
				{
					results.append(*at);
				}
			}

			return detail::RemoveDuplication(std::move(results));
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Ellipse& b)
		{
			if (a == b)
			{
				return Array<Vec2>{};
			}

			if ((not Intersect(a, b.boundingRect()))
				|| (not Intersect(a.boundingRect(), b)))
			{
				return none;
			}

			Array<Vec2> results;

			const double
				a1 = a.a, a2 = b.a,
				b1 = a.b, b2 = b.b,
				x1 = a.x, x2 = b.x,
				y1 = a.y, y2 = b.y;

			// 交点になるか
			const auto IsIntersection = [a2, b2, x2, y2](const Vec2& v)
			{
				const double t = Math::Square(v.x - x2) / Math::Square(a2) + Math::Square(v.y - y2) / Math::Square(b2);
				return (std::abs(t - 1) < 1e-8);
			};

			const double
				u1 = Math::Square(a1 / a2) - Math::Square(b1 / b2),
				u2 = 2.0 * a1 / Math::Square(a2) * (x1 - x2),
				u3 = Math::Square(x1 - x2) / Math::Square(a2) + Math::Square(y1 - y2) / Math::Square(b2) + Math::Square(b1 / b2) - 1,
				u4 = -2.0 * b1 / Math::Square(b2) * (y1 - y2);

			// t1 x^4 + t2 x^3 + t3 x^2 + t4 x + t5 = 0
			// を満たす x (|x| ≤ 1) が存在すれば
			//それが変換後の交点のx座標
			const double
				t1 = u1 * u1,
				t2 = 2 * u1 * u2,
				t3 = u2 * u2 + u4 * u4 + 2 * u1 * u3,
				t4 = 2 * u2 * u3,
				t5 = u3 * u3 - u4 * u4;

			if (const auto opt = detail::SolveQuarticEquation(t1, t2, t3, t4, t5))
			{
				for (const double x : *opt)
				{
					if (1.0 < std::abs(x))
					{
						continue;
					}

					const double y = std::sqrt(1 - Math::Square(x));

					Vec2 v1{ x, y }, v2{ x, -y };

					v1.x *= a1; v1.y *= b1; v1.moveBy(a.center);
					v2.x *= a1; v2.y *= b1; v2.moveBy(a.center);

					if (IsIntersection(v1))
					{
						results << v1;
					}

					if (IsIntersection(v2))
					{
						results << v2;
					}
				}
			}

			if (results)
			{
				return results;
			}

			if ((Intersect(a, b.top()) && Intersect(a, b.right()) && Intersect(a, b.bottom()) && Intersect(a, b.left()))
				|| (Intersect(b, a.top()) && Intersect(b, a.right()) && Intersect(b, a.bottom()) && Intersect(b, a.left())))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Triangle& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a, b.side(i)))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Quad& b)
		{
			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a, b.side(i)))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RoundRect& b)
		{
			const std::array<Vec2, 4> rectPoints = detail::RectPoints(b.rect);
			const std::array<Vec2, 4> vs = { Vec2{ b.r, 0 }, Vec2{ 0, b.r }, Vec2{ -b.r, 0 }, Vec2{ 0, -b.r } };

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				const Vec2 begin = rectPoints[i];
				const Vec2 end = rectPoints[(i + 1) % 4];
				const Vec2 center = begin + vs[i] + vs[(i + 1) % 4];

				if (const auto& points = IntersectAt(a, Line{ begin + vs[i], end + vs[(i + 2) % 4] }))
				{
					results.append(*points);
				}

				if (const auto& points = IntersectAt(a, Circle{ center, b.r }))
				{
					for (const auto& point : *points)
					{
						if (Intersect(RectF{ Arg::center(0.5 * (begin + center)), b.r }, point))
						{
							results << point;
						}
					}
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			{
				const std::array<Vec2, 4> add = { Vec2{ a.a, 0 }, Vec2{ 0, a.b }, Vec2{ -a.a, 0}, Vec2{ 0, -a.b } };

				// RoundRect が Ellipse を内包
				if (Intersect(a.center + add[0], b)
					&& Intersect(a.center + add[1], b)
					&& Intersect(a.center + add[2], b)
					&& Intersect(a.center + add[3], b))
				{
					return Array<Vec2>{};
				}

				// Ellipse が RoundRect を内包
				const std::array<Line, 4> lines = detail::DivideToLines(b);
				const std::array<Circle, 4> circles = detail::DivideToCircles(b);

				if ((not lines[0].hasLength() || Intersect(a, lines[0]))
					&& (not lines[1].hasLength() || Intersect(a, lines[1]))
					&& (not lines[2].hasLength() || Intersect(a, lines[2]))
					&& (not lines[3].hasLength() || Intersect(a, lines[3]))
					&& Intersect(a, circles[0])
					&& Intersect(a, circles[1])
					&& Intersect(a, circles[2])
					&& Intersect(a, circles[3]))
				{
					return Array<Vec2>{};
				}
			}

			return none;
		}


		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Polygon& b)
		{
			if (not Intersect(a, b.boundingRect()))
			{
				return none;
			}

			Array<Vec2> results;

			for (const Array<Vec2>& inner : b.inners())
			{
				const size_t inner_size = inner.size();

				for (size_t i = 0; i < inner_size; ++i)
				{
					if (const auto& points = a.intersectsAt(Line{ inner[i], inner[(i + 1) % inner_size] }))
					{
						results.append(*points);
					}
				}
			}

			const Array<Vec2>& outer = b.outer();

			const size_t outer_size = outer.size();

			for (size_t i = 0; i < outer_size; ++i)
			{
				if (const auto& points = a.intersectsAt(Line{ outer[i], outer[(i + 1) % outer_size] }))
				{
					results.append(*points);
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const LineString& b)
		{
			if (not a.intersects(b))
			{
				return none;
			}

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto at = IntersectAt(Line{ pPoints[i], pPoints[i + 1] }, a);
					at.has_value())
				{
					results.append(*at);
				}
			}

			return detail::RemoveDuplication(std::move(results));
		}

		Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Triangle& b)
		{
			if ((a.p0 == b.p0 && a.p1 == b.p1 && a.p2 == b.p2)
				|| (a.p0 == b.p1 && a.p1 == b.p2 && a.p2 == b.p0)
				|| (a.p0 == b.p2 && a.p1 == b.p0 && a.p2 == b.p1)) // 同じ三角形
			{
				return Array<Vec2>{};
			}

			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Quad& b)
		{
			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Triangle& a, const RoundRect& b)
		{
			if (b.r == 0)
			{
				return IntersectAt(a, b.rect);
			}

			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Polygon& b)
		{
			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 3; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Triangle& a, const LineString& b)
		{
			if (not a.intersects(b))
			{
				return none;
			}

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto at = IntersectAt(Line{ pPoints[i], pPoints[i + 1] }, a);
					at.has_value())
				{
					results.append(*at);
				}
			}

			return detail::RemoveDuplication(std::move(results));
		}

		Optional<Array<Vec2>> IntersectAt(const Quad& a, const Quad& b)
		{
			if ((a.p0 == b.p0 && a.p1 == b.p1 && a.p2 == b.p2 && a.p3 == b.p3)
				|| (a.p0 == b.p1 && a.p1 == b.p2 && a.p2 == b.p3 && a.p3 == b.p0)
				|| (a.p0 == b.p2 && a.p1 == b.p3 && a.p2 == b.p0 && a.p3 == b.p1)
				|| (a.p0 == b.p3 && a.p1 == b.p0 && a.p2 == b.p1 && a.p3 == b.p2)) // 同じ四角形
			{
				return Array<Vec2>{};
			}

			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Quad& a, const RoundRect& b)
		{
			if (b.r == 0.0)
			{
				return IntersectAt(a, b.rect);
			}

			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Quad& a, const Polygon& b)
		{
			if (not Intersect(a, b.boundingRect()))
			{
				return none;
			}

			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Quad& a, const LineString& b)
		{
			if (not b)
			{
				return none;
			}

			bool hasIntersection = false;

			Array<Vec2> results;

			for (size_t i = 0; i < 4; ++i)
			{
				if (const auto& points = IntersectAt(a.side(i), b))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const RoundRect& b)
		{
			if (b.r == 0.0)
			{
				return IntersectAt(b.rect, a);
			}

			if ((a.rect == b.rect) && (a.r == b.r))
			{
				return Array<Vec2>{};
			}

			const std::array<RoundRect, 2> roundRects = { a,b };

			Array<Vec2> results;

			//頂点
			std::array<std::array<Vec2, 4>, 2> outer, inner;

			std::array<std::array<Vec2, 4>, 2> add;

			//RoundRectから四分円を取り除いたもの
			std::array<std::array<Line, 4>, 2> sides;

			for (size_t index = 0; index < 2; ++index)
			{
				const RoundRect& tmp = roundRects[index];

				add[index] = { Vec2{ tmp.r, 0 }, Vec2{ 0, tmp.r }, Vec2{ -tmp.r, 0 }, Vec2{ 0, -tmp.r } };

				RectF rect = tmp.rect;

				outer[index] = { rect.tl(), rect.tr(), rect.br(), rect.bl() };

				rect = RectF{ Arg::center(tmp.center()), (tmp.w - 2 * tmp.r), (tmp.h - 2 * tmp.r) };

				inner[index] = { rect.tl(), rect.tr(), rect.br(), rect.bl() };

				for (size_t j = 0; j < 4; ++j)
				{
					sides[index][j] = Line{ inner[index][j], inner[index][(j + 1) % 4] }.movedBy(add[index][(j + 3) % 4]);
				}
			}

			//四分円どうし以外の交点
			for (size_t index = 0; index < 2; ++index)
			{
				for (const Line& line : sides[index])
				{
					if (const auto& points = IntersectAt(line, roundRects[(index + 1) % 2]))
					{
						results.append(*points);
					}
				}
			}

			//四分円どうしの交点
			for (size_t indexA = 0; indexA < 4; ++indexA)
			{
				for (size_t indexB = 0; indexB < 4; ++indexB)
				{
					if (const auto& points = IntersectAt(Circle{ inner[0][indexA], a.r }, Circle{ inner[1][indexB], b.r }))
					{
						for (const Vec2& point : *points)
						{
							// 四分円上にあるか
							if (Intersect(point, RectF{ Arg::center(0.5 * (inner[0][indexA] + outer[0][indexA])), a.r })
								&& Intersect(point, RectF{ Arg::center(0.5 * (inner[1][indexB] + outer[1][indexB])), b.r }))
							{
								results << point;
							}
						}
					}
				}
			}

			if (results)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			if (Intersect(a, b))
			{
				return Array<Vec2>{};
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const LineString& b)
		{
			if (not b)
			{
				return none;
			}

			bool hasIntersection = false;

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto& points = IntersectAt(a, Line{ pPoints[i], pPoints[i + 1] }))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const Polygon& a, const LineString& b)
		{
			if (not b)
			{
				return none;
			}

			bool hasIntersection = false;

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto& points = IntersectAt(a, Line{ pPoints[i], pPoints[i + 1] }))
				{
					hasIntersection = true;

					results.append(*points);
				}
			}

			if (hasIntersection)
			{
				return detail::RemoveDuplication(std::move(results));
			}

			return none;
		}

		Optional<Array<Vec2>> IntersectAt(const LineString& a, const LineString& b)
		{
			if (not a.intersects(b))
			{
				return none;
			}

			Array<Vec2> results;
			const Vec2* pPoints = b.data();

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (const auto at = IntersectAt(Line{ pPoints[i], pPoints[i + 1] }, a);
					at.has_value())
				{
					results.append(*at);
				}
			}

			return detail::RemoveDuplication(std::move(results));
		}

		//////////////////////////////////////////////////
		//
		//	Contains
		//
		//////////////////////////////////////////////////

		bool Contains(const Rect& a, const Polygon& b) noexcept
		{
			return Contains(RectF{ a }, b);
		}

		bool Contains(const Rect& a, const LineString& b) noexcept
		{
			return Contains(RectF{ a }, b);
		}

		bool Contains(const RectF& a, const Polygon& b) noexcept
		{
			if (not b
				|| (not b.boundingRect().intersects(a)))
			{
				return false;
			}

			if (Contains(a, b.boundingRect()))
			{
				return true;
			}

			const auto [left, right, top, bottom] = detail::GetLRTB(a);

			for (const auto& point : b.outer())
			{
				if (not detail::Contains(point, left, right, top, bottom))
				{
					return false;
				}
			}

			return true;
		}

		bool Contains(const RectF& a, const LineString& b) noexcept
		{
			const auto [left, right, top, bottom] = detail::GetLRTB(a);

			for (const auto& point : b)
			{
				if (not detail::Contains(point, left, right, top, bottom))
				{
					return false;
				}
			}

			return true;
		}

		bool Contains(const Circle& a, const Ellipse& b) noexcept
		{
			const bool pointsAreInside = Contains(a, b.top())
				&& Contains(a, b.bottom())
				&& Contains(a, b.left())
				&& Contains(a, b.right());

			if (not pointsAreInside)
			{
				return false;
			}

			const auto intersection = IntersectAt(a, b);

			return (intersection.has_value() && intersection->isEmpty());
		}

		bool Contains(const Circle& a, const Polygon& b) noexcept
		{
			if (not b
				|| (not b.boundingRect().intersects(b)))
			{
				return false;
			}

			if (Contains(a, b.boundingRect()))
			{
				return true;
			}

			for (const auto& point : b.outer())
			{
				if (not Contains(a, point))
				{
					return false;
				}
			}

			return true;
		}

		bool Contains(const Circle& a, const LineString& b) noexcept
		{
			if (not b)
			{
				return false;
			}

			for (const auto& point : b)
			{
				if (not Contains(a, point))
				{
					return false;
				}
			}

			return true;
		}

		bool Contains(const Ellipse& a, const Circle& b) noexcept
		{
			const bool pointsAreInside = Contains(a, b.top())
				&& Contains(a, b.bottom())
				&& Contains(a, b.left())
				&& Contains(a, b.right());

			if (not pointsAreInside)
			{
				return false;
			}

			const auto intersection = IntersectAt(a, b);

			return (intersection.has_value() && intersection->isEmpty());
		}

		bool Contains(const Ellipse& a, const Ellipse& b) noexcept
		{
			const bool pointsAreInside = Contains(a, b.top())
				&& Contains(a, b.bottom())
				&& Contains(a, b.left())
				&& Contains(a, b.right());

			if (not pointsAreInside)
			{
				return false;
			}

			const auto intersection = IntersectAt(a, b);

			return (intersection.has_value() && intersection->isEmpty());
		}

		bool Contains(const Polygon& a, const Rect& b)
		{
			return Contains(a, RectF{ b });
		}

		bool Contains(const Polygon& a, const RectF& b)
		{
			const Vec2 vertices[4] = { b.pos, b.pos + Vec2{ b.w, 0 }, b.pos + Vec2{ b.w, b.h }, b.pos + Vec2{ 0, b.h } };

			CwOpenPolygon rect;

			rect.outer().assign(std::begin(vertices), std::end(vertices));

			return boost::geometry::within(rect, a._detail()->getPolygon());
		}

		bool Contains(const Polygon& a, const Circle& b) noexcept
		{
			if ((not a)
				|| (not a.boundingRect().intersects(b)))
			{
				return false;
			}

			if (not Contains(a, b.center))
			{
				return false;
			}

			{
				const auto& outer = a._detail()->getPolygon().outer();
				const size_t num_outer = outer.size();

				for (size_t i = 0; i < num_outer; ++i)
				{
					if (Line{ outer[i], outer[(i + 1) % num_outer] }.intersects(b))
					{
						return false;
					}
				}
			}

			{
				for (const auto& inner : a._detail()->getPolygon().inners())
				{
					const size_t num_inner = inner.size();

					for (size_t i = 0; i < num_inner; ++i)
					{
						if (Line{ inner[i], inner[(i + 1) % num_inner] }.intersects(b))
						{
							return false;
						}
					}
				}
			}

			return true;
		}

		bool Contains(const Polygon& a, const Triangle& b)
		{
			if ((not a)
				|| (not a.boundingRect().intersects(b)))
			{
				return false;
			}

			const Vec2* p = &b.p0;

			return boost::geometry::within(CWOpenRing(p, p + 3), a._detail()->getPolygon());
		}

		bool Contains(const Polygon& a, const Quad& b)
		{
			if ((not a)
				|| (not a.boundingRect().intersects(b)))
			{
				return false;
			}

			const Vec2* p = &b.p0;

			return boost::geometry::within(CWOpenRing(p, p + 4), a._detail()->getPolygon());
		}

		bool Contains(const Polygon& a, const Polygon& b)
		{
			if ((not a)
				|| (not b)
				|| (not a.boundingRect().intersects(b.boundingRect())))
			{
				return false;
			}

			return boost::geometry::within(b._detail()->getPolygon(), a._detail()->getPolygon());
		}

		//////////////////////////////////////////////////
		//
		//	Distance
		//
		//////////////////////////////////////////////////

		double Distance(const Point& a, const Line& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const Bezier2& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const Rect& b)
		{
			return Distance(Vec2{ a }, RectF{ b });
		}

		double Distance(const Point& a, const RectF& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const Circle& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const Triangle& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const Quad& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const RoundRect& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const Polygon& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const MultiPolygon& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Point& a, const LineString& b)
		{
			return Distance(Vec2{ a }, b);
		}

		double Distance(const Vec2& a, const Line& b)
		{
			return boost::geometry::distance(GVec2{ a.x, a.y }, GSegment{ b.begin, b.end });
		}

		double Distance(const Vec2& a, const Bezier2& b)
		{
			double result = Math::Inf;

			const auto [u1, v1] = b.p0 - 2 * b.p1 + b.p2;
			const auto [u2, v2] = -b.p0 + b.p1;
			const auto [u3, v3] = -b.p0 + a;

			const double
				t1 = (u1 * u1 + v1 * v1),
				t2 = 3 * (u1 * u2 + v1 * v2),
				t3 = 2 * (u2 * u2 + v2 * v2) - (u1 * u3 + v1 * v3),
				t4 = -(u2 * u3 + v2 * v3);

			if (const auto opt = detail::SolveCubicEquation(t1, t2, t3, t4))
			{
				for (const double x : *opt)
				{
					if ((-1e-12 < x) && (x < 1 + 1e-12))
					{
						result = Min(result, Distance(a, b.getPos(Clamp(x, 0.0, 1.0))));
					}
				}
			}

			result = Min({ result, Distance(a, b.p0), Distance(a, b.p2) });

			return result;
		}

		double Distance(const Vec2& a, const Rect& b)
		{
			return Distance(a, RectF{ b });
		}

		double Distance(const Vec2& a, const RectF& b)
		{
			return boost::geometry::distance(GVec2{ a.x, a.y }, GBox{ b.pos, b.br() });
		}

		double Distance(const Vec2& a, const Triangle& b)
		{
			return boost::geometry::distance(GVec2{ a.x, a.y }, detail::MakeTriangle(b));
		}

		double Distance(const Vec2& a, const Quad& b)
		{
			return boost::geometry::distance(GVec2{ a.x, a.y }, detail::MakeQuad(b));
		}

		double Distance(const Vec2& a, const RoundRect& b)
		{
			using detail::RoundRectRegion;

			switch (const auto p = detail::RoundRectParts(b);
			detail::FindRoundRectRegion(a, p))
			{
			case RoundRectRegion::TL:
				return Distance(a, p.circleTL);
			case RoundRectRegion::T:
			case RoundRectRegion::B:
				return Distance(a, p.rectB);
			case RoundRectRegion::TR:
				return Distance(a, p.circleTR);
			case RoundRectRegion::L:
			case RoundRectRegion::R:
				return Distance(a, p.rectA);
			case RoundRectRegion::C:
				return 0.0;
			case RoundRectRegion::BL:
				return Distance(a, p.circleBL);
			case RoundRectRegion::BR:
			default:
				return Distance(a, p.circleBR);
			}
		}

		double Distance(const Vec2& a, const Polygon& b)
		{
			return boost::geometry::distance(GVec2{ a.x, a.y }, b._detail()->getPolygon());
		}

		double Distance(const Vec2& a, const MultiPolygon& b)
		{
			const GVec2 v{ a.x, a.y };
			double res = Math::Inf;

			for (const Polygon& polygon : b)
			{
				res = Min(res, boost::geometry::distance(v, polygon._detail()->getPolygon()));

				if (res == 0.0)
				{
					return 0.0;
				}
			}

			return res;
		}

		double Distance(const Vec2& a, const LineString& b)
		{
			return boost::geometry::distance(GVec2{ a.x, a.y }, detail::MakeLineString(b));
		}

		double Distance(const Line& a, const Line& b)
		{
			return boost::geometry::distance(GSegment{ a.begin, a.end }, GSegment{ b.begin, b.end });
		}

		double Distance(const Line& a, const Bezier2& b)
		{
			if (Intersect(a, b))
			{
				return 0.0;
			}

			double result = Math::Inf;

			const auto [x1, y1] = b.p0;
			const auto [x2, y2] = b.p1;
			const auto [x3, y3] = b.p2;
			const auto [u1, v1] = a.end - a.begin;

			const double
				t1 = u1 * (y1 - 2 * y2 + y3) - v1 * (x1 - 2 * x2 + x3),
				t2 = u1 * (-y1 + y2) - v1 * (-x1 + x2);

			if (const auto opt = detail::SolveLinearEquation(t1, t2))
			{
				for (const double x : *opt)
				{
					if ((-1e-12 < x) && (x < 1 + 1e-12))
					{
						result = Min(result, Distance(a, b.getPos(Clamp(x, 0.0, 1.0))));
					}
				}
			}

			result = Min({ result, Distance(a.begin, b), Distance(a.end, b), Distance(a, b.p0), Distance(a, b.p2) });

			return result;
		}

		double Distance(const Line& a, const Rect& b)
		{
			return Distance(a, RectF{ b });
		}

		double Distance(const Line& a, const RectF& b)
		{
			return boost::geometry::distance(GSegment{ a.begin, a.end }, GBox{ b.pos, b.br() });
		}

		double Distance(const Line& a, const Circle& b)
		{
			return Max(0.0, Distance(b.center, a) - b.r);
		}

		double Distance(const Line& a, const Triangle& b)
		{
			return boost::geometry::distance(GSegment{ a.begin, a.end }, detail::MakeTriangle(b));
		}

		double Distance(const Line& a, const Quad& b)
		{
			return boost::geometry::distance(GSegment{ a.begin, a.end }, detail::MakeQuad(b));
		}

		double Distance(const Line& a, const RoundRect& b)
		{
			if (Intersect(a, b))
			{
				return 0.0;
			}

			double results = Math::Inf;

			const std::array<Line, 4> lines = detail::DivideToLines(b);

			for (size_t i = 0; i < 4; ++i)
			{
				const Line& line = lines[i];

				results = Min(results, Distance(a, line));

				Vec2 center;

				if (i % 2 == 0)
				{
					center = Vec2{ line.begin.x, lines[(i + 3) % 4].end.y };
				}
				else
				{
					center = Vec2{ lines[(i + 3) % 4].end.x, line.begin.y };
				}

				results = Min(results, Distance(a, Circle{ center, b.r }));
			}

			return results;
		}

		double Distance(const Line& a, const Polygon& b)
		{
			return boost::geometry::distance(GSegment{ a.begin, a.end }, b._detail()->getPolygon());
		}

		double Distance(const Line& a, const MultiPolygon& b)
		{
			const GSegment s{ a.begin, a.end };
			double res = Math::Inf;

			for (const Polygon& polygon : b)
			{
				res = Min(res, boost::geometry::distance(s, polygon._detail()->getPolygon()));

				if (res == 0.0)
				{
					return 0.0;
				}
			}

			return res;
		}

		double Distance(const Line& a, const LineString& b)
		{
			return boost::geometry::distance(GSegment{ a.begin, a.end }, detail::MakeLineString(b));
		}

		double Distance(const Bezier2& a, const Rect& b)
		{
			return Distance(a, b.asQuad());
		}

		double Distance(const Bezier2& a, const RectF& b)
		{
			return Distance(a, b.asQuad());
		}

		double Distance(const Bezier2& a, const Triangle& b)
		{
			if (Intersect(a, b))
			{
				return 0.0;
			}

			double res = Math::Inf;

			for (size_t i = 0; i < 3; ++i)
			{
				res = Min(res, Distance(a, b.side(i)));
			}

			return res;
		}

		double Distance(const Bezier2& a, const Quad& b)
		{
			if (Intersect(a, b))
			{
				return 0.0;
			}

			double res = Math::Inf;

			for (size_t i = 0; i < 4; ++i)
			{
				res = Min(res, Distance(a, b.side(i)));
			}

			return res;
		}

		double Distance(const Rect& a, const Bezier2& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const Rect& b)
		{
			return Distance(RectF{ a }, RectF{ b });
		}

		double Distance(const Rect& a, const RectF& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const Circle& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const Triangle& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const Quad& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const RoundRect& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const Polygon& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const MultiPolygon& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const Rect& a, const LineString& b)
		{
			return Distance(RectF{ a }, b);
		}

		double Distance(const RectF& a, const Rect& b)
		{
			return Distance(a, RectF{ b });
		}

		double Distance(const RectF& a, const RectF& b)
		{
			return boost::geometry::distance(GBox{ a.pos, a.br() }, GBox{ b.pos, b.br() });
		}

		double Distance(const RectF& a, const Circle& b)
		{
			return Max(0.0, boost::geometry::distance(GBox{ a.pos, a.br() }, GVec2{ a.x, a.y }) - b.r);
		}

		double Distance(const RectF& a, const Triangle& b)
		{
			return boost::geometry::distance(GBox{ a.pos, a.br() }, detail::MakeTriangle(b));
		}

		double Distance(const RectF& a, const Quad& b)
		{
			return boost::geometry::distance(GBox{ a.pos, a.br() }, detail::MakeQuad(b));
		}

		double Distance(const RectF& a, const RoundRect& b)
		{
			if (Intersect(a, b))
			{
				return 0.0;
			}

			double result = Math::Inf;

			for (size_t i = 0; i < 4; ++i)
			{
				result = Min(result, Distance(a.side(i), b));
			}

			return result;
		}

		double Distance(const RectF& a, const Polygon& b)
		{
			return boost::geometry::distance(GBox{ a.pos, a.br() }, b._detail()->getPolygon());
		}

		double Distance(const RectF& a, const MultiPolygon& b)
		{
			const GBox box{ a.pos, a.br() };
			double res = Math::Inf;

			for (const Polygon& polygon : b)
			{
				res = Min(res, boost::geometry::distance(box, polygon._detail()->getPolygon()));

				if (res == 0.0)
				{
					return 0.0;
				}
			}

			return res;
		}

		double Distance(const RectF& a, const LineString& b)
		{
			return boost::geometry::distance(GBox{ a.pos, a.br() }, detail::MakeLineString(b));
		}

		double Distance(const Circle& a, const Triangle& b)
		{
			return Max(0.0, Distance(a.center, b) - a.r);
		}

		double Distance(const Circle& a, const Quad& b)
		{
			return Max(0.0, Distance(a.center, b) - a.r);
		}

		double Distance(const Circle& a, const RoundRect& b)
		{
			return Max(0.0, Distance(a.center, b) - a.r);
		}

		double Distance(const Circle& a, const Polygon& b)
		{
			return Max(0.0, Distance(a.center, b) - a.r);
		}

		double Distance(const Circle& a, const LineString& b)
		{
			return Max(0.0, Distance(a.center, b) - a.r);
		}

		double Distance(const Triangle& a, const Triangle& b)
		{
			return boost::geometry::distance(detail::MakeTriangle(a), detail::MakeTriangle(b));
		}

		double Distance(const Triangle& a, const Quad& b)
		{
			return boost::geometry::distance(detail::MakeTriangle(a), detail::MakeQuad(b));
		}

		double Distance(const Triangle& a, const Polygon& b)
		{
			return boost::geometry::distance(detail::MakeTriangle(a), b._detail()->getPolygon());
		}

		double Distance(const Triangle& a, const LineString& b)
		{
			return boost::geometry::distance(detail::MakeTriangle(a), detail::MakeLineString(b));
		}

		double Distance(const Quad& a, const Quad& b)
		{
			return boost::geometry::distance(detail::MakeQuad(a), detail::MakeQuad(b));
		}

		double Distance(const Quad& a, const Polygon& b)
		{
			return boost::geometry::distance(detail::MakeQuad(a), b._detail()->getPolygon());
		}

		double Distance(const Quad& a, const LineString& b)
		{
			return boost::geometry::distance(detail::MakeQuad(a), detail::MakeLineString(b));
		}

		double Distance(const Polygon& a, const Polygon& b)
		{
			return boost::geometry::distance(a._detail()->getPolygon(), b._detail()->getPolygon());
		}

		double Distance(const Polygon& a, const LineString& b)
		{
			return boost::geometry::distance(a._detail()->getPolygon(), detail::MakeLineString(b));
		}

		double Distance(const LineString& a, const LineString& b)
		{
			return boost::geometry::distance(detail::MakeLineString(a), detail::MakeLineString(b));
		}

		//////////////////////////////////////////////////
		//
		//	Center
		//
		//////////////////////////////////////////////////

		Vec2 Center(const Bezier2& a)
		{
			if (Distance(a.p0, a.p2) < 1e-5)
			{
				return 0.5 * (a.p0 + a.p1);
			}
			if (Distance(a.p1, a.p2) < 1e-5)
			{
				return 0.5 * (a.p0 + a.p2);
			}

			const auto [x1, y1] = a.p0;
			const auto [x2, y2] = a.p1;
			const auto [x3, y3] = a.p2;

			const double
				t1 = x1 - 2 * x2 + x3,
				t2 = y1 - 2 * y2 + y3,
				t3 = -x1 + x2,
				t4 = -y1 + y2,

				a1 = Math::Square(t1) + Math::Square(t2),
				b1 = 2 * (t1 * t3 + t2 * t4),
				c1 = Math::Square(t3) + Math::Square(t4),

				a1_sqrt = std::sqrt(a1),

				u1 = 0.5 * b1 / a1,
				u2 = -Math::Square(u1) + c1 / a1;

			auto F = [a1_sqrt, u2](double x)
			{
				const double t = std::sqrt(std::fma(x, x, u2));
				return a1_sqrt * (x * t + u2 * log(x + t));
			};

			const double c2 = F(u1);

			// 0 ≤ t ≤ x の範囲での a の長さ
			auto L = [F, c2, u1](double x)
			{
				return F(u1 + x) - c2;
			};

			// d/dx L(x)
			auto dL = [a1_sqrt, u1, u2](double x)
			{
				return 2 * a1_sqrt * fma(u1 + x, u1 + x, u2);
			};

			// L(x) = d となる x を求める
			const double d = 0.5 * L(1.0);

			//ニュートン法
			auto N = [L, dL, d](double x)
			{
				return std::fma(d - L(x), 1.0 / dL(x), x);
			};

			constexpr int32 limit = 40;
			int32 count = 0;

			double t = 0.5;
			while ((std::abs(L(t) - d) > 1e-8) && (count < limit))
			{
				t = N(t);

				++count;
			}

			return a.getPos(t);
		}

		//////////////////////////////////////////////////
		//
		//	IsClockwise
		//
		//////////////////////////////////////////////////

		bool IsClockwise(const Array<Point>& points) noexcept
		{
			return detail::IsClockwise(points.data(), points.size());
		}

		bool IsClockwise(const Point* points, const size_t size) noexcept
		{
			return detail::IsClockwise(points, size);
		}

		bool IsClockwise(const Array<Float2>& points) noexcept
		{
			return detail::IsClockwise(points.data(), points.size());
		}

		bool IsClockwise(const Float2* points, const size_t size) noexcept
		{
			return detail::IsClockwise(points, size);
		}

		bool IsClockwise(const Array<Vec2>& points) noexcept
		{
			return detail::IsClockwise(points.data(), points.size());
		}

		bool IsClockwise(const Vec2* points, const size_t size) noexcept
		{
			return detail::IsClockwise(points, size);
		}

		//////////////////////////////////////////////////
		//
		//	BoundingRect
		//
		//////////////////////////////////////////////////

		RectF BoundingRect(const Array<Point>& points) noexcept
		{
			return detail::BoundingRect(points.data(), points.size());
		}

		RectF BoundingRect(const Point* points, const size_t size) noexcept
		{
			return detail::BoundingRect(points, size);
		}

		RectF BoundingRect(const Array<Float2>& points) noexcept
		{
			return detail::BoundingRectF(points.data(), points.size());
		}

		RectF BoundingRect(const Float2* points, const size_t size) noexcept
		{
			return detail::BoundingRectF(points, size);
		}

		RectF BoundingRect(const Array<Vec2>& points) noexcept
		{
			return detail::BoundingRectF(points.data(), points.size());
		}

		RectF BoundingRect(const Vec2* points, const size_t size) noexcept
		{
			return detail::BoundingRectF(points, size);
		}

		//////////////////////////////////////////////////
		//
		//	ConvexHull
		//
		//////////////////////////////////////////////////

		Polygon ConvexHull(const Array<Point>& points)
		{
			return detail::ConvexHull(points.data(), points.size());
		}

		Polygon ConvexHull(const Point* points, const size_t size)
		{
			return detail::ConvexHull(points, size);
		}

		Polygon ConvexHull(const Array<Float2>& points)
		{
			return detail::ConvexHull(points.data(), points.size());
		}

		Polygon ConvexHull(const Float2* points, const size_t size)
		{
			return detail::ConvexHull(points, size);
		}

		Polygon ConvexHull(const Array<Vec2>& points)
		{
			return detail::ConvexHull(points.data(), points.size());
		}

		Polygon ConvexHull(const Vec2* points, const size_t size)
		{
			return detail::ConvexHull(points, size);
		}

		//////////////////////////////////////////////////
		//
		//	ConcaveHull
		//
		//////////////////////////////////////////////////

		Polygon ConcaveHull(const Array<Point>& points, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points.data(), points.size(), concavity, lengthThreshold);
		}

		Polygon ConcaveHull(const Point* points, const size_t size, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points, size, concavity, lengthThreshold);
		}

		Polygon ConcaveHull(const Array<Float2>& points, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points.data(), points.size(), concavity, lengthThreshold);
		}

		Polygon ConcaveHull(const Float2* points, const size_t size, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points, size, concavity, lengthThreshold);
		}

		Polygon ConcaveHull(const Array<Vec2>& points, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points.data(), points.size(), concavity, lengthThreshold);
		}

		Polygon ConcaveHull(const Vec2* points, const size_t size, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points, size, concavity, lengthThreshold);
		}

		//////////////////////////////////////////////////
		//
		//	Subtract
		//
		//////////////////////////////////////////////////

		Array<Polygon> Subtract(const RectF& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::difference(GBox{ a.pos, a.br() }, b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		Array<Polygon> Subtract(const Polygon& a, const RectF& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::difference(a._detail()->getPolygon(), GBox{ b.pos, b.br() }, results);

			return results.map(detail::ToPolygon);
		}

		Array<Polygon> Subtract(const Polygon& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::difference(a._detail()->getPolygon(), b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		//////////////////////////////////////////////////
		//
		//	And
		//
		//////////////////////////////////////////////////

		Array<Polygon> And(const RectF& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::intersection(GBox{ a.pos, a.br() }, b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		Array<Polygon> And(const Polygon& a, const RectF& b)
		{
			return And(b, a);
		}

		Array<Polygon> And(const Polygon& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::intersection(a._detail()->getPolygon(), b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		//////////////////////////////////////////////////
		//
		//	Or
		//
		//////////////////////////////////////////////////

		Array<Polygon> Or(const RectF& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::union_(GBox{ a.pos, a.br() }, b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		Array<Polygon> Or(const Polygon& a, const RectF& b)
		{
			return Or(b, a);
		}

		Array<Polygon> Or(const Polygon& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::union_(a._detail()->getPolygon(), b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		MultiPolygon Or(const MultiPolygon& a, const Polygon& b)
		{
			boost::geometry::model::multi_polygon<CwOpenPolygon> polygons;

			for (const auto& ap : a)
			{
				polygons.push_back(ap._detail()->getPolygon());
			}

			boost::geometry::model::multi_polygon<CwOpenPolygon> unitedPolygons;
			boost::geometry::union_(polygons, b._detail()->getPolygon(), unitedPolygons);

			MultiPolygon results;

			for (const auto& unitedPolygon : unitedPolygons)
			{
				Array<Array<Vec2>> retHoles;

				for (const auto& hole : unitedPolygon.inners())
				{
					retHoles.emplace_back(hole.begin(), hole.end());
				}

				if (Polygon::Validate(unitedPolygon.outer(), retHoles) == PolygonFailureType::OK)
				{
					results.emplace_back(unitedPolygon.outer(), retHoles);
				}
			}

			return results;
		}

		//////////////////////////////////////////////////
		//
		//	Xor
		//
		//////////////////////////////////////////////////

		Array<Polygon> Xor(const RectF& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::sym_difference(GBox{ a.pos, a.br() }, b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		Array<Polygon> Xor(const Polygon& a, const RectF& b)
		{
			return Xor(b, a);
		}

		Array<Polygon> Xor(const Polygon& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			boost::geometry::sym_difference(a._detail()->getPolygon(), b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		//////////////////////////////////////////////////
		//
		//	FrechetDistance
		//
		//////////////////////////////////////////////////

		double FrechetDistance(const LineString& a, const LineString& b)
		{
			if (a.isEmpty() || b.isEmpty())
			{
				return Inf<double>;
			}

			return boost::geometry::discrete_frechet_distance(GLineString(a.begin(), a.end()), GLineString(b.begin(), b.end()));
		}

		//////////////////////////////////////////////////
		//
		//	HausdorffDistance
		//
		//////////////////////////////////////////////////

		double HausdorffDistance(const LineString& a, const LineString& b)
		{
			if (a.isEmpty() || b.isEmpty())
			{
				return Inf<double>;
			}

			return boost::geometry::discrete_hausdorff_distance(GLineString(a.begin(), a.end()), GLineString(b.begin(), b.end()));
		}

		//////////////////////////////////////////////////
		//
		//	ComposePolygons
		//
		//////////////////////////////////////////////////

		MultiPolygon ComposePolygons(const Array<LineString>& rings)
		{
			//-----------------------------------------------
			//	Authors (OpenSiv3D challenge #10 participants)
			//	- Ebishu
			//	- fal_rnd
			//-----------------------------------------------

			MultiPolygon results, outers;
			Array<LineString> holes;

			for (const auto& ring : rings)
			{
				if (Geometry2D::IsClockwise(ring))
				{
					const Array<Polygon> polygons = Polygon::Correct(ring);
					outers.append(polygons);
					results.append(polygons);
				}
				else
				{
					holes << ring;
				}
			}

			const size_t outers_size = outers.size();

			for (const LineString& hole : holes)
			{
				size_t w = (size_t)-1;
				double dist = Inf<double>;

				const Vec2& point = hole.front();

				for (size_t i = 0; i < outers_size; ++i)
				{
					if (Geometry2D::Contains(outers[i], point))
					{
						const Array<Vec2>& outer = outers[i].outer();

						double d = Inf<double>;

						for (size_t j = 0, outer_size = outer.size(); j < outer_size; ++j)
						{
							d = Min(d, Geometry2D::Distance(point, Line{ outer[j], outer[(j + 1) % outer_size] }));
						}

						if (d < dist)
						{
							dist = d;
							w = i;
						}
					}
				}

				if (w != (size_t)-1)
				{
					results[w].addHole(hole);
				}
			}

			return results;
		}
	}
}

namespace s3d
{
	RectF Bezier3::boundingRect() const noexcept
	{
		const auto [a1, a2] = -p0 + 3 * p1 - 3 * p2 + p3;
		const auto [b1, b2] = 3 * p0 - 6 * p1 + 3 * p2;
		const auto [c1, c2] = -3 * p0 + 3 * p1;
		const auto [d1, d2] = p0;

		double minX = Min(p0.x, p3.x);
		double maxX = Max(p0.x, p3.x);

		if (const auto opt = detail::SolveQuadraticEquation(3 * a1, 2 * b1, c1))
		{
			for (const double t : *opt)
			{
				if (InRange(t, 0.0, 1.0))
				{
					// k = a1 t^3 + b1 t^2 + c1 t + d1
					const double k = std::fma(std::fma(std::fma(a1, t, b1), t, c1), t, d1);

					minX = Min(minX, k);
					maxX = Max(maxX, k);
				}
			}
		}

		double minY = Min(p0.y, p3.y);
		double maxY = Max(p0.y, p3.y);

		if (const auto opt = detail::SolveQuadraticEquation(3 * a2, 2 * b2, c2))
		{
			for (const double t : *opt)
			{
				if (InRange(t, 0.0, 1.0))
				{
					// k = a2 t^3 + b2 t^2 + c2 t + d2
					const double k = std::fma(std::fma(std::fma(a2, t, b2), t, c2), t, d2);

					minY = Min(minY, k);
					maxY = Max(maxY, k);
				}
			}
		}

		return { minX, minY, (maxX - minX), (maxY - minY) };
	}
}