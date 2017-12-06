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

# include "CPolygon.hpp"
//# include <Siv3D/Shape2D.hpp>
//# include <Siv3D/Mouse.hpp>
//# include <Siv3D/Cursor.hpp>

namespace s3d
{
	Polygon::Polygon()
		: pImpl(std::make_unique<CPolygon>())
	{

	}

	Polygon::Polygon(const Polygon& polygon)
		: Polygon()
	{
		pImpl->copyFrom(*polygon.pImpl);
	}

	Polygon::Polygon(Polygon&& polygon)
		: Polygon()
	{
		pImpl->moveFrom(*polygon.pImpl);
	}

	Polygon::Polygon(const Vec2* outer, const size_t size, const Array<Array<Vec2>>& holes)
		: pImpl(std::make_unique<CPolygon>(outer, size, holes))
	{

	}

	//Polygon::Polygon(const Shape2D& shape)
	//	: pImpl(std::make_unique<CPolygon>(shape.vertices().data(), shape.vertices().size(), shape.indices()))
	//{

	//}

	Polygon::~Polygon()
	{

	}

	Polygon& Polygon::operator =(const Polygon& polygon)
	{
		pImpl->copyFrom(*polygon.pImpl);

		return *this;
	}

	Polygon& Polygon::operator =(Polygon&& polygon)
	{
		pImpl->moveFrom(*polygon.pImpl);

		return *this;
	}

	bool Polygon::isEmpty() const
	{
		return pImpl->outer().isEmpty();
	}

	bool Polygon::hasHoles() const
	{
		return !pImpl->inners().isEmpty();
	}

	void Polygon::swap(Polygon& polygon) noexcept
	{
		std::swap(pImpl, polygon.pImpl);
	}

	const Array<Vec2>& Polygon::outer() const
	{
		return pImpl->outer();
	}

	const Array<Array<Vec2>>& Polygon::inners() const
	{
		return pImpl->inners();
	}
	
	const Array<Float2>& Polygon::vertices() const
	{
		return pImpl->vertices();
	}
	
	const Array<uint32>& Polygon::indices() const
	{
		return pImpl->indices();
	}

	const RectF& Polygon::boundingRect() const
	{
		return pImpl->boundingRect();
	}

	size_t Polygon::num_triangles() const
	{
		return pImpl->indices().size() / 3;
	}

	Triangle Polygon::triangle(const size_t index) const
	{
		const auto& vertices = pImpl->vertices();
		const auto& indices = pImpl->indices();
		return{ vertices[indices[index * 3]], vertices[indices[index * 3 + 1]], vertices[indices[index * 3 + 2]] };
	}

	Polygon Polygon::movedBy(const double x, const double y) const
	{
		Polygon result(*this);

		result.moveBy(x, y);

		return result;
	}

	Polygon& Polygon::moveBy(const double x, const double y)
	{
		pImpl->moveBy(x, y);

		return *this;
	}

	//double Polygon::area() const
	//{
	//	return pImpl->area();
	//}

	//double Polygon::perimeter() const
	//{
	//	return pImpl->perimeter();
	//}

	Vec2 Polygon::centroid() const
	{
		return pImpl->centroid();
	}
	
	Polygon Polygon::computeConvexHull() const
	{
		return pImpl->computeConvexHull();
	}

	bool Polygon::intersects(const Polygon& polygon) const
	{
		return pImpl->intersects(*polygon.pImpl);
	}

	//bool Polygon::leftClicked() const
	//{
	//	return MouseL.down() && mouseOver();
	//}

	//bool Polygon::leftPressed() const
	//{
	//	return MouseL.pressed() && mouseOver();
	//}

	//bool Polygon::leftReleased() const
	//{
	//	return MouseL.up() && mouseOver();
	//}

	//bool Polygon::rightClicked() const
	//{
	//	return MouseR.down() && mouseOver();
	//}

	//bool Polygon::rightPressed() const
	//{
	//	return MouseR.pressed() && mouseOver();
	//}

	//bool Polygon::rightReleased() const
	//{
	//	return MouseR.up() && mouseOver();
	//}

	//bool Polygon::mouseOver() const
	//{
	//	return Geometry2D::Intersect(Cursor::PosF(), *this);
	//}

	//const Polygon& Polygon::draw(const ColorF& color) const
	//{
	//	pImpl->draw(color);

	//	return *this;
	//}

	//const Polygon& Polygon::drawFrame(const double thickness, const ColorF& color) const
	//{
	//	pImpl->drawFrame(thickness, color);

	//	return *this;
	//}
}
