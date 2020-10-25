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

# include <Siv3D/Windows/Windows.hpp>
# include <ShellScalingApi.h> // for GetDpiForMonitor()
# include <Siv3D/Common.hpp>
# include <Siv3D/Indexed.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/EngineLog.hpp>
# include "Monitor.hpp"

namespace s3d::detail
{
	static Rect ToRect(RECT rect)
	{
		return{ rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top) };
	}

	BOOL CALLBACK MonitorCallback(HMONITOR handle, HDC, RECT*, LPARAM data)
	{
		LOG_SCOPED_TRACE(U"MonitorCallback()");

		MONITORINFOEXW monitorInfo = { sizeof(monitorInfo) };

		LOG_VERBOSE(U"GetMonitorInfoW()");
		if (::GetMonitorInfoW(handle, &monitorInfo))
		{
			Monitor* monitor = reinterpret_cast<Monitor*>(data);

			if (Unicode::FromWstring(monitorInfo.szDevice) == monitor->adapterName)
			{
				monitor->displayRect	= detail::ToRect(monitorInfo.rcMonitor);
				monitor->workArea		= detail::ToRect(monitorInfo.rcWork);
				monitor->handle			= handle;

				uint32 dpiX = 0, dpiY = 0;
				LOG_VERBOSE(U"GetDpiForMonitor()");
				if (SUCCEEDED(::GetDpiForMonitor(handle, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)))
				{
					monitor->displayDPI = dpiX;
				}

				return false;
			}
		}

		return true;
	}

	Monitor CreateMonitor(const DISPLAY_DEVICEW& adapter, const DISPLAY_DEVICEW* display)
	{
		LOG_SCOPED_TRACE(U"CreateMonitor()");

		Monitor monitor;
		monitor.adapterString		= Unicode::FromWstring(adapter.DeviceString);
		monitor.adapterName			= Unicode::FromWstring(adapter.DeviceName);
		monitor.isPrimaryAdapter	= !!(adapter.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE);

		if (display)
		{
			monitor.displayString	= Unicode::FromWstring(display->DeviceString);
			monitor.displayName		= Unicode::FromWstring(display->DeviceName);
		}

		{
			const HDC hdc = ::CreateDCW(L"DISPLAY", adapter.DeviceName, nullptr, nullptr);
			monitor.widthMillimeter		= ::GetDeviceCaps(hdc, HORZSIZE);
			monitor.heightMillimeter	= ::GetDeviceCaps(hdc, VERTSIZE);
			::DeleteDC(hdc);
		}

		LOG_VERBOSE(U"EnumDisplayMonitors()");
		::EnumDisplayMonitors(nullptr, nullptr, MonitorCallback, (LPARAM)&monitor);

		return monitor;
	}

	Array<Monitor> EnumActiveMonitors()
	{
		LOG_SCOPED_TRACE(U"EnumActiveMonitors()");

		Array<Monitor> monitors;

		for (DWORD adapterIndex = 0;; ++adapterIndex)
		{
			DISPLAY_DEVICEW adapter = { sizeof(adapter) };

			LOG_VERBOSE(U"EnumDisplayDevicesW(nullptr, {}, ...)"_fmt(adapterIndex));
			if (!::EnumDisplayDevicesW(nullptr, adapterIndex, &adapter, 0))
			{
				break;
			}

			if (not (adapter.StateFlags & DISPLAY_DEVICE_ACTIVE))
			{
				continue;
			}

			DWORD displayIndex = 0;

			for (;; displayIndex++)
			{
				DISPLAY_DEVICEW display = { sizeof(display) };

				LOG_VERBOSE(U"EnumDisplayDevicesW(\"{}\", {}, ...)"_fmt(Unicode::FromWstring(adapter.DeviceName), displayIndex));
				if (!::EnumDisplayDevicesW(adapter.DeviceName, displayIndex, &display, 0))
				{
					break;
				}

				if (not (display.StateFlags & DISPLAY_DEVICE_ACTIVE)
					|| (display.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
				{
					continue;
				}

				monitors.push_back(CreateMonitor(adapter, &display));
			}

			if (displayIndex == 0)
			{
				monitors.push_back(CreateMonitor(adapter, nullptr));
			}
		}

		std::stable_sort(monitors.begin(), monitors.end(),
			[](const Monitor& a, const Monitor& b) { return a.isPrimaryAdapter > b.isPrimaryAdapter; });

		for (auto [i, monitor] : Indexed(monitors))
		{
			LOG_TRACE(U"🖥️ Monitor[{}]{}"_fmt(i, monitor.isPrimaryAdapter ? U" (primary)" : U""));
			LOG_TRACE(U"- adapterName: {}"_fmt(monitor.adapterName));
			LOG_TRACE(U"- adapterString: {}"_fmt(monitor.adapterString));
			LOG_TRACE(U"- displayName: {}"_fmt(monitor.displayName));
			LOG_TRACE(U"- displayString: {}"_fmt(monitor.displayString));
			LOG_TRACE(U"- size: {}mm x {}mm"_fmt(monitor.widthMillimeter, monitor.heightMillimeter));
			LOG_TRACE(U"- disprayRect: {}"_fmt(monitor.displayRect));
			LOG_TRACE(U"- workArea: {}"_fmt(monitor.workArea));
			LOG_TRACE(U"- displayDPI: {}"_fmt(monitor.displayDPI));
			LOG_TRACE(U"- handle: {}"_fmt((void*)monitor.handle));
		}

		return monitors;
	}
}
