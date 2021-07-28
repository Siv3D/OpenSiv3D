//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline constexpr Disc::Disc(const double _r) noexcept
		: center{ 0.0, 0.0, 0.0 }
		, r{ _r } {}

	inline constexpr Disc::Disc(const double cx, const double cy, const double cz, const double _r) noexcept
		: center{ cx, cy, cz }
		, r{ _r } {}

	inline constexpr Disc::Disc(const Vec3& _center, const double _r) noexcept
		: center{ _center }
		, r{ _r } {}
}
