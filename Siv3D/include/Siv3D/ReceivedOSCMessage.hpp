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
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "OSCArgument.hpp"

namespace s3d
{
	/// @brief OSC 受信メッセージ
	struct ReceivedOSCMessage
	{
		/// @brief アドレスパターン
		String addressPattern;

		/// @brief 引数
		Array<OSCArgument> arguments;
	};
}
