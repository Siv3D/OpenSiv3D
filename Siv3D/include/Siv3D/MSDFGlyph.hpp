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
# include "Image.hpp"
# include "GlyphInfo.hpp"

namespace s3d
{
	/// @brief MSDF 用グリフ
	struct MSDFGlyph : GlyphInfo
	{
		/// @brief MSDF 画像
		Image image;
	};
}
