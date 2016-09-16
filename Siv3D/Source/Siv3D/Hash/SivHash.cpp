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

namespace s3d
{
	namespace Hash
	{
		size_t FNV1a(const uint8* data, const size_t size)
		{
			#if (SIV3D_PLATFORM_PTR_SIZE == 4)
				const size_t offset_basis	= 2166136261U;
				const size_t FNV_prime		= 16777619U;
			#else
				const size_t offset_basis	= 14695981039346656037ULL;
				const size_t FNV_prime		= 1099511628211ULL;
			#endif

			size_t result = offset_basis;
			
			for (size_t next = 0; next < size; ++next)
			{
				result ^= (size_t)data[next];
				result *= FNV_prime;
			}
			
			return result;
		}
	}
}
