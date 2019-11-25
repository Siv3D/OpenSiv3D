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
# include "Fwd.hpp"
# include "Array.hpp"

namespace s3d
{
	class Serial
	{
	private:

		class SerialDetail;

		std::shared_ptr<SerialDetail> pImpl;

	public:

		Serial();

		explicit Serial(const String& port, int32 baudrate = 9600);

		~Serial();

		bool open(const String& port, int32 baudrate = 9600);

		void close();

		[[nodiscard]] bool isOpened() const;

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] int32 baudrate() const noexcept;

		[[nodiscard]] const String& port() const noexcept;

		[[nodiscard]] size_t available();

		void clearInput();

		void clearOutput();

		void clear();

		size_t read(void* dst, size_t size);

		Array<uint8> readBytes();

		bool readBytes(Array<uint8>& dst);

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>> * = nullptr>
		bool read(Type& to)
		{
			return read(std::addressof(to), sizeof(Type)) == sizeof(Type);
		}

		size_t write(const void* src, size_t size);

		bool writeByte(uint8 byte);

		bool writeByte(Byte byte);

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>> * = nullptr>
		bool write(const Type& from)
		{
			return (write(std::addressof(from), sizeof(Type))) == sizeof(Type);
		}
	};

	struct SerialPortInfo
	{
		String port;

		String description;

		String hardwareID;
	};

	namespace System
	{
		[[nodiscard]] Array<SerialPortInfo> EnumerateSerialPorts();
	}
}
