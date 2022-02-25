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
	inline constexpr FloatRect::FloatRect(const float l, const float t, const float r, const float b) noexcept
		: left{ l }
		, top{ t }
		, right{ r }
		, bottom{ b } {}

	inline constexpr FloatRect::FloatRect(const int32 l, const int32 t, const int32 r, const int32 b) noexcept
		: left{ static_cast<float>(l) }
		, top{ static_cast<float>(t) }
		, right{ static_cast<float>(r) }
		, bottom{ static_cast<float>(b) } {}

	inline constexpr FloatRect::FloatRect(const double l, const double t, const double r, const double b) noexcept
		: left{ static_cast<float>(l) }
		, top{ static_cast<float>(t) }
		, right{ static_cast<float>(r) }
		, bottom{ static_cast<float>(b) } {}
}
