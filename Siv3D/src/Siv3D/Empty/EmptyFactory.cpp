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

# include "CEmpty.hpp"

namespace s3d
{
	ISiv3DEmpty* ISiv3DEmpty::Create()
	{
		return new CEmpty;
	}
}
