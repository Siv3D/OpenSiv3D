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

		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Circle& b);
		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Ellipse& b);

		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Circle& b);
		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Ellipse& b);
		
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Ellipse& b);
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Circle& b);

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Ellipse& b);
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Circle& b);

		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier2& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier3& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const RectF& b);

		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Line& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier2& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier3& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Rect& b);
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RectF& b);
	}
}
