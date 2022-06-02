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
# include <ThirdParty/Xoshiro-cpp/XoshiroCpp.hpp>
# include "Common.hpp"
# include "SFMT.hpp"

namespace s3d
{
	namespace PRNG
	{
		using SplitMix64			= XoshiroCpp::SplitMix64;
		using Xoshiro256Plus		= XoshiroCpp::Xoshiro256Plus;
		using Xoshiro256PlusPlus	= XoshiroCpp::Xoshiro256PlusPlus;
		using Xoshiro256StarStar	= XoshiroCpp::Xoshiro256StarStar;
		using Xoroshiro128Plus		= XoshiroCpp::Xoroshiro128Plus;
		using Xoroshiro128PlusPlus	= XoshiroCpp::Xoroshiro128PlusPlus;
		using Xoroshiro128StarStar	= XoshiroCpp::Xoroshiro128StarStar;
		using Xoshiro128Plus		= XoshiroCpp::Xoshiro128Plus;
		using Xoshiro128PlusPlus	= XoshiroCpp::Xoshiro128PlusPlus;
		using Xoshiro128StarStar	= XoshiroCpp::Xoshiro128StarStar;
	}

	using SmallRNG = PRNG::Xoshiro256PlusPlus;
}
