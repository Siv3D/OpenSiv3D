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
# include <memory>
# if  __has_include(<bit>)
#	include <bit>
# endif
# include "Common.hpp"
# include "Concepts.hpp"

namespace s3d
{
	namespace Hash
	{
		inline size_t FNV1a(const void* input, size_t size) noexcept;

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		inline size_t FNV1a(const TriviallyCopyable& input) noexcept;

		uint64 XXHash3(const void* input, size_t size) noexcept;

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		inline uint64 XXHash3(const TriviallyCopyable& input) noexcept;

		template <class Type>
		inline void Combine(size_t& h, const Type& input) noexcept;
	}
}

# include "detail/Hash.ipp"
