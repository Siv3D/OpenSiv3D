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
# include "IPv4Address.hpp"
# include "ReceivedOSCMessage.hpp"

namespace s3d
{
	class OSCReceiver
	{
	public:

		OSCReceiver() = default;

		OSCReceiver(const IPv4Address& ipv4, int16 port);

		~OSCReceiver();

		[[nodiscard]]
		bool hasMessages();

		[[nodiscard]]
		size_t num_messages();

		[[nodiscard]]
		ReceivedOSCMessage pop();

		void clear();

	private:

		class OSCReceiverDetail;

		std::shared_ptr<OSCReceiverDetail> pImpl;
	};
}
