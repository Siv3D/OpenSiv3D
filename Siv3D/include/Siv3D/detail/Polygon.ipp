//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Polygon::operator bool() const noexcept
	{
		return (not isEmpty());
	}

	inline void Polygon::swap(Polygon& polygon) noexcept
	{
		std::swap(pImpl, polygon.pImpl);
	}

	inline Polygon Polygon::movedBy(const double x, const double y) const
	{
		return movedBy(Vec2{ x, y });
	}

	inline Polygon& Polygon::moveBy(const double x, const double y) noexcept
	{
		return moveBy(Vec2{ x, y });
	}

	inline Polygon Polygon::rotated(const double angle) const
	{
		return rotatedAt(Vec2{ 0, 0 }, angle);
	}

	inline Polygon Polygon::rotatedAt(const double x, const double y, const double angle) const
	{
		return rotatedAt(Vec2{ x, y }, angle);
	}

	inline Polygon& Polygon::rotate(const double angle)
	{
		return rotateAt(Vec2{ 0, 0 }, angle);
	}

	inline Polygon& Polygon::rotateAt(const double x, const double y, const double angle)
	{
		return rotateAt(Vec2{ x, y }, angle);
	}

	template <class Shape2DType>
	inline bool Polygon::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> Polygon::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class Shape2DType>
	inline bool Polygon::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}

	inline void Polygon::draw(const double x, const double y, const ColorF& color) const
	{
		draw(Vec2{ x, y }, color);
	}

	inline void Polygon::drawFrame(const double x, const double y, const double thickness, const ColorF& color) const
	{
		drawFrame(Vec2{ x, y }, thickness, color);
	}

	inline void Polygon::drawWireframe(const double x, const double y, const double thickness, const ColorF& color) const
	{
		drawWireframe(Vec2{ x, y }, thickness, color);
	}

	inline PolygonFailureType Polygon::Validate(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
	{
		return Validate(vertices.data(), vertices.size(), holes);
	}

	inline Array<Polygon> Polygon::Correct(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
	{
		return Correct(vertices.data(), vertices.size(), holes);
	}

	inline Polygon Polygon::CorrectOne(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
	{
		return CorrectOne(vertices.data(), vertices.size(), holes);
	}

	inline const Polygon::PolygonDetail* Polygon::_detail() const noexcept
	{
		return pImpl.get();
	}

	inline void swap(Polygon& a, Polygon& b) noexcept
	{
		a.swap(b);
	}
}

template <>
void std::swap(s3d::Polygon& a, s3d::Polygon& b) noexcept
{
	a.swap(b);
}
