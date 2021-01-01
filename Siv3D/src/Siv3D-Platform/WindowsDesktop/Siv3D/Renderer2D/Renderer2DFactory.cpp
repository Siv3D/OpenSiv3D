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
# include <Siv3D/Renderer2D/Null/CRenderer2D_Null.hpp>
# include <Siv3D/Renderer2D/GL4/CRenderer2D_GL4.hpp>
# include <Siv3D/Renderer2D/D3D11/CRenderer2D_D3D11.hpp>

namespace s3d
{
	ISiv3DRenderer2D* ISiv3DRenderer2D::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer2D_Null;
		}
		else if ((g_applicationOptions.renderer == EngineOption::Renderer::PlatformDefault)
			|| (g_applicationOptions.renderer == EngineOption::Renderer::Direct3D11))
		{
			return new CRenderer2D_D3D11;
		}
		else
		{
			return new CRenderer2D_GL4;
		}
	}
}
