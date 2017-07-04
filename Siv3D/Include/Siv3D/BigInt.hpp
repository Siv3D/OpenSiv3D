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

// boost 1.64.0 workaround
# ifndef _HAS_AUTO_PTR_ETC
#	define _HAS_AUTO_PTR_ETC 1
# endif

# include <memory>
# include <iostream>
# include "Fwd.hpp"
# include "String.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// 多倍長整数型
	/// </summary>
	class BigInt
	{
	private:

		struct CBigInt;
		std::unique_ptr<CBigInt> pImpl;
		friend class BigFloat;
		friend BigInt operator /(int64 a, const BigInt& b);
		friend BigInt operator /(uint64 a, const BigInt& b);
		friend BigInt operator %(int64 a, const BigInt& b);
		friend BigInt operator %(uint64 a, const BigInt& b);

	public:

		BigInt() : BigInt(0) {}
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt(Integer i) : BigInt(static_cast<int64>(i)) {}
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt(Integer i) : BigInt(static_cast<uint64>(i)) {}
		BigInt(int64 i);
		BigInt(uint64 i);
		explicit BigInt(const char* number);
		explicit BigInt(const wchar* number);
		explicit BigInt(const std::string& number);
		explicit BigInt(const std::wstring& number);
		explicit BigInt(const String& number) : BigInt(number.str()) {}
		BigInt(const BigInt& other);
		BigInt(BigInt&& other);
		~BigInt();

		BigInt& assign(int64 i);
		BigInt& assign(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& assign(Integer i) { return assign(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& assign(Integer i) { return assign(static_cast<uint64>(i)); }
		BigInt& assign(const char* number);
		BigInt& assign(const wchar* number);
		BigInt& assign(const std::string& number);
		BigInt& assign(const std::wstring& number);
		BigInt& assign(const String& number) { return assign(number.str()); }
		BigInt& assign(const BigInt& other);
		BigInt& assign(BigInt&& other);

		BigInt& operator =(int64 i) { return assign(i); }
		BigInt& operator =(uint64 i) { return assign(i); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator =(Integer i) { return assign(i); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator =(Integer i) { return assign(i); }
		BigInt& operator =(const char* number) { return assign(number); }
		BigInt& operator =(const wchar* number) { return assign(number); }
		BigInt& operator =(const std::string& number) { return assign(number); }
		BigInt& operator =(const std::wstring& number) { return assign(number); }
		BigInt& operator =(const String& number) { return assign(number); }
		BigInt& operator =(const BigInt& other) { return assign(other); }
		BigInt& operator =(BigInt&& other) { return assign(std::move(other)); }

		const BigInt& operator +() const { return *this; }
		BigInt& operator ++();
		BigInt operator ++(int);
		BigInt operator +(int64 i) const;
		BigInt operator +(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator +(Integer i) const { return operator +(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator +(Integer i) const { return operator +(static_cast<uint64>(i)); }
		BigInt operator +(const BigInt& i) const;
		BigInt& operator +=(int64 i);
		BigInt& operator +=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator +=(Integer i) { return operator +=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator +=(Integer i) { return operator +=(static_cast<uint64>(i)); }
		BigInt& operator +=(const BigInt& i);

		BigInt operator -() const &;
		BigInt operator -() && ;
		BigInt& operator --();
		BigInt operator --(int);
		BigInt operator -(int64 i) const;
		BigInt operator -(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator -(Integer i) const { return operator -(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator -(Integer i) const { return operator -(static_cast<uint64>(i)); }
		BigInt operator -(const BigInt& i) const;
		BigInt& operator -=(int64 i);
		BigInt& operator -=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator -=(Integer i) { return operator -=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator -=(Integer i) { return operator -=(static_cast<uint64>(i)); }
		BigInt& operator -=(const BigInt& i);

		BigInt operator *(int64 i) const;
		BigInt operator *(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator *(Integer i) const { return operator *(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator *(Integer i) const { return operator *(static_cast<uint64>(i)); }
		BigInt operator *(const BigInt& i) const;
		BigInt& operator *=(int64 i);
		BigInt& operator *=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator *=(Integer i) { return operator *=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator *=(Integer i) { return operator *=(static_cast<uint64>(i)); }
		BigInt& operator *=(const BigInt& i);

		BigInt operator /(int64 i) const;
		BigInt operator /(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator /(Integer i) const { return operator /(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator /(Integer i) const { return operator /(static_cast<uint64>(i)); }
		BigInt operator /(const BigInt& i) const;
		BigInt& operator /=(int64 i);
		BigInt& operator /=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator /=(Integer i) { return operator /=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator /=(Integer i) { return operator /=(static_cast<uint64>(i)); }
		BigInt& operator /=(const BigInt& i);

		BigInt operator %(int64 i) const;
		BigInt operator %(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator %(Integer i) const { return operator %(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator %(Integer i) const { return operator %(static_cast<uint64>(i)); }
		BigInt operator %(const BigInt& i) const;
		BigInt& operator %=(int64 i);
		BigInt& operator %=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator %=(Integer i) { return operator %=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator %=(Integer i) { return operator %=(static_cast<uint64>(i)); }
		BigInt& operator %=(const BigInt& i);

		BigInt operator &(int64 i) const;
		BigInt operator &(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator &(Integer i) const { return operator &(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator &(Integer i) const { return operator &(static_cast<uint64>(i)); }
		BigInt operator &(const BigInt& i) const;
		BigInt& operator &=(int64 i);
		BigInt& operator &=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator &=(Integer i) { return operator &=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator &=(Integer i) { return operator &=(static_cast<uint64>(i)); }
		BigInt& operator &=(const BigInt& i);

		BigInt operator |(int64 i) const;
		BigInt operator |(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator |(Integer i) const { return operator |(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator |(Integer i) const { return operator |(static_cast<uint64>(i)); }
		BigInt operator |(const BigInt& i) const;
		BigInt& operator |=(int64 i);
		BigInt& operator |=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator |=(Integer i) { return operator |=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator |=(Integer i) { return operator |=(static_cast<uint64>(i)); }
		BigInt& operator |=(const BigInt& i);

		BigInt operator ^(int64 i) const;
		BigInt operator ^(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator ^(Integer i) const { return operator ^(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator ^(Integer i) const { return operator ^(static_cast<uint64>(i)); }
		BigInt operator ^(const BigInt& i) const;
		BigInt& operator ^=(int64 i);
		BigInt& operator ^=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator ^=(Integer i) { return operator ^=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator ^=(Integer i) { return operator ^=(static_cast<uint64>(i)); }
		BigInt& operator ^=(const BigInt& i);

		BigInt operator <<(int64 i) const;
		BigInt operator <<(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator <<(Integer i) const { return operator <<(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator <<(Integer i) const { return operator <<(static_cast<uint64>(i)); }
		BigInt& operator <<=(int64 i);
		BigInt& operator <<=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator <<=(Integer i) { return operator <<=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator <<=(Integer i) { return operator <<=(static_cast<uint64>(i)); }

		BigInt operator >>(int64 i) const;
		BigInt operator >>(uint64 i) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator >>(Integer i) const { return operator >> (static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator >>(Integer i) const { return operator >> (static_cast<uint64>(i)); }
		BigInt& operator >>=(int64 i);
		BigInt& operator >>=(uint64 i);
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator >>=(Integer i) { return operator >>=(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator >>=(Integer i) { return operator >>=(static_cast<uint64>(i)); }

		int32 compare(int64 i) const;
		int32 compare(uint64 i) const;
		int32 compare(long double f) const;
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		int32 compare(Integer i) const { return compare(static_cast<int64>(i)); }
		template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		int32 compare(Integer i) const { return compare(static_cast<uint64>(i)); }
		template <class Float, std::enable_if_t<std::is_floating_point<Float>::value>* = nullptr>
		int32 compare(Float f) const { return compare(static_cast<long double>(f)); }
		int32 compare(const BigInt& i) const;

		explicit operator bool() const;
		bool isZero() const;
		int32 sign() const;
		BigInt abs() const;
		BigInt pow(uint32 x) const;
		void divmod(const BigInt& x, BigInt& q, BigInt& r) const;
		uint32 lsb() const;

		bool bitTest(uint32 index) const;
		BigInt& bitSet(uint32 index, bool value);
		BigInt& bitFlip(uint32 index);

		int32 asInt32() const;
		int64 asInt64() const;
		uint32 asUint32() const;
		uint64 asUint64() const;
		size_t asSize_t() const;
		float asFloat() const;
		double asDouble() const;
		BigFloat asBigFloat() const;

		explicit operator size_t() const
		{
			return asSize_t();
		}

		explicit operator float() const
		{
			return asFloat();
		}

		explicit operator double() const
		{
			return asDouble();
		}

		explicit operator BigFloat() const;

		std::string stdStr() const;

		String str() const
		{
			const std::string t =stdStr();
			return String(t.begin(), t.end());
		}

		void swap(BigInt& other) noexcept;

		friend BigInt GCD(const BigInt&, const BigInt&);
		friend BigInt LCM(const BigInt&, const BigInt&);
	};

	template <class Type, std::enable_if_t<std::is_integral<Type>::value>* = nullptr>
	inline BigInt operator +(const Type& a, const BigInt& b)
	{
		return b + a;
	}

	template <class Type, std::enable_if_t<std::is_integral<Type>::value>* = nullptr>
	inline BigInt operator -(const Type& a, const BigInt& b)
	{
		return -b + a;
	}

	template <class Type, std::enable_if_t<std::is_integral<Type>::value>* = nullptr>
	inline BigInt operator *(const Type& a, const BigInt& b)
	{
		return b * a;
	}

	template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
	inline BigInt operator /(Integer a, const BigInt& b)
	{
		return static_cast<int64>(a) / b;
	}

	template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
	inline BigInt operator /(Integer a, const BigInt& b)
	{
		return static_cast<uint64>(a) / b;
	}

	BigInt operator /(int64 a, const BigInt& b);
	BigInt operator /(uint64 a, const BigInt& b);

	template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
	inline BigInt operator %(Integer a, const BigInt& b)
	{
		return static_cast<int64>(a) / b;
	}

	template <class Integer, std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
	inline BigInt operator %(Integer a, const BigInt& b)
	{
		return static_cast<uint64>(a) / b;
	}

	BigInt operator %(int64 a, const BigInt& b);
	BigInt operator %(uint64 a, const BigInt& b);

	template <class Type, std::enable_if_t<std::is_integral<Type>::value>* = nullptr>
	inline BigInt operator &(const Type& a, const BigInt& b)
	{
		return b & a;
	}

	template <class Type, std::enable_if_t<std::is_integral<Type>::value>* = nullptr>
	inline BigInt operator |(const Type& a, const BigInt& b)
	{
		return b | a;
	}

	template <class Type, std::enable_if_t<std::is_integral<Type>::value>* = nullptr>
	inline BigInt operator ^(const Type& a, const BigInt& b)
	{
		return b ^ a;
	}

	BigInt GCD(const BigInt& a, const BigInt& b);

	BigInt LCM(const BigInt& a, const BigInt& b);

	bool IsPrime(uint64 n);

	inline namespace literals
	{
		inline namespace bigint_literals
		{
			inline BigInt operator ""_big(unsigned long long int i)
			{
				return BigInt(i);
			}

			inline BigInt operator ""_big(const char* number, size_t)
			{
				return BigInt(number);
			}

			inline BigInt operator ""_big(const wchar* number, size_t)
			{
				return BigInt(number);
			}
		}
	}

	inline bool operator ==(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) == 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator ==(const BigInt& a, Number b)
	{
		return a.compare(b) == 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator ==(Number a, const BigInt& b)
	{
		return b.compare(a) == 0;
	}

	inline bool operator !=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) != 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator !=(const BigInt& a, Number b)
	{
		return a.compare(b) != 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator !=(Number a, const BigInt& b)
	{
		return b.compare(a) != 0;
	}

	inline bool operator <(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) < 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator <(const BigInt& a, Number b)
	{
		return a.compare(b) < 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator <(Number a, const BigInt& b)
	{
		return b.compare(a) < 0;
	}

	inline bool operator <=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) <= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator <=(const BigInt& a, Number b)
	{
		return a.compare(b) <= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator <=(Number a, const BigInt& b)
	{
		return b.compare(a) <= 0;
	}

	inline bool operator >(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) > 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator >(const BigInt& a, Number b)
	{
		return a.compare(b) > 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator >(Number a, const BigInt& b)
	{
		return b.compare(a) > 0;
	}

	inline bool operator >=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) >= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator >=(const BigInt& a, Number b)
	{
		return a.compare(b) >= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic<Number>::value>* = nullptr>
	inline bool operator >=(Number a, const BigInt& b)
	{
		return b.compare(a) >= 0;
	}

	template <class Type>
	struct IsBigInt : std::false_type {};

	template <>
	struct IsBigInt<BigInt> : std::true_type {};
}

namespace std
{
	void inline swap(s3d::BigInt& a, s3d::BigInt& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting BigInt
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const BigInt& i)
	{
		formatData.string.append(i.str());
	}

	inline std::ostream& operator <<(std::ostream& os, const BigInt& i)
	{
		return os << i.stdStr();
	}

	inline std::wostream& operator <<(std::wostream& os, const BigInt& i)
	{
		return os << i.str();
	}

	inline std::istream& operator >>(std::istream& is, BigInt& i)
	{
		std::string s;
		is >> s;
		i.assign(s);
		return is;
	}

	inline std::wistream& operator >>(std::wistream& is, BigInt& i)
	{
		std::wstring s;
		is >> s;
		i.assign(s);
		return is;
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::BigInt& i)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = S3DSTR("{") + tag + S3DSTR("}");

		f.writer().write(fmt, i.str().str());
	}
}
//
//////////////////////////////////////////////////////////////////////////////