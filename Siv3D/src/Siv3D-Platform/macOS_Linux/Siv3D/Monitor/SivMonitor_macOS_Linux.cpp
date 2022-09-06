//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Monitor.hpp>
# include <Siv3D/MonitorInfo.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/WindowState.hpp>

namespace s3d
{
	namespace System
	{
		size_t GetCurrentMonitorIndex()
		{
			const auto& state = Window::GetState();
			const Point pos = state.bounds.pos;
			const Size size = state.bounds.size;
			
			const auto monitors = EnumerateMonitors();
			int32 bestoverlap = 0;
			size_t bestIndex = 0;
			
			for (size_t i = 0; i < monitors.size(); ++i)
			{
				const auto& monitor = monitors[i];
				const Point mPos = monitor.displayRect.pos;
				const Size mSize = monitor.displayRect.size;
				
				const int32 overlap =
					Max(0, Min(pos.x + size.x, mPos.x + mSize.x) - Max(pos.x, mPos.x)) *
					Max(0, Min(pos.y + size.y, mPos.y + mSize.y) - Max(pos.y, mPos.y));
				
				if (bestoverlap < overlap)
				{
					bestoverlap = overlap;
					bestIndex = i;
				}
			}
			
			return bestIndex;
		}
	}
}
