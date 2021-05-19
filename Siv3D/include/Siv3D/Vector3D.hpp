//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
	/// @brief 3 次元のベクトル
	/// @tparam Type ベクトルの要素の型
	template <class Type>
	struct Vector3D
	{
		/// @brief ベクトルの要素の型
		using value_type = Type;

		/// @brief ベクトルの次元数
		static constexpr size_t Dimension = 3;

		/// @brief ベクトルの X 成分
		value_type x;

		/// @brief ベクトルの Y 成分
		value_type y;

		/// @brief ベクトルの Z 成分
		value_type z;

		SIV3D_NODISCARD_CXX20
		Vector3D() = default;

		SIV3D_NODISCARD_CXX20
		Vector3D(const Vector3D&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Vector3D(value_type _x, value_type _y, value_type _z) noexcept;

		template <class X, class Y, class Z>
		SIV3D_NODISCARD_CXX20
		constexpr Vector3D(X _x, Y _y, Z _z) noexcept;

		template <class U>
		SIV3D_NODISCARD_CXX20
		constexpr Vector3D(const Vector3D<U>& v) noexcept;

		template <class Z>
		SIV3D_NODISCARD_CXX20
		constexpr Vector3D(const Vector2D<value_type>& xy, Z _z) noexcept;

		template <class X>
		SIV3D_NODISCARD_CXX20
		constexpr Vector3D(X _x, const Vector2D<value_type>& yz) noexcept;

		[[nodiscard]]
		constexpr value_type elem(size_t index) const noexcept;

		[[nodiscard]]
		value_type* getPointer() noexcept;

		[[nodiscard]]
		const value_type* getPointer() const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator +() const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator -() const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator +(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator -(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator *(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator *(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator /(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector3D operator /(Vector3D v) const noexcept;

		constexpr Vector3D& operator +=(Vector3D v) noexcept;

		constexpr Vector3D& operator -=(Vector3D v) noexcept;

		constexpr Vector3D& operator *=(value_type s) noexcept;

		constexpr Vector3D& operator *=(Vector3D v) noexcept;

		constexpr Vector3D& operator /=(value_type s) noexcept;

		constexpr Vector3D& operator /=(Vector3D v) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend constexpr Vector3D operator *(Arithmetic s, const Vector3D& v) noexcept
		{
			return (v * static_cast<Type>(s));
		}

		[[nodiscard]]
		friend constexpr bool operator ==(const Vector3D& lhs, const Vector3D& rhs) noexcept
		{
			return (lhs.x == rhs.x)
				&& (lhs.y == rhs.y)
				&& (lhs.z == rhs.z);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Vector3D& lhs, const Vector3D& rhs) noexcept
		{
			return (lhs.x != rhs.x)
				|| (lhs.y != rhs.y)
				|| (lhs.z != rhs.z);
		}

		[[nodiscard]]
		constexpr bool epsilonEquals(Vector3D other, value_type epsilon) const noexcept;

		[[nodiscard]]
		constexpr bool hasSameDirection(Vector3D other) const noexcept;

		[[nodiscard]]
		constexpr bool hasOppositeDirection(Vector3D other) const noexcept;

		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		[[nodiscard]]
		bool hasNaN() const noexcept;

		[[nodiscard]]
		constexpr value_type minComponent() const noexcept;

		[[nodiscard]]
		constexpr value_type maxComponent() const noexcept;

		constexpr void clear() noexcept;

		constexpr Vector3D& set(value_type _x, value_type _y, value_type _z) noexcept;

		constexpr Vector3D& set(Vector3D v) noexcept;

		[[nodiscard]]
		constexpr Vector3D movedBy(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		constexpr Vector3D movedBy(Vector3D v) const noexcept;

		constexpr Vector3D& moveBy(value_type _x, value_type _y, value_type _z) noexcept;

		constexpr Vector3D& moveBy(Vector3D v) noexcept;
		
		//[[nodiscard]]
		//Vector3D clamped(const AABB& aabb) const noexcept;

		//Vector3D& clamp(const AABB& aabb) noexcept;

		//[[nodiscard]]
		//Vector3D clamped(const OBB& obb) const noexcept;

		//Vector3D& clamp(const OBB& obb) noexcept;

		[[nodiscard]]
		constexpr value_type dot(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr Vector3D cross(Vector3D v) const noexcept;

		[[nodiscard]]
		value_type length() const noexcept;

		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		[[nodiscard]]
		value_type invLength() const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanLength() const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(Vector3D v) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(Vector3D v) const noexcept;

		[[nodiscard]]
		Vector3D withLength(value_type _length) const noexcept;

		Vector3D& setLength(value_type _length) noexcept;

		[[nodiscard]]
		Vector3D limitLength(value_type maxLength) const noexcept;

		Vector3D& limitLengthSelf(value_type maxLength) noexcept;

		[[nodiscard]]
		Vector3D normalized() const noexcept;

		Vector3D& normalize() noexcept;

		[[nodiscard]]
		constexpr Vector3D getMidpoint(Vector3D other) const noexcept;

		[[nodiscard]]
		constexpr Vector3D lerp(Vector3D other, value_type f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> xx() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> xy() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> xz() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> yx() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> yy() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> yz() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> zx() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> zy() const noexcept;

		[[nodiscard]]
		constexpr Vector2D<value_type> zz() const noexcept;

		[[nodiscard]]
		constexpr Vector3D xxx() const noexcept;

		[[nodiscard]]
		constexpr Vector3D xyz() const noexcept;

		[[nodiscard]]
		constexpr Vector3D xzy() const noexcept;

		[[nodiscard]]
		constexpr Vector3D yyy() const noexcept;

		[[nodiscard]]
		constexpr Vector3D yxz() const noexcept;

		[[nodiscard]]
		constexpr Vector3D yzx() const noexcept;

		[[nodiscard]]
		constexpr Vector3D zzz() const noexcept;

		[[nodiscard]]
		constexpr Vector3D zxy() const noexcept;

		[[nodiscard]]
		constexpr Vector3D zyx() const noexcept;

		[[nodiscard]]
		constexpr Vector4D<Type> xyz0() const noexcept;

		[[nodiscard]]
		static constexpr Vector3D Zero() noexcept;

		[[nodiscard]]
		static constexpr Vector3D One() noexcept;

		[[nodiscard]]
		static constexpr Vector3D All(value_type value = 1) noexcept;

		[[nodiscard]]
		static constexpr Vector3D UnitX() noexcept;

		[[nodiscard]]
		static constexpr Vector3D UnitY() noexcept;

		[[nodiscard]]
		static constexpr Vector3D UnitZ() noexcept;

		[[nodiscard]]
		static constexpr Vector3D Left(value_type length = 1) noexcept;

		[[nodiscard]]
		static constexpr Vector3D Right(value_type length = 1) noexcept;

		[[nodiscard]]
		static constexpr Vector3D Up(value_type length = 1) noexcept;

		[[nodiscard]]
		static constexpr Vector3D Down(value_type length = 1) noexcept;

		[[nodiscard]]
		static constexpr Vector3D Forward(value_type length = 1) noexcept;

		[[nodiscard]]
		static constexpr Vector3D Backward(value_type length = 1) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Vector3D& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.z << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Vector3D& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.z >> unused;
		}

		friend void Formatter(FormatData& formatData, const Vector3D& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Vector3D& value);
	};

	using Float3	= Vector3D<float>;
	using Vec3		= Vector3D<double>;
}

template <class Type>
struct SIV3D_HIDDEN fmt::formatter<s3d::Vector3D<Type>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Vector3D<Type>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {})", value.x, value.y, value.z);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y, value.z);
		}
	}
};

template <class Type>
struct std::hash<s3d::Vector3D<Type>>
{
	[[nodiscard]]
	size_t operator()(const s3d::Vector3D<Type>& value) const noexcept
	{
		return value.hash();
	}
};
