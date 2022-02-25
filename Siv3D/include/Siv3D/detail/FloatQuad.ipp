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
	inline constexpr FloatQuad::FloatQuad(const Float2& p0, const Float2& p1, const Float2& p2, const Float2& p3) noexcept
		: p{ p0, p1, p2, p3 } {}

	inline constexpr FloatQuad::FloatQuad(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
		: p{ p0, p1, p2, p3 } {}

	inline constexpr FloatQuad::FloatQuad(const Quad& q) noexcept
		: p{ q.p0, q.p1, q.p2, q.p3 } {}
}
