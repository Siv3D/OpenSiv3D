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

# define XXH_STATIC_LINKING_ONLY
# define XXH_PRIVATE_API
# include "../../ThirdParty/zstd/common/xxhash.h"
# include <Siv3D/XXHash.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	namespace Hash
	{
		uint64 XXHash(const void* data, const size_t size, const uint64 seed)
		{
			return XXH64(data, size, seed);
		}

		uint64 XXHashFromFile(const FilePath& path, const uint64 seed)
		{
			BinaryReader reader(path);

			XXH64_state_t state;

			XXH64_reset(&state, seed);

			if (size_t sizeToRead = reader.size())
			{
				uint8* const buffer = static_cast<uint8*>(::malloc(4096));

				while (sizeToRead)
				{
					const size_t readSize = reader.read(buffer, 4096);

					XXH64_update(&state, buffer, readSize);

					sizeToRead -= readSize;
				}

				::free(buffer);
			}

			return XXH64_digest(&state);
		}
	}
}
