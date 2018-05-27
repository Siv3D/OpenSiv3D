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

# include "CWebcam.hpp"

namespace s3d
{
	ISiv3DWebcam* ISiv3DWebcam::Create()
	{
		return new CWebcam;
	}
}

