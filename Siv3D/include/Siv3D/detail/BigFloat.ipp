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
	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat::BigFloat(const SignedInt i)
		: BigFloat{ static_cast<int64>(i) } {}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat::BigFloat(const UnsignedInt i)
		: BigFloat{ static_cast<uint64>(i) } {}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat::BigFloat(const Float f)
		: BigFloat{ static_cast<long double>(f) } {}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat& BigFloat::assign(const SignedInt i)
	{
		return assign(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat& BigFloat::assign(const UnsignedInt i)
	{
		return assign(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat& BigFloat::assign(const Float f)
	{
		return assign(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator =(const SignedInt i)
	{
		return assign(i);
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator =(const UnsignedInt i)
	{
		return assign(i);
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat& BigFloat::operator =(const Float f)
	{
		return assign(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator +(const SignedInt i) const
	{
		return operator +(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator +(const UnsignedInt i) const
	{
		return operator +(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat BigFloat::operator +(const Float f) const
	{
		return operator +(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator +=(const SignedInt i)
	{
		return operator +=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator +=(const UnsignedInt i)
	{
		return operator +=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat& BigFloat::operator +=(const Float f)
	{
		return operator +=(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator -(const SignedInt i) const
	{
		return operator -(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator -(const UnsignedInt i) const
	{
		return operator -(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat BigFloat::operator -(const Float f) const
	{
		return operator -(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator -=(const SignedInt i)
	{
		return operator -=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator -=(const UnsignedInt i)
	{
		return operator -=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat& BigFloat::operator -=(const Float f)
	{
		return operator -=(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator *(const SignedInt i) const
	{
		return operator *(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator *(const UnsignedInt i) const
	{
		return operator *(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat BigFloat::operator *(const Float f) const
	{
		return operator *(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator *=(const SignedInt i)
	{
		return operator *=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator *=(const UnsignedInt i)
	{
		return operator *=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat& BigFloat::operator *=(const Float f)
	{
		return operator *=(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator /(const SignedInt i) const
	{
		return operator /(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat BigFloat::operator /(const UnsignedInt i) const
	{
		return operator /(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat BigFloat::operator /(const Float f) const
	{
		return operator /(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator /=(const SignedInt i)
	{
		return operator /=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigFloat& BigFloat::operator /=(const UnsignedInt i)
	{
		return operator /=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline BigFloat& BigFloat::operator /=(const Float f)
	{
		return operator /=(static_cast<long double>(f));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline int32 BigFloat::compare(const SignedInt i) const
	{
		return compare(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline int32 BigFloat::compare(const UnsignedInt i) const
	{
		return compare(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline int32 BigFloat::compare(const Float f) const
	{
		return compare(static_cast<long double>(f));
	}
}

template <>
inline void std::swap(s3d::BigFloat& a, s3d::BigFloat& b) noexcept
{
	a.swap(b);
}
