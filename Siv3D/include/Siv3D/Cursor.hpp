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
# include "PointVector.hpp"

namespace s3d
{
	enum class CursorStyle
	{
		Arrow,

		IBeam,

		Cross,

		Hand,

		NotAllowed,

		ResizeUpDown,

		ResizeLeftRight,

		Hidden,

		Default = Arrow,
	};

	namespace Cursor
	{
		/// <summary>
		/// マウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// マウスカーソルの位置（クライアント座標）
		/// </returns>
		Point Pos();

		/// <summary>
		/// 1 フレーム前のマウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 フレーム前のマウスカーソルの位置（クライアント座標）
		/// </returns>
		Point PreviousPos();

		/// <summary>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量（クライアント座標）
		/// </returns>
		Point Delta();

		/// <summary>
		/// マウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// マウスカーソルの位置（クライアント座標）
		/// </returns>
		Vec2 PosF();

		/// <summary>
		/// 1 フレーム前のマウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 フレーム前のマウスカーソルの位置（クライアント座標）
		/// </returns>
		Vec2 PreviousPosF();

		/// <summary>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量（クライアント座標）
		/// </returns>
		Vec2 DeltaF();

		/// <summary>
		/// マウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// マウスカーソルの位置（クライアント座標）
		/// </returns>
		Point PosRaw();

		/// <summary>
		/// 1 フレーム前のマウスカーソルの位置を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 フレーム前のマウスカーソルの位置（クライアント座標）
		/// </returns>
		Point PreviousPosRaw();

		/// <summary>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量を返します（クライアント座標）
		/// </summary>
		/// <returns>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量（クライアント座標）
		/// </returns>
		Point DeltaRaw();

		/// <summary>
		/// マウスカーソルの位置を返します（スクリーン座標）
		/// </summary>
		/// <returns>
		/// マウスカーソルの位置（スクリーン座標）
		/// </returns>
		Point ScreenPos();

		/// <summary>
		/// 1 フレーム前のマウスカーソルの位置を返します（スクリーン座標）
		/// </summary>
		/// <returns>
		/// 1 フレーム前のマウスカーソルの位置（スクリーン座標）
		/// </returns>
		Point PreviousScreenPos();

		/// <summary>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量を返します（スクリーン座標）
		/// </summary>
		/// <returns>
		/// 1 つ前のフレームと比べたマウスカーソルの移動量（スクリーン座標）
		/// </returns>
		Point ScreenDelta();

		void SetPos(int32 x, int32 y);

		inline void SetPos(const Point& pos)
		{
			SetPos(pos.x, pos.y);
		}

		bool OnClientRect();

		void SetTransformLocal(const Mat3x2& matrix);

		void SetTransformCamera(const Mat3x2& matrix);

		void SetTransformScreen(const Mat3x2& matrix);

		/// <summary>
		/// クライアント座標系のカーソル位置に適用されている座標変換を返します。
		/// </summary>
		/// <returns>
		/// 適用されている座標変換
		/// </returns>
		const Mat3x2& GetTransformLocal();

		const Mat3x2& GetTransformCamera();

		const Mat3x2& GetTransformScreen();

		/// <summary>
		/// マウスカーソルの移動範囲をクライアント画面に制限します
		/// </summary>
		/// <param name="clip">
		/// 制限を設定する場合は true, 解除する場合は false
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void ClipClientRect(bool clip);

		void SetStyle(CursorStyle style);

		CursorStyle GetStyle();
	}

	namespace win::Cursor
	{
		void ClipRect(const Optional<Rect>& rect);
	}
}
