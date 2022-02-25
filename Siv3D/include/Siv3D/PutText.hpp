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
# include "String.hpp"
# include "PredefinedNamedParameter.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param x 描画する中心の X 座標
	/// @param y 描画する中心の Y 座標
	void PutText(String s, double x, double y);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param center 描画する中心座標
	void PutText(String s, Vec2 center);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param topLeft 描画する左上の座標
	void PutText(String s, Arg::topLeft_<Vec2> topLeft);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param topCenter 描画する上辺中心の座標
	void PutText(String s, Arg::topCenter_<Vec2> topCenter);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param topRight 描画する右上の座標
	void PutText(String s, Arg::topRight_<Vec2> topRight);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param rightCenter 描画する右辺中心の座標
	void PutText(String s, Arg::rightCenter_<Vec2> rightCenter);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param bottomRight 描画する右下の座標
	void PutText(String s, Arg::bottomRight_<Vec2> bottomRight);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param bottomCenter 描画する下辺中心の座標
	void PutText(String s, Arg::bottomCenter_<Vec2> bottomCenter);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param bottomLeft 描画する左下の座標
	void PutText(String s, Arg::bottomLeft_<Vec2> bottomLeft);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param leftCenter 描画する左辺中心の座標
	void PutText(String s, Arg::leftCenter_<Vec2> leftCenter);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param center 描画する中心座標
	void PutText(String s, Arg::center_<Vec2> center);
}
