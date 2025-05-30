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

# include "CAudioDecoder.hpp"

namespace s3d
{
	ISiv3DAudioDecoder* ISiv3DAudioDecoder::Create()
	{
		return new CAudioDecoder;
	}
}
