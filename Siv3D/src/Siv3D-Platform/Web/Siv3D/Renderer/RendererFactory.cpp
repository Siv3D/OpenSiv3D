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
# include <Siv3D/Renderer/Null/CRenderer_Null.hpp>
# include <Siv3D/Renderer/GLES3/CRenderer_GLES3.hpp>

namespace s3d
{
	ISiv3DRenderer* ISiv3DRenderer::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer_Null;
		}
		else
		{
			return new CRenderer_GLES3;
		}
	}
}
