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

# include <Siv3DEngine.hpp>
# include <Siv3D/Network.hpp>
# include "INetwork.hpp"

namespace s3d
{
	namespace Network
	{
		Optional<IPv4> GetPrivateIPv4()
		{
			return Siv3DEngine::Get<ISiv3DNetwork>()->getMachineIP();
		}
	}
}
