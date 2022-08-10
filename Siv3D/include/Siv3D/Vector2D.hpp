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

		constexpr Vector2D& operator =(const Vector2D&) = default;

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

		/// @brief 指定した別のベクトルとの各成分の差の絶対値が epsilon 以下であるかを返します。
		/// @param other 別のベクトル
		/// @param epsilon 差の絶対値の許容量
		/// @return 別のベクトルとの各成分の差の絶対値が epsilon 以下である場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool epsilonEquals(Vector2D other, value_type epsilon) const noexcept;

		/// @brief 指定した別のベクトルとのなす角が 180 ° 未満であるかを返します。
		/// @param other 別のベクトル
		/// @return 別のベクトルとのなす角が 180 ° 未満である場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool hasSameDirection(Vector2D other) const noexcept;

		/// @brief 指定した別のベクトルとのなす角が 180 ° より大きいかを返します。
		/// @param other 別のベクトル
		/// @return 別のベクトルとのなす角が 180 ° より大きい場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool hasOppositeDirection(Vector2D other) const noexcept;

		/// @brief ゼロベクトルであるかを返します。
		/// @return ゼロベクトルである場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		/// @brief NaN である成分を持つかを返します。
		/// @return NaN である成分を持つ場合 true, それ以外の場合は false
		[[nodiscard]]
		bool hasNaN() const noexcept;

		/// @brief 最小の成分を返します。
		/// @return 最小の成分
		[[nodiscard]]
		constexpr value_type minComponent() const noexcept;

		/// @brief 最大の成分を返します。
		/// @return 最大の成分
		[[nodiscard]]
		constexpr value_type maxComponent() const noexcept;

		/// @brief 各成分を 0 にセットします。
		constexpr void clear() noexcept;

		/// @brief 各成分を変更します。
		/// @param _x 新しい X 成分
		/// @param _y 新しい Y 成分
		/// @return *this
		constexpr Vector2D& set(value_type _x, value_type _y) noexcept;

		/// @brief ベクトルを変更します。
		/// @param v 新しいベクトル
		/// @return *this
		constexpr Vector2D& set(Vector2D v) noexcept;

		/// @brief 位置ベクトルを移動させた新しいベクトルを返します。
		/// @param _x X 成分の移動量
		/// @param _y Y 成分の移動量
		/// @return 移動後の新しいベクトル
		[[nodiscard]]
		constexpr Vector2D movedBy(value_type _x, value_type _y) const noexcept;

		/// @brief 位置ベクトルを移動させた新しいベクトルを返します。
		/// @param v 移動量
		/// @return 移動後の新しいベクトル
		[[nodiscard]]
		constexpr Vector2D movedBy(Vector2D v) const noexcept;

		/// @brief 位置ベクトルを移動させます。
		/// @param _x X 成分の移動量
		/// @param _y Y 成分の移動量
		/// @return *this
		constexpr Vector2D& moveBy(value_type _x, value_type _y) noexcept;

		/// @brief 位置ベクトルを移動させます。
		/// @param v 移動量
		/// @return *this
		constexpr Vector2D& moveBy(Vector2D v) noexcept;

		[[nodiscard]]
		Vector2D clamped(const RectF& rect) const noexcept;

		Vector2D& clamp(const RectF& rect) noexcept;

		[[nodiscard]]
		constexpr value_type dot(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr value_type cross(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr value_type horizontalAspectRatio() const noexcept;

		/// @brief ベクトルの大きさ（長さ）を返します。
		/// @return ベクトルの大きさ（長さ）
		[[nodiscard]]
		value_type length() const noexcept;

		/// @brief ベクトルの大きさ（長さ）の二乗を返します。
		/// @remark 平方根を計算しないため `length()` より高速です。
		/// @return ベクトルの大きさ（長さ）の二乗
		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		/// @brief ベクトルの長さの逆数 (1 / length())を返します。
		/// @return ベクトルの長さの逆数
		[[nodiscard]]
		value_type invLength() const noexcept;

		/// @brief 原点からこの位置ベクトルまでのマンハッタン距離を返します。
		/// @return 原点からのマンハッタン距離
		[[nodiscard]]
		constexpr value_type manhattanLength() const noexcept;

		/// @brief 別の位置ベクトルからのマンハッタン距離を返します。
		/// @param _x 別の位置ベクトルの X 成分
		/// @param _y 別の位置ベクトルの Y 成分
		/// @return 別の位置ベクトルからのマンハッタン距離
		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(value_type _x, value_type _y) const noexcept;

		/// @brief 別の位置ベクトルからのマンハッタン距離を返します。
		/// @param v 別の位置ベクトル
		/// @return 別の位置ベクトルからのマンハッタン距離
		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(Vector2D v) const noexcept;

		/// @brief 別の位置ベクトルからの距離を返します。
		/// @param _x 別の位置ベクトルの X 成分
		/// @param _y 別の位置ベクトルの Y 成分
		/// @return 別の位置ベクトルからの距離
		[[nodiscard]]
		value_type distanceFrom(value_type _x, value_type _y) const noexcept;

		/// @brief 別の位置ベクトルからの距離を返します。
		/// @param v 別の位置ベクトル
		/// @return 別の位置ベクトルからの距離
		[[nodiscard]]
		value_type distanceFrom(Vector2D v) const noexcept;

		/// @brief 別の位置ベクトルからの距離の二乗を返します。
		/// @param _x 別の位置ベクトルの X 成分
		/// @param _y 別の位置ベクトルの Y 成分
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の位置ベクトルからの距離の二乗
		[[nodiscard]]
		constexpr value_type distanceFromSq(value_type _x, value_type _y) const noexcept;

		/// @brief 別の位置ベクトルからの距離の二乗を返します。
		/// @param v 別の位置ベクトル
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の位置ベクトルからの距離の二乗
		[[nodiscard]]
		constexpr value_type distanceFromSq(Vector2D v) const noexcept;

		/// @brief 向きが同じで大きさ（長さ）を変更した新しいベクトルを返します。
		/// @param _length ベクトルの大きさ（長さ）
		/// @return 新しいベクトル。自身がゼロベクトルの場合はゼロベクトル
		[[nodiscard]]
		Vector2D withLength(value_type _length) const noexcept;

		/// @brief ベクトルの向きはそのままで、大きさ（長さ）だけを変更します。
		/// @param _length ベクトルの大きさ（長さ）
		/// @remark 自身がゼロベクトルの場合は何もしません。
		/// @return *this
		Vector2D& setLength(value_type _length) noexcept;

		/// @brief 向きが同じで大きさ（長さ）を一定の値以下にした新しいベクトルを返します。
		/// @param maxLength ベクトルの最大の大きさ（長さ）
		/// @return 大きさ（長さ）を一定の値以下にした新しいベクトル
		[[nodiscard]]
		Vector2D limitLength(value_type maxLength) const noexcept;

		/// @brief ベクトルの向きはそのままで、大きさ（長さ）を一定の値以下にします
		/// @param maxLength ベクトルの最大の大きさ（長さ）
		/// @return *this
		Vector2D& limitLengthSelf(value_type maxLength) noexcept;

		/// @brief 正規化した（大きさを 1 にした）ベクトルを返します。
		/// @return 正規化した（大きさを 1 にした）ベクトル
		[[nodiscard]]
		Vector2D normalized() const noexcept;

		/// @brief 自身を正規化（大きさを 1 に）します。
		/// @return *this
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

		/// @brief Vec2 を Point 型に変換します。小数点数以下は切り捨てられます。
		/// @return Point
		[[nodiscard]]
		constexpr Point asPoint() const noexcept;

		/// @brief 点を中心とした円を作成します。
		/// @param r 円の半径
		/// @return 円
		[[nodiscard]]
		Circle asCircle(double r) const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		[[nodiscard]]
		size_t hash() const noexcept;

		/// @brief Vector2D{ x, x } を返します。
		/// @return Vector2D{ x, x }
		[[nodiscard]]
		constexpr Vector2D xx() const noexcept;

		/// @brief Vector2D{ x, y } を返します。
		/// @return Vector2D{ x, y }
		[[nodiscard]]
		constexpr Vector2D xy() const noexcept;

		/// @brief Vector2D{ y, x } を返します。
		/// @return Vector2D{ y, x }
		[[nodiscard]]
		constexpr Vector2D yx() const noexcept;

		/// @brief Vector2D{ y, y } を返します。
		/// @return Vector2D{ y, y }
		[[nodiscard]]
		constexpr Vector2D yy() const noexcept;

		/// @brief Vector2D{ x, 0 } を返します。
		/// @return Vector2D{ x, 0 }
		[[nodiscard]]
		constexpr Vector2D x0() const noexcept;

		/// @brief Vector2D{ y, 0 } を返します。
		/// @return Vector2D{ y, 0 }
		[[nodiscard]]
		constexpr Vector2D y0() const noexcept;

		[[nodiscard]]
		constexpr Vector3D<Type> xy0() const noexcept;

		/// @brief Vector2D{ 0, 0 } を返します。
		/// @return Vector2D{ 0, 0 }
		[[nodiscard]]
		static constexpr Vector2D Zero() noexcept;

		/// @brief Vector2D{ 1, 1 } を返します。
		/// @return Vector2D{ 1, 1 }
		[[nodiscard]]
		static constexpr Vector2D One() noexcept;

		/// @brief Vector2D{ value, value } を返します。
		/// @param value 値
		/// @return Vector2D{ value, value }
		[[nodiscard]]
		static constexpr Vector2D All(value_type value = 1) noexcept;

		/// @brief Vector2D{ 1, 0 } を返します。
		/// @return Vector2D{ 1, 0 }
		[[nodiscard]]
		static constexpr Vector2D UnitX() noexcept;

		/// @brief Vector2D{ 0, 1 } を返します。
		/// @return Vector2D{ 0, 1 }
		[[nodiscard]]
		static constexpr Vector2D UnitY() noexcept;

		/// @brief Vector2D{ -length, 0 } を返します。
		/// @param length 値
		/// @return Vector2D{ -length, 0 }
		[[nodiscard]]
		static constexpr Vector2D Left(value_type length = 1) noexcept;

		/// @brief Vector2D{ length, 0 } を返します。
		/// @param length 値
		/// @return Vector2D{ length, 0 }
		[[nodiscard]]
		static constexpr Vector2D Right(value_type length = 1) noexcept;

		/// @brief Vector2D{ 0, -length } を返します。
		/// @param length 値
		/// @return Vector2D{ 0, -length }
		[[nodiscard]]
		static constexpr Vector2D Up(value_type length = 1) noexcept;

		/// @brief Vector2D{ 0, length } を返します。
		/// @return Vector2D{ 0, length }
		[[nodiscard]]
		static constexpr Vector2D Down(value_type length = 1) noexcept;

		/// @brief Vector2D{ 0.5, 0.5 } を返します。
		/// @return Vector2D{ 0.5, 0.5 }
		[[nodiscard]]
		static constexpr Vector2D AnchorCenter() noexcept;

		/// @brief Vector2D{ 0, 0 } を返します。
		/// @return Vector2D{ 0, 0 }
		[[nodiscard]]
		static constexpr Vector2D AnchorTopLeft() noexcept;

		/// @brief Vector2D{ 0.5, 0 } を返します。
		/// @return Vector2D{ 0.5, 0 }
		[[nodiscard]]
		static constexpr Vector2D AnchorTopCenter() noexcept;

		/// @brief Vector2D{ 1, 0 } を返します。
		/// @return Vector2D{ 1, 0 }
		[[nodiscard]]
		static constexpr Vector2D AnchorTopRight() noexcept;

		/// @brief Vector2D{ 1, 0.5 } を返します。
		/// @return Vector2D{ 1, 0.5 }
		[[nodiscard]]
		static constexpr Vector2D AnchorRightCenter() noexcept;

		/// @brief Vector2D{ 1, 1 } を返します。
		/// @return Vector2D{ 1, 1 }
		[[nodiscard]]
		static constexpr Vector2D AnchorBottomRight() noexcept;

		/// @brief Vector2D{ 0.5, 1 } を返します。
		/// @return Vector2D{ 0.5, 1 }
		[[nodiscard]]
		static constexpr Vector2D AnchorBottomCenter() noexcept;

		/// @brief Vector2D{ 0, 1 } を返します。
		/// @return Vector2D{ 0, 1 }
		[[nodiscard]]
		static constexpr Vector2D AnchorBottomLeft() noexcept;

		/// @brief Vector2D{ 0, 0.5 } を返します。
		/// @return Vector2D{ 0, 0.5 }
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
	size_t operator ()(const s3d::Vector2D<Type>& value) const noexcept
	{
		return value.hash();
	}
};
