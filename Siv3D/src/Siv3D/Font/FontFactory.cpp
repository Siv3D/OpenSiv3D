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
# include "CFont.hpp"
# include "CFont_Headless.hpp"

namespace s3d
{
	ISiv3DFont* ISiv3DFont::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CFont_Headless;
		}
		else
		{
			return new CFont;
		}
	}
}
