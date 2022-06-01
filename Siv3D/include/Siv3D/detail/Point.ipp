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

namespace s3d
{
	namespace Geometry2D
	{
		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Point& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Vec2& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Line& b) noexcept;

		[[nodiscard]]
		bool Intersect(const Point& a, const Bezier2& b);

		//[[nodiscard]]
		//bool Intersect(const Point& a, const Bezier3& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Rect& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const RectF& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Circle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Ellipse& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Triangle& b) noexcept;

		[[nodiscard]]
		inline constexpr bool Intersect(const Point& a, const Quad& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Point& a, const RoundRect& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Point& a, const Polygon& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Point& a, const MultiPolygon& b) noexcept;

		[[nodiscard]]
		inline bool Intersect(const Point& a, const LineString& b) noexcept;
	}

	inline constexpr Point::Point(const value_type _x, const value_type _y) noexcept
		: x{ _x }
		, y{ _y } {}

# if __cpp_lib_concepts
	template <Concept::Integral IntegerX, Concept::Integral IntegerY>
# else
	template <class IntegerX, class IntegerY, std::enable_if_t<std::conjunction_v<std::is_integral<IntegerX>, std::is_integral<IntegerY>>>*>
# endif
	inline constexpr Point::Point(const IntegerX _x, const IntegerY _y) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ static_cast<value_type>(_y) } {}

	inline constexpr Point::value_type Point::elem(const size_t index) const noexcept
	{
		if (index == 0)
		{
			return x;
		}
		else if (index == 1)
		{
			return y;
		}
		else
		{
			return 0;
		}
	}

	inline Point::value_type* Point::getPointer() noexcept
	{
		return &x;
	}

	inline const Point::value_type* Point::getPointer() const noexcept
	{
		return &x;
	}

	inline constexpr Point Point::operator +() const noexcept
	{
		return *this;
	}

	inline constexpr Point Point::operator -() const noexcept
	{
		return{ -x, -y };
	}

	inline constexpr Point Point::operator +(const Point p) const noexcept
	{
		return{ x + p.x, y + p.y };
	}

	inline constexpr Point Point::operator -(const Point p) const noexcept
	{
		return{ x - p.x, y - p.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::operator +(const Vector2D<Type> v) const noexcept
	{
		return{ x + v.x, y + v.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::operator -(const Vector2D<Type> v) const noexcept
	{
		return{ x - v.x, y - v.y };
	}

	inline constexpr Point Point::operator *(const int32 s) const noexcept
	{
		return{ x * s, y * s };
	}

	inline constexpr Float2 Point::operator * (const float s) const noexcept
	{
		return{ x * s, y * s };
	}

	inline constexpr Vec2 Point::operator * (const double s) const noexcept
	{
		return{ x * s, y * s };
	}

	inline constexpr Point Point::operator *(const Point p) const noexcept
	{
		return{ x * p.x, y * p.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::operator *(const Vector2D<Type> v) const noexcept
	{
		return{ x * v.x, y * v.y };
	}

	inline constexpr Point Point::operator /(const int32 s) const noexcept
	{
		return{ x / s, y / s };
	}

	inline constexpr Float2 Point::operator /(const float s) const noexcept
	{
		return{ x / s, y / s };
	}

	inline constexpr Vec2 Point::operator /(const double s) const noexcept
	{
		return{ x / s, y / s };
	}

	inline constexpr Point Point::operator /(const Point p) const noexcept
	{
		return{ x / p.x, y / p.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::operator /(const Vector2D<Type> v) const noexcept
	{
		return{ x / v.x, y / v.y };
	}

	inline constexpr Point& Point::operator +=(const Point p) noexcept
	{
		x += p.x; y += p.y;
		return *this;
	}

	inline constexpr Point& Point::operator -=(const Point p) noexcept
	{
		x -= p.x; y -= p.y;
		return *this;
	}

	inline constexpr Point& Point::operator *=(const int32 s) noexcept
	{
		x *= s; y *= s;
		return *this;
	}

	inline constexpr Point& Point::operator /=(const int32 s) noexcept
	{
		assert(s != 0);
		x /= s; y /= s;
		return *this;
	}

	inline constexpr bool Point::isZero() const noexcept
	{
		return ((x == 0) && (y == 0));
	}

	constexpr Point::value_type Point::minComponent() const noexcept
	{
		return Min(x, y);
	}

	constexpr Point::value_type Point::maxComponent() const noexcept
	{
		return Max(x, y);
	}

	inline constexpr void Point::clear() noexcept
	{
		x = 0; y = 0;
	}

	inline constexpr Point& Point::set(const int32 _x, const int32 _y) noexcept
	{
		x = _x; y = _y;
		return *this;
	}

	inline constexpr Point& Point::set(const Point p) noexcept
	{
		return *this = p;
	}

	inline constexpr Point Point::movedBy(const int32 _x, const int32 _y) const noexcept
	{
		return{ x + _x, y + _y };
	}

	inline constexpr Point Point::movedBy(const Point p) const noexcept
	{
		return{ x + p.x, y + p.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::movedBy(const Vector2D<Type> v) const noexcept
	{
		return{ x + v.x, y + v.y };
	}

	inline constexpr Point& Point::moveBy(const int32 _x, const int32 _y) noexcept
	{
		x += _x; y += _y;
		return *this;
	}

	inline constexpr Point& Point::moveBy(const Point p) noexcept
	{
		x += p.x; y += p.y;
		return *this;
	}

	template <class Type>
	inline constexpr Type Point::horizontalAspectRatio() const noexcept
	{
		if (y == 0)
		{
			return 0;
		}

		return (static_cast<Type>(x) / y);
	}

	template <class Type>
	inline Type Point::length() const noexcept
	{
		return static_cast<Type>(std::sqrt((x * x) + (y * y)));
	}

	template <class Type>
	inline constexpr Type Point::lengthSq() const noexcept
	{
		return static_cast<Type>((x * x) + (y * y));
	}

	inline constexpr int32 Point::manhattanLength() const noexcept
	{
		return Abs(x) + Abs(y);
	}

	inline constexpr int32 Point::manhattanDistanceFrom(const int32 _x, const int32 _y) const noexcept
	{
		const auto xMinMax = std::minmax(x, _x);
		const auto yMinMax = std::minmax(y, _y);
		return (xMinMax.second - xMinMax.first) + (yMinMax.second - yMinMax.first);
	}

	inline constexpr int32 Point::manhattanDistanceFrom(const Point p) const noexcept
	{
		return manhattanDistanceFrom(p.x, p.y);
	}

	inline double Point::distanceFrom(const double _x, const double _y) const noexcept
	{
		return std::sqrt(distanceFromSq(_x, _y));
	}

	inline double Point::distanceFrom(const Point p) const noexcept
	{
		return distanceFrom(p.x, p.y);
	}

	template <class Type>
	inline double Point::distanceFrom(const Vector2D<Type> p) const noexcept
	{
		return distanceFrom(p.x, p.y);
	}

	inline constexpr double Point::distanceFromSq(const double _x, const double _y) const noexcept
	{
		const double xx = (x - _x) * (x - _x);
		const double yy = (y - _y) * (y - _y);
		return (xx + yy);
	}

	inline constexpr double Point::distanceFromSq(const Point p) const noexcept
	{
		return distanceFromSq(p.x, p.y);
	}

	template <class Type>
	inline constexpr double Point::distanceFromSq(const Vector2D<Type> p) const noexcept
	{
		return distanceFromSq(p.x, p.y);
	}

	constexpr int32 Point::area() const noexcept
	{
		return (x * y);
	}

	template <class Type>
	inline Type Point::getAngle() const noexcept
	{
		if (isZero())
		{
			return Math::NaN_v<Type>;
		}

		return std::atan2(x, -y);
	}

	template <class Type>
	inline Type Point::getAngle(const Vector2D<Type> other) const noexcept
	{
		if (isZero() || other.isZero())
		{
			return Math::NaN_v<Type>;
		}

		return std::atan2(Vector2D<Type>{ *this }.cross(other), Vector2D<Type>{ *this }.dot(other));
	}

	inline constexpr Point Point::getPerpendicularCW() const noexcept
	{
		return{ -y, x };
	}

	inline constexpr Point Point::getPerpendicularCCW() const noexcept
	{
		return{ y, -x };
	}

	template <class Type>
	constexpr Vector2D<Type> Point::getMidpoint(const Point other) const noexcept
	{
		return{ x + (other.x - x) * 0.5, y + (other.y - y) * 0.5 };
	}

	template <class Type>
	constexpr Vector2D<Type> Point::getMidpoint(const Vector2D<Type> other) const noexcept
	{
		return{ x * 0.5 + other.x * 0.5, y * 0.5 + other.y * 0.5 };
	}

	template <class T, class U>
	auto Point::getPointByAngleAndDistance(const T angle, const U distance) const noexcept
	{
		using ValueType = CommonFloat_t<T, U>;
		const auto s = std::sin(angle);
		const auto c = std::cos(angle);
		return Vector2D<ValueType>{
			static_cast<ValueType>((s * distance) + x),
			static_cast<ValueType>((-c * distance) + y) };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::lerp(const Point other, const double f) const noexcept
	{
		return{ x + (other.x - x) * f, y + (other.y - y) * f };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Point::lerp(const Vector2D<Type> other, const double f) const noexcept
	{
		return { x + (other.x - x) * f, y + (other.y - y) * f };
	}

	template <class Shape2DType>
	inline constexpr bool Point::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	inline size_t Point::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline constexpr Point Point::xx() const noexcept
	{
		return{ x, x };
	}

	inline constexpr Point Point::xy() const noexcept
	{
		return{ x, y };
	}

	inline constexpr Point Point::yx() const noexcept
	{
		return{ y, x };
	}

	inline constexpr Point Point::yy() const noexcept
	{
		return{ y, y };
	}

	inline constexpr Point Point::x0() const noexcept
	{
		return{ x, 0 };
	}

	inline constexpr Point Point::y0() const noexcept
	{
		return{ y, 0 };
	}

	inline constexpr Point Point::Zero() noexcept
	{
		return{ 0, 0 };
	}

	inline constexpr Point Point::One() noexcept
	{
		return{ 1, 1 };
	}

	inline constexpr Point Point::All(const value_type value) noexcept
	{
		return{ value, value };
	}

	inline constexpr Point Point::UnitX() noexcept
	{
		return{ 1, 0 };
	}

	inline constexpr Point Point::UnitY() noexcept
	{
		return{ 0, 1 };
	}

	inline constexpr Point Point::Left(const value_type length) noexcept
	{
		return{ -length, 0 };
	}

	inline constexpr Point Point::Right(const value_type length) noexcept
	{
		return{ length, 0 };
	}

	inline constexpr Point Point::Up(const value_type length) noexcept
	{
		return{ 0, -length };
	}

	inline constexpr Point Point::Down(const value_type length) noexcept
	{
		return{ 0, length };
	}
}
