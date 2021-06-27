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

# include "CRenderer3D_WebGPU.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/WebGPU/CRenderer_WebGPU.hpp>
# include <Siv3D/Shader/WebGPU/CShader_WebGPU.hpp>
# include <Siv3D/Texture/WebGPU/CTexture_WebGPU.hpp>

namespace s3d
{
	CRenderer3D_WebGPU::CRenderer3D_WebGPU() {}

	CRenderer3D_WebGPU::~CRenderer3D_WebGPU()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_WebGPU::~CRenderer3D_WebGPU()");
	}

	void CRenderer3D_WebGPU::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_WebGPU::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= dynamic_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
			pShader		= dynamic_cast<CShader_WebGPU*>(SIV3D_ENGINE(Shader)); assert(pShader);
			pTexture	= dynamic_cast<CTexture_WebGPU*>(SIV3D_ENGINE(Texture)); assert(pTexture);
		}
	}
}
