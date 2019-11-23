//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <serial/serial.h>
# include <Siv3D/Serial.hpp>

namespace s3d
{
	namespace System
	{
		Array<SerialPortInfo> EnumerateSerialPorts()
		{
			Array<SerialPortInfo> infos;

			for (const auto& p : serial::list_ports())
			{
				SerialPortInfo info;
				info.port = Unicode::Widen(p.port);
				info.description = Unicode::Widen(p.description);
				info.hardwareID = Unicode::Widen(p.hardware_id);
				infos << info;
			}

			return infos;
		}
	}
}
