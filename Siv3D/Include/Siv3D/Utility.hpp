//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <random>

namespace s3d
{
	inline auto& GetDefaultRNG()
	{
		static thread_local std::mt19937_64 rng;
		return rng;
	}

	static auto AsBool = [](const auto& v) { return !!v; };
}
