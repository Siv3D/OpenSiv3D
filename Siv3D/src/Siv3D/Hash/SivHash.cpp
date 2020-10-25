﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Hash.hpp>
# include <ThirdParty/xxHash/xxhash.h>

namespace s3d
{
	namespace Hash
	{
		uint64 XXHash3(const void* input, const size_t size) noexcept
		{
			return XXH3_64bits(input, size);
		}
	}
}
