﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CScreenCapture.hpp"

namespace s3d
{
	ISiv3DScreenCapture* ISiv3DScreenCapture::Create()
	{
		return new CScreenCapture;
	}
}

