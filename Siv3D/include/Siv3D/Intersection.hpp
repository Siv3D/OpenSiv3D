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

namespace s3d
{
	/// <summary>
	/// 二次元図形の作成と幾何計算
	/// </summary>
	namespace Geometry2D
	{
		bool Intersect(const Point& a, const Point&			b) noexcept;
		bool Intersect(const Point& a, const Vec2&			b) noexcept;
		bool Intersect(const Point& a, const Line&			b) noexcept;
		//bool Intersect(const Point& a, const Bezier2&		 b);
		//bool Intersect(const Point& a, const Bezier3&		 b);
		bool Intersect(const Point& a, const Rect&			b) noexcept;
		bool Intersect(const Point& a, const RectF&			b) noexcept;
		bool Intersect(const Point& a, const Circle&		b) noexcept;
		bool Intersect(const Point& a, const Ellipse&		b) noexcept;
		bool Intersect(const Point& a, const Triangle&		b) noexcept;
		bool Intersect(const Point& a, const Quad&			b) noexcept;
		bool Intersect(const Point& a, const RoundRect&		b) noexcept;
		bool Intersect(const Point& a, const Polygon&		b) noexcept;
		//bool Intersect(const Point& a, const MultiPolygon&	b);
		//bool Intersect(const Point& a, const LineString&	b);

		bool Intersect(const Vec2& a, const Point&			b) noexcept;
		bool Intersect(const Vec2& a, const Vec2&			b) noexcept;
		bool Intersect(const Vec2& a, const Line&			b) noexcept;
		//bool Intersect(const Vec2& a, const Bezier2&		 b);
		//bool Intersect(const Vec2& a, const Bezier3&		 b);
		bool Intersect(const Vec2& a, const Rect&			b) noexcept;
		bool Intersect(const Vec2& a, const RectF&			b) noexcept;
		bool Intersect(const Vec2& a, const Circle&			b) noexcept;
		bool Intersect(const Vec2& a, const Ellipse&		b) noexcept;
		bool Intersect(const Vec2& a, const Triangle&		b) noexcept;
		bool Intersect(const Vec2& a, const Quad&			b) noexcept;
		bool Intersect(const Vec2& a, const RoundRect&		b) noexcept;
		bool Intersect(const Vec2& a, const Polygon&		b) noexcept;
		//bool Intersect(const Vec2& a, const MultiPolygon&	b);
		//bool Intersect(const Vec2& a, const LineString&		b);

		bool Intersect(const Line& a, const Point&			b) noexcept;
		bool Intersect(const Line& a, const Vec2&			b) noexcept;
		bool Intersect(const Line& a, const Line&			b) noexcept;
		//bool Intersect(const Line& a, const Bezier2&		 b);
		//bool Intersect(const Line& a, const Bezier3&		 b);
		bool Intersect(const Line& a, const Rect&			b) noexcept;
		bool Intersect(const Line& a, const RectF&			b) noexcept;
		bool Intersect(const Line& a, const Circle&			b) noexcept;
		bool Intersect(const Line& a, const Ellipse&		b) noexcept;
		bool Intersect(const Line& a, const Triangle&		b) noexcept;
		bool Intersect(const Line& a, const Quad&			b) noexcept;
		bool Intersect(const Line& a, const RoundRect&		b) noexcept;
		bool Intersect(const Line& a, const Polygon&		b) noexcept;
		//bool Intersect(const Line& a, const MultiPolygon&	b);
		//bool Intersect(const Line& a, const LineString&		b);

		//bool Intersect(const Bezier2& a, const Point&			b);
		//bool Intersect(const Bezier2& a, const Vec2&			b);
		//bool Intersect(const Bezier2& a, const Line&			b);
		//bool Intersect(const Bezier2& a, const Bezier2&		 b);
		//bool Intersect(const Bezier2& a, const Bezier3&		 b);
		//bool Intersect(const Bezier2& a, const Rect&			b);
		//bool Intersect(const Bezier2& a, const RectF&			b);
		bool Intersect(const Bezier2& a, const Circle&		b);
		bool Intersect(const Bezier2& a, const Ellipse&		b);
		//bool Intersect(const Bezier2& a, const Triangle&		b);
		//bool Intersect(const Bezier2& a, const Quad&			b);
		//bool Intersect(const Bezier2& a, const RoundRect&		b);
		//bool Intersect(const Bezier2& a, const Polygon&		b);
		//bool Intersect(const Bezier2& a, const MultiPolygon&	b);
		//bool Intersect(const Bezier2& a, const LineString&	b);

		//bool Intersect(const Bezier3& a, const Point&			b);
		//bool Intersect(const Bezier3& a, const Vec2&			b);
		//bool Intersect(const Bezier3& a, const Line&			b);
		//bool Intersect(const Bezier3& a, const Bezier2&		 b);
		//bool Intersect(const Bezier3& a, const Bezier3&		 b);
		//bool Intersect(const Bezier3& a, const Rect&			b);
		//bool Intersect(const Bezier3& a, const RectF&			b);
		bool Intersect(const Bezier3& a, const Circle&		b);
		bool Intersect(const Bezier3& a, const Ellipse&		b);
		//bool Intersect(const Bezier3& a, const Triangle&		b);
		//bool Intersect(const Bezier3& a, const Quad&			b);
		//bool Intersect(const Bezier3& a, const RoundRect&		b);
		//bool Intersect(const Bezier3& a, const Polygon&		b);
		//bool Intersect(const Bezier3& a, const MultiPolygon&	b);
		//bool Intersect(const Bezier3& a, const LineString&	b);

		bool Intersect(const Rect& a, const Point&			b) noexcept;
		bool Intersect(const Rect& a, const Vec2&			b) noexcept;
		bool Intersect(const Rect& a, const Line&			b) noexcept;
		//bool Intersect(const Rect& a, const Bezier2&		 b);
		//bool Intersect(const Rect& a, const Bezier3&		 b);
		bool Intersect(const Rect& a, const Rect&			b) noexcept;
		bool Intersect(const Rect& a, const RectF&			b) noexcept;
		bool Intersect(const Rect& a, const Circle&			b) noexcept;
		//bool Intersect(const Rect& a, const Ellipse&		b);
		bool Intersect(const Rect& a, const Triangle&		b) noexcept;
		bool Intersect(const Rect& a, const Quad&			b) noexcept;
		bool Intersect(const Rect& a, const RoundRect&		b) noexcept;
		bool Intersect(const Rect& a, const Polygon&		b) noexcept;
		//bool Intersect(const Rect& a, const MultiPolygon&	b);
		//bool Intersect(const Rect& a, const LineString&		b);

		bool Intersect(const RectF& a, const Point&			b) noexcept;
		bool Intersect(const RectF& a, const Vec2&			b) noexcept;
		bool Intersect(const RectF& a, const Line&			b) noexcept;
		//bool Intersect(const RectF& a, const Bezier2&		 b);
		//bool Intersect(const RectF& a, const Bezier3&		 b);
		bool Intersect(const RectF& a, const Rect&			b) noexcept;
		bool Intersect(const RectF& a, const RectF&			b) noexcept;
		bool Intersect(const RectF& a, const Circle&		b) noexcept;
		//bool Intersect(const RectF& a, const Ellipse&		b);
		bool Intersect(const RectF& a, const Triangle&		b) noexcept;
		bool Intersect(const RectF& a, const Quad&			b) noexcept;
		bool Intersect(const RectF& a, const RoundRect&		b) noexcept;
		bool Intersect(const RectF& a, const Polygon&		b) noexcept;
		//bool Intersect(const RectF& a, const MultiPolygon&	b);
		//bool Intersect(const RectF& a, const LineString&	b);

		bool Intersect(const Circle& a, const Point&			b) noexcept;
		bool Intersect(const Circle& a, const Vec2&				b) noexcept;
		bool Intersect(const Circle& a, const Line&				b) noexcept;
		bool Intersect(const Circle& a, const Bezier2&			b);
		bool Intersect(const Circle& a, const Bezier3&			b);
		bool Intersect(const Circle& a, const Rect&				b) noexcept;
		bool Intersect(const Circle& a, const RectF&			b) noexcept;
		bool Intersect(const Circle& a, const Circle&			b) noexcept;
		//bool Intersect(const Circle& a, const Ellipse&			b);
		bool Intersect(const Circle& a, const Triangle&			b) noexcept;
		bool Intersect(const Circle& a, const Quad&				b) noexcept;
		bool Intersect(const Circle& a, const RoundRect&		b) noexcept;
		bool Intersect(const Circle& a, const Polygon&			b) noexcept;
		//bool Intersect(const Circle& a, const MultiPolygon&		b);
		//bool Intersect(const Circle& a, const LineString&		b);

		bool Intersect(const Ellipse& a, const Point&			b) noexcept;
		bool Intersect(const Ellipse& a, const Vec2&			b) noexcept;
		bool Intersect(const Ellipse& a, const Line&			b) noexcept;
		bool Intersect(const Ellipse& a, const Bezier2&			b);
		bool Intersect(const Ellipse& a, const Bezier3&			b);
		//bool Intersect(const Ellipse& a, const Rect&			b);
		//bool Intersect(const Ellipse& a, const RectF&			b);
		//bool Intersect(const Ellipse& a, const Circle&			b);
		//bool Intersect(const Ellipse& a, const Ellipse&			b);
		//bool Intersect(const Ellipse& a, const Triangle&		b);
		//bool Intersect(const Ellipse& a, const Quad&			b);
		//bool Intersect(const Ellipse& a, const RoundRect&		b);
		//bool Intersect(const Ellipse& a, const Polygon&			b);
		//bool Intersect(const Ellipse& a, const MultiPolygon&	b);
		//bool Intersect(const Ellipse& a, const LineString&		b);

		bool Intersect(const Triangle& a, const Point&			b) noexcept;
		bool Intersect(const Triangle& a, const Vec2&			b) noexcept;
		bool Intersect(const Triangle& a, const Line&			b) noexcept;
		//bool Intersect(const Triangle& a, const Bezier2&		 b);
		//bool Intersect(const Triangle& a, const Bezier3&		 b);
		bool Intersect(const Triangle& a, const Rect&			b) noexcept;
		bool Intersect(const Triangle& a, const RectF&			b) noexcept;
		bool Intersect(const Triangle& a, const Circle&			b) noexcept;
		//bool Intersect(const Triangle& a, const Ellipse&		b);
		bool Intersect(const Triangle& a, const Triangle&		b) noexcept;
		bool Intersect(const Triangle& a, const Quad&			b) noexcept;
		bool Intersect(const Triangle& a, const RoundRect&		b) noexcept;
		bool Intersect(const Triangle& a, const Polygon&		b) noexcept;
		//bool Intersect(const Triangle& a, const MultiPolygon&	b);
		//bool Intersect(const Triangle& a, const LineString&		b);

		bool Intersect(const Quad& a, const Point&				b) noexcept;
		bool Intersect(const Quad& a, const Vec2&				b) noexcept;
		bool Intersect(const Quad& a, const Line&				b) noexcept;
		//bool Intersect(const Quad& a, const Bezier2&		 b);
		//bool Intersect(const Quad& a, const Bezier3&		 b);
		bool Intersect(const Quad& a, const Rect&				b) noexcept;
		bool Intersect(const Quad& a, const RectF&				b) noexcept;
		bool Intersect(const Quad& a, const Circle&				b) noexcept;
		//bool Intersect(const Quad& a, const Ellipse&			b);
		bool Intersect(const Quad& a, const Triangle&			b) noexcept;
		bool Intersect(const Quad& a, const Quad&				b) noexcept;
		bool Intersect(const Quad& a, const RoundRect&			b) noexcept;
		bool Intersect(const Quad& a, const Polygon&			b) noexcept;
		//bool Intersect(const Quad& a, const MultiPolygon&		b);
		//bool Intersect(const Quad& a, const LineString&			b);

		bool Intersect(const RoundRect& a, const Point&			b) noexcept;
		bool Intersect(const RoundRect& a, const Vec2&			b) noexcept;
		bool Intersect(const RoundRect& a, const Line&			b) noexcept;
		//bool Intersect(const RoundRect& a, const Bezier2&		 b);
		//bool Intersect(const RoundRect& a, const Bezier3&		 b);
		bool Intersect(const RoundRect& a, const Rect&			b) noexcept;
		bool Intersect(const RoundRect& a, const RectF&			b) noexcept;
		bool Intersect(const RoundRect& a, const Circle&		b) noexcept;
		//bool Intersect(const RoundRect& a, const Ellipse&		b);
		bool Intersect(const RoundRect& a, const Triangle&		b) noexcept;
		bool Intersect(const RoundRect& a, const Quad&			b) noexcept;
		bool Intersect(const RoundRect& a, const RoundRect&		b) noexcept;
		bool Intersect(const RoundRect& a, const Polygon&		b) noexcept;
		//bool Intersect(const RoundRect& a, const MultiPolygon&	b);
		//bool Intersect(const RoundRect& a, const LineString&	b);

		bool Intersect(const Polygon& a, const Point&			b) noexcept;
		bool Intersect(const Polygon& a, const Vec2&			b) noexcept;
		bool Intersect(const Polygon& a, const Line&			b) noexcept;
		//bool Intersect(const Polygon& a, const Bezier2&		 b);
		//bool Intersect(const Polygon& a, const Bezier3&		 b);
		bool Intersect(const Polygon& a, const Rect&			b) noexcept;
		bool Intersect(const Polygon& a, const RectF&			b) noexcept;
		bool Intersect(const Polygon& a, const Circle&			b) noexcept;
		//bool Intersect(const Polygon& a, const Ellipse&			b);
		bool Intersect(const Polygon& a, const Triangle&		b) noexcept;
		bool Intersect(const Polygon& a, const Quad&			b) noexcept;
		bool Intersect(const Polygon& a, const RoundRect&		b) noexcept;
		bool Intersect(const Polygon& a, const Polygon&			b);
		//bool Intersect(const Polygon& a, const MultiPolygon&	b);
		//bool Intersect(const Polygon& a, const LineString&		b);

		//bool Intersect(const MultiPolygon& a, const Point&			b);
		//bool Intersect(const MultiPolygon& a, const Vec2&			b);
		//bool Intersect(const MultiPolygon& a, const Line&			b);
		//bool Intersect(const MultiPolygon& a, const Bezier2&		 b);
		//bool Intersect(const MultiPolygon& a, const Bezier3&		 b);
		//bool Intersect(const MultiPolygon& a, const Rect&			b);
		//bool Intersect(const MultiPolygon& a, const RectF&			b);
		//bool Intersect(const MultiPolygon& a, const Circle&			b);
		//bool Intersect(const MultiPolygon& a, const Ellipse&		b);
		//bool Intersect(const MultiPolygon& a, const Triangle&		b);
		//bool Intersect(const MultiPolygon& a, const Quad&			b);
		//bool Intersect(const MultiPolygon& a, const RoundRect&		b);
		//bool Intersect(const MultiPolygon& a, const Polygon&		b);
		//bool Intersect(const MultiPolygon& a, const MultiPolygon&	b);
		//bool Intersect(const MultiPolygon& a, const LineString&		b);

		//bool Intersect(const LineString& a, const Point&		b);
		//bool Intersect(const LineString& a, const Vec2&			b);
		//bool Intersect(const LineString& a, const Line&			b);
		//bool Intersect(const LineString& a, const Bezier2&		 b);
		//bool Intersect(const LineString& a, const Bezier3&		 b);
		//bool Intersect(const LineString& a, const Rect&			b);
		//bool Intersect(const LineString& a, const RectF&		b);
		//bool Intersect(const LineString& a, const Circle&		b);
		//bool Intersect(const LineString& a, const Ellipse&		b);
		//bool Intersect(const LineString& a, const Triangle&		b);
		//bool Intersect(const LineString& a, const Quad&			b);
		//bool Intersect(const LineString& a, const RoundRect&	b);
		//bool Intersect(const LineString& a, const Polygon&		b);
		//bool Intersect(const LineString& a, const MultiPolygon&	b);
		//bool Intersect(const LineString& a, const LineString&	b);

		bool Contains(const Rect& a, const Point& b);
	}
}
