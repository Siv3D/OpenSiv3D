//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Hash.hpp>
# include "../../ThirdParty/MurmurHash3/MurmurHash3.h"

namespace s3d
{
	namespace detail
	{
		//-----------------------------------------------------------------------------
		// MurmurHash2 was written by Austin Appleby, and is placed in the public
		// domain. The author hereby disclaims copyright to this source code.
		// https://github.com/aappleby/smhasher

		# if defined (SIV3D_TARGET_X86)

			static uint32_t MurmurHash2(const void * key, int len, uint32_t seed)
			{
				// 'm' and 'r' are mixing constants generated offline.
				// They're not really 'magic', they just happen to work well.

				const uint32_t m = 0x5bd1e995;
				const int r = 24;

				// Initialize the hash to a 'random' value

				uint32_t h = seed ^ len;

				// Mix 4 bytes at a time into the hash

				const unsigned char * data = (const unsigned char *)key;

				while (len >= 4)
				{
					uint32_t k = *(uint32_t*)data;

					k *= m;
					k ^= k >> r;
					k *= m;

					h *= m;
					h ^= k;

					data += 4;
					len -= 4;
				}

				// Handle the last few bytes of the input array

				switch (len)
				{
				case 3: h ^= data[2] << 16;
				case 2: h ^= data[1] << 8;
				case 1: h ^= data[0];
					h *= m;
				};

				// Do a few final mixes of the hash to ensure the last few
				// bytes are well-incorporated.

				h ^= h >> 13;
				h *= m;
				h ^= h >> 15;

				return h;
			}

		# else

			static uint64_t MurmurHash64A(const void * key, int len, uint64_t seed)
			{
				const uint64_t m = 0xc6a4a7935bd1e995ULL;
				const int r = 47;

				uint64_t h = seed ^ (len * m);

				const uint64_t * data = (const uint64_t *)key;
				const uint64_t * end = data + (len / 8);

				while (data != end)
				{
					uint64_t k = *data++;

					k *= m;
					k ^= k >> r;
					k *= m;

					h ^= k;
					h *= m;
				}

				const unsigned char * data2 = (const unsigned char*)data;

				switch (len & 7)
				{
				case 7: h ^= uint64_t(data2[6]) << 48;
				case 6: h ^= uint64_t(data2[5]) << 40;
				case 5: h ^= uint64_t(data2[4]) << 32;
				case 4: h ^= uint64_t(data2[3]) << 24;
				case 3: h ^= uint64_t(data2[2]) << 16;
				case 2: h ^= uint64_t(data2[1]) << 8;
				case 1: h ^= uint64_t(data2[0]);
					h *= m;
				};

				h ^= h >> r;
				h *= m;
				h ^= h >> r;

				return h;
			}

		# endif
	}

	namespace Hash
	{
		size_t FNV1a(const void* data_, const size_t size)
		{
			const uint8* data = static_cast<const uint8*>(data_);

			# if (SIV3D_PLATFORM_PTR_SIZE == 4)
				const size_t offset_basis	= 2166136261U;
				const size_t FNV_prime		= 16777619U;
			# else
				const size_t offset_basis	= 14695981039346656037ULL;
				const size_t FNV_prime		= 1099511628211ULL;
			# endif

			size_t result = offset_basis;
			
			for (size_t next = 0; next < size; ++next)
			{
				result ^= (size_t)data[next];
				result *= FNV_prime;
			}
			
			return result;
		}

		size_t Murmur2(const void* p, size_t size)
		{
			constexpr uint32 seed = 11111111;

			# if defined (SIV3D_TARGET_X86)

				return detail::MurmurHash2(p, size, seed);

			# else

				return detail::MurmurHash64A(p, size, seed);

			# endif
		}
	}
}
