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
	template <class Type>
	inline constexpr Vector3D<Type>::Vector3D(const value_type _x, const value_type _y, const value_type _z) noexcept
		: x{ _x }
		, y{ _y }
		, z{ _z } {}

	template <class Type>
	template <class X, class Y, class Z>
	inline constexpr Vector3D<Type>::Vector3D(const X _x, const Y _y, const Z _z) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ static_cast<value_type>(_y) }
		, z{ static_cast<value_type>(_z) } {}

	template <class Type>
	template <class U>
	inline constexpr Vector3D<Type>::Vector3D(const Vector3D<U>& v) noexcept
		: x{ static_cast<value_type>(v.x) }
		, y{ static_cast<value_type>(v.y) }
		, z{ static_cast<value_type>(v.z) } {}

	template <class Type>
	template <class Z>
	inline constexpr Vector3D<Type>::Vector3D(const Vector2D<value_type>& xy, const Z _z) noexcept
		: x{ xy.x }
		, y{ xy.y }
		, z{ static_cast<value_type>(_z) } {}

	template <class Type>
	template <class X>
	inline constexpr Vector3D<Type>::Vector3D(const X _x, const Vector2D<value_type>& yz) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ yz.x }
		, z{ yz.y } {}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::elem(const size_t index) const noexcept
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

	template <class Type>
	inline typename Vector3D<Type>::value_type* Vector3D<Type>::getPointer() noexcept
	{
		return &x;
	}

	template <class Type>
	inline const typename Vector3D<Type>::value_type* Vector3D<Type>::getPointer() const noexcept
	{
		return &x;
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator +() const noexcept
	{
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator -() const noexcept
	{
		return{ -x, -y, -z };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator +(const Vector3D v) const noexcept
	{
		return{ (x + v.x), (y + v.y), (z + v.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator -(const Vector3D v) const noexcept
	{
		return{ (x - v.x), (y - v.y), (z - v.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator *(const value_type s) const noexcept
	{
		return{ (x * s), (y * s), (z * s) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator *(const Vector3D v) const noexcept
	{
		return{ (x * v.x), (y * v.y), (z * v.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator /(const value_type s) const noexcept
	{
		return *this * (static_cast<value_type>(1.0) / s);
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::operator /(const Vector3D v) const noexcept
	{
		return{ (x / v.x), (y / v.y), (z / v.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::operator +=(const Vector3D v) noexcept
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::operator -=(const Vector3D v) noexcept
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::operator *=(const value_type s) noexcept
	{
		x *= s; y *= s; z *= s;
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::operator *=(const Vector3D v) noexcept
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::operator /=(const value_type s) noexcept
	{
		return *this *= (static_cast<value_type>(1.0) / s);
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::operator /=(const Vector3D v) noexcept
	{
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}

	template <class Type>
	inline constexpr bool Vector3D<Type>::epsilonEquals(const Vector3D other, const value_type epsilon) const noexcept
	{
		return (AbsDiff(x, other.x) <= epsilon)
			&& (AbsDiff(y, other.y) <= epsilon)
			&& (AbsDiff(z, other.z) <= epsilon);
	}

	template <class Type>
	inline constexpr bool Vector3D<Type>::hasSameDirection(const Vector3D other) const noexcept
	{
		return dot(other) > 0;
	}

	template <class Type>
	inline constexpr bool Vector3D<Type>::hasOppositeDirection(const Vector3D other) const noexcept
	{
		return dot(other) < 0;
	}

	template <class Type>
	inline constexpr bool Vector3D<Type>::isZero() const noexcept
	{
		return (x == static_cast<value_type>(0.0))
			&& (y == static_cast<value_type>(0.0))
			&& (z == static_cast<value_type>(0.0));
	}

	template <class Type>
	inline bool Vector3D<Type>::hasNaN() const noexcept
	{
		return std::isnan(x)
			|| std::isnan(y)
			|| std::isnan(z);
	}

	template <class Type>
	constexpr typename Vector3D<Type>::value_type Vector3D<Type>::minComponent() const noexcept
	{
		return Min({ x, y, z });
	}

	template <class Type>
	constexpr typename Vector3D<Type>::value_type Vector3D<Type>::maxComponent() const noexcept
	{
		return Max({ x, y, z });
	}

	template <class Type>
	inline constexpr void Vector3D<Type>::clear() noexcept
	{
		x = 0; y = 0; z = 0;
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::set(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		x = _x; y = _y; z = _z;
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::set(const Vector3D v) noexcept
	{
		return *this = v;
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::movedBy(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return{ (x + _x), (y + _y), (z + _z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::movedBy(const Vector3D v) const noexcept
	{
		return{ (x + v.x), (y + v.y), (z + v.z) };
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::moveBy(const value_type _x, const value_type _y, const value_type _z) noexcept
	{
		x += _x; y += _y; z += _z;
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type>& Vector3D<Type>::moveBy(const Vector3D v) noexcept
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::dot(const Vector3D v) const noexcept
	{
		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::cross(const Vector3D v) const noexcept
	{
		return{ (y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x) };
	}

	template <class Type>
	inline typename Vector3D<Type>::value_type Vector3D<Type>::angleTo(const Vector3D v) const noexcept
	{
		const value_type denom = std::sqrt(lengthSq() * v.lengthSq());

		if (denom < static_cast<value_type>(0.0000001))
		{
			return Math::Pi_v<value_type>;
		}

		const value_type theta = (dot(v) / denom);

		return std::acos(Clamp(theta, static_cast<value_type>(-1.0), static_cast<value_type>(1.0)));
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::projectOnVector(const Vector3D v) const noexcept
	{
		if (v.lengthSq() < 0.0000001)
		{
			return{ 0, 0, 0 };
		}

		return (v * (dot(v) / v.dot(v)));
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::projectOnPlane(const Vector3D planeNormal) const noexcept
	{
		return (*this - projectOnVector(planeNormal));
	}

	template <class Type>
	inline typename Vector3D<Type>::value_type Vector3D<Type>::length() const noexcept
	{
		return std::sqrt(lengthSq());
	}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::lengthSq() const noexcept
	{
		return (x * x) + (y * y) + (z * z);
	}

	template <class Type>
	inline typename Vector3D<Type>::value_type Vector3D<Type>::invLength() const noexcept
	{
		return (static_cast<value_type>(1.0) / length());
	}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::manhattanLength() const noexcept
	{
		return (Abs(x) + Abs(y) + Abs(z));
	}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::manhattanDistanceFrom(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		const auto xMinMax = std::minmax(x, _x);
		const auto yMinMax = std::minmax(y, _y);
		const auto zMinMax = std::minmax(z, _z);
		return (xMinMax.second - xMinMax.first)
			+ (yMinMax.second - yMinMax.first)
			+ (zMinMax.second - zMinMax.first);
	}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::manhattanDistanceFrom(const Vector3D v) const noexcept
	{
		return manhattanDistanceFrom(v.x, v.y, v.z);
	}

	template <class Type>
	inline typename Vector3D<Type>::value_type Vector3D<Type>::distanceFrom(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		return std::sqrt(distanceFromSq(_x, _y, _z));
	}

	template <class Type>
	inline typename Vector3D<Type>::value_type Vector3D<Type>::distanceFrom(const Vector3D v) const noexcept
	{
		return distanceFrom(v.x, v.y, v.z);
	}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::distanceFromSq(const value_type _x, const value_type _y, const value_type _z) const noexcept
	{
		const value_type xx = (x - _x) * (x - _x);
		const value_type yy = (y - _y) * (y - _y);
		const value_type zz = (z - _z) * (z - _z);
		return (xx + yy + zz);
	}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::distanceFromSq(const Vector3D v) const noexcept
	{
		return distanceFromSq(v.x, v.y, v.z);
	}

	template <class Type>
	inline Vector3D<Type> Vector3D<Type>::withLength(const value_type _length) const noexcept
	{
		if (const value_type len = length())
		{
			return (*this * (_length / len));
		}

		return *this;
	}

	template <class Type>
	inline Vector3D<Type>& Vector3D<Type>::setLength(const value_type _length) noexcept
	{
		if (const value_type len = length())
		{
			*this *= (_length / len);
		}

		return *this;
	}

	template <class Type>
	inline Vector3D<Type> Vector3D<Type>::limitLength(const value_type maxLength) const noexcept
	{
		if (const value_type len = length();
			len > maxLength)
		{
			return (*this * (maxLength / len));
		}

		return *this;
	}

	template <class Type>
	inline Vector3D<Type>& Vector3D<Type>::limitLengthSelf(const value_type maxLength) noexcept
	{
		if (const value_type len = length();
			len > maxLength)
		{
			*this *= (maxLength / len);
		}

		return *this;
	}

	template <class Type>
	inline Vector3D<Type> Vector3D<Type>::normalized() const noexcept
	{
		return (*this * invLength());
	}

	template <class Type>
	inline Vector3D<Type>& Vector3D<Type>::normalize() noexcept
	{
		return (*this *= invLength());
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::getMidpoint(const Vector3D other) const noexcept
	{
		constexpr value_type half(0.5);
		return{ (x * half + other.x * half), (y * half + other.y * half), (z * half + other.z * half) };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::lerp(const Vector3D other, const value_type f) const noexcept
	{
		return{ (x + (other.x - x) * f), (y + (other.y - y) * f), (z + (other.z - z) * f) };
	}

	template <class Type>
	inline size_t Vector3D<Type>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::xx() const noexcept
	{
		return{ x, x };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::xy() const noexcept
	{
		return{ x, y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::xz() const noexcept
	{
		return{ x, z };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::yx() const noexcept
	{
		return{ y, x };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::yy() const noexcept
	{
		return{ y, y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::yz() const noexcept
	{
		return{ y, z };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::zx() const noexcept
	{
		return{ z, x };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::zy() const noexcept
	{
		return{ z, y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector3D<Type>::zz() const noexcept
	{
		return{ z, z };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::xxx() const noexcept
	{
		return{ x, x, x };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::xyz() const noexcept
	{
		return *this;
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::xzy() const noexcept
	{
		return{ x, z, y };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::yyy() const noexcept
	{
		return{ y, y, y };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::yxz() const noexcept
	{
		return{ y, x, z };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::yzx() const noexcept
	{
		return{ y, z, x };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::zzz() const noexcept
	{
		return{ z, z, z };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::zxy() const noexcept
	{
		return{ z, x, y };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::zyx() const noexcept
	{
		return{ z, y, x };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector3D<Type>::xyz0() const noexcept
	{
		return{ x, y, z, 0 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector3D<Type>::xyz1() const noexcept
	{
		return{ x, y, z, 1 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::Zero() noexcept
	{
		return{ 0, 0, 0 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::One() noexcept
	{
		return{ 1, 1, 1 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::All(const value_type value) noexcept
	{
		return{ value, value, value };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::UnitX() noexcept
	{
		return{ 1, 0, 0 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::UnitY() noexcept
	{
		return{ 0, 1, 0 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::UnitZ() noexcept
	{
		return{ 0, 0, 1 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::Left(const value_type length) noexcept
	{
		return{ -length, 0, 0 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::Right(const value_type length) noexcept
	{
		return{ length, 0, 0 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::Up(const value_type length) noexcept
	{
		return{ 0, length, 0 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::Down(const value_type length) noexcept
	{
		return{ 0, -length, 0 };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::Forward(const value_type length) noexcept
	{
		return{ 0, 0, length };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector3D<Type>::Backward(const value_type length) noexcept
	{
		return{ 0, 0, -length };
	}
}
