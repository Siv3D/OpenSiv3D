//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
		uint64 XXHash(ByteArrayView view, const uint64 seed)
		{
			return XXH64(view.data(), view.size_bytes(), seed);
		}

		uint64 XXHashFromFile(const FilePath& path, const uint64 seed)
		{
			constexpr size_t bufferSize = 4096;

			BinaryReader reader(path);

			XXH64_state_t state;

			XXH64_reset(&state, seed);

			if (int64 sizeToRead = reader.size())
			{
				Byte* const buffer = static_cast<Byte*>(::malloc(bufferSize));

				while (sizeToRead)
				{
					const int64 readSize = reader.read(buffer, bufferSize);

					XXH64_update(&state, buffer, static_cast<size_t>(readSize));

					sizeToRead -= readSize;
				}

				::free(buffer);
			}

			return XXH64_digest(&state);
		}
	}
}
