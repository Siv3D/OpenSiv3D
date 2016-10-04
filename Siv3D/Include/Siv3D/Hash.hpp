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
# include <type_traits>
# include "Fwd.hpp"

namespace s3d
{
	namespace Hash
	{
		size_t FNV1a(const uint8* p, size_t size);

		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		size_t FNV1a(const Type& keyValue)
		{
			return FNV1a(static_cast<const uint8*>(static_cast<const void*>(std::addressof(keyValue))), sizeof(keyValue));
		}
	}
}
