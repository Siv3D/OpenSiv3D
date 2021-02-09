
# pragma once
# include <Siv3D/Common.hpp>

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4819)
# include <boost/geometry.hpp>
# include <boost/geometry/geometries/point.hpp>
# include <boost/geometry/geometries/box.hpp>
# include <boost/geometry/index/rtree.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

# include "../agg/agg_curves.h"

namespace bg = boost::geometry;
namespace bgm = bg::model;
namespace bgi = bg::index;
typedef bgm::point<double, 2, bg::cs::cartesian> Point;
typedef bgm::box<Point> Box;
typedef std::vector<Point> Points;
typedef std::vector<Points> Rings;
typedef std::pair<Point, Point> SegmentPair;
typedef std::pair<Box, SegmentPair> SegmentValue;
typedef bgi::rtree<SegmentValue, bgi::rstar<16>> Tree;

namespace sdf_glyph_foundry
{
	struct User {
		Rings rings;
		Points ring;
	};

	void CloseRing(Points &ring)
	{
		const Point &first = ring.front();
		const Point &last = ring.back();

		if (first.get<0>() != last.get<0>() ||
			first.get<1>() != last.get<1>())
		{
			ring.push_back(first);
		}
	}

	int MoveTo(const FT_Vector *to, void *ptr)
	{
		User *user = (User*)ptr;
		if (!user->ring.empty()) {
			CloseRing(user->ring);
			user->rings.push_back(user->ring);
			user->ring.clear();
		}
		user->ring.emplace_back(float(to->x) / 64.0, float(to->y) / 64.0);
		return 0;
	}

	int LineTo(const FT_Vector *to, void *ptr)
	{
		User *user = static_cast<User*>(ptr);
		user->ring.emplace_back(float(to->x) / 64.0, float(to->y) / 64.0);
		return 0;
	}

	int ConicTo(const FT_Vector *control,
				const FT_Vector *to,
				void *ptr)
	{
		User *user = static_cast<User*>(ptr);

		if (!user->ring.empty()) {
			Point const& prev = user->ring.back();
			auto dx = prev.get<0>();
			auto dy = prev.get<1>();

			// pop off last point, duplicate of first point in bezier curve
			// WARNING: pop_back invalidates `prev`
			// http://en.cppreference.com/w/cpp/container/vector/pop_back
			user->ring.pop_back();

			agg_fontnik::curve3_div curve(dx,dy,
								  float(control->x) / 64, float(control->y) / 64,
								  float(to->x) / 64, float(to->y) / 64);

			curve.rewind(0);
			double x, y;
			unsigned cmd;

			while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y))) {
				user->ring.emplace_back(x, y);
			}
		}

		return 0;
	}

	int CubicTo(const FT_Vector *c1,
				const FT_Vector *c2,
				const FT_Vector *to,
				void *ptr)
	{
		User *user = static_cast<User*>(ptr);

		if (!user->ring.empty()) {

			Point const& prev = user->ring.back();
			auto dx = prev.get<0>();
			auto dy = prev.get<1>();

			// pop off last point, duplicate of first point in bezier curve
			// WARNING: pop_back invalidates `prev`
			// http://en.cppreference.com/w/cpp/container/vector/pop_back
			user->ring.pop_back();

			agg_fontnik::curve4_div curve(dx,dy,
								  float(c1->x) / 64, float(c1->y) / 64,
								  float(c2->x) / 64, float(c2->y) / 64,
								  float(to->x) / 64, float(to->y) / 64);

			curve.rewind(0);
			double x, y;
			unsigned cmd;

			while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y))) {
				user->ring.emplace_back(x, y);
			}
		}

		return 0;
	}

	// point in polygon ray casting algorithm
	bool PolyContainsPoint(const Rings &rings, const Point &p)
	{
		bool c = false;

		for (const Points &ring : rings) {
			auto p1 = ring.begin();
			auto p2 = p1 + 1;

			for (; p2 != ring.end(); p1++, p2++) {
				if (((p1->get<1>() > p.get<1>()) != (p2->get<1>() > p.get<1>())) && (p.get<0>() < (p2->get<0>() - p1->get<0>()) * (p.get<1>() - p1->get<1>()) / (p2->get<1>() - p1->get<1>()) + p1->get<0>())) {
					c = !c;
				}
			}
		}

		return c;
	}

	double SquaredDistance(const Point &v, const Point &w)
	{
		const double a = v.get<0>() - w.get<0>();
		const double b = v.get<1>() - w.get<1>();
		return a * a + b * b;
	}

	Point ProjectPointOnLineSegment(const Point &p,
									const Point &v,
									const Point &w)
	{
	  const double l2 = SquaredDistance(v, w);
	  if (l2 == 0) return v;

	  const double t = ((p.get<0>() - v.get<0>()) * (w.get<0>() - v.get<0>()) + (p.get<1>() - v.get<1>()) * (w.get<1>() - v.get<1>())) / l2;
	  if (t < 0) return v;
	  if (t > 1) return w;

	  return Point(
		  v.get<0>() + t * (w.get<0>() - v.get<0>()),
		  v.get<1>() + t * (w.get<1>() - v.get<1>())
	  );
	}

	double SquaredDistanceToLineSegment(const Point &p,
										const Point &v,
										const Point &w)
	{
		const Point s = ProjectPointOnLineSegment(p, v, w);
		return SquaredDistance(p, s);
	}

	double MinDistanceToLineSegment(const Tree &tree,
									const Point &p,
									int radius)
	{
		const int squared_radius = radius * radius;

		std::vector<SegmentValue> results;
		tree.query(bgi::intersects(
			Box{
				Point{p.get<0>() - radius, p.get<1>() - radius},
				Point{p.get<0>() + radius, p.get<1>() + radius}
			}),
			std::back_inserter(results));

		double sqaured_distance = std::numeric_limits<double>::infinity();

		for (const auto &value : results) {
			const SegmentPair &segment = value.second;
			const double dist = SquaredDistanceToLineSegment(p,
															 segment.first,
															 segment.second);
			if (dist < sqaured_distance && dist < squared_radius) {
				sqaured_distance = dist;
			}
		}

		return std::sqrt(sqaured_distance);
	}
} // ns sdf_glyph_foundry
