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
	/// @brief 
	enum class QRMode : uint8
	{
		/// @brief 無効なデータ
		Invalid,

		/// @brief 数字
		Numeric,

		/// @brief 0-9, A-Z, $ % * + - . / : と半角スペース。小文字と大文字は区別されない
		Alnum,

		/// @brief バイナリ
		Binary,

		/// @brief 漢字・かな (Shift_JIS)
		Kanji,
	};
}
