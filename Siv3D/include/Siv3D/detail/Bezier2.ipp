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
	inline constexpr Bezier2::Bezier2(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2) noexcept
		: p0{ _p0 }
		, p1{ _p1 }
		, p2{ _p2 } {}

	inline constexpr Vec2& Bezier2::p(const size_t index) noexcept
	{
		return (&p0)[index];
	}

	inline constexpr const Vec2& Bezier2::p(const size_t index) const noexcept
	{
		return (&p0)[index];
	}

	inline constexpr Vec2 Bezier2::point(const size_t index) const
	{
		if (index == 0)
		{
			return p0;
		}
		else if (index == 1)
		{
			return p1;
		}
		else if (index == 2)
		{
			return p2;
		}
		else
		{
			throw std::out_of_range("Bezier2::point() index out of range");
		}
	}

	inline constexpr Vec2 Bezier2::getPos(const double t) const noexcept
	{
		return (1 - t) * (1 - t) * p0 + 2 * (1 - t) * t * p1 + t * t * p2;
	}

	inline Vec2 Bezier2::getTangent(const double t) const noexcept
	{
		return ((p1 - p0) * 2 * (1 - t) + (p2 - p1) * (2 * t)).normalized();
	}

	inline size_t Bezier2::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	inline constexpr bool Bezier2::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> Bezier2::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	inline constexpr Bezier2Path::Bezier2Path(const Bezier2& bezier) noexcept
		: m_v0{ 2 * bezier.p0 - 4 * bezier.p1 + 2 * bezier.p2 }
		, m_v1{ -2 * bezier.p0 + 2 * bezier.p1 } {}

	inline constexpr void Bezier2Path::setT(const double t) noexcept
	{
		m_t = t;
	}

	inline constexpr double Bezier2Path::getT() const noexcept
	{
		return m_t;
	}

	inline double Bezier2Path::advance(const double distance, const int32 quality) noexcept
	{
		for (int32 i = 0; i < quality; ++i)
		{
			m_t += (distance / quality) / (m_t * m_v0 + m_v1).length();
		}

		return m_t;
	}
}
