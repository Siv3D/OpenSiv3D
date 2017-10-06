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
# include "Fwd.hpp"
# include "Vertex2D.hpp"
# include "Array.hpp"
# include "Line.hpp"

namespace s3d
{
	class Shape2D
	{
	private:

		Array<Float2> m_vertices;

		Array<uint32> m_indices;

		Shape2D(uint32 vSize, uint32 iSize);

		Shape2D(uint32 vSize, uint32 iSize, const Float2& offset, uint32 baseIndex);

	public:

		Shape2D() = default;

		Shape2D(Array<Float2> vertices, Array<uint32> indices)
			: m_vertices(std::move(vertices))
			, m_indices(std::move(indices)) {}

		static Shape2D Cross(double r, double width, const Vec2& center = Vec2(0, 0), double angle = 0.0);

		static Shape2D Plus(double r, double width, const Vec2& center = Vec2(0, 0), double angle = 0.0);

		static Shape2D Ngon(uint32 n, double r, const Vec2& center = Vec2(0, 0), double angle = 0.0);

		static Shape2D Pentagon(double r, const Vec2& center = Vec2(0, 0), double angle = 0.0)
		{
			return Ngon(5, r, center, angle);
		}

		static Shape2D Hexagon(double r, const Vec2& center = Vec2(0, 0), double angle = 0.0)
		{
			return Ngon(6, r, center, angle);
		}

		static Shape2D Star(double r, const Vec2& center = Vec2(0, 0), double angle = 0.0);

		static Shape2D NStar(uint32 n, double rOuter, double rInner, const Vec2& center = Vec2(0, 0), double angle = 0.0);

		static Shape2D Arrow(const Vec2& from, const Vec2& to, double width, const Vec2& headSize);

		static Shape2D Arrow(const Line& line, double width, const Vec2& headSize)
		{
			return Arrow(line.begin, line.end, width, headSize);
		}

		static Shape2D Rhombus(double w, double h, const Vec2& center = Vec2(0, 0), double angle = 0.0);

		static Shape2D RectBalloon(const RectF& rect, const Vec2& target, double pointingRootRatio = 0.5);


		//static Shape2D DoubleArrow(const Vec2& a, const Vec2& b, double width, const Vec2& headSize);		

		//static Shape2D DoubleArrow(const Line& line, double width, const Vec2& headSize);	

		// ArrowHead

		// Check

		// Heart

		const Array<Float2>& vertices() const
		{
			return m_vertices;
		}

		const Array<uint32> indices() const
		{
			return m_indices;
		}

		const Shape2D& draw(const ColorF& color = Palette::White) const;

		const Shape2D& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;
	};
}
