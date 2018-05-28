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
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CWebcam::CWebcam()
	{

	}

	CWebcam::~CWebcam()
	{

	}

	bool CWebcam::init()
	{
		LOG_INFO(U"ℹ️ Webcam initialized");

		return true;
	}
}
