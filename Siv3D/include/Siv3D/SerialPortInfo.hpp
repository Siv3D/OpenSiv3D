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

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	struct SerialPortInfo
	{
		String port;

		String description;

		String hardwareID;
	};

	namespace System
	{
		[[nodiscard]]
		Array<SerialPortInfo> EnumerateSerialPorts();
	}
}
