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

namespace s3d
{
	template <class Type>
	inline constexpr Vector2D<Type> Point::operator +(const Vector2D<Type>& v) const noexcept
	{
		return{ x + v.x, y + v.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::operator -(const Vector2D<Type>& v) const noexcept
	{
		return{ x - v.x, y - v.y };
	}

	inline constexpr Float2 Point::operator * (const float s) const noexcept
	{
		return{ x * s, y * s };
	}

	inline constexpr Vec2 Point::operator * (const double s) const noexcept
	{
		return{ x * s, y * s };
	}

	template <class Type>
	constexpr Vector2D<Type> Point::operator *(const Vector2D<Type>& v) const noexcept
	{
		return{ x * v.x, y * v.y };
	}

	template <class Type>
	constexpr Vector2D<Type> Point::operator /(const Vector2D<Type>& v) const noexcept
	{
		return{ x / p.x, y / p.y };
	}

	constexpr Float2 Point::operator /(float s) const noexcept
	{
		return{ x / s, y / s };
	}

	constexpr Vec2 Point::operator /(double s) const noexcept
	{
		return{ x / s, y / s };
	}
}
