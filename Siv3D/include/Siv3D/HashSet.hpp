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
# include <ThirdParty/parallel_hashmap/phmap.h>
# include "HeterogeneousLookupHelper.hpp"

namespace s3d
{
	template <class Type,
		class Hash	= std::conditional_t<std::is_same_v<Type, String>, StringHash, phmap::priv::hash_default_hash<Type>>,
		class Eq	= std::conditional_t<std::is_same_v<Type, String>, StringCompare, phmap::priv::hash_default_eq<Type>>,
		class Alloc	= phmap::priv::Allocator<Type>>
	using HashSet = phmap::flat_hash_set<Type, Hash, Eq, Alloc>;

	template <class Type>
	inline void swap(HashSet<Type>& a, HashSet<Type>& b) noexcept;

	template <class Type>
	inline void Formatter(FormatData& formatData, const HashSet<Type>& set);
}

# include "detail/HashSet.ipp"

# if SIV3D_INTRINSIC(SSE)
#	undef PHMAP_HAVE_SSE2
#	undef PHMAP_HAVE_SSSE3
# endif
