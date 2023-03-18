//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Texture/Null/CTexture_Null.hpp>
# include <Siv3D/Texture/GL4/CTexture_GL4.hpp>
# include <Siv3D/Texture/GLES3/CTexture_GLES3.hpp>

namespace s3d
{
	ISiv3DTexture* ISiv3DTexture::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CTexture_Null;
		}
		else if (g_engineOptions.renderer == EngineOption::Renderer::WebGL2)
		{
			return new CTexture_GLES3;
		}
		else
		{
			return new CTexture_GL4;
		}
	}
}
