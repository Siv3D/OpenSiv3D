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
# include <Siv3D/Renderer3D/GLES3/CRenderer3D_GLES3.hpp>

namespace s3d
{
	__attribute__((weak))
	ISiv3DRenderer3D* ISiv3DRenderer3D::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CRenderer3D_Null;
		}
		else
		{
			return new CRenderer3D_GLES3;
		}
	}
}
