//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <iostream>
# include "Fwd.hpp"
# include "BigInt.hpp"
# include "String.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// 100 桁の有効桁数を持つ浮動小数点数型
	/// </summary>
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
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat(Integer i) : BigFloat(static_cast<int64>(i)) {}
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat(Integer i) : BigFloat(static_cast<uint64>(i)) {}
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat(Float f) : BigFloat(static_cast<long double>(f)) {}
		BigFloat(int64 f);
		BigFloat(uint64 f);
		BigFloat(long double f);
		BigFloat(const BigInt& number);
		explicit BigFloat(const std::string_view number);
		explicit BigFloat(const StringView number);
		BigFloat(const BigFloat& other);
		BigFloat(BigFloat&& other);
		~BigFloat();

		BigFloat& assign(int64 i);
		BigFloat& assign(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& assign(Integer i) { return assign(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& assign(Integer i) { return assign(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat& assign(Float f) { return assign(static_cast<long double>(f)); }
		BigFloat& assign(long double f);
		BigFloat& assign(const BigInt& number);
		BigFloat& assign(const std::string_view number);
		BigFloat& assign(const StringView number);
		BigFloat& assign(const BigFloat& other);
		BigFloat& assign(BigFloat&& other);

		BigFloat& operator =(int64 i);
		BigFloat& operator =(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator =(Integer i) { return assign(i); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator =(Integer i) { return assign(i); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat& operator =(Float f) { return assign(static_cast<long double>(f)); }
		BigFloat& operator =(long double f);
		BigFloat& operator =(const BigInt& number);
		BigFloat& operator =(const std::string_view number);
		BigFloat& operator =(const StringView number);
		BigFloat& operator =(const BigFloat& other);
		BigFloat& operator =(BigFloat&& other);

		[[nodiscard]] const BigFloat& operator +() const;
		BigFloat& operator ++();
		BigFloat operator ++(int);
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator +(Integer i) const { return operator +(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator +(Integer i) const { return operator +(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		[[nodiscard]] BigFloat operator +(Float f) const { return operator +(static_cast<long double>(f)); }
		[[nodiscard]] BigFloat operator +(int64 i) const;
		[[nodiscard]] BigFloat operator +(uint64 i) const;
		[[nodiscard]] BigFloat operator +(long double f) const;
		[[nodiscard]] BigFloat operator +(const BigInt& number) const;
		[[nodiscard]] BigFloat operator +(const BigFloat& number) const;
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator +=(Integer i) { return operator +=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator +=(Integer i) { return operator +=(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat& operator +=(Float f) { return operator +=(static_cast<long double>(f)); }
		BigFloat& operator +=(int64 i);
		BigFloat& operator +=(uint64 i);
		BigFloat& operator +=(long double f);
		BigFloat& operator +=(const BigInt& number);
		BigFloat& operator +=(const BigFloat& number);

		[[nodiscard]] BigFloat operator -() const &;
		[[nodiscard]] BigFloat operator -() &&;
		BigFloat& operator --();
		BigFloat operator --(int);
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator -(Integer i) const { return operator -(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator -(Integer i) const { return operator -(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		[[nodiscard]] BigFloat operator -(Float f) const { return operator -(static_cast<long double>(f)); }
		[[nodiscard]] BigFloat operator -(int64 i) const;
		[[nodiscard]] BigFloat operator -(uint64 i) const;
		[[nodiscard]] BigFloat operator -(long double f) const;
		[[nodiscard]] BigFloat operator -(const BigInt& number) const;
		[[nodiscard]] BigFloat operator -(const BigFloat& number) const;
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator -=(Integer i) { return operator -=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator -=(Integer i) { return operator -=(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat& operator -=(Float f) { return operator -=(static_cast<long double>(f)); }
		BigFloat& operator -=(int64 i);
		BigFloat& operator -=(uint64 i);
		BigFloat& operator -=(long double f);
		BigFloat& operator -=(const BigInt& number);
		BigFloat& operator -=(const BigFloat& number);

		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator *(Integer i) const { return operator *(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator *(Integer i) const { return operator *(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		[[nodiscard]] BigFloat operator *(Float f) const { return operator *(static_cast<long double>(f)); }
		[[nodiscard]] BigFloat operator *(int64 i) const;
		[[nodiscard]] BigFloat operator *(uint64 i) const;
		[[nodiscard]] BigFloat operator *(long double f) const;
		[[nodiscard]] BigFloat operator *(const BigInt& number) const;
		[[nodiscard]] BigFloat operator *(const BigFloat& number) const;
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator *=(Integer i) { return operator *=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator *=(Integer i) { return operator *=(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat& operator *=(Float f) { return operator *=(static_cast<long double>(f)); }
		BigFloat& operator *=(int64 i);
		BigFloat& operator *=(uint64 i);
		BigFloat& operator *=(long double f);
		BigFloat& operator *=(const BigInt& number);
		BigFloat& operator *=(const BigFloat& number);

		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator /(Integer i) const { return operator /(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] BigFloat operator /(Integer i) const { return operator /(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		[[nodiscard]] BigFloat operator /(Float f) const { return operator /(static_cast<long double>(f)); }
		[[nodiscard]] BigFloat operator /(int64 i) const;
		[[nodiscard]] BigFloat operator /(uint64 i) const;
		[[nodiscard]] BigFloat operator /(long double f) const;
		[[nodiscard]] BigFloat operator /(const BigInt& number) const;
		[[nodiscard]] BigFloat operator /(const BigFloat& number) const;
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator /=(Integer i) { return operator /=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator /=(Integer i) { return operator /=(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat& operator /=(Float f) { return operator /=(static_cast<long double>(f)); }
		BigFloat& operator /=(int64 i);
		BigFloat& operator /=(uint64 i);
		BigFloat& operator /=(long double f);
		BigFloat& operator /=(const BigInt& number);
		BigFloat& operator /=(const BigFloat& number);

		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] int32 compare(Integer i) const { return compare(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		[[nodiscard]] int32 compare(Integer i) const { return compare(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>* = nullptr>
		[[nodiscard]] int32 compare(Float f) const { return compare(static_cast<long double>(f)); }
		[[nodiscard]] int32 compare(int64 i) const;
		[[nodiscard]] int32 compare(uint64 i) const;
		[[nodiscard]] int32 compare(long double f) const;
		[[nodiscard]] int32 compare(const BigInt& number) const;
		[[nodiscard]] int32 compare(const BigFloat& number) const;

		[[nodiscard]] explicit operator bool() const;
		[[nodiscard]] bool isZero() const;
		[[nodiscard]] int32 sign() const;
		[[nodiscard]] BigFloat abs() const;

		[[nodiscard]] float asFloat() const;
		[[nodiscard]] double asDouble() const;
		[[nodiscard]] long double asLongDouble() const;

		[[nodiscard]] std::string stdStr() const;
		[[nodiscard]] std::wstring stdWstr() const;
		[[nodiscard]] String str() const;

		void swap(BigFloat& other) noexcept;

		//size_t hash() const;

		BigFloatDetail& detail();
		const BigFloatDetail& detail() const;
	};

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

	template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
	[[nodiscard]] inline BigFloat operator /(Integer a, const BigFloat& b)
	{
		return static_cast<int64>(a) / b;
	}

	template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
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

	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			[[nodiscard]] BigFloat operator ""_bigF(unsigned long long int i);

			[[nodiscard]] BigFloat operator ""_bigF(const char* number, size_t);

			[[nodiscard]] BigFloat operator ""_bigF(const char32* number, size_t);
		}
	}

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

	template <>
	struct IsBigFloat<BigFloat> : std::true_type {};

	template <>
	struct IsBigNumber<BigInt> : std::true_type {};

	template <>
	struct IsBigNumber<BigFloat> : std::true_type {};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const BigFloat& value);

	std::ostream& operator <<(std::ostream output, const BigFloat& value);

	std::wostream& operator <<(std::wostream& output, const BigFloat& value);

	std::istream& operator >>(std::istream& input, BigFloat& value);

	std::wistream& operator >>(std::wistream& input, BigFloat& value);
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

//namespace std
//{
//	template <>
//	struct hash<s3d::BigFloat>
//	{
//		[[nodiscard]] size_t operator()(const s3d::BigFloat& value) const noexcept
//		{
//			return value.hash();
//		}
//	};
//}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	void inline swap(s3d::BigFloat& a, s3d::BigFloat& b) noexcept
	{
		a.swap(b);
	}
}
