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
# include "Fwd.hpp"
# include "ByteArrayView.hpp"

namespace s3d
{
	namespace Hash
	{
		constexpr uint64 DefaultXXHSeed = 11111111;

		uint64 XXHash(const void* data, size_t size, uint64 seed = DefaultXXHSeed);

		inline uint64 XXHash(const ByteArrayView view, uint64 seed = DefaultXXHSeed)
		{
			return XXHash(view.data(), view.size(), seed);
		}

		uint64 XXHashFromFile(const FilePath& path, uint64 seed = DefaultXXHSeed);
	}
}
