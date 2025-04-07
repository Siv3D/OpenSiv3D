﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Clipboard/CClipboard.hpp>

namespace s3d
{
	ISiv3DClipboard* ISiv3DClipboard::Create()
	{
		return new CClipboard;
	}
}
