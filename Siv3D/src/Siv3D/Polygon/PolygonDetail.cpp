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

# include "PolygonDetail.hpp"
# include "Triangulation.hpp"
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

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
			const Vector2D<Type>* itEnd = (it + vertexSize);

			double left		= it->x;
			double top		= it->y;
			double right	= left;
			double bottom	= top;
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

		[[nodiscard]]
		static double TriangleArea(const Float2& p0, const Float2& p1, const Float2& p2) noexcept
		{
			return std::abs((p0.x - p2.x) * (p1.y - p0.y) - (p0.x - p1.x) * (p2.y - p0.y)) * 0.5;
		}
	}

	Polygon::PolygonDetail::PolygonDetail()
	{

	}

	Polygon::PolygonDetail::PolygonDetail(const Vec2* const pOuterVertex, const size_t vertexSize, Array<Array<Vec2>> holes, const SkipValidation skipValidation)
	{
		if (vertexSize < 3)
		{
			return;
		}

		if (not skipValidation)
		{
			if (Validate(pOuterVertex, vertexSize, holes)
				!= PolygonFailureType::OK)
			{
				return;
			}
		}

		holes.remove_if([](const Array<Vec2>& hole) { return (hole.size() < 3); });

		// [1 of 5]
		{
			m_polygon.outer().assign(pOuterVertex, pOuterVertex + vertexSize);

			for (const auto& hole : holes)
			{
				m_polygon.inners().emplace_back(hole.begin(), hole.end());
			}
		}

		// [2 of 5]
		m_holes = std::move(holes);

		// [3 of 5], [4 of 5]
		{
			Array<Vertex2D::IndexType> indices;
			detail::Triangulate(m_polygon.outer(), m_holes, m_vertices, indices);
			assert(indices.size() % 3 == 0);
			m_indices.resize(indices.size() / 3);
			assert(m_indices.size_bytes() == indices.size_bytes());
			std::memcpy(m_indices.data(), indices.data(), indices.size_bytes());
		}

		// [5 of 5]
		m_boundingRect = detail::CalculateBoundingRect(pOuterVertex, vertexSize);
	}

	Polygon::PolygonDetail::PolygonDetail(const Vec2* pOuterVertex, const size_t vertexSize, Array<TriangleIndex> indices, const RectF& boundingRect, const SkipValidation skipValidation)
	{
		if (vertexSize < 3)
		{
			return;
		}

		if (not skipValidation)
		{
			if (Validate(pOuterVertex, vertexSize)
				!= PolygonFailureType::OK)
			{
				return;
			}
		}

		// [1 of 5]
		m_polygon.outer().assign(pOuterVertex, pOuterVertex + vertexSize);

		// [2 of 5]
		// do nothing

		// [3 of 5]
		m_vertices.assign(pOuterVertex, pOuterVertex + vertexSize);

		// [4 of 5]
		m_indices = std::move(indices);

		// [5 of 5]
		m_boundingRect = boundingRect;
	}

	Polygon::PolygonDetail::PolygonDetail(const Array<Vec2>& outer, Array<Array<Vec2>> holes, Array<Float2> vertices, Array<TriangleIndex> indices, const RectF& boundingRect, const SkipValidation skipValidation)
	{
		if (outer.size() < 3)
		{
			return;
		}

		if (not skipValidation)
		{
			if (Validate(outer, holes)
				!= PolygonFailureType::OK)
			{
				return;
			}
		}

		holes.remove_if([](const Array<Vec2>& hole) { return (hole.size() < 3); });

		// [1 of 5]
		{
			m_polygon.outer().assign(outer.begin(), outer.end());

			for (const auto& hole : holes)
			{
				m_polygon.inners().emplace_back(hole.begin(), hole.end());
			}
		}

		// [2 of 5]
		m_holes = std::move(holes);

		// [3 of 5]
		m_vertices = std::move(vertices);

		// [4 of 5]
		m_indices = std::move(indices);

		// [5 of 5]
		m_boundingRect = boundingRect;
	}

	Polygon::PolygonDetail::PolygonDetail(const Float2* pOuterVertex, const size_t vertexSize, Array<TriangleIndex> indices)
	{
		if (vertexSize < 3)
		{
			return;
		}

		// [1 of 5]
		m_polygon.outer().assign(pOuterVertex, pOuterVertex + vertexSize);

		// [2 of 5]
		// do nothing

		// [3 of 5]
		m_vertices.assign(pOuterVertex, pOuterVertex + vertexSize);

		// [4 of 5]
		m_indices = std::move(indices);

		// [5 of 5]
		m_boundingRect = detail::CalculateBoundingRect(pOuterVertex, vertexSize);
	}

	const Array<Vec2>& Polygon::PolygonDetail::outer() const noexcept
	{
		return m_polygon.outer();
	}

	const Array<Array<Vec2>>& Polygon::PolygonDetail::inners() const noexcept
	{
		return m_holes;
	}

	const Array<Float2>& Polygon::PolygonDetail::vertices() const noexcept
	{
		return m_vertices;
	}

	const Array<TriangleIndex>& Polygon::PolygonDetail::indices() const noexcept
	{
		return m_indices;
	}

	const RectF& Polygon::PolygonDetail::boundingRect() const noexcept
	{
		return m_boundingRect;
	}

	void Polygon::PolygonDetail::moveBy(const Vec2 v) noexcept
	{
		if (outer().isEmpty())
		{
			return;
		}

		{
			for (auto& point : m_polygon.outer())
			{
				point.moveBy(v);
			}

			for (auto& hole : m_polygon.inners())
			{
				for (auto& point : hole)
				{
					point.moveBy(v);
				}
			}
		}

		for (auto& hole : m_holes)
		{
			for (auto& point : hole)
			{
				point.moveBy(v);
			}
		}

		{
			const Float2 vf{ v };

			for (auto& point : m_vertices)
			{
				point.moveBy(vf);
			}
		}

		m_boundingRect.moveBy(v);
	}

	void Polygon::PolygonDetail::rotateAt(const Vec2 pos, const double angle)
	{
		if (outer().isEmpty())
		{
			return;
		}

		if (not pos.isZero())
		{
			for (auto& point : m_polygon.outer())
			{
				point -= pos;
			}

			for (auto& hole : m_polygon.inners())
			{
				for (auto& point : hole)
				{
					point -= pos;
				}
			}

			const Float2 posF = pos;

			for (auto& vertex : m_vertices)
			{
				vertex -= posF;
			}
		}

		const double s = std::sin(angle);
		const double c = std::cos(angle);

		for (auto& point : m_polygon.outer())
		{
			const double x = (point.x * c - point.y * s);
			const double y = (point.x * s + point.y * c);
			point.set(x, y);
		}

		for (auto& hole : m_polygon.inners())
		{
			for (auto& point : hole)
			{
				const double x = (point.x * c - point.y * s);
				const double y = (point.x * s + point.y * c);
				point.set(x, y);
			}
		}

		const float sF = static_cast<float>(s);
		const float cF = static_cast<float>(c);

		for (auto& vertex : m_vertices)
		{
			const float x = (vertex.x * cF - vertex.y * sF);
			const float y = (vertex.x * sF + vertex.y * cF);
			vertex.set(x, y);
		}

		if (not pos.isZero())
		{
			for (auto& point : m_polygon.outer())
			{
				point += pos;
			}

			for (auto& hole : m_polygon.inners())
			{
				for (auto& point : hole)
				{
					point += pos;
				}
			}

			const Float2 posF = pos;

			for (auto& vertex : m_vertices)
			{
				vertex += posF;
			}
		}

		m_holes.clear();

		for (auto& hole : m_polygon.inners())
		{
			m_holes.emplace_back();
			m_holes.back().insert(m_holes.back().end(), hole.begin(), hole.end());
		}

		m_boundingRect = detail::CalculateBoundingRect(m_vertices.data(), m_vertices.size());
	}

	void Polygon::PolygonDetail::transform(const double s, const double c, const Vec2& pos)
	{
		if (outer().isEmpty())
		{
			return;
		}

		for (auto& point : m_polygon.outer())
		{
			const double x = (point.x * c - point.y * s + pos.x);
			const double y = (point.x * s + point.y * c + pos.y);
			point.set(x, y);
		}

		for (auto& hole : m_polygon.inners())
		{
			for (auto& point : hole)
			{
				const double x = (point.x * c - point.y * s + pos.x);
				const double y = (point.x * s + point.y * c + pos.y);
				point.set(x, y);
			}
		}

		const float sF = static_cast<float>(s);
		const float cF = static_cast<float>(c);
		const float xF = static_cast<float>(pos.x);
		const float yF = static_cast<float>(pos.y);

		for (auto& vertex : m_vertices)
		{
			const float x = (vertex.x * cF - vertex.y * sF + xF);
			const float y = (vertex.x * sF + vertex.y * cF + yF);
			vertex.set(x, y);
		}

		m_holes.clear();

		for (auto& hole : m_polygon.inners())
		{
			m_holes.emplace_back();
			m_holes.back().insert(m_holes.back().end(), hole.begin(), hole.end());
		}

		m_boundingRect = detail::CalculateBoundingRect(m_vertices.data(), m_vertices.size());
	}

	void Polygon::PolygonDetail::scale(const double s)
	{
		if (outer().isEmpty())
		{
			return;
		}

		for (auto& point : m_polygon.outer())
		{
			point *= s;
		}

		for (auto& hole : m_polygon.inners())
		{
			for (auto& point : hole)
			{
				point *= s;
			}
		}

		for (auto& hole : m_holes)
		{
			for (auto& point : hole)
			{
				point *= s;
			}
		}

		const float sf = static_cast<float>(s);

		for (auto& point : m_vertices)
		{
			point *= sf;
		}

		// [Siv3D ToDo] 不要に
		m_boundingRect = detail::CalculateBoundingRect(m_vertices.data(), m_vertices.size());
	}

	void Polygon::PolygonDetail::scale(const Vec2 s)
	{
		if (outer().isEmpty())
		{
			return;
		}

		for (auto& point : m_polygon.outer())
		{
			point *= s;
		}

		for (auto& hole : m_polygon.inners())
		{
			for (auto& point : hole)
			{
				point *= s;
			}
		}

		for (auto& hole : m_holes)
		{
			for (auto& point : hole)
			{
				point *= s;
			}
		}

		const Float2 sf{ s };

		for (auto& point : m_vertices)
		{
			point *= sf;
		}

		// [Siv3D ToDo] 不要に
		m_boundingRect = detail::CalculateBoundingRect(m_vertices.data(), m_vertices.size());
	}

	void Polygon::PolygonDetail::scaleAt(const Vec2 pos, const double s)
	{
		if (outer().isEmpty())
		{
			return;
		}

		for (auto& point : m_polygon.outer())
		{
			point = (pos + (point - pos) * s);
		}

		for (auto& hole : m_polygon.inners())
		{
			for (auto& point : hole)
			{
				point = (pos + (point - pos) * s);
			}
		}

		for (auto& hole : m_holes)
		{
			for (auto& point : hole)
			{
				point = (pos + (point - pos) * s);
			}
		}

		const float sf = static_cast<float>(s);
		const Float2 posF{ pos };

		for (auto& point : m_vertices)
		{
			point = (posF + (point - posF) * sf);
		}

		// [Siv3D ToDo] 不要に
		m_boundingRect = detail::CalculateBoundingRect(m_vertices.data(), m_vertices.size());
	}

	void Polygon::PolygonDetail::scaleAt(const Vec2 pos, const Vec2 s)
	{
		if (outer().isEmpty())
		{
			return;
		}

		for (auto& point : m_polygon.outer())
		{
			point = (pos + (point - pos) * s);
		}

		for (auto& hole : m_polygon.inners())
		{
			for (auto& point : hole)
			{
				point = (pos + (point - pos) * s);
			}
		}

		for (auto& hole : m_holes)
		{
			for (auto& point : hole)
			{
				point = (pos + (point - pos) * s);
			}
		}

		const Float2 sf{ s };
		const Float2 posF{ pos };

		for (auto& point : m_vertices)
		{
			point = (posF + (point - posF) * sf);
		}

		// [Siv3D ToDo] 不要に
		m_boundingRect = detail::CalculateBoundingRect(m_vertices.data(), m_vertices.size());
	}

	double Polygon::PolygonDetail::area() const noexcept
	{
		const size_t _num_triangles = m_indices.size();

		double result = 0.0;

		for (size_t i = 0; i < _num_triangles; ++i)
		{
			const auto& index = m_indices[i];

			result += detail::TriangleArea(m_vertices[index.i0], m_vertices[index.i1], m_vertices[index.i2]);
		}

		return result;
	}

	double Polygon::PolygonDetail::perimeter() const noexcept
	{
		double result = 0.0;

		{
			const auto& outer = m_polygon.outer();
			const size_t num_outer = outer.size();

			for (size_t i = 0; i < num_outer; ++i)
			{
				result += outer[i].distanceFrom(outer[(i + 1) % num_outer]);
			}
		}

		{
			for (const auto& inner : m_polygon.inners())
			{
				const size_t num_inner = inner.size();

				for (size_t i = 0; i < num_inner; ++i)
				{
					result += inner[i].distanceFrom(inner[(i + 1) % num_inner]);
				}
			}
		}

		return result;
	}

	Vec2 Polygon::PolygonDetail::centroid() const
	{
		if (outer().isEmpty())
		{
			return Vec2{ 0, 0 };
		}

		Vec2 centroid;

		boost::geometry::centroid(m_polygon, centroid);

		return centroid;
	}

	Polygon Polygon::PolygonDetail::computeConvexHull() const
	{
		CWOpenRing result;

		boost::geometry::convex_hull(m_polygon.outer(), result);

		return Polygon{ result };
	}

	Polygon Polygon::PolygonDetail::calculateBuffer(const double distance) const
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
			auto& in_outer = in.outer();
			const auto& src_outer = src.outer();

			for (size_t i = 0; i < src_outer.size(); ++i)
			{
				in_outer.push_back(src_outer[src_outer.size() - i - 1]);
			}

			if (src.outer().size() >= 2)
			{
				in_outer.push_back(src_outer[src_outer.size() - 1]);

				in_outer.push_back(src_outer[src_outer.size() - 2]);
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
			}
		}

		boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return{};
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

		return Polygon{ outer, holes };
	}

	Polygon Polygon::PolygonDetail::calculateRoundBuffer(const double distance) const
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
			auto& in_outer = in.outer();
			const auto& src_outer = src.outer();

			for (size_t i = 0; i < src_outer.size(); ++i)
			{
				in_outer.push_back(src_outer[src_outer.size() - i - 1]);
			}

			if (src.outer().size() >= 2)
			{
				in_outer.push_back(src_outer[src_outer.size() - 1]);

				in_outer.push_back(src_outer[src_outer.size() - 2]);
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
			}
		}

		boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return{};
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

		return Polygon{ outer, holes };
	}

	Polygon Polygon::PolygonDetail::simplified(const double maxDistance) const
	{
		if (not m_polygon.outer())
		{
			return{};
		}

		GLineString result;
		{
			GLineString v(m_polygon.outer().begin(), m_polygon.outer().end());

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
			GLineString v(hole.begin(), hole.end()), result2;

			v.push_back(v.front());

			boost::geometry::simplify(v, result2, maxDistance);

			if (result2.size() > 3)
			{
				result2.pop_back();
			}

			holeResults.push_back(std::move(result2));
		}

		return Polygon{ result, holeResults };
	}

	bool Polygon::PolygonDetail::append(const RectF& other)
	{
		const boost::geometry::model::box<Vec2> box{ other.pos, other.br() };

		Array<CwOpenPolygon> results;

		boost::geometry::union_(m_polygon, box, results);

		if (results.size() != 1)
		{
			return false;
		}

		auto& outer = results[0].outer();

		if ((2 < outer.size())
			&& (outer.front() == outer.back()))
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
				const auto resultHole = result.inners()[i];

				holes[i].assign(resultHole.begin(), resultHole.end());
			}
		}

		*this = PolygonDetail{ outer.data(), outer.size(), holes, SkipValidation::Yes };

		return true;
	}

	bool Polygon::PolygonDetail::append(const Polygon& other)
	{
		Array<CwOpenPolygon> results;

		boost::geometry::union_(m_polygon, other._detail()->getPolygon(), results);

		if (results.size() != 1)
		{
			return false;
		}

		auto& outer = results[0].outer();

		if ((2 < outer.size())
			&& (outer.front() == outer.back()))
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
				const auto resultHole = result.inners()[i];

				holes[i].assign(resultHole.begin(), resultHole.end());
			}
		}

		*this = PolygonDetail{ outer.data(), outer.size(), holes, SkipValidation::Yes };

		return true;
	}

	bool Polygon::PolygonDetail::intersects(const Line& other) const
	{
		if (outer().isEmpty()
			|| (not Geometry2D::Intersect(m_boundingRect, other)))
		{
			return false;
		}

		const Float2* pVertex = m_vertices.data();

		for (const auto& triangleIndex : m_indices)
		{
			const Triangle triangle{ pVertex[triangleIndex.i0], pVertex[triangleIndex.i1], pVertex[triangleIndex.i2] };

			if (Geometry2D::Intersect(other, triangle))
			{
				return true;
			}
		}

		return false;
	}

	bool Polygon::PolygonDetail::intersects(const RectF& other) const
	{
		if (outer().isEmpty()
			|| (not m_boundingRect.intersects(other)))
		{
			return false;
		}

		const boost::geometry::model::box<Vec2> box{ other.pos, other.br() };

		return boost::geometry::intersects(m_polygon, box);
	}

	bool Polygon::PolygonDetail::intersects(const PolygonDetail& other) const
	{
		if (outer().isEmpty()
			|| other.outer().isEmpty()
			|| (not m_boundingRect.intersects(other.m_boundingRect)))
		{
			return false;
		}

		return boost::geometry::intersects(m_polygon, other.m_polygon);
	}

	void Polygon::PolygonDetail::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addPolygon(m_vertices, m_indices, none, color.toFloat4());
	}

	void Polygon::PolygonDetail::draw(const Vec2& offset, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addPolygon(m_vertices, m_indices, Float2{ offset }, color.toFloat4());
	}

	void Polygon::PolygonDetail::drawFrame(const double thickness, const ColorF& color) const
	{
		if (not m_polygon.outer())
		{
			return;
		}

		SIV3D_ENGINE(Renderer2D)->addLineString(
			LineStyle::Default,
			m_polygon.outer().data(),
			m_polygon.outer().size(),
			none,
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			CloseRing::Yes
		);

		for (const auto& hole : m_polygon.inners())
		{
			SIV3D_ENGINE(Renderer2D)->addLineString(
				LineStyle::Default,
				hole.data(),
				hole.size(),
				none,
				static_cast<float>(thickness),
				false,
				color.toFloat4(),
				CloseRing::Yes
			);
		}
	}

	void Polygon::PolygonDetail::drawFrame(const Vec2& offset, double thickness, const ColorF& color) const
	{
		if (not m_polygon.outer())
		{
			return;
		}

		SIV3D_ENGINE(Renderer2D)->addLineString(
			LineStyle::Default,
			m_polygon.outer().data(),
			m_polygon.outer().size(),
			Float2{ offset },
			static_cast<float>(thickness),
			false,
			color.toFloat4(),
			CloseRing::Yes
		);

		for (const auto& hole : m_polygon.inners())
		{
			SIV3D_ENGINE(Renderer2D)->addLineString(
				LineStyle::Default,
				hole.data(),
				hole.size(),
				Float2{ offset },
				static_cast<float>(thickness),
				false,
				color.toFloat4(),
				CloseRing::Yes
			);
		}
	}

	void Polygon::PolygonDetail::drawTransformed(const double s, const double c, const Vec2& pos, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addPolygonTransformed(m_vertices, m_indices,
			static_cast<float>(s), static_cast<float>(c),
			Float2{ pos },
			color.toFloat4());
	}

	const CwOpenPolygon& Polygon::PolygonDetail::getPolygon() const noexcept
	{
		return m_polygon;
	}
}


namespace s3d
{
	Polygon Triangle::calculateBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return asPolygon();
		}

		using polygon_t = boost::geometry::model::polygon<Vec2, true, false>;
		const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(distance);
		const boost::geometry::strategy::buffer::end_round end_strategy(0);
		const boost::geometry::strategy::buffer::point_circle circle_strategy(0);
		const boost::geometry::strategy::buffer::side_straight side_strategy;
		const boost::geometry::strategy::buffer::join_miter join_strategy{ 65536 };

		polygon_t in;
		{
			auto& outer = in.outer();
			outer.push_back(p(2));
			outer.push_back(p(1));
			outer.push_back(p(0));
			outer.push_back(p(2));
			outer.push_back(p(1));
		}

		boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return{};
		}

		auto& outer = multiPolygon[0].outer();

		if ((2 < outer.size())
			&& (outer.front() == outer.back()))
		{
			outer.pop_back();
		}

		return Polygon{ outer };
	}

	Polygon Triangle::calculateRoundBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return asPolygon();
		}

		using polygon_t = boost::geometry::model::polygon<Vec2, true, false>;
		const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(distance);
		const boost::geometry::strategy::buffer::end_round end_strategy(0);
		const boost::geometry::strategy::buffer::point_circle circle_strategy(0);
		const boost::geometry::strategy::buffer::side_straight side_strategy;
		const boost::geometry::strategy::buffer::join_round_by_divide join_strategy(4);

		polygon_t in;
		{
			auto& outer = in.outer();
			outer.push_back(p(2));
			outer.push_back(p(1));
			outer.push_back(p(0));
			outer.push_back(p(2));
			outer.push_back(p(1));
		}

		boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return{};
		}

		auto& outer = multiPolygon[0].outer();

		if ((2 < outer.size())
			&& (outer.front() == outer.back()))
		{
			outer.pop_back();
		}

		return Polygon{ outer };
	}
}

namespace s3d
{
	Polygon Quad::calculateBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return asPolygon();
		}

		using polygon_t = boost::geometry::model::polygon<Vec2, true, false>;
		const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(distance);
		const boost::geometry::strategy::buffer::end_round end_strategy(0);
		const boost::geometry::strategy::buffer::point_circle circle_strategy(0);
		const boost::geometry::strategy::buffer::side_straight side_strategy;
		const boost::geometry::strategy::buffer::join_miter join_strategy{ 65536 };

		polygon_t in;
		{
			auto& outer = in.outer();
			outer.push_back(p(3));
			outer.push_back(p(2));
			outer.push_back(p(1));
			outer.push_back(p(0));
			outer.push_back(p(3));
			outer.push_back(p(2));
		}

		boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return{};
		}

		auto& outer = multiPolygon[0].outer();

		if ((2 < outer.size())
			&& (outer.front() == outer.back()))
		{
			outer.pop_back();
		}

		return Polygon{ outer };
	}

	Polygon Quad::calculateRoundBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return asPolygon();
		}

		using polygon_t = boost::geometry::model::polygon<Vec2, true, false>;
		const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(distance);
		const boost::geometry::strategy::buffer::end_round end_strategy(0);
		const boost::geometry::strategy::buffer::point_circle circle_strategy(0);
		const boost::geometry::strategy::buffer::side_straight side_strategy;
		const boost::geometry::strategy::buffer::join_round_by_divide join_strategy(4);

		polygon_t in;
		{
			auto& outer = in.outer();
			outer.push_back(p(3));
			outer.push_back(p(2));
			outer.push_back(p(1));
			outer.push_back(p(0));
			outer.push_back(p(3));
			outer.push_back(p(2));
		}

		boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;
		boost::geometry::buffer(in, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);

		if (multiPolygon.size() != 1)
		{
			return{};
		}

		auto& outer = multiPolygon[0].outer();

		if ((2 < outer.size())
			&& (outer.front() == outer.back()))
		{
			outer.pop_back();
		}

		return Polygon{ outer };
	}
}

# include <Siv3D/LineString.hpp>

namespace s3d
{
	using gLineString = boost::geometry::model::linestring<Vec2, Array>;

	namespace detail
	{
		Polygon CalculateBuffer(const LineString& points, const double distance, CloseRing closeRing, int32 bufferQuality)
		{
			if (points.size() < 2)
			{
				return{};
			}

			bufferQuality = Max(0, bufferQuality);

			const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy{ distance };
			const boost::geometry::strategy::buffer::end_flat end_strategy{};
			const boost::geometry::strategy::buffer::point_square point_strategy{};
			const boost::geometry::strategy::buffer::join_miter join_strategy{ 5 };
			const boost::geometry::strategy::buffer::side_straight side_strategy;

			boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;

			if (closeRing && (2 < points.size()))
			{
				gLineString lines(points.begin(), points.end());

				lines.insert(lines.end(), lines.begin(), lines.begin() + 2);

				boost::geometry::buffer(lines, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, point_strategy);
			}
			else
			{
				boost::geometry::buffer(gLineString(points.begin(), points.end()), multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, point_strategy);
			}

			if (multiPolygon.size() != 1)
			{
				return{};
			}

			auto& resultOuter = multiPolygon[0].outer();

			if ((2 < resultOuter.size())
				&& (resultOuter.front() == resultOuter.back()))
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
					const auto resultHole = result.inners()[i];

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

			return Polygon{ outer2, holes };
		}

		Polygon CalculateRoundBuffer(const LineString& points, const double distance, CloseRing closeRing, int32 bufferQuality)
		{
			if (points.size() < 2)
			{
				return{};
			}

			bufferQuality = Max(0, bufferQuality);

			const boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy{ distance };
			const boost::geometry::strategy::buffer::point_circle circle_strategy{ static_cast<size_t>(bufferQuality) };
			const boost::geometry::strategy::buffer::join_round join_strategy{ static_cast<size_t>(bufferQuality) };
			constexpr boost::geometry::strategy::buffer::side_straight side_strategy{};

			boost::geometry::model::multi_polygon<CwOpenPolygon> multiPolygon;

			if (closeRing && (2 < points.size()))
			{
				gLineString lines(points.begin(), points.end());
				
				lines.insert(lines.end(), lines.begin(), lines.begin() + 2);

				const boost::geometry::strategy::buffer::end_flat end_strategy{};
				boost::geometry::buffer(lines, multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);
			}
			else
			{
				if (points.front() == points.back())
				{
					const boost::geometry::strategy::buffer::end_flat end_strategy{};
					boost::geometry::buffer(gLineString(points.begin(), points.end()), multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);
				}
				else
				{
					const boost::geometry::strategy::buffer::end_round end_strategy{ static_cast<size_t>(bufferQuality) };
					boost::geometry::buffer(gLineString(points.begin(), points.end()), multiPolygon, distance_strategy, side_strategy, join_strategy, end_strategy, circle_strategy);
				}
			}

			if (multiPolygon.size() != 1)
			{
				return{};
			}

			auto& resultOuter = multiPolygon[0].outer();

			if ((2 < resultOuter.size())
				&& (resultOuter.front() == resultOuter.back()))
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
					const auto resultHole = result.inners()[i];

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

			return Polygon{ outer2, holes };
		}
	}

	LineString LineString::simplified(const double maxDistance, const CloseRing closeRing) const
	{
		if (size() < 2)
		{
			return *this;
		}

		gLineString input(begin(), end()), result;

		if (closeRing && (input.front() != input.back()))
		{
			input.push_back(input.front());

			boost::geometry::simplify(input, result, maxDistance);

			result.pop_back();
		}
		else
		{
			boost::geometry::simplify(input, result, maxDistance);
		}

		return LineString(result.begin(), result.end());
	}

	LineString LineString::densified(const double maxDistance, const CloseRing closeRing) const
	{
		if (size() < 2)
		{
			return *this;
		}

		gLineString input(begin(), end()), result;

		if (closeRing && (input.front() != input.back()))
		{
			input.push_back(input.front());

			boost::geometry::densify(input, result, maxDistance);

			result.pop_back();
		}
		else
		{
			boost::geometry::densify(input, result, maxDistance);
		}

		return LineString(result.begin(), result.end());
	}

	Polygon LineString::calculateBuffer(const double distance, const int32 bufferQuality) const
	{
		return detail::CalculateBuffer(*this, distance, CloseRing::No, bufferQuality);
	}

	Polygon LineString::calculateBufferClosed(const double distance, const int32 bufferQuality) const
	{
		return detail::CalculateBuffer(*this, distance, CloseRing::Yes, bufferQuality);
	}

	Polygon LineString::calculateRoundBuffer(const double distance, const int32 bufferQuality) const
	{
		return detail::CalculateRoundBuffer(*this, distance, CloseRing::No, bufferQuality);
	}

	Polygon LineString::calculateRoundBufferClosed(const double distance, const int32 bufferQuality) const
	{
		return detail::CalculateRoundBuffer(*this, distance, CloseRing::Yes, bufferQuality);
	}
}
