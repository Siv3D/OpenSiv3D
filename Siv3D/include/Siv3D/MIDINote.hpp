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

namespace s3d
{
	/// @brief MIDI ノート
	struct MIDINote
	{
		/// @brief キー（音の高さ）
		uint32 key;

		/// @brief ノート・オンの時刻（ミリ秒）
		int32 startMillisec;

		/// @brief ノート・オンからノート・オフまでの時間（ミリ秒）
		int32 lengthMillisec;
	};
}
