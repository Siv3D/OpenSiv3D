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
# include "IPv4Address.hpp"
# include "ReceivedOSCMessage.hpp"

namespace s3d
{
	/// @brief OSC 受信クラス
	class OSCReceiver
	{
	public:

		SIV3D_NODISCARD_CXX20
		OSCReceiver();

		/// @brief OSC メッセージの受信を開始します。
		/// @param ipv4 受信側のアドレス
		/// @param port 受信側のポート番号
		SIV3D_NODISCARD_CXX20
		OSCReceiver(const IPv4Address& ipv4, int16 port);

		/// @brief OSC メッセージの受信を終了します。
		~OSCReceiver();

		/// @brief これまで受信して未取得のメッセージがあるかを返します。
		/// @return 受信して未取得のメッセージがある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasMessages();

		/// @brief これまで受信して未取得のメッセージの個数を返します。
		/// @return 受信して未取得のメッセージの個数
		[[nodiscard]]
		size_t num_messages();

		/// @brief 受信して未取得のメッセージのうち最も古いものを取得します。
		/// @throw Error 未取得のメッセージがない場合
		/// @return 未取得のメッセージのうち最も古いもの
		[[nodiscard]]
		ReceivedOSCMessage pop();

		/// @brief これまで受信して未取得のメッセージをすべて破棄します。
		void clear();

	private:

		class OSCReceiverDetail;

		std::shared_ptr<OSCReceiverDetail> pImpl;
	};
}
