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
# include "../ThirdParty/hopscotch_map/hopscotch_set.h"

namespace s3d
{
	template <
		class Key,
		class Hash = std::hash<Key>,
		class KeyEqual = std::equal_to<Key>,
		class Allocator = std::allocator<Key>,
		unsigned int NeighborhoodSize = 62,
		bool StoreHash = false,
		class GrowthPolicy = tsl::power_of_two_growth_policy>
		using HashSet = tsl::hopscotch_set<Key, Hash, KeyEqual, Allocator, NeighborhoodSize, StoreHash, GrowthPolicy>;
}
