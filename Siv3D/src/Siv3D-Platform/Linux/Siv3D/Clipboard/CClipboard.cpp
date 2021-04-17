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
# include "CClipboard.hpp"

namespace s3d
{
	CClipboard::CClipboard() {}

	CClipboard::~CClipboard()
	{
		LOG_SCOPED_TRACE(U"CClipboard::~CClipboard()");
	}

	void CClipboard::init()
	{
		LOG_SCOPED_TRACE(U"CClipboard::init()");
	}
}
