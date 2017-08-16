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
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "PointVector.hpp"

namespace s3d
{
	class Polygon
	{
	private:

		class CPolygon;

		std::unique_ptr<CPolygon> pImpl;

	public:

		Polygon();

		Polygon(const Polygon& polygon);

		Polygon(Polygon&& polygon);

		Polygon(const Vec2* outer, size_t size, const Array<Array<Vec2>>& holes = {});

		explicit Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes = {})
			: Polygon(outer.data(), outer.size(), holes) {}

		explicit Polygon(const Shape2D& shape);

		explicit Polygon(std::initializer_list<Vec2> outer)
			: Polygon(outer.begin(), outer.size()) {}

		~Polygon();

		Polygon& operator =(const Polygon& polygon);

		Polygon& operator =(Polygon&& polygon);

		explicit operator bool() const { return !isEmpty(); }

		bool isEmpty() const;

		bool hasHoles() const;

		const Array<Vec2>& outer() const;

		const Array<Array<Vec2>>& inners() const;

		const Array<Float2>& vertices() const;
		
		const Array<uint32>& indices() const;
		
		const RectF& boundingRect() const;

		size_t num_triangles() const;

		Triangle triangle(size_t index) const;

		Polygon movedBy(double x, double y) const;

		Polygon movedBy(const Vec2& v) const
		{
			return movedBy(v.x, v.y);
		}

		Polygon& moveBy(double x, double y);

		Polygon& moveBy(const Vec2& v)
		{
			return moveBy(v.x, v.y);
		}

		//Polygon rotated(double angle) const:

		//Polygon rotatedAt(const Vec2& pos, double angle) const;

		//Polygon& rotate(double angle) const:

		//Polygon& rotateAt(const Vec2& pos, double angle) const;

		//double area() const;

		//double perimeter() const;

		Vec2 centroid() const;

		Polygon computeConvexHull() const;

		//Polygon simplified(double maxDistance = 2.0) const;

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
		}

		bool intersects(const Polygon& polygon) const;

		template <class Shape2DType>
		bool contains(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Contains(*this, shape)))
		{
			return Geometry2D::Contains(*this, shape);
		}

		bool leftClicked() const;

		bool leftPressed() const;

		bool leftReleased() const;

		bool rightClicked() const;

		bool rightPressed() const;

		bool rightReleased() const;

		bool mouseOver() const;

		const Polygon& draw(const ColorF& color = Palette::White) const;

		//const Polygon& draw(const Array<ColorF>& colors) const;

		const Polygon& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		//const Polygon& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;
	};
}
