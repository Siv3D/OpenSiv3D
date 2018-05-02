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

# include "CObjectDetection.hpp"

namespace s3d
{
	ISiv3DObjectDetection* ISiv3DObjectDetection::Create()
	{
		return new CObjectDetection;
	}
}

