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
# if  __has_include(<compare>)
#	include <compare>
# endif
# include <memory>
# include "BigInt.hpp"

namespace s3d
{
	/// @brief 100 桁の精度を持つ浮動小数点数型
	class BigFloat
	{
	private:

		struct BigFloatDetail;

	public:

		SIV3D_NODISCARD_CXX20
		BigFloat();
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		SIV3D_NODISCARD_CXX20
		BigFloat(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		SIV3D_NODISCARD_CXX20
		BigFloat(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		SIV3D_NODISCARD_CXX20
		BigFloat(Float f);
		
		SIV3D_NODISCARD_CXX20
		BigFloat(int64 f);
		
		SIV3D_NODISCARD_CXX20
		BigFloat(uint64 f);
		
		SIV3D_NODISCARD_CXX20
		BigFloat(long double f);
		
		SIV3D_NODISCARD_CXX20
		BigFloat(const BigInt& number);
		
		SIV3D_NODISCARD_CXX20
		explicit BigFloat(std::string_view number);
		
		SIV3D_NODISCARD_CXX20
		explicit BigFloat(StringView number);
		
		SIV3D_NODISCARD_CXX20
		BigFloat(const BigFloat& other);
		
		SIV3D_NODISCARD_CXX20
		BigFloat(BigFloat&& other) noexcept;
		
		~BigFloat();

		//////////////////////////////////////////////////
		//
		//	assign
		//
		//////////////////////////////////////////////////

		BigFloat& assign(int64 i);
		
		BigFloat& assign(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigFloat& assign(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigFloat& assign(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		BigFloat& assign(Float f);
		
		BigFloat& assign(long double f);
		
		BigFloat& assign(const BigInt& number);
		
		BigFloat& assign(std::string_view number);
		
		BigFloat& assign(StringView number);
		
		BigFloat& assign(const BigFloat& other);
		
		BigFloat& assign(BigFloat&& other) noexcept;

		//////////////////////////////////////////////////
		//
		//	=
		//
		//////////////////////////////////////////////////

		BigFloat& operator =(int64 i);
		
		BigFloat& operator =(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigFloat& operator =(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigFloat& operator =(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		BigFloat& operator =(Float f);
		
		BigFloat& operator =(long double f);
		
		BigFloat& operator =(const BigInt& number);
		
		BigFloat& operator =(std::string_view number);
		
		BigFloat& operator =(StringView number);
		
		BigFloat& operator =(const BigFloat& other);
		
		BigFloat& operator =(BigFloat&& other) noexcept;

		//////////////////////////////////////////////////
		//
		//	+
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		const BigFloat& operator +() const;
		
		BigFloat& operator ++();
		
		BigFloat operator ++(int);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigFloat operator +(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigFloat operator +(UnsignedInt i) const;
		
		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		BigFloat operator +(Float f) const;
		
		[[nodiscard]]
		BigFloat operator +(int64 i) const;
		
		[[nodiscard]]
		BigFloat operator +(uint64 i) const;
		
		[[nodiscard]]
		BigFloat operator +(long double f) const;
		
		[[nodiscard]]
		BigFloat operator +(const BigInt& number) const;
		
		[[nodiscard]]
		BigFloat operator +(const BigFloat& number) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigFloat& operator +=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigFloat& operator +=(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		BigFloat& operator +=(Float f);
		
		BigFloat& operator +=(int64 i);
		
		BigFloat& operator +=(uint64 i);
		
		BigFloat& operator +=(long double f);
		
		BigFloat& operator +=(const BigInt& number);
		
		BigFloat& operator +=(const BigFloat& number);

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline BigFloat operator +(Arithmetic a, const BigFloat& b)
		{
			return (b + a);
		}

		//////////////////////////////////////////////////
		//
		//	-
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigFloat operator -() const&;
		
		[[nodiscard]]
		BigFloat operator -()&&;
		
		BigFloat& operator --();
		
		BigFloat operator --(int);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigFloat operator -(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigFloat operator -(UnsignedInt i) const;
		
		SIV3D_CONCEPT_FLOATING_POINT		
		[[nodiscard]]
		BigFloat operator -(Float f) const;
		
		[[nodiscard]]
		BigFloat operator -(int64 i) const;
		
		[[nodiscard]]
		BigFloat operator -(uint64 i) const;
		
		[[nodiscard]]
		BigFloat operator -(long double f) const;
		
		[[nodiscard]]
		BigFloat operator -(const BigInt& number) const;
		
		[[nodiscard]]
		BigFloat operator -(const BigFloat& number) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigFloat& operator -=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigFloat& operator -=(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		BigFloat& operator -=(Float f);
		
		BigFloat& operator -=(int64 i);
		
		BigFloat& operator -=(uint64 i);
		
		BigFloat& operator -=(long double f);
		
		BigFloat& operator -=(const BigInt& number);
		
		BigFloat& operator -=(const BigFloat& number);

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline BigFloat operator -(Arithmetic a, const BigFloat& b)
		{
			return -(b - a);
		}

		//////////////////////////////////////////////////
		//
		//	*
		//
		//////////////////////////////////////////////////

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigFloat operator *(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigFloat operator *(UnsignedInt i) const;
		
		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		BigFloat operator *(Float f) const;
		
		[[nodiscard]]
		BigFloat operator *(int64 i) const;
		
		[[nodiscard]]
		BigFloat operator *(uint64 i) const;
		
		[[nodiscard]]
		BigFloat operator *(long double f) const;
		
		[[nodiscard]]
		BigFloat operator *(const BigInt& number) const;
		
		[[nodiscard]]
		BigFloat operator *(const BigFloat& number) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigFloat& operator *=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigFloat& operator *=(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		BigFloat& operator *=(Float f);
		
		BigFloat& operator *=(int64 i);
		
		BigFloat& operator *=(uint64 i);
		
		BigFloat& operator *=(long double f);
		
		BigFloat& operator *=(const BigInt& number);
		
		BigFloat& operator *=(const BigFloat& number);

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline BigFloat operator *(Arithmetic a, const BigFloat& b)
		{
			return (b * a);
		}

		//////////////////////////////////////////////////
		//
		//	/
		//
		//////////////////////////////////////////////////

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]] BigFloat operator /(SignedInt i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigFloat operator /(UnsignedInt i) const;
		
		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		BigFloat operator /(Float f) const;
		
		[[nodiscard]]
		BigFloat operator /(int64 i) const;
		
		[[nodiscard]]
		BigFloat operator /(uint64 i) const;
		
		[[nodiscard]]
		BigFloat operator /(long double f) const;
		
		[[nodiscard]]
		BigFloat operator /(const BigInt& number) const;
		
		[[nodiscard]]
		BigFloat operator /(const BigFloat& number) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigFloat& operator /=(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigFloat& operator /=(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		BigFloat& operator /=(Float f);
		
		BigFloat& operator /=(int64 i);
		
		BigFloat& operator /=(uint64 i);
		
		BigFloat& operator /=(long double f);
		
		BigFloat& operator /=(const BigInt& number);
		
		BigFloat& operator /=(const BigFloat& number);

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline BigFloat operator /(Arithmetic a, const BigFloat& b)
		{
			return BigFloat{ a } / b;
		}

		//////////////////////////////////////////////////
		//
		//	compare
		//
		//////////////////////////////////////////////////

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
		int32 compare(int64 i) const;
		
		[[nodiscard]]
		int32 compare(uint64 i) const;
		
		[[nodiscard]]
		int32 compare(long double f) const;
		
		[[nodiscard]]
		int32 compare(const BigInt& number) const;
		
		[[nodiscard]]
		int32 compare(const BigFloat& number) const;

		//////////////////////////////////////////////////
		//
		//	==
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator ==(const BigFloat& a, const BigFloat& b)
		{
			return (a.compare(b) == 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator ==(const BigFloat& a, const Arithmetic b)
		{
			return (a.compare(b) == 0);
		}

#if __cpp_impl_three_way_comparison

		//////////////////////////////////////////////////
		//
		//	<=>
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline std::partial_ordering operator <=>(const BigFloat& a, const BigFloat& b)
		{
			if (a.isNaN() || b.isNaN()) {
				return std::partial_ordering::unordered;
			}
			return (a.compare(b) <=> 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline std::partial_ordering operator <=>(const BigFloat& a, const Arithmetic b)
		{
			if constexpr (std::is_floating_point_v<Arithmetic>) {
				if (std::isnan(b)) {
					return std::partial_ordering::unordered;
				}
			}
			if (a.isNaN()) {
				return std::partial_ordering::unordered;
			}
			return (a.compare(b) <=> 0);
		}

#else

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator ==(const BigFloat a, const BigFloat& b)
		{
			return (b.compare(a) == 0);
		}

		//////////////////////////////////////////////////
		//
		//	!=
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator !=(const BigFloat& a, const BigFloat& b)
		{
			return (a.compare(b) != 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator !=(const BigFloat& a, const Arithmetic b)
		{
			return (a.compare(b) != 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator !=(const Arithmetic a, const BigFloat& b)
		{
			return (b.compare(a) != 0);
		}

		//////////////////////////////////////////////////
		//
		//	<
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator <(const BigFloat& a, const BigFloat& b)
		{
			return (a.compare(b) < 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <(const BigFloat& a, const Arithmetic b)
		{
			return (a.compare(b) < 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <(const Arithmetic a, const BigFloat& b)
		{
			return (b.compare(a) > 0);
		}

		//////////////////////////////////////////////////
		//
		//	<=
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator <=(const BigFloat& a, const BigFloat& b)
		{
			return (a.compare(b) <= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <=(const BigFloat& a, const Arithmetic b)
		{
			return (a.compare(b) <= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator <=(const Arithmetic a, const BigFloat& b)
		{
			return (b.compare(a) >= 0);
		}

		//////////////////////////////////////////////////
		//
		//	>
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator >(const BigFloat& a, const BigFloat& b)
		{
			return (a.compare(b) > 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >(const BigFloat& a, const Arithmetic b)
		{
			return (a.compare(b) > 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >(const Arithmetic a, const BigFloat& b)
		{
			return (b.compare(a) < 0);
		}

		//////////////////////////////////////////////////
		//
		//	>=
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		friend inline bool operator >=(const BigFloat& a, const BigFloat& b)
		{
			return (a.compare(b) >= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >=(const BigFloat& a, const Arithmetic b)
		{
			return (a.compare(b) >= 0);
		}

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		friend inline bool operator >=(const Arithmetic a, const BigFloat& b)
		{
			return (b.compare(a) <= 0);
		}

#endif

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
		bool isNaN() const;

		[[nodiscard]]
		bool isInf() const;

		[[nodiscard]]
		int32 sign() const;
		
		[[nodiscard]]
		BigFloat abs() const;

		void swap(BigFloat& other) noexcept;

		size_t hash() const;

		//////////////////////////////////////////////////
		//
		//	conversions
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		float asFloat() const;
		
		[[nodiscard]]
		double asDouble() const;
		
		[[nodiscard]]
		long double asLongDouble() const;

		[[nodiscard]]
		std::string to_string() const;
				
		[[nodiscard]]
		std::wstring to_wstring() const;
		
		[[nodiscard]]
		String str() const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const BigFloat& value)
		{
			return (output << value.str());
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, BigFloat& value)
		{
			if (String s; input >> s)
			{
				value.assign(s);
			}

			return input;
		}

		friend void Formatter(FormatData& formatData, const BigFloat& value);

		//////////////////////////////////////////////////
		//
		//	detail
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigFloatDetail& _detail();

		[[nodiscard]]
		const BigFloatDetail& _detail() const;

	private:

		std::unique_ptr<BigFloatDetail> pImpl;
	};

	namespace Math
	{
		[[nodiscard]]
		BigFloat Fmod(const BigFloat& x, const BigFloat& y);

		[[nodiscard]]
		BigFloat Fraction(const BigFloat& x);

		[[nodiscard]]
		BigFloat Frexp(const BigFloat& x, int32& exp);

		[[nodiscard]]
		BigFloat Ldexp(const BigFloat& x, const BigFloat& y);

		[[nodiscard]]
		BigFloat Log(const BigFloat& x);

		[[nodiscard]]
		BigFloat Log2(const BigFloat& x);

		[[nodiscard]]
		BigFloat Log10(const BigFloat& x);

		[[nodiscard]]
		BigFloat Modf(const BigFloat& x, BigFloat& exp);

		[[nodiscard]]
		BigInt Pow(const BigInt& x, uint32 y);

		[[nodiscard]]
		BigFloat Pow(const BigFloat& x, const BigFloat& y);

		[[nodiscard]]
		int32 Sign(const BigInt& x);

		[[nodiscard]]
		int32 Sign(const BigFloat& x);

		[[nodiscard]]
		BigFloat ToRadians(const BigFloat& x);

		[[nodiscard]]
		BigFloat ToDegrees(const BigFloat& x);

		[[nodiscard]]
		BigFloat Abs(const BigInt& x);

		[[nodiscard]]
		BigFloat Abs(const BigFloat& x);

		[[nodiscard]]
		BigFloat AbsDiff(const BigFloat& x, const BigFloat& y);

		[[nodiscard]]
		BigFloat Square(const BigInt& x);

		[[nodiscard]]
		BigFloat Square(const BigFloat& x);

		[[nodiscard]]
		BigFloat Exp(const BigFloat& x);

		[[nodiscard]]
		BigFloat Exp2(const BigFloat& x);

		[[nodiscard]]
		BigFloat Rsqrt(const BigFloat& x);

		[[nodiscard]]
		BigFloat Sqrt(const BigFloat& x);

		[[nodiscard]]
		BigFloat Ceil(const BigFloat& x);

		[[nodiscard]]
		BigFloat Floor(const BigFloat& x);

		[[nodiscard]]
		BigFloat Round(const BigFloat& x);

		[[nodiscard]]
		BigFloat Clamp(const BigFloat& x, const BigFloat& min, const BigFloat& max);

		[[nodiscard]]
		BigFloat Saturate(const BigFloat& x);

		[[nodiscard]]
		BigFloat Acos(const BigFloat& x);

		[[nodiscard]]
		BigFloat Asin(const BigFloat& x);

		[[nodiscard]]
		BigFloat Atan(const BigFloat& x);

		[[nodiscard]]
		BigFloat Atan2(const BigFloat& y, const BigFloat& x);

		[[nodiscard]]
		BigFloat Cos(const BigFloat& x);

		[[nodiscard]]
		BigFloat Cosh(const BigFloat& x);

		[[nodiscard]]
		BigFloat Sin(const BigFloat& x);

		[[nodiscard]]
		BigFloat Sinh(const BigFloat& x);

		[[nodiscard]]
		BigFloat Tan(const BigFloat& x);

		[[nodiscard]]
		BigFloat Tanh(const BigFloat& x);

		[[nodiscard]]
		BigFloat Normalize(const BigFloat& x);

		[[nodiscard]]
		BigFloat Smoothstep(const BigFloat& min, const BigFloat& max, const BigFloat& x);

		[[nodiscard]]
		BigFloat Smoothstep(const BigFloat& x);
	}

	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			[[nodiscard]]
			BigFloat operator ""_bigF(const char* s);
		}
	}
}

template <>
inline void std::swap(s3d::BigFloat& a, s3d::BigFloat& b) noexcept;

template <>
struct std::hash<s3d::BigFloat>
{
	[[nodiscard]]
	size_t operator ()(const s3d::BigFloat& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/BigFloat.ipp"
