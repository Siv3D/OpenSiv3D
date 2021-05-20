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

namespace s3d
{
	/// @brief 録音のフォーマット
	enum class RecordingFormat : uint8
	{
		/// @brief ステレオ 11,025 Hz
		Stereo_11025Hz,

		/// @brief ステレオ 22,050 Hz
		Stereo_22050Hz,

		/// @brief ステレオ 44,100 Hz
		Stereo_44100Hz,

		/// @brief ステレオ 48,000 Hz
		Stereo_48000Hz,

		/// @brief ステレオ 96,000 Hz
		Stereo_96000Hz,

		/// @brief デフォルト（ステレオ 44,100 Hz）
		Default = Stereo_44100Hz,
	};
}
