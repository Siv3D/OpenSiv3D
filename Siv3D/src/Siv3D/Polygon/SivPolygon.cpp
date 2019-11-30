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

# include <Siv3D/Shape2D.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include "PolygonDetail.hpp"

namespace s3d
{
	Polygon::Polygon()
		: pImpl(std::make_unique<PolygonDetail>())
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

	Polygon::Polygon(const Vec2* outer, const size_t size, const Array<Array<Vec2>>& holes, const bool checkValidity)
		: pImpl(std::make_unique<PolygonDetail>(outer, size, holes, checkValidity))
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const bool checkValidity)
		: Polygon(outer.data(), outer.size(), holes, checkValidity)
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, const Array<uint16>& indices, const RectF& boundingRect, const bool checkValidity)
		: pImpl(std::make_unique<PolygonDetail>(outer.data(), outer.size(), indices, boundingRect, checkValidity))
	{

	}

	Polygon::Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<Float2>& vertices, const Array<uint16>& indices, const RectF& boundingRect, const bool checkValidity)
		: pImpl(std::make_unique<PolygonDetail>(outer, holes, vertices, indices, boundingRect, checkValidity))
	{

	}

	Polygon::Polygon(const Shape2D& shape)
		: pImpl(std::make_unique<PolygonDetail>(shape.vertices().data(), shape.vertices().size(), shape.indices(), false))
	{

	}

	Polygon::Polygon(std::initializer_list<Vec2> outer)
		: Polygon(outer.begin(), outer.size())
	{

	}

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

	size_t Polygon::num_holes() const
	{
		return pImpl->inners().size();
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

	const Array<uint16>& Polygon::indices() const
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

	Polygon& Polygon::addHole(const Array<Vec2>& hole)
	{
		const auto& outer = pImpl->outer();

		Array<Array<Vec2>> inners = pImpl->inners();

		inners.push_back(hole);

		return *this = Polygon(outer, inners);
	}

	Polygon& Polygon::addHoles(const Array<Array<Vec2>>& holes)
	{
		const auto& outer = pImpl->outer();

		Array<Array<Vec2>> inners = pImpl->inners();

		inners.append(holes);

		return *this = Polygon(outer, inners);
	}

	Polygon Polygon::movedBy(const double x, const double y) const
	{
		Polygon result(*this);

		result.moveBy(x, y);

		return result;
	}

	Polygon Polygon::movedBy(const Vec2& v) const
	{
		return movedBy(v.x, v.y);
	}

	Polygon& Polygon::moveBy(const double x, const double y)
	{
		pImpl->moveBy(x, y);

		return *this;
	}

	Polygon& Polygon::moveBy(const Vec2& v)
	{
		return moveBy(v.x, v.y);
	}

	Polygon Polygon::rotated(const double angle) const
	{
		return rotatedAt(Vec2(0, 0), angle);
	}

	Polygon Polygon::rotatedAt(const double x, const double y, const double angle) const
	{
		return rotatedAt(Vec2(x, y), angle);
	}

	Polygon Polygon::rotatedAt(const Vec2& pos, const double angle) const
	{
		Polygon result(*this);

		result.rotateAt(pos, angle);

		return result;
	}

	Polygon& Polygon::rotate(const double angle)
	{
		pImpl->rotateAt(Vec2(0, 0), angle);

		return *this;
	}

	Polygon& Polygon::rotateAt(const double x, const double y, const double angle)
	{
		return rotateAt(Vec2(x, y), angle);
	}

	Polygon& Polygon::rotateAt(const Vec2& pos, const double angle)
	{
		pImpl->rotateAt(pos, angle);

		return *this;
	}

	Polygon Polygon::transformed(const double s, const double c, const Vec2& pos) const
	{
		Polygon result(*this);

		result.transform(s, c, pos);

		return result;
	}

	Polygon& Polygon::transform(const double s, const double c, const Vec2& pos)
	{
		pImpl->transform(s, c, pos);

		return *this;
	}

	Polygon Polygon::scaled(const double s) const
	{
		Polygon result(*this);

		result.scale(s);

		return result;
	}

	Polygon& Polygon::scale(const double s)
	{
		pImpl->scale(s);

		return *this;
	}

	Polygon Polygon::scaled(const Vec2& s) const
	{
		Polygon result(*this);

		result.scale(s);

		return result;
	}

	Polygon& Polygon::scale(const Vec2& s)
	{
		pImpl->scale(s);

		return *this;
	}

	double Polygon::area() const
	{
		return pImpl->area();
	}

	double Polygon::perimeter() const
	{
		return pImpl->perimeter();
	}

	Vec2 Polygon::centroid() const
	{
		return pImpl->centroid();
	}

	Polygon Polygon::calculateConvexHull() const
	{
		return pImpl->calculateConvexHull();
	}

	Polygon Polygon::calculateBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return *this;
		}

		return pImpl->calculateBuffer(distance);
	}

	Polygon Polygon::calculateRoundBuffer(const double distance) const
	{
		if (distance == 0.0)
		{
			return *this;
		}

		return pImpl->calculateRoundBuffer(distance);
	}

	Polygon Polygon::simplified(const double maxDistance) const
	{
		return pImpl->simplified(maxDistance);
	}

	bool Polygon::append(const Polygon& polygon)
	{
		return pImpl->append(polygon);
	}

	bool Polygon::intersects(const Polygon& polygon) const
	{
		return pImpl->intersects(*polygon.pImpl);
	}

	bool Polygon::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool Polygon::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool Polygon::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool Polygon::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool Polygon::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool Polygon::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool Polygon::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Polygon& Polygon::draw(const ColorF& color) const
	{
		pImpl->draw(color);

		return *this;
	}

	void Polygon::draw(const double x, const double y, const ColorF& color) const
	{
		draw(Vec2(x, y), color);
	}

	void Polygon::draw(const Vec2& pos, const ColorF& color) const
	{
		pImpl->draw(pos, color);
	}

	const Polygon& Polygon::drawFrame(const double thickness, const ColorF& color) const
	{
		pImpl->drawFrame(thickness, color);

		return *this;
	}

	void Polygon::drawFrame(const double x, const double y, const double thickness, const ColorF& color) const
	{
		drawFrame(Vec2(x, y), thickness, color);
	}

	void Polygon::drawFrame(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		pImpl->drawFrame(pos, thickness, color);
	}

	const Polygon& Polygon::drawWireframe(const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return *this;
		}

		const auto& vertices = pImpl->vertices();
		const auto& indices = pImpl->indices();

		const size_t num_triangles = indices.size() / 3;
		const Float2* pVertex = vertices.data();
		const uint16* pIndex = indices.data();

		for (size_t i = 0; i < num_triangles; ++i)
		{
			Triangle(pVertex[pIndex[i * 3]], pVertex[pIndex[i * 3 + 1]], pVertex[pIndex[i * 3 + 2]]).drawFrame(thickness, color);
		}

		return *this;
	}

	void Polygon::drawWireframe(const double x, const double y, const double thickness, const ColorF& color) const
	{
		drawWireframe(Vec2(x, y), thickness, color);
	}

	void Polygon::drawWireframe(const Vec2& pos, const double thickness, const ColorF& color) const
	{
		if (isEmpty())
		{
			return;
		}

		const auto& vertices = pImpl->vertices();
		const auto& indices = pImpl->indices();

		const size_t num_triangles = indices.size() / 3;
		const Float2* pVertex = vertices.data();
		const uint16* pIndex = indices.data();

		for (size_t i = 0; i < num_triangles; ++i)
		{
			Triangle(pVertex[pIndex[i * 3]], pVertex[pIndex[i * 3 + 1]], pVertex[pIndex[i * 3 + 2]])
				.moveBy(pos)
				.drawFrame(thickness, color);
		}
	}

	void Polygon::drawTransformed(const double s, const double c, const Vec2& pos, const ColorF& color) const
	{
		pImpl->drawTransformed(s, c, pos, color);
	}

	const Polygon::PolygonDetail* Polygon::_detail() const
	{
		return pImpl.get();
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& OStream(std::basic_ostream<CharType>& output, const Polygon& value)
	{
		output << CharType('(');

		output << CharType('(');

		bool b = false;

		for (const auto& point : value.outer())
		{
			if (std::exchange(b, true))
			{
				output << CharType(',');
			}

			output << point;
		}

		output << CharType(')');

		if (value.inners())
		{
			output << CharType(',');

			output << CharType('(');

			b = false;

			for (const auto& hole : value.inners())
			{
				if (std::exchange(b, true))
				{
					output << CharType(',');

					output << CharType('(');
				}

				bool b2 = false;

				for (const auto& point : hole)
				{
					if (std::exchange(b2, true))
					{
						output << CharType(',');
					}

					output << point;
				}

				output << CharType(')');
			}
		}

		return output << CharType(')');
	}

	std::ostream& operator <<(std::ostream& output, const Polygon& value)
	{
		return OStream(output, value);
	}

	std::wostream& operator <<(std::wostream& output, const Polygon& value)
	{
		return OStream(output, value);
	}
}
