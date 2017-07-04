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
# include "Quad.hpp"

namespace s3d
{
	struct FloatQuad
	{
		Float2 p[4];

		FloatQuad() = default;

		constexpr FloatQuad(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
			: p{ p0, p1, p2, p3 } {}

		constexpr FloatQuad(const Quad& q) noexcept
			: p{ q.p0, q.p1, q.p2, q.p3 } {}
	};
}
