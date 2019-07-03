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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include "CNetwork.hpp"

namespace s3d
{
    std::string macOS_GetPrivateIPv4();
    
	CNetwork::CNetwork()
	{

	}

	CNetwork::~CNetwork()
	{
		LOG_TRACE(U"CNetwork::~CNetwork()");
	}

	void CNetwork::init()
	{
		LOG_TRACE(U"CNetwork::init()");

		LOG_INFO(U"ℹ️ CNetwork initialized");
	}

	Optional<IPv4> CNetwork::getMachineIP() const
	{
        const String ip = Unicode::WidenAscii(macOS_GetPrivateIPv4());
        
        if (!ip.isEmpty() && !ip.starts_with(U"127"))
        {
            return IPv4(ip);
        }

		return none;
	}
	
	Array<IPv4> CNetwork::getMachineIPs() const
	{
		if (auto ip = getMachineIP())
		{
			return{ ip.value() };
		}
		else
		{
			return{};
		}
	}
}
