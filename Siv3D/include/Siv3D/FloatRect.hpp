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
# include "PointVector.hpp"

namespace s3d
{
	struct FloatRect
	{
		float left, top, right, bottom;

		FloatRect() = default;

		constexpr FloatRect(float l, float t, float r, float b) noexcept
			: left(l)
			, top(t)
			, right(r)
			, bottom(b) {}

		constexpr FloatRect(int32 l, int32 t, int32 r, int32 b) noexcept
			: left(static_cast<float>(l))
			, top(static_cast<float>(t))
			, right(static_cast<float>(r))
			, bottom(static_cast<float>(b)) {}

		constexpr FloatRect(double l, double t, double r, double b) noexcept
			: left(static_cast<float>(l))
			, top(static_cast<float>(t))
			, right(static_cast<float>(r))
			, bottom(static_cast<float>(b)) {}
	};
}
