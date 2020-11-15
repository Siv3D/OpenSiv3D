//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

	inline PolygonFailureType Polygon::Validate(const Array<Vec2>& vertices, const Array<Array<Vec2>>& holes)
	{
		return Validate(vertices.data(), vertices.size(), holes);
	}
}
