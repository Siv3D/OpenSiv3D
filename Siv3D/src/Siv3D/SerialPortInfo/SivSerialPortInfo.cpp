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

# include <Siv3D/SerialPortInfo.hpp>
# include <Siv3D/Unicode.hpp>
# include <ThirdParty/serial/serial.h>

namespace s3d
{
	namespace System
	{
		Array<SerialPortInfo> EnumerateSerialPorts()
		{
			const std::vector<serial::PortInfo> portInfo = serial::list_ports();

			Array<SerialPortInfo> results(portInfo.size());

			for (size_t i = 0; i < portInfo.size(); ++i)
			{
				const auto& info = portInfo[i];
				auto& result = results[i];
				result.port			= Unicode::Widen(info.port);
				result.description	= Unicode::FromUTF8(info.description);
				result.hardwareID	= Unicode::Widen(info.hardware_id);
			}

			return results;
		}
	}
}
