//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Array.hpp"
# include "StringView.hpp"
# include "Byte.hpp"

namespace s3d
{
	/// @brief シリアル通信
	class Serial
	{
	public:

		enum class ByteSize
		{
			FiveBits	= 5,
			SixBits		= 6,
			SevenBits	= 7,
			EightBits	= 8
		};

		enum class Parity
		{
			None_	= 0,
			Odd		= 1,
			Even	= 2,
			Mark	= 3,
			Space	= 4
		};

		enum StopBits
		{
			One				= 1,
			Two				= 2,
			OnePointFive
		};

		enum class FlowControl
		{
			None_,
			Software,
			Hardware
		};

		Serial();

		explicit Serial(StringView port, int32 baudrate = 9600,
			ByteSize byteSize = ByteSize::EightBits, Parity parity = Parity::None_,
			StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None_);

		~Serial();

		bool open(StringView port, int32 baudrate = 9600,
			ByteSize byteSize = ByteSize::EightBits, Parity parity = Parity::None_,
			StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None_);

		void close();

		[[nodiscard]]
		bool isOpen() const;

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		int32 baudrate() const noexcept;

		[[nodiscard]]
		const String& port() const noexcept;

		[[nodiscard]]
		size_t available();

		void clearInput();

		void clearOutput();

		void clear();

		size_t read(void* dst, size_t size);

		Array<uint8> readBytes();

		bool readBytes(Array<uint8>& dst);

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool read(TriviallyCopyable& to);

		size_t write(const void* src, size_t size);

		bool writeByte(uint8 byte);

		bool writeByte(Byte byte);

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool write(const TriviallyCopyable& from);

		void setRTS(bool level);

		void setDTR(bool level);

		bool waitForChange();

		bool getCTS();

		bool getDSR();

		bool getRI();

		bool getCD();

	private:

		class SerialDetail;

		std::shared_ptr<SerialDetail> pImpl;
	};
}

# include "detail/Serial.ipp"
