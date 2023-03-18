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

namespace s3d
{
	EngineOptions g_engineOptions;

	namespace detail
	{
		int SetEngineOption(const EngineOption::DebugHeap value) noexcept
		{
			g_engineOptions.debugHeap = value;
			return 0;
		}

		int SetEngineOption(const EngineOption::Renderer value) noexcept
		{
			g_engineOptions.renderer = value;
			return 0;
		}

		int SetEngineOption(const EngineOption::D3D11Driver value) noexcept
		{
			g_engineOptions.d3d11Driver = value;
			return 0;
		}
	}
}
