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
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Array.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 二次元図形の作成と幾何計算
	/// </summary>
	namespace Geometry2D
	{
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const Line& a, const RectF& b);
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Circle& b);
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Ellipse& b);
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const LineString& b);

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Circle& b);
		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Ellipse& b);

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Circle& b);
		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Ellipse& b);
		
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Ellipse& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const LineString& b);

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Ellipse& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const LineString& b);

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier2& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier3& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const RectF& b);
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const Ellipse& b);
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const Quad& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const LineString& b);

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier2& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier3& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RectF& b);
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Ellipse& b);
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const LineString& b);

		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Line& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier2& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier3& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Rect& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const RectF& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Ellipse& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const LineString& b);

		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Line& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier2& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier3& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Rect& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const RectF& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Ellipse& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const LineString& b);

		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Line& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Bezier2& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Bezier3& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Rect& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const RectF& b);
		Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Ellipse& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const LineString& b);

		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Line& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier2& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier3& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Rect& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const RectF& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Circle& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Ellipse& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Triangle& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Quad& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Polygon& b);
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const LineString& b);
	}
}
