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
# include "Optional.hpp"
# include "Array.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 二次元図形の作成と幾何計算
	/// </summary>
	namespace Geometry2D
	{
		Optional<Array<Vec2>> IntersectAt(const Line& a, const Ellipse& b);

		Optional<Array<Vec2>> IntersectAt(const Rect& a, const Ellipse& b);

		Optional<Array<Vec2>> IntersectAt(const RectF& a, const Ellipse& b);
	}
}
