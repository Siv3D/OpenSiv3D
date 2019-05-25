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

# include <Siv3D/Hash.hpp>
# include <Siv3D/ByteArrayView.hpp>

namespace s3d
{
	namespace detail
	{
		//-----------------------------------------------------------------------------
		// MurmurHash2 was written by Austin Appleby, and is placed in the public
		// domain. The author hereby disclaims copyright to this source code.
		// https://github.com/aappleby/smhasher

		inline uint64 MurmurHash64A(const void* key, int32 len, uint64 seed) noexcept
		{
			const uint64 m = 0xc6a4a7935bd1e995ULL;
			const int r = 47;

			uint64 h = seed ^ (len * m);

			const uint64* data = static_cast<const uint64*>(key);
			const uint64* end = data + (len / 8);

			while (data != end)
			{
				uint64 k = *data++;

				k *= m;
				k ^= k >> r;
				k *= m;

				h ^= k;
				h *= m;
			}

			const Byte* data2 = static_cast<const Byte*>(static_cast<const void*>(data));

			switch (len & 7)
			{
			case 7: h ^= uint64(data2[6]) << 48;
			case 6: h ^= uint64(data2[5]) << 40;
			case 5: h ^= uint64(data2[4]) << 32;
			case 4: h ^= uint64(data2[3]) << 24;
			case 3: h ^= uint64(data2[2]) << 16;
			case 2: h ^= uint64(data2[1]) << 8;
			case 1: h ^= uint64(data2[0]);
				h *= m;
			};

			h ^= h >> r;
			h *= m;
			h ^= h >> r;

			return h;
		}
	}

	namespace Hash
	{
		uint64 FNV1a(const ByteArrayView view) noexcept
		{
			const Byte* data = view.data();
			const uint64 offset_basis = 14695981039346656037ULL;
			const uint64 FNV_prime = 1099511628211ULL;

			uint64 result = offset_basis;

			for (uint64 next = 0; next < view.size(); ++next)
			{
				result ^= static_cast<uint64>(data[next]);
				result *= FNV_prime;
			}

			return result;
		}

		uint64 FNV1a(const void* data, size_t size) noexcept
		{
			return FNV1a(ByteArrayView(data, size));
		}

		uint64 FNV1a(ByteArrayViewAdapter viewAdapter) noexcept
		{
			return FNV1a(ByteArrayView(viewAdapter.data(), viewAdapter.size_bytes()));
		}

		uint64 Murmur2(const ByteArrayView view) noexcept
		{
			constexpr uint32 seed = 11111111;
			return detail::MurmurHash64A(view.data(), static_cast<int32>(view.size()), seed);
		}

		uint64 Murmur2(const void* data, size_t size) noexcept
		{
			return Murmur2(ByteArrayView(data, size));
		}

		uint64 Murmur2(ByteArrayViewAdapter viewAdapter) noexcept
		{
			return Murmur2(ByteArrayView(viewAdapter.data(), viewAdapter.size_bytes()));
		}
	}
}
