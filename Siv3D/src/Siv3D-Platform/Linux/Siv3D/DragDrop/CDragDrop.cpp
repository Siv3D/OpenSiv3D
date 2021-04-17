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

# include <Siv3D/EngineLog.hpp>
# include "CDragDrop.hpp"

namespace s3d
{
	CDragDrop::CDragDrop() {}

	CDragDrop::~CDragDrop()
	{
		LOG_SCOPED_TRACE(U"CDragDrop::~CDragDrop()");
	}

	void CDragDrop::init()
	{
		LOG_SCOPED_TRACE(U"CDragDrop::init()");
	}

}
