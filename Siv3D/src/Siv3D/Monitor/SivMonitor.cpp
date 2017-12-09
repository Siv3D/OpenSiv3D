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

# include <Siv3D/Windows.hpp>
# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"

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

			Monitor* monitor = (Monitor*)userData;

			if (monitor->displayDeviceName.toWstr() == monitorInfo.szDevice)
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
		Array<Monitor> EnumActiveMonitors()
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
			const HMONITOR currentMonitor = ::MonitorFromWindow(Siv3DEngine::GetWindow()->getHandle(), MONITOR_DEFAULTTOPRIMARY);
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
}

# elif defined(SIV3D_TARGET_MACOS)

# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Window.hpp>

namespace s3d
{
	namespace System
	{
		Array<Monitor> EnumActiveMonitors()
		{
			Array<Monitor> results;
			
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			
			for (int32 i = 0; i < numMonitors; ++i)
			{
				GLFWmonitor* monitor = monitors[i];
				
				Monitor result;
				result.name = Unicode::Widen(::glfwGetMonitorName(monitor));
				
				uint32 displayID, unitNumber;
				int32 xPos, yPos, width, height;
				int32 wx, wy, ww, wh;
				glfwGetMonitorInfo_Siv3D(monitor, &displayID, &unitNumber,
										 &xPos, &yPos, &width, &height,
										 &wx, &wy, &ww, &wh);
				result.id = Format(displayID);
				result.displayDeviceName = Format(unitNumber);
				result.displayRect.x = xPos;
				result.displayRect.y = yPos;
				result.displayRect.w = width;
				result.displayRect.h = height;
				result.workArea.x = wx;
				result.workArea.y = wy;
				result.workArea.w = ww;
				result.workArea.h = wh;
				result.isPrimary = (i == 0);

				results.push_back(result);
			}
			
			return results;
		}

		size_t GetCurrentMonitorIndex()
		{
			const auto& state = Window::GetState();
			const Point pos = state.pos;
			const Size size = state.windowSize;
			
			const auto monitors = EnumActiveMonitors();
			int32 bestoverlap = 0;
			size_t bestIndex = 0;
			
			for (size_t i = 0; i < monitors.size(); ++i)
			{
				const auto& monitor = monitors[i];
				const Point mPos = monitor.displayRect.pos;
				const Size mSize = monitor.displayRect.size;

				const int32 overlap =
					std::max(0, std::min(pos.x + size.x, mPos.x + mSize.x) - std::max(pos.x, mPos.x)) *
					std::max(0, std::min(pos.y + size.y, mPos.y + mSize.y) - std::max(pos.y, mPos.y));
				
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

# elif defined(SIV3D_TARGET_LINUX)

# include "../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Window.hpp>

namespace s3d
{
	namespace System
	{
		Array<Monitor> EnumActiveMonitors()
		{
			Array<Monitor> results;
			
			int32 numMonitors;
			GLFWmonitor** monitors = ::glfwGetMonitors(&numMonitors);
			
			for (int32 i = 0; i < numMonitors; ++i)
			{
				GLFWmonitor* monitor = monitors[i];
				
				Monitor result;
				result.name = Unicode::Widen(::glfwGetMonitorName(monitor));
				
				uint32 displayID;
				int32 xPos, yPos, width, height;
				int32 wx, wy, ww, wh;
				char* name = nullptr;
				glfwGetMonitorInfo_Siv3D(monitor, &displayID, &name,
										 &xPos, &yPos, &width, &height,
										 &wx, &wy, &ww, &wh);
				result.id = Format(displayID);
				result.displayDeviceName = Unicode::Widen(name);
				result.displayRect.x = xPos;
				result.displayRect.y = yPos;
				result.displayRect.w = width;
				result.displayRect.h = height;
				result.workArea.x = wx;
				result.workArea.y = wy;
				result.workArea.w = ww;
				result.workArea.h = wh;
				result.isPrimary = (i == 0);

				results.push_back(result);

				::free(name); // free monitor name buffer.
			}
			
			return results;
		}

		size_t GetCurrentMonitorIndex()
		{
			const auto& state = Window::GetState();
			const Point pos = state.pos;
			const Size size = state.windowSize;
			
			const auto monitors = EnumActiveMonitors();
			int32 bestoverlap = 0;
			size_t bestIndex = 0;
			
			for (size_t i = 0; i < monitors.size(); ++i)
			{
				const auto& monitor = monitors[i];
				const Point mPos = monitor.displayRect.pos;
				const Size mSize = monitor.displayRect.size;

				const int32 overlap =
					std::max(0, std::min(pos.x + size.x, mPos.x + mSize.x) - std::max(pos.x, mPos.x)) *
					std::max(0, std::min(pos.y + size.y, mPos.y + mSize.y) - std::max(pos.y, mPos.y));
				
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

# endif

namespace s3d
{
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
