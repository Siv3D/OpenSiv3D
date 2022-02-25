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
	/// @brief アドオンインタフェース
	class IAddon
	{
	public:

		/// @brief デストラクタ
		virtual ~IAddon() = default;

		/// @brief アドオンの登録時の初期化処理を記述します。
		/// @remark この関数が false を返すとアドオンの登録は失敗します。
		/// @return アドオンの初期化に成功した場合 true, それ以外の場合は false
		virtual bool init() { return true; }

		/// @brief アドオンの毎フレームの更新処理を記述します。
		/// @remark この関数が false を返すと `System::Update()` は false を返します。
		/// @return アドオンの更新に成功した場合 true, それ以外の場合は false
		virtual bool update() { return true; }

		/// @brief アドオンの毎フレームの描画処理を記述します。
		virtual void draw() const {}
	};
}
