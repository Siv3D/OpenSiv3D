//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

S3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
# include "../hopscotch_map/hopscotch_map.h"
S3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	template <
		class Key,
		class T,
		class Hash = std::hash<Key>,
		class KeyEqual = std::equal_to<Key>,
		class Allocator = std::allocator<std::pair<Key, T>>,
		unsigned int NeighborhoodSize = 62,
		bool StoreHash = false,
		class GrowthPolicy = tsl::power_of_two_growth_policy>
	using HashMap = tsl::hopscotch_map<Key, T, Hash, KeyEqual, Allocator, NeighborhoodSize, StoreHash, GrowthPolicy>;
}
