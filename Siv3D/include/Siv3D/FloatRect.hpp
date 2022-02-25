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

namespace s3d
{
	struct FloatRect
	{
		float left;
		
		float top;
			
		float right;
		
		float bottom;

		SIV3D_NODISCARD_CXX20
		FloatRect() = default;

		SIV3D_NODISCARD_CXX20
		constexpr FloatRect(float l, float t, float r, float b) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr FloatRect(int32 l, int32 t, int32 r, int32 b) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr FloatRect(double l, double t, double r, double b) noexcept;
	};
}

# include "detail/FloatRect.ipp"
