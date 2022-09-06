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
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/DLL.hpp>
# include <ShellScalingApi.h> // for GetDpiForMonitor()

namespace s3d
{
	Optional<decltype(GetDpiForMonitor)*> g_pGetDpiForMonitor;

	namespace detail
	{
		// チェック用デバイス名とモニタハンドル
		using MonitorCheck = std::pair<const String, HMONITOR>;

		static BOOL CALLBACK MonitorCallback(HMONITOR hMonitor, HDC, LPRECT, LPARAM userData)
		{
			if (not g_pGetDpiForMonitor.has_value())
			{
				g_pGetDpiForMonitor = nullptr;

				if (LibraryHandle shcore = DLL::LoadSystemLibraryNoThrow(L"Shcore.dll"))
				{
					decltype(GetDpiForMonitor)* pGetDpiForMonitor = DLL::GetFunctionNoThrow(shcore, "GetDpiForMonitor");
					*g_pGetDpiForMonitor = pGetDpiForMonitor;
				}
			}

			MONITORINFOEX monitorInfo{};
			monitorInfo.cbSize = sizeof(monitorInfo);
			::GetMonitorInfoW(hMonitor, &monitorInfo);

			MonitorInfo* monitor = reinterpret_cast<MonitorInfo*>(userData);

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

				monitor->fullscreenResolution = monitor->displayRect.size;

				if (*g_pGetDpiForMonitor)
				{
					uint32 dpiX = 0, dpiY = 0;
					if (SUCCEEDED((*g_pGetDpiForMonitor)(hMonitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)))
					{
						monitor->scaling = (dpiX / static_cast<double>(USER_DEFAULT_SCREEN_DPI));
					}
				}
				else
				{
					monitor->scaling = 1.0;
				}

				return false;
			}

			return true;
		}

		static MonitorInfo MakeMonitorInfo(const DISPLAY_DEVICEW& displayDevice, const DISPLAY_DEVICEW* monitor)
		{
			MonitorInfo monitorInfo;

			if (monitor)
			{
				monitorInfo.name = Unicode::FromWstring(monitor->DeviceString);
				monitorInfo.id = Unicode::FromWstring(monitor->DeviceID);
			}
			else
			{
				monitorInfo.name = Unicode::FromWstring(displayDevice.DeviceString);
				monitorInfo.id = Unicode::FromWstring(displayDevice.DeviceID);
			}

			monitorInfo.displayDeviceName	= Unicode::FromWstring(displayDevice.DeviceName);
			monitorInfo.isPrimary			= !!(displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE);

			{
				const HDC hdc = ::CreateDCW(L"DISPLAY", displayDevice.DeviceName, nullptr, nullptr);
				Size sizeMillimeter{ ::GetDeviceCaps(hdc, HORZSIZE),  ::GetDeviceCaps(hdc, VERTSIZE) };
				::DeleteDC(hdc);
				monitorInfo.sizeMillimeter = sizeMillimeter;
			}

			if (DEVMODE devMode{ .dmSize = sizeof(DEVMODE) };
				::EnumDisplaySettingsW(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode))
			{
				monitorInfo.refreshRate = devMode.dmDisplayFrequency;
			}

			// モニターの配置とサイズを取得
			::EnumDisplayMonitors(nullptr, nullptr, MonitorCallback, (LPARAM)&monitorInfo);

			return monitorInfo;
		}

		static BOOL CALLBACK MonitorCheckProc(HMONITOR hMonitor, HDC, LPRECT, LPARAM userData)
		{
			MONITORINFOEX monitorInfo{};
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

		static bool GetFriendlyName(Array<MonitorInfo>& monitors)
		{
			UINT32 nPaths, nModes;

			if (::GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &nPaths, &nModes) != ERROR_SUCCESS)
			{
				return false;
			}

			Array<DISPLAYCONFIG_PATH_INFO> displayPaths(nPaths);
			Array<DISPLAYCONFIG_MODE_INFO> displayModes(nModes);

			if (::QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &nPaths, displayPaths.data(), &nModes, displayModes.data(), nullptr) != ERROR_SUCCESS)
			{
				return false;
			}

			for (const auto& mode : displayModes)
			{
				if (mode.infoType != DISPLAYCONFIG_MODE_INFO_TYPE_TARGET)
				{
					continue;
				}

				const DISPLAYCONFIG_DEVICE_INFO_HEADER deviceHeader
				{
					.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME,
					.size = sizeof(DISPLAYCONFIG_TARGET_DEVICE_NAME),
					.adapterId = mode.adapterId,
					.id = mode.id,
				};

				DISPLAYCONFIG_TARGET_DEVICE_NAME deviceName
				{
					.header = deviceHeader
				};

				if (::DisplayConfigGetDeviceInfo(&deviceName.header) != ERROR_SUCCESS)
				{
					continue;
				}

				{
					String friendlyName = Unicode::FromWstring(deviceName.monitorFriendlyDeviceName);

					if ((deviceName.outputTechnology == DISPLAYCONFIG_OUTPUT_TECHNOLOGY_INTERNAL)
						|| (deviceName.outputTechnology == DISPLAYCONFIG_OUTPUT_TECHNOLOGY_DISPLAYPORT_EMBEDDED)
						|| (deviceName.outputTechnology == DISPLAYCONFIG_OUTPUT_TECHNOLOGY_UDI_EMBEDDED))
					{
						friendlyName += U"(Internal Display)";
					}

					const String id = Unicode::FromWstring(deviceName.monitorDevicePath);

					for (auto& monitor : monitors)
					{
						if (monitor.id == id)
						{
							if (friendlyName)
							{
								monitor.name = std::move(friendlyName);
							}

							break;
						}
					}
				}
			}

			return true;
		}
	}

	namespace System
	{
		Array<MonitorInfo> EnumerateMonitors()
		{
			Array<MonitorInfo> monitors;
			DISPLAY_DEVICE displayDevice{ .cb = sizeof(DISPLAY_DEVICE) };

			// デスクトップとして割り当てられている仮想ディスプレイを検索
			for (int32 deviceIndex = 0; ::EnumDisplayDevicesW(0, deviceIndex, &displayDevice, 0); ++deviceIndex)
			{
				if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
				{
					DISPLAY_DEVICE monitor{ .cb = sizeof(DISPLAY_DEVICE) };

					// デスクトップとして使われているモニターの一覧を取得
					for (int32 monitorIndex = 0; ::EnumDisplayDevicesW(displayDevice.DeviceName, monitorIndex, &monitor, EDD_GET_DEVICE_INTERFACE_NAME); ++monitorIndex)
					{
						if ((monitor.StateFlags & DISPLAY_DEVICE_ACTIVE) &&
							not(monitor.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
						{
							
							monitors.push_back(detail::MakeMonitorInfo(displayDevice, &monitor));
						}

						ZeroMemory(&monitor, sizeof(monitor));
						monitor.cb = sizeof(monitor);
					}
				}

				ZeroMemory(&displayDevice, sizeof(displayDevice));
				displayDevice.cb = sizeof(displayDevice);
			}

			// no monitor is found
			if (monitors.empty())
			{
				for (int32 deviceIndex = 0; ::EnumDisplayDevicesW(0, deviceIndex, &displayDevice, 0); ++deviceIndex)
				{
					if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
					{
						monitors.push_back(detail::MakeMonitorInfo(displayDevice, nullptr));
						break;
					}
				}
			}

			detail::GetFriendlyName(monitors);

			return monitors;
		}

		size_t GetCurrentMonitorIndex()
		{
			const HMONITOR currentMonitor = ::MonitorFromWindow(static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle()), MONITOR_DEFAULTTOPRIMARY);
			size_t index = 0;

			DISPLAY_DEVICE displayDevice =
			{
				.cb = sizeof(DISPLAY_DEVICE),
			};

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
							detail::MonitorCheck desc = { Unicode::FromWstring(displayDevice.DeviceName), nullptr };

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
}
