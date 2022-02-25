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
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief マイクの情報
	struct MicrophoneInfo
	{
		/// @brief `Microphone` の初期化に使うデバイス番号
		uint32 microphoneIndex = 0;

		/// @brief 名前
		String name;

		/// @brief 対応するサンプルレート
		Array<uint32> sampleRates;

		/// @brief 推奨サンプルレート
		uint32 preferredSampleRate;
	};

	namespace System
	{
		/// @brief 利用可能なマイクの一覧を返します。
		/// @return 利用可能なマイクの一覧
		[[nodiscard]]
		Array<MicrophoneInfo> EnumerateMicrophones();
	}
}
