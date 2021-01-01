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

namespace s3d
{
	ApplicationOptions g_applicationOptions;

	namespace detail
	{
		int SetEngineOption(const EngineOption::DebugHeap value) noexcept
		{
			g_applicationOptions.debugHeap = value;
			return 0;
		}

		int SetEngineOption(const EngineOption::Renderer value) noexcept
		{
			g_applicationOptions.renderer = value;
			return 0;
		}

		int SetEngineOption(const EngineOption::D3D11Driver value) noexcept
		{
			g_applicationOptions.d3d11Driver = value;
			return 0;
		}
	}
}
