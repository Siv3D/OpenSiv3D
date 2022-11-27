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

namespace s3d
{
	/// @brief OSC 型タグ
	enum class OSCTypeTag : char
	{
		/// @brief False
		False		= 'F',

		/// @brief True
		True		= 'T',

		/// @brief ASCII 文字
		Char		= 'c',

		/// @brief int32
		Int32		= 'i',

		/// @brief int64
		Int64		= 'h',

		/// @brief float32
		Float		= 'f',

		/// @brief float64
		Double		= 'd',

		/// @brief MIDI メッセージ
		MIDIMessage	= 'm',

		/// @brief 時刻タグ
		TimeTag		= 't',

		/// @brief RGBA カラー
		RGBAColor	= 'r',

		/// @brief OSC 文字列
		String		= 's',

		/// @brief OSC 文字列（シンボル）
		Symbol		= 'S',

		/// @brief blob
		Blob		= 'b',

		/// @brief Nil
		Nil			= 'N',

		/// @brief 無限
		Infinitum	= 'I',

		/// @brief 配列の開始
		ArrayBegin	= '[',

		/// @brief 配列の終了
		ArrayEnd	= ']'
	};
}
