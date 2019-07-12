//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Windows.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>

namespace s3d
{
	namespace detail
	{
		// チェック用デバイス名とモニタハンドル
		using MonitorCheck = std::pair<const String, HMONITOR>;

		static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC, LPRECT, LPARAM userData)
		{
			MONITORINFOEX monitorInfo;
			monitorInfo.cbSize = sizeof(monitorInfo);
			::GetMonitorInfoW(hMonitor, &monitorInfo);

			Monitor* monitor = reinterpret_cast<Monitor*>(userData);

			if (monitor->displayDeviceName.toWstr() == monitorInfo.szDevice)
			{
				monitor->displayRect.x = monitorInfo.rcMonitor.left;
				monitor->displayRect.y = monitorInfo.rcMonitor.top;
				monitor->displayRect.w = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);
				monitor->displayRect.h = (monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);

				monitor->workArea.x = monitorInfo.rcWork.left;
				monitor->workArea.y = monitorInfo.rcWork.top;
				monitor->workArea.w = (monitorInfo.rcWork.right - monitorInfo.rcWork.left);
				monitor->workArea.h = (monitorInfo.rcWork.bottom - monitorInfo.rcWork.top);

				return false;
			}

			return true;
		}

		static BOOL CALLBACK MonitorCheckProc(HMONITOR hMonitor, HDC, LPRECT, LPARAM userData)
		{
			MONITORINFOEX monitorInfo;
			monitorInfo.cbSize = sizeof(monitorInfo);
			::GetMonitorInfoW(hMonitor, &monitorInfo);

			MonitorCheck* monitor = (MonitorCheck*)userData;

			if (monitor->first.toWstr() == monitorInfo.szDevice)
			{
				monitor->second = hMonitor;
				return false;
			}

			return true;
		}
	}

	namespace System
	{
		Array<Monitor> EnumerateActiveMonitors()
		{
			Array<Monitor> monitors;
			DISPLAY_DEVICE displayDevice;
			displayDevice.cb = sizeof(displayDevice);

			// デスクトップとして割り当てられている仮想ディスプレイを検索
			for (int32 deviceIndex = 0; ::EnumDisplayDevicesW(0, deviceIndex, &displayDevice, 0); ++deviceIndex)
			{
				if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
				{
					DISPLAY_DEVICE monitor;
					ZeroMemory(&monitor, sizeof(monitor));
					monitor.cb = sizeof(monitor);

					// デスクトップとして使われているモニターの一覧を取得
					for (int32 monitorIndex = 0; ::EnumDisplayDevicesW(displayDevice.DeviceName, monitorIndex, &monitor, 0); ++monitorIndex)
					{
						if ((monitor.StateFlags & DISPLAY_DEVICE_ACTIVE) &&
							!(monitor.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
						{
							Monitor monitorInfo;
							monitorInfo.displayDeviceName = Unicode::FromWString(displayDevice.DeviceName);
							// モニターの配置とサイズを取得
							::EnumDisplayMonitors(nullptr, nullptr, detail::MonitorEnumProc, (LPARAM)&monitorInfo);
							// その他の情報を取得
							monitorInfo.id			= Unicode::FromWString(monitor.DeviceID);
							monitorInfo.name		= Unicode::FromWString(monitor.DeviceString);
							monitorInfo.isPrimary	= !!(displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE);
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

		size_t GetCurrentMonitorIndex()
		{
			const HMONITOR currentMonitor = ::MonitorFromWindow(static_cast<HWND>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle()), MONITOR_DEFAULTTOPRIMARY);
			size_t index = 0;

			DISPLAY_DEVICE displayDevice;
			displayDevice.cb = sizeof(displayDevice);

			// デスクトップとして割り当てられている仮想デスクトップを検索
			for (int32 deviceIndex = 0; ::EnumDisplayDevicesW(0, deviceIndex, &displayDevice, 0); ++deviceIndex)
			{
				if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
				{
					DISPLAY_DEVICE monitor;
					ZeroMemory(&monitor, sizeof(monitor));
					monitor.cb = sizeof(monitor);

					// デスクトップとして使われているモニターの一覧を取得
					for (int32 monitorIndex = 0; ::EnumDisplayDevicesW(displayDevice.DeviceName, monitorIndex, &monitor, 0); ++monitorIndex)
					{
						if ((monitor.StateFlags & DISPLAY_DEVICE_ACTIVE) &&
							!(monitor.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
						{
							detail::MonitorCheck desc = { Unicode::FromWString(displayDevice.DeviceName), nullptr };

							// モニターのハンドルを取得
							::EnumDisplayMonitors(nullptr, nullptr, detail::MonitorCheckProc, (LPARAM)&desc);

							if (desc.second == currentMonitor)
							{
								return index;
							}

							++index;
						}

						ZeroMemory(&monitor, sizeof(monitor));
						monitor.cb = sizeof(monitor);
					}
				}

				ZeroMemory(&displayDevice, sizeof(displayDevice));
				displayDevice.cb = sizeof(displayDevice);
			}

			return 0;
		}
	}

	void Formatter(FormatData& formatData, const Monitor& value)
	{
		String output;
		output += U"Name: " + value.name + U"\n";
		output += U"ID: " + value.id + U"\n";
		output += U"DisplayDeviceName: " + value.displayDeviceName + U"\n";
		output += U"DisplayRect: " + Format(value.displayRect) + U"\n";
		output += U"WorkArea: " + Format(value.workArea) + U"\n";
		output += U"Primary: " + Format(value.isPrimary);
		formatData.string.append(output);
	}
}
