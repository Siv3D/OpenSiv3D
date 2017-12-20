//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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
	public:

		int32 size;

		uint32 code;

		constexpr Icon(uint32 _code, int32 _size) noexcept
			: size(_size)
			, code(_code) {}

		static Image LoadImage(uint32 _code, int32 _size);

		//
		//	http://fontawesome.io/cheatsheet/
		//
		//	example:
		//		Icon(0xf000) for fa-glass
	};
}
