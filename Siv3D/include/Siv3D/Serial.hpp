//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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

		/// @brief バイトサイズ
		enum class ByteSize : uint8
		{
			FiveBits	= 5,
			SixBits		= 6,
			SevenBits	= 7,
			EightBits	= 8
		};

		/// @brief パリティ
		enum class Parity : uint8
		{
			None_	= 0,
			Odd		= 1,
			Even	= 2,
			Mark	= 3,
			Space	= 4
		};

		/// @brief ストップビット
		enum StopBits : uint8
		{
			One				= 1,
			Two				= 2,
			OnePointFive
		};

		/// @brief Flow Control
		enum class FlowControl : uint8
		{
			None_,
			Software,
			Hardware
		};

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Serial();

		/// @brief シリアルポートに接続します。
		/// @param port シリアルポートの名前
		/// @param baudrate ボーレート
		/// @param byteSize バイトサイズ
		/// @param parity パリティ
		/// @param stopBits ストップビット
		/// @param flowControl Flow Control
		/// @remark シリアルポートの名前は `System::EnumerateSerialPorts()` で列挙できます。
		SIV3D_NODISCARD_CXX20
		explicit Serial(StringView port, int32 baudrate = 9600,
			ByteSize byteSize = ByteSize::EightBits, Parity parity = Parity::None_,
			StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None_);

		/// @brief デストラクタ
		/// @remark シリアルポートに接続している場合は切断します。
		~Serial();

		/// @brief シリアルポートに接続します。
		/// @param port シリアルポートの名前
		/// @param baudrate ボーレート
		/// @param byteSize バイトサイズ
		/// @param parity パリティ
		/// @param stopBits ストップビット
		/// @param flowControl Flow Control
		/// @remark シリアルポートの名前は `System::EnumerateSerialPorts()` で列挙できます。
		/// @return 接続に成功した場合 true, それ以外の場合は false
		bool open(StringView port, int32 baudrate = 9600,
			ByteSize byteSize = ByteSize::EightBits, Parity parity = Parity::None_,
			StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None_);

		/// @brief シリアルポートとの接続を切断します。
		void close();

		/// @brief シリアルポートに接続されているかを返します。
		/// @return 接続されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const;

		/// @brief シリアルポートに接続されているかを返します。
		/// @remark `isOpen()` と同じです。
		/// @return 接続されている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const;

		/// @brief ボーレートを返します。
		/// @return ボーレート
		[[nodiscard]]
		int32 baudrate() const noexcept;

		/// @brief シリアルポートの名前を返します。
		/// @return シリアルポートの名前
		[[nodiscard]]
		const String& port() const noexcept;

		/// @brief 受信済みで読み込み可能なデータのサイズ（バイト）を返します。
		/// @return 読み込み可能なデータのサイズ（バイト）
		[[nodiscard]]
		size_t available();

		/// @brief 読み込みバッファを消去します。
		void clearInput();

		/// @brief 書き込みバッファを消去します。
		void clearOutput();

		/// @brief 読み込みバッファと書き込みバッファを消去します。
		void clear();

		/// @brief 受信したデータを読み込みます。
		/// @param dst 読み込み先
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		size_t read(void* dst, size_t size);

		/// @brief 受信したデータを読み込みます。
		/// @return 読み込んだデータ
		Array<uint8> readBytes();

		/// @brief 受信したデータを読み込みます。
		/// @param dst 読み込み先
		/// @return 読み込みに成功した場合 true, それ以外の場合は false
		bool readBytes(Array<uint8>& dst);

		/// @brief 受信したデータを読み込みます。
		/// @tparam TriviallyCopyable 読み込む値の型
		/// @param to 読み込み先
		/// @return 読み込みに成功した場合 true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool read(TriviallyCopyable& to);

		/// @brief バイナリデータを書き込みます。
		/// @param src 書き込むデータの先頭ポインタ
		/// @param size 書き込むデータのサイズ（バイト）
		/// @return 書き込みに成功したバイト数
		size_t write(const void* src, size_t size);

		/// @brief 1 バイトのデータを書き込みます。
		/// @param byte 書き込むデータ
		/// @return 書き込みに成功した場合 true, それ以外の場合は false
		bool writeByte(uint8 byte);

		/// @brief 1 バイトのデータを書き込みます。
		/// @param byte 書き込むデータ
		/// @return 書き込みに成功した場合 true, それ以外の場合は false
		bool writeByte(Byte byte);

		/// @brief バイナリデータを書き込みます。
		/// @tparam TriviallyCopyable 書き込む値の型
		/// @param from 書き込むデータ
		/// @return 書き込みに成功した場合 true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool write(const TriviallyCopyable& from);

		/// @brief RTS ハンドシェイクの状態を変更します。
		/// @param level on にする場合 true, off にする場合 false
		/// @remark デフォルトでは on です。
		void setRTS(bool level);

		/// @brief DTR ハンドシェイクの状態を変更します。
		/// @param level on にする場合 true, off にする場合 false
		/// @remark デフォルトでは on です。
		void setDTR(bool level);

		/// @brief CTS, DSR, RI, CD の変更、もしくは何らかの割り込みまで待機します。
		/// @return 変更があった場合は true, それ以外の何かが起こった場合は false
		bool waitForChange();

		/// @brief CTS の状態を返します。
		/// @return CTS の状態
		[[nodiscard]]
		bool getCTS();

		/// @brief DSR の状態を返します。
		/// @return DSR の状態
		[[nodiscard]]
		bool getDSR();

		/// @brief RI の状態を返します。
		/// @return RI の状態
		[[nodiscard]]
		bool getRI();

		/// @brief CD の状態を返します。
		/// @return CD の状態
		[[nodiscard]]
		bool getCD();

	private:

		class SerialDetail;

		std::shared_ptr<SerialDetail> pImpl;
	};
}

# include "detail/Serial.ipp"
