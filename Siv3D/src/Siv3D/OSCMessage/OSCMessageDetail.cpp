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

# include "OSCMessageDetail.hpp"

namespace s3d
{
	OSCMessage::OSCMessageDetail::OSCMessageDetail(const size_t bufferSize)
		: m_buffer(bufferSize, '\0')
		, m_stream{ m_buffer.data(), bufferSize } {}

	osc::OutboundPacketStream& OSCMessage::OSCMessageDetail::getStream()
	{
		return m_stream;
	}

	const osc::OutboundPacketStream* OSCMessage::OSCMessageDetail::getStreamPtr() const
	{
		return &m_stream;
	}
}
