//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// 点、またはサイズ
	/// </summary>
	struct Point
	{
		using value_type = int32;

		value_type x, y;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Point() noexcept = default;

		constexpr Point(int32 _x, int32 _y) noexcept
			: x(_x)
			, y(_y) {}

		template <class U, class V>
		constexpr Point(U _x, V _y)
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y)) {}

		/// <summary>
		/// Point{ x, x }
		/// </summary>
		constexpr Point xx() const noexcept
		{
			return{ x, x };
		}

		/// <summary>
		/// Point{ x, y }
		/// </summary>
		constexpr Point xy() const noexcept
		{
			return *this;
		}

		/// <summary>
		/// Point{ y, x }
		/// </summary>
		constexpr Point yx() const noexcept
		{
			return{ y, x };
		}

		/// <summary>
		/// Point{ y, y }
		/// </summary>
		constexpr Point yy() const noexcept
		{
			return{ y, y };
		}

		constexpr Point operator +() const noexcept
		{
			return *this;
		}

		constexpr Point operator -() const noexcept
		{
			return{ -x, -y };
		}

		constexpr Point operator +(const Point& p) const noexcept
		{
			return{ x + p.x, y + p.y };
		}

		constexpr Point operator -(const Point& p) const noexcept
		{
			return{ x - p.x, y - p.y };
		}

		template <class Type>
		constexpr Vector2D<Type> operator +(const Vector2D<Type>& v) const noexcept;

		template <class Type>
		constexpr Vector2D<Type> operator -(const Vector2D<Type>& v) const noexcept;

		constexpr Point operator *(int32 s) const noexcept
		{
			return{ x * s, y * s };
		}

		constexpr Float2 operator *(float s) const noexcept;

		constexpr Vec2 operator *(double s) const noexcept;

		constexpr Point operator *(const Point& p) const noexcept
		{
			return{ x * p.x, y * p.y };
		}

		template <class Type>
		constexpr Vector2D<Type> operator *(const Vector2D<Type>& v) const noexcept;

		constexpr Point operator /(int32 s) const noexcept
		{
			return{ x / s, y / s };
		}

		constexpr Point operator /(const Point& p) const noexcept
		{
			return{ x / p.x, y / p.y };
		}

		template <class Type>
		constexpr Vector2D<Type> operator /(const Vector2D<Type>& v) const noexcept;

		constexpr Float2 operator /(float s) const noexcept;

		constexpr Vec2 operator /(double s) const noexcept;

		S3D_CONSTEXPR_CPP14 Point& operator +=(const Point& p) noexcept
		{
			x += p.x;
			y += p.y;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Point& operator -=(const Point& p) noexcept
		{
			x -= p.x;
			y -= p.y;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Point& operator *=(int32 s) noexcept
		{
			x *= s;
			y *= s;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Point& operator /=(int32 s) noexcept
		{
			assert(s != 0);
			x /= s;
			y /= s;
			return *this;
		}

		constexpr bool operator ==(const Point& p) const noexcept
		{
			return x == p.x && y == p.y;
		}

		constexpr bool operator !=(const Point& p) const noexcept
		{
			return x != p.x || y != p.y;
		}
	};

	using Size = Point;
}
