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
# include "CFont.hpp"
# include "CFont_Headless.hpp"

namespace s3d
{
	ISiv3DFont* ISiv3DFont::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CFont_Headless;
		}
		else
		{
			return new CFont;
		}
	}
}
