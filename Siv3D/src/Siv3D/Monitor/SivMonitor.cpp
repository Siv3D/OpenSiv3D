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

# include <Siv3D/Monitor.hpp>

namespace s3d
{
	String Monitor::format() const
	{
		String output;
		output += U"name: " + name + U"\n";
		output += U"id: " + id + U"\n";
		output += U"displayDeviceName: " + displayDeviceName + U"\n";
		output += U"displayRect: {}\n"_fmt(displayRect);
		output += U"workArea: {}\n"_fmt(workArea);

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
		Monitor GetCurrentMonitor()
		{
			auto monitors = EnumerateActiveMonitors();

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
