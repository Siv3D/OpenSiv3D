﻿//-----------------------------------------------
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
# include <Siv3D/Renderer/Null/CRenderer_Null.hpp>
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>

namespace s3d
{
	ISiv3DRenderer* ISiv3DRenderer::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer_Null;
		}
		else if (g_applicationOptions.renderer == EngineOption::Renderer::PlatformDefault
			|| g_applicationOptions.renderer == EngineOption::Renderer::Direct3D11)
		{
			return new CRenderer_D3D11;
		}
		else
		{
			return new CRenderer_GL4;
		}
	}
}
