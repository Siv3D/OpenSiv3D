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

# include "CTexture_Metal.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CTexture_Metal::CTexture_Metal()
	{
		// do nothing
	}

	CTexture_Metal::~CTexture_Metal()
	{
		LOG_SCOPED_TRACE(U"CTexture_Metal::~CTexture_Metal()");
	}

	void CTexture_Metal::init()
	{
		
	}

	void CTexture_Metal::updateAsyncTextureLoad(const size_t)
	{
		// do nothing
	}
}
