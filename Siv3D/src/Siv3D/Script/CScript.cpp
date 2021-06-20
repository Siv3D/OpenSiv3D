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

# include "CScript.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CScript::CScript() {}

	CScript::~CScript()
	{
		LOG_SCOPED_TRACE(U"CScript::~CScript()");
	}

	void CScript::init()
	{
		LOG_SCOPED_TRACE(U"CScript::init()");
	}
}
