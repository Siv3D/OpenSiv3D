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

# include <Siv3D/OSCMessage.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/OSCMessage/OSCMessageDetail.hpp>

namespace s3d
{
	OSCMessage::OSCMessage(const size_t bufferSize)
		: pImpl{ std::make_shared<OSCMessageDetail>(bufferSize) } {}

	OSCMessage& OSCMessage::beginBundle()
	{
		try
		{
			pImpl->getStream() << osc::BeginBundleImmediate;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::beginBundle(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::endBundle()
	{
		try
		{
			pImpl->getStream() << osc::EndBundle;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::endBundle(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::beginMessage(const StringView addressPattern)
	{
		try
		{
			pImpl->getStream() << osc::BeginMessage(addressPattern.toUTF8().c_str());
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::beginMessage(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::endMessage()
	{
		try
		{
			pImpl->getStream() << osc::EndMessage;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::endMessage(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addBool(const bool value)
	{
		try
		{
			pImpl->getStream() << value;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addBool(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addChar(const char value)
	{
		try
		{
			pImpl->getStream() << value;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addChar(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addInt32(const int32 value)
	{
		try
		{
			pImpl->getStream() << static_cast<osc::int32>(value);
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addInt32(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addInt64(const int64 value)
	{
		try
		{
			pImpl->getStream() << static_cast<osc::int64>(value);
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addInt64(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addFloat(const float value)
	{
		try
		{
			pImpl->getStream() << value;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addFloat(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addDouble(const double value)
	{
		try
		{
			pImpl->getStream() << value;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addDouble(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addMIDIMessage(const uint32 value)
	{
		try
		{
			pImpl->getStream() << osc::MidiMessage{ value };
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addMIDIMessage(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addTimeTag(const uint64 value)
	{
		try
		{
			pImpl->getStream() << osc::TimeTag{ value };
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addTimeTag(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addRGBA(const Color& value)
	{
		try
		{
			pImpl->getStream() << osc::RgbaColor{ value.asUint32() };
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addRGBA(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addString(const StringView value)
	{
		try
		{
			const std::string utf8 = value.toUTF8();
			pImpl->getStream() << utf8.c_str();
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addString(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addSymbol(const StringView value)
	{
		try
		{
			const std::string utf8 = value.toUTF8();
			pImpl->getStream() << osc::Symbol{ utf8.c_str() };
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addSymbol(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addBlob(const Blob& blob)
	{
		return addBlob(blob.data(), blob.size_bytes());
	}

	OSCMessage& OSCMessage::addBlob(const void* data, const size_t size)
	{
		try
		{
			pImpl->getStream() << osc::Blob{ data, static_cast<osc::osc_bundle_element_size_t>(size) };
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addBlob(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addNil()
	{
		try
		{
			pImpl->getStream() << osc::OscNil;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addNil(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::addInf()
	{
		try
		{
			pImpl->getStream() << osc::Infinitum;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::addInf(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::beginArray()
	{
		try
		{
			pImpl->getStream() << osc::BeginArray;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::beginArray(), out of buffer" };
		}
	}

	OSCMessage& OSCMessage::endArray()
	{
		try
		{
			pImpl->getStream() << osc::EndArray;
			return *this;
		}
		catch (const osc::OutOfBufferMemoryException&)
		{
			throw Error{ U"OSCMessage::endArray(), out of buffer" };
		}
	}

	const osc::OutboundPacketStream* OSCMessage::_detail() const noexcept
	{
		return pImpl->getStreamPtr();
	}
}
