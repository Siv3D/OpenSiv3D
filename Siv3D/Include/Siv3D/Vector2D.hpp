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
# include <cmath>
# include <utility>
# include "Fwd.hpp"
# include "Point.hpp"
# include "Format.hpp"
# include "Hash.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	/// <summary>
	/// 2 次元ベクトル
	/// </summary>
	template <class Type>
	struct Vector2D
	{
		template <class U>
		using vector_type = Vector2D<U>;

		using value_type = Type;

		value_type x, y;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Vector2D() noexcept = default;

		constexpr Vector2D(const Vector2D&) noexcept = default;

		template <class X, class Y>
		constexpr Vector2D(X _x, Y _y) noexcept
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
			return *this * (static_cast<value_type>(1.0) / s);
		}

		constexpr Vector2D operator /(const Vector2D& v) const noexcept
		{
			return{ x / v.x, y / v.y };
		}

		constexpr Vector2D& operator +=(const Vector2D& v) noexcept
		{
			x += v.x; y += v.y;
			return *this;
		}

		constexpr Vector2D& operator -=(const Vector2D& v) noexcept
		{
			x -= v.x; y -= v.y;
			return *this;
		}

		constexpr Vector2D& operator *=(value_type s) noexcept
		{
			x *= s; y *= s;
			return *this;
		}

		constexpr Vector2D& operator *=(const Vector2D& v) noexcept
		{
			x *= v.x; y *= v.y;
			return *this;
		}

		constexpr Vector2D& operator /=(value_type s) noexcept
		{
			return *this *= (static_cast<value_type>(1.0) / s);
		}

		constexpr Vector2D& operator /=(const Vector2D& v) noexcept
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

		constexpr Vector2D& set(value_type _x, value_type _y) noexcept
		{
			x = _x; y = _y;
			return *this;
		}

		constexpr Vector2D& set(const Vector2D& v) noexcept
		{
			return *this = v;
		}

		S3D_NODISCARD constexpr Vector2D movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ x + _x, y + _y };
		}

		S3D_NODISCARD constexpr Vector2D movedBy(const Vector2D& v) const noexcept
		{
			return{ x + v.x, y + v.y };
		}

		constexpr Vector2D& moveBy(value_type _x, value_type _y) noexcept
		{
			x += _x; y += _y;
			return *this;
		}

		constexpr Vector2D& moveBy(const Vector2D& v) noexcept
		{
			return *this += v;
		}

		Vector2D& clamp(const RectF& rect) noexcept;

		S3D_NODISCARD Vector2D clamped(const RectF& rect) noexcept;

		constexpr bool isZero() const noexcept
		{
			return x == static_cast<value_type>(0.0)
				&& y == static_cast<value_type>(0.0);
		}

		bool hasNaN() const noexcept
		{
			return std::isnan(x)
				|| std::isnan(y);
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

		value_type distanceFrom(value_type _x, value_type _y) const noexcept
		{
			return distanceFrom({ _x, _y });
		}

		value_type distanceFrom(const Vector2D& v) const noexcept
		{
			return (*this - v).length();
		}

		constexpr value_type distanceFromSq(value_type _x, value_type _y) const noexcept
		{
			return distanceFromSq({ _x, _y });
		}

		constexpr value_type distanceFromSq(const Vector2D& v) const noexcept
		{
			return (*this - v).lengthSq();
		}

		S3D_NODISCARD Vector2D normalized() const noexcept
		{
			return *this * lengthInv();
		}

		Vector2D& normalize() noexcept
		{
			return *this *= lengthInv();
		}

		S3D_NODISCARD Vector2D rotated(value_type angle) const noexcept
		{
			const value_type s = std::sin(angle);
			const value_type c = std::cos(angle);
			return{ x * c - y * s, x * s + y * c };
		}

		Vector2D& rotate(value_type angle) noexcept
		{
			return *this = rotated(angle);
		}
		
		S3D_NODISCARD value_type getAngle(const Vector2D& v) const
		{
			if (isZero() || v.isZero())
			{
				return static_cast<value_type>(Math::NaN);
			}

			return std::atan2(cross(v), dot(v));
		}

		S3D_NODISCARD constexpr Vector2D projection(const Vector2D& onto) const noexcept
		{
			return onto.lengthSq() ? onto * dot(onto) / onto.lengthSq() : Zero();
		}

		S3D_NODISCARD constexpr Vector2D lerp(const Vector2D& other, double f) const noexcept
		{
			return Vector2D(x + (other.x - x) * f, y + (other.y - y) * f);
		}

		template <class Shape2DType>
		bool intersects(const Shape2DType& shape) const noexcept(noexcept(Geometry2D::Intersect(*this, shape)))
		{
			return Geometry2D::Intersect(*this, shape);
		}

		/// <summary>
		/// Vector2D{ 0, 0 }
		/// </summary>
		static constexpr Vector2D Zero() noexcept
		{
			return{ 0, 0 };
		}

		/// <summary>
		/// Vector2D{ 1, 1 }
		/// </summary>
		static constexpr Vector2D One() noexcept
		{
			return{ 1, 1 };
		}

		/// <summary>
		/// Vector2D{ value, value }
		/// </summary>
		static constexpr Vector2D All(value_type value = 1) noexcept
		{
			return{ value, value };
		}

		/// <summary>
		/// Vector2D{ 1, 0 }
		/// </summary>
		static constexpr Vector2D UnitX() noexcept
		{
			return{ 1, 0 };
		}

		/// <summary>
		/// Vector2D{ 0, 1 }
		/// </summary>
		static constexpr Vector2D UnitY() noexcept
		{
			return{ 0, 1 };
		}

		/// <summary>
		/// Vector2D{ -length, 0 }
		/// </summary>
		static constexpr Vector2D Left(value_type length = 1) noexcept
		{
			return{ -length, 0 };
		}

		/// <summary>
		/// Vector2D{ length, 0 }
		/// </summary>
		static constexpr Vector2D Right(value_type length = 1) noexcept
		{
			return{ length, 0 };
		}

		/// <summary>
		/// Vector2D{ 0, -length }
		/// </summary>
		static constexpr Vector2D Up(value_type length = 1) noexcept
		{
			return{ 0, -length };
		}

		/// <summary>
		/// Vector2D{ 0, length }
		/// </summary>
		static constexpr Vector2D Down(value_type length = 1) noexcept
		{
			return{ 0, length };
		}
	};

	template <class Type, class U>
	inline constexpr Vector2D<Type> operator *(U s, const Vector2D<Type>& v) noexcept
	{
		return v * static_cast<Type>(s);
	}

	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
}

namespace std
{
	template <class Type>
	struct hash<s3d::Vector2D<Type>>
	{
		size_t operator()(const s3d::Vector2D<Type>& keyVal) const
		{
			return s3d::Hash::FNV1a(keyVal);
		}
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Vector2D
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	void Formatter(FormatData& formatData, const Float2& value);
	void Formatter(FormatData& formatData, const Vec2& value);

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
		return os << CharType('(')
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
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Vector2D<Type>& v)
	{
		CharType unused;
		return is >> unused
			>> v.x >> unused
			>> v.y >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter, class Type>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Vector2D<Type>& v)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, v.x, v.y);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
