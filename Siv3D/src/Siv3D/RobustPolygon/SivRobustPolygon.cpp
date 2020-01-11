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

# include <Siv3D/RobustPolygon.hpp>
# include <Siv3D/Shape2D.hpp>
# include "RobustPolygonDetail.hpp"

namespace s3d
{
	namespace Robust
	{
		Polygon::Polygon()
			: pImpl(std::make_unique<PolygonDetail>())
		{

		}

		//Polygon(const Polygon& polygon);

		//Polygon(Polygon&& polygon) noexcept;;

		Polygon::Polygon(const Vec2* outer, const size_t size)
			: pImpl(std::make_unique<PolygonDetail>(outer, size, Array<Array<Vec2>>{}))
		{

		}

		Polygon::Polygon(const Vec2* outer, const size_t size, const Array<Array<Vec2>>& holes)
			: pImpl(std::make_unique<PolygonDetail>(outer, size, holes))
		{

		}

		Polygon::Polygon(const Vec2* outer, const size_t size, const RectF& boundingRect)
			: pImpl(std::make_unique<PolygonDetail>(outer, size, Array<Array<Vec2>>{}, boundingRect))
		{

		}

		Polygon::Polygon(const Vec2* outer, const size_t size, const Array<Array<Vec2>>& holes, const RectF& boundingRect)
			: pImpl(std::make_unique<PolygonDetail>(outer, size, holes, boundingRect))
		{

		}

		Polygon::Polygon(const Array<Vec2>& outer)
			: Polygon(outer.data(), outer.size())
		{

		}

		Polygon::Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes)
			: Polygon(outer.data(), outer.size(), holes)
		{

		}

		Polygon::Polygon(const Array<Vec2>& outer, const RectF& boundingRect)
			: Polygon(outer.data(), outer.size(), boundingRect)
		{

		}

		Polygon::Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const RectF& boundingRect)
			: Polygon(outer.data(), outer.size(), holes, boundingRect)
		{

		}

		//Polygon::Polygon(const Array<Vec2>& outer, const Array<IndexType>& indices, const RectF& boundingRect)
		//	: Polygon(outer.data(), outer.size(), Array<Array<Vec2>>{}, boundingRect)
		//{

		//}

		//Polygon::Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<IndexType>& indices, const RectF& boundingRect)
		//	: pImpl(std::make_unique<PolygonDetail>(outer, size, holes, boundingRect))
		//{

		//}

		Polygon::Polygon(const Shape2D& shape)
			: pImpl(std::make_unique<PolygonDetail>(shape.vertices().data(), shape.vertices().size(), shape.indices()))
		{

		}

		Polygon::~Polygon()
		{

		}

		//Polygon& Polygon::operator =(const Polygon& polygon);

		//Polygon& Polygon::operator =(Polygon&& polygon) noexcept;



	}
}
