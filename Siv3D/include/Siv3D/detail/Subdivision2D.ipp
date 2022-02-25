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
	inline bool Subdivision2D::isEmpty() const noexcept
	{
		return (m_addedPoints == 0);
	}

	inline Subdivision2D::operator bool() const noexcept
	{
		return (m_addedPoints != 0);
	}

	inline constexpr Subdivision2D::Vertex::Vertex(const Vec2& _pt, const bool _isvirtual, const int32 _firstEdge)
		: firstEdge{ _firstEdge }
		, type{ _isvirtual }
		, pt{ _pt } {}

	inline constexpr bool Subdivision2D::Vertex::isvirtual() const noexcept
	{
		return (type > 0);
	}

	inline constexpr bool Subdivision2D::Vertex::isfree() const noexcept
	{
		return (type < 0);
	}

	inline constexpr Subdivision2D::QuadEdge::QuadEdge(int32 edgeidx)
	{
		assert((edgeidx & 3) == 0);
		next[0] = edgeidx;
		next[1] = edgeidx + 3;
		next[2] = edgeidx + 2;
		next[3] = edgeidx + 1;
	}

	inline constexpr bool Subdivision2D::QuadEdge::isfree() const noexcept
	{
		return (next[0] <= 0);
	}
}
