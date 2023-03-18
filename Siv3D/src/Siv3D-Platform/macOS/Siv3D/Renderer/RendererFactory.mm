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
# include <Siv3D/Renderer/Null/CRenderer_Null.hpp>
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
# include <Siv3D/Renderer/Metal/CRenderer_Metal.hpp>

namespace s3d
{
	ISiv3DRenderer* ISiv3DRenderer::Create()
	{
		if ((g_engineOptions.renderer == EngineOption::Renderer::OpenGL)
			|| (g_engineOptions.renderer == EngineOption::Renderer::PlatformDefault))
		{
			return new CRenderer_GL4;
		}
		else if (g_engineOptions.renderer == EngineOption::Renderer::Metal)
		{
			return new CRenderer_Metal;
		}
		else
		{
			return new CRenderer_Null;
		}
	}
}
