//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CLogger.hpp"

namespace s3d
{
	ISiv3DLogger* ISiv3DLogger::Create()
	{
		return new CLogger;
	}
}
