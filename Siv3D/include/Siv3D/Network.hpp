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

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "IPv4Address.hpp"

namespace s3d
{
	namespace Network
	{
		[[nodiscard]]
		Array<IPv4Address> EnumerateIPv4Addresses();
	}
}
