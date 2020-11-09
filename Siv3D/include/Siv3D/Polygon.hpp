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

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "PolygonFailureType.hpp"
# include "Vertex2D.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class Polygon
	{
	public:

		using IndexType = Vertex2D::IndexType;

		Polygon();

		Polygon(const Polygon& polygon);

		Polygon(Polygon&& polygon) noexcept;

		Polygon(const Vec2* outer, size_t size, const Array<Array<Vec2>>& holes = {}, CheckValidity checkValidity = CheckValidity::No);

		explicit Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes = {}, CheckValidity checkValidity = CheckValidity::No);

		Polygon(const Array<Vec2>& outer, const Array<IndexType>& indices, const RectF& boundingRect, CheckValidity checkValidity = CheckValidity::No);

		Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<IndexType>& indices, const RectF& boundingRect, CheckValidity checkValidity = CheckValidity::No);

		//Polygon(const Shape2D& shape);

		explicit Polygon(std::initializer_list<Vec2> outer, CheckValidity checkValidity = CheckValidity::No);

		~Polygon();

	private:

		class PolygonDetail;

		std::unique_ptr<PolygonDetail> pImpl;
	};
}
