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

# include "CRenderer3D_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/Shader/D3D11/CShader_D3D11.hpp>
# include <Siv3D/Texture/D3D11/CTexture_D3D11.hpp>

namespace s3d
{
	CRenderer3D_D3D11::CRenderer3D_D3D11() {}

	CRenderer3D_D3D11::~CRenderer3D_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_D3D11::~CRenderer3D_D3D11()");
	}

	void CRenderer3D_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_D3D11::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= dynamic_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
			pShader		= dynamic_cast<CShader_D3D11*>(SIV3D_ENGINE(Shader)); assert(pShader);
			pTexture	= dynamic_cast<CTexture_D3D11*>(SIV3D_ENGINE(Texture)); assert(pTexture);
			m_device	= pRenderer->getDevice(); assert(m_device);
			m_context	= pRenderer->getContext(); assert(m_context);
		}
	}
}
