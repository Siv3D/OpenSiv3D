//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <iostream>
# include "Fwd.hpp"

namespace s3d
{
	class BigInt
	{
	private:

		struct CBigInt;
		std::unique_ptr<CBigInt> pImpl;

	public:

		BigInt() : BigInt(0) {}
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt(Integer i) : BigInt(static_cast<int64>(i)) {}
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt(Integer i) : BigInt(static_cast<uint64>(i)) {}
		BigInt(int64 i);
		BigInt(uint64 i);
		BigInt(const char* number);
		BigInt(const wchar* number);
		BigInt(const std::string& number);
		BigInt(const std::wstring& number);
		BigInt(const BigInt& other);
		BigInt(BigInt&& other);
		~BigInt();

		BigInt& assign(int64 i);
		BigInt& assign(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& assign(Integer i) { return assign(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& assign(Integer i) { return assign(static_cast<uint64>(i)); }
		BigInt& assign(const char* number);
		BigInt& assign(const wchar* number);
		BigInt& assign(const std::string& number);
		BigInt& assign(const std::wstring& number);
		BigInt& assign(const BigInt& other);
		BigInt& assign(BigInt&& other);

		BigInt& operator =(int64 i) { return assign(i); }
		BigInt& operator =(uint64 i) { return assign(i); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator =(Integer i) { return assign(i); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator =(Integer i) { return assign(i); }
		BigInt& operator =(const char* number) { return assign(number); }
		BigInt& operator =(const wchar* number) { return assign(number); }
		BigInt& operator =(const std::string& number) { return assign(number); }
		BigInt& operator =(const std::wstring& number) { return assign(number); }
		BigInt& operator =(const BigInt& other) { return assign(other); }
		BigInt& operator =(BigInt&& other) { return assign(std::move(other)); }

		const BigInt& operator +() const { return *this; }
		BigInt& operator ++();
		BigInt operator ++(int);
		BigInt operator +(int64 i) const;
		BigInt operator +(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator +(Integer i) const { return operator +(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator +(Integer i) const { return operator +(static_cast<uint64>(i)); }
		BigInt operator +(const BigInt& i) const;
		BigInt& operator +=(int64 i);
		BigInt& operator +=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator +=(Integer i) { return operator +=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator +=(Integer i) { return operator +=(static_cast<uint64>(i)); }
		BigInt& operator +=(const BigInt& i);

		BigInt operator -() const &;
		BigInt operator -() && ;
		BigInt& operator --();
		BigInt operator --(int);
		BigInt operator -(int64 i) const;
		BigInt operator -(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator -(Integer i) const { return operator -(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator -(Integer i) const { return operator -(static_cast<uint64>(i)); }
		BigInt operator -(const BigInt& i) const;
		BigInt& operator -=(int64 i);
		BigInt& operator -=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator -=(Integer i) { return operator -=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator -=(Integer i) { return operator -=(static_cast<uint64>(i)); }
		BigInt& operator -=(const BigInt& i);

		BigInt operator *(int64 i) const;
		BigInt operator *(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator *(Integer i) const { return operator *(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator *(Integer i) const { return operator *(static_cast<uint64>(i)); }
		BigInt operator *(const BigInt& i) const;
		BigInt& operator *=(int64 i);
		BigInt& operator *=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator *=(Integer i) { return operator *=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator *=(Integer i) { return operator *=(static_cast<uint64>(i)); }
		BigInt& operator *=(const BigInt& i);

		BigInt operator /(int64 i) const;
		BigInt operator /(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator /(Integer i) const { return operator /(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator /(Integer i) const { return operator /(static_cast<uint64>(i)); }
		BigInt operator /(const BigInt& i) const;
		BigInt& operator /=(int64 i);
		BigInt& operator /=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator /=(Integer i) { return operator /=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator /=(Integer i) { return operator /=(static_cast<uint64>(i)); }
		BigInt& operator /=(const BigInt& i);

		BigInt operator %(int64 i) const;
		BigInt operator %(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator %(Integer i) const { return operator %(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator %(Integer i) const { return operator %(static_cast<uint64>(i)); }
		BigInt operator %(const BigInt& i) const;
		BigInt& operator %=(int64 i);
		BigInt& operator %=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator %=(Integer i) { return operator %=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator %=(Integer i) { return operator %=(static_cast<uint64>(i)); }
		BigInt& operator %=(const BigInt& i);

		BigInt operator &(int64 i) const;
		BigInt operator &(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator &(Integer i) const { return operator &(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator &(Integer i) const { return operator &(static_cast<uint64>(i)); }
		BigInt operator &(const BigInt& i) const;
		BigInt& operator &=(int64 i);
		BigInt& operator &=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator &=(Integer i) { return operator &=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator &=(Integer i) { return operator &=(static_cast<uint64>(i)); }
		BigInt& operator &=(const BigInt& i);

		BigInt operator |(int64 i) const;
		BigInt operator |(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator |(Integer i) const { return operator |(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator |(Integer i) const { return operator |(static_cast<uint64>(i)); }
		BigInt operator |(const BigInt& i) const;
		BigInt& operator |=(int64 i);
		BigInt& operator |=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator |=(Integer i) { return operator |=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator |=(Integer i) { return operator |=(static_cast<uint64>(i)); }
		BigInt& operator |=(const BigInt& i);

		BigInt operator ^(int64 i) const;
		BigInt operator ^(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator ^(Integer i) const { return operator ^(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator ^(Integer i) const { return operator ^(static_cast<uint64>(i)); }
		BigInt operator ^(const BigInt& i) const;
		BigInt& operator ^=(int64 i);
		BigInt& operator ^=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator ^=(Integer i) { return operator ^=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator ^=(Integer i) { return operator ^=(static_cast<uint64>(i)); }
		BigInt& operator ^=(const BigInt& i);

		BigInt operator <<(int64 i) const;
		BigInt operator <<(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator <<(Integer i) const { return operator <<(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator <<(Integer i) const { return operator <<(static_cast<uint64>(i)); }
		BigInt& operator <<=(int64 i);
		BigInt& operator <<=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator <<=(Integer i) { return operator <<=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator <<=(Integer i) { return operator <<=(static_cast<uint64>(i)); }

		BigInt operator >>(int64 i) const;
		BigInt operator >>(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator >>(Integer i) const { return operator >> (static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt operator >>(Integer i) const { return operator >> (static_cast<uint64>(i)); }
		BigInt& operator >>=(int64 i);
		BigInt& operator >>=(uint64 i);
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator >>=(Integer i) { return operator >>=(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		BigInt& operator >>=(Integer i) { return operator >>=(static_cast<uint64>(i)); }

		int32 compare(int64 i) const;
		int32 compare(uint64 i) const;
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && std::is_signed<Integer>::value)>* = nullptr>
		int32 compare(Integer i) const { return compare(static_cast<int64>(i)); }
		template <class Integer, typename std::enable_if_t<(std::is_integral<Integer>::value && !std::is_signed<Integer>::value)>* = nullptr>
		int32 compare(Integer i) const { return compare(static_cast<uint64>(i)); }
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

		std::string stdStr() const;
		std::wstring str() const;

		void swap(BigInt& other);

		friend BigInt GCD(const BigInt&, const BigInt&);
		friend BigInt LCM(const BigInt&, const BigInt&);
	};

	inline bool operator ==(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) == 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator ==(const BigInt& a, Integer b)
	{
		return a.compare(b) == 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator ==(Integer a, const BigInt& b)
	{
		return b.compare(a) == 0;
	}

	inline bool operator !=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) != 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator !=(const BigInt& a, Integer b)
	{
		return a.compare(b) != 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator !=(Integer a, const BigInt& b)
	{
		return b.compare(a) != 0;
	}

	inline bool operator <(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) < 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator <(const BigInt& a, Integer b)
	{
		return a.compare(b) < 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator <(Integer a, const BigInt& b)
	{
		return b.compare(a) < 0;
	}

	inline bool operator <=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) <= 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator <=(const BigInt& a, Integer b)
	{
		return a.compare(b) <= 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator <=(Integer a, const BigInt& b)
	{
		return b.compare(a) <= 0;
	}

	inline bool operator >(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) > 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator >(const BigInt& a, Integer b)
	{
		return a.compare(b) > 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator >(Integer a, const BigInt& b)
	{
		return b.compare(a) > 0;
	}

	inline bool operator >=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) >= 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator >=(const BigInt& a, Integer b)
	{
		return a.compare(b) >= 0;
	}

	template <class Integer, typename std::enable_if_t<std::is_integral<Integer>::value>* = nullptr>
	inline bool operator >=(Integer a, const BigInt& b)
	{
		return b.compare(a) >= 0;
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

	BigInt GCD(const BigInt& a, const BigInt& b);

	BigInt LCM(const BigInt& a, const BigInt& b);
}

namespace std
{
	void inline swap(s3d::BigInt& a, s3d::BigInt& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}
