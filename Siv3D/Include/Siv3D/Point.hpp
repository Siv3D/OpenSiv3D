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
# include <utility>
# include <cassert>
# include <iostream>
# include "Platform.hpp"
# include "Fwd.hpp"
# include "Format.hpp"
# include "Color.hpp"
# include "Intersection.hpp"

namespace s3d
{
	/// <summary>
	/// 点、またはサイズ
	/// </summary>
	struct Point
	{
		template <class U>
		using vector_type = Vector2D<U>;

		using value_type = int32;

		value_type x, y;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Point() noexcept = default;

		constexpr Point(const Point&) noexcept = default;

		constexpr Point(int32 _x, int32 _y) noexcept
			: x(_x)
			, y(_y) {}

		template <class X, class Y, std::enable_if_t<std::is_integral<X>::value && std::is_integral<Y>::value>* = nullptr>
		constexpr Point(X _x, Y _y) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y)) {}

		template <class X, class Y, std::enable_if_t<!std::is_integral<X>::value || !std::is_integral<Y>::value>* = nullptr>
		constexpr Point(X _x, Y _y) noexcept = delete;

		/// <summary>
		/// Point{ x, x }
		/// </summary>
		[[nodiscard]] constexpr Point xx() const noexcept
		{
			return{ x, x };
		}

		/// <summary>
		/// Point{ x, y }
		/// </summary>
		[[nodiscard]] constexpr Point xy() const noexcept
		{
			return *this;
		}

		/// <summary>
		/// Point{ y, x }
		/// </summary>
		[[nodiscard]] constexpr Point yx() const noexcept
		{
			return{ y, x };
		}

		/// <summary>
		/// Point{ y, y }
		/// </summary>
		[[nodiscard]] constexpr Point yy() const noexcept
		{
			return{ y, y };
		}

		[[nodiscard]] constexpr Point operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] constexpr Point operator -() const noexcept
		{
			return{ -x, -y };
		}

		[[nodiscard]] constexpr Point operator +(const Point& p) const noexcept
		{
			return{ x + p.x, y + p.y };
		}

		[[nodiscard]] constexpr Point operator -(const Point& p) const noexcept
		{
			return{ x - p.x, y - p.y };
		}

		template <class Type>
		[[nodiscard]] constexpr Vector2D<Type> operator +(const Vector2D<Type>& v) const noexcept;

		template <class Type>
		[[nodiscard]] constexpr Vector2D<Type> operator -(const Vector2D<Type>& v) const noexcept;

		[[nodiscard]] constexpr Point operator *(const int32 s) const noexcept
		{
			return{ x * s, y * s };
		}

		[[nodiscard]] constexpr Float2 operator *(float s) const noexcept;

		[[nodiscard]] constexpr Vec2 operator *(double s) const noexcept;

		[[nodiscard]] constexpr Point operator *(const Point& p) const noexcept
		{
			return{ x * p.x, y * p.y };
		}

		template <class Type>
		[[nodiscard]] constexpr Vector2D<Type> operator *(const Vector2D<Type>& v) const noexcept;

		[[nodiscard]] constexpr Point operator /(const int32 s) const noexcept
		{
			return{ x / s, y / s };
		}

		[[nodiscard]] constexpr Point operator /(const Point& p) const noexcept
		{
			return{ x / p.x, y / p.y };
		}

		template <class Type>
		[[nodiscard]] constexpr Vector2D<Type> operator /(const Vector2D<Type>& v) const noexcept;

		[[nodiscard]] constexpr Float2 operator /(float s) const noexcept;

		[[nodiscard]] constexpr Vec2 operator /(double s) const noexcept;

		constexpr Point& operator +=(const Point& p) noexcept
		{
			x += p.x; y += p.y;
			return *this;
		}

		constexpr Point& operator -=(const Point& p) noexcept
		{
			x -= p.x; y -= p.y;
			return *this;
		}

		constexpr Point& operator *=(const int32 s) noexcept
		{
			x *= s; y *= s;
			return *this;
		}

		constexpr Point& operator /=(const int32 s) noexcept
		{
			assert(s != 0);
			x /= s; y /= s;
			return *this;
		}

		[[nodiscard]] constexpr bool operator ==(const Point& p) const noexcept
		{
			return x == p.x && y == p.y;
		}

		[[nodiscard]] constexpr bool operator !=(const Point& p) const noexcept
		{
			return x != p.x || y != p.y;
		}

		constexpr Point& set(const int32 _x, const int32 _y) noexcept
		{
			x = _x; y = _y;
			return *this;
		}

		constexpr Point& set(const Point& p) noexcept
		{
			return *this = p;
		}

		[[nodiscard]] constexpr Point movedBy(const int32 _x, const int32 _y) const noexcept
		{
			return{ x + _x, y + _y };
		}

		[[nodiscard]] constexpr Point movedBy(const Point& p) const noexcept
		{
			return{ x + p.x, y + p.y };
		}

		template <class Type>
		[[nodiscard]] constexpr Vector2D<Type> movedBy(const Vector2D<Type>& v) const noexcept;

		constexpr Point& moveBy(int32 _x, int32 _y) noexcept
		{
			x += _x; y += _y;
			return *this;
		}

		constexpr Point& moveBy(const Point& p) noexcept
		{
			return *this += p;
		}

		[[nodiscard]] constexpr bool isZero() const noexcept
		{
			return x == 0 && y == 0;
		}

		[[nodiscard]] double distanceFrom(const Point& p) const noexcept;

		template <class Type>
		[[nodiscard]] Type distanceFrom(const Vector2D<Type>& p) const noexcept;

		[[nodiscard]] constexpr double distanceFromSq(const Point& p) const noexcept;

		template <class Type>
		[[nodiscard]] constexpr Type distanceFromSq(const Vector2D<Type>& p) const noexcept;

		template <class Type = double>
		[[nodiscard]] Type length() const noexcept;

		template <class Type = double>
		[[nodiscard]] constexpr Type lengthSq() const noexcept;

		template <class Type>
		[[nodiscard]] constexpr Vector2D<Type> lerp(const Vector2D<Type>& other, const double f) const noexcept;

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		[[nodiscard]] bool leftClicked() const;

		[[nodiscard]] bool leftPressed() const;

		[[nodiscard]] bool leftReleased() const;

		[[nodiscard]] bool rightClicked() const;

		[[nodiscard]] bool rightPressed() const;

		[[nodiscard]] bool rightReleased() const;

		[[nodiscard]] bool mouseOver() const;

		/// <summary>
		/// Point{ 0, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Point Zero() noexcept
		{
			return{ 0, 0 };
		}

		/// <summary>
		/// Point{ 1, 1 }
		/// </summary>
		[[nodiscard]] static constexpr Point One() noexcept
		{
			return{ 1, 1 };
		}

		/// <summary>
		/// Point{ value, value }
		/// </summary>
		[[nodiscard]] static constexpr Point All(const value_type value = 1) noexcept
		{
			return{ value, value };
		}

		/// <summary>
		/// Point{ 1, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Point UnitX() noexcept
		{
			return{ 1, 0 };
		}

		/// <summary>
		/// Point{ 0, 1 }
		/// </summary>
		[[nodiscard]] static constexpr Point UnitY() noexcept
		{
			return{ 0, 1 };
		}

		/// <summary>
		/// Point{ -length, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Point Left(const value_type length = 1) noexcept
		{
			return{ -length, 0 };
		}

		/// <summary>
		/// Point{ length, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Point Right(const value_type length = 1) noexcept
		{
			return{ length, 0 };
		}

		/// <summary>
		/// Point{ 0, -length }
		/// </summary>
		[[nodiscard]] static constexpr Point Up(const value_type length = 1) noexcept
		{
			return{ 0, -length };
		}

		/// <summary>
		/// Point{ 0, length }
		/// </summary>
		[[nodiscard]] static constexpr Point Down(const value_type length = 1) noexcept
		{
			return{ 0, length };
		}
	};

	[[nodiscard]] inline constexpr Point operator *(int32 s, const Point& p) noexcept;

	[[nodiscard]] inline constexpr Float2 operator *(float s, const Point& p) noexcept;

	[[nodiscard]] inline constexpr Vec2 operator *(double s, const Point& p) noexcept;

	using Size = Point;
}

namespace std
{
	template <>
	struct hash<s3d::Point>
	{
		[[nodiscard]] size_t operator()(const s3d::Point& keyVal) const noexcept
		{
			return hash<s3d::uint64>()(*((s3d::uint64*)&keyVal));
		}
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Point
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
	void Formatter(FormatData& formatData, const Point& value);

	/// <summary>
	/// 出力ストリームに点を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="v">
	/// 点
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, const Point& v)
	{
		return os << CharType('(')
			<< v.x << CharType(',')
			<< v.y << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに点を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="v">
	/// 点
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& is, Point& v)
	{
		CharType unused;
		return is >> unused
			>> v.x >> unused
			>> v.y >> unused;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::Point& v)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("({") + tag + S3DSTR("},{") + tag + S3DSTR("})");

		f.writer().write(fmt, v.x, v.y);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
