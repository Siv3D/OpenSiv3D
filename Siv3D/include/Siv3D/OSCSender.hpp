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
# include <memory>
# include "Common.hpp"
# include "OSCMessage.hpp"
# include "IPv4Address.hpp"

class UdpTransmitSocket;

namespace s3d
{
	class OSCSender
	{
	public:

		SIV3D_NODISCARD_CXX20
		OSCSender() = default;

		SIV3D_NODISCARD_CXX20
		OSCSender(const IPv4Address& ipv4, int16 port);

		void send(const OSCMessage& message);

	public:

		std::shared_ptr<UdpTransmitSocket> m_transmitSocket;
	};
}
