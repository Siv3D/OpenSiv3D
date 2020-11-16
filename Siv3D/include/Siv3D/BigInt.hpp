//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Concepts.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief 多倍長整数型
	class BigInt
	{
	private:

		struct BigIntDetail;
		
		std::unique_ptr<BigIntDetail> pImpl;

		BigInt _divI(int64 a) const;
		BigInt _divI(uint64 a) const;
		BigInt _modI(int64 a) const;
		BigInt _modI(uint64 a) const;

	public:

		SIV3D_NODISCARD_CXX20
		BigInt();
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		SIV3D_NODISCARD_CXX20
		BigInt(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		SIV3D_NODISCARD_CXX20
		BigInt(UnsignedInt i);
		
		SIV3D_NODISCARD_CXX20
		BigInt(int64 i);
		
		SIV3D_NODISCARD_CXX20
		BigInt(uint64 i);
		
		SIV3D_NODISCARD_CXX20
		explicit BigInt(std::string_view number);
		
		SIV3D_NODISCARD_CXX20
		explicit BigInt(StringView number);
		
		SIV3D_NODISCARD_CXX20
		BigInt(const BigInt& other);
		
		SIV3D_NODISCARD_CXX20
		BigInt(BigInt&& other) noexcept;

		~BigInt();

		//////////////////////////////////////////////////
		//
		//	assign
		//
		//////////////////////////////////////////////////

		BigInt& assign(int64 i);
		
		BigInt& assign(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& assign(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& assign(UnsignedInt i);
		
		BigInt& assign(std::string_view number);
		
		BigInt& assign(StringView number);
		
		BigInt& assign(const BigInt& other);
		
		BigInt& assign(BigInt&& other) noexcept;

		//////////////////////////////////////////////////
		//
		//	=
		//
		//////////////////////////////////////////////////

		BigInt& operator =(int64 i);
		
		BigInt& operator =(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator =(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator =(UnsignedInt i);
		
		BigInt& operator =(std::string_view number);
		
		BigInt& operator =(StringView number);
		
		BigInt& operator =(const BigInt& other);
		
		BigInt& operator =(BigInt&& other) noexcept;

		//////////////////////////////////////////////////
		//
		//	+
		//
		//////////////////////////////////////////////////
		
		[[nodiscard]]
		const BigInt& operator +() const;
		
		BigInt& operator ++();
		
		BigInt operator ++(int);
		
		[[nodiscard]]
		BigInt operator +(int64 i) const;
		
		[[nodiscard]]
		BigInt operator +(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL	
		[[nodiscard]]
		BigInt operator +(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator +(UnsignedInt i) const;
		
		[[nodiscard]]
		BigInt operator +(const BigInt& i) const;
		
		BigInt& operator +=(int64 i);
		
		BigInt& operator +=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL	
		BigInt& operator +=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator +=(UnsignedInt i);
		
		BigInt& operator +=(const BigInt& i);

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator +(const Int a, const BigInt& b)
		{
			return (b + a);
		}

		//////////////////////////////////////////////////
		//
		//	-
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator -() const&;
		
		[[nodiscard]]
		BigInt operator -()&&;
		
		BigInt& operator --();
		
		BigInt operator --(int);
		
		[[nodiscard]]
		BigInt operator -(int64 i) const;
		
		[[nodiscard]]
		BigInt operator -(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator -(SignedInt i) const;

		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator -(UnsignedInt i) const;

		[[nodiscard]]
		BigInt operator -(const BigInt& i) const;
		
		BigInt& operator -=(int64 i);
		
		BigInt& operator -=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator -=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator -=(UnsignedInt i);
		
		BigInt& operator -=(const BigInt& i);

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator -(const Int a, const BigInt& b)
		{
			return (-b + a);
		}

		//////////////////////////////////////////////////
		//
		//	*
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator *(int64 i) const;

		[[nodiscard]]
		BigInt operator *(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator *(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator *(UnsignedInt i) const;
		
		[[nodiscard]]
		BigInt operator *(const BigInt& i) const;
		
		BigInt& operator *=(int64 i);
		
		BigInt& operator *=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator *=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator *=(UnsignedInt i);
		
		BigInt& operator *=(const BigInt& i);

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator *(const Int a, const BigInt& b)
		{
			return (b * a);
		}

		//////////////////////////////////////////////////
		//
		//	/
		//
		//////////////////////////////////////////////////

		[[nodiscard]]		
		BigInt operator /(int64 i) const;

		[[nodiscard]]
		BigInt operator /(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator /(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator /(UnsignedInt i) const;

		[[nodiscard]]
		BigInt operator /(const BigInt& i) const;

		BigInt& operator /=(int64 i);
		
		BigInt& operator /=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator /=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator /=(UnsignedInt i);
		
		BigInt& operator /=(const BigInt& i);

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator /(const SignedInt a, const BigInt& b)
		{
			return (static_cast<int64>(a) / b);
		}

		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator /(const UnsignedInt a, const BigInt& b)
		{
			return (static_cast<uint64>(a) / b);
		}

		[[nodiscard]]
		friend inline BigInt operator /(const int64 a, const BigInt& b)
		{
			return b._divI(a);
		}

		[[nodiscard]]
		friend inline BigInt operator /(const uint64 a, const BigInt& b)
		{
			return b._divI(a);
		}

		//////////////////////////////////////////////////
		//
		//	%
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator %(int64 i) const;
		
		[[nodiscard]]
		BigInt operator %(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator %(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator %(UnsignedInt i) const;
		
		[[nodiscard]]
		BigInt operator %(const BigInt& i) const;
		
		BigInt& operator %=(int64 i);
		
		BigInt& operator %=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator %=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL	
		BigInt& operator %=(UnsignedInt i);
		
		BigInt& operator %=(const BigInt& i);

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator %(const SignedInt a, const BigInt& b)
		{
			return (static_cast<int64>(a) % b);
		}

		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator %(const UnsignedInt a, const BigInt& b)
		{
			return (static_cast<uint64>(a) % b);
		}

		[[nodiscard]]
		friend inline BigInt operator %(const int64 a, const BigInt& b)
		{
			return b._modI(a);
		}

		[[nodiscard]]
		friend inline BigInt operator %(const uint64 a, const BigInt& b)
		{
			return b._modI(a);
		}

		//////////////////////////////////////////////////
		//
		//	&
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator &(int64 i) const;
		
		[[nodiscard]]
		BigInt operator &(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator &(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator &(UnsignedInt i) const;
		
		[[nodiscard]]
		BigInt operator &(const BigInt& i) const;
		
		BigInt& operator &=(int64 i);
		
		BigInt& operator &=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator &=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator &=(UnsignedInt i);
		
		BigInt& operator &=(const BigInt& i);

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator &(const Int a, const BigInt& b)
		{
			return (b & a);
		}

		//////////////////////////////////////////////////
		//
		//	|
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator |(int64 i) const;
		
		[[nodiscard]]
		BigInt operator |(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator |(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator |(UnsignedInt i) const;
		
		[[nodiscard]]
		BigInt operator |(const BigInt& i) const;
		
		BigInt& operator |=(int64 i);
		
		BigInt& operator |=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator |=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator |=(UnsignedInt i);
		
		BigInt& operator |=(const BigInt& i);

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator |(const Int a, const BigInt& b)
		{
			return (b | a);
		}

		//////////////////////////////////////////////////
		//
		//	^
		//
		//////////////////////////////////////////////////

		[[nodiscard]]	
		BigInt operator ^(int64 i) const;
		
		[[nodiscard]]
		BigInt operator ^(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator ^(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator ^(UnsignedInt i) const;
		
		[[nodiscard]]
		BigInt operator ^(const BigInt& i) const;
		
		BigInt& operator ^=(int64 i);
		
		BigInt& operator ^=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator ^=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator ^=(UnsignedInt i);
		
		BigInt& operator ^=(const BigInt& i);

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		friend inline BigInt operator ^(const Int a, const BigInt& b)
		{
			return (b ^ a);
		}

		//////////////////////////////////////////////////
		//
		//	<<
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator <<(int64 i) const;
		
		[[nodiscard]]
		BigInt operator <<(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator <<(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator <<(UnsignedInt i) const;
		
		BigInt& operator <<=(int64 i);
		
		BigInt& operator <<=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator <<=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator <<=(UnsignedInt i);

		//////////////////////////////////////////////////
		//
		//	>>
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator >>(int64 i) const;
		
		[[nodiscard]]
		BigInt operator >>(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator >>(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator >>(UnsignedInt i) const;
		
		BigInt& operator >>=(int64 i);
		
		BigInt& operator >>=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator >>=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator >>=(UnsignedInt i);

		//////////////////////////////////////////////////
		//
		//	compare
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		int32 compare(int64 i) const;
		
		[[nodiscard]]
		int32 compare(uint64 i) const;
		
		[[nodiscard]]
		int32 compare(long double f) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		int32 compare(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		int32 compare(UnsignedInt i) const;
		
		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		int32 compare(Float f) const;
		
		[[nodiscard]]
		int32 compare(const BigInt& i) const;

		//////////////////////////////////////////////////
		//
		//	==
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator ==(const BigInt& a, const BigInt& b)
		{
			return (a.compare(b) == 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator ==(const BigInt& a, const Arithmetic b)
		{
			return (a.compare(b) == 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator ==(const Arithmetic a, const BigInt& b)
		{
			return (b.compare(a) == 0);
		}

		//////////////////////////////////////////////////
		//
		//	!=
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator !=(const BigInt& a, const BigInt& b)
		{
			return (a.compare(b) != 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator !=(const BigInt& a, const Arithmetic b)
		{
			return (a.compare(b) == 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator !=(const Arithmetic a, const BigInt& b)
		{
			return (b.compare(a) != 0);
		}

		//////////////////////////////////////////////////
		//
		//	<
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator <(const BigInt& a, const BigInt& b)
		{
			return (a.compare(b) < 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <(const BigInt& a, const Arithmetic b)
		{
			return (a.compare(b) < 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <(const Arithmetic a, const BigInt& b)
		{
			return (b.compare(a) > 0);
		}

		//////////////////////////////////////////////////
		//
		//	<=
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator <=(const BigInt& a, const BigInt& b)
		{
			return (a.compare(b) <= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <=(const BigInt& a, const Arithmetic b)
		{
			return (a.compare(b) <= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <=(const Arithmetic a, const BigInt& b)
		{
			return (b.compare(a) >= 0);
		}

		//////////////////////////////////////////////////
		//
		//	>
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator >(const BigInt& a, const BigInt& b)
		{
			return (a.compare(b) > 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >(const BigInt& a, const Arithmetic b)
		{
			return (a.compare(b) > 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >(const Arithmetic a, const BigInt& b)
		{
			return (b.compare(a) < 0);
		}

		//////////////////////////////////////////////////
		//
		//	>=
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator >=(const BigInt& a, const BigInt& b)
		{
			return (a.compare(b) >= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >=(const BigInt& a, const Arithmetic b)
		{
			return (a.compare(b) >= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >=(const Arithmetic a, const BigInt& b)
		{
			return (b.compare(a) <= 0);
		}

		//////////////////////////////////////////////////
		//
		//	utilities
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		explicit operator bool() const;
		
		[[nodiscard]]
		bool isZero() const;
		
		[[nodiscard]]
		int32 sign() const;
		
		[[nodiscard]]
		BigInt abs() const;
		
		[[nodiscard]]
		BigInt pow(uint32 x) const;
		
		void divmod(const BigInt& x, BigInt& q, BigInt& r) const;
		
		[[nodiscard]]
		uint32 lsb() const;

		[[nodiscard]]
		bool bitTest(uint32 index) const;
		
		BigInt& bitSet(uint32 index, bool value);
		
		BigInt& bitFlip(uint32 index);

		void swap(BigInt& other) noexcept;

		[[nodiscard]]
		size_t hash() const;

		//////////////////////////////////////////////////
		//
		//	conversions
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		int32 asInt32() const;
		
		[[nodiscard]]
		int64 asInt64() const;
		
		[[nodiscard]]
		uint32 asUint32() const;
		
		[[nodiscard]]
		uint64 asUint64() const;
		
		[[nodiscard]]
		size_t asSize_t() const;
		
		[[nodiscard]]
		float asFloat() const;
		
		[[nodiscard]]
		double asDouble() const;
		
		[[nodiscard]]
		BigFloat asBigFloat() const;

		[[nodiscard]]
		explicit operator size_t() const;

		[[nodiscard]]
		explicit operator float() const;

		[[nodiscard]]
		explicit operator double() const;

		[[nodiscard]]
		explicit operator BigFloat() const;

		[[nodiscard]]
		std::string stdStr() const;

		[[nodiscard]]
		std::wstring stdWstr() const;

		[[nodiscard]]
		String str() const;

		//////////////////////////////////////////////////
		//
		//	detail
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigIntDetail& _detail();

		[[nodiscard]]
		const BigIntDetail& _detail() const;
	};

	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			[[nodiscard]]
			BigInt operator ""_big(unsigned long long int i);

			[[nodiscard]]
			BigInt operator ""_big(const char* s, size_t length);

			[[nodiscard]]
			BigInt operator ""_big(const char32* s, size_t length);
		}
	}

	namespace Math
	{
		[[nodiscard]]
		BigInt GCD(const BigInt& a, const BigInt& b);

		[[nodiscard]]
		BigInt LCM(const BigInt& a, const BigInt& b);
	}
}

template <>
inline void std::swap(s3d::BigInt& a, s3d::BigInt& b) noexcept;

template <>
struct std::hash<s3d::BigInt>
{
	[[nodiscard]]
	size_t operator()(const s3d::BigInt& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/BigInt.ipp"
