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
# include "YesNo.hpp"

namespace s3d
{
	/// @brief 再帰的に処理する
	using Recursive			= YesNo<struct Recursive_tag>;

	/// @brief やり直しを許可する
	using AllowUndo			= YesNo<struct AllowUndo_tag>;

	/// @brief 固定されている
	using Fixed				= YesNo<struct Fixed_tag>;

	/// @brief 妥当性をチェックする
	using SkipValidation	= YesNo<struct SkipValidation_tag>;
	
	/// @brief 即座に開始する
	using StartImmediately	= YesNo<struct StartImmediately_tag>;
	
	/// @brief 先頭と終端をつなげて輪を閉じる
	using CloseRing			= YesNo<struct CloseRing_tag>;
	
	/// @brief 距離が近い順にソートする
	using SortByDistance	= YesNo<struct SortByDistance_tag>;
	
	/// @brief 回転を許可する
	using AllowFlip			= YesNo<struct AllowFlip_tag>;
	
	/// @brief 事前に計算を完了させる
	using Precompute		= YesNo<struct Precompute_tag>;

	/// @brief 例外を発生させる
	using AllowExceptions	= YesNo<struct AllowExceptions_tag>;
	
	/// @brief 拡大を許可する
	using AllowScaleUp		= YesNo<struct AllowScaleUp_tag>;

	/// @brief クロスフェードする
	using CrossFade			= YesNo<struct CrossFade_tag>;

	/// @brief 色を反転する
	using InvertColor		= YesNo<struct InvertColor_tag>;

	/// @brief アルファ値を更新する
	using OverwriteAlpha	= YesNo<struct OverwriteAlpha_tag>;

	/// @brief 穴の発生を許可する
	using AllowHoles		= YesNo<struct AllowHoles_tag>;

	/// @brief アンチエイリアスを有向にする
	using Antialiased		= YesNo<struct Antialiased_tag>;
	
	/// @brief ループ再生を有効にする
	using Loop				= YesNo<struct Loop_tag>;

	/// @brief Y 座標を上下反転させる
	using FlipY				= YesNo<struct FlipY_tag>;

	/// @brief 片側だけ処理
	using OneSided			= YesNo<struct OneSided_tag>;

	/// @brief 2 つの物体間での衝突を有向にする
	using EnableCollision	= YesNo<struct EnableCollision_tag>;
	
	/// @brief ロスレスで圧縮する
	using Lossless			= YesNo<struct Lossless_tag>;

	/// @brief カーソルの座標を変換する
	using TransformCursor	= YesNo<struct TransformCursor_tag>;

	/// @brief ホワイトスペースを維持する
	using PreserveWhitespace = YesNo<struct PreserveWhitespace_tag>;

	/// @brief ファイル全体をマップする
	using MapAll			= YesNo<struct MapAll_tag>;

	/// @brief ディザリングする
	using Dither			= YesNo<struct Dither_tag>;

	/// @brief アルファチャンネルを持つ
	using HasAlpha			= YesNo<struct HasAlpha_tag>;

	/// @brief 中心にそろえる
	using Centering			= YesNo<struct Centering_tag>;

	/// @brief フォールバックを使う
	using UseFallback		= YesNo<struct UseFallback_tag>;

	/// @brief 色がある
	using HasColor			= YesNo<struct HasColor_tag>;
	
	/// @brief ヘッダを持つ
	using HasHeader			= YesNo<struct HasHeader_tag>;

	/// @brief 深度バッファを持つ
	using HasDepth			= YesNo<struct HasDepth_tag>;

	/// @brief Diffuse Texture を持つ
	using HasDiffuseTexture = YesNo<struct HasDiffuseTexture_tag>;

	/// @brief パラメータの名前を含む
	using IncludeParamNames = YesNo<struct IncludeParamNames_tag>;

	/// @brief 詳細を出力する
	using Verbose = YesNo<struct Verbose_tag>;

	/// @brief リガチャ（合字）を使う
	using Ligature = YesNo<struct Ligature_tag>;
}
