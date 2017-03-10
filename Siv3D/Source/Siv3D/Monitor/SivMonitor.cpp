//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Monitor.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

namespace s3d
{
	namespace detail
	{
		static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC, LPRECT, LPARAM userData)
		{
			MONITORINFOEX monitorInfo;
			monitorInfo.cbSize = sizeof(monitorInfo);
			::GetMonitorInfoW(hMonitor, &monitorInfo);

			Monitor* monitor = (Monitor*)userData;

			if (monitor->name == monitorInfo.szDevice)
			{
				monitor->displayRect.x = monitorInfo.rcMonitor.left;
				monitor->displayRect.y = monitorInfo.rcMonitor.top;
				monitor->displayRect.w = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
				monitor->displayRect.h = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

				monitor->workArea.x = monitorInfo.rcWork.left;
				monitor->workArea.y = monitorInfo.rcWork.top;
				monitor->workArea.w = monitorInfo.rcWork.right - monitorInfo.rcWork.left;
				monitor->workArea.h = monitorInfo.rcWork.bottom - monitorInfo.rcWork.top;

				return false;
			}

			return true;
		}
	}

	namespace System
	{
		Array<Monitor> EnumMonitors()
		{
			Array<Monitor> monitors;
			DISPLAY_DEVICE displayDevice;
			displayDevice.cb = sizeof(displayDevice);

			for (int32 deviceIndex = 0; ::EnumDisplayDevicesW(0, deviceIndex, &displayDevice, 0); ++deviceIndex)
			{
				if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
				{
					DISPLAY_DEVICE monitor;
					ZeroMemory(&monitor, sizeof(monitor));
					monitor.cb = sizeof(monitor);

					for (int32 monitorIndex = 0; ::EnumDisplayDevicesW(displayDevice.DeviceName, monitorIndex, &monitor, 0); ++monitorIndex)
					{
						if ((monitor.StateFlags & DISPLAY_DEVICE_ACTIVE) &&
							!(monitor.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
						{
							Monitor monitorInfo;
							monitorInfo.name = displayDevice.DeviceName;
							::EnumDisplayMonitors(nullptr, nullptr, detail::MonitorEnumProc, (LPARAM)&monitorInfo);
							monitorInfo.id = monitor.DeviceID;
							monitorInfo.name = monitor.DeviceString;
							monitorInfo.isPrimary = !!(displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE);
							monitors.push_back(monitorInfo);
						}

						ZeroMemory(&monitor, sizeof(monitor));
						monitor.cb = sizeof(monitor);
					}
				}

				ZeroMemory(&displayDevice, sizeof(displayDevice));
				displayDevice.cb = sizeof(displayDevice);
			}

			return monitors;
		}
	}
}

# elif defined(SIV3D_TARGET_MACOS)

namespace s3d
{
	namespace System
	{
		Array<Monitor> EnumMonitors()
		{
			return{};
		}
	}
}

# elif defined(SIV3D_TARGET_LINUX)

namespace s3d
{
	namespace System
	{
		Array<Monitor> EnumMonitors()
		{
			return{};
		}
	}
}

# endif
