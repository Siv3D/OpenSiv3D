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

# include <Siv3D/Polygon.hpp>
# include <Siv3D/HashSet.hpp>
# include "PolygonDetail.hpp"
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4819)
# include <boost/geometry/algorithms/is_valid.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static bool HasSamePoints(const Vec2* pVertex, const size_t vertexSize)
		{
			return (HashSet<Vec2>(pVertex, pVertex + vertexSize).size() != vertexSize);
		}

		[[nodiscard]]
		constexpr PolygonFailureType Convert(const boost::geometry::validity_failure_type failure) noexcept
		{
			// https://www.boost.org/doc/libs/1_72_0/libs/geometry/doc/html/geometry/reference/enumerations/validity_failure_type.html
			switch (failure)
			{
			case boost::geometry::no_failure:
				return PolygonFailureType::OK;
			case boost::geometry::failure_few_points:
				return PolygonFailureType::FewPoints;
			case boost::geometry::failure_wrong_topological_dimension:
				return PolygonFailureType::WrongTopologicalDimension;
			case boost::geometry::failure_spikes:
				return PolygonFailureType::Spikes;
			case boost::geometry::failure_duplicate_points:
				return PolygonFailureType::DuplicatePoints;
			case boost::geometry::failure_not_closed:
				return PolygonFailureType::NotClosed;
			case boost::geometry::failure_self_intersections:
				return PolygonFailureType::SelfIntersections;
			case boost::geometry::failure_wrong_orientation:
				return PolygonFailureType::WrongOrientation;
			case boost::geometry::failure_interior_rings_outside:
				return PolygonFailureType::InteriorRingsOutside;
			case boost::geometry::failure_nested_interior_rings:
				return PolygonFailureType::NestedInteriorRings;
			case boost::geometry::failure_disconnected_interior:
				return PolygonFailureType::DisconnectedInterior;
			case boost::geometry::failure_intersecting_interiors:
				return PolygonFailureType::IntersectingInteriors;
			case boost::geometry::failure_wrong_corner_order:
				return PolygonFailureType::WrongCornerOrder;
			case boost::geometry::failure_invalid_coordinate:
				return PolygonFailureType::InvalidCoordinate;
			default:
				return PolygonFailureType::Unknown;
			}
		}
	}

	Polygon::Polygon()
		: pImpl{ std::make_unique<PolygonDetail>() }
	{

	}

	Polygon::Polygon(const Polygon& polygon)
		: pImpl{ std::make_unique<PolygonDetail>(*polygon.pImpl) }
	{

	}

	Polygon::Polygon(Polygon&& polygon) noexcept
		: pImpl{ std::move(polygon.pImpl) }
	{

	}

	Polygon::Polygon(const Vec2* outer, const size_t size, Array<Array<Vec2>> holes, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer, size, std::move(holes), skipValidation) }
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer.data(), outer.size(), std::move(holes), skipValidation) }
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, const Array<TriangleIndex>& indices, const RectF& boundingRect, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer.data(), outer.size(), indices, boundingRect, skipValidation) }
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, Array<Array<Vec2>> holes, const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const RectF& boundingRect, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer, std::move(holes), vertices, indices, boundingRect, skipValidation) }
	{

	}

	Polygon::Polygon(std::initializer_list<Vec2> outer, const SkipValidation skipValidation)
		: pImpl{ std::make_unique<PolygonDetail>(outer.begin(), outer.size(), Array<Array<Vec2>>{}, skipValidation) }
	{

	}

	Polygon::~Polygon()
	{

	}

	Polygon& Polygon::operator =(const Polygon& polygon)
	{
		*pImpl = *polygon.pImpl;
		
		return *this;
	}

	Polygon& Polygon::operator =(Polygon&& polygon) noexcept
	{
		pImpl = std::move(polygon.pImpl);

		return *this;
	}

	bool Polygon::isEmpty() const noexcept
	{
		return pImpl->outer().isEmpty();
	}

	bool Polygon::hasHoles() const noexcept
	{
		return (not pImpl->inners().isEmpty());
	}

	size_t Polygon::num_holes() const noexcept
	{
		return pImpl->inners().size();
	}

	const Array<Vec2>& Polygon::outer() const noexcept
	{
		return pImpl->outer();
	}

	const Array<Array<Vec2>>& Polygon::inners() const noexcept
	{
		return pImpl->inners();
	}

	const Array<Float2>& Polygon::vertices() const noexcept
	{
		return pImpl->vertices();
	}

	const Array<TriangleIndex>& Polygon::indices() const noexcept
	{
		return pImpl->indices();
	}

	const RectF& Polygon::boundingRect() const noexcept
	{
		return pImpl->boundingRect();
	}

	size_t Polygon::num_triangles() const noexcept
	{
		return pImpl->indices().size();
	}

	Triangle Polygon::triangle(const size_t index) const
	{
		const auto& indices = pImpl->indices();

		if (index >= indices.size())
		{
			throw std::out_of_range("Polygon::triangle(): index out of range");
		}

		const auto& vertices = pImpl->vertices();
		const auto& triangleIndex = indices[index];
	
		return{ vertices[triangleIndex.i0], vertices[triangleIndex.i1], vertices[triangleIndex.i2] };
	}

	Polygon& Polygon::addHole(Array<Vec2> hole, const SkipValidation skipValidation)
	{
		if (hole.size() < 3)
		{
			return *this;
		}

		Array<Array<Vec2>> inners{ Arg::reserve = (pImpl->inners().size() + 1) };
		{
			inners.append(pImpl->inners());
			inners.push_back(std::move(hole));
		}

		return (*this = Polygon{ pImpl->outer(), std::move(inners), skipValidation });
	}

	Polygon& Polygon::addHoles(Array<Array<Vec2>> holes, const SkipValidation skipValidation)
	{
		holes.remove_if([](const Array<Vec2>& hole) { return (hole.size() < 3); });

		if (not holes)
		{
			return *this;
		}

		Array<Array<Vec2>> inners{ Arg::reserve = (pImpl->inners().size() + holes.size()) };
		{
			inners.append(pImpl->inners());
			inners.append(holes);
		}

		return (*this = Polygon(pImpl->outer(), std::move(inners), skipValidation));
	}

	Polygon Polygon::movedBy(const double x, const double y) const
	{
		return movedBy(Vec2{ x, y });
	}

	Polygon Polygon::movedBy(const Vec2 v) const
	{
		Polygon result(*this);

		result.moveBy(v);

		return result;
	}

	Polygon& Polygon::moveBy(const double x, const double y) noexcept
	{
		return moveBy(Vec2{ x, y });
	}

	Polygon& Polygon::moveBy(const Vec2 v) noexcept
	{
		pImpl->moveBy(v);

		return *this;
	}



	const Polygon& Polygon::draw(const ColorF& color) const
	{
		pImpl->draw(color);

		return *this;
	}



	PolygonFailureType Polygon::Validate(const Vec2* pVertex, const size_t vertexSize, const Array<Array<Vec2>>& holes)
	{
		CwOpenPolygon polygon;
		{
			polygon.outer().assign(pVertex, pVertex + vertexSize);

			polygon.inners().reserve(holes.size());

			for (const auto& hole : holes)
			{
				polygon.inners().emplace_back(hole.begin(), hole.end());
			}
		}

		boost::geometry::validity_failure_type failure;
		bool valid = boost::geometry::is_valid(polygon, failure);

		if (valid)
		{
			// 頂点の重複は boost::geometry::is_valid() で取得できないので、
			// HashSet を使って計算
			if (detail::HasSamePoints(polygon.outer().data(), polygon.outer().size()))
			{
				valid = false;
				failure = boost::geometry::failure_duplicate_points;
			}
		}

		if (valid)
		{
			for (const auto& inner : polygon.inners())
			{
				if (detail::HasSamePoints(inner.data(), inner.size()))
				{
					valid = false;
					failure = boost::geometry::failure_duplicate_points;
				}
			}
		}

		return detail::Convert(failure);
	}
}
