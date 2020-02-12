//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <serial/serial.h>
# include <Siv3D/Serial.hpp>
# include "SerialDetail.hpp"

namespace s3d
{
	Serial::Serial()
		: pImpl(std::make_shared<SerialDetail>())
	{

	}

	Serial::Serial(const String& port, const int32 baudrate)
		: pImpl(std::make_shared<SerialDetail>(port, baudrate))
	{

	}

	Serial::~Serial()
	{

	}

	bool Serial::open(const String& port, const int32 baudrate)
	{
		return pImpl->open(port, baudrate);
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

		return !dst.isEmpty();
	}

	size_t Serial::write(const void* src, const size_t size)
	{
		return pImpl->write(src, size);
	}

	bool Serial::writeByte(uint8 byte)
	{
		return write(byte);
	}

	bool Serial::writeByte(Byte byte)
	{
		return write(byte);
	}

	namespace System
	{
		Array<SerialPortInfo> EnumerateSerialPorts()
		{
			Array<SerialPortInfo> infos;

			for (const auto& p : serial::list_ports())
			{
				SerialPortInfo info;
				info.port = Unicode::Widen(p.port);
				info.description = Unicode::FromUTF8(p.description);
				info.hardwareID = Unicode::Widen(p.hardware_id);
				infos << info;
			}

			return infos;
		}
	}
}
