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
	inline Duration Random(const Duration& max) noexcept
	{
		return Random(max, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Duration Random(const Duration& max, URBG&& urbg) noexcept
	{
		return Duration{ Random(max.count(), std::forward<URBG>(urbg)) };
	}

	inline Duration Random(const Duration& min, const Duration& max) noexcept
	{
		return Random(min, max, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Duration Random(const Duration& min, const Duration& max, URBG&& urbg) noexcept
	{
		return Duration{ Random(min.count(), max.count(), std::forward<URBG>(urbg)) };
	}
}
