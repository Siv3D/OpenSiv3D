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

namespace s3d
{
# if __cpp_lib_concepts
	template <Concept::Integral IntegerX, Concept::Integral IntegerY, Concept::Integral IntegerZ>
# else
	template <class IntegerX, class IntegerY, class IntegerZ, std::enable_if_t<std::conjunction_v<std::is_integral<IntegerX>, std::is_integral<IntegerY>, std::is_integral<IntegerZ>>>*>
# endif
	inline constexpr Point3D::Point3D(const IntegerX _x, const IntegerY _y, const IntegerZ _z) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ static_cast<value_type>(_y) }
		, z{ static_cast<value_type>(_z) } {}

	inline constexpr Point3D::value_type Point3D::elem(const size_t index) const noexcept
	{
		if (index == 0)
		{
			return x;
		}
		else if (index == 1)
		{
			return y;
		}
		else if (index == 2)
		{
			return z;
		}
		else
		{
			return 0;
		}
	}

	inline Point3D::value_type* Point3D::getPointer() noexcept
	{
		return &x;
	}

	inline const Point3D::value_type* Point3D::getPointer() const noexcept
	{
		return &x;
	}

	inline constexpr Point3D Point3D::operator +() const noexcept
	{
		return *this;
	}

	inline constexpr Point3D Point3D::operator -() const noexcept
	{
		return{ -x, -y, -z };
	}

	inline constexpr Point3D Point3D::operator +(const Point3D p) const noexcept
	{
		return{ (x + p.x), (y + p.y), (z + p.z) };
	}

	inline constexpr Point3D Point3D::operator -(const Point3D p) const noexcept
	{
		return{ (x - p.x), (y - p.y), (z - p.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Point3D::operator +(const Vector3D<Type> v) const noexcept
	{
		return{ (x + v.x), (y + v.y), (z + v.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Point3D::operator -(const Vector3D<Type> v) const noexcept
	{
		return{ (x - v.x), (y - v.y), (z - v.z) };
	}

	inline constexpr Point3D Point3D::operator *(const int32 s) const noexcept
	{
		return{ (x * s), (y * s), (z * s) };
	}

	inline constexpr Float3 Point3D::operator *(const float s) const noexcept
	{
		return{ (x * s), (y * s), (z * s) };
	}

	inline constexpr Vec3 Point3D::operator *(const double s) const noexcept
	{
		return{ (x * s), (y * s), (z * s) };
	}

	inline constexpr Point3D Point3D::operator *(const Point3D p) const noexcept
	{
		return{ (x * p.x), (y * p.y), (z * p.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Point3D::operator *(const Vector3D<Type> v) const noexcept
	{
		return{ (x * v.x), (y * v.y), (z * v.z) };
	}

	inline constexpr Point3D Point3D::operator /(const int32 s) const noexcept
	{
		return{ (x / s), (y / s), (z / s) };
	}

	inline constexpr Float3 Point3D::operator /(const float s) const noexcept
	{
		return{ (x / s), (y / s), (z / s) };
	}

	inline constexpr Vec3 Point3D::operator /(const double s) const noexcept
	{
		return{ (x / s), (y / s), (z / s) };
	}

	inline constexpr Point3D Point3D::operator /(const Point3D p) const noexcept
	{
		return{ (x / p.x), (y / p.y), (z / p.z) };
	}

	inline constexpr Point3D Point3D::operator %(const int32 s) const noexcept
	{
		return{ (x % s), (y % s), (z % s) };
	}

	inline constexpr Point3D Point3D::operator %(const Point3D p) const noexcept
	{
		return{ (x % p.x), (y % p.y), (z % p.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Point3D::operator /(const Vector3D<Type> v) const noexcept
	{
		return{ (x / v.x), (y / v.y), (z / v.z) };
	}

	inline constexpr Point3D& Point3D::operator +=(const Point3D p) noexcept
	{
		x += p.x; y += p.y; z += p.z;
		return *this;
	}

	inline constexpr Point3D& Point3D::operator -=(const Point3D p) noexcept
	{
		x -= p.x; y -= p.y; z -= p.z;
		return *this;
	}

	inline constexpr Point3D& Point3D::operator *=(const int32 s) noexcept
	{
		x *= s; y *= s; z *= s;
		return *this;
	}

	inline constexpr Point3D& Point3D::operator /=(const int32 s) noexcept
	{
		assert(s != 0);
		x /= s; y /= s; z /= s;
		return *this;
	}

	inline constexpr Point3D& Point3D::operator %=(const int32 s) noexcept
	{
		assert(s != 0);
		x %= s; y %= s; z %= s;
		return *this;
	}

	inline constexpr bool Point3D::isZero() const noexcept
	{
		return ((x == 0) && (y == 0) && (z == 0));
	}

	inline constexpr Point3D::value_type Point3D::minComponent() const noexcept
	{
		return Min({ x, y, z });
	}

	inline constexpr Point3D::value_type Point3D::maxComponent() const noexcept
	{
		return Max({ x, y, z });
	}

	inline constexpr void Point3D::clear() noexcept
	{
		x = 0; y = 0; z = 0;
	}

	inline constexpr Point3D& Point3D::set(const int32 _x, const int32 _y, const int32 _z) noexcept
	{
		x = _x; y = _y; z = _z;
		return *this;
	}

	inline constexpr Point3D& Point3D::set(const Point3D p) noexcept
	{
		return (*this = p);
	}

	inline constexpr Point3D Point3D::movedBy(const int32 _x, const int32 _y, const int32 _z) const noexcept
	{
		return{ (x + _x), (y + _y), (z + _z) };
	}

	inline constexpr Point3D Point3D::movedBy(const Point3D p) const noexcept
	{
		return{ (x + p.x), (y + p.y), (z + p.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Point3D::movedBy(const Vector3D<Type> v) const noexcept
	{
		return{ (x + v.x), (y + v.y), (z + v.z) };
	}

	inline constexpr Point3D& Point3D::moveBy(const int32 _x, const int32 _y, const int32 _z) noexcept
	{
		x += _x; y += _y; z += _z;
		return *this;
	}

	inline constexpr Point3D& Point3D::moveBy(const Point3D p) noexcept
	{
		x += p.x; y += p.y; z += p.z;
		return *this;
	}

	template <class Type>
	inline Type Point3D::length() const noexcept
	{
		return static_cast<Type>(std::sqrt((x * x) + (y * y) + (z * z)));
	}

	template <class Type>
	inline constexpr Type Point3D::lengthSq() const noexcept
	{
		return static_cast<Type>((x * x) + (y * y) + (z * z));
	}

	inline constexpr int32 Point3D::manhattanLength() const noexcept
	{
		return (Abs(x) + Abs(y) + Abs(z));
	}

	inline constexpr int32 Point3D::manhattanDistanceFrom(const int32 _x, const int32 _y, const int32 _z) const noexcept
	{
		const auto xMinMax = std::minmax(x, _x);
		const auto yMinMax = std::minmax(y, _y);
		const auto zMinMax = std::minmax(z, _z);
		return ((xMinMax.second - xMinMax.first) + (yMinMax.second - yMinMax.first) + (zMinMax.second - zMinMax.first));
	}

	inline constexpr int32 Point3D::manhattanDistanceFrom(const Point3D p) const noexcept
	{
		return manhattanDistanceFrom(p.x, p.y, p.z);
	}

	inline double Point3D::distanceFrom(const double _x, const double _y, const double _z) const noexcept
	{
		return std::sqrt(distanceFromSq(_x, _y, _z));
	}

	inline double Point3D::distanceFrom(const Point3D p) const noexcept
	{
		return distanceFrom(p.x, p.y, p.z);
	}

	template <class Type>
	inline double Point3D::distanceFrom(const Vector3D<Type> p) const noexcept
	{
		return distanceFrom(p.x, p.y, p.z);
	}

	inline constexpr double Point3D::distanceFromSq(const double _x, const double _y, const double _z) const noexcept
	{
		const double xx = ((x - _x) * (x - _x));
		const double yy = ((y - _y) * (y - _y));
		const double zz = ((z - _z) * (z - _z));
		return (xx + yy + zz);
	}

	inline constexpr double Point3D::distanceFromSq(const Point3D p) const noexcept
	{
		return distanceFromSq(p.x, p.y, p.z);
	}

	template <class Type>
	inline constexpr double Point3D::distanceFromSq(const Vector3D<Type> p) const noexcept
	{
		return distanceFromSq(p.x, p.y, p.z);
	}

	template <class Type>
	constexpr Vector3D<Type> Point3D::getMidpoint(const Point3D other) const noexcept
	{
		return{ (x + (other.x - x) * 0.5), (y + (other.y - y) * 0.5), (z + (other.z - z) * 0.5) };
	}

	template <class Type>
	constexpr Vector3D<Type> Point3D::getMidpoint(const Vector3D<Type> other) const noexcept
	{
		return{ (x * 0.5 + other.x * 0.5), (y * 0.5 + other.y * 0.5), (z * 0.5 + other.z * 0.5) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Point3D::lerp(const Point3D other, const double f) const noexcept
	{
		return{ (x + (other.x - x) * f), (y + (other.y - y) * f), (z + (other.z - z) * f) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Point3D::lerp(const Vector3D<Type> other, const double f) const noexcept
	{
		return { (x + (other.x - x) * f), (y + (other.y - y) * f), (z + (other.z - z) * f) };
	}

	inline size_t Point3D::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	inline constexpr Point3D Point3D::Zero() noexcept
	{
		return{ 0, 0, 0 };
	}

	inline constexpr Point3D Point3D::One() noexcept
	{
		return{ 1, 1, 1 };
	}

	inline constexpr Point3D Point3D::All(const value_type value) noexcept
	{
		return{ value, value, value };
	}

	inline constexpr Point3D Point3D::UnitX() noexcept
	{
		return{ 1, 0, 0 };
	}

	inline constexpr Point3D Point3D::UnitY() noexcept
	{
		return{ 0, 1, 0 };
	}

	inline constexpr Point3D Point3D::UnitZ() noexcept
	{
		return{ 0, 0, 1 };
	}
}
