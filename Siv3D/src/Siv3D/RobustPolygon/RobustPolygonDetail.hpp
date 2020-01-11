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
# include <boost/geometry/geometries/geometries.hpp>
# include <boost/geometry/geometries/register/point.hpp>
# include <Siv3D/RobustPolygon.hpp>

BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Vec2, double, boost::geometry::cs::cartesian, x, y)

namespace s3d
{
	namespace Robust
	{
		using CwOpenPolygon = boost::geometry::model::polygon<Vec2, false, false, Array, Array>;
		using CwOpenRing = boost::geometry::model::ring<Vec2, false, false, Array>;

		class Polygon::PolygonDetail
		{
		private:

		public:

			PolygonDetail();

			PolygonDetail(const Vec2* pOuterVertex, size_t vertexSize, Array<Array<Vec2>> holes);

			PolygonDetail(const Vec2* pOuterVertex, size_t vertexSize, Array<Array<Vec2>> holes, const RectF& boundingRect);
		
			PolygonDetail(const Float2* pOuterVertex, size_t vertexSize, const Array<uint16>& indices);

			//PolygonDetail(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<uint16>& indices, const RectF& boundingRect);
		};
	}
}
