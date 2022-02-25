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
// s3d::SevenSegment is originally created by Hotaka Okumoto (OpenSiv3D Project)
//-----------------------------------------------

# pragma once
# include <array>
# include <Siv3D/Common.hpp>
# include <Siv3D/2DShapes.hpp>

namespace s3d
{
	/// @brief 7 セグメントディスプレイ風の文字描画
	namespace SevenSegment
	{
		//  _       _   _       _   _   _   _   _   _
		// | |   |  _|  _| |_| |_  |_    | |_| |_| | |  _
		// |_|   | |_   _|   |  _| |_|   | |_|   | |_| 
		//
		//  0   1   2   3   4   5   6   7   8   9   0   -
		//
		// <states>
		//      _
		// |         |  _
		//                 |     |  _
		// [0] [1] [2] [3] [4] [5] [6]

		/// @brief 7 セグメントを描画します。
		/// @param states 点灯させるセグメント
		/// @param pos 描画する左上の座標
		/// @param size 1 つのセグメントの大きさ（ピクセル）
		/// @param halfThickness セグメントの太さの半分（ピクセル）
		/// @param s セグメント間のすき間（ピクセル）
		/// @param colorON 点灯時の色
		/// @param colorOFF 消灯時の色
		inline void Draw(const std::array<bool, 7>& states, const Vec2& pos, double size, double halfThickness, double s, const ColorF& colorON, const ColorF& colorOFF);

		/// @brief 7 セグメントで文字を描画します。
		/// @param ch 文字。 (U'0', U'1', U'2', U'3', U'4', U'5', U'6', U'7', U'8', U'9', U'-', U' ' ) のいずれか
		/// @param pos 描画する左上の座標
		/// @param size 1 つのセグメントの大きさ（ピクセル）
		/// @param halfThickness セグメントの太さの半分（ピクセル）
		/// @param s セグメント間のすき間（ピクセル）
		/// @param colorON 点灯時の色
		/// @param colorOFF 消灯時の色
		inline void DrawChar(char32 ch, const Vec2& pos, double size, double halfThickness, double s, const ColorF& colorON, const ColorF& colorOFF);
	
		/// @brief 7 セグメントでテキストを描画します。
		/// @param text テキスト。 (U'0', U'1', U'2', U'3', U'4', U'5', U'6', U'7', U'8', U'9', U'-', U' ' ) の組み合わせ
		/// @param pos 描画する左上の座標
		/// @param size 1 つのセグメントの大きさ（ピクセル）
		/// @param halfThickness セグメントの太さの半分（ピクセル）
		/// @param s セグメント間のすき間（ピクセル）
		/// @param margin 字間（ピクセル）
		/// @param colorON 点灯時の色
		/// @param colorOFF 消灯時の色
		inline void DrawText(StringView text, const Vec2& pos, double size, double halfThickness, double s, double margin, const ColorF& colorON, const ColorF& colorOFF);
	}
}

# include "detail/SevenSegment.ipp"

/*

# include <Siv3D.hpp>

void Main()
{
	int32 n = 0;

	while (System::Update())
	{
		if (MouseL.down())
		{
			n = Random(-99999, 99999);
		}

		SevenSegment::DrawText(U"{:>6}"_fmt(n), Vec2{ 40, 40 }, 70, 8, 4, 10, ColorF{ 0, 1, 0 }, ColorF{ 0.15 });

		SevenSegment::DrawText(U"{:0>6}"_fmt(Scene::FrameCount()), Vec2{ 40, 240 }, 40, 4, 1, 20, ColorF{ 1, 0.5, 0 }, ColorF{ 0, 0.2, 0.2 });
	}
}

*/
