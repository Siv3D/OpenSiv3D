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
# include "Mesh.hpp"
# include "GlyphInfo.hpp"

namespace s3d
{
	struct MeshGlyph
	{
		Mesh mesh;

		/// @brief グリフインデックス
		GlyphIndex glyphIndex = 0;

		/// @brief X 方向の移動
		double xAdvance = 0;

		/// @brief Y 方向の移動
		double yAdvance = 0;

		double xOffset = 0.0;
	};
}
