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
		catch(const serial::IOException&)
		{
			return false;
		}

		m_port = port;
		m_baudrate = baudrate;
		return m_serial.isOpen();
	}

	void Serial::SerialDetail::close()
	{
		try
		{
			m_serial.close();
		}
		catch (const serial::IOException&)
		{

		}

		m_port.clear();
		m_baudrate = 0;
	}

	bool Serial::SerialDetail::isOpened()
	{
		if (!m_serial.isOpen())
		{
			return false;
		}

		try
		{
			m_serial.available();
			return true;
		}
		catch (const serial::IOException&)
		{
			close();
			return false;
		}
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
		try
		{
			return m_serial.available();
		}
		catch (const serial::IOException&)
		{
			close();
			return 0;
		}
	}

	void Serial::SerialDetail::clearInput()
	{
		if (!isOpened())
		{
			return;
		}

		m_serial.flushInput();
	}

	void Serial::SerialDetail::clearOutput()
	{
		if (!isOpened())
		{
			return;
		}

		m_serial.flushOutput();
	}

	void Serial::SerialDetail::clear()
	{
		if (!isOpened())
		{
			return;
		}

		m_serial.flush();
	}

	size_t Serial::SerialDetail::read(void* dst, const size_t size)
	{
		if (!isOpened())
		{
			return 0;
		}

		try
		{
			return m_serial.read(static_cast<uint8*>(dst), size);
		}
		catch (const serial::IOException&)
		{
			close();
			return 0;
		}
	}

	size_t Serial::SerialDetail::write(const void* src, const size_t size)
	{
		if (!isOpened())
		{
			return 0;
		}

		try
		{
			return m_serial.write(static_cast<const uint8*>(src), size);
		}
		catch (const serial::IOException&)
		{
			close();
			return 0;
		}
	}
}
