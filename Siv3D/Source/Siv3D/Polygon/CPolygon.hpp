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

# pragma once

// boost 1.64.0 workaround
# ifndef _HAS_AUTO_PTR_ETC
#	define _HAS_AUTO_PTR_ETC 1
# endif

# include <boost/geometry/geometries/geometries.hpp>
# include <boost/geometry/geometries/register/point.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Triangle.hpp>

using gPolygon = boost::geometry::model::polygon<s3d::Vec2, false, false, s3d::Array, s3d::Array>;
using gRing = boost::geometry::model::ring<s3d::Vec2, false, false, s3d::Array>;
BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Vec2, double, boost::geometry::cs::cartesian, x, y)

namespace s3d
{
	class Polygon::CPolygon
	{
	private:

		gPolygon m_polygon;

		RectF m_boundingRect{ 0 };

		Array<Array<Vec2>> m_holes;

		Array<Float2> m_vertices;

		Array<uint32> m_indices;

	public:

		CPolygon();

		CPolygon(const Vec2* pVertex, size_t vertexSize, Array<Array<Vec2>> holes);

		CPolygon(const Float2* pVertex, size_t vertexSize, const Array<uint32>& indices);

		void copyFrom(CPolygon& other);

		void moveFrom(CPolygon& other);

		void moveBy(double x, double y);

		//double area() const;

		//double perimeter() const;

		//Vec2 centroid() const;

		bool intersects(const CPolygon& other) const;

		const Array<Vec2>& outer() const;

		const Array<Array<Vec2>>& inners() const;

		const RectF& boundingRect() const;

		const Array<Float2>& vertices() const;

		const Array<uint32>& indices() const;

		void draw(const ColorF& color) const;
	};
}
