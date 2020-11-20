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
# include "Array.hpp"
# include "PointVector.hpp"
# include "TriangleIndex.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	class Polygon;

	class Shape2D
	{
	public:

		Shape2D();

		Shape2D(Array<Float2> vertices, Array<TriangleIndex> indices);

		~Shape2D();

		[[nodiscard]]
		static Shape2D Cross(double r, double width, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D Plus(double r, double width, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D Pentagon(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D Hexagon(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D Ngon(uint32 n, double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D Star(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D NStar(uint32 n, double rOuter, double rInner, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D Arrow(const Vec2& from, const Vec2& to, double width, const Vec2& headSize);

		[[nodiscard]]
		static Shape2D Arrow(const Line& line, double width, const Vec2& headSize);

		[[nodiscard]]
		static Shape2D Rhombus(double w, double h, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		static Shape2D RectBalloon(const RectF& rect, const Vec2& target, double pointingRootRatio = 0.5);

		[[nodiscard]]
		static Shape2D Stairs(const Vec2& base, double w, double h, uint32 steps, bool upStairs = true);

		[[nodiscard]]
		static Shape2D Heart(double r, const Vec2& center = Vec2{ 0, 0 }, double angle = 0.0);

		[[nodiscard]]
		const Array<Float2>& vertices() const noexcept;

		[[nodiscard]] 
		const Array<TriangleIndex> indices() const noexcept;

		const Shape2D& draw(const ColorF& color = Palette::White) const;

		const Shape2D& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		[[nodiscard]]
		Polygon asPolygon() const;

	private:

		Array<Float2> m_vertices;

		Array<TriangleIndex> m_indices;
	};
}

# include "detail/Shape2D.ipp"
