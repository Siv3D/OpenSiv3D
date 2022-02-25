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
	inline size_t Spline2D::size() const noexcept
	{
		return m_size;
	}

	inline bool Spline2D::isEmpty() const noexcept
	{
		return (m_size == 0);
	}

	inline Spline2D::operator bool() const noexcept
	{
		return (m_size != 0);
	}

	inline bool Spline2D::isRing() const noexcept
	{
		return (m_size && m_isRing);
	}

	inline void Spline2D::clear() noexcept
	{
		m_splinesBuffer.clear();
		m_offset = 0;
		m_size = 0;
		m_isRing = false;
	}

	inline void Spline2D::swap(Spline2D& other) noexcept
	{
		m_splinesBuffer.swap(other.m_splinesBuffer);
		std::swap(m_offset, other.m_offset);
		std::swap(m_size, other.m_size);
		std::swap(m_isRing, other.m_isRing);
	}

	inline Vec2 Spline2D::position(const SplineIndex si) const
	{
		return position(si.i, si.t);
	}

	inline Vec2 Spline2D::velocity(const SplineIndex si) const
	{
		return velocity(si.i, si.t);
	}

	inline Vec2 Spline2D::acceleration(const SplineIndex si) const
	{
		return acceleration(si.i, si.t);
	}

	inline double Spline2D::curvature(const SplineIndex si) const
	{
		return curvature(si.i, si.t);
	}
}

template <>
void std::swap(s3d::Spline2D& a, s3d::Spline2D& b) noexcept
{
	a.swap(b);
}
