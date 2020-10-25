//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ApplicationOptions.hpp>
# include <Siv3D/Texture/Null/CTexture_Null.hpp>
//# include <Siv3D/Texture/GL4/CTexture_GL4.hpp>

namespace s3d
{
	ISiv3DTexture* ISiv3DTexture::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CTexture_Null;
		}
		else
		{
			return new CTexture_Null;
		}
	}
}
