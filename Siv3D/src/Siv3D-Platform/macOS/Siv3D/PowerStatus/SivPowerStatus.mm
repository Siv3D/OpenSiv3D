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

# include <algorithm>
# include <Siv3D/PowerStatus.hpp>
# import  <Cocoa/Cocoa.h>
# import  <IOKit/ps/IOPowerSources.h>
# import  <IOKit/ps/IOPSKeys.h>

namespace s3d
{
	namespace detail
	{
		static void GetPowerSource(CFDictionaryRef dictionary, bool& hasAC, bool& hasBattery, bool& charging,
							Optional<int32>& maxTimeToEmptySec, Optional<int32>& percent, Optional<int32>& timeToFullSec)
		{
			CFBooleanRef b;
			
			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSIsPresentKey), (const void**)&b)
				&& (b == kCFBooleanFalse))
			{
				return;
			}
			
			CFStringRef str;
			
			if (!CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSPowerSourceStateKey), (const void**)&str))
			{
				return;
			}
			
			//
			// has AC?
			//
			bool isAC = false;
			
			if (CFStringCompare(str, CFSTR(kIOPSACPowerValue), 0) == kCFCompareEqualTo)
			{
				isAC = hasAC = true;
			}
			else if (CFStringCompare(str, CFSTR(kIOPSBatteryPowerValue), 0) != kCFCompareEqualTo)
			{
				return;
			}
			
			//
			// time to empty
			//
			Optional<int32> timeToEmptySec;
			
			CFNumberRef num;
			
			if (!isAC && CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSTimeToEmptyKey), (const void**)&num))
			{
				SInt32 val;
				
				if (CFNumberGetValue(num, kCFNumberSInt32Type, &val) && (val > 0))
				{
					timeToEmptySec = val * 60;
				}
			}
			
			//
			// max capacity
			//
			Optional<int32> maxCapacityPaercent;
			
			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSMaxCapacityKey), (const void**)&num))
			{
				SInt32 val;
				
				if (CFNumberGetValue(num, kCFNumberSInt32Type, &val) && (val > 0))
				{
					hasBattery = true;
					
					maxCapacityPaercent = val;
				}
			}
			
			//
			// current capacity
			//
			Optional<int32> currentCapacityPercent;
			
			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSCurrentCapacityKey), (const void**)&num))
			{
				SInt32 val;
				
				if (CFNumberGetValue(num, kCFNumberSInt32Type, &val) && (val > 0))
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
			bool isCharging = false;
			
			if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSIsChargingKey), (const void**)&b)
				&& (b == kCFBooleanTrue))
			{
				isCharging = true;
				
				//
				// time to full charge
				//
				if (CFDictionaryGetValueIfPresent(dictionary, CFSTR(kIOPSTimeToFullChargeKey), (const void**)&num))
				{
					SInt32 val;
					
					if (CFNumberGetValue(num, kCFNumberSInt32Type, &val) && (val > 0))
					{
						timeToFullSec = val * 60;
					}
				}
			}
			
			bool update = false;
			
			if (!timeToEmptySec && !maxTimeToEmptySec)
			{
				update = (!currentCapacityPercent && !percent)
				|| (currentCapacityPercent > percent);
			}
			else
			{
				update = (timeToEmptySec > maxTimeToEmptySec);
			}
			
			if (!update)
			{
				return;
			}
			
			maxTimeToEmptySec = timeToEmptySec;
			
			percent = currentCapacityPercent;
			
			charging = isCharging;
		}
	}
		
	namespace System
	{
		PowerStatus GetPowerStatus()
		{
			PowerStatus result;
			
			Optional<int32> maxTimeToEmptySec, percent, timeToFullSec;
			
			if (CFTypeRef powerSourceInfo = IOPSCopyPowerSourcesInfo())
			{
				if (CFArrayRef list = IOPSCopyPowerSourcesList(powerSourceInfo))
				{
					bool hasAC = false, hasBattery = false, charging = false;
					
					const CFIndex total = CFArrayGetCount(list);
					
					for (CFIndex i = 0; i < total; ++i)
					{
						CFTypeRef t = (CFTypeRef) CFArrayGetValueAtIndex(list, i);
						
						if (CFDictionaryRef dictionary = IOPSGetPowerSourceDescription(powerSourceInfo, t))
						{
							detail::GetPowerSource(dictionary, hasAC, hasBattery, charging, maxTimeToEmptySec, percent, timeToFullSec);
						}
					}
					
					if (!hasBattery) // no battery
					{
						result.ac = ACLineStatus::Online;
						result.battery = BatteryStatus::NoBattery;
					}
					else
					{
						result.battery = percent <= 5 ? BatteryStatus::Critical
						: percent <= 33 ? BatteryStatus::Low
						: percent <= 66 ? BatteryStatus::Middle
						: BatteryStatus::High;
						
						result.batteryLifePercent = percent;
						
						if (charging) // charging
						{
							result.ac = ACLineStatus::Online;
							result.batteryTimeToFullChargeSec = timeToFullSec;
							result.charging = true;
						}
						else if (hasAC) // full charged
						{
							result.ac = ACLineStatus::Online;
						}
						else // on battery
						{
							result.ac = ACLineStatus::Offline;
							result.batteryLifeTimeSec = maxTimeToEmptySec;
						}
					}
					
					CFRelease(list);
				}
				
				CFRelease(powerSourceInfo);
			}
			
			if (result.ac == ACLineStatus::Unknown)
			{
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
			
			return result;
		}
	}
}
