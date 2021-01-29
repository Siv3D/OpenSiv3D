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

# include <Siv3D/ApplicationOptions.hpp>
# include <Siv3D/Texture/Null/CTexture_Null.hpp>
# include <Siv3D/Texture/GL4/CTexture_GL4.hpp>
# include <Siv3D/Texture/D3D11/CTexture_D3D11.hpp>

namespace s3d
{
	ISiv3DTexture* ISiv3DTexture::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CTexture_Null;
		}
		else if (g_applicationOptions.renderer == EngineOption::Renderer::PlatformDefault
			|| g_applicationOptions.renderer == EngineOption::Renderer::Direct3D11)
		{
			return new CTexture_D3D11;
		}
		else
		{
			return new CTexture_GL4;
		}
	}
}
