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

# include "CRenderer3D_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
//# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
//# include <Siv3D/Shader/GL4/CShader_GL4.hpp>
//# include <Siv3D/Texture/GL4/CTexture_GL4.hpp>

namespace s3d
{
	CRenderer3D_GL4::CRenderer3D_GL4() {}

	CRenderer3D_GL4::~CRenderer3D_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_GL4::~CRenderer3D_GL4()");
	}

	void CRenderer3D_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_GL4::init()");
		
		// 各種ポインタを保存
		{
			//pRenderer	= dynamic_cast<CRenderer_GL4*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
			//pShader		= dynamic_cast<CShader_GL4*>(SIV3D_ENGINE(Shader)); assert(pShader);
			//pTexture	= dynamic_cast<CTexture_GL4*>(SIV3D_ENGINE(Texture)); assert(pTexture);
		}
	}
}
