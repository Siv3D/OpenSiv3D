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
# include "../ThirdParty/tsl/hopscotch_map.h"
# include "Format.hpp"

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
		class GrowthPolicy = tsl::hh::power_of_two_growth_policy<2>>
		using HashTable = tsl::hopscotch_map<Key, T, Hash, KeyEqual, Allocator, NeighborhoodSize, StoreHash, GrowthPolicy>;
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	template <class Key, class Value>
	inline void Formatter(FormatData& formatData, const HashTable<Key, Value>& table)
	{
		formatData.string.append(StringView(U"{\n"));

		for (auto[key, value] : table)
		{
			formatData.string.append(StringView(U"\t{"));

			Formatter(formatData, key);

			formatData.string.append(StringView(U":\t"));

			Formatter(formatData, value);

			formatData.string.append(StringView(U"},\n"));
		}

		formatData.string.push_back(U'}');
	}
}
