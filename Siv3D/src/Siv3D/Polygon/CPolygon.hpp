//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

// boost 1.65.1 workaround
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
using gLineString = boost::geometry::model::linestring<s3d::Vec2, s3d::Array>;
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

		CPolygon(const Vec2* pOuterVertex, size_t vertexSize, const Array<uint32>& indices, const RectF& boundingRect);

		CPolygon(const Float2* pOuterVertex, size_t vertexSize, const Array<uint32>& indices);

		void copyFrom(CPolygon& other);

		void moveFrom(CPolygon& other);

		void moveBy(double x, double y);

		void rotateAt(const Vec2& pos, double angle);

		double area() const;

		double perimeter() const;

		Vec2 centroid() const;
		
		Polygon calculateConvexHull() const;

		Polygon calculateBuffer(double distance) const;

		Polygon calculateRoundBuffer(double distance) const;

		Polygon simplified(double maxDistance) const;

		bool append(const Polygon& polygon);

		bool intersects(const CPolygon& other) const;

		const Array<Vec2>& outer() const;

		const Array<Array<Vec2>>& inners() const;

		const RectF& boundingRect() const;

		const Array<Float2>& vertices() const;

		const Array<uint32>& indices() const;

		void draw(const ColorF& color) const;

		void draw(const Vec2& offset, const ColorF& color) const;

		void drawFrame(double thickness, const ColorF& color) const;

		void drawFrame(const Vec2& offset, double thickness, const ColorF& color) const;

		const gPolygon& getPolygon() const;
	};
}
