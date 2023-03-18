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

# include <Siv3D/OSCSender.hpp>
# include <ThirdParty/oscpack/ip/IpEndpointName.h>
# include <ThirdParty/oscpack/ip/UdpSocket.h>
# include <ThirdParty/oscpack/osc/OscOutboundPacketStream.h>

namespace s3d
{
	OSCSender::OSCSender(const IPv4Address& ipv4, const int16 port)
		: m_transmitSocket{ std::make_shared<UdpTransmitSocket>(IpEndpointName{ ipv4.getData()[0], ipv4.getData()[1], ipv4.getData()[2], ipv4.getData()[3], port }) } {}

	void OSCSender::send(const OSCMessage& message)
	{
		if (not m_transmitSocket)
		{
			return;
		}

		const osc::OutboundPacketStream* pStream = message._detail();

		m_transmitSocket->Send(pStream->Data(), pStream->Size());
	}
}
