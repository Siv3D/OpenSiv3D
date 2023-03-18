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

# include <Siv3D/Serial.hpp>
# include "SerialDetail.hpp"

namespace s3d
{
	Serial::Serial()
		: pImpl{ std::make_shared<SerialDetail>() } {}

	Serial::Serial(const StringView port, const int32 baudrate,
		const ByteSize byteSize, const Parity parity, const StopBits stopBits, const FlowControl flowControl)
		: Serial{}
	{
		open(port, baudrate, byteSize, parity, stopBits, flowControl);
	}

	Serial::~Serial() {}

	bool Serial::open(const StringView port, const int32 baudrate,
		const ByteSize byteSize, const Parity parity, const StopBits stopBits, const FlowControl flowControl)
	{
		return pImpl->open(port, baudrate, byteSize, parity, stopBits, flowControl);
	}

	void Serial::close()
	{
		pImpl->close();
	}

	bool Serial::isOpen() const
	{
		return pImpl->isOpen();
	}

	Serial::operator bool() const
	{
		return isOpen();
	}

	int32 Serial::baudrate() const noexcept
	{
		return pImpl->baudrate();
	}

	const String& Serial::port() const noexcept
	{
		return pImpl->port();
	}

	size_t Serial::available()
	{
		return pImpl->available();
	}

	void Serial::clearInput()
	{
		pImpl->clearInput();
	}

	void Serial::clearOutput()
	{
		pImpl->clearOutput();
	}

	void Serial::clear()
	{
		pImpl->clear();
	}

	size_t Serial::read(void* dst, const size_t size)
	{
		return pImpl->read(dst, size);
	}

	Array<uint8> Serial::readBytes()
	{
		Array<uint8> result(available());

		if (result)
		{
			read(result.data(), result.size_bytes());
		}

		return result;
	}

	bool Serial::readBytes(Array<uint8>& dst)
	{
		dst.clear();

		dst.resize(available());

		if (dst)
		{
			read(dst.data(), dst.size_bytes());
		}

		return (not dst.isEmpty());
	}

	size_t Serial::write(const void* src, const size_t size)
	{
		return pImpl->write(src, size);
	}

	bool Serial::writeByte(const uint8 byte)
	{
		return write(byte);
	}

	bool Serial::writeByte(const Byte byte)
	{
		return write(byte);
	}

	void Serial::setRTS(const bool level)
	{
		pImpl->setRTS(level);
	}

	void Serial::setDTR(const bool level)
	{
		pImpl->setDTR(level);
	}

	bool Serial::waitForChange()
	{
		return pImpl->waitForChange();
	}

	bool Serial::getCTS()
	{
		return pImpl->getCTS();
	}

	bool Serial::getDSR()
	{
		return pImpl->getDSR();
	}

	bool Serial::getRI()
	{
		return pImpl->getRI();
	}

	bool Serial::getCD()
	{
		return pImpl->getCD();
	}
}
