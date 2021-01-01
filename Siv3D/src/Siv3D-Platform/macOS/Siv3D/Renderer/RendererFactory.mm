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
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
# include <Siv3D/Renderer/Metal/CRenderer_Metal.hpp>

namespace s3d
{
	ISiv3DRenderer* ISiv3DRenderer::Create()
	{
		if ((g_applicationOptions.renderer == EngineOption::Renderer::OpenGL)
			|| (g_applicationOptions.renderer == EngineOption::Renderer::PlatformDefault))
		{
			return new CRenderer_GL4;
		}
		else if (g_applicationOptions.renderer == EngineOption::Renderer::Metal)
		{
			return new CRenderer_Metal;
		}
		else
		{
			return new CRenderer_Null;
		}
	}
}
