﻿//-----------------------------------------------
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

namespace s3d
{
	namespace Window
	{
		SIV3D_CONCEPT_FORMATTABLE_ARGS_
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}
	}
}
