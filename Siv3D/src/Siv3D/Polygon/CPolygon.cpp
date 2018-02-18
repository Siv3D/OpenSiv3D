//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CPolygon.hpp"
S3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
S3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
S3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
S3D_DISABLE_MSVC_WARNINGS_PUSH(4245)
S3D_DISABLE_MSVC_WARNINGS_PUSH(4267)
S3D_DISABLE_MSVC_WARNINGS_PUSH(4456)
S3D_DISABLE_MSVC_WARNINGS_PUSH(4819)
# include <boost/geometry/algorithms/intersects.hpp>
# include <boost/geometry/strategies/strategies.hpp>
# include <boost/geometry/algorithms/centroid.hpp>
# include <boost/geometry/algorithms/convex_hull.hpp>
# include <boost/geometry/algorithms/simplify.hpp>
# include <boost/geometry/algorithms/buffer.hpp>
# include <boost/geometry/algorithms/union.hpp>
S3D_DISABLE_MSVC_WARNINGS_POP()
S3D_DISABLE_MSVC_WARNINGS_POP()
S3D_DISABLE_MSVC_WARNINGS_POP()
S3D_DISABLE_MSVC_WARNINGS_POP()
S3D_DISABLE_MSVC_WARNINGS_POP()
S3D_DISABLE_MSVC_WARNINGS_POP()
S3D_DISABLE_MSVC_WARNINGS_POP()
# include "../../ThirdParty/clip2tri/clip2tri.h"
# include "../Siv3DEngine.hpp"
# include <Siv3D/LineString.hpp>
# include <Siv3D/Logger.hpp>
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	namespace detail
	{
		template <class Type>
		static RectF CalculateBoundingRect(const Vector2D<Type>* const pVertex, const size_t vertexSize)
		{
			assert(pVertex != nullptr);
			assert(vertexSize != 0);

			const Vector2D<Type>* it = pVertex;
			const Vector2D<Type>* itEnd = it + vertexSize;

			double left = it->x;
			double top = it->y;
			double right = left;
			double bottom = top;
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

			return RectF(left, top, right - left, bottom - top);
		}

		static double TriangleArea(const Float2& p0, const Float2& p1, const Float2& p2)
		{
			return std::abs((p0.x - p2.x) * (p1.y - p0.y) - (p0.x - p1.x) * (p2.y - p0.y)) * 0.5;
		}
	}

	Polygon::CPolygon::CPolygon()
	{

	}

	Polygon::CPolygon::CPolygon(const Vec2* const pVertex, const size_t vertexSize, Array<Array<Vec2>> _holes)
	{
		if (vertexSize < 3)
		{
			return;
		}

		m_holes = std::move(_holes);

		m_holes.remove_if([](const Array<Vec2>& hole) { return hole.size() < 3; });

		m_polygon.outer().assign(pVertex, pVertex + vertexSize);

		for (const auto& hole : m_holes)
		{
			m_polygon.inners().push_back(gRing(hole.begin(), hole.end()));
		}

		m_boundingRect = detail::CalculateBoundingRect(pVertex, vertexSize);

		Triangulate(m_holes, Array<Vec2>(pVertex, pVertex + vertexSize), m_vertices, m_indices);
	}

	Polygon::CPolygon::CPolygon(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes, const Array<uint32>& indices, const RectF& boundingRect)
	{
		if (vertexSize < 3)
		{
			return;
		}

		m_holes = holes;

		m_polygon.outer().assign(pVertex, pVertex + vertexSize);

		for (const auto& hole : m_holes)
		{
			m_polygon.inners().push_back(gRing(hole.begin(), hole.end()));
		}

		m_boundingRect = boundingRect;

		m_indices = indices;
	}

	Polygon::CPolygon::CPolygon(const Float2* const pVertex, const size_t vertexSize, const Array<uint32>& indices)
	{
		if (vertexSize < 3)
		{
			return;
		}

		m_polygon.outer().assign(pVertex, pVertex + vertexSize);

		m_boundingRect = detail::CalculateBoundingRect(pVertex, vertexSize);

		m_vertices.assign(pVertex, pVertex + vertexSize);

		m_indices = indices;
	}

	void Polygon::CPolygon::copyFrom(CPolygon& other)
	{
		m_polygon = other.m_polygon;

		m_boundingRect = other.m_boundingRect;

		m_holes = other.m_holes;

		m_vertices = other.m_vertices;

		m_indices = other.m_indices;
	}

	void Polygon::CPolygon::moveFrom(CPolygon& other)
	{
		m_polygon = std::move(other.m_polygon);

		m_boundingRect = other.m_boundingRect;

		other.m_boundingRect.set(0, 0, 0, 0);

		m_holes = std::move(other.m_holes);

		m_vertices = std::move(other.m_vertices);

		m_indices = std::move(other.m_indices);
	}

	void Polygon::CPolygon::moveBy(const double x, const double y)
	{
		for (auto& point : m_polygon.outer())
		{
			point.moveBy(x, y);
		}

		for (auto& hole : m_polygon.inners())
		{
			for (auto& point : hole)
			{
				point.moveBy(x, y);
			}
		}

		m_boundingRect.moveBy(x, y);

		for (auto& hole : m_holes)
		{
			for (auto& point : hole)
			{
				point.moveBy(x, y);
			}
		}

		const float xf = static_cast<float>(x);
		const float yf = static_cast<float>(y);

		for (auto& point : m_vertices)
		{
			point.moveBy(xf, yf);
		}
	}

	double Polygon::CPolygon::area() const
	{
		const size_t _num_triangles = m_indices.size() / 3;

		//const bool _hasHoles = !m_polygon.inners().empty();

		double result = 0.0;

		for (size_t index = 0; index < _num_triangles; ++index)
		{
			const uint32 indices[3] =
			{
				m_indices[index * 3 + 0],
				m_indices[index * 3 + 1],
				m_indices[index * 3 + 2],
			};

			result +=detail::TriangleArea(m_vertices[indices[0]], m_vertices[indices[1]], m_vertices[indices[2]]);
		}

		return result;
	}
	
	Vec2 Polygon::CPolygon::centroid() const
	{
		if (outer().isEmpty())
		{
			return Vec2(0, 0);
		}
		
		Vec2 centroid;
		
		boost::geometry::centroid(m_polygon, centroid);
		
		return centroid;
	}
	
	Polygon Polygon::CPolygon::calculateConvexHull() const
	{
		gRing result;
		
		boost::geometry::convex_hull(m_polygon.outer(), result);
		
		return Polygon(result);
	}

	Polygon Polygon::CPolygon::calculateBuffer(const double distance) const
	{
		using polygon_t = boost::geometry::model::polygon<Vec2, true, false>;
		const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(distance);
		const boost::geometry::strategy::buffer::end_round end_strategy(0);
		const boost::geometry::strategy::buffer::point_circle circle_strategy(0);
		const boost::geometry::strategy::buffer::side_straight side_strategy;
		const boost::geometry::strategy::buffer::join_miter join_strategy;

		const auto& src = m_polygon;

		polygon_t in;
		{
			for (size_t i = 0; i < src.outer().size(); ++i)
			{
				in.outer().push_back(src.outer()[src.outer().size() - i - 1]);
			}

			if (src.outer().size() >= 2)
			{
				in.outer().push_back(src.outer()[src.outer().size() - 1]);

				in.outer().push_back(src.outer()[src.outer().size() - 2]);
			}
		}

		if (const size_t num_holes = src.inners().size())
		{
			in.inners().resize(num_holes);

			for (size_t i = 0; i < num_holes; ++i)
			{
				for (size_t k = 0; k < src.inners()[i].size(); ++k)
				{
					in.inners()[i].push_back(src.inners()[i][src.inners()[i].size() - k - 1]);
				}

				if (!src.inners()[i].empty())
				{
					in.inners()[i].push_back(src.inners()[i][src.inners()[i].size() - 1]);
				}
			}
		}

		boost::geometry::model::multi_polygon<gPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return Polygon();
		}

		auto& outer = multiPolygon[0].outer();

		if (outer.size() > 2 && (outer.front().x == outer.back().x) && (outer.front().y == outer.back().y))
		{
			outer.pop_back();
		}

		const auto& inners = multiPolygon[0].inners();

		Array<Array<Vec2>> holes(inners.size());

		for (size_t i = 0; i < holes.size(); ++i)
		{
			const auto& resultHole = inners[i];

			holes[i].assign(resultHole.rbegin(), resultHole.rend());
		}

		return Polygon(outer, holes);
	}

	Polygon Polygon::CPolygon::calculateRoundBuffer(const double distance) const
	{
		using polygon_t = boost::geometry::model::polygon<Vec2, true, false>;
		const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(distance);
		const boost::geometry::strategy::buffer::end_round end_strategy(0);
		const boost::geometry::strategy::buffer::point_circle circle_strategy(0);
		const boost::geometry::strategy::buffer::side_straight side_strategy;
		const boost::geometry::strategy::buffer::join_round_by_divide join_strategy(4);

		const auto& src = m_polygon;

		polygon_t in;
		{
			for (size_t i = 0; i < src.outer().size(); ++i)
			{
				in.outer().push_back(src.outer()[src.outer().size() - i - 1]);
			}

			if (src.outer().size() >= 2)
			{
				in.outer().push_back(src.outer()[src.outer().size() - 1]);

				in.outer().push_back(src.outer()[src.outer().size() - 2]);
			}
		}

		if (const size_t num_holes = src.inners().size())
		{
			in.inners().resize(num_holes);

			for (size_t i = 0; i < num_holes; ++i)
			{
				for (size_t k = 0; k < src.inners()[i].size(); ++k)
				{
					in.inners()[i].push_back(src.inners()[i][src.inners()[i].size() - k - 1]);
				}

				if (!src.inners()[i].empty())
				{
					in.inners()[i].push_back(src.inners()[i][src.inners()[i].size() - 1]);
				}
			}
		}

		boost::geometry::model::multi_polygon<gPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return Polygon();
		}

		auto& outer = multiPolygon[0].outer();

		if (outer.size() > 2 && (outer.front().x == outer.back().x) && (outer.front().y == outer.back().y))
		{
			outer.pop_back();
		}

		const auto& inners = multiPolygon[0].inners();

		Array<Array<Vec2>> holes(inners.size());

		for (size_t i = 0; i < holes.size(); ++i)
		{
			const auto& resultHole = inners[i];

			holes[i].assign(resultHole.rbegin(), resultHole.rend());
		}

		return Polygon(outer, holes);
	}

	Polygon Polygon::CPolygon::simplified(const double maxDistance) const
	{
		if (!m_polygon.outer())
		{
			return Polygon();
		}

		gLineString result;
		{
			gLineString v(m_polygon.outer().begin(), m_polygon.outer().end());

			v.push_back(v.front());

			boost::geometry::simplify(v, result, maxDistance);

			if (result.size() > 3)
			{
				result.pop_back();
			}
		}

		Array<Array<Vec2>> holeResults;

		for (auto& hole : m_polygon.inners())
		{
			gLineString v(hole.begin(), hole.end()), result2;

			v.push_back(v.front());

			boost::geometry::simplify(v, result2, maxDistance);

			if (result2.size() > 3)
			{
				result2.pop_back();
			}

			holeResults.push_back(std::move(result2));
		}

		return Polygon(result, holeResults);
	}

	bool Polygon::CPolygon::append(const Polygon& polygon)
	{
		Array<gPolygon> results;

		boost::geometry::union_(m_polygon, polygon._detail()->getPolygon(), results);

		if (results.size() != 1)
		{
			return false;
		}

		auto& outer = results[0].outer();

		if (outer.size() > 2 && (outer.front().x == outer.back().x) && (outer.front().y == outer.back().y))
		{
			outer.pop_back();
		}

		Array<Array<Vec2>> holes;

		const auto& result = results[0];

		if (const size_t num_holes = result.inners().size())
		{
			holes.resize(num_holes);

			for (size_t i = 0; i < num_holes; ++i)
			{
				const auto& resultHole = result.inners()[i];

				holes[i].assign(resultHole.begin(), resultHole.end());
			}
		}

		*this = CPolygon(outer.data(), outer.size(), holes);

		return true;
	}

	bool Polygon::CPolygon::intersects(const CPolygon& other) const
	{
		if (outer().isEmpty() || other.outer().isEmpty() || !m_boundingRect.intersects(other.m_boundingRect))
		{
			return false;
		}

		return boost::geometry::intersects(m_polygon, other.m_polygon);
	}

	const Array<Vec2>& Polygon::CPolygon::outer() const
	{
		return m_polygon.outer();
	}

	const Array<Array<Vec2>>& Polygon::CPolygon::inners() const
	{
		return m_holes;
	}

	const RectF& Polygon::CPolygon::boundingRect() const
	{
		return m_boundingRect;
	}

	const Array<Float2>& Polygon::CPolygon::vertices() const
	{
		return m_vertices;
	}

	const Array<uint32>& Polygon::CPolygon::indices() const
	{
		return m_indices;
	}

	void Polygon::CPolygon::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addShape2D(m_vertices, m_indices, color.toFloat4());
	}

	void Polygon::CPolygon::drawFrame(double thickness, const ColorF& color) const
	{
		if (m_polygon.outer().isEmpty())
		{
			return;
		}

		Siv3DEngine::GetRenderer2D()->addLineString(
			LineStyle::Default,
			m_polygon.outer().data(),
			static_cast<uint32>(m_polygon.outer().size()),
			none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			true
		);

		for (const auto& hole : m_polygon.inners())
		{
			Siv3DEngine::GetRenderer2D()->addLineString(
				LineStyle::Default,
				hole.data(),
				static_cast<uint32>(hole.size()),
				none,
				static_cast<float>(thickness),
				false,
				color.toFloat4(),
				true
			);
		}
	}

	const gPolygon& Polygon::CPolygon::getPolygon() const
	{
		return m_polygon;
	}

	Polygon LineString::calculateBuffer(const double distance, const uint32 quality, const bool isClosed) const
	{
		if (size() < 2)
		{
			return Polygon();
		}

		const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(distance);
		const boost::geometry::strategy::buffer::end_round end_strategy(quality);
		const boost::geometry::strategy::buffer::point_circle circle_strategy(quality);
		const boost::geometry::strategy::buffer::side_straight side_strategy;
		const boost::geometry::strategy::buffer::join_round join_strategy(quality);

		boost::geometry::model::multi_polygon<gPolygon> multiPolygon;

		if (isClosed && size() > 2)
		{
			gLineString lines(begin(), end());

			lines.push_back(front());

			boost::geometry::buffer(lines, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);
		}
		else
		{
			boost::geometry::buffer(gLineString(begin(), end()), multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);
		}

		if (multiPolygon.size() != 1)
		{
			return Polygon();
		}

		auto& resultOuter = multiPolygon[0].outer();

		if (resultOuter.size() > 2 && (resultOuter.front().x == resultOuter.back().x) && (resultOuter.front().y == resultOuter.back().y))
		{
			resultOuter.pop_back();
		}

		Array<Array<Vec2>> holes;

		const auto& result = multiPolygon[0];

		if (const size_t num_holes = result.inners().size())
		{
			holes.resize(num_holes);

			for (size_t i = 0; i < num_holes; ++i)
			{
				const auto& resultHole = result.inners()[i];

				holes[i].assign(resultHole.begin(), resultHole.end());
			}
		}	

		Array<Vec2> outer2;

		outer2 << resultOuter[0];

		Vec2 previous = resultOuter[0];

		for (size_t i = 1; i < resultOuter.size(); ++i)
		{
			const Vec2 current = resultOuter[i];

			if (previous != current)
			{
				outer2 << current;

				previous = current;
			}
		}

		return Polygon(outer2, holes);
	}
}
