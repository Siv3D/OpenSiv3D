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

# include <Siv3D/Unicode.hpp>
# include "OSCPacketListener.hpp"

namespace s3d
{
	bool OSCPacketListener::hasMessages()
	{
		std::lock_guard lock{ m_mutex };

		return (not m_messages.empty());
	}

	size_t OSCPacketListener::num_messages()
	{
		std::lock_guard lock{ m_mutex };

		return m_messages.size();
	}

	ReceivedOSCMessage OSCPacketListener::pop()
	{
		std::lock_guard lock{ m_mutex };

		ReceivedOSCMessage message = m_messages.front();

		m_messages.pop();

		return message;
	}

	void OSCPacketListener::clear()
	{
		std::lock_guard lock{ m_mutex };

		while (not m_messages.empty())
		{
			m_messages.pop();
		}
	}

	void OSCPacketListener::push(ReceivedOSCMessage&& message)
	{
		std::lock_guard lock{ m_mutex };

		m_messages.push(std::move(message));
	}

	void OSCPacketListener::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName&)
	{
		try
		{
			ReceivedOSCMessage message;
			message.addressPattern = Unicode::WidenAscii(m.AddressPattern());
			message.arguments.resize(m.ArgumentCount());

			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();

			for (auto& argument : message.arguments)
			{
				argument.tag = OSCTypeTag{ arg->TypeTag() };

				switch (arg->TypeTag())
				{
				case osc::TypeTagValues::FALSE_TYPE_TAG:
				case osc::TypeTagValues::TRUE_TYPE_TAG:
					argument.value = arg->AsBoolUnchecked();
					break;
				case osc::TypeTagValues::CHAR_TYPE_TAG:
					argument.value = arg->AsCharUnchecked();
					break;
				case osc::TypeTagValues::INT32_TYPE_TAG:
					argument.value = static_cast<int32>(arg->AsInt32Unchecked());
					break;
				case osc::TypeTagValues::INT64_TYPE_TAG:
					argument.value = static_cast<int64>(arg->AsInt64Unchecked());
					break;
				case osc::TypeTagValues::FLOAT_TYPE_TAG:
					argument.value = arg->AsFloatUnchecked();
					break;
				case osc::TypeTagValues::DOUBLE_TYPE_TAG:
					argument.value = arg->AsDoubleUnchecked();
					break;
				case osc::TypeTagValues::MIDI_MESSAGE_TYPE_TAG:
					argument.value = static_cast<uint32>(arg->AsMidiMessageUnchecked());
					break;
				case osc::TypeTagValues::TIME_TAG_TYPE_TAG:
					argument.value = static_cast<uint64>(arg->AsTimeTagUnchecked());
					break;
				case osc::TypeTagValues::RGBA_COLOR_TYPE_TAG:
					argument.value = Color::FromRGBA(arg->AsRgbaColorUnchecked());
					break;
				case osc::TypeTagValues::STRING_TYPE_TAG:
					argument.value = Unicode::FromUTF8(arg->AsStringUnchecked());
					break;
				case osc::TypeTagValues::SYMBOL_TYPE_TAG:
					argument.value = Unicode::FromUTF8(arg->AsSymbolUnchecked());
					break;
				case osc::TypeTagValues::BLOB_TYPE_TAG:
					argument.value = arg->AsBlobUnchecked();
					break;
				case osc::TypeTagValues::NIL_TYPE_TAG:
				case osc::TypeTagValues::INFINITUM_TYPE_TAG:
				case osc::TypeTagValues::ARRAY_BEGIN_TYPE_TAG:
				case osc::TypeTagValues::ARRAY_END_TYPE_TAG:
				default:
					break;
				}

				++arg;
			}

			push(std::move(message));
		}
		catch (osc::Exception&)
		{

		}
	}
}
