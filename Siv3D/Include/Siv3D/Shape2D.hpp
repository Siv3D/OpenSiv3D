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

namespace s3d
{
	struct Shape2D
	{
		/// <summary>
		/// 頂点バッファ
		/// </summary>
		Array<Vertex2D> vertices;

		/// <summary>
		/// インデックスバッファ
		/// </summary>
		/// <remarks>
		/// サイズは 3 の倍数でなければなりません。
		/// </remarks>
		Array<uint32> indices;

		Shape2D() = default;

		Shape2D(uint32 vertexSize, uint32 indexSize)
			: vertices(vertexSize)
			, indices(indexSize) {}

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

		static Shape2D Arrow(const Vec2& from, const Vec2& to, double thickness, const Vec2& headSize);

		static Shape2D DoubleArrow(const Vec2& a, const Vec2& b, double thickness, const Vec2& headSize);		

		// ArrowHead

		// Check
	};
}
