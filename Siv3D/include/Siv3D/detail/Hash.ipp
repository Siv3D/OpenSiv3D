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

namespace s3d
{
	namespace detail
	{
		inline constexpr void HashCombine(size_t& h, size_t k) noexcept
		{
			static_assert((sizeof(size_t) == 8) || (sizeof(size_t) == 4));

			if constexpr (sizeof(size_t) == 8)
			{
				constexpr uint64 m = 0xc6a4a7935bd1e995;
				constexpr int r = 47;
				k *= m;
				k ^= k >> r;
				k *= m;
				h ^= k;
				h *= m;
				h += 0xe6546b64;
			}
			else
			{
				constexpr uint32 c1 = 0xcc9e2d51;
				constexpr uint32 c2 = 0x1b873593;

			# if __cpp_lib_bit_cast

				k *= c1;
				k = std::rotl(k, 15);
				k *= c2;
				h ^= k;
				h = std::rotl(h, 13);
				h = h * 5 + 0xe6546b64;

			# else

				k *= c1;
				k = (k << 15) | (k >> (32 - 15));
				k *= c2;
				h ^= k;
				h = (h << 13) | (h >> (32 - 13));
				h = h * 5 + 0xe6546b64;

			# endif
			}
		}
	}

	namespace Hash
	{
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
		inline size_t FNV1a(const TriviallyCopyable& input) noexcept
		{
			return FNV1a(std::addressof(input), sizeof(TriviallyCopyable));
		}

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
		inline uint64 XXHash3(const TriviallyCopyable& input) noexcept
		{
			return XXHash3(std::addressof(input), sizeof(TriviallyCopyable));
		}

		template <class Type>
		inline void Combine(size_t& h, const Type& input) noexcept
		{
			detail::HashCombine(h, std::hash<Type>{}(input));
		}
	}
}
