//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Renderer2D/Null/CRenderer2D_Null.hpp>
# include <Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.hpp>

namespace s3d
{
	__attribute__((weak))
	ISiv3DRenderer2D* ISiv3DRenderer2D::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer2D_Null;
		}
		else
		{
			return new CRenderer2D_GLES3;
		}
	}
}
