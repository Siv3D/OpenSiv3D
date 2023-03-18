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
# include <Siv3D/OSCReceiver.hpp>
# include "OSCPacketListener.hpp"
# include <Siv3D/AsyncTask.hpp>
# include <ThirdParty/oscpack/ip/IpEndpointName.h>
# include <ThirdParty/oscpack/ip/UdpSocket.h>

namespace s3d
{
	class OSCReceiver::OSCReceiverDetail
	{
	public:

		OSCReceiverDetail() = default;

		OSCReceiverDetail(const IPv4Address& ipv4, int16 port);

		~OSCReceiverDetail();

		[[nodiscard]]
		bool hasMessages();

		[[nodiscard]]
		size_t num_messages();

		[[nodiscard]]
		ReceivedOSCMessage pop();

		void clear();

	private:

		static void Run(OSCReceiverDetail* osc);

		OSCPacketListener m_listner;

		std::unique_ptr<UdpListeningReceiveSocket> m_socket;

		AsyncTask<void> m_task;
	};
}
