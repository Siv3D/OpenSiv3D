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
	void PutText(String&& s, double x, double y);

	/// @brief 指定した位置にテキストを描画します。
	/// @param s テキスト
	/// @param center 描画する中心座標
	void PutText(String&& s, Vec2 center);

	void PutText(String&& s, Arg::topLeft_<Vec2> topLeft);

	void PutText(String&& s, Arg::topCenter_<Vec2> topCenter);

	void PutText(String&& s, Arg::topRight_<Vec2> topRight);

	void PutText(String&& s, Arg::rightCenter_<Vec2> rightCenter);

	void PutText(String&& s, Arg::bottomRight_<Vec2> bottomRight);

	void PutText(String&& s, Arg::bottomCenter_<Vec2> bottomCenter);

	void PutText(String&& s, Arg::bottomLeft_<Vec2> bottomLeft);

	void PutText(String&& s, Arg::leftCenter_<Vec2> leftCenter);

	void PutText(String&& s, Arg::center_<Vec2> center);
}
