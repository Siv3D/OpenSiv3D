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
	/// @brief 3D 図形の基本頂点データ
	struct alignas(16) Vertex3D
	{
		using IndexType = uint32;

		Float3 pos;

		Float3 normal;

		Float2 tex;

		//constexpr void set(float x, float y, Float4 _color) noexcept;

		//constexpr void set(float x, float y, float u, float v) noexcept;

		//constexpr void set(float x, float y, float u, float v, Float4 _color) noexcept;

		//constexpr void set(Float2 _pos, Float4 _color) noexcept;

		//constexpr void set(Float2 _pos, float u, float v, Float4 _color) noexcept;

		//constexpr void set(Float2 _pos, Float2 _tex, Float4 _color) noexcept;
	};
}

//# include "detail/Vertex3D.ipp"
