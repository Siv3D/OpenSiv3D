//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "RobustPolygonDetail.hpp"
# include <boost/geometry/algorithms/is_valid.hpp>
# include <Siv3D/HashSet.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]] Robust::PolygonValidityFailureType Convert(boost::geometry::validity_failure_type failure) noexcept
		{
			// https://www.boost.org/doc/libs/1_72_0/libs/geometry/doc/html/geometry/reference/enumerations/validity_failure_type.html
			switch (failure)
			{
			case boost::geometry::no_failure:
				return Robust::PolygonValidityFailureType::OK;
			case boost::geometry::failure_few_points:
				return Robust::PolygonValidityFailureType::FailureFewPoints;
			case boost::geometry::failure_wrong_topological_dimension:
				return Robust::PolygonValidityFailureType::FailureWrongTopologicalDimension;
			case boost::geometry::failure_spikes:
				return Robust::PolygonValidityFailureType::FailureSpikes;
			case boost::geometry::failure_duplicate_points:
				return Robust::PolygonValidityFailureType::FailureDuplicatePoints;
			case boost::geometry::failure_not_closed:
				return Robust::PolygonValidityFailureType::FailureNotClosed;
			case boost::geometry::failure_self_intersections:
				return Robust::PolygonValidityFailureType::FailureSelfIntersections;
			case boost::geometry::failure_wrong_orientation:
				return Robust::PolygonValidityFailureType::FailureWrongOrientation;
			case boost::geometry::failure_interior_rings_outside:
				return Robust::PolygonValidityFailureType::FailureInteriorRingsOutside;
			case boost::geometry::failure_nested_interior_rings:
				return Robust::PolygonValidityFailureType::FailureNestedInteriorRings;
			case boost::geometry::failure_disconnected_interior:
				return Robust::PolygonValidityFailureType::FailureDisconnectedInterior;
			case boost::geometry::failure_intersecting_interiors:
				return Robust::PolygonValidityFailureType::FailureIntersectingInteriors;
			case boost::geometry::failure_wrong_corner_order:
				return Robust::PolygonValidityFailureType::FailureWrongCornerOrder;
			case boost::geometry::failure_invalid_coordinate:
				return Robust::PolygonValidityFailureType::FailureInvalidCoordinate;
			default:
				return Robust::PolygonValidityFailureType::FailureUnknown;
			}
		}
	}

	namespace Robust
	{
		StringView ToString(PolygonValidityFailureType failureType) noexcept
		{
			switch (failureType)
			{
			case PolygonValidityFailureType::OK:
				return U"OK"_sv;
			case PolygonValidityFailureType::FailureFewPoints:
				return U"FailureFewPoints"_sv;
			case PolygonValidityFailureType::FailureWrongTopologicalDimension:
				return U"FailureWrongTopologicalDimension"_sv;
			case PolygonValidityFailureType::FailureSpikes:
				return U"FailureSpikes"_sv;
			case PolygonValidityFailureType::FailureDuplicatePoints:
				return U"FailureDuplicatePoints"_sv;
			case PolygonValidityFailureType::FailureNotClosed:
				return U"FailureNotClosed"_sv;
			case PolygonValidityFailureType::FailureSelfIntersections:
				return U"FailureSelfIntersections"_sv;
			case PolygonValidityFailureType::FailureWrongOrientation:
				return U"FailureWrongOrientation"_sv;
			case PolygonValidityFailureType::FailureInteriorRingsOutside:
				return U"FailureInteriorRingsOutside"_sv;
			case PolygonValidityFailureType::FailureNestedInteriorRings:
				return U"FailureNestedInteriorRings"_sv;
			case PolygonValidityFailureType::FailureDisconnectedInterior:
				return U"FailureDisconnectedInterior"_sv;
			case PolygonValidityFailureType::FailureIntersectingInteriors:
				return U"FailureIntersectingInteriors"_sv;
			case PolygonValidityFailureType::FailureWrongCornerOrder:
				return U"FailureWrongCornerOrder"_sv;
			case PolygonValidityFailureType::FailureInvalidCoordinate:
				return U"FailureInvalidCoordinate"_sv;
			case PolygonValidityFailureType::FailureUnknown:
			default:
				return U"FailureUnknown"_sv;
			}
		}


		bool Polygon::IsValid(const Vec2* pVertex, const size_t vertexSize)
		{
			PolygonValidityFailureType unused;
			return IsValid(pVertex, vertexSize, unused);
		}

		bool Polygon::IsValid(const Vec2* pVertex, const size_t vertexSize, const Array<Array<Vec2>>& holes)
		{
			PolygonValidityFailureType unused;
			return IsValid(pVertex, vertexSize, holes, unused);
		}

		bool Polygon::IsValid(const Vec2* pVertex, const size_t vertexSize, PolygonValidityFailureType& validityFailureType)
		{
			CwOpenPolygon polygon;
			polygon.outer().assign(pVertex, pVertex + vertexSize);

			boost::geometry::validity_failure_type failure;
			bool valid = boost::geometry::is_valid(polygon, failure);

			if (valid)
			{
				// 頂点の重複は boost::geometry::is_valid() で取得できないので、
				// HashSet を使って計算
				if (HashSet<Vec2>(pVertex, pVertex + vertexSize).size() != vertexSize)
				{
					valid = false;
					failure = boost::geometry::failure_duplicate_points;
				}
			}

			validityFailureType = detail::Convert(failure);

			return valid;
		}

		bool Polygon::IsValid(const Vec2* pVertex, const size_t vertexSize, const Array<Array<Vec2>>& holes, PolygonValidityFailureType& validityFailureType)
		{
			CwOpenPolygon polygon;
			polygon.outer().assign(pVertex, pVertex + vertexSize);

			for (const auto& hole : holes)
			{
				polygon.inners().emplace_back(hole.begin(), hole.end());
			}

			boost::geometry::validity_failure_type failure;
			bool valid = boost::geometry::is_valid(polygon, failure);

			if (valid)
			{
				// 頂点の重複は boost::geometry::is_valid() で取得できないので、
				// HashSet を使って計算
				if (HashSet<Vec2>(pVertex, pVertex + vertexSize).size() != vertexSize)
				{
					valid = false;
					failure = boost::geometry::failure_duplicate_points;
				}
			}

			validityFailureType = detail::Convert(failure);

			return valid;
		}

		bool Polygon::IsValid(const Array<Vec2>& vertices)
		{
			return IsValid(vertices.data(), vertices.size());
		}

		bool Polygon::IsValid(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
		{
			return IsValid(vertices.data(), vertices.size(), holes);
		}

		bool Polygon::IsValid(const Array<Vec2>& vertices, PolygonValidityFailureType& validityFailureType)
		{
			return IsValid(vertices.data(), vertices.size(), validityFailureType);
		}

		bool Polygon::IsValid(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes, PolygonValidityFailureType& validityFailureType)
		{
			return IsValid(vertices.data(), vertices.size(), holes, validityFailureType);
		}


		Polygon::PolygonDetail::PolygonDetail()
		{

		}

		Polygon::PolygonDetail::PolygonDetail(const Vec2* pOuterVertex, const size_t vertexSize, Array<Array<Vec2>> holes)
		{
			//if (!IsValid(pOuterVertex, vertexSize))
			//{
			//	return;
			//}

		}

		//Polygon::PolygonDetail::PolygonDetail(const Vec2* pOuterVertex, size_t vertexSize, Array<Array<Vec2>> holes, const RectF& boundingRect);

		//Polygon::PolygonDetail::PolygonDetail(const Float2* pOuterVertex, size_t vertexSize, const Array<uint16>& indices);
	}
}
