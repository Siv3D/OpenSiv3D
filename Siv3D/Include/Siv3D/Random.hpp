//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <random>
# include "Fwd.hpp"

namespace s3d
{
	// 仮の実装
	inline auto& GetDefaultRNG()
	{
        static std::mt19937_64 rng{ std::random_device{}() };
        return rng;
	}
}
