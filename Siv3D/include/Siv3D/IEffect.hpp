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
# include "Uncopyable.hpp"

namespace s3d
{
	/// @brief エフェクトインタフェース
	struct IEffect : private Uncopyable
	{
		/// @brief デストラクタ
		virtual ~IEffect() = default;

		/// @brief エフェクトの更新と描画を記述します。
		/// @param timeSec エフェクトの発生からの時間
		/// @return エフェクトを継続する場合は true を、破棄する場合は false を返します。
		virtual bool update(double timeSec) = 0;
	};
}
