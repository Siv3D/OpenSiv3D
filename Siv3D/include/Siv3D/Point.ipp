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
		return{ x / v.x, y / v.y };
	}

	constexpr Float2 Point::operator /(const float s) const noexcept
	{
		return{ x / s, y / s };
	}

	constexpr Vec2 Point::operator /(const double s) const noexcept
	{
		return{ x / s, y / s };
	}

	template <class Type>
	constexpr Vector2D<Type> Point::movedBy(const Vector2D<Type>& v) const noexcept
	{
		return{ x + v.x, y + v.y };
	}

	inline double Point::distanceFrom(const Point& p) const noexcept
	{
		return distanceFrom(Vec2(p));
	}

	template <class Type>
	Type Point::distanceFrom(const Vector2D<Type>& p) const noexcept
	{
		return std::sqrt(distanceFromSq(p));
	}

	inline constexpr double Point::distanceFromSq(const Point& p) const noexcept
	{
		return distanceFromSq(Vec2(p));
	}

	template <class Type>
	constexpr Type Point::distanceFromSq(const Vector2D<Type>& p) const noexcept
	{
		return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
	}

	template <class Type>
	Type Point::length() const noexcept
	{
		return static_cast<Type>(std::sqrt(lengthSq()));
	}

	template <class Type>
	constexpr Type Point::lengthSq() const noexcept
	{
		return static_cast<Type>(x * x + y * y);
	}

	template <class Type>
	constexpr Vector2D<Type> Point::lerp(const Vector2D<Type>& other, const double f) const noexcept
	{
		return Vector2D<Type>(x + (other.x - x) * f, y + (other.y - y) * f);
	}

	inline constexpr Point operator *(const int32 s, const Point& p) noexcept
	{
		return{ s * p.x, s * p.y };
	}

	inline constexpr Float2 operator *(const float s, const Point& p) noexcept
	{
		return{ s * p.x, s * p.y };
	}

	inline constexpr Vec2 operator *(const double s, const Point& p) noexcept
	{
		return{ s * p.x, s * p.y };
	}
}
