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
# include <Siv3D/Renderer3D/Null/CRenderer3D_Null.hpp>
# include <Siv3D/Renderer3D/GL4/CRenderer3D_GL4.hpp>
# include <Siv3D/Renderer3D/D3D11/CRenderer3D_D3D11.hpp>

namespace s3d
{
	ISiv3DRenderer3D* ISiv3DRenderer3D::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer3D_Null;
		}
		else if ((g_engineOptions.renderer == EngineOption::Renderer::PlatformDefault)
			|| (g_engineOptions.renderer == EngineOption::Renderer::Direct3D11))
		{
			return new CRenderer3D_D3D11;
		}
		else
		{
			return new CRenderer3D_GL4;
		}
	}
}
