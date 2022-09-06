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
