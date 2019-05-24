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
	struct Icon
	{
		uint32 code;

		int32 size;

		//
		//	https://fontawesome.com/icons?d=gallery&s=brands,solid&m=free
		//
		//	example:
		//		Icon(0xf000) for fa-glass
		constexpr Icon(uint32 _code, int32 _size) noexcept
			: code(_code)
			, size(_size) {}

		[[nodiscard]] static Image CreateImage(uint32 _code, int32 _size);

		[[nodiscard]] static Image CreateMSDFImage(uint32 _code, double scale);
	};
}
