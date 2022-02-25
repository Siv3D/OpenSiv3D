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

namespace s3d
{
	inline constexpr void Vertex2D::set(const float x, const float y, const Float4 _color) noexcept
	{
		pos.set(x, y);
		color	= _color;
	}

	inline constexpr void Vertex2D::set(const float x, const float y, const float u, const float v) noexcept
	{
		pos.set(x, y);
		tex.set(u, v);
	}

	inline constexpr void Vertex2D::set(const float x, const float y, const float u, const float v, const Float4 _color) noexcept
	{
		pos.set(x, y);
		tex.set(u, v);
		color	= _color;
	}

	inline constexpr void Vertex2D::set(const Float2 _pos, const Float4 _color) noexcept
	{
		pos		= _pos;
		color	= _color;
	}

	inline constexpr void Vertex2D::set(const Float2 _pos, const float u, const float v, const Float4 _color) noexcept
	{
		pos		= _pos;
		tex.set(u, v);
		color	= _color;
	}

	inline constexpr void Vertex2D::set(const Float2 _pos, const Float2 _tex, const Float4 _color) noexcept
	{
		pos		= _pos;
		tex		= _tex;
		color	= _color;
	}
}
