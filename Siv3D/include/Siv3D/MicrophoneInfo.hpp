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
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief マイクの情報
	struct MicrophoneInfo
	{
		uint32 microphoneIndex = 0;

		/// @brief 名前
		String name;
	};

	namespace System
	{
		/// @brief 利用可能なマイクの一覧を返します。
		/// @return 利用可能なマイクの一覧
		[[nodiscard]]
		Array<MicrophoneInfo> EnumerateMicrophones();
	}
}
