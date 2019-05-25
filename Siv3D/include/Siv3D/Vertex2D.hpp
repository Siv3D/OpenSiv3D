//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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
		using IndexType = uint16;

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

		void set(float x, float y, const Float4& _color) noexcept
		{
			pos.set(x, y);
			color = _color;
		}

		void set(float x, float y, float u, float v) noexcept
		{
			pos.set(x, y);
			tex.set(u, v);
		}

		void set(float x, float y, float u, float v, const Float4& _color) noexcept
		{
			pos.set(x, y);
			tex.set(u, v);
			color = _color;
		}

		void set(const Float2& _pos, const Float4& _color) noexcept
		{
			pos = _pos;
			color = _color;
		}

		void set(const Float2& _pos, float u, float v, const Float4& _color) noexcept
		{
			pos = _pos;
			tex.set(u, v);
			color = _color;
		}

		void set(const Float2& _pos, const Float2& _tex, const Float4& _color) noexcept
		{
			pos = _pos;
			tex = _tex;
			color = _color;
		}
	};
}
