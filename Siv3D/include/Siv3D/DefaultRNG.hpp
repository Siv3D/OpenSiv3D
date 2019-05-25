//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "SFMT.hpp"

namespace s3d
{
	using DefaultRNGType = SFMT19937_64;

	[[nodiscard]] DefaultRNGType& GetDefaultRNG();

	void Reseed(uint64 seed);

	void Reseed(const std::array<uint64, 16>& seeds);
}
