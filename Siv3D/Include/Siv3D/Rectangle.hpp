//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 長方形
	/// </summary>
	template <class SizeType>
	struct Rectangle
	{
		using value_type = typename SizeType::value_type;

#pragma warning(disable:4201)
		union
		{
			struct
			{
				/// <summary>
				/// 長方形の左上の点の X 座標
				/// </summary>
				value_type x;

				/// <summary>
				/// 長方形の左上の点の Y 座標
				/// </summary>
				value_type y;

				/// <summary>
				/// 長方形の幅
				/// </summary>
				value_type w;

				/// <summary>
				/// 長方形の高さ
				/// </summary>
				value_type h;
			};

			struct
			{
				/// <summary>
				/// 長方形の左上の点の位置
				/// </summary>
				SizeType pos;

				/// <summary>
				/// 長方形のサイズ
				/// </summary>
				SizeType size;
			};
		};

#pragma warning(default:4201)
	};

	/// <summary>
	/// 長方形（要素が int 型）
	/// </summary>
	using Rect = Rectangle<Point>;

	/// <summary>
	/// 長方形（要素が double 型）
	/// </summary>
	using RectF = Rectangle<Vec2>;
}
