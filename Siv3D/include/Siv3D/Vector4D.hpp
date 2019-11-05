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
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Format.hpp"
# include "Hash.hpp"

namespace s3d
{
	/// <summary>
	/// 4 次元ベクトル
	/// </summary>
	template <class Type>
	struct Vector4D
	{
		template <class U>
		using vector_type = Vector4D<U>;

		using value_type = Type;

		value_type x, y, z, w;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Vector4D() noexcept = default;

		constexpr Vector4D(const Vector4D&) noexcept = default;

		template <class X, class Y, class Z, class W>
		constexpr Vector4D(X _x, Y _y, Z _z, W _w) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y))
			, z(static_cast<value_type>(_z))
			, w(static_cast<value_type>(_w)) {}

		constexpr Vector4D(value_type _x, value_type _y, value_type _z, value_type _w) noexcept
			: x(_x)
			, y(_y)
			, z(_z)
			, w(_w) {}

		template <class X, class Y>
		constexpr Vector4D(X _x, Y _y, const Vector2D<value_type>& zw) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y))
			, z(zw.x)
			, w(zw.y) {}

		template <class X, class W>
		constexpr Vector4D(X _x, const Vector2D<value_type>& yz, W _w) noexcept
			: x(static_cast<value_type>(_x))
			, y(yz.x)
			, z(yz.y)
			, w(static_cast<value_type>(_w)) {}

		template <class Z, class W>
		constexpr Vector4D(const Vector2D<value_type>& xy, Z _z, W _w) noexcept
			: x(xy.x)
			, y(xy.y)
			, z(static_cast<value_type>(_z))
			, w(static_cast<value_type>(_w)) {}

		constexpr Vector4D(const Vector2D<value_type>& xy, const Vector2D<value_type>& zw) noexcept
			: x(xy.x)
			, y(xy.y)
			, z(zw.x)
			, w(zw.y) {}

		template <class X>
		constexpr Vector4D(X _x, const Vector3D<value_type>& yzw) noexcept
			: x(static_cast<value_type>(_x))
			, y(yzw.x)
			, z(yzw.y)
			, w(yzw.z) {}

		template <class Z>
		constexpr Vector4D(const Vector3D<value_type>& xyz, Z _z) noexcept
			: x(xyz.x)
			, y(xyz.y)
			, z(xyz.z)
			, w(static_cast<value_type>(_z)) {}

		template <class U>
		constexpr Vector4D(const Vector4D<U>& v) noexcept
			: x(static_cast<value_type>(v.x))
			, y(static_cast<value_type>(v.y))
			, z(static_cast<value_type>(v.z))
			, w(static_cast<value_type>(v.w)) {}

		[[nodiscard]] constexpr value_type elem(size_t index) const noexcept
		{
			return index == 0 ? x
				: index == 1 ? y
				: index == 2 ? z
				: index == 3 ? w
				: 0;
		}

		[[nodiscard]] constexpr Vector4D operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] constexpr Vector4D operator -() const noexcept
		{
			return{ -x, -y, -z, -w };
		}

		[[nodiscard]] constexpr Vector4D operator +(const Vector4D& v) const noexcept
		{
			return{ x + v.x, y + v.y, z + v.z, w + v.w };
		}

		[[nodiscard]] constexpr Vector4D operator -(const Vector4D& v) const noexcept
		{
			return{ x - v.x, y - v.y, z - v.z, w - v.w };
		}

		[[nodiscard]] constexpr Vector4D operator *(value_type s) const noexcept
		{
			return{ x * s, y * s, z * s, w * s };
		}

		[[nodiscard]] constexpr Vector4D operator *(const Vector4D& v) const noexcept
		{
			return{ x * v.x, y * v.y, z * v.z, w * v.w };
		}

		[[nodiscard]] constexpr Vector4D operator /(value_type s) const noexcept
		{
			return *this * (static_cast<value_type>(1.0) / s);
		}

		[[nodiscard]] constexpr Vector4D operator /(const Vector4D& v) const noexcept
		{
			return{ x / v.x, y / v.y, z / v.z, w / v.w };
		}

		constexpr Vector4D& operator +=(const Vector4D& v) noexcept
		{
			x += v.x; y += v.y; z += v.z; w += v.w;
			return *this;
		}

		constexpr Vector4D& operator -=(const Vector4D& v) noexcept
		{
			x -= v.x; y -= v.y; z -= v.z; w -= v.w;
			return *this;
		}

		constexpr Vector4D& operator *=(value_type s) noexcept
		{
			x *= s; y *= s; z *= s; w *= s;
			return *this;
		}

		constexpr Vector4D& operator *=(const Vector4D& v) noexcept
		{
			x *= v.x; y *= v.y; z *= v.z; w *= v.w;
			return *this;
		}

		constexpr Vector4D& operator /=(value_type s) noexcept
		{
			return *this *= (static_cast<value_type>(1.0) / s);
		}

		constexpr Vector4D& operator /=(const Vector4D& v) noexcept
		{
			x /= v.x; y /= v.y; z /= v.z; w /= v.w;
			return *this;
		}

		[[nodiscard]] constexpr bool operator ==(const Vector4D& v) const noexcept
		{
			return v.x == x && v.y == y && v.z == z && v.w == w;
		}

		[[nodiscard]] constexpr bool operator !=(const Vector4D& v) const noexcept
		{
			return v.x != x || v.y != y || v.z != z || v.w != w;
		}

		constexpr Vector4D& set(value_type _x, value_type _y, value_type _z, value_type _w) noexcept
		{
			x = _x; y = _y; z = _z; w = _w;
			return *this;
		}

		constexpr Vector4D& set(const Vector2D<value_type>& xy, value_type _z, value_type _w) noexcept
		{
			x = xy.x; y = xy.y; z = _z; w = _w;
			return *this;
		}

		constexpr Vector4D& set(value_type _x, const Vector2D<value_type>& yz, value_type _w) noexcept
		{
			x = _x; y = yz.x; z = yz.y; w = _w;
			return *this;
		}

		constexpr Vector4D& set(value_type _x, value_type _y, const Vector2D<value_type>& zw) noexcept
		{
			x = _x; y = _y; z = zw.x; w = zw.y;
			return *this;
		}

		constexpr Vector4D& set(const Vector3D<value_type>& xyz, value_type _w) noexcept
		{
			x = xyz.x; y = xyz.y; z = xyz.z; w = _w;
			return *this;
		}

		constexpr Vector4D& set(value_type _x, const Vector3D<value_type>& yzw) noexcept
		{
			x = _x; y = yzw.x; z = yzw.y; w = yzw.z;
			return *this;
		}

		constexpr Vector4D& set(const Vector4D& v) noexcept
		{
			return *this = v;
		}

		[[nodiscard]] constexpr Vector4D movedBy(value_type _x, value_type _y, value_type _z, value_type _w) const noexcept
		{
			return{ x + _x, y + _y, z + _z, w + _w };
		}

		[[nodiscard]] constexpr Vector4D movedBy(const Vector4D& v) const noexcept
		{
			return{ x + v.x, y + v.y, z + v.z, w + v.w };
		}

		constexpr Vector4D& moveBy(value_type _x, value_type _y, value_type _z, value_type _w) noexcept
		{
			x += _x; y += _y; z += _z; w += _w;
			return *this;
		}

		constexpr Vector4D& moveBy(const Vector4D& v) noexcept
		{
			return *this += v;
		}

		[[nodiscard]] constexpr bool isZero() const noexcept
		{
			return x == static_cast<value_type>(0.0)
				&& y == static_cast<value_type>(0.0)
				&& z == static_cast<value_type>(0.0)
				&& w == static_cast<value_type>(0.0);
		}

		[[nodiscard]] bool hasNaN() const noexcept
		{
			return std::isnan(x)
				|| std::isnan(y)
				|| std::isnan(z)
				|| std::isnan(w);
		}

		[[nodiscard]] constexpr Type dot(const Vector4D& v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
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

		Vector4D& setLength(value_type _length) noexcept
		{
			const value_type len = length();

			if (len == 0.0)
			{
				return *this;
			}

			return *this *= (_length / len);
		}

		[[nodiscard]] Vector4D clampLength(value_type maxLength) const noexcept
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

		[[nodiscard]] value_type distanceFrom(double _x, double _y, double _z, double _w) const noexcept
		{
			return (*this - Vector4D(_x, _y, _z, _w)).length();
		}

		[[nodiscard]] value_type distanceFrom(const Vector4D& v) const noexcept
		{
			return (*this - v).length();
		}

		[[nodiscard]] constexpr value_type distanceFromSq(double _x, double _y, double _z, double _w) const noexcept
		{
			return (*this - Vector4D(_x, _y, _z, _w)).lengthSq();
		}

		[[nodiscard]] constexpr value_type distanceFromSq(const Vector4D& v) const noexcept
		{
			return (*this - v).lengthSq();
		}

		[[nodiscard]] Vector4D normalized() const noexcept
		{
			return *this * lengthInv();
		}

		Vector4D& normalize() noexcept
		{
			return *this *= lengthInv();
		}

		[[nodiscard]] constexpr Vector4D lerp(const Vector4D& other, double f) const noexcept
		{
			return Vector4D(x + (other.x - x) * f, y + (other.y - y) * f, z + (other.z - z) * f, w + (other.w - w) * f);
		}

		/// <summary>
		/// Vector2D{ x, x }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> xx() const noexcept
		{
			return{ x, x };
		}

		/// <summary>
		/// Vector2D{ x, y }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> xy() const noexcept
		{
			return{ x, y };
		}

		/// <summary>
		/// Vector2D{ x, z }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> xz() const noexcept
		{
			return{ x, z };
		}

		/// <summary>
		/// Vector2D{ x, w }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> xw() const noexcept
		{
			return{ x, w };
		}

		/// <summary>
		/// Vector2D{ y, x }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> yx() const noexcept
		{
			return{ y, x };
		}

		/// <summary>
		/// Vector2D{ y, y }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> yy() const noexcept
		{
			return{ y, y };
		}

		/// <summary>
		/// Vector2D{ y, z }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> yz() const noexcept
		{
			return{ y, z };
		}

		/// <summary>
		/// Vector2D{ y, w }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> yw() const noexcept
		{
			return{ y, w };
		}

		/// <summary>
		/// Vector2D{ z, x }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> zx() const noexcept
		{
			return{ z, x };
		}

		/// <summary>
		/// Vector2D{ z, y }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> zy() const noexcept
		{
			return{ z, y };
		}

		/// <summary>
		/// Vector2D{ z, z }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> zz() const noexcept
		{
			return{ z, z };
		}

		/// <summary>
		/// Vector2D{ z, w }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> zw() const noexcept
		{
			return{ z, w };
		}

		/// <summary>
		/// Vector2D{ w, x }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> wx() const noexcept
		{
			return{ w, x };
		}

		/// <summary>
		/// Vector2D{ w, y }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> wy() const noexcept
		{
			return{ w, y };
		}

		/// <summary>
		/// Vector2D{ w, z }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> wz() const noexcept
		{
			return{ w, z };
		}

		/// <summary>
		/// Vector2D{ w, w }
		/// </summary>
		[[nodiscard]] constexpr Vector2D<value_type> ww() const noexcept
		{
			return{ w, w };
		}

		/// <summary>
		/// Vector3D{ x, x, x }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> xxx() const noexcept
		{
			return{ x, x, x };
		}

		/// <summary>
		/// Vector3D{ y, y, y }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> yyy() const noexcept
		{
			return{ y, y, y };
		}

		/// <summary>
		/// Vector3D{ z, z, z }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> zzz() const noexcept
		{
			return{ z, z, z };
		}

		/// <summary>
		/// Vector3D{ w, w, w }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> www() const noexcept
		{
			return{ w, w, w };
		}

		/// <summary>
		/// Vector3D{ x, y, z }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> xyz() const noexcept
		{
			return{ x, y, z };
		}

		/// <summary>
		/// Vector3D{ z, y, x }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> zyx() const noexcept
		{
			return{ z, y, x };
		}

		/// <summary>
		/// Vector3D{ y, z, w }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> yzw() const noexcept
		{
			return{ y, z, w };
		}

		/// <summary>
		/// Vector3D{ w, z, y }
		/// </summary>
		[[nodiscard]] constexpr Vector3D<value_type> wzy() const noexcept
		{
			return{ w, z, y };
		}

		/// <summary>
		/// Vector4D{ x, x, x, x }
		/// </summary>
		[[nodiscard]] constexpr Vector4D xxxx() const noexcept
		{
			return{ x, x, x, x };
		}

		/// <summary>
		/// Vector4D{ y, y, y, y }
		/// </summary>
		[[nodiscard]] constexpr Vector4D yyyy() const noexcept
		{
			return{ y, y, y, y };
		}

		/// <summary>
		/// Vector4D{ z, z, z, z }
		/// </summary>
		[[nodiscard]] constexpr Vector4D zzzz() const noexcept
		{
			return{ z, z, z, z };
		}

		/// <summary>
		/// Vector4D{ w, w, w, w }
		/// </summary>
		[[nodiscard]] constexpr Vector4D wwww() const noexcept
		{
			return{ w, w, w, w };
		}

		/// <summary>
		/// Vector4D{ x, y, z, w }
		/// </summary>
		[[nodiscard]] constexpr Vector4D xyzw() const noexcept
		{
			return{ x, y, z, w };
		}

		/// <summary>
		/// Vector4D{ w, x, y, z }
		/// </summary>
		[[nodiscard]] constexpr Vector4D wxyz() const noexcept
		{
			return{ w, x, y, z };
		}

		/// <summary>
		/// Vector4D{ z, w, x, y }
		/// </summary>
		[[nodiscard]] constexpr Vector4D zwxy() const noexcept
		{
			return{ z, w, x, y };
		}

		/// <summary>
		/// Vector4D{ y, z, w, x }
		/// </summary>
		[[nodiscard]] constexpr Vector4D yzwx() const noexcept
		{
			return{ y, z, w, x };
		}

		/// <summary>
		/// Vector4D{ w, z, y, x }
		/// </summary>
		[[nodiscard]] constexpr Vector4D wzyx() const noexcept
		{
			return{ w, z, y, x };
		}

		/// <summary>
		/// Vector4D{ 0, 0, 0, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector4D Zero() noexcept
		{
			return{ 0, 0, 0, 0 };
		}

		/// <summary>
		/// Vector4D{ 1, 1, 1, 1 }
		/// </summary>
		[[nodiscard]] static constexpr Vector4D One() noexcept
		{
			return{ 1, 1, 1, 1 };
		}

		/// <summary>
		/// Vector4D{ value, value, value, value }
		/// </summary>
		[[nodiscard]] static constexpr Vector4D All(value_type value = 1) noexcept
		{
			return{ value, value, value, value };
		}

		/// <summary>
		/// Vector4D{ 1, 0, 0, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector4D UnitX() noexcept
		{
			return{ 1, 0, 0, 0 };
		}

		/// <summary>
		/// Vector4D{ 0, 1, 0, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector4D UnitY() noexcept
		{
			return{ 0, 1, 0, 0 };
		}

		/// <summary>
		/// Vector4D{ 0, 0, 1, 0 }
		/// </summary>
		[[nodiscard]] static constexpr Vector4D UnitZ() noexcept
		{
			return{ 0, 0, 1, 0 };
		}

		/// <summary>
		/// Vector4D{ 0, 0, 0, 1 }
		/// </summary>
		[[nodiscard]] static constexpr Vector4D UnitW() noexcept
		{
			return{ 0, 0, 0, 1 };
		}
	};

	template <class Type, class U, std::enable_if_t<std::is_scalar_v<U>>* = nullptr>
	[[nodiscard]] inline constexpr Vector4D<Type> operator *(U s, const Vector4D<Type>& v) noexcept
	{
		return v * static_cast<Type>(s);
	}

	using Float4	= Vector4D<float>;
	using Vec4		= Vector4D<double>;
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Float4& value);
	
	void Formatter(FormatData& formatData, const Vec4& value);

	template <class CharType, class Type>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Vector4D<Type>& value)
	{
		return output << CharType('(')
			<< value.x << CharType(',') << CharType(' ')
			<< value.y << CharType(',') << CharType(' ')
			<< value.z << CharType(',') << CharType(' ')
			<< value.w << CharType(')');
	}

	template <class CharType, class Type>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& input, Vector4D<Type>& value)
	{
		CharType unused;
		return input >> unused
			>> value.x >> unused
			>> value.y >> unused
			>> value.z >> unused
			>> value.w >> unused;
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
	struct hash<s3d::Vector4D<Type>>
	{
		[[nodiscard]] size_t operator()(const s3d::Vector4D<Type>& value) const noexcept
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
	struct formatter<s3d::Vector4D<Type>, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Vector4D<Type>& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.x, value.y, value.z, value.w);
		}
	};
}
