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
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Triangle.hpp>

BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Vec2, double, boost::geometry::cs::cartesian, x, y)

namespace s3d
{
	using gPolygon		= boost::geometry::model::polygon<Vec2, false, false, Array, Array>;
	using gRing			= boost::geometry::model::ring<Vec2, false, false, Array>;
	using gLineString	= boost::geometry::model::linestring<Vec2, Array>;
	using gMultiPoint	= boost::geometry::model::multi_point<Vec2>;

	class Polygon::PolygonDetail
	{
	private:

		gPolygon m_polygon;

		RectF m_boundingRect{ 0 };

		Array<Array<Vec2>> m_holes;

		Array<Float2> m_vertices;

		Array<uint16> m_indices;

	public:

		PolygonDetail();

		PolygonDetail(const Vec2* pVertex, size_t vertexSize, Array<Array<Vec2>> holes, bool checkValidity);

		PolygonDetail(const Vec2* pOuterVertex, size_t vertexSize, const Array<uint16>& indices, const RectF& boundingRect, bool checkValidity);

		PolygonDetail(const Float2* pOuterVertex, size_t vertexSize, const Array<uint16>& indices, bool checkValidity);

		PolygonDetail(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<uint16>& indices, const RectF& boundingRect, bool checkValidity);

		void copyFrom(const PolygonDetail& other);

		void moveFrom(PolygonDetail& other);

		void moveBy(double x, double y);

		void rotateAt(const Vec2& pos, double angle);

		void transform(double s, double c, const Vec2& pos);

		void scale(double s);

		void scale(const Vec2& s);

		double area() const;

		double perimeter() const;

		Vec2 centroid() const;

		Polygon calculateConvexHull() const;

		Polygon calculateBuffer(double distance) const;

		Polygon calculateRoundBuffer(double distance) const;

		Polygon simplified(double maxDistance) const;

		bool append(const Polygon& polygon);

		bool intersects(const PolygonDetail& other) const;

		const Array<Vec2>& outer() const;

		const Array<Array<Vec2>>& inners() const;

		const RectF& boundingRect() const;

		const Array<Float2>& vertices() const;

		const Array<uint16>& indices() const;

		void draw(const ColorF& color) const;

		void draw(const Vec2& offset, const ColorF& color) const;

		void drawFrame(double thickness, const ColorF& color) const;

		void drawFrame(const Vec2& offset, double thickness, const ColorF& color) const;

		void drawTransformed(double s, double c, const Vec2& pos, const ColorF& color) const;

		const gPolygon& getPolygon() const;
	};
}
