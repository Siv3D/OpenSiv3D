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
# include <Siv3D/Window/CWindow.hpp>
# include <Siv3D/Window/Null/CWindow_Null.hpp>

namespace s3d
{
	ISiv3DWindow* ISiv3DWindow::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CWindow_Null;
		}
		else
		{
			return new CWindow;
		}
	}
}
