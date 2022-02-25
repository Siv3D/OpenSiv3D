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
# include "../Common.hpp"

namespace s3d
{
	/// @brief 部品 (P2Shape) の形状の種類を示します。
	enum class P2ShapeType : uint8
	{
		/// @brief 線分
		Line,

		/// @brief 連続する複数の線分
		LineString,

		/// @brief 円
		Circle,

		/// @brief 長方形
		Rect,

		/// @brief 三角形
		Triangle,

		/// @brief 凸な四角形
		Quad,

		/// @brief 多角形
		Polygon
	};
}
