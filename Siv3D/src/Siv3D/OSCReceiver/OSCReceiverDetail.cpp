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

# include <Siv3D/Error.hpp>
# include "OSCReceiverDetail.hpp"

namespace s3d
{
	OSCReceiver::OSCReceiverDetail::OSCReceiverDetail(const IPv4Address& ipv4, const int16 port)
		: m_listner{}
		, m_socket{ std::make_unique<UdpListeningReceiveSocket>(IpEndpointName{ ipv4.getData()[0], ipv4.getData()[1], ipv4.getData()[2], ipv4.getData()[3], port }, &m_listner) }
	{
		m_task = Async(Run, this);
	}

	OSCReceiver::OSCReceiverDetail::~OSCReceiverDetail()
	{
		if (m_task.isValid())
		{
			m_socket->AsynchronousBreak();

			m_task.get();
		}
	}

	bool OSCReceiver::OSCReceiverDetail::hasMessages()
	{
		return m_listner.hasMessages();
	}

	size_t OSCReceiver::OSCReceiverDetail::num_messages()
	{
		return m_listner.num_messages();
	}

	ReceivedOSCMessage OSCReceiver::OSCReceiverDetail::pop()
	{
		if (not m_listner.hasMessages())
		{
			throw Error{ U"OSCReceiver::pop(): no message exists" };
		}

		return m_listner.pop();
	}

	void OSCReceiver::OSCReceiverDetail::clear()
	{
		m_listner.clear();
	}

	void OSCReceiver::OSCReceiverDetail::Run(OSCReceiverDetail* osc)
	{
		osc->m_socket->Run();
	}
}
