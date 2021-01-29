//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Hash.hpp>

# define XXH_STATIC_LINKING_ONLY
# define XXH_IMPLEMENTATION
# define XXH_NAMESPACE SIV3D_
# include <ThirdParty/xxHash/xxhash.h>

namespace s3d
{
	namespace Hash
	{
		uint64 XXHash3(const void* input, const size_t size) noexcept
		{
			return SIV3D_XXH3_64bits(input, size);
		}
	}
}
