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

# pragma once
# include <Siv3D/Serial.hpp>

namespace s3d
{
	class Serial::SerialDetail
	{
	private:

		serial::Serial m_serial;

		String m_port;

		int32 m_baudrate = 0;

	public:

		SerialDetail();

		SerialDetail(const String& port, int32 baudrate);

		bool open(const String& port, int32 baudrate);

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
	};
}
