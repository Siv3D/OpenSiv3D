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
	/// <summary>
	/// スプライトの頂点データ
	/// </summary>
	struct Vertex2D
	{
		/// <summary>
		/// 位置
		/// </summary>
		Float2 pos;
		
		/// <summary>
		/// UV 座標
		/// </summary>
		Float2 tex;
		
		/// <summary>
		/// 色
		/// </summary>
		Float4 color;

		void set(const Float2& _pos, const Float2& _tex, const Float4& _color)
		{
			pos = _pos;
			tex = _tex;
			color = _color;
		}
	};
}
