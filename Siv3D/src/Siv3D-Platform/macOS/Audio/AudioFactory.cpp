//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Audio/AL/CAudio_AL.hpp>

namespace s3d
{
	ISiv3DAudio* ISiv3DAudio::Create()
	{
		return new CAudio_AL;
	}
}
