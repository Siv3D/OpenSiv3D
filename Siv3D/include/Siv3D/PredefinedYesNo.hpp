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
# include "YesNo.hpp"

namespace s3d
{
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
}
