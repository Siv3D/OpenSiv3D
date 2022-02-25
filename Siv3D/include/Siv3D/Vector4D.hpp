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
# include "FormatData.hpp"
# include "FormatLiteral.hpp"

namespace s3d
{
	/// @brief 4 次元のベクトル
	/// @tparam Type ベクトルの要素の型
	template <class Type>
	struct Vector4D
	{
		using value_type = Type;

		static constexpr size_t Dimension = 4;

		value_type x, y, z, w;

		SIV3D_NODISCARD_CXX20
		Vector4D() = default;

		SIV3D_NODISCARD_CXX20
		Vector4D(const Vector4D&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(value_type _x, value_type _y, value_type _z, value_type _w) noexcept;

		template <class X, class Y, class Z, class W>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, Y _y, Z _z, W _w) noexcept;

		template <class U>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector4D<U>& v) noexcept;

		template <class X, class Y>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, Y _y, const Vector2D<value_type>& zw) noexcept;

		template <class X, class W>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, const Vector2D<value_type>& yz, W _w) noexcept;

		template <class Z, class W>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector2D<value_type>& xy, Z _z, W _w) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector2D<value_type>& xy, const Vector2D<value_type>& zw) noexcept;

		template <class X>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(X _x, const Vector3D<value_type>& yzw) noexcept;

		template <class Z>
		SIV3D_NODISCARD_CXX20
		constexpr Vector4D(const Vector3D<value_type>& xyz, Z _z) noexcept;

		[[nodiscard]]
		constexpr value_type elem(size_t index) const noexcept;

		[[nodiscard]]
		value_type* getPointer() noexcept;

		[[nodiscard]]
		const value_type* getPointer() const noexcept;

		constexpr Vector4D& operator =(const Vector4D&) = default;

		[[nodiscard]]
		constexpr Vector4D operator +() const noexcept;

		[[nodiscard]]
		constexpr Vector4D operator -() const noexcept;

		[[nodiscard]]
		constexpr Vector4D operator +(Vector4D v) const noexcept;

		[[nodiscard]]
		constexpr Vector4D operator -(Vector4D v) const noexcept;

		[[nodiscard]]
		constexpr Vector4D operator *(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector4D operator *(Vector4D v) const noexcept;

		[[nodiscard]]
		constexpr Vector4D operator /(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector4D operator /(Vector4D v) const noexcept;

		constexpr Vector4D& operator +=(Vector4D v) noexcept;

		constexpr Vector4D& operator -=(Vector4D v) noexcept;

		constexpr Vector4D& operator *=(value_type s) noexcept;

		constexpr Vector4D& operator *=(Vector4D v) noexcept;

		constexpr Vector4D& operator /=(value_type s) noexcept;

		constexpr Vector4D& operator /=(Vector4D v) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend constexpr Vector4D operator *(Arithmetic s, const Vector4D& v) noexcept
		{
			return (v * static_cast<Type>(s));
		}

		[[nodiscard]]
		friend constexpr bool operator ==(const Vector4D& lhs, const Vector4D& rhs) noexcept
		{
			return (lhs.x == rhs.x)
				&& (lhs.y == rhs.y)
				&& (lhs.z == rhs.z)
				&& (lhs.w == rhs.w);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Vector4D& lhs, const Vector4D& rhs) noexcept
		{
			return (lhs.x != rhs.x)
				|| (lhs.y != rhs.y)
				|| (lhs.z != rhs.z)
				|| (lhs.w != rhs.w);
		}

		[[nodiscard]]
		constexpr bool epsilonEquals(Vector4D other, value_type epsilon) const noexcept;

		[[nodiscard]]
		constexpr bool hasSameDirection(Vector4D other) const noexcept;

		[[nodiscard]]
		constexpr bool hasOppositeDirection(Vector4D other) const noexcept;

		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		[[nodiscard]]
		bool hasNaN() const noexcept;

		[[nodiscard]]
		constexpr value_type minComponent() const noexcept;

		[[nodiscard]]
		constexpr value_type maxComponent() const noexcept;

		constexpr void clear() noexcept;

		constexpr Vector4D& set(const Vector2D<value_type>& xy, const Vector2D<value_type>& zw) noexcept;

		constexpr Vector4D& set(const Vector2D<value_type>& xy, value_type _z, value_type _w) noexcept;

		constexpr Vector4D& set(value_type _x, const Vector2D<value_type>& yz, value_type _w) noexcept;

		constexpr Vector4D& set(value_type _x, value_type _y, const Vector2D<value_type>& zw) noexcept;

		constexpr Vector4D& set(const Vector3D<value_type>& xyz, value_type _w) noexcept;

		constexpr Vector4D& set(value_type _x, const Vector3D<value_type>& yzw) noexcept;

		constexpr Vector4D& set(value_type _x, value_type _y, value_type _z, value_type _w) noexcept;

		constexpr Vector4D& set(Vector4D v) noexcept;

		[[nodiscard]]
		constexpr Vector4D movedBy(value_type _x, value_type _y, value_type _z, value_type _w) const noexcept;

		[[nodiscard]]
		constexpr Vector4D movedBy(Vector4D v) const noexcept;

		constexpr Vector4D& moveBy(value_type _x, value_type _y, value_type _z, value_type _w) noexcept;

		constexpr Vector4D& moveBy(Vector4D v) noexcept;

		[[nodiscard]]
		constexpr value_type dot(Vector4D v) const noexcept;

		[[nodiscard]]
		value_type length() const noexcept;

		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		[[nodiscard]]
		value_type invLength() const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanLength() const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(value_type _x, value_type _y, value_type _z, value_type _w) const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(Vector4D v) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(value_type _x, value_type _y, value_type _z, value_type _w) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(Vector4D v) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(value_type _x, value_type _y, value_type _z, value_type _w) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(Vector4D v) const noexcept;

		[[nodiscard]]
		Vector4D withLength(value_type _length) const noexcept;

		Vector4D& setLength(value_type _length) noexcept;

		[[nodiscard]]
		Vector4D limitLength(value_type maxLength) const noexcept;

		Vector4D& limitLengthSelf(value_type maxLength) noexcept;

		[[nodiscard]]
		Vector4D normalized() const noexcept;

		Vector4D& normalize() noexcept;

		[[nodiscard]]
		constexpr Vector4D getMidpoint(Vector4D other) const noexcept;

		[[nodiscard]]
		constexpr Vector4D lerp(Vector4D other, value_type f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> xx() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> xy() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> xz() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> xw() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> yx() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> yy() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> yz() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> yw() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> zx() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> zy() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> zz() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> zw() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> wx() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> wy() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> wz() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> ww() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> xxx() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> xyz() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> yyy() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> yxz() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> yzw() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> zzz() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> zyx() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> www() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<value_type> wzy() const noexcept;

		[[nodiscard]]
		constexpr Vector4D xyz0() const noexcept;

		[[nodiscard]]
		constexpr Vector4D xyz1() const noexcept;

		[[nodiscard]]
		constexpr Vector4D xyzw() const noexcept;

		[[nodiscard]]
		constexpr Vector4D xxxx() const noexcept;

		[[nodiscard]]
		constexpr Vector4D yyyy() const noexcept;

		[[nodiscard]]
		constexpr Vector4D zzzz() const noexcept;

		[[nodiscard]]
		constexpr Vector4D wwww() const noexcept;

		[[nodiscard]]
		constexpr Vector4D wzyx() const noexcept;

		[[nodiscard]]
		static constexpr Vector4D Zero() noexcept;

		[[nodiscard]]
		static constexpr Vector4D One() noexcept;

		[[nodiscard]]
		static constexpr Vector4D All(value_type value = 1) noexcept;

		[[nodiscard]]
		static constexpr Vector4D UnitX() noexcept;

		[[nodiscard]]
		static constexpr Vector4D UnitY() noexcept;

		[[nodiscard]]
		static constexpr Vector4D UnitZ() noexcept;

		[[nodiscard]]
		static constexpr Vector4D UnitW() noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Vector4D& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.z << CharType(',') << CharType(' ')
				<< value.w << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Vector4D& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.z >> unused
				>> value.w >> unused;
		}

		friend void Formatter(FormatData& formatData, const Vector4D& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Vector4D& value);
	};

	using Float4	= Vector4D<float>;
	using Vec4		= Vector4D<double>;
}

template <class Type>
struct SIV3D_HIDDEN fmt::formatter<s3d::Vector4D<Type>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Vector4D<Type>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.x, value.y, value.z, value.w);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.z, value.w);
		}
	}
};

template <class Type>
struct std::hash<s3d::Vector4D<Type>>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Vector4D<Type>& value) const noexcept
	{
		return value.hash();
	}
};
