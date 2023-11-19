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
# include "FormatLiteral.hpp"
# include "CommonFloat.hpp"
# include "Hash.hpp"
# include "MathConstants.hpp"
# include "2DShapesFwd.hpp"

namespace s3d
{
	template <class Type> struct Vector2D;
	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	struct Circle;
	struct Color;
	class Image;
	struct FormatData;

	/// @brief 2 次元のベクトル（整数）
	struct Point
	{
		/// @brief ベクトルの要素の型
		using value_type = int32;

		/// @brief ベクトルの次元数
		static constexpr size_t Dimension = 2;

		/// @brief ベクトルの X 成分
		value_type x;
		
		/// @brief ベクトルの Y 成分
		value_type y;

		SIV3D_NODISCARD_CXX20
		Point() = default;

		SIV3D_NODISCARD_CXX20
		Point(const Point&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Point(value_type _x, value_type _y) noexcept;

	# if __cpp_lib_concepts
		template <Concept::Integral IntegerX, Concept::Integral IntegerY>
	# else
		template <class IntegerX, class IntegerY, std::enable_if_t<std::conjunction_v<std::is_integral<IntegerX>, std::is_integral<IntegerY>>>* = nullptr>
	# endif
		SIV3D_NODISCARD_CXX20
		constexpr Point(IntegerX _x, IntegerY _y) noexcept;

		template <class X, class Y, std::enable_if_t<(not std::is_integral_v<X>) || (not std::is_integral_v<Y>)>* = nullptr>
		constexpr Point(X _x, Y _y) noexcept = delete;

		[[nodiscard]]
		constexpr value_type elem(size_t index) const noexcept;

		/// @brief x 成分へのポインタを返します。
		/// @rematk 戻り値に対して [0] で x 成分、[1] で y 成分にアクセスできます。
		/// @return x 成分へのポインタ
		[[nodiscard]]
		value_type* getPointer() noexcept;

		/// @brief x 成分へのポインタを返します。
		/// @rematk 戻り値に対して [0] で x 成分、[1] で y 成分にアクセスできます。
		/// @return x 成分へのポインタ
		[[nodiscard]]
		const value_type* getPointer() const noexcept;

		constexpr Point& operator =(const Point&) = default;

		[[nodiscard]]
		constexpr Point operator +() const noexcept;

		[[nodiscard]]
		constexpr Point operator -() const noexcept;

		[[nodiscard]]
		constexpr Point operator +(Point p) const noexcept;

		[[nodiscard]]
		constexpr Point operator -(Point p) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector2D<Type> operator +(Vector2D<Type> v) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector2D<Type> operator -(Vector2D<Type> v) const noexcept;

		[[nodiscard]]
		constexpr Point operator *(int32 s) const noexcept;

		[[nodiscard]]
		constexpr Float2 operator *(float s) const noexcept;

		[[nodiscard]]
		constexpr Vec2 operator *(double s) const noexcept;

		[[nodiscard]]
		constexpr Point operator *(Point p) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector2D<Type> operator *(Vector2D<Type> v) const noexcept;

		[[nodiscard]]
		friend constexpr Point operator *(int32 s, Point p) noexcept
		{
			return{ s * p.x, s * p.y };
		}

		[[nodiscard]]
		friend constexpr Vector2D<float> operator *(float s, Point p) noexcept
		{
			return{ s * p.x, s * p.y };
		}

		[[nodiscard]]
		friend constexpr Vector2D<double> operator *(double s, Point p) noexcept
		{
			return{ s * p.x, s * p.y };
		}

		[[nodiscard]]
		constexpr Point operator /(int32 s) const noexcept;

		[[nodiscard]]
		constexpr Float2 operator /(float s) const noexcept;

		[[nodiscard]]
		constexpr Vec2 operator /(double s) const noexcept;

		[[nodiscard]]
		constexpr Point operator /(Point p) const noexcept;

		[[nodiscard]]
		constexpr Point operator %(int32 s) const noexcept;

		[[nodiscard]]
		constexpr Point operator %(Point p) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector2D<Type> operator /(Vector2D<Type> v) const noexcept;

		constexpr Point& operator +=(Point p) noexcept;

		constexpr Point& operator -=(Point p) noexcept;

		constexpr Point& operator *=(int32 s) noexcept;

		constexpr Point& operator /=(int32 s) noexcept;

		constexpr Point& operator %=(int32 s) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(Point lhs, Point rhs) noexcept
		{
			return (lhs.x == rhs.x)
				&& (lhs.y == rhs.y);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Point lhs, Point rhs) noexcept
		{
			return (lhs.x != rhs.x)
				|| (lhs.y != rhs.y);
		}

		/// @brief すべての成分が 0 であるかを返します。
		/// @return　すべての成分が 0 である場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		/// @brief 最大の成分を返します。
		/// @remark Point{ 3, 2 } の場合、3 を返します。
		/// @return 最大の成分
		[[nodiscard]]
		constexpr value_type minComponent() const noexcept;

		/// @brief 最小の成分を返します。
		/// @remark Point{ 3, 2 } の場合、2 を返します。
		/// @return 最小の成分
		[[nodiscard]]
		constexpr value_type maxComponent() const noexcept;

		/// @brief すべての成分を 0 にします。
		constexpr void clear() noexcept;

		/// @brief x 成分のみを変更した自身のコピーを返します。
		/// @param _x x 成分
		/// @return x 成分を変更したコピー
		[[nodiscard]]
		constexpr Point withX(value_type _x) const noexcept;

		/// @brief y 成分のみを変更した自身のコピーを返します。
		/// @param _y y 成分
		/// @return y 成分を変更したコピー
		[[nodiscard]]
		constexpr Point withY(value_type _y) const noexcept;

		constexpr Point& set(value_type _x, value_type _y) noexcept;

		constexpr Point& set(Point p) noexcept;

		/// @brief 現在の座標から移動した座標を返します。
		/// @param _x X 方向の移動量
		/// @param _y Y 方向の移動量
		/// @return 現在の座標から移動した座標
		[[nodiscard]]
		constexpr Point movedBy(value_type _x, value_type _y) const noexcept;

		/// @brief 現在の座標から移動した座標を返します。
		/// @param p 移動量
		/// @return 現在の座標から移動した座標
		[[nodiscard]]
		constexpr Point movedBy(Point p) const noexcept;

		/// @brief 現在の座標から移動した座標を返します。
		/// @tparam Type 移動量を表す二次元ベクトルの要素の型
		/// @param v 移動量
		/// @return 現在の座標から移動した座標
		template <class Type>
		[[nodiscard]]
		constexpr Vector2D<Type> movedBy(Vector2D<Type> v) const noexcept;

		constexpr Point& moveBy(value_type _x, value_type _y) noexcept;

		constexpr Point& moveBy(Point p) noexcept;

		/// @brief 水平方向のアスペクト比を返します。
		/// @tparam Type 戻り値の型
		/// @remark Point{ 3, 2 } の場合、1.5 を返します。
		/// @return 水平方向のアスペクト比
		template <class Type = double>
		[[nodiscard]]
		constexpr Type horizontalAspectRatio() const noexcept;

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
		/// @return 別の座標からのマンハッタン距離
		[[nodiscard]]
		constexpr int32 manhattanDistanceFrom(int32 _x, int32 _y) const noexcept;

		/// @brief 別の座標からのマンハッタン距離を返します。
		/// @param p 別の座標
		/// @return 別の座標からのマンハッタン距離
		[[nodiscard]]
		constexpr int32 manhattanDistanceFrom(Point p) const noexcept;

		/// @brief 別の座標からの距離を返します。
		/// @param _x 別の座標の X 成分
		/// @param _y 別の座標の Y 成分
		/// @return 別の座標からの距離
		[[nodiscard]]
		double distanceFrom(double _x, double _y) const noexcept;

		/// @brief 別の座標からの距離を返します。
		/// @param p 別の座標
		/// @return 別の座標からの距離
		[[nodiscard]]
		double distanceFrom(Point p) const noexcept;

		/// @brief 別の座標からの距離を返します。
		/// @tparam Type 別の座標の成分の型
		/// @param p 別の座標
		/// @return 別の座標からの距離
		template <class Type>
		[[nodiscard]]
		double distanceFrom(Vector2D<Type> p) const noexcept;

		/// @brief 別の座標からの距離の二乗を返します。
		/// @param _x 別の座標の X 成分
		/// @param _y 別の座標の Y 成分
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の座標からの距離の二乗
		[[nodiscard]]
		constexpr double distanceFromSq(double _x, double _y) const noexcept;

		/// @brief 別の座標からの距離の二乗を返します。
		/// @param p 別の座標
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の座標からの距離の二乗
		[[nodiscard]]
		constexpr double distanceFromSq(Point p) const noexcept;

		/// @brief 別の座標からの距離の二乗を返します。
		/// @tparam Type 別の座標の成分の型
		/// @param p 別の座標
		/// @remark 平方根を計算しないため `distanceFrom()` より高速です。
		/// @return 別の座標からの距離の二乗
		template <class Type>
		[[nodiscard]]
		constexpr double distanceFromSq(Vector2D<Type> p) const noexcept;

		/// @brief 幅 x, 高さ y の長方形の面積を返します。
		/// @return 幅 x, 高さ y の長方形の面積
		[[nodiscard]]
		constexpr int32 area() const noexcept;

		/// @brief 時計回りに 90°* n 回転した座標を返します。
		/// @param n 時計回りに 90° 回転させる回数（負の場合は反時計回り）
		/// @return 時計回りに 90°* n 回転した座標
		[[nodiscard]]
		constexpr Point rotated90(int32 n = 1) const noexcept;

		/// @brief 自身を時計回りに 90°* n 回転します。
		/// @param n 時計回りに 90° 回転させる回数（負の場合は反時計回り）
		/// @return *this
		constexpr Point& rotate90(int32 n = 1) noexcept;

		/// @brief centerを中心とし、時計回りに 90°* n 回転した座標を返します。
		/// @param center 回転の中心座標
		/// @param n 時計回りに 90° 回転させる回数（負の場合は反時計回り）
		/// @return centerを中心とし、時計回りに 90°* n 回転した座標
		[[nodiscard]]
		constexpr Point rotated90At(Point center, int32 n = 1) const noexcept;

		/// @brief centerを中心とし、自身を時計回りに 90°* n 回転します。
		/// @param center 回転の中心座標
		/// @param n 時計回りに 90° 回転させる回数（負の場合は反時計回り）
		/// @return *this
		constexpr Point& rotate90At(Point center, int32 n = 1) noexcept;

		template <class Type = double>
		[[nodiscard]]
		Type getAngle() const noexcept;

		template <class Type>
		[[nodiscard]]
		Type getAngle(Vector2D<Type> other) const noexcept;

		[[nodiscard]]
		constexpr Point getPerpendicularCW() const noexcept;

		[[nodiscard]]
		constexpr Point getPerpendicularCCW() const noexcept;

		/// @brief 別の座標との中間にある座標を返します。
		/// @tparam Type 戻り値の二次元座標の要素の型
		/// @param other 別の座標
		/// @return 別の座標との中間にある座標
		template <class Type = double>
		[[nodiscard]]
		constexpr Vector2D<Type> getMidpoint(Point other) const noexcept;

		/// @brief 別の座標との中間にある座標を返します。
		/// @tparam Type 戻り値の二次元座標の要素の型
		/// @param other 別の座標
		/// @return 別の座標との中間にある座標
		template <class Type>
		[[nodiscard]]
		constexpr Vector2D<Type> getMidpoint(Vector2D<Type> other) const noexcept;

		template <class T, class U>
		[[nodiscard]]
		auto getPointByAngleAndDistance(T angle, U distance) const noexcept;

		template <class Type = double>
		[[nodiscard]]
		constexpr Vector2D<Type> lerp(Point other, double f) const noexcept;

		template <class Type>
		[[nodiscard]]
		constexpr Vector2D<Type> lerp(Vector2D<Type> other, double f) const noexcept;

		/// @brief この座標を中心とした円を作成して返します。
		/// @param r 円の半径
		/// @return この座標を中心とした円
		[[nodiscard]]
		Circle asCircle(double r) const noexcept;

		template <class Shape2DType>
		[[nodiscard]]
		constexpr bool intersects(const Shape2DType& other) const;

		[[nodiscard]]
		bool leftClicked() const noexcept;

		[[nodiscard]]
		bool leftPressed() const noexcept;

		[[nodiscard]]
		bool leftReleased() const noexcept;

		[[nodiscard]]
		bool rightClicked() const noexcept;

		[[nodiscard]]
		bool rightPressed() const noexcept;

		[[nodiscard]]
		bool rightReleased() const noexcept;

		[[nodiscard]]
		bool mouseOver() const noexcept;

		const Point& paint(Image& dst, const Color& color) const;

		const Point& overwrite(Image& dst, const Color& color) const;

		[[nodiscard]]
		size_t hash() const noexcept;

		/// @brief Point{ x, x } を返します。
		/// @return Point{ x, x }
		[[nodiscard]]
		constexpr Point xx() const noexcept;

		/// @brief Point{ x, y } を返します。
		/// @return Point{ x, y }
		[[nodiscard]]
		constexpr Point xy() const noexcept;

		/// @brief Point{ y x } を返します。
		/// @return Point{ y, x }
		[[nodiscard]]
		constexpr Point yx() const noexcept;

		/// @brief Point{ y, y } を返します。
		/// @return Point{ y, y }
		[[nodiscard]]
		constexpr Point yy() const noexcept;

		/// @brief Point{ x, 0 } を返します。
		/// @return Point{ x, 0 }
		[[nodiscard]]
		constexpr Point x0() const noexcept;

		/// @brief Point{ y, 0 } を返します。
		/// @return Point{ y, 0 }
		[[nodiscard]]
		constexpr Point y0() const noexcept;

		/// @brief Point{ 0, 0 } を返します。
		/// @return Point{ 0, 0 }
		[[nodiscard]]
		static constexpr Point Zero() noexcept;

		/// @brief Point{ 1, 1 } を返します。
		/// @return Point{ 1, 1 }
		[[nodiscard]]
		static constexpr Point One() noexcept;

		/// @brief Point{ value, value } を返します。
		/// @param value 値
		/// @return Point{ value, value }
		[[nodiscard]]
		static constexpr Point All(value_type value = 1) noexcept;

		/// @brief Point{ 1, 0 } を返します。
		/// @return Point{ 1, 0 }
		[[nodiscard]]
		static constexpr Point UnitX() noexcept;

		/// @brief Point{ 0, 1 } を返します。
		/// @return Point{ 0, 1 }
		[[nodiscard]]
		static constexpr Point UnitY() noexcept;

		/// @brief Point{ -length, 0 } を返します。
		/// @param length 値
		/// @return Point{ -length, 0 }
		[[nodiscard]]
		static constexpr Point Left(value_type length = 1) noexcept;

		/// @brief Point{ length, 0 } を返します。
		/// @param length 値
		/// @return Point{ length, 0 }
		[[nodiscard]]
		static constexpr Point Right(value_type length = 1) noexcept;

		/// @brief Point{ 0, -length } を返します。
		/// @param length 値
		/// @return Point{ 0, -length }
		[[nodiscard]]
		static constexpr Point Up(value_type length = 1) noexcept;

		/// @brief Point{ 0, length } を返します。
		/// @param length 値
		/// @return Point{ 0, length }
		[[nodiscard]]
		static constexpr Point Down(value_type length = 1) noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Point& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Point& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused;
		}

		friend void Formatter(FormatData& formatData, const Point& value);
	};

	using Size = Point;
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::Point, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Point& value, FormatContext& ctx)
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

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::Point>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Point& value) const noexcept
	{
		return value.hash();
	}
};
