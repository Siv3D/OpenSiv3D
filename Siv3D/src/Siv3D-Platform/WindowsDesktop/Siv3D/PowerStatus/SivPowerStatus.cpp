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

# include <Siv3D/PowerStatus.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	namespace System
	{
		PowerStatus GetPowerStatus()
		{
			SYSTEM_POWER_STATUS s;

			PowerStatus status;

			if (not ::GetSystemPowerStatus(&s))
			{
				return status;
			}

			status.ac = (s.ACLineStatus == AC_LINE_ONLINE) ? ACLineStatus::Online
				: (s.ACLineStatus == AC_LINE_OFFLINE) ? ACLineStatus::Offline : ACLineStatus::Unknown;

			status.battery = (s.BatteryFlag & BATTERY_FLAG_HIGH) ? BatteryStatus::High
				: (s.BatteryFlag & BATTERY_FLAG_LOW) ? BatteryStatus::Low
				: (s.BatteryFlag & BATTERY_FLAG_CRITICAL) ? BatteryStatus::Critical
				: (s.BatteryFlag & BATTERY_FLAG_NO_BATTERY) ? BatteryStatus::NoBattery
				: (s.BatteryFlag & BATTERY_FLAG_UNKNOWN) ? BatteryStatus::Unknown
				: BatteryStatus::Middle;

			status.charging = !!(s.BatteryFlag & BATTERY_FLAG_CHARGING);
			status.batterySaver = !!(s.SystemStatusFlag & SYSTEM_STATUS_FLAG_POWER_SAVING_ON);

			if (s.BatteryLifePercent != BATTERY_PERCENTAGE_UNKNOWN)
			{
				status.batteryLifePercent = s.BatteryLifePercent;
			}

			if (s.BatteryLifeTime != BATTERY_LIFE_UNKNOWN)
			{
				status.batteryLifeTimeSec = s.BatteryLifeTime;
			}

			if (s.BatteryFullLifeTime != BATTERY_LIFE_UNKNOWN)
			{
				status.batteryTimeToFullChargeSec = s.BatteryFullLifeTime;
			}

			return status;
		}
	}
}
