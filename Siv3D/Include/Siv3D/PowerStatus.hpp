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

# pragma once
# include "Fwd.hpp"
# include "Optional.hpp"

namespace s3d
{
	enum class ACLineStatus
	{
		Unknown,
		
		Offline,
		
		Online,
	};

	enum class BatteryStatus
	{
		Unknown,
		
		High,

		Middle,
		
		Low,
		
		Critical,
		
		NoBattery,
	};

	struct PowerStatus
	{
		ACLineStatus ac = ACLineStatus::Unknown;

		BatteryStatus battery = BatteryStatus::Unknown;

		Optional<int32> batteryLifePercent;

		Optional<int32> batteryLifeTimeSec;

		Optional<int32> batteryTimeToFullChargeSec;

		bool charging = false;

		bool batterySaver = false;
	};

	namespace System
	{
		// macOS: 0.1ms
		PowerStatus GetPowerStatus();
	}
}
