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
	inline constexpr Vector4D<Type>::Vector4D(const value_type _x, const value_type _y, const value_type _z, const value_type _w) noexcept
		: x{ _x }
		, y{ _y }
		, z{ _z }
		, w{ _w } {}

	template <class Type>
	template <class X, class Y, class Z, class W>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Y _y, const Z _z, const W _w) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ static_cast<value_type>(_y) }
		, z{ static_cast<value_type>(_z) }
		, w{ static_cast<value_type>(_w) } {}


	template <class Type>
	template <class U>
	inline constexpr Vector4D<Type>::Vector4D(const Vector4D<U>& v) noexcept
		: x{ static_cast<value_type>(v.x) }
		, y{ static_cast<value_type>(v.y) }
		, z{ static_cast<value_type>(v.z) }
		, w{ static_cast<value_type>(v.w) } {}

	template <class Type>
	template <class X, class Y>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Y _y, const Vector2D<value_type>& zw) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ static_cast<value_type>(_y) }
		, z{ zw.x }
		, w{ zw.y } {}

	template <class Type>
	template <class X, class W>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Vector2D<value_type>& yz, const W _w) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ yz.x }
		, z{ yz.y }
		, w{ static_cast<value_type>(_w) } {}

	template <class Type>
	template <class Z, class W>
	inline constexpr Vector4D<Type>::Vector4D(const Vector2D<value_type>& xy, const Z _z, const W _w) noexcept
		: x{ xy.x }
		, y{ xy.y }
		, z{ static_cast<value_type>(_z) }
		, w{ static_cast<value_type>(_w) } {}

	template <class Type>
	inline constexpr Vector4D<Type>::Vector4D(const Vector2D<value_type>& xy, const Vector2D<value_type>& zw) noexcept
		: x{ xy.x }
		, y{ xy.y }
		, z{ zw.x }
		, w{ zw.y } {}

	template <class Type>
	template <class X>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Vector3D<value_type>& yzw) noexcept
		: x{ static_cast<value_type>(_x) }
		, y{ yzw.x }
		, z{ yzw.y }
		, w{ yzw.z } {}

	template <class Type>
	template <class Z>
	inline constexpr Vector4D<Type>::Vector4D(const Vector3D<value_type>& xyz, const Z _z) noexcept
		: x{ xyz.x }
		, y{ xyz.y }
		, z{ xyz.z }
		, w{ static_cast<value_type>(_z) } {}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::elem(const size_t index) const noexcept
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
		else if (index == 3)
		{
			return w;
		}
		else
		{
			return 0;
		}
	}

	template <class Type>
	inline typename Vector4D<Type>::value_type* Vector4D<Type>::getPointer() noexcept
	{
		return &x;
	}

	template <class Type>
	inline const typename Vector4D<Type>::value_type* Vector4D<Type>::getPointer() const noexcept
	{
		return &x;
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator +() const noexcept
	{
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator -() const noexcept
	{
		return{ -x, -y, -z, -w };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator +(const Vector4D v) const noexcept
	{
		return{ (x + v.x), (y + v.y), (z + v.z), (w + v.w) };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator -(const Vector4D v) const noexcept
	{
		return{ (x - v.x), (y - v.y), (z - v.z), (w - v.w) };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator *(const value_type s) const noexcept
	{
		return{ (x * s), (y * s), (z * s), (w * s) };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator *(const Vector4D v) const noexcept
	{
		return{ (x * v.x), (y * v.y), (z * v.z), (w * v.w) };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator /(const value_type s) const noexcept
	{
		return *this * (static_cast<value_type>(1.0) / s);
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::operator /(const Vector4D v) const noexcept
	{
		return{ (x / v.x), (y / v.y), (z / v.z), (w / v.w) };
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::operator +=(const Vector4D v) noexcept
	{
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::operator -=(const Vector4D v) noexcept
	{
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::operator *=(const value_type s) noexcept
	{
		x *= s; y *= s; z *= s; w *= s;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::operator *=(const Vector4D v) noexcept
	{
		x *= v.x; y *= v.y; z *= v.z; w *= v.w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::operator /=(const value_type s) noexcept
	{
		return *this *= (static_cast<value_type>(1.0) / s);
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::operator /=(const Vector4D v) noexcept
	{
		x /= v.x; y /= v.y; z /= v.z; w /= v.w;
		return *this;
	}

	template <class Type>
	inline constexpr bool Vector4D<Type>::epsilonEquals(const Vector4D other, const value_type epsilon) const noexcept
	{
		return (AbsDiff(x, other.x) <= epsilon)
			&& (AbsDiff(y, other.y) <= epsilon)
			&& (AbsDiff(z, other.z) <= epsilon)
			&& (AbsDiff(w, other.w) <= epsilon);
	}

	template <class Type>
	inline constexpr bool Vector4D<Type>::hasSameDirection(const Vector4D other) const noexcept
	{
		return dot(other) > 0;
	}

	template <class Type>
	inline constexpr bool Vector4D<Type>::hasOppositeDirection(const Vector4D other) const noexcept
	{
		return dot(other) < 0;
	}

	template <class Type>
	inline constexpr bool Vector4D<Type>::isZero() const noexcept
	{
		return (x == static_cast<value_type>(0.0))
			&& (y == static_cast<value_type>(0.0))
			&& (z == static_cast<value_type>(0.0))
			&& (w == static_cast<value_type>(0.0));
	}

	template <class Type>
	inline bool Vector4D<Type>::hasNaN() const noexcept
	{
		return std::isnan(x)
			|| std::isnan(y)
			|| std::isnan(z)
			|| std::isnan(w);
	}

	template <class Type>
	constexpr typename Vector4D<Type>::value_type Vector4D<Type>::minComponent() const noexcept
	{
		return Min(Min(x, y), Min(z, w));
	}

	template <class Type>
	constexpr typename Vector4D<Type>::value_type Vector4D<Type>::maxComponent() const noexcept
	{
		return Max(Max(x, y), Max(z, w));
	}

	template <class Type>
	inline constexpr void Vector4D<Type>::clear() noexcept
	{
		x = 0; y = 0; z = 0; w = 0;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const Vector2D<value_type>& xy, const Vector2D<value_type>& zw) noexcept
	{
		x = xy.x; y = xy.y; z = zw.x; w = zw.y;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const Vector2D<value_type>& xy, const value_type _z, const value_type _w) noexcept
	{
		x = xy.x; y = xy.y; z = _z; w = _w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const value_type _x, const Vector2D<value_type>& yz, const value_type _w) noexcept
	{
		x = _x; y = yz.x; z = yz.y; w = _w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const value_type _x, const value_type _y, const Vector2D<value_type>& zw) noexcept
	{
		x = _x; y = _y; z = zw.x; w = zw.y;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const Vector3D<value_type>& xyz, const value_type _w) noexcept
	{
		x = xyz.x; y = xyz.y; z = xyz.z; w = _w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const value_type _x, const Vector3D<value_type>& yzw) noexcept
	{
		x = _x; y = yzw.x; z = yzw.y; w = yzw.z;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const value_type _x, const value_type _y, const value_type _z, const value_type _w) noexcept
	{
		x = _x; y = _y; z = _z; w = _w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::set(const Vector4D v) noexcept
	{
		return *this = v;
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::movedBy(const value_type _x, const value_type _y, const value_type _z, const value_type _w) const noexcept
	{
		return{ (x + _x), (y + _y), (z + _z), (w + _w) };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::movedBy(const Vector4D v) const noexcept
	{
		return{ (x + v.x), (y + v.y), (z + v.z), (w + v.w) };
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::moveBy(const value_type _x, const value_type _y, const value_type _z, const value_type _w) noexcept
	{
		x += _x; y += _y; z += _z; w += _w;
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type>& Vector4D<Type>::moveBy(const Vector4D v) noexcept
	{
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::dot(const Vector4D v) const noexcept
	{
		return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
	}

	template <class Type>
	inline typename Vector4D<Type>::value_type Vector4D<Type>::length() const noexcept
	{
		return std::sqrt(lengthSq());
	}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::lengthSq() const noexcept
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	template <class Type>
	inline typename Vector4D<Type>::value_type Vector4D<Type>::invLength() const noexcept
	{
		return (static_cast<value_type>(1.0) / length());
	}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::manhattanLength() const noexcept
	{
		return (Abs(x) + Abs(y) + Abs(z) + Abs(w));
	}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::manhattanDistanceFrom(const value_type _x, const value_type _y, const value_type _z, const value_type _w) const noexcept
	{
		const auto xMinMax = std::minmax(x, _x);
		const auto yMinMax = std::minmax(y, _y);
		const auto zMinMax = std::minmax(z, _z);
		const auto wMinMax = std::minmax(w, _w);
		return (xMinMax.second - xMinMax.first)
			+ (yMinMax.second - yMinMax.first)
			+ (zMinMax.second - zMinMax.first)
			+ (wMinMax.second - wMinMax.first);
	}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::manhattanDistanceFrom(const Vector4D v) const noexcept
	{
		return manhattanDistanceFrom(v.x, v.y, v.z, v.w);
	}

	template <class Type>
	inline typename Vector4D<Type>::value_type Vector4D<Type>::distanceFrom(const value_type _x, const value_type _y, const value_type _z, const value_type _w) const noexcept
	{
		return std::sqrt(distanceFromSq(_x, _y, _z, _w));
	}

	template <class Type>
	inline typename Vector4D<Type>::value_type Vector4D<Type>::distanceFrom(const Vector4D v) const noexcept
	{
		return distanceFrom(v.x, v.y, v.z, v.w);
	}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::distanceFromSq(const value_type _x, const value_type _y, const value_type _z, const value_type _w) const noexcept
	{
		const value_type xx = (x - _x) * (x - _x);
		const value_type yy = (y - _y) * (y - _y);
		const value_type zz = (z - _z) * (z - _z);
		const value_type ww = (w - _w) * (w - _w);
		return (xx + yy + zz + ww);
	}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::distanceFromSq(const Vector4D v) const noexcept
	{
		return distanceFromSq(v.x, v.y, v.z, v.w);
	}

	template <class Type>
	inline Vector4D<Type> Vector4D<Type>::withLength(const value_type _length) const noexcept
	{
		if (const value_type len = length())
		{
			return (*this * (_length / len));
		}

		return *this;
	}

	template <class Type>
	inline Vector4D<Type>& Vector4D<Type>::setLength(const value_type _length) noexcept
	{
		if (const value_type len = length())
		{
			*this *= (_length / len);
		}

		return *this;
	}

	template <class Type>
	inline Vector4D<Type> Vector4D<Type>::limitLength(const value_type maxLength) const noexcept
	{
		if (const value_type len = length();
			len > maxLength)
		{
			return (*this * (maxLength / len));
		}

		return *this;
	}

	template <class Type>
	inline Vector4D<Type>& Vector4D<Type>::limitLengthSelf(const value_type maxLength) noexcept
	{
		if (const value_type len = length();
			len > maxLength)
		{
			*this *= (maxLength / len);
		}

		return *this;
	}

	template <class Type>
	inline Vector4D<Type> Vector4D<Type>::normalized() const noexcept
	{
		return (*this * invLength());
	}

	template <class Type>
	inline Vector4D<Type>& Vector4D<Type>::normalize() noexcept
	{
		return (*this *= invLength());
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::getMidpoint(const Vector4D other) const noexcept
	{
		constexpr value_type half(0.5);
		return{ (x * half + other.x * half), (y * half + other.y * half), (z * half + other.z * half), (w * half + other.w * half) };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::lerp(const Vector4D other, const value_type f) const noexcept
	{
		return{ (x + (other.x - x) * f), (y + (other.y - y) * f), (z + (other.z - z) * f), (w + (other.w - w) * f) };
	}

	template <class Type>
	inline size_t Vector4D<Type>::hash() const noexcept
	{
		return Hash::FNV1a(*this);
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::xx() const noexcept
	{
		return{ x, x };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::xy() const noexcept
	{
		return{ x, y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::xz() const noexcept
	{
		return{ x, z };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::xw() const noexcept
	{
		return{ x, w };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::yx() const noexcept
	{
		return{ y, x };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::yy() const noexcept
	{
		return{ y, y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::yz() const noexcept
	{
		return{ y, z };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::yw() const noexcept
	{
		return{ y, w };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::zx() const noexcept
	{
		return{ z, x };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::zy() const noexcept
	{
		return{ z, y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::zz() const noexcept
	{
		return{ z, z };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::zw() const noexcept
	{
		return{ z, w };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::wx() const noexcept
	{
		return{ w, x };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::wy() const noexcept
	{
		return{ w, y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::wz() const noexcept
	{
		return{ w, z };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector4D<Type>::ww() const noexcept
	{
		return{ w, w };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::xxx() const noexcept
	{
		return{ x, x, x };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::xyz() const noexcept
	{
		return{ x, y, z };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::yyy() const noexcept
	{
		return{ y, y, y };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::yxz() const noexcept
	{
		return{ y, x, z };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::yzw() const noexcept
	{
		return{ y, z, w };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::zzz() const noexcept
	{
		return{ z, z, z };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::zyx() const noexcept
	{
		return{ z, y, x };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::www() const noexcept
	{
		return{ w, w, w };
	}

	template <class Type>
	inline constexpr Vector3D<Type> Vector4D<Type>::wzy() const noexcept
	{
		return{ w, z, y };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::xyz0() const noexcept
	{
		return{ x, y, z, 0 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::xyz1() const noexcept
	{
		return{ x, y, z, 1 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::xyzw() const noexcept
	{
		return *this;
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::xxxx() const noexcept
	{
		return{ x, x, x, x };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::yyyy() const noexcept
	{
		return{ y, y, y, y };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::zzzz() const noexcept
	{
		return{ z, z, z, z };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::wwww() const noexcept
	{
		return{ w, w, w, w };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::wzyx() const noexcept
	{
		return{ w, z, y, x };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::Zero() noexcept
	{
		return{ 0, 0, 0, 0 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::One() noexcept
	{
		return{ 1, 1, 1, 1 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::All(const value_type value) noexcept
	{
		return{ value, value, value, value };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::UnitX() noexcept
	{
		return{ 1, 0, 0, 0 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::UnitY() noexcept
	{
		return{ 0, 1, 0, 0 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::UnitZ() noexcept
	{
		return{ 0, 0, 1, 0 };
	}

	template <class Type>
	inline constexpr Vector4D<Type> Vector4D<Type>::UnitW() noexcept
	{
		return{ 0, 0, 0, 1 };
	}
}
