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

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	namespace Hash
	{
		uint64 FNV1a(ByteArrayView view) noexcept;

		uint64 FNV1a(const void* data, size_t size) noexcept;

		uint64 FNV1a(ByteArrayViewAdapter viewAdapter) noexcept;

		uint64 Murmur2(ByteArrayView view) noexcept;

		uint64 Murmur2(const void* data, size_t size) noexcept;

		uint64 Murmur2(ByteArrayViewAdapter viewAdapter) noexcept;
	}

	template <class Type>
	struct FNV1aHash
	{
		size_t operator()(const Type& keyVal) const noexcept
		{
			return Hash::FNV1a(keyVal);
		}
	};

	template <class Type>
	struct Murmur2Hash
	{
		size_t operator()(const Type& keyVal) const noexcept
		{
			return Hash::Murmur2(keyVal);
		}
	};
}
