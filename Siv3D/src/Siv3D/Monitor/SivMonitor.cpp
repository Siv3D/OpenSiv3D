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

namespace s3d
{
	String MonitorInfo::format() const
	{
		String output;
		output += U"name: " + name + U"\n";
		output += U"id: " + id + U"\n";
		output += U"displayDeviceName: " + displayDeviceName + U"\n";
		output += U"displayRect: {}\n"_fmt(displayRect);
		output += U"workArea: {}\n"_fmt(workArea);
		output += U"fullscreenResolution: {}\n"_fmt(fullscreenResolution);

		if (sizeMillimeter)
		{
			output += U"sizeMillimeter: {}mm x {}mm\n"_fmt(sizeMillimeter->x, sizeMillimeter->y);
		}

		if (scaling)
		{
			output += U"scaling: {}%\n"_fmt(scaling.value() * 100);
		}

		if (refreshRate)
		{
			output += U"refreshRate: {}Hz\n"_fmt(refreshRate.value());
		}

		output += U"isPrimary: {}"_fmt(isPrimary);

		return output;
	}

	namespace System
	{
		MonitorInfo GetCurrentMonitor()
		{
			auto monitors = EnumerateMonitors();

			if (not monitors)
			{
				throw Error(U"System::GetCurrentMonitor(): No monitor found");
			}

			const size_t monitorIndex = GetCurrentMonitorIndex();

			if (monitorIndex >= monitors.size())
			{
				throw Error(U"System::GetCurrentMonitor(): Monitor index out of range");
			}

			return monitors[monitorIndex];
		}
	}
}
