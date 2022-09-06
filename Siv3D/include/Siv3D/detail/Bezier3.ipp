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
	inline constexpr Bezier3::Bezier3(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2, const Vec2& _p3) noexcept
		: p0{ _p0 }
		, p1{ _p1 }
		, p2{ _p2 }
		, p3{ _p3 } {}


	inline constexpr Vec2& Bezier3::p(const size_t index) noexcept
	{
		return (&p0)[index];
	}

	inline constexpr const Vec2& Bezier3::p(const size_t index) const noexcept
	{
		return (&p0)[index];
	}

	inline constexpr Vec2 Bezier3::point(const size_t index) const
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
		else if (index == 3)
		{
			return p3;
		}
		else
		{
			throw std::out_of_range("Bezier3::point() index out of range");
		}
	}

	inline constexpr Vec2 Bezier3::getPos(const double t) const noexcept
	{
		return (1 - t) * (1 - t) * (1 - t) * p0 + 3 * (1 - t) * (1 - t) * t * p1 + 3 * (1 - t) * t * t * p2 + t * t * t * p3;
	}

	inline size_t Bezier3::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Shape2DType>
	inline constexpr bool Bezier3::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> Bezier3::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	inline constexpr Bezier3Path::Bezier3Path(const Bezier3& bezier) noexcept
		: m_v0{ -3 * bezier.p0 + 9 * bezier.p1 - 9 * bezier.p2 + 3 * bezier.p3 }
		, m_v1{ 6 * bezier.p0 - 12 * bezier.p1 + 6 * bezier.p2 }
		, m_v2{ -3 * bezier.p0 + 3 * bezier.p1 } {}

	inline constexpr void Bezier3Path::setT(const double t) noexcept
	{
		m_t = t;
	}

	inline constexpr double Bezier3Path::getT() const noexcept
	{
		return m_t;
	}
}
