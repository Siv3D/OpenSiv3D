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
# include "SerialDetail.hpp"

namespace s3d
{
	Serial::SerialDetail::SerialDetail()
	{

	}

	Serial::SerialDetail::SerialDetail(const String& port, const int32 baudrate)
	{
		open(port, baudrate);
	}

	bool Serial::SerialDetail::open(const String& port, int32 baudrate)
	{
		if (isOpened())
		{
			close();
		}

		m_serial.setPort(port.narrow());
		m_serial.setBaudrate(static_cast<uint32>(baudrate));
		try
		{
			m_serial.open();
		}
		catch(const serial::IOException& e)
		{
			return false;
		}

		m_port = port;
		m_baudrate = baudrate;
		return m_serial.isOpen();
	}

	void Serial::SerialDetail::close()
	{
		m_serial.close();
		m_port.clear();
		m_baudrate = 0;
	}

	bool Serial::SerialDetail::isOpened() const
	{
		return m_serial.isOpen();
	}

	int32 Serial::SerialDetail::baudrate() const noexcept
	{
		return m_baudrate;
	}

	const String& Serial::SerialDetail::port() const noexcept
	{
		return m_port;
	}

	size_t Serial::SerialDetail::available()
	{
		return m_serial.available();
	}

	void Serial::SerialDetail::clearInput()
	{
		m_serial.flushInput();
	}

	void Serial::SerialDetail::clearOutput()
	{
		m_serial.flushOutput();
	}

	void Serial::SerialDetail::clear()
	{
		m_serial.flush();
	}

	size_t Serial::SerialDetail::read(void* dst, const size_t size)
	{
		return m_serial.read(static_cast<uint8*>(dst), size);
	}

	size_t Serial::SerialDetail::write(const void* src, const size_t size)
	{
		return m_serial.write(static_cast<const uint8*>(src), size);
	}
}
