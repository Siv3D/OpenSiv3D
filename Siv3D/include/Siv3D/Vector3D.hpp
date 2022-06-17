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
	struct Box;

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

		constexpr Vector3D& operator =(const Vector3D&) = default;

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
		/// @param _z 新しい Z 成分
		/// @return *this
		constexpr Vector3D& set(value_type _x, value_type _y, value_type _z) noexcept;

		/// @brief ベクトルを変更します。
		/// @param v 新しいベクトル
		/// @return *this
		constexpr Vector3D& set(Vector3D v) noexcept;

		[[nodiscard]]
		constexpr Vector3D movedBy(value_type _x, value_type _y, value_type _z) const noexcept;

		[[nodiscard]]
		constexpr Vector3D movedBy(Vector3D v) const noexcept;

		constexpr Vector3D& moveBy(value_type _x, value_type _y, value_type _z) noexcept;

		constexpr Vector3D& moveBy(Vector3D v) noexcept;
		
		[[nodiscard]]
		Vector3D clamped(const Box& box) const noexcept;

		Vector3D& clamp(const Box& box) noexcept;

		[[nodiscard]]
		constexpr value_type dot(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr Vector3D cross(Vector3D v) const noexcept;

		[[nodiscard]]
		value_type angleTo(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr Vector3D projectOnVector(Vector3D v) const noexcept;

		[[nodiscard]]
		constexpr Vector3D projectOnPlane(Vector3D planeNormal) const noexcept;

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

		/// @brief 原点からこの位置ベクトルまでの 3 次元マンハッタン距離を返します。
		/// @return 原点からの 3 次元マンハッタン距離
		[[nodiscard]]
		constexpr value_type manhattanLength() const noexcept;

		/// @brief 別の位置ベクトルからの 3 次元マンハッタン距離を返します。
		/// @param _x 別の位置ベクトルの X 成分
		/// @param _y 別の位置ベクトルの Y 成分
		/// @param _z 別の位置ベクトルの Z 成分
		/// @return 別の位置ベクトルからの 3 次元マンハッタン距離
		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(value_type _x, value_type _y, value_type _z) const noexcept;

		/// @brief 別の位置ベクトルからの 3 次元マンハッタン距離を返します。
		/// @param v 別の位置ベクトル
		/// @return 別の位置ベクトルからの 3 次元マンハッタン距離
		[[nodiscard]]
		constexpr value_type manhattanDistanceFrom(Vector3D v) const noexcept;

		/// @brief 別の位置ベクトルからの距離を返します。
		/// @param _x 別の位置ベクトルの X 成分
		/// @param _y 別の位置ベクトルの Y 成分
		/// @param _z 別の位置ベクトルの Z 成分
		/// @return 別の位置ベクトルからの距離
		[[nodiscard]]
		value_type distanceFrom(value_type _x, value_type _y, value_type _z) const noexcept;

		/// @brief 別の位置ベクトルからの距離を返します。
		/// @param v 別の位置ベクトル
		/// @return 別の位置ベクトルからの距離
		[[nodiscard]]
		value_type distanceFrom(Vector3D v) const noexcept;

		/// @brief 別の位置ベクトルからの距離の二乗を返します。
		/// @param _x 別の位置ベクトルの X 成分
		/// @param _y 別の位置ベクトルの Y 成分
		/// @param _z 別の位置ベクトルの Z 成分
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の位置ベクトルからの距離の二乗
		[[nodiscard]]
		constexpr value_type distanceFromSq(value_type _x, value_type _y, value_type _z) const noexcept;

		/// @brief 別の位置ベクトルからの距離の二乗を返します。
		/// @param v 別の位置ベクトル
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の位置ベクトルからの距離の二乗
		[[nodiscard]]
		constexpr value_type distanceFromSq(Vector3D v) const noexcept;

		/// @brief 向きが同じで大きさ（長さ）を変更した新しいベクトルを返します。
		/// @param _length ベクトルの大きさ（長さ）
		/// @return 新しいベクトル。自身がゼロベクトルの場合はゼロベクトル
		[[nodiscard]]
		Vector3D withLength(value_type _length) const noexcept;

		/// @brief ベクトルの向きはそのままで、大きさ（長さ）だけを変更します。
		/// @param _length ベクトルの大きさ（長さ）
		/// @remark 自身がゼロベクトルの場合は何もしません。
		/// @return *this
		Vector3D& setLength(value_type _length) noexcept;

		/// @brief 向きが同じで大きさ（長さ）を一定の値以下にした新しいベクトルを返します。
		/// @param maxLength ベクトルの最大の大きさ（長さ）
		/// @return 大きさ（長さ）を一定の値以下にした新しいベクトル
		[[nodiscard]]
		Vector3D limitLength(value_type maxLength) const noexcept;

		/// @brief ベクトルの向きはそのままで、大きさ（長さ）を一定の値以下にします
		/// @param maxLength ベクトルの最大の大きさ（長さ）
		/// @return *this
		Vector3D& limitLengthSelf(value_type maxLength) noexcept;

		/// @brief 正規化した（大きさを 1 にした）ベクトルを返します。
		/// @return 正規化した（大きさを 1 にした）ベクトル
		[[nodiscard]]
		Vector3D normalized() const noexcept;

		/// @brief 自身を正規化（大きさを 1 に）します。
		/// @return *this
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
		constexpr Vector4D<Type> xyz1() const noexcept;

		/// @brief Vector3D{ 0, 0, 0 } を返します。
		/// @return Vector3D{ 0, 0, 0 }
		[[nodiscard]]
		static constexpr Vector3D Zero() noexcept;

		/// @brief Vector3D{ 1, 1, 1 } を返します。
		/// @return Vector3D{ 1, 1, 1 }
		[[nodiscard]]
		static constexpr Vector3D One() noexcept;

		/// @brief Vector3D{ value, value, value } を返します。
		/// @return Vector3D{ value, value, value }
		[[nodiscard]]
		static constexpr Vector3D All(value_type value = 1) noexcept;

		/// @brief Vector3D{ 1, 0, 0 } を返します。
		/// @return Vector3D{ 1, 0, 0 }
		[[nodiscard]]
		static constexpr Vector3D UnitX() noexcept;

		/// @brief Vector3D{ 0, 1, 0 } を返します。
		/// @return Vector3D{ 0, 1, 0 }
		[[nodiscard]]
		static constexpr Vector3D UnitY() noexcept;

		/// @brief Vector3D{ 0, 0, 1 } を返します。
		/// @return Vector3D{ 0, 0, 1 }
		[[nodiscard]]
		static constexpr Vector3D UnitZ() noexcept;

		/// @brief Vector3D{ -length, 0, 0 } を返します。
		/// @return Vector3D{ -length, 0, 0 }
		[[nodiscard]]
		static constexpr Vector3D Left(value_type length = 1) noexcept;

		/// @brief Vector3D{ length, 0, 0 } を返します。
		/// @return Vector3D{ length, 0, 0 }
		[[nodiscard]]
		static constexpr Vector3D Right(value_type length = 1) noexcept;

		/// @brief Vector3D{ 0, length, 0 } を返します。
		/// @return Vector3D{ 0, length, 0 }
		[[nodiscard]]
		static constexpr Vector3D Up(value_type length = 1) noexcept;

		/// @brief Vector3D{ 0, -length, 0 } を返します。
		/// @return Vector3D{ 0, -length, 0 }
		[[nodiscard]]
		static constexpr Vector3D Down(value_type length = 1) noexcept;

		/// @brief Vector3D{ 0, 0, length } を返します。
		/// @return Vector3D{ 0, 0, length }
		[[nodiscard]]
		static constexpr Vector3D Forward(value_type length = 1) noexcept;

		/// @brief Vector3D{ 0, 0, -length } を返します。
		/// @return Vector3D{ 0, 0, -length }
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
	size_t operator ()(const s3d::Vector3D<Type>& value) const noexcept
	{
		return value.hash();
	}
};
