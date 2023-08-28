//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	template <class Type> struct Vector3D;
	using Float3 = Vector3D<float>;
	using Vec3 = Vector3D<double>;
	struct FormatData;

	/// @brief 3 次元のベクトル（整数）
	struct Point3D
	{
		/// @brief ベクトルの要素の型
		using value_type = int32;

		/// @brief ベクトルの次元数
		static constexpr size_t Dimension = 3;

		/// @brief ベクトルの X 成分
		value_type x;

		/// @brief ベクトルの Y 成分
		value_type y;

		/// @brief ベクトルの Z 成分
		value_type z;

		SIV3D_NODISCARD_CXX20
		Point3D() = default;

		SIV3D_NODISCARD_CXX20
		Point3D(const Point3D&) = default;

	# if __cpp_lib_concepts
		template <Concept::Integral IntegerX, Concept::Integral IntegerY, Concept::Integral IntegerZ>
	# else
		template <class IntegerX, class IntegerY, class IntegerZ, std::enable_if_t<std::conjunction_v<std::is_integral<IntegerX>, std::is_integral<IntegerY>, std::is_integral<IntegerZ>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Point3D(IntegerX _x, IntegerY _y, IntegerZ _z) noexcept;

		template <class X, class Y, class Z, std::enable_if_t<(not std::is_integral_v<X>) || (not std::is_integral_v<Y>) || (not std::is_integral_v<Z>)>* = nullptr>
		constexpr Point3D(X _x, Y _y, Z _z) noexcept = delete;

		[[nodiscard]]
		constexpr value_type elem(size_t index) const noexcept;

		[[nodiscard]]
		value_type* getPointer() noexcept;

		[[nodiscard]]
		const value_type* getPointer() const noexcept;

		constexpr Point3D& operator =(const Point3D&) = default;

		[[nodiscard]]
		constexpr Point3D operator +() const noexcept;

		[[nodiscard]]
		constexpr Point3D operator -() const noexcept;

		[[nodiscard]]
		constexpr Point3D operator +(Point3D p) const noexcept;

		[[nodiscard]]
		constexpr Point3D operator -(Point3D p) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector3D<Type> operator +(Vector3D<Type> v) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector3D<Type> operator -(Vector3D<Type> v) const noexcept;

		[[nodiscard]]
		constexpr Point3D operator *(int32 s) const noexcept;

		[[nodiscard]]
		constexpr Float3 operator *(float s) const noexcept;

		[[nodiscard]]
		constexpr Vec3 operator *(double s) const noexcept;

		[[nodiscard]]
		constexpr Point3D operator *(Point3D p) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector3D<Type> operator *(Vector3D<Type> v) const noexcept;

		[[nodiscard]]
		friend constexpr Point3D operator *(int32 s, Point3D p) noexcept
		{
			return{ (s * p.x), (s * p.y), (s * p.z) };
		}

		[[nodiscard]]
		friend constexpr Vector3D<float> operator *(float s, Point3D p) noexcept
		{
			return{ (s * p.x), (s * p.y), (s * p.z) };
		}

		[[nodiscard]]
		friend constexpr Vector3D<double> operator *(double s, Point3D p) noexcept
		{
			return{ (s * p.x), (s * p.y), (s * p.z) };
		}

		[[nodiscard]]
		constexpr Point3D operator /(int32 s) const noexcept;

		[[nodiscard]]
		constexpr Float3 operator /(float s) const noexcept;

		[[nodiscard]]
		constexpr Vec3 operator /(double s) const noexcept;

		[[nodiscard]]
		constexpr Point3D operator /(Point3D p) const noexcept;

		[[nodiscard]]
		constexpr Point3D operator %(int32 s) const noexcept;

		[[nodiscard]]
		constexpr Point3D operator %(Point3D p) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector3D<Type> operator /(Vector3D<Type> v) const noexcept;

		constexpr Point3D& operator +=(Point3D p) noexcept;

		constexpr Point3D& operator -=(Point3D p) noexcept;

		constexpr Point3D& operator *=(int32 s) noexcept;

		constexpr Point3D& operator /=(int32 s) noexcept;

		constexpr Point3D& operator %=(int32 s) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(Point3D lhs, Point3D rhs) noexcept
		{
			return (lhs.x == rhs.x)
				&& (lhs.y == rhs.y)
				&& (lhs.z == rhs.z);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Point3D lhs, Point3D rhs) noexcept
		{
			return (lhs.x != rhs.x)
				|| (lhs.y != rhs.y)
				|| (lhs.z != rhs.z);
		}

		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		[[nodiscard]]
		constexpr value_type minComponent() const noexcept;

		[[nodiscard]]
		constexpr value_type maxComponent() const noexcept;

		constexpr void clear() noexcept;

		constexpr Point3D& set(int32 _x, int32 _y, int32 _z) noexcept;

		constexpr Point3D& set(Point3D p) noexcept;

		[[nodiscard]]
		constexpr Point3D movedBy(int32 _x, int32 _y, int32 _z) const noexcept;

		[[nodiscard]]
		constexpr Point3D movedBy(Point3D p) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector3D<Type> movedBy(Vector3D<Type> v) const noexcept;

		constexpr Point3D& moveBy(int32 _x, int32 _y, int32 _z) noexcept;

		constexpr Point3D& moveBy(Point3D p) noexcept;

		/// @brief ベクトルの大きさ（長さ）を返します。
		/// @tparam Type 結果の型
		/// @return ベクトルの大きさ（長さ）
		template <class Type = double>
		[[nodiscard]]
		Type length() const noexcept;

		/// @brief ベクトルの大きさ（長さ）の二乗を返します。
		/// @tparam Type 結果の型
		/// @remark 平方根を計算しないため `length()` より高速です。
		/// @return ベクトルの大きさ（長さ）の二乗
		template <class Type = double>
		[[nodiscard]]
		constexpr Type lengthSq() const noexcept;

		/// @brief 原点からこの座標までのマンハッタン距離を返します。
		/// @return 原点からのマンハッタン距離
		[[nodiscard]]
		constexpr int32 manhattanLength() const noexcept;

		/// @brief 別の位置ベクトルからのマンハッタン距離を返します。
		/// @param _x 別の座標の X 成分
		/// @param _y 別の座標の Y 成分
		/// @param _z 別の座標の Z 成分
		/// @return 別の座標からのマンハッタン距離
		[[nodiscard]]
		constexpr int32 manhattanDistanceFrom(int32 _x, int32 _y, int32 _z) const noexcept;

		/// @brief 別の座標からのマンハッタン距離を返します。
		/// @param p 別の座標
		/// @return 別の座標からのマンハッタン距離
		[[nodiscard]]
		constexpr int32 manhattanDistanceFrom(Point3D p) const noexcept;

		/// @brief 別の座標からの距離を返します。
		/// @param _x 別の座標の X 成分
		/// @param _y 別の座標の Y 成分
		/// @param _z 別の座標の Z 成分
		/// @return 別の座標からの距離
		[[nodiscard]]
		double distanceFrom(double _x, double _y, double _z) const noexcept;

		/// @brief 別の座標からの距離を返します。
		/// @param p 別の座標
		/// @return 別の座標からの距離
		[[nodiscard]]
		double distanceFrom(Point3D p) const noexcept;

		/// @brief 別の座標からの距離を返します。
		/// @tparam Type 別の座標の成分の型
		/// @param p 別の座標
		/// @return 別の座標からの距離
		template <class Type>
		[[nodiscard]]
		double distanceFrom(Vector3D<Type> p) const noexcept;

		/// @brief 別の座標からの距離の二乗を返します。
		/// @param _x 別の座標の X 成分
		/// @param _y 別の座標の Y 成分
		/// @param _z 別の座標の Z 成分
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の座標からの距離の二乗
		[[nodiscard]]
		constexpr double distanceFromSq(double _x, double _y, double _z) const noexcept;

		/// @brief 別の座標からの距離の二乗を返します。
		/// @param p 別の座標
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の座標からの距離の二乗
		[[nodiscard]]
		constexpr double distanceFromSq(Point3D p) const noexcept;

		/// @brief 別の座標からの距離の二乗を返します。
		/// @tparam Type 別の座標の成分の型
		/// @param p 別の座標
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の座標からの距離の二乗
		template <class Type>
		[[nodiscard]]
		constexpr double distanceFromSq(Vector3D<Type> p) const noexcept;

		template <class Type = double>
		[[nodiscard]]
		constexpr Vector3D<Type> getMidpoint(Point3D other) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector3D<Type> getMidpoint(Vector3D<Type> other) const noexcept;

		template <class Type = double>
		[[nodiscard]]
		constexpr Vector3D<Type> lerp(Point3D other, double f) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector3D<Type> lerp(Vector3D<Type> other, double f) const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

		/// @brief Point3D{ 0, 0, 0 } を返します。
		/// @return Point3D{ 0, 0, 0 }
		[[nodiscard]]
		static constexpr Point3D Zero() noexcept;

		/// @brief Point{ 1, 1, 1 } を返します。
		/// @return Point{ 1, 1, 1 }
		[[nodiscard]]
		static constexpr Point3D One() noexcept;

		/// @brief Point3D{ value, value, value } を返します。
		/// @param value 値
		/// @return Point3D{ value, value, value }
		[[nodiscard]]
		static constexpr Point3D All(value_type value = 1) noexcept;

		/// @brief Point3D{ 1, 0, 0 } を返します。
		/// @return Point3D{ 1, 0, 0 }
		[[nodiscard]]
		static constexpr Point3D UnitX() noexcept;

		/// @brief Point3D{ 0, 1, 0 } を返します。
		/// @return Point3D{ 0, 1, 0 }
		[[nodiscard]]
		static constexpr Point3D UnitY() noexcept;

		/// @brief Point3D{ 0, 0, 1 } を返します。
		/// @return Point3D{ 0, 0, 1 }
		[[nodiscard]]
		static constexpr Point3D UnitZ() noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Point3D& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(',') << CharType(' ')
				<< value.z << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Point3D& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused
				>> value.z >> unused;
		}

		friend void Formatter(FormatData& formatData, const Point3D& value);
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Point3D, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Point3D& value, FormatContext& ctx)
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

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::Point3D>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Point3D& value) const noexcept
	{
		return value.hash();
	}
};
