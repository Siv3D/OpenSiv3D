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
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 2D 図形の基本頂点データ
	struct alignas(16) Vertex2D
	{
		/// @brief 2D 描画のインデックス配列に使われる型
		using IndexType = uint16;

		/// @brief 位置
		Float2 pos;
		
		/// @brief UV 座標
		Float2 tex;
		
		/// @brief 色
		Float4 color;

		constexpr void set(float x, float y, Float4 _color) noexcept;

		constexpr void set(float x, float y, float u, float v) noexcept;

		constexpr void set(float x, float y, float u, float v, Float4 _color) noexcept;

		constexpr void set(Float2 _pos, Float4 _color) noexcept;

		constexpr void set(Float2 _pos, float u, float v, Float4 _color) noexcept;

		constexpr void set(Float2 _pos, Float2 _tex, Float4 _color) noexcept;
	};
}

# include "detail/Vertex2D.ipp"
