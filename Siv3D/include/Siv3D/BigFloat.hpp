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
# include "BigInt.hpp"

namespace s3d
{
	/// @brief 100 桁の精度を持つ浮動小数点数型
	class BigFloat
	{
	private:

		struct BigFloatDetail;
		
		std::unique_ptr<BigFloatDetail> pImpl;

		friend BigFloat operator /(int64 a, const BigFloat& b);
		friend BigFloat operator /(uint64 a, const BigFloat& b);
		friend BigFloat operator /(long double a, const BigFloat& b);

	public:

		BigFloat();
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigFloat(SignedInt i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigFloat(UnsignedInt i);
		
		SIV3D_CONCEPT_FLOATING_POINT
		BigFloat(Float f);
		
		BigFloat(int64 f);
		
		BigFloat(uint64 f);
		
		BigFloat(long double f);
		
		BigFloat(const BigInt& number);
		
		explicit BigFloat(std::string_view number);
		
		explicit BigFloat(StringView number);
		
		BigFloat(const BigFloat& other);
		
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
		BigFloatDetail& _detail();

		[[nodiscard]]
		const BigFloatDetail& _detail() const;
	};

	/*
	template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
	[[nodiscard]] inline BigFloat operator +(const Type& a, const BigFloat& b)
	{
		return b + a;
	}

	template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
	[[nodiscard]] inline BigFloat operator -(const Type& a, const BigFloat& b)
	{
		return -b + a;
	}

	template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
	[[nodiscard]] inline BigFloat operator *(const Type& a, const BigFloat& b)
	{
		return b * a;
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL
	[[nodiscard]] inline BigFloat operator /(Integer a, const BigFloat& b)
	{
		return static_cast<int64>(a) / b;
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL
	[[nodiscard]] inline BigFloat operator /(Integer a, const BigFloat& b)
	{
		return static_cast<uint64>(a) / b;
	}

	template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>* = nullptr>
	[[nodiscard]] inline BigFloat operator /(Float a, const BigFloat& b)
	{
		return static_cast<long double>(a) / b;
	}

	[[nodiscard]] BigFloat operator /(int64 a, const BigFloat& b);
	[[nodiscard]] BigFloat operator /(uint64 a, const BigFloat& b);
	[[nodiscard]] BigFloat operator /(long double a, const BigFloat& b);

	[[nodiscard]] inline bool operator ==(const BigFloat& a, const BigFloat& b)
	{
		return a.compare(b) == 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator ==(const BigFloat& a, Number b)
	{
		return a.compare(b) == 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator ==(Number a, const BigFloat& b)
	{
		return b.compare(a) == 0;
	}

	[[nodiscard]] inline bool operator !=(const BigFloat& a, const BigFloat& b)
	{
		return a.compare(b) != 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator !=(const BigFloat& a, Number b)
	{
		return a.compare(b) != 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator !=(Number a, const BigFloat& b)
	{
		return b.compare(a) != 0;
	}

	[[nodiscard]] inline bool operator <(const BigFloat& a, const BigFloat& b)
	{
		return a.compare(b) < 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <(const BigFloat& a, Number b)
	{
		return a.compare(b) < 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <(Number a, const BigFloat& b)
	{
		return b.compare(a) < 0;
	}

	[[nodiscard]] inline bool operator <=(const BigFloat& a, const BigFloat& b)
	{
		return a.compare(b) <= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <=(const BigFloat& a, Number b)
	{
		return a.compare(b) <= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <=(Number a, const BigFloat& b)
	{
		return b.compare(a) <= 0;
	}

	[[nodiscard]] inline bool operator >(const BigFloat& a, const BigFloat& b)
	{
		return a.compare(b) > 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >(const BigFloat& a, Number b)
	{
		return a.compare(b) > 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >(Number a, const BigFloat& b)
	{
		return b.compare(a) > 0;
	}

	[[nodiscard]] inline bool operator >=(const BigFloat& a, const BigFloat& b)
	{
		return a.compare(b) >= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >=(const BigFloat& a, Number b)
	{
		return a.compare(b) >= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >=(Number a, const BigFloat& b)
	{
		return b.compare(a) >= 0;
	}

	namespace Math
	{
		[[nodiscard]] BigFloat Abs(const BigFloat& x);

		[[nodiscard]] BigFloat Sqrt(const BigFloat& x);

		[[nodiscard]] BigFloat Floor(const BigFloat& x);

		[[nodiscard]] BigFloat Ceil(const BigFloat& x);

		[[nodiscard]] BigFloat Round(const BigFloat& x);

		[[nodiscard]] BigFloat Exp(const BigFloat& x);

		[[nodiscard]] BigFloat Exp2(const BigFloat& x);

		[[nodiscard]] BigFloat Log(const BigFloat& x);

		[[nodiscard]] BigFloat Log2(const BigFloat& x);

		[[nodiscard]] BigFloat Log10(const BigFloat& x);

		[[nodiscard]] BigFloat Cos(const BigFloat& x);

		[[nodiscard]] BigFloat Sin(const BigFloat& x);

		[[nodiscard]] BigFloat Tan(const BigFloat& x);

		[[nodiscard]] BigFloat Acos(const BigFloat& x);

		[[nodiscard]] BigFloat Asin(const BigFloat& x);

		[[nodiscard]] BigFloat Atan(const BigFloat& x);

		[[nodiscard]] BigFloat Cosh(const BigFloat& x);

		[[nodiscard]] BigFloat Sinh(const BigFloat& x);

		[[nodiscard]] BigFloat Tanh(const BigFloat& x);

		[[nodiscard]] BigFloat Ldexp(const BigFloat& x, int64 exp);

		[[nodiscard]] std::pair<BigFloat, int32> Frexp(const BigFloat& x);

		BigFloat Frexp(const BigFloat& x, int32& exp);

		[[nodiscard]] BigFloat Pow(const BigFloat& x, const BigFloat& y);

		[[nodiscard]] BigFloat Fmod(const BigFloat& x, const BigFloat& y);

		[[nodiscard]] BigFloat Atan2(const BigFloat& x, const BigFloat& y);

		[[nodiscard]] BigFloat Sign(const BigFloat& x);

		[[nodiscard]] BigFloat Radians(const BigFloat& x);

		[[nodiscard]] BigFloat Degrees(const BigFloat& x);

		[[nodiscard]] BigFloat Square(const BigFloat& x);

		[[nodiscard]] BigFloat Rsqrt(const BigFloat& x);

		[[nodiscard]] BigFloat Saturate(const BigFloat& x);
	}
	*/

	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			[[nodiscard]]
			BigFloat operator ""_bigF(unsigned long long int i);

			[[nodiscard]]
			BigFloat operator ""_bigF(const char* s, size_t length);

			[[nodiscard]]
			BigFloat operator ""_bigF(const char32* s, size_t length);
		}
	}
}

template <>
inline void std::swap(s3d::BigFloat& a, s3d::BigFloat& b) noexcept;

template <>
struct std::hash<s3d::BigFloat>
{
	[[nodiscard]]
	size_t operator()(const s3d::BigFloat& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/BigFloat.ipp"
