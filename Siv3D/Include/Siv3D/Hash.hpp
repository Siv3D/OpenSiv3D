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

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	namespace Hash
	{
		size_t FNV1a(const uint8* p, size_t size);

		template <class KeyType>
		size_t FNV1a(const KeyType& keyValue)
		{
			return FNV1a(static_cast<const uint8*>(static_cast<const void*>(&keyValue)), sizeof(keyValue));
		}
	}
}
