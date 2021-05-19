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
# include "2DShapesFwd.hpp"

namespace s3d
{
	/// @brief 2 次元のベクトル
	/// @tparam Type ベクトルの要素の型
	template <class Type>
	struct Vector2D
	{
		/// @brief ベクトルの要素の型
		using value_type = Type;

		/// @brief ベクトルの次元数
		static constexpr size_t Dimension = 2;

		/// @brief ベクトルの X 成分
		value_type x;
		
		/// @brief ベクトルの Y 成分
		value_type y;

		SIV3D_NODISCARD_CXX20
		Vector2D() = default;

		SIV3D_NODISCARD_CXX20
		Vector2D(const Vector2D&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(value_type _x, value_type _y) noexcept
			: x{ _x }
			, y{ _y } {}

		template <class X, class Y>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(X _x, Y _y) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(Point p) noexcept;

		template <class U>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(const Vector2D<U>& v) noexcept;

		[[nodiscard]]
		constexpr value_type elem(size_t index) const noexcept;

		[[nodiscard]]
		value_type* getPointer() noexcept;

		[[nodiscard]]
		const value_type* getPointer() const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator +() const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator -() const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator +(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator -(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator *(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator *(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator /(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator /(Vector2D v) const noexcept;

		constexpr Vector2D& operator +=(Vector2D v) noexcept;

		constexpr Vector2D& operator -=(Vector2D v) noexcept;

		constexpr Vector2D& operator *=(value_type s) noexcept;

		constexpr Vector2D& operator *=(Vector2D v) noexcept;

		constexpr Vector2D& operator /=(value_type s) noexcept;

		constexpr Vector2D& operator /=(Vector2D v) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend constexpr Vector2D operator *(Arithmetic s, Vector2D v) noexcept
		{
			return (v * static_cast<Type>(s));
		}

		[[nodiscard]]
		friend constexpr bool operator ==(Vector2D lhs, Vector2D rhs) noexcept
		{
			return (lhs.x == rhs.x)
				&& (lhs.y == rhs.y);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Vector2D lhs, Vector2D rhs) noexcept
		{
			return (lhs.x != rhs.x)
				|| (lhs.y != rhs.y);
		}

		[[nodiscard]]
		constexpr bool epsilonEquals(Vector2D other, value_type epsilon) const noexcept;

		[[nodiscard]]
		constexpr bool hasSameDirection(Vector2D other) const noexcept;

		[[nodiscard]]
		constexpr bool hasOppositeDirection(Vector2D other) const noexcept;

		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		[[nodiscard]]
		bool hasNaN() const noexcept;

		[[nodiscard]]
		constexpr value_type minComponent() const noexcept;

		[[nodiscard]]
		constexpr value_type maxComponent() const noexcept;

		constexpr void clear() noexcept;

		constexpr Vector2D& set(value_type _x, value_type _y) noexcept;

		constexpr Vector2D& set(Vector2D v) noexcept;

		[[nodiscard]]
		constexpr Vector2D movedBy(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr Vector2D movedBy(Vector2D v) const noexcept;

		constexpr Vector2D& moveBy(value_type _x, value_type _y) noexcept;

		constexpr Vector2D& moveBy(Vector2D v) noexcept;

		[[nodiscard]]
		Vector2D clamped(const RectF& rect) const noexcept;

		Vector2D& clamp(const RectF& rect) noexcept;

		[[nodiscard]]
		constexpr value_type dot(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr value_type cross(Vector2D v) const noexcept;

		[[nodiscard]]
		value_type length() const noexcept;

		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		[[nodiscard]]
		value_type invLength() const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanLength() const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(Vector2D v) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(Vector2D v) const noexcept;

		[[nodiscard]]
		Vector2D withLength(value_type _length) const noexcept;

		Vector2D& setLength(value_type _length) noexcept;

		[[nodiscard]]
		Vector2D limitLength(value_type maxLength) const noexcept;

		Vector2D& limitLengthSelf(value_type maxLength) noexcept;

		[[nodiscard]]
		Vector2D normalized() const noexcept;

		Vector2D& normalize() noexcept;

		[[nodiscard]]
		Vector2D rotated(value_type angle) const noexcept;

		Vector2D& rotate(value_type angle) noexcept;

		[[nodiscard]]
		Vector2D rotatedAt(Vector2D center, value_type angle) const noexcept;

		Vector2D& rotateAt(Vector2D center, value_type angle) noexcept;

		[[nodiscard]]
		value_type getAngle() const noexcept;

		[[nodiscard]] 
		value_type getAngle(Vector2D other) const noexcept;

		[[nodiscard]]
		constexpr Vector2D getPerpendicularCW() const noexcept;

		[[nodiscard]]
		constexpr Vector2D getPerpendicularCCW() const noexcept;

		[[nodiscard]]
		constexpr Vector2D getMidpoint(Vector2D other) const noexcept;

		[[nodiscard]]
		constexpr Vector2D projection(Vector2D onto) const noexcept;

		[[nodiscard]]
		Vector2D getPointByAngleAndDistance(value_type angle, value_type distance) const noexcept;

		[[nodiscard]]
		constexpr Vector2D lerp(Vector2D other, value_type f) const noexcept;

		[[nodiscard]]
		constexpr Point asPoint() const noexcept;

		[[nodiscard]]
		Circle asCircle(double r) const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		[[nodiscard]]
		size_t hash() const noexcept;

		/// <summary>
		/// Vector2D{ x, x }
		/// </summary>
		[[nodiscard]]
		constexpr Vector2D xx() const noexcept;

		/// <summary>
		/// Vector2D{ x, y }
		/// </summary>
		[[nodiscard]]
		constexpr Vector2D xy() const noexcept;

		/// <summary>
		/// Vector2D{ y, x }
		/// </summary>
		[[nodiscard]]
		constexpr Vector2D yx() const noexcept;

		/// <summary>
		/// Vector2D{ y, y }
		/// </summary>
		[[nodiscard]]
		constexpr Vector2D yy() const noexcept;

		/// <summary>
		/// Vector2D{ x, 0 }
		/// </summary>
		[[nodiscard]]
		constexpr Vector2D x0() const noexcept;

		/// <summary>
		/// Vector2D{ y, 0 }
		/// </summary>
		[[nodiscard]]
		constexpr Vector2D y0() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<Type> xy0() const noexcept;

		/// <summary>
		/// Vector2D{ 0, 0 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D Zero() noexcept;

		/// <summary>
		/// Vector2D{ 1, 1 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D One() noexcept;

		/// <summary>
		/// Vector2D{ value, value }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D All(value_type value = 1) noexcept;

		/// <summary>
		/// Vector2D{ 1, 0 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D UnitX() noexcept;

		/// <summary>
		/// Vector2D{ 0, 1 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D UnitY() noexcept;

		/// <summary>
		/// Vector2D{ -length, 0 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D Left(value_type length = 1) noexcept;

		/// <summary>
		/// Vector2D{ length, 0 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D Right(value_type length = 1) noexcept;

		/// <summary>
		/// Vector2D{ 0, -length }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D Up(value_type length = 1) noexcept;

		/// <summary>
		/// Vector2D{ 0, length }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D Down(value_type length = 1) noexcept;

		/// <summary>
		/// Vector2D{ 0.5, 0.5 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorCenter() noexcept;

		/// <summary>
		/// Vector2D{ 0, 0 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorTopLeft() noexcept;

		/// <summary>
		/// Vector2D{ 0.5, 0 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorTopCenter() noexcept;

		/// <summary>
		/// Vector2D{ 1, 0 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorTopRight() noexcept;

		/// <summary>
		/// Vector2D{ 1, 0.5 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorRightCenter() noexcept;

		/// <summary>
		/// Vector2D{ 1, 1 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorBottomRight() noexcept;

		/// <summary>
		/// Vector2D{ 0.5, 1 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorBottomCenter() noexcept;

		/// <summary>
		/// Vector2D{ 0, 1 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorBottomLeft() noexcept;

		/// <summary>
		/// Vector2D{ 0, 0.5 }
		/// </summary>
		[[nodiscard]]
		static constexpr Vector2D AnchorLeftCenter() noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Vector2D& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Vector2D& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused;
		}

		friend void Formatter(FormatData& formatData, const Vector2D& value)
		{
			_Formatter(formatData, value);
		}

		static void _Formatter(FormatData& formatData, const Vector2D& value);
	};

	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	using SizeF		= Vec2;
}

template <class Type>
struct SIV3D_HIDDEN fmt::formatter<s3d::Vector2D<Type>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Vector2D<Type>& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {})", value.x, value.y);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.x, value.y);
		}
	}
};

template <class Type>
struct std::hash<s3d::Vector2D<Type>>
{
	[[nodiscard]]
	size_t operator()(const s3d::Vector2D<Type>& value) const noexcept
	{
		return value.hash();
	}
};
