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
# include "StringView.hpp"
# include "ColorHSV.hpp"

namespace osc
{
	class OutboundPacketStream;
}

namespace s3d
{
	class Blob;

	/// @brief OSC 送信メッセージ
	class OSCMessage
	{
	public:

		/// @brief OSC 送信メッセージ用のバッファを構築します。
		/// @param bufferSize メッセージ用に確保するバッファサイズ
		SIV3D_NODISCARD_CXX20
		explicit OSCMessage(size_t bufferSize = 1024);

		/// @brief バンドルを開始します。
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& beginBundle();

		/// @brief バンドルを終了します。
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& endBundle();

		/// @brief メッセージを開始します。
		/// @param addressPattern アドレスパターン
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& beginMessage(StringView addressPattern);

		/// @brief メッセージを終了します。
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& endMessage();

		/// @brief bool 型の値を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addBool(bool value);

		/// @brief ASCII 文字を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addChar(char value);

		/// @brief int32 型の値を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addInt32(int32 value);

		/// @brief int64 型の値を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addInt64(int64 value);

		/// @brief float 型の値を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addFloat(float value);

		/// @brief double 型の値を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addDouble(double value);

		/// @brief MIDI メッセージを引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addMIDIMessage(uint32 value);

		/// @brief 時刻タグを引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addTimeTag(uint64 value);

		/// @brief RGBA カラーを引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addRGBA(const Color& value);

		/// @brief 文字列を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addString(StringView value);

		/// @brief シンボル文字列を引数として追加します。
		/// @param value 追加する値
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addSymbol(StringView value);

		/// @brief blob を引数として追加します。
		/// @param blob 追加するデータ
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addBlob(const Blob& blob);

		/// @brief blob を引数として追加します。
		/// @param data 追加するデータの先頭ポインタ
		/// @param size 追加するデータのサイズ（バイト）
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addBlob(const void* data, size_t size);

		/// @brief Nil 値を引数として追加します。
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addNil();

		/// @brief 無限を表す値を引数として追加します。
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& addInf();

		/// @brief 配列を開始します。
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& beginArray();

		/// @brief 配列を終了します。
		/// @throws Error バッファが不足している場合
		/// @return *this
		OSCMessage& endArray();

		[[nodiscard]]
		const osc::OutboundPacketStream* _detail() const noexcept;

	public:

		class OSCMessageDetail;

		std::shared_ptr<OSCMessageDetail> pImpl;
	};
}
