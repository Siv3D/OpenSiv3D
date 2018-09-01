//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	struct Icon
	{
		uint32 code;

		int32 size;

		constexpr Icon(uint32 _code, int32 _size) noexcept
			: code(_code)
			, size(_size) {}

		[[nodiscard]] static Image LoadImage(uint32 _code, int32 _size);

		//
		//	http://fontawesome.io/cheatsheet/
		//
		//	example:
		//		Icon(0xf000) for fa-glass
	};
}
