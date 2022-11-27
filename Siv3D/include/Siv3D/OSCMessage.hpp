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
# include "StringView.hpp"
# include "ColorHSV.hpp"

namespace osc
{
	class OutboundPacketStream;
}

namespace s3d
{
	class OSCMessage
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit OSCMessage(size_t bufferSize = 1024);

		OSCMessage& beginBundle();

		OSCMessage& endBundle();

		OSCMessage& beginMessage(StringView addressPattern);

		OSCMessage& endMessage();

		OSCMessage& addBool(bool value);

		OSCMessage& addChar(char value);

		OSCMessage& addInt32(int32 value);

		OSCMessage& addInt64(int64 value);

		OSCMessage& addFloat(float value);

		OSCMessage& addDouble(double value);

		OSCMessage& addMIDIMessage(uint32 value);

		OSCMessage& addTimeTag(uint64 value);

		OSCMessage& addRGBA(const Color& value);

		OSCMessage& addString(StringView value);

		OSCMessage& addSymbol(StringView value);

		OSCMessage& addBlob(const void* data, size_t size);

		OSCMessage& addNil();

		OSCMessage& addInf();

		OSCMessage& beginArray();

		OSCMessage& endArray();

		[[nodiscard]]
		const osc::OutboundPacketStream* _detail() const noexcept;

	public:

		class OSCMessageDetail;

		std::shared_ptr<OSCMessageDetail> pImpl;
	};
}
