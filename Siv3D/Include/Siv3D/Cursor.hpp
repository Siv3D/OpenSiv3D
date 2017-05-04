//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	namespace Cursor
	{
		/// <summary>
		/// マウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// マウスカーソルの位置（クライアント座標）
		/// </returns>
		const Point& Pos();

		/// <summary>
		/// 1 フレーム前のマウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 フレーム前のマウスカーソルの位置（クライアント座標）
		/// </returns>
		const Point& PreviousPos();

		/// <summary>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量（クライアント座標）
		/// </returns>
		const Point& Delta();

		/// <summary>
		/// マウスカーソルの位置を返します（スクリーン座標）
		/// </summary>
		/// <returns>
		/// マウスカーソルの位置（スクリーン座標）
		/// </returns>
		const Point& ScreenPos();

		/// <summary>
		/// 1 フレーム前のマウスカーソルの位置を返します（スクリーン座標）
		/// </summary>
		/// <returns>
		/// 1 フレーム前のマウスカーソルの位置（スクリーン座標）
		/// </returns>
		const Point& PreviousScreenPos();

		/// <summary>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量を返します（スクリーン座標）
		/// </summary>
		/// <returns>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量（スクリーン座標）
		/// </returns>
		const Point& ScreenDelta();

		void SetPos(const Point& pos);

		bool OnClient();
		
		void Clip(const Rect& rect);
	}
}
