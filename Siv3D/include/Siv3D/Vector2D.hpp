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
# include <cmath>
# include <utility>
# include "Platform.hpp"
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

		[[nodiscard]] constexpr value_type elem(size_t index) const noexcept
		{
			return index == 0 ? x
				: index == 1 ? y
				: 0;
		}

		[[nodiscard]] constexpr Vector2D operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] constexpr Vector2D operator -() const noexcept
		{
			return{ -x, -y };
		}

		[[nodiscard]] constexpr Vector2D operator +(const Vector2D& v) const noexcept
		{
			return{ x + v.x, y + v.y };
		}

		[[nodiscard]] constexpr Vector2D operator -(const Vector2D& v) const noexcept
		{
			return{ x - v.x, y - v.y };
		}

		[[nodiscard]] constexpr Vector2D operator *(value_type s) const noexcept
		{
			return{ x * s, y * s };
		}

		[[nodiscard]] constexpr Vector2D operator *(const Vector2D& v) const noexcept
		{
			return{ x * v.x, y * v.y };
		}

		[[nodiscard]] constexpr Vector2D operator /(value_type s) const noexcept
		{
			return *this * (static_cast<value_type>(1.0) / s);
		}

		[[nodiscard]] constexpr Vector2D operator /(const Vector2D& v) const noexcept
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

		[[nodiscard]] constexpr bool operator ==(const Vector2D& v) const noexcept
		{
			return v.x == x && v.y == y;
		}

		[[nodiscard]] constexpr bool operator !=(const Vector2D& v) const noexcept
		{
			return v.x != x || v.y != y;
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

		[[nodiscard]] constexpr Vector2D movedBy(value_type _x, value_type _y) const noexcept
		{
			return{ x + _x, y + _y };
		}

		[[nodiscard]] constexpr Vector2D movedBy(const Vector2D& v) const noexcept
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

		[[nodiscard]] Vector2D clamped(const RectF& rect) const noexcept;

		Vector2D& clamp(const RectF& rect) noexcept;

		[[nodiscard]] constexpr bool isZero() const noexcept
		{
			return x == static_cast<value_type>(0.0)
				&& y == static_cast<value_type>(0.0);
		}

		[[nodiscard]] bool hasNaN() const noexcept
		{
			return std::isnan(x)
				|| std::isnan(y);
		}

		[[nodiscard]] constexpr value_type dot(const Vector2D& v) const noexcept
		{
			return x * v.x + y * v.y;
		}

		[[nodiscard]] constexpr value_type cross(const Vector2D& v) const noexcept
		{
			return x * v.y - y * v.x;
		}

		[[nodiscard]] value_type length() const noexcept
		{
			return std::sqrt(lengthSq());
		}

		[[nodiscard]] constexpr value_type lengthSq() const noexcept
		{
			return dot(*this);
		}

		[[nodiscard]] value_type lengthInv() const noexcept
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

		[[nodiscard]] Vector2D clampLength(value_type maxLength) const noexcept
		{
			const value_type len = length();

			if (len <= maxLength)
			{
				return *this;
			}
			else
			{
				return *this * (maxLength / len);
			}
		}

		[[nodiscard]] value_type distanceFrom(value_type _x, value_type _y) const noexcept
		{
			return distanceFrom({ _x, _y });
		}

		[[nodiscard]] value_type distanceFrom(const Vector2D& v) const noexcept
		{
			return (*this - v).length();
		}

		[[nodiscard]] constexpr value_type distanceFromSq(value_type _x, value_type _y) const noexcept
		{
			return distanceFromSq({ _x, _y });
		}

		[[nodiscard]] constexpr value_type distanceFromSq(const Vector2D& v) const noexcept
		{
			return (*this - v).lengthSq();
		}

		[[nodiscard]] Vector2D normalized() const noexcept
		{
			return *this * lengthInv();
		}

		Vector2D& normalize() noexcept
		{
			return *this *= lengthInv();
		}

		[[nodiscard]] Vector2D rotated(value_type angle) const noexcept
		{
			const value_type s = std::sin(angle);
			const value_type c = std::cos(angle);
			return{ x * c - y * s, x * s + y * c };
		}

		Vector2D& rotate(value_type angle) noexcept
		{
			return *this = rotated(angle);
		}
		
		[[nodiscard]] value_type getAngle(const Vector2D& v) const
		{
			if (isZero() || v.isZero())
			{
				return static_cast<value_type>(Math::Constants::NaN);
			}

			return std::atan2(cross(v), dot(v));
		}

		[[nodiscard]] constexpr Vector2D projection(const Vector2D& onto) const noexcept
		{
			return onto.lengthSq() ? onto * dot(onto) / onto.lengthSq() : Zero();
		}

		[[nodiscard]] constexpr Vector2D lerp(const Vector2D& other, double f) const noexcept
		{
			return Vector2D(x + (other.x - x) * f, y + (other.y - y) * f);
		}

		[[nodiscard]] constexpr Point asPoint() const noexcept
		{
			return{ static_cast<Point::value_type>(x), static_cast<Point::value_type>(y) };
		}

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		/// <summary>
		/// Vector2D{ x, x }
		/// </summary>
		[[nodiscard]] constexpr Vector2D xx() const noexcept
		{
			return{ x, x };
		}

		/// <summary>
		/// Vector2D{ x, y }
		/// </summary>
		[[nodiscard]] constexpr Vector2D xy() const noexcept
		{
			return{ x, y };
		}

		/// <summary>
		/// Vector2D{ y, x }
		/// </summary>
		[[nodiscard]] constexpr Vector2D yx() const noexcept
		{
			return{ y, x };
		}

		/// <summary>
		/// Vector2D{ y, y }
		/// </summary>
		[[nodiscard]] constexpr Vector2D yy() const noexcept
		{
			return{ y, y };
		}
 
		/// <summary>
		/// Vector2D{ 0, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D Zero() noexcept
		{
			return{ 0, 0 };
		}

		/// <summary>
		/// Vector2D{ 1, 1 }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D One() noexcept
		{
			return{ 1, 1 };
		}

		/// <summary>
		/// Vector2D{ value, value }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D All(value_type value = 1) noexcept
		{
			return{ value, value };
		}

		/// <summary>
		/// Vector2D{ 1, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D UnitX() noexcept
		{
			return{ 1, 0 };
		}

		/// <summary>
		/// Vector2D{ 0, 1 }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D UnitY() noexcept
		{
			return{ 0, 1 };
		}

		/// <summary>
		/// Vector2D{ -length, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D Left(value_type length = 1) noexcept
		{
			return{ -length, 0 };
		}

		/// <summary>
		/// Vector2D{ length, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D Right(value_type length = 1) noexcept
		{
			return{ length, 0 };
		}

		/// <summary>
		/// Vector2D{ 0, -length }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D Up(value_type length = 1) noexcept
		{
			return{ 0, -length };
		}

		/// <summary>
		/// Vector2D{ 0, length }
		/// </summary>
		[[nodiscard]] static constexpr Vector2D Down(value_type length = 1) noexcept
		{
			return{ 0, length };
		}
	};

	template <class Type, class U, std::enable_if_t<std::is_scalar_v<U>>* = nullptr>
	[[nodiscard]] inline constexpr Vector2D<Type> operator *(U s, const Vector2D<Type>& v) noexcept
	{
		return v * static_cast<Type>(s);
	}

	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	using SizeF		= Vec2;
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Float2& value);

	void Formatter(FormatData& formatData, const Vec2& value);

	template <class CharType, class Type>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Vector2D<Type>& value)
	{
		return os << CharType('(')
			<< value.x << CharType(',') << CharType(' ')
			<< value.y << CharType(')');
	}

	template <class CharType, class Type>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Vector2D<Type>& value)
	{
		CharType unused;
		return is >> unused
			>> value.x >> unused
			>> value.y >> unused;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <class Type>
	struct hash<s3d::Vector2D<Type>>
	{
		[[nodiscard]] size_t operator()(const s3d::Vector2D<Type>& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt_s3d
{
	template <class Type>
	struct formatter<s3d::Vector2D<Type>, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Vector2D<Type>& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.x, value.y);
		}
	};
}
