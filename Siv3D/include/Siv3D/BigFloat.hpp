//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

// boost 1.65.0 workaround
# ifndef _HAS_AUTO_PTR_ETC
#	define _HAS_AUTO_PTR_ETC 1
# endif

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

		struct CBigFloat;
		std::unique_ptr<CBigFloat> pImpl;

		friend BigFloat operator /(int64 a, const BigFloat& b);
		friend BigFloat operator /(uint64 a, const BigFloat& b);
		friend BigFloat operator /(long double a, const BigFloat& b);

	public:

		BigFloat() : BigFloat(0.0) {}
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
		explicit BigFloat(const char* number);
		explicit BigFloat(const char32* number);
		explicit BigFloat(const std::string& number);
		explicit BigFloat(const std::wstring& number);
		explicit BigFloat(const String& number);
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
		BigFloat& assign(const char* number);
		BigFloat& assign(const char32* number);
		BigFloat& assign(const std::string& number);
		BigFloat& assign(const std::wstring& number);
		BigFloat& assign(const String& number);
		BigFloat& assign(const BigFloat& other);
		BigFloat& assign(BigFloat&& other);

		BigFloat& operator =(int64 i) { return assign(i); }
		BigFloat& operator =(uint64 i) { return assign(i); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator =(Integer i) { return assign(i); }
		template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
		BigFloat& operator =(Integer i) { return assign(i); }
		template <class Float, std::enable_if_t<(std::is_floating_point_v<Float>)>* = nullptr>
		BigFloat& operator =(Float f) { return assign(static_cast<long double>(f)); }
		BigFloat& operator =(long double f) { return assign(f); }
		BigFloat& operator =(const BigInt& number) { return assign(number); }
		BigFloat& operator =(const char* number) { return assign(number); }
		BigFloat& operator =(const char32* number) { return assign(number); }
		BigFloat& operator =(const std::string& number) { return assign(number); }
		BigFloat& operator =(const std::wstring& number) { return assign(number); }
		BigFloat& operator =(const String& number) { return assign(number); }
		BigFloat& operator =(const BigFloat& other) { return assign(other); }
		BigFloat& operator =(BigFloat&& other) { return assign(std::move(other)); }

		[[nodiscard]] const BigFloat& operator +() const { return *this; }
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

		[[nodiscard]] const BigFloat& operator -() const { return *this; }
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

		CBigFloat& detail();
		const CBigFloat& detail() const;
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

	inline namespace literals
	{
		inline namespace bigfloat_literals
		{
			[[nodiscard]] inline BigFloat operator ""_bigF(unsigned long long int i)
			{
				return BigFloat(i);
			}

			[[nodiscard]] inline BigFloat operator ""_bigF(const char* number, size_t)
			{
				return BigFloat(number);
			}

			[[nodiscard]] inline BigFloat operator ""_bigF(const char32* number, size_t)
			{
				return BigFloat(number);
			}
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
}

namespace std
{
	void inline swap(s3d::BigFloat& a, s3d::BigFloat& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}

namespace s3d
{
	void Formatter(FormatData& formatData, const BigFloat& value);

	std::ostream& operator <<(std::ostream output, const BigFloat& value);

	std::wostream& operator <<(std::wostream& output, const BigFloat& value);

	std::istream& operator >>(std::istream& input, BigFloat& value);

	std::wistream& operator >>(std::wistream& input, BigFloat& value);
}

//namespace fmt
//{
//	template <class ArgFormatter>
//	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::BigFloat& value)
//	{
//		const auto tag = s3d::detail::GetTag(format_str);
//
//		const auto fmt = S3DSTR("{") + tag + S3DSTR("}");
//
//		f.writer().write(fmt, value.str().str());
//	}
//}
