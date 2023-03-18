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
# include <mutex>
# include <queue>
# include <Siv3D/ReceivedOSCMessage.hpp>
# include <ThirdParty/oscpack/osc/OscPacketListener.h>

namespace s3d
{
	class OSCPacketListener : public osc::OscPacketListener
	{
	public:

		[[nodiscard]]
		bool hasMessages();

		[[nodiscard]]
		size_t num_messages();

		[[nodiscard]]
		ReceivedOSCMessage pop();

		void clear();

	private:

		std::mutex m_mutex;

		std::queue<ReceivedOSCMessage> m_messages;

		void push(ReceivedOSCMessage&& message);

		void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName&) override;
	};
}
