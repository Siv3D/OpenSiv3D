//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Rectangle.hpp>

namespace s3d
{
	struct Monitor
	{
		String adapterString;
		String adapterName;
		String displayString;
		String displayName;
		int32 widthMillimeter = 0;
		int32 heightMillimeter = 0;
		HMONITOR handle = nullptr;
		Rect displayRect = Rect(0);
		Rect workArea = Rect(0);
		uint32 displayDPI = 96;
		bool isPrimaryAdapter = false;
		
		[[nodiscard]]
		double getScale() const noexcept
		{
			return static_cast<double>(displayDPI) / USER_DEFAULT_SCREEN_DPI;
		}
	};

	namespace detail
	{
		BOOL CALLBACK MonitorCallback(HMONITOR handle, HDC, RECT*, LPARAM data);

		Monitor CreateMonitor(const DISPLAY_DEVICEW& adapter, const DISPLAY_DEVICEW* display);

		Array<Monitor> EnumActiveMonitors();
	}
}
