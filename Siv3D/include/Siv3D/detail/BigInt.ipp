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
	inline BigInt::BigInt(const SignedInt i)
		: BigInt{ static_cast<int64>(i) } {}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt::BigInt(const UnsignedInt i)
		: BigInt{ static_cast<uint64>(i) } {}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::assign(const SignedInt i)
	{
		return assign(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::assign(const UnsignedInt i)
	{
		return assign(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator =(const SignedInt i)
	{
		return assign(i);
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator =(const UnsignedInt i)
	{
		return assign(i);
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator +(const SignedInt i) const
	{
		return operator +(static_cast<int64>(i));
	}
		
	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator +(const UnsignedInt i) const
	{
		return operator +(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator +=(const SignedInt i)
	{
		return operator +=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator +=(const UnsignedInt i)
	{
		return operator +=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator -(const SignedInt i) const
	{
		return operator -(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator -(const UnsignedInt i) const
	{
		return operator -(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator -=(const SignedInt i)
	{ 
		return operator -=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator -=(const UnsignedInt i)
	{
		return operator -=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator *(const SignedInt i) const
	{
		return operator *(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator *(const UnsignedInt i) const
	{
		return operator *(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator *=(const SignedInt i)
	{
		return operator *=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator *=(const UnsignedInt i)
	{
		return operator *=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator /(const SignedInt i) const
	{
		return operator /(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator /(const UnsignedInt i) const
	{
		return operator /(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator /=(const SignedInt i)
	{
		return operator /=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator /=(const UnsignedInt i)
	{
		return operator /=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator %(const SignedInt i) const
	{
		return operator %(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator %(const UnsignedInt i) const
	{
		return operator %(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator %=(const SignedInt i)
	{
		return operator %=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator %=(const UnsignedInt i)
	{
		return operator %=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator &(const SignedInt i) const
	{
		return operator &(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator &(const UnsignedInt i) const
	{
		return operator &(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator &=(const SignedInt i)
	{
		return operator &=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator &=(const UnsignedInt i)
	{
		return operator &=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator |(const SignedInt i) const
	{
		return operator |(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator |(const UnsignedInt i) const
	{
		return operator |(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator |=(const SignedInt i)
	{
		return operator |=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator |=(const UnsignedInt i)
	{
		return operator |=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator ^(const SignedInt i) const
	{
		return operator ^(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator ^(const UnsignedInt i) const
	{
		return operator ^(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator ^=(const SignedInt i)
	{
		return operator ^=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator ^=(const UnsignedInt i)
	{
		return operator ^=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator <<(const SignedInt i) const
	{
		return operator <<(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator <<(const UnsignedInt i) const
	{
		return operator <<(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator <<=(const SignedInt i)
	{
		return operator <<=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator <<=(const UnsignedInt i)
	{
		return operator <<=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator >>(const SignedInt i) const
	{
		return operator >> (static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator >>(const UnsignedInt i) const
	{
		return operator >> (static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator >>=(const SignedInt i)
	{
		return operator >>=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator >>=(const UnsignedInt i)
	{
		return operator >>=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline int32 BigInt::compare(const SignedInt i) const
	{
		return compare(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline int32 BigInt::compare(const UnsignedInt i) const
	{
		return compare(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline int32 BigInt::compare(const Float f) const
	{
		return compare(static_cast<long double>(f));
	}

	inline BigInt::operator size_t() const
	{
		return asSize_t();
	}

	inline BigInt::operator float() const
	{
		return asFloat();
	}

	inline BigInt::operator double() const
	{
		return asDouble();
	}
}

template <>
inline void std::swap(s3d::BigInt& a, s3d::BigInt& b) noexcept
{
	a.swap(b);
}
