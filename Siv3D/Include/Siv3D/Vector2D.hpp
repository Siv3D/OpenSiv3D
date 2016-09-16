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
# include <cmath>
# include <utility>
# include "Fwd.hpp"
# include "Point.hpp"
# include "Hash.hpp"

namespace s3d
{
	/// <summary>
	/// 2 次元ベクトル
	/// </summary>
	template <class Type>
	struct Vector2D
	{
		using value_type = Type;

		value_type x, y;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Vector2D() noexcept = default;

		constexpr Vector2D(const Vector2D&) noexcept = default;

		template <class U, class V>
		constexpr Vector2D(U _x, V _y) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y)) {}

		constexpr Vector2D(value_type _x, value_type _y) noexcept
			: x(_x)
			, y(_y) {}

		constexpr Vector2D(const Point& v) noexcept
			: x(static_cast<value_type>(v.x))
			, y(static_cast<value_type>(v.y)) {}

		template <class U>
		constexpr Vector2D(const Vector2D<U>& v) noexcept
			: x(static_cast<value_type>(v.x))
			, y(static_cast<value_type>(v.y)) {}

		constexpr Vector2D operator +() const noexcept
		{
			return *this;
		}

		constexpr Vector2D operator -() const noexcept
		{
			return{ -x, -y };
		}

		constexpr Vector2D operator +(const Vector2D& v) const noexcept
		{
			return{ x + v.x, y + v.y };
		}

		constexpr Vector2D operator -(const Vector2D& v) const noexcept
		{
			return{ x - v.x, y - v.y };
		}

		constexpr Vector2D operator *(value_type s) const noexcept
		{
			return{ x * s, y * s };
		}

		constexpr Vector2D operator *(const Vector2D& v) const noexcept
		{
			return{ x * v.x, y * v.y };
		}

		constexpr Vector2D operator /(value_type s) const noexcept
		{
			return{ x / s, y / s };
		}

		constexpr Vector2D operator /(const Vector2D& v) const noexcept
		{
			return{ x / v.x, y / v.y };
		}

		S3D_CONSTEXPR_CPP14 Vector2D& operator +=(const Vector2D& v) noexcept
		{
			x += v.x; y += v.y;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Vector2D& operator -=(const Vector2D& v) noexcept
		{
			x -= v.x; y -= v.y;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Vector2D& operator *=(value_type s) noexcept
		{
			x *= s; y *= s;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Vector2D& operator *=(const Vector2D& v) noexcept
		{
			x *= v.x; y *= v.y;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Vector2D& operator /=(value_type s) noexcept
		{
			return *this *= static_cast<value_type>(1.0) / s;
		}

		S3D_CONSTEXPR_CPP14 Vector2D& operator /=(const Vector2D& v) noexcept
		{
			x /= v.x; y /= v.y;
			return *this;
		}

		constexpr bool operator ==(const Vector2D& v) const noexcept
		{
			return v.x == x && v.y == y;
		}

		constexpr bool operator !=(const Vector2D& v) const noexcept
		{
			return v.x != x || v.y != y;
		}

		/// <summary>
		/// Vector2D{ x, x }
		/// </summary>
		constexpr Vector2D xx() const noexcept
		{
			return{ x, x };
		}

		/// <summary>
		/// Vector2D{ x, y }
		/// </summary>
		constexpr Vector2D xy() const noexcept
		{
			return{ x, y };
		}

		/// <summary>
		/// Vector2D{ y, x }
		/// </summary>
		constexpr Vector2D yx() const noexcept
		{
			return{ y, x };
		}

		/// <summary>
		/// Vector2D{ y, y }
		/// </summary>
		constexpr Vector2D yy() const noexcept
		{
			return{ y, y };
		}

		constexpr Point asPoint() const noexcept
		{
			return{ static_cast<Point::value_type>(x), static_cast<Point::value_type>(y) };
		}

		S3D_CONSTEXPR_CPP14 Vector2D& set(value_type _x, value_type _y) noexcept
		{
			x = _x; y = _y;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Vector2D& set(const Vector2D& v) noexcept
		{
			return *this = v;
		}

		constexpr Vector2D movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ x + _x, y + _y };
		}

		constexpr Vector2D movedBy(const Vector2D& v) const noexcept
		{
			return{ x + v.x, y + v.y };
		}

		S3D_CONSTEXPR_CPP14 Vector2D& moveBy(value_type _x, value_type _y) noexcept
		{
			x += _x; y += _y;
			return *this;
		}

		S3D_CONSTEXPR_CPP14 Vector2D& moveBy(const Vector2D& v) noexcept
		{
			return *this += v;
		}

		constexpr bool isZero() const noexcept
		{
			return x == static_cast<value_type>(0.0)
				&& y == static_cast<value_type>(0.0);
		}

		constexpr value_type dot(const Vector2D& v) const noexcept
		{
			return x * v.x + y * v.y;
		}

		constexpr value_type cross(const Vector2D& v) const noexcept
		{
			return x * v.y - y * v.x;
		}

		value_type length() const noexcept
		{
			return std::sqrt(lengthSq());
		}

		constexpr value_type lengthSq() const noexcept
		{
			return dot(*this);
		}

		value_type lengthInv() const noexcept
		{
			return static_cast<value_type>(1.0) / length();
		}

		Vector2D& setLength(value_type _length) noexcept
		{
			const value_type len = length();

			if (len == 0.0)
			{
				return *this;
			}

			return *this *= (_length / len);
		}

		value_type distanceFrom(const Vector2D& v) const noexcept
		{
			return (*this - v).length();
		}

		constexpr value_type distanceFromSq(const Vector2D& v) const noexcept
		{
			return (*this - v).lengthSq();
		}

		Vector2D normalized() const noexcept
		{
			return *this * lengthInv();
		}

		Vector2D& normalize() noexcept
		{
			return *this *= lengthInv();
		}

		Vector2D rotated(value_type angle) const noexcept
		{
			const value_type s = std::sin(angle);
			const value_type c = std::cos(angle);
			return{ x * c - y * s, x * s + y * c };
		}

		Vector2D& rotate(value_type angle) noexcept
		{
			return *this = rotated(angle);
		}

		constexpr Vector2D projection(const Vector2D& onto) const noexcept
		{
			return onto.lengthSq() ? onto * dot(onto) / onto.lengthSq() : Zero();
		}

		constexpr Vector2D lerp(const Vector2D& other, double f) const noexcept
		{
			return Vector2D(x + (other.x - x) * f, y + (other.y - y) * f);
		}

		/// <summary>
		/// Vector2D{ 0, 0 }
		/// </summary>
		static constexpr Vector2D Zero()
		{
			return{ 0, 0 };
		}

		/// <summary>
		/// Vector2D{ 1, 1 }
		/// </summary>
		static constexpr Vector2D One()
		{
			return{ 1, 1 };
		}

		/// <summary>
		/// Vector2D{ value, value }
		/// </summary>
		static constexpr Vector2D All(value_type value = 1)
		{
			return{ value, value };
		}

		/// <summary>
		/// Vector2D{ 1, 0 }
		/// </summary>
		static constexpr Vector2D UnitX()
		{
			return{ 1, 0 };
		}

		/// <summary>
		/// Vector2D{ 0, 1 }
		/// </summary>
		static constexpr Vector2D UnitY()
		{
			return{ 0, 1 };
		}

		/// <summary>
		/// Vector2D{ -value, 0 }
		/// </summary>
		static constexpr Vector2D Left(value_type length = 1)
		{
			return{ -length, 0 };
		}

		/// <summary>
		/// Vector2D{ value, 0 }
		/// </summary>
		static constexpr Vector2D Right(value_type length = 1)
		{
			return{ length, 0 };
		}

		/// <summary>
		/// Vector2D{ 0, -value }
		/// </summary>
		static constexpr Vector2D Up(value_type length = 1)
		{
			return{ 0, -length };
		}

		/// <summary>
		/// Vector2D{ 0, value }
		/// </summary>
		static constexpr Vector2D Down(value_type length = 1)
		{
			return{ 0, length };
		}
	};

	/// <summary>
	/// 出力ストリームに 2 次元ベクトルを渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="v">
	/// 2 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Vector2D<Type>& v)
	{
		return os	<< CharType('(')
					<< v.x << CharType(',')
					<< v.y << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに 2 次元ベクトルを渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="v">
	/// 2 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Vector2D<Type>& v)
	{
		CharType unused;
		return is	>> unused
					>> v.x >> unused
					>> v.y >> unused;
	}

	template <class Type, class U>
	inline constexpr Vector2D<Type> operator *(U s, const Vector2D<Type>& v) noexcept
	{
		return v * s;
	}

	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
}

namespace std
{
	template <>
	struct hash<s3d::Float2>
	{
		size_t operator ()(const s3d::Float2& keyVal) const
		{
			return s3d::Hash::FNV1a(keyVal);
		}
	};

	template <>
	struct hash<s3d::Vec2>
	{
		size_t operator ()(const s3d::Vec2& keyVal) const
		{
			return s3d::Hash::FNV1a(keyVal);
		}
	};
}
