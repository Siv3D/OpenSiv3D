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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/MultiPolygon.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Polygon/PolygonDetail.hpp>

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4819)
# include <boost/geometry/strategies/strategies.hpp>
# include <boost/geometry/algorithms/convex_hull.hpp>
# include <boost/geometry/algorithms/difference.hpp>
# include <boost/geometry/algorithms/intersection.hpp>
# include <boost/geometry/algorithms/union.hpp>
# include <boost/geometry/algorithms/sym_difference.hpp>
# include <boost/geometry/algorithms/discrete_frechet_distance.hpp>
# include <boost/geometry/algorithms/discrete_hausdorff_distance.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
# include <ThirdParty/concaveman-cpp/concaveman.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
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
		inline Polygon ConcaveHull(const Array<PointType>& points, const double concavity, const double lengthThreshold)
		{
			if (points.size() < 3)
			{
				return{};
			}

			std::vector<std::array<double, 2>> pts;
			{
				pts.reserve(points.size());

				for (const auto& point : points)
				{
					pts.push_back(std::array<double, 2>{ static_cast<double>(point.x), static_cast<double>(point.y) });
				}
			}

			HashTable<Vec2, int> table;
			{
				table.reserve(points.size());

				for (int i = 0; const auto & point : points)
				{
					table.emplace(point, i++);
				}
			}

			CWOpenRing convexHull;
			{
				const PointType* pPoints = points.data();
				const size_t size = points.size();
				boost::geometry::convex_hull(boost::geometry::model::multi_point<PointType>(pPoints, (pPoints + size)), convexHull);
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
				return Rect{ 0 };
			}

			const Point* it		= points;
			const Point* itEnd	= (it + size);

			using value_type	= Point::value_type;
			value_type left		= it->x;
			value_type top		= it->y;
			value_type right	= left;
			value_type bottom	= top;
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
				return RectF{ 0 };
			}

			const PointType* it		= points;
			const PointType* itEnd	= (it + size);

			using value_type	= typename PointType::value_type;
			value_type left		= it->x;
			value_type top		= it->y;
			value_type right	= left;
			value_type bottom	= top;
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

	namespace Geometry2D
	{
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

			for (size_t i = 0; i < (b.size() - 1); ++i)
			{
				if (Intersect(a, Line{ b[i], b[i + 1] }))
				{
					return true;
				}
			}

			return false;
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
			return detail::ConcaveHull(points, concavity, lengthThreshold);
		}

		Polygon ConcaveHull(const Array<Float2>& points, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points, concavity, lengthThreshold);
		}

		Polygon ConcaveHull(const Array<Vec2>& points, const double concavity, const double lengthThreshold)
		{
			return detail::ConcaveHull(points, concavity, lengthThreshold);
		}

		//////////////////////////////////////////////////
		//
		//	Subtract
		//
		//////////////////////////////////////////////////

		Array<Polygon> Subtract(const RectF& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			const boost::geometry::model::box<Vec2> box{ a.pos, a.br() };

			boost::geometry::difference(box, b._detail()->getPolygon(), results);

			return results.map(detail::ToPolygon);
		}

		Array<Polygon> Subtract(const Polygon& a, const RectF& b)
		{
			Array<CwOpenPolygon> results;

			const boost::geometry::model::box<Vec2> box{ b.pos, b.br() };

			boost::geometry::difference(a._detail()->getPolygon(), box, results);

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

			const boost::geometry::model::box<Vec2> box{ a.pos, a.br() };

			boost::geometry::intersection(box, b._detail()->getPolygon(), results);

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

			const boost::geometry::model::box<Vec2> box{ a.pos, a.br() };

			boost::geometry::union_(box, b._detail()->getPolygon(), results);

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

		//////////////////////////////////////////////////
		//
		//	Xor
		//
		//////////////////////////////////////////////////

		Array<Polygon> Xor(const RectF& a, const Polygon& b)
		{
			Array<CwOpenPolygon> results;

			const boost::geometry::model::box<Vec2> box{ a.pos, a.br() };

			boost::geometry::sym_difference(box, b._detail()->getPolygon(), results);

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
	}
}
