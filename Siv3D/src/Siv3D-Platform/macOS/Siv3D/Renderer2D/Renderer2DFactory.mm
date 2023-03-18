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
# include <Siv3D/Renderer2D/Null/CRenderer2D_Null.hpp>
# include <Siv3D/Renderer2D/GL4/CRenderer2D_GL4.hpp>
# include <Siv3D/Renderer2D/Metal/CRenderer2D_Metal.hpp>

namespace s3d
{
	ISiv3DRenderer2D* ISiv3DRenderer2D::Create()
	{
		if ((g_engineOptions.renderer == EngineOption::Renderer::OpenGL)
			|| (g_engineOptions.renderer == EngineOption::Renderer::PlatformDefault))
		{
			return new CRenderer2D_GL4;
		}
		else if (g_engineOptions.renderer == EngineOption::Renderer::Metal)
		{
			return new CRenderer2D_Metal;
		}
		else
		{
			return new CRenderer2D_Null;
		}
	}
}
