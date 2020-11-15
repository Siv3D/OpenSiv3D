//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "PolygonDetail.hpp"
# include "Triangulation.hpp"

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
			m_indices.resize(indices.size() * 3);
			assert(m_indices.size_bytes()  == indices.size_bytes());
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
}
