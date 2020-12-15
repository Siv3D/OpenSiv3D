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
# include <boost/geometry/geometries/geometries.hpp>
# include <boost/geometry/geometries/register/point.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/2DShapes.hpp>

BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Point, s3d::int32, boost::geometry::cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Float2, float, boost::geometry::cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Vec2, double, boost::geometry::cs::cartesian, x, y)

namespace s3d
{
	using CwOpenPolygon	= boost::geometry::model::polygon<Vec2, false, false, Array, Array>;
	using CWOpenRing	= boost::geometry::model::ring<Vec2, false, false, Array>;
	using GLineString	= boost::geometry::model::linestring<Vec2, Array>;

	class Polygon::PolygonDetail
	{
	private:

		CwOpenPolygon m_polygon;

		Array<Array<Vec2>> m_holes;

		Array<Float2> m_vertices;

		Array<TriangleIndex> m_indices;

		RectF m_boundingRect{ 0 };

	public:

		PolygonDetail();

		PolygonDetail(const Vec2* pVertex, size_t vertexSize, Array<Array<Vec2>> holes, SkipValidation skipValidation);

		PolygonDetail(const Vec2* pOuterVertex, size_t vertexSize, Array<TriangleIndex> indices, const RectF& boundingRect, SkipValidation skipValidation);
	
		PolygonDetail(const Array<Vec2>& outer, Array<Array<Vec2>> holes, Array<Float2> vertices, Array<TriangleIndex> indices, const RectF& boundingRect, SkipValidation skipValidation);

		PolygonDetail(const Float2* pOuterVertex, size_t vertexSize, Array<TriangleIndex> indices);

		[[nodiscard]]
		const Array<Vec2>& outer() const noexcept;

		[[nodiscard]]
		const Array<Array<Vec2>>& inners() const noexcept;

		[[nodiscard]]
		const Array<Float2>& vertices() const noexcept;

		[[nodiscard]]
		const Array<TriangleIndex>& indices() const noexcept;

		[[nodiscard]]
		const RectF& boundingRect() const noexcept;

		void moveBy(Vec2 v) noexcept;



		double area() const noexcept;

		double perimeter() const noexcept;

		Vec2 centroid() const;

		Polygon calculateConvexHull() const;

		Polygon calculateBuffer(double distance) const;

		Polygon calculateRoundBuffer(double distance) const;

		Polygon simplified(double maxDistance) const;


		void draw(const ColorF& color) const;

		void drawFrame(double thickness, const ColorF& color) const;



		const CwOpenPolygon& getPolygon() const noexcept;
	};
}
