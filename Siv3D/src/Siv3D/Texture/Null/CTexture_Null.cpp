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

# include "CTexture_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CTexture_Null::CTexture_Null()
	{

	}

	CTexture_Null::~CTexture_Null()
	{
		LOG_SCOPED_TRACE(U"CTexture_Null::~CTexture_Null()");
	}

	void CTexture_Null::init()
	{
		LOG_SCOPED_TRACE(U"CTexture_Null::init()");

	}

	bool CTexture_Null::update()
	{
		return true;
	}
}
