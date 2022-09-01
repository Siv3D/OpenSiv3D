//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>

# ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wunused-parameter"
#	pragma clang diagnostic ignored "-Wdeprecated-copy-with-user-provided-copy"
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4457)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4819)
# include <boost/geometry.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# ifdef __clang__
#	pragma clang diagnostic pop
# endif

# include <boost/geometry/geometries/register/point.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/2DShapes.hpp>

# ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
# endif

BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Point, s3d::int32, boost::geometry::cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Float2, float, boost::geometry::cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_POINT_2D(s3d::Vec2, double, boost::geometry::cs::cartesian, x, y)

# ifdef __GNUC__
#	pragma GCC diagnostic pop
# endif

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

		RectF m_boundingRect = RectF::Empty();

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

		void rotateAt(Vec2 pos, double angle);

		void transform(double s, double c, const Vec2& pos);

		void scale(double s);

		void scale(Vec2 s);

		void scaleAt(Vec2 pos, double s);

		void scaleAt(Vec2 pos, Vec2 s);

		double area() const noexcept;

		double perimeter() const noexcept;

		Vec2 centroid() const;

		Polygon computeConvexHull() const;

		Polygon calculateBuffer(double distance) const;

		Polygon calculateRoundBuffer(double distance) const;

		Polygon simplified(double maxDistance) const;

		bool append(const RectF& other);

		bool append(const Polygon& other);

		bool intersects(const Line& other) const;

		bool intersects(const RectF& other) const;

		bool intersects(const PolygonDetail& other) const;


		void draw(const ColorF& color) const;

		void draw(const Vec2& offset, const ColorF& color) const;

		void drawFrame(double thickness, const ColorF& color) const;

		void drawFrame(const Vec2& offset, double thickness, const ColorF& color) const;

		void drawTransformed(double s, double c, const Vec2& pos, const ColorF& color) const;

		const CwOpenPolygon& getPolygon() const noexcept;
	};
}
