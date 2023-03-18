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

# pragma once
# include <Siv3D/Serial.hpp>
# include <ThirdParty/serial/serial.h>

namespace s3d
{
	class Serial::SerialDetail
	{
	public:

		bool open(StringView port, int32 baudrate, ByteSize byteSize, Parity parity, StopBits stopBits, FlowControl flowControl);

		void close();

		bool isOpen();

		int32 baudrate() const noexcept;

		const String& port() const noexcept;

		size_t available();

		void clearInput();

		void clearOutput();

		void clear();

		size_t read(void* dst, size_t size);

		size_t write(const void* src, size_t size);

		void setRTS(bool level);

		void setDTR(bool level);

		bool waitForChange();

		bool getCTS();

		bool getDSR();

		bool getRI();

		bool getCD();

	private:

		serial::Serial m_serial;

		String m_port;

		int32 m_baudrate = 0;
	};
}
