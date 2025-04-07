//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CSoundFont.hpp"

namespace s3d
{
	ISiv3DSoundFont* ISiv3DSoundFont::Create()
	{
		return new CSoundFont;
	}
}
