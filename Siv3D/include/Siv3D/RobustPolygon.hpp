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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "PointVector.hpp"

namespace s3d
{
	namespace Robust
	{
		enum class PolygonValidityFailureType
		{
			OK,
			FailureFewPoints,
			FailureWrongTopologicalDimension,
			FailureSpikes,
			FailureDuplicatePoints,
			FailureNotClosed,
			FailureSelfIntersections,
			FailureWrongOrientation,
			FailureInteriorRingsOutside,
			FailureNestedInteriorRings,
			FailureDisconnectedInterior,
			FailureIntersectingInteriors,
			FailureWrongCornerOrder,
			FailureInvalidCoordinate,
			FailureUnknown,
		};

		[[nodiscard]] StringView ToString(PolygonValidityFailureType failureType) noexcept;

		class Polygon
		{
		private:

			class PolygonDetail;

			std::unique_ptr<PolygonDetail> pImpl;

		public:

			using IndexType = uint16;

			Polygon();

			Polygon(const Polygon& polygon);

			Polygon(Polygon&& polygon) noexcept;

			Polygon(const Vec2* outer, size_t size);

			Polygon(const Vec2* outer, size_t size, const Array<Array<Vec2>>& holes);

			Polygon(const Vec2* outer, size_t size, const RectF& boundingRect);

			Polygon(const Vec2* outer, size_t size, const Array<Array<Vec2>>& holes, const RectF& boundingRect);

			explicit Polygon(const Array<Vec2>& outer);

			Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes);

			Polygon(const Array<Vec2>& outer, const RectF& boundingRect);

			Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const RectF& boundingRect);

			Polygon(const Array<Vec2>& outer, const Array<IndexType>& indices, const RectF& boundingRect);

			Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<IndexType>& indices, const RectF& boundingRect);

			Polygon(const Shape2D& shape);

			~Polygon();

			Polygon& operator =(const Polygon& polygon);

			Polygon& operator =(Polygon&& polygon) noexcept;

			[[nodiscard]] static bool IsValid(const Vec2* pVertex, size_t vertexSize);

			[[nodiscard]] static bool IsValid(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes);

			[[nodiscard]] static bool IsValid(const Vec2* pVertex, size_t vertexSize, PolygonValidityFailureType& validityFailureType);

			[[nodiscard]] static bool IsValid(const Vec2* pVertex, size_t vertexSize, const Array<Array<Vec2>>& holes, PolygonValidityFailureType& validityFailureType);

			[[nodiscard]] static bool IsValid(const Array<Vec2>& vertices);

			[[nodiscard]] static bool IsValid(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes);

			[[nodiscard]] static bool IsValid(const Array<Vec2>& vertices, PolygonValidityFailureType& validityFailureType);

			[[nodiscard]] static bool IsValid(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes, PolygonValidityFailureType& validityFailureType);
		};
	}
}
