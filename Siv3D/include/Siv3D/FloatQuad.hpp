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
# include "Common.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	struct FloatQuad
	{
		Float2 p[4];

		SIV3D_NODISCARD_CXX20
		FloatQuad() = default;

		SIV3D_NODISCARD_CXX20
		constexpr FloatQuad(const Float2& p0, const Float2& p1, const Float2& p2, const Float2& p3) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr FloatQuad(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept;
	
		SIV3D_NODISCARD_CXX20
		explicit constexpr FloatQuad(const Quad& q) noexcept;
	};
}

# include "detail/FloatQuad.ipp"
