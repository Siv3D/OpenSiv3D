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

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	struct Point
	{
		int32 x, y;

		Point() = default;

		constexpr Point(int32 _x, int32 _y)
			: x(_x)
			, y(_y) {}

		constexpr bool operator ==(const Point& other) const
		{
			return x == other.x && y == other.y;
		}

		constexpr bool operator !=(const Point& other) const
		{
			return x != other.x || y != other.y;
		}
	};

	using Size = Point;
}
