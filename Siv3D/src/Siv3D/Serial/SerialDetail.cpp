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

# include "SerialDetail.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	bool Serial::SerialDetail::open(const StringView port, const int32 baudrate,
		const ByteSize byteSize, const Parity parity, const StopBits stopBits, const FlowControl flowControl)
	{
		if (isOpen())
		{
			close();
		}

		m_serial.setPort(port.narrow());
		m_serial.setBaudrate(static_cast<uint32>(baudrate));
		m_serial.setBytesize(static_cast<serial::bytesize_t>(FromEnum(byteSize)));
		m_serial.setParity(static_cast<serial::parity_t>(FromEnum(parity)));
		m_serial.setStopbits(static_cast<serial::stopbits_t>(FromEnum(stopBits)));
		m_serial.setFlowcontrol(static_cast<serial::flowcontrol_t>(FromEnum(flowControl)));
		try
		{
			m_serial.open();
		}
		catch (const serial::IOException& e)
		{
			LOG_FAIL(U"❌ Failed to open Serial `{0}`. {1}"_fmt(port, Unicode::Widen(e.what())));
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

	bool Serial::SerialDetail::isOpen()
	{
		if (not m_serial.isOpen())
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
		if (not isOpen())
		{
			return;
		}

		m_serial.flushInput();
	}

	void Serial::SerialDetail::clearOutput()
	{
		if (not isOpen())
		{
			return;
		}

		m_serial.flushOutput();
	}

	void Serial::SerialDetail::clear()
	{
		if (not isOpen())
		{
			return;
		}

		m_serial.flush();
	}

	size_t Serial::SerialDetail::read(void* dst, const size_t size)
	{
		if (not isOpen())
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
		if (not isOpen())
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

	void Serial::SerialDetail::setRTS(const bool level)
	{
		if (not isOpen())
		{
			return;
		}

		m_serial.setRTS(level);
	}

	void Serial::SerialDetail::setDTR(const bool level)
	{
		if (not isOpen())
		{
			return;
		}

		m_serial.setDTR(level);
	}

	bool Serial::SerialDetail::waitForChange()
	{
		if (not isOpen())
		{
			return false;
		}

		try
		{
			return m_serial.waitForChange();
		}
		catch (const serial::SerialException&)
		{
			return false;
		}
	}

	bool Serial::SerialDetail::getCTS()
	{
		if (not isOpen())
		{
			return false;
		}

		return m_serial.getCTS();
	}

	bool Serial::SerialDetail::getDSR()
	{
		if (not isOpen())
		{
			return false;
		}

		return m_serial.getDSR();
	}

	bool Serial::SerialDetail::getRI()
	{
		if (not isOpen())
		{
			return false;
		}

		return m_serial.getRI();
	}

	bool Serial::SerialDetail::getCD()
	{
		if (not isOpen())
		{
			return false;
		}

		return m_serial.getCD();
	}
}
