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
# include <string>
# include <vector>
# include <fstream>
//# include <gio/gio.h>
# include <Siv3D/PowerStatus.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace System
	{
		PowerStatus GetPowerStatus()
		{
			PowerStatus status
			{
				.ac = ACLineStatus::Unknown,
				.battery = BatteryStatus::Unknown,
				.batterySaver = false,
				.charging = false,
			};

			return status;
		}
	}	
}
