//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Optional.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	namespace Geometry2D
	{
		//////////////////////////////////////////////////
		//
		//	Point intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Point& a, const Bezier2& b) noexcept;
		
		//[[nodiscard]]
		//bool Intersect(const Point& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Circle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Quad& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Point& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Point& a, const Polygon& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Point& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		inline bool Intersect(const Point& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Vec2 intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Point& b) noexcept;
		
		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Vec2& b) noexcept;
		
		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Vec2& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Vec2& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Circle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Vec2& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Vec2& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Vec2& a, const Polygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Vec2& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Vec2& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Line intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Line& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Line& a, const Vec2& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Line& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Line& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const Rect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const RectF& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const Circle& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const Triangle& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Line& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Line& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Bezier2 intersects ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Point& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const RectF& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Bezier2& a, const Circle& b);

		[[nodiscard]]
		bool Intersect(const Bezier2& a, const Ellipse& b);

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier2& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Bezier3 intersects ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Point& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const RectF& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Bezier3& a, const Circle& b);

		[[nodiscard]]
		bool Intersect(const Bezier3& a, const Ellipse& b);

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Bezier3& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Rect intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Rect& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Rect& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Rect& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Rect& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Rect& a, const Triangle& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Rect& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Rect& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Rect& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Rect& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Rect& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RectF intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RectF& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RectF& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RectF& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RectF& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RectF& a, const Triangle& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RectF& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RectF& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RectF& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RectF& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RectF& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Circle intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Circle& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Circle& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Circle& a, const Line& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Circle& a, const Bezier2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Circle& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Circle& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Circle& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Circle& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Circle& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Circle& a, const Triangle& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Circle& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Circle& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Circle& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Circle& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Circle& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Ellipse intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Ellipse& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Ellipse& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Ellipse& a, const Line& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Ellipse& a, const Bezier2& b);

		[[nodiscard]]
		inline bool Intersect(const Ellipse& a, const Bezier3& b);

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Ellipse& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Ellipse& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Triangle intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Triangle& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Triangle& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Triangle& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Triangle& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Triangle& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Triangle& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Triangle& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Triangle& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Triangle& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Triangle& a, const Triangle& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Triangle& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Triangle& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Triangle& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Triangle& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Triangle& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Quad intersects ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		inline constexpr bool Intersect(const Quad& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Quad& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Quad& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Quad& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Quad& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Quad& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Quad& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Quad& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Quad& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Quad& a, const Triangle& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Quad& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Quad& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Quad& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Quad& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Quad& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RoundRect intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const Point& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RoundRect& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RoundRect& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RoundRect& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const RoundRect& a, const Quad& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RoundRect& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RoundRect& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const RoundRect& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const RoundRect& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Polygon intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const Point& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Polygon& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Polygon& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Polygon& a, const Rect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Polygon& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Polygon& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const Quad& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Polygon& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const Polygon& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Polygon& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	MultiPolygon intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline bool Intersect(const MultiPolygon& a, const Point& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const MultiPolygon& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const MultiPolygon& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	LineString intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Point& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Line& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const LineString& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const LineString& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Circle& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Quad& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const LineString& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//bool Intersect(const LineString& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const LineString& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Line intersectsAt ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Bezier3& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Rect& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Line& a, const RectF& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Circle& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Ellipse& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Line& a, const MultiPolygon& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Line& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Bezier2 intersectsAt ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Bezier3& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Rect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const RectF& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Circle& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const MultiPolygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier2& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Bezier3 intersectsAt ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Bezier3& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Rect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const RectF& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Circle& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const MultiPolygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Bezier3& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Rect intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Rect& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Bezier3& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Circle& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Rect& a, const MultiPolygon& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	RectF intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const RectF& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Bezier3& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Circle& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RectF& a, const MultiPolygon& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Circle intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Line& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier2& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Bezier3& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const Rect& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Circle& a, const RectF& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Circle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const RoundRect& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Circle& a, const MultiPolygon& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Circle& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Ellipse intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Line& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier2& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Bezier3& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Rect& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RectF& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Circle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const MultiPolygon& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Ellipse& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Triangle intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Bezier3& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Rect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const RectF& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Circle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Triangle& a, const MultiPolygon& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Triangle& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Quad intersectsAt ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Bezier3& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Rect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const RectF& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Circle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const MultiPolygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Quad& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	RoundRect intersectsAt ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Bezier3& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Rect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const RectF& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Circle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const MultiPolygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const RoundRect& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Polygon intersectsAt ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Bezier3& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Rect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const RectF& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Circle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const MultiPolygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const Polygon& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	MultiPolygon intersectsAt ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Bezier3& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Rect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const RectF& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Circle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Ellipse& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const MultiPolygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const MultiPolygon& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	LineString intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Line& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier2& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Bezier3& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Rect& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const RectF& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Circle& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Ellipse& b);

		[[nodiscard]]
		inline Optional<Array<Vec2>> IntersectAt(const LineString& a, const Triangle& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Quad& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const RoundRect& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const Polygon& b);

		//[[nodiscard]]
		//Optional<Array<Vec2>> IntersectAt(const LineString& a, const MultiPolygon& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const LineString& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	Rect contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Point& b) noexcept;
		
		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Rect& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Rect& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Circle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Quad& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Contains(const Rect& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Rect& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Contains(const Rect& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RectF contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Point& b) noexcept;
		
		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RectF& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RectF& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Circle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Quad& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Contains(const RectF& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RectF& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Contains(const RectF& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Circle contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Circle& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Circle& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Circle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Circle& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Circle& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Contains(const Circle& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Circle& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Contains(const Circle& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Ellipse contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const Ellipse& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Ellipse& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Ellipse& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Ellipse& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Ellipse& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Ellipse& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Ellipse& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Ellipse& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Triangle contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const Triangle& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Triangle& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Triangle& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Triangle& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Triangle& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Triangle& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Triangle& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Triangle& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Quad contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const Quad& a, const Point& b) noexcept;
		
		[[nodiscard]]
		inline constexpr bool Contains(const Quad& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Quad& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Quad& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Quad& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Quad& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Contains(const Quad& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const Quad& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RoundRect contains ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const RoundRect& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Polygon contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline bool Contains(const Polygon& a, const Point& b) noexcept;

		[[nodiscard]]
		inline bool Contains(const Polygon& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline bool Contains(const Polygon& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline bool Contains(const Polygon& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline bool Contains(const Polygon& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		bool Contains(const Polygon& a, const Rect& b);

		[[nodiscard]]
		bool Contains(const Polygon& a, const RectF& b);

		[[nodiscard]]
		bool Contains(const Polygon& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline bool Contains(const Polygon& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		bool Contains(const Polygon& a, const Triangle& b);

		[[nodiscard]]
		bool Contains(const Polygon& a, const Quad& b);

		//[[nodiscard]]
		//inline bool Contains(const Polygon& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		bool Contains(const Polygon& a, const Polygon& b);

		//[[nodiscard]]
		//inline bool Contains(const Polygon& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//inline bool Contains(const Polygon& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	MultiPolygon contains ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const MultiPolygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr bool Contains(const MultiPolygon& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Point distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Point& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Vec2 distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Vec2& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Line distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Line& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Bezier2 distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Bezier2& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Bezier3 distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Bezier3& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Rect distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Rect& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RectF distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const RectF& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Circle distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Circle& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Ellipse distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Ellipse& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Triangle distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Triangle& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Quad distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Quad& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RoundRect distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const RoundRect& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Polygon distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const Polygon& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	MultiPolygon distanceFrom ...
		//
		//////////////////////////////////////////////////]

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const MultiPolygon& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	LineString distanceFrom ...
		//
		//////////////////////////////////////////////////

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Point& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Vec2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Line& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Bezier2& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Bezier3& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Rect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const RectF& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Circle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Ellipse& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Triangle& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Quad& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const RoundRect& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const Polygon& b) noexcept;

		//[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const MultiPolygon& b) noexcept;

		////[[nodiscard]]
		//inline constexpr double Distance(const LineString& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	IsClockwise
		//
		//////////////////////////////////////////////////

		template <class PointType>
		[[nodiscard]]
		inline constexpr bool IsClockwise(const PointType& p0, const PointType& p1, const PointType& p2) noexcept;

		template <class PointType>
		[[nodiscard]]
		inline constexpr bool IsClockwise(const PointType& p0, const PointType& p1, const PointType& p2, const PointType& p3) noexcept;

		[[nodiscard]]
		inline bool IsClockwise(const Array<Point>& points) noexcept;

		[[nodiscard]]
		inline bool IsClockwise(const Point* points, size_t size) noexcept;

		[[nodiscard]]
		inline bool IsClockwise(const Array<Float2>& points) noexcept;

		[[nodiscard]]
		inline bool IsClockwise(const Float2* points, size_t size) noexcept;
		
		[[nodiscard]]
		inline bool IsClockwise(const Array<Vec2>& points) noexcept;

		[[nodiscard]]
		inline bool IsClockwise(const Vec2* points, size_t size) noexcept;

		//////////////////////////////////////////////////
		//
		//	BoundingRect
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		RectF BoundingRect(const Array<Point>& points) noexcept;

		[[nodiscard]]
		RectF BoundingRect(const Point* points, size_t size) noexcept;

		[[nodiscard]]
		RectF BoundingRect(const Array<Float2>& points) noexcept;

		[[nodiscard]]
		RectF BoundingRect(const Float2* points, size_t size) noexcept;

		[[nodiscard]]
		RectF BoundingRect(const Array<Vec2>& points) noexcept;

		[[nodiscard]]
		RectF BoundingRect(const Vec2* points, size_t size) noexcept;

		//////////////////////////////////////////////////
		//
		//	ConvexHull
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Polygon ConvexHull(const Array<Point>& points);

		[[nodiscard]]
		Polygon ConvexHull(const Point* points, size_t size);

		[[nodiscard]]
		Polygon ConvexHull(const Array<Float2>& points);

		[[nodiscard]]
		Polygon ConvexHull(const Float2* points, size_t size);

		[[nodiscard]]
		Polygon ConvexHull(const Array<Vec2>& points);

		[[nodiscard]]
		Polygon ConvexHull(const Vec2* points, size_t size);

		//////////////////////////////////////////////////
		//
		//	ConcaveHull
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Polygon ConcaveHull(const Array<Point>& points, double concavity = 2.0, double lengthThreshold = 0.0);

		[[nodiscard]]
		Polygon ConcaveHull(const Array<Float2>& points, double concavity = 2.0, double lengthThreshold = 0.0);

		[[nodiscard]]
		Polygon ConcaveHull(const Array<Vec2>& points, double concavity = 2.0, double lengthThreshold = 0.0);
	
		//////////////////////////////////////////////////
		//
		//	Subtract
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Array<Polygon> Subtract(const RectF& a, const Polygon& b);

		[[nodiscard]]
		Array<Polygon> Subtract(const Polygon& a, const RectF& b);

		[[nodiscard]]
		Array<Polygon> Subtract(const Polygon& a, const Polygon& b);

		//////////////////////////////////////////////////
		//
		//	And
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Array<Polygon> And(const RectF& a, const Polygon& b);

		[[nodiscard]]
		Array<Polygon> And(const Polygon& a, const RectF& b);

		[[nodiscard]]
		Array<Polygon> And(const Polygon& a, const Polygon& b);

		//////////////////////////////////////////////////
		//
		//	Or
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Array<Polygon> Or(const RectF& a, const Polygon& b);

		[[nodiscard]]
		Array<Polygon> Or(const Polygon& a, const RectF& b);

		[[nodiscard]]
		Array<Polygon> Or(const Polygon& a, const Polygon& b);

		//////////////////////////////////////////////////
		//
		//	Xor
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Array<Polygon> Xor(const RectF& a, const Polygon& b);

		[[nodiscard]]
		Array<Polygon> Xor(const Polygon& a, const RectF& b);

		[[nodiscard]]
		Array<Polygon> Xor(const Polygon& a, const Polygon& b);

		//////////////////////////////////////////////////
		//
		//	FrechetDistance
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		double FrechetDistance(const LineString& a, const LineString& b);

		//////////////////////////////////////////////////
		//
		//	HausdorffDistance
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		double HausdorffDistance(const LineString& a, const LineString& b);
	}
}

# include "detail/Geometry2D.ipp"
