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
	class LineString;
	class MultiPolygon;

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

		//[[nodiscard]]
		//bool Intersect(const Point& a, const MultiPolygon& b) noexcept;

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

		//[[nodiscard]]
		//bool Intersect(const Vec2& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Vec2& a, const LineString& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Line intersects ...
		//
		//////////////////////////////////////////////////

		//////////////////////////////////////////////////
		//
		//	Bezier2 intersects ...
		//
		//////////////////////////////////////////////////

		//////////////////////////////////////////////////
		//
		//	Bezier3 intersects ...
		//
		//////////////////////////////////////////////////

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
		inline constexpr bool Intersect(const Rect& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Rect& a, const RectF& b) noexcept;

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
		inline constexpr bool Intersect(const RectF& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const RectF& a, const RectF& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Circle intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Circle& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Circle& a, const Vec2& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Triangle intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Triangle& a, const Vec2& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Quad intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Intersect(const Quad& a, const Vec2& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RoundRect intersects ...
		//
		//////////////////////////////////////////////////

		//////////////////////////////////////////////////
		//
		//	Polygon intersects ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline bool Intersect(const Polygon& a, const Vec2& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	MultiPolygon intersects ...
		//
		//////////////////////////////////////////////////

		//////////////////////////////////////////////////
		//
		//	LineString intersects ...
		//
		//////////////////////////////////////////////////




		//////////////////////////////////////////////////
		//
		//	Rect intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Rect& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const Rect& a, const RectF& b);

		//////////////////////////////////////////////////
		//
		//	RectF intersectsAt ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Rect& b);

		[[nodiscard]]
		Optional<Array<Vec2>> IntersectAt(const RectF& a, const RectF& b);

		//////////////////////////////////////////////////
		//
		//	Rect contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Point& b) noexcept;
		
		[[nodiscard]]
		inline constexpr bool Contains(const Rect& a, const Vec2& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	RectF contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Point& b) noexcept;
		
		[[nodiscard]]
		inline constexpr bool Contains(const RectF& a, const Vec2& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	Quad contains ...
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		bool Contains(const Quad& a, const Point& b) noexcept;
		
		[[nodiscard]]
		bool Contains(const Quad& a, const Vec2& b) noexcept;

		//////////////////////////////////////////////////
		//
		//	IsClockwise
		//
		//////////////////////////////////////////////////

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
