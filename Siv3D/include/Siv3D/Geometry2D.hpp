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
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const Rect& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const RectF& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const Circle& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const Ellipse& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const Polygon& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Line& a, const LineString& b);

		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Circle& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Ellipse& b);

		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Circle& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Ellipse& b);
		
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const Line& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const Ellipse& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const Polygon& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Rect& a, const LineString& b);

		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const Line& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const Ellipse& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const Polygon& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RectF& a, const LineString& b);

		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Line& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier2& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier3& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Rect& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const RectF& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Ellipse& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const RoundRect& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const Polygon& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Circle& a, const LineString& b);

		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Line& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier2& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier3& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Rect& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RectF& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Ellipse& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Polygon& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const LineString& b);

		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Line& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier2& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier3& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Rect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const RectF& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Ellipse& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Polygon& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Triangle& a, const LineString& b);

		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Line& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier2& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier3& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Rect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const RectF& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Ellipse& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const Polygon& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Quad& a, const LineString& b);

		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Line& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Bezier2& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Bezier3& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Rect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const RectF& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Ellipse& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Polygon& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const LineString& b);

		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Line& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Bezier2& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Bezier3& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Rect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const RectF& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Circle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Ellipse& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Polygon& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const Polygon& a, const LineString& b);

		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Line& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier2& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier3& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Rect& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const RectF& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Circle& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Ellipse& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Triangle& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Quad& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const RoundRect& b);
		//[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const Polygon& b);
		[[nodiscard]] Optional<Array<Vec2>> IntersectAt(const LineString& a, const LineString& b);


		[[nodiscard]] double Distance(const Point& a, const Point&			b) noexcept;
		[[nodiscard]] double Distance(const Point& a, const Vec2&			b) noexcept;
		[[nodiscard]] double Distance(const Point& a, const Line&			b);
		//[[nodiscard]] double Distance(const Point& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const Point& a, const Bezier3&		b);
		[[nodiscard]] double Distance(const Point& a, const Rect&			b);
		[[nodiscard]] double Distance(const Point& a, const RectF&			b);
		[[nodiscard]] double Distance(const Point& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Point& a, const Ellipse&		b);
		[[nodiscard]] double Distance(const Point& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Point& a, const Quad&			b);
		[[nodiscard]] double Distance(const Point& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Point& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const Point& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Point& a, const LineString&		b);

		[[nodiscard]] double Distance(const Vec2& a, const Point&			b) noexcept;
		[[nodiscard]] double Distance(const Vec2& a, const Vec2&			b) noexcept;
		[[nodiscard]] double Distance(const Vec2& a, const Line&			b);
		//[[nodiscard]] double Distance(const Vec2& a, const Bezier2&			b);
		//[[nodiscard]] double Distance(const Vec2& a, const Bezier3&			b);
		[[nodiscard]] double Distance(const Vec2& a, const Rect&			b);
		[[nodiscard]] double Distance(const Vec2& a, const RectF&			b);
		[[nodiscard]] double Distance(const Vec2& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Vec2& a, const Ellipse&			b);
		[[nodiscard]] double Distance(const Vec2& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Vec2& a, const Quad&			b);
		[[nodiscard]] double Distance(const Vec2& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Vec2& a, const Polygon&			b);
		//[[nodiscard]] double Distance(const Vec2& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Vec2& a, const LineString&		b);

		[[nodiscard]] double Distance(const Line& a, const Point&			b);
		[[nodiscard]] double Distance(const Line& a, const Vec2&			b);
		[[nodiscard]] double Distance(const Line& a, const Line&			b);
		//[[nodiscard]] double Distance(const Line& a, const Bezier2&			b);
		//[[nodiscard]] double Distance(const Line& a, const Bezier3&			b);
		[[nodiscard]] double Distance(const Line& a, const Rect&			b);
		[[nodiscard]] double Distance(const Line& a, const RectF&			b);
		[[nodiscard]] double Distance(const Line& a, const Circle&		b);
		//[[nodiscard]] double Distance(const Line& a, const Ellipse&			b);
		[[nodiscard]] double Distance(const Line& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Line& a, const Quad&			b);
		//[[nodiscard]] double Distance(const Line& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Line& a, const Polygon&			b);
		//[[nodiscard]] double Distance(const Line& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Line& a, const LineString&		b);

		[[nodiscard]] double Distance(const Rect& a, const Point&			b);
		[[nodiscard]] double Distance(const Rect& a, const Vec2&			b);
		[[nodiscard]] double Distance(const Rect& a, const Line&			b);
		//[[nodiscard]] double Distance(const Rect& a, const Bezier2&			b);
		//[[nodiscard]] double Distance(const Rect& a, const Bezier3&			b);
		[[nodiscard]] double Distance(const Rect& a, const Rect&			b);
		[[nodiscard]] double Distance(const Rect& a, const RectF&			b);
		[[nodiscard]] double Distance(const Rect& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Rect& a, const Ellipse&			b);
		[[nodiscard]] double Distance(const Rect& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Rect& a, const Quad&			b);
		//[[nodiscard]] double Distance(const Rect& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Rect& a, const Polygon&			b);
		//[[nodiscard]] double Distance(const Rect& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Rect& a, const LineString&		b);
		
		[[nodiscard]] double Distance(const RectF& a, const Point&			b);
		[[nodiscard]] double Distance(const RectF& a, const Vec2&			b);
		[[nodiscard]] double Distance(const RectF& a, const Line&			b);
		//[[nodiscard]] double Distance(const RectF& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const RectF& a, const Bezier3&		b);
		[[nodiscard]] double Distance(const RectF& a, const Rect&			b);
		[[nodiscard]] double Distance(const RectF& a, const RectF&			b);
		[[nodiscard]] double Distance(const RectF& a, const Circle&			b);
		//[[nodiscard]] double Distance(const RectF& a, const Ellipse&		b);
		[[nodiscard]] double Distance(const RectF& a, const Triangle&		b);
		[[nodiscard]] double Distance(const RectF& a, const Quad&			b);
		//[[nodiscard]] double Distance(const RectF& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const RectF& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const RectF& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const RectF& a, const LineString&		b);

		[[nodiscard]] double Distance(const Circle& a, const Point&			b);
		[[nodiscard]] double Distance(const Circle& a, const Vec2&			b);
		[[nodiscard]] double Distance(const Circle& a, const Line&			b);
		//[[nodiscard]] double Distance(const Circle& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const Circle& a, const Bezier3&		b);
		[[nodiscard]] double Distance(const Circle& a, const Rect&			b);
		[[nodiscard]] double Distance(const Circle& a, const RectF&			b);
		[[nodiscard]] double Distance(const Circle& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Circle& a, const Ellipse&		b);
		[[nodiscard]] double Distance(const Circle& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Circle& a, const Quad&			b);
		[[nodiscard]] double Distance(const Circle& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Circle& a, const Polygon&			b);
		//[[nodiscard]] double Distance(const Circle& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Circle& a, const LineString&		b);

		//[[nodiscard]] double Distance(const Ellipse& a, const Point&			b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Vec2&			b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Line&			b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Bezier3&		b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Rect&			b);
		//[[nodiscard]] double Distance(const Ellipse& a, const RectF&			b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Ellipse&		b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Triangle&		b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Quad&			b);
		//[[nodiscard]] double Distance(const Ellipse& a, const RoundRect&		b);
		//[[nodiscard]] double Distance(const Ellipse& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const Ellipse& a, const MultiPolygon&	b);
		//[[nodiscard]] double Distance(const Ellipse& a, const LineString&		b);

		[[nodiscard]] double Distance(const Triangle& a, const Point&			b);
		[[nodiscard]] double Distance(const Triangle& a, const Vec2&			b);
		[[nodiscard]] double Distance(const Triangle& a, const Line&			b);
		//[[nodiscard]] double Distance(const Triangle& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const Triangle& a, const Bezier3&		b);
		[[nodiscard]] double Distance(const Triangle& a, const Rect&			b);
		[[nodiscard]] double Distance(const Triangle& a, const RectF&			b);
		[[nodiscard]] double Distance(const Triangle& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Triangle& a, const Ellipse&		b);
		[[nodiscard]] double Distance(const Triangle& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Triangle& a, const Quad&			b);
		//[[nodiscard]] double Distance(const Triangle& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Triangle& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const Triangle& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Triangle& a, const LineString&		b);

		[[nodiscard]] double Distance(const Quad& a, const Point&			b);
		[[nodiscard]] double Distance(const Quad& a, const Vec2&			b);
		[[nodiscard]] double Distance(const Quad& a, const Line&			b);
		//[[nodiscard]] double Distance(const Quad& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const Quad& a, const Bezier3&		b);
		[[nodiscard]] double Distance(const Quad& a, const Rect&			b);
		[[nodiscard]] double Distance(const Quad& a, const RectF&			b);
		[[nodiscard]] double Distance(const Quad& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Quad& a, const Ellipse&		b);
		[[nodiscard]] double Distance(const Quad& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Quad& a, const Quad&			b);
		//[[nodiscard]] double Distance(const Quad& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Quad& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const Quad& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Quad& a, const LineString&		b);

		[[nodiscard]] double Distance(const RoundRect& a, const Point&		b);
		[[nodiscard]] double Distance(const RoundRect& a, const Vec2&			b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Line&			b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Bezier3&		b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Rect&			b);
		//[[nodiscard]] double Distance(const RoundRect& a, const RectF&			b);
		[[nodiscard]] double Distance(const RoundRect& a, const Circle&		b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Ellipse&		b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Triangle&		b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Quad&			b);
		//[[nodiscard]] double Distance(const RoundRect& a, const RoundRect&		b);
		//[[nodiscard]] double Distance(const RoundRect& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const RoundRect& a, const MultiPolygon&	b);
		//[[nodiscard]] double Distance(const RoundRect& a, const LineString&		b);

		[[nodiscard]] double Distance(const Polygon& a, const Point&			b);
		[[nodiscard]] double Distance(const Polygon& a, const Vec2&			b);
		[[nodiscard]] double Distance(const Polygon& a, const Line&			b);
		//[[nodiscard]] double Distance(const Polygon& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const Polygon& a, const Bezier3&		b);
		[[nodiscard]] double Distance(const Polygon& a, const Rect&			b);
		[[nodiscard]] double Distance(const Polygon& a, const RectF&			b);
		[[nodiscard]] double Distance(const Polygon& a, const Circle&			b);
		//[[nodiscard]] double Distance(const Polygon& a, const Ellipse&		b);
		[[nodiscard]] double Distance(const Polygon& a, const Triangle&		b);
		[[nodiscard]] double Distance(const Polygon& a, const Quad&			b);
		//[[nodiscard]] double Distance(const Polygon& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const Polygon& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const Polygon& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const Polygon& a, const LineString&		b);

		//[[nodiscard]] double Distance(const MultiPolygon& a, const Point&			b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Vec2&			b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Line&			b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Bezier3&		b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Rect&			b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const RectF&			b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Circle&			b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Ellipse&		b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Triangle&		b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Quad&			b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const RoundRect&		b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const MultiPolygon&	b);
		//[[nodiscard]] double Distance(const MultiPolygon& a, const LineString&		b);

		[[nodiscard]] double Distance(const LineString& a, const Point&			b);
		[[nodiscard]] double Distance(const LineString& a, const Vec2&			b);
		[[nodiscard]] double Distance(const LineString& a, const Line&			b);
		//[[nodiscard]] double Distance(const LineString& a, const Bezier2&		b);
		//[[nodiscard]] double Distance(const LineString& a, const Bezier3&		b);
		[[nodiscard]] double Distance(const LineString& a, const Rect&			b);
		[[nodiscard]] double Distance(const LineString& a, const RectF&			b);
		[[nodiscard]] double Distance(const LineString& a, const Circle&			b);
		//[[nodiscard]] double Distance(const LineString& a, const Ellipse&		b);
		[[nodiscard]] double Distance(const LineString& a, const Triangle&		b);
		[[nodiscard]] double Distance(const LineString& a, const Quad&			b);
		//[[nodiscard]] double Distance(const LineString& a, const RoundRect&		b);
		[[nodiscard]] double Distance(const LineString& a, const Polygon&		b);
		//[[nodiscard]] double Distance(const LineString& a, const MultiPolygon&	b);
		[[nodiscard]] double Distance(const LineString& a, const LineString&		b);

		//[[nodiscard]] bool Center(const Point& a) noexcept;
		//[[nodiscard]] bool Center(const Vec2& a) noexcept;
		//[[nodiscard]] bool Center(const Line& a) noexcept;
		//[[nodiscard]] bool Center(const Bezier2& a) noexcept;
		//[[nodiscard]] bool Center(const Bezier3& a) noexcept;
		//[[nodiscard]] bool Center(const Rect& a) noexcept;
		//[[nodiscard]] bool Center(const RectF& a) noexcept;
		//[[nodiscard]] bool Center(const Circle& a) noexcept;
		//[[nodiscard]] bool Center(const Ellipse& a) noexcept;
		//[[nodiscard]] bool Center(const Triangle& a) noexcept;
		//[[nodiscard]] bool Center(const Quad& a) noexcept;
		//[[nodiscard]] bool Center(const RoundRect& a) noexcept;
		//[[nodiscard]] bool Center(const Polygon& a) noexcept;
		//[[nodiscard]] bool Center(const MultiPolygon& a) noexcept;
		//[[nodiscard]] bool Center(const LineString& a) noexcept;

		//[[nodiscard]] bool IsClockWise(const Array<Vec2>& points);

		[[nodiscard]] Polygon ConvexHull(const Array<Vec2>& points);

		[[nodiscard]] Array<Polygon> Subtract(const Polygon& a, const Polygon& b);
		[[nodiscard]] Array<Polygon> And(const Polygon& a, const Polygon& b);
		[[nodiscard]] Array<Polygon> Or(const Polygon& a, const Polygon& b);
		[[nodiscard]] Array<Polygon> Xor(const Polygon& a, const Polygon& b);

		[[nodiscard]] double FrechetDistance(const LineString& a, const LineString& b);

		[[nodiscard]] double HausdorffDistance(const LineString& a, const LineString& b);
	}
}
