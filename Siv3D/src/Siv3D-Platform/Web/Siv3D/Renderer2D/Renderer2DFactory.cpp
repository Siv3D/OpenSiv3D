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
# include <Siv3D/Renderer2D/Null/CRenderer2D_Null.hpp>
# include <Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.hpp>
# include <Siv3D/Renderer2D/WebGPU/CRenderer2D_WebGPU.hpp>

namespace s3d
{
	ISiv3DRenderer2D* ISiv3DRenderer2D::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer2D_Null;
		}
		else if (g_engineOptions.renderer == EngineOption::Renderer::WebGPU)
		{
			return new CRenderer2D_WebGPU;
		}
		else
		{
			return new CRenderer2D_GLES3;
		}
	}
}
