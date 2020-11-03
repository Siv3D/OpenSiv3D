//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"

namespace s3d
{
	class Image;

	namespace Cursor
	{
		/// @brief 現在のフレームにおける、マウスカーソルのクライアント座標（ピクセル）を返します。
		/// @return 現在のフレームにおける、マウスカーソルの座標 (ピクセル)
		[[nodiscard]]
		Point Pos();

		/// @brief 現在のフレームにおける、マウスカーソルのクライアント座標（ピクセル）を返します。
		/// @remark 座標が小数値を含む場合があります。
		/// @return 現在のフレームおける、マウスカーソルの座標 (ピクセル)
		[[nodiscard]]
		Vec2 PosF();

		/// @brief 直前のフレームにおける、マウスカーソルのクライアント座標（ピクセル）を返します。
		/// @return 直前のフレームおける、マウスカーソルの座標 (ピクセル)
		[[nodiscard]]
		Point PreviousPos();

		/// @brief 直前のフレームにおける、マウスカーソルのクライアント座標（ピクセル）を返します。
		/// @remark 座標が小数値を含む場合があります。
		/// @return 直前のフレームおける、マウスカーソルの座標 (ピクセル)
		[[nodiscard]]
		Vec2 PreviousPosF();

		/// @brief 直前のフレームから現在のフレームまでのマウスカーソルの移動量（ピクセル）を返します。
		/// @remark `Cursor::Pos() - Cursor::PreviousPos()` と同値です。
		/// @return 直前のフレームから現在のフレームまでのマウスカーソルの移動量 (ピクセル)
		[[nodiscard]]
		Point Delta();

		/// @brief 直前のフレームから現在のフレームまでのマウスカーソルの移動量（ピクセル）を返します。
		/// @remark `Cursor::PosF() - Cursor::PreviousPosF()` と同値です。
		/// @remark 移動量が小数値を含む場合があります。
		/// @return 直前のフレームから現在のフレームまでのマウスカーソルの移動量 (ピクセル)
		[[nodiscard]]
		Vec2 DeltaF();

		/// @brief 現在のフレームにおける、未変換のマウスカーソルのクライアント座標（ピクセル）を返します。
		/// @return 現在のフレームおける、未変換のマウスカーソルの座標 (ピクセル)
		[[nodiscard]]
		Point PosRaw();

		/// @brief 直前のフレームにおける、未変換のマウスカーソルのクライアント座標（ピクセル）を返します。
		/// @return 直前のフレームおける、未変換のマウスカーソルの座標 (ピクセル)
		[[nodiscard]]
		Point PreviousPosRaw();

		/// @brief 直前のフレームから現在のフレームまでの未変換のマウスカーソルの移動量（ピクセル）を返します。
		/// @remark `Cursor::PosRaw() - Cursor::PreviousPosRaw()` と同値です。
		/// @return 直前のフレームから現在のフレームまでの未変換のマウスカーソルの移動量 (ピクセル)
		[[nodiscard]]
		Point DeltaRaw();

		/// @brief 現在のフレームにおける、マウスカーソルのスクリーン座標（ピクセル）を返します。
		/// @return 現在のフレームおける、マウスカーソルのスクリーン座標 (ピクセル)
		[[nodiscard]]
		Point ScreenPos();

		/// @brief 直前のフレームにおける、マウスカーソルのスクリーン座標（ピクセル）を返します。
		/// @return 直前のフレームおける、マウスカーソルのスクリーン座標 (ピクセル)
		[[nodiscard]]
		Point ScreenPreviousPos();

		/// @brief 直前のフレームから現在のフレームまでの、スクリーン上でのマウスカーソルの移動量（ピクセル）を返します。
		/// @remark `Cursor::ScreenPos() - Cursor::ScreenPreviousPos()` と同値です。
		/// @return 直前のフレームから現在のフレームまでのスクリーン上でのマウスカーソルの移動量 (ピクセル)
		[[nodiscard]]
		Point ScreenDelta();

		/// @brief マウスカーソルを指定したクライアント座標に移動させます。
		/// @param x 移動先の X 座標 (ピクセル)
		/// @param y 移動先の Y 座標 (ピクセル)
		inline void SetPos(int32 x, int32 y);

		/// @brief マウスカーソルを指定したクライアント座標に移動させます。
		/// @param pos 移動先の座標 (ピクセル)
		void SetPos(Point pos);

		/// @brief マウスカーソルの移動範囲をクライアント画面に制限されているかを返します。
		/// @return 制限されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsClippedToWindow() noexcept;

		/// @brief マウスカーソルの移動範囲をクライアント画面に制限します
		/// @param clip 制限を設定する場合 true, 解除する場合は false
		void ClipToWindow(bool clip);

		bool Register(StringView name, const Image& image, Point hotSpot = Point{ 0, 0 });

		void RequestStyle(StringView name);
	}
}

# include "detail/Cursor.ipp"
