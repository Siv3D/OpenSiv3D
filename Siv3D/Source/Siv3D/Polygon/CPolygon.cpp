//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CPolygon.hpp"
S3D_DISABLE_MSVC_WARNINGS_PUSH(4819)
# include <boost/geometry/algorithms/intersects.hpp>
S3D_DISABLE_MSVC_WARNINGS_POP()
# include "../../ThirdParty/clip2tri/clip2tri.h"
# include <Siv3D/Shape2D.hpp>

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
	}

	Polygon::CPolygon::CPolygon()
	{

	}

	Polygon::CPolygon::CPolygon(const Vec2* const pVertex, const size_t vertexSize, Array<Array<Vec2>> _holes)
		: m_holes(std::move(_holes))
	{
		if (vertexSize < 3)
		{
			return;
		}

		m_holes.removed_if([](const Array<Vec2>& hole) { return hole.size() < 3; });

		m_polygon.outer().assign(pVertex, pVertex + vertexSize);

		for (const auto& hole : m_holes)
		{
			m_polygon.inners().push_back(gRing(hole.begin(), hole.end()));
		}

		m_boundingRect = detail::CalculateBoundingRect(pVertex, vertexSize);

		Triangulate(m_holes, Array<Vec2>(pVertex, pVertex + vertexSize), m_vertices, m_indices);
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
		Shape2D{ m_vertices, m_indices }.draw(color);
	}
}
