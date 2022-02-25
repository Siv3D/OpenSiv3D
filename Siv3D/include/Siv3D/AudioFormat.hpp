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
	/// @brief 音声フォーマット
	enum class AudioFormat : uint8
	{
		/// @brief 不明
		Unknown,

		/// @brief WAVE
		WAVE,

		/// @brief MP3
		MP3,

		/// @brief AAC
		AAC,

		/// @brief Ogg Vorbis
		OggVorbis,

		/// @brief Opus
		Opus,

		/// @brief WMA
		WMA,

		/// @brief AIFF
		AIFF,

		/// @brief FLAC
		FLAC,

		/// @brief MIDI
		MIDI,

		/// @brief 指定しない（データと拡張子から判断）
		Unspecified = Unknown,
	};
}
