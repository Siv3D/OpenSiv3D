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
# include <Siv3D/Cursor/CCursor.hpp>
# include <Siv3D/Cursor/CCursor_Null.hpp>

namespace s3d
{
	ISiv3DCursor* ISiv3DCursor::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CCursor_Null;
		}
		else
		{
			return new CCursor;
		}
	}
}
