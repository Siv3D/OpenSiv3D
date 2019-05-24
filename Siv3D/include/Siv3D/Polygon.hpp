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
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "PointVector.hpp"

namespace s3d
{
	class Polygon
	{
	private:

		class PolygonDetail;

		std::unique_ptr<PolygonDetail> pImpl;

	public:

		using IndexType = uint16;

		Polygon();

		Polygon(const Polygon& polygon);

		Polygon(Polygon&& polygon);

		Polygon(const Vec2* outer, size_t size, const Array<Array<Vec2>>& holes = {});

		explicit Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes = {});

		Polygon(const Array<Vec2>& outer, const Array<IndexType>& indices, const RectF& boundingRect);

		Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<IndexType>& indices, const RectF& boundingRect);

		Polygon(const Shape2D& shape);

		explicit Polygon(std::initializer_list<Vec2> outer);

		~Polygon();

		Polygon& operator =(const Polygon& polygon);

		Polygon& operator =(Polygon&& polygon);

		[[nodiscard]] explicit operator bool() const { return !isEmpty(); }

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] bool hasHoles() const;

		[[nodiscard]] size_t num_holes() const;

		void swap(Polygon& polygon) noexcept;

		[[nodiscard]] const Array<Vec2>& outer() const;

		[[nodiscard]] const Array<Array<Vec2>>& inners() const;

		[[nodiscard]] const Array<Float2>& vertices() const;
		
		[[nodiscard]] const Array<IndexType>& indices() const;
		
		[[nodiscard]] const RectF& boundingRect() const;

		[[nodiscard]] size_t num_triangles() const;

		[[nodiscard]] Triangle triangle(size_t index) const;

		Polygon& addHole(const Array<Vec2>& hole);

		Polygon& addHoles(const Array<Array<Vec2>>& holes);

		[[nodiscard]] Polygon movedBy(double x, double y) const;

		[[nodiscard]] Polygon movedBy(const Vec2& v) const;

		Polygon& moveBy(double x, double y);

		Polygon& moveBy(const Vec2& v);

		[[nodiscard]] Polygon rotated(double angle) const;

		[[nodiscard]] Polygon rotatedAt(double x, double y, double angle) const;

		[[nodiscard]] Polygon rotatedAt(const Vec2& pos, double angle) const;

		Polygon& rotate(double angle);

		Polygon& rotateAt(double x, double y, double angle);

		Polygon& rotateAt(const Vec2& pos, double angle);

		[[nodiscard]] Polygon transformed(double s, double c, const Vec2& pos) const;

		Polygon& transform(double s, double c, const Vec2& pos);

		[[nodiscard]] Polygon scaled(double s) const;

		Polygon& scale(double s);

		[[nodiscard]] double area() const;

		[[nodiscard]] double perimeter() const;

		[[nodiscard]] Vec2 centroid() const;

		[[nodiscard]] Polygon calculateConvexHull() const;

		[[nodiscard]] Polygon calculateBuffer(double distance) const;

		[[nodiscard]] Polygon calculateRoundBuffer(double distance) const;

		[[nodiscard]] Polygon simplified(double maxDistance = 2.0) const;

		bool append(const Polygon& polygon);

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		[[nodiscard]] bool intersects(const Polygon& polygon) const;

		template <class Shape2DType>
		[[nodiscard]] bool contains(const Shape2DType& shape) const
		{
			return Geometry2D::Contains(*this, shape);
		}

		[[nodiscard]] bool leftClicked() const;

		[[nodiscard]] bool leftPressed() const;

		[[nodiscard]] bool leftReleased() const;

		[[nodiscard]] bool rightClicked() const;

		[[nodiscard]] bool rightPressed() const;

		[[nodiscard]] bool rightReleased() const;

		[[nodiscard]] bool mouseOver() const;

		const Polygon& paint(Image& dst, const Color& color) const;

		const Polygon& paint(Image& dst, double x, double y, const Color& color) const;

		const Polygon& paint(Image& dst, const Vec2& pos, const Color& color) const;

		const Polygon& overwrite(Image& dst, const Color& color, bool antialiased = true) const;

		const Polygon& overwrite(Image& dst, double x, double y, const Color& color, bool antialiased = true) const;

		const Polygon& overwrite(Image& dst, const Vec2& pos, const Color& color, bool antialiased = true) const;

		const Polygon& draw(const ColorF& color = Palette::White) const;

		void draw(double x, double y, const ColorF& color = Palette::White) const;

		void draw(const Vec2& pos, const ColorF& color = Palette::White) const;

		//const Polygon& draw(const Array<ColorF>& colors) const;

		const Polygon& drawFrame(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawFrame(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		const Polygon& drawWireframe(double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(double x, double y, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawWireframe(const Vec2& pos, double thickness = 1.0, const ColorF& color = Palette::White) const;

		void drawTransformed(double s, double c, const Vec2& pos, const ColorF& color = Palette::White) const;

		const PolygonDetail* _detail() const;
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	std::ostream& operator <<(std::ostream& output, const Polygon& value);
	std::wostream& operator <<(std::wostream& output, const Polygon& value);
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{

}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	inline void swap(s3d::Polygon& a, s3d::Polygon& b) noexcept
	{
		a.swap(b);
	}
}
