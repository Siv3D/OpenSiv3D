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
	/// @brief フォントの描画方式
	enum class FontMethod : uint8
	{
		/// @brief ビットマップ（デフォルト）
		/// @remark 利点: 文字キャッシュの生成が高速。正確な字形をレンダリングできる
		/// @rematk 欠点: 基本サイズより拡大したときにぼやける。影、輪郭などの距離エフェクトを適用できない
		Bitmap,

		/// @brief SDF
		/// @remark 利点: 基本サイズより拡大したときにぼやけない。影、輪郭などの距離エフェクトを適用できる
		/// @rematk 欠点: 文字キャッシュの生成がやや遅い。鋭角が丸くなる。基本サイズが足りないと複雑な文字にノイズがのる
		SDF,

		/// @brief MSDF
		/// @remark 利点: 基本サイズより拡大したときにぼやけない。影、輪郭などの距離エフェクトを適用できる（ただし SDF より範囲が狭い）
		/// @rematk 欠点: 文字キャッシュの生成が遅い。基本サイズが足りないと複雑な文字にノイズがのる
		MSDF,
	};
}
