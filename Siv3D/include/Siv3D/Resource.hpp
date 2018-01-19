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
# include "Array.hpp"

namespace s3d
{
	[[nodiscard]] const Array<FilePath>& EnumResourceFiles();

	[[nodiscard]] FilePath Resource(const FilePath& path);
}
