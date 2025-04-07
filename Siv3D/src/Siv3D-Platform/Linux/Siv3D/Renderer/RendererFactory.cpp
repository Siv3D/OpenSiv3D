//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Renderer/Null/CRenderer_Null.hpp>
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
# include <Siv3D/Renderer/GLES3/CRenderer_GLES3.hpp>

namespace s3d
{
	ISiv3DRenderer* ISiv3DRenderer::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer_Null;
		}
		else if (g_engineOptions.renderer == EngineOption::Renderer::WebGL2)
		{
			return new CRenderer_GLES3;
		}
		else
		{
			return new CRenderer_GL4;
		}
	}
}
