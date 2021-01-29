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

# include "CTexture_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CTexture_GL4::CTexture_GL4()
	{
		// do nothing
	}

	CTexture_GL4::~CTexture_GL4()
	{
		LOG_SCOPED_TRACE(U"CTexture_GL4::~CTexture_GL4()");
	}

	void CTexture_GL4::init()
	{

	}

	void CTexture_GL4::updateAsyncTextureLoad(const size_t)
	{
		// do nothing
	}
}
