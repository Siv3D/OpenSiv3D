﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Pentablet/Null/CPentablet_Null.hpp>

namespace s3d
{
	ISiv3DPentablet* ISiv3DPentablet::Create()
	{
		return new CPentablet_Null;
	}
}
