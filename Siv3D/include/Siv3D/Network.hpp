//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Optional.hpp"
# include "IPv4.hpp"

namespace s3d
{
	enum class NetworkError
	{
		OK,

		EoF,

		NoBufferSpaceAvailable,

		ConnectionRefused,

		Error,
	};

	namespace Network
	{
		[[nodiscard]] Optional<IPv4> GetPrivateIPv4();
	}
}
