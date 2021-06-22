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

# include "CRenderer3D_GLES3.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/GLES3/CRenderer_GLES3.hpp>
# include <Siv3D/Shader/GLES3/CShader_GLES3.hpp>
# include <Siv3D/Texture/GLES3/CTexture_GLES3.hpp>

namespace s3d
{
	CRenderer3D_GLES3::CRenderer3D_GLES3() {}

	CRenderer3D_GLES3::~CRenderer3D_GLES3()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_GLES3::~CRenderer3D_GLES3()");
	}

	void CRenderer3D_GLES3::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_GLES3::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= dynamic_cast<CRenderer_GLES3*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
			pShader		= dynamic_cast<CShader_GLES3*>(SIV3D_ENGINE(Shader)); assert(pShader);
			pTexture	= dynamic_cast<CTexture_GLES3*>(SIV3D_ENGINE(Texture)); assert(pTexture);
		}
	}
}
