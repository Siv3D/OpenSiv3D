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

# include <Siv3D/OSCReceiver.hpp>
# include <Siv3D/OSCReceiver/OSCReceiverDetail.hpp>

namespace s3d
{
	OSCReceiver::OSCReceiver()
		: pImpl{ std::make_shared<OSCReceiverDetail>() } {}

	OSCReceiver::OSCReceiver(const IPv4Address& ipv4, const int16 port)
		: pImpl{ std::make_shared<OSCReceiverDetail>(ipv4, port) } {}

	OSCReceiver::~OSCReceiver() {}

	bool OSCReceiver::hasMessages()
	{
		return pImpl->hasMessages();
	}

	size_t OSCReceiver::num_messages()
	{
		return pImpl->num_messages();
	}

	ReceivedOSCMessage OSCReceiver::pop()
	{
		return pImpl->pop();
	}

	void OSCReceiver::clear()
	{
		pImpl->clear();
	}
}
