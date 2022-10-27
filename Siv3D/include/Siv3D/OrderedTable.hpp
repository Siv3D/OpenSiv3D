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
# include "Common.hpp"
# if SIV3D_INTRINSIC(SSE)
#	define PHMAP_HAVE_SSE2 1
#	define PHMAP_HAVE_SSSE3 1
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(26495)
# include <ThirdParty/parallel_hashmap/btree.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# include "HeterogeneousLookupHelper.hpp"
# include "FormatData.hpp"

namespace s3d
{
	/// @brief テーブル
	/// @tparam Key キーの型
	/// @tparam Value 値の型
	/// @tparam Compare キーの比較関数の型
	/// @tparam Alloc アロケータの型
	template <class Key, class Value,
		class Compare = phmap::Less<Key>,
		class Alloc = phmap::priv::Allocator<phmap::priv::Pair<const Key, Value>>>
	using OrderedTable = phmap::btree_map<Key, Value, Compare, Alloc>;

	template <class Key, class Value>
	inline void swap(OrderedTable<Key, Value>& a, OrderedTable<Key, Value>& b) noexcept;

	template <class Key, class Value>
	inline void Formatter(FormatData& formatData, const OrderedTable<Key, Value>& table);
}

# include "detail/OrderedTable.ipp"

# if SIV3D_INTRINSIC(SSE)
#	undef PHMAP_HAVE_SSE2
#	undef PHMAP_HAVE_SSSE3
# endif