//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Logger/CLogger.hpp>

namespace s3d
{
	ISiv3DLogger* ISiv3DLogger::Create()
	{
		return new CLogger;
	}
}
