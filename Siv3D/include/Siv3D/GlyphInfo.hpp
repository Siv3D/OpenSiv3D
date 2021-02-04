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
	/// @brief フォントファイル内のグリフインデックス
	using GlyphIndex = uint32;

	/// @brief グリフ情報
	struct GlyphInfo
	{
		/// @brief グリフインデックス
		GlyphIndex glyphIndex = 0;

		/// @brief X 方向の移動
		int32 xAdvance = 0;

		/// @brief Y 方向の移動
		int32 yAdvance = 0;
	};
}
