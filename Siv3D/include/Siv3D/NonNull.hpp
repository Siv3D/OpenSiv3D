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
# include <cassert>
# include "Common.hpp"

namespace s3d
{
	template <class Pointer>
	struct NonNull
	{
		Pointer pointer;

		NonNull() = delete;

		NonNull(std::nullptr_t) = delete;

		SIV3D_NODISCARD_CXX20
		constexpr explicit NonNull(Pointer _pointer) noexcept
			: pointer{ _pointer }
		{
			assert(pointer != nullptr);
		}
	};
}
