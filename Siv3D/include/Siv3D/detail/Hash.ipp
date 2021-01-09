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

# pragma once

namespace s3d
{
	namespace Hash
	{
		inline size_t FNV1a(const void* input, const size_t size) noexcept
		{
			const uint8* data = static_cast<const uint8*>(input);
			const uint8* const end = (data + size);

			if constexpr (sizeof(size_t) == 8)
			{
				constexpr uint64 offset_basis	= 14695981039346656037ULL;
				constexpr uint64 fnv_prime		= 1099511628211ULL;
				uint64 result = offset_basis;

				for (; data != end; ++data)
				{
					result ^= static_cast<uint64>(*data);
					result *= fnv_prime;
				}

				return result;
			}
			else
			{
				constexpr uint32 offset_basis	= 2166136261u;
				constexpr uint32 fnv_prime		= 16777619u;
				uint32 result = offset_basis;

				for (; data != end; ++data)
				{
					result ^= static_cast<uint32>(*data);
					result *= fnv_prime;
				}

				return result;
			}
		}

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
	}
}
