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

# include "CRenderer3D_Null.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer3D_Null::CRenderer3D_Null() {}

	CRenderer3D_Null::~CRenderer3D_Null()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_Null::~CRenderer3D_Null()");
	}

	void CRenderer3D_Null::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_Null::init()");
	}
}
