﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	/// @brief フォントファイル内のグリフインデックス
	/// @remark 同じ文字であっても、フォントごとにグリフインデックスは異なります。
	/// @remark 0 は、存在しないなど無効なグリフを意味します
	using GlyphIndex = uint32;
}
