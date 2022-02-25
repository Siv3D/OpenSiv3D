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
# include "PointVector.hpp"
# include "GlyphIndex.hpp"

namespace s3d
{
	/// @brief グリフ情報
	struct GlyphInfo
	{
		/// @brief グリフインデックス
		GlyphIndex glyphIndex = 0;

		int32 buffer = 0;

		int16 left = 0;

		int16 top = 0;

		int16 width = 0;

		int16 height = 0;

		int16 ascender = 0;

		int16 descender = 0;

		/// @brief X 方向の移動
		double xAdvance = 0;

		/// @brief Y 方向の移動
		double yAdvance = 0;

		[[nodiscard]]
		constexpr Vec2 getOffset(double scale = 1.0) const noexcept;

		[[nodiscard]]
		constexpr Vec2 getBase(double scale = 1.0) const noexcept;
	};
}

# include "detail/GlyphInfo.ipp"
