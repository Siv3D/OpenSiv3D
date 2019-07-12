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
	namespace SDF
	{
		[[nodiscard]] Image GenerateMSDF(const FilePath& fontFile, char32 codePoint, double scale = 1.0);

		[[nodiscard]] Image GenerateMSDFIcon(uint32 codePoint, double scale = 1.0);
	}
}
