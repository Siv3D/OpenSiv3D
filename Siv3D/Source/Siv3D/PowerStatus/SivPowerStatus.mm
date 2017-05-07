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


# include <algorithm>
# include <Siv3D/PowerStatus.hpp>
# import  <Cocoa/Cocoa.h>
# import  <IOKit/ps/IOPowerSources.h>
# import  <IOKit/ps/IOPSKeys.h>

namespace s3d
{
	namespace detail
	{
		void GetPowerSource(CFDictionaryRef dictionary, bool& hasAC, bool& haveBattery, bool& charging,
							Optional<int32>& maxTimeToEmptySec, Optional<int32>& percent, Optional<int32>& timeToFullSec)
		{
			CFBooleanRef bval;

			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSIsPresentKey), (const void**)&bval)
				 && (bval == kCFBooleanFalse))
			{
				return;
			}
		
			CFStringRef strval;
			
			if (!CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSPowerSourceStateKey), (const void**)&strval))
			{
				return;
			}
			
			//
			// has AC?
			//
			bool l_isAC = false;
			
			if (CFStringCompare(strval, CFSTR(kIOPSACPowerValue), 0) == kCFCompareEqualTo)
			{
				l_isAC = hasAC = true;
			}
			else if (CFStringCompare(strval, CFSTR(kIOPSBatteryPowerValue), 0) != kCFCompareEqualTo)
			{
				return;
			}
			
			//
			// time to empty
			//
			Optional<int32> timeToEmptySec;
			
			CFNumberRef numval;
			
			if (!l_isAC && CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSTimeToEmptyKey), (const void**)&numval))
			{
				SInt32 val;
				
				if (CFNumberGetValue(numval, kCFNumberSInt32Type, &val) && val > 0)
				{
					timeToEmptySec = val * 60;
				}
			}
			
			//
			// max capacity
			//
			Optional<int32> maxCapacityPaercent;
			
			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSMaxCapacityKey), (const void**)&numval))
			{
				SInt32 val;
				
				if (CFNumberGetValue(numval, kCFNumberSInt32Type, &val) && val > 0)
				{
					haveBattery = true;
					
					maxCapacityPaercent = val;
				}
			}
			
			//
			// current capacity
			//
			Optional<int32> currentCapacityPercent;
			
			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSCurrentCapacityKey), (const void**)&numval))
			{
				SInt32 val;
				
				if (CFNumberGetValue(numval, kCFNumberSInt32Type, &val) && val > 0)
				{
					currentCapacityPercent = val;
				}
			}
			
			if (currentCapacityPercent && maxCapacityPaercent)
			{
				currentCapacityPercent =
					std::min(static_cast<int32>(100.0 * currentCapacityPercent.value() / maxCapacityPaercent.value()), 100);
			}
			
			//
			// is charging?
			//
			bool l_charge = false;
			
			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSIsChargingKey), (const void**)&bval)
				&& (bval == kCFBooleanTrue))
			{
				l_charge = true;
			}
			
			//
			// time to full charge
			//
			if (l_charge && CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSTimeToFullChargeKey), (const void**)&numval))
			{
				SInt32 val;

				if (CFNumberGetValue(numval, kCFNumberSInt32Type, &val) && val > 0)
				{
					timeToFullSec = val * 60;
				}
			}

			bool choose = false;
			
			if (!timeToEmptySec && !maxTimeToEmptySec)
			{
				if (!currentCapacityPercent && !percent)
				{
					choose = true;
				}
				
				if (currentCapacityPercent > percent)
				{
					choose = true;
				}
			}
			else if (timeToEmptySec > maxTimeToEmptySec)
			{
				choose = true;
			}
			
			if (choose)
			{
				maxTimeToEmptySec = timeToEmptySec;
				percent = currentCapacityPercent;
				charging = l_charge;
			}
		}
		
		void GetPowerStatus_macOS(PowerStatus& result)
		{
			bool succeeded = false;
			
			Optional<int32> maxTimeToEmptySec, percent, timeToFullSec;
			
			if (CFTypeRef powerSourceInfo = IOPSCopyPowerSourcesInfo())
			{
				if (CFArrayRef list = IOPSCopyPowerSourcesList(powerSourceInfo))
				{
					bool hasAC = false;
					bool hasBattery = false;
					bool charging = false;
					
					const CFIndex total = CFArrayGetCount(list);
	
					for (CFIndex i = 0; i < total; ++i)
					{
						CFTypeRef t = (CFTypeRef) CFArrayGetValueAtIndex(list, i);

						if (CFDictionaryRef dictionary = IOPSGetPowerSourceDescription(powerSourceInfo, t))
						{
							GetPowerSource(dictionary, hasAC, hasBattery, charging, maxTimeToEmptySec, percent, timeToFullSec);
							
							succeeded = true;
						}
					}
					
					if (!hasBattery) // no battery
					{
						result.ac = ACLineStatus::Online;
						result.battery = BatteryStatus::NoBattery;
					}
					else if (charging) // charging
					{
						result.ac = ACLineStatus::Online;
						result.batteryTimeToFullChargeSec = timeToFullSec;
						result.battery = percent <= 5 ? BatteryStatus::Critical
						: percent <= 20 ? BatteryStatus::Low : BatteryStatus::High;
						result.charging = true;
					}
					else if (hasAC) // full charged
					{
						result.ac = ACLineStatus::Online;
						result.battery = BatteryStatus::High;
					}
					else // on battery
					{
						result.ac = ACLineStatus::Offline;
						result.battery = percent <= 5 ? BatteryStatus::Critical
						: percent <= 20 ? BatteryStatus::Low : BatteryStatus::High;
					}
					
					CFRelease(list);
				}
			
				CFRelease(powerSourceInfo);
			}
			
			if (succeeded)
			{
				if (result.ac == ACLineStatus::Offline)
				{
					result.batteryLifeTimeSec = maxTimeToEmptySec;
				}
			
				result.batteryLifePercent = percent;
				
				return;
			}

			CFTimeInterval batteryLifeTimeSec = IOPSGetTimeRemainingEstimate();
			
			if (batteryLifeTimeSec == kIOPSTimeRemainingUnlimited)
			{
				result.ac = ACLineStatus::Online;
			}
			else if (batteryLifeTimeSec == kIOPSTimeRemainingUnknown)
			{
				result.ac = ACLineStatus::Offline;
			}
			else
			{
				result.ac = ACLineStatus::Offline;
				result.batteryLifeTimeSec = batteryLifeTimeSec;
			}
		}
	}
}
