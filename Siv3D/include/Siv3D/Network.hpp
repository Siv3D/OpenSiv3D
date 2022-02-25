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
