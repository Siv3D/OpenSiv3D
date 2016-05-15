//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/BigInt.hpp>
# include "CBigInt.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		Constructor
	//
	////////////////////////////////////////////////////////////////

	BigInt::BigInt(int64 i)
		: pImpl(std::make_unique<CBigInt>())
	{
		assign(i);
	}

	BigInt::BigInt(uint64 i)
		: pImpl(std::make_unique<CBigInt>())
	{
		assign(i);
	}

	BigInt::BigInt(const char* number)
		: pImpl(std::make_unique<CBigInt>())
	{
		assign(number);
	}

	BigInt::BigInt(const wchar* number)
		: pImpl(std::make_unique<CBigInt>())
	{
		assign(number);
	}

	BigInt::BigInt(const std::string& number)
		: pImpl(std::make_unique<CBigInt>())
	{
		assign(number);
	}

	BigInt::BigInt(const std::wstring& number)
		: pImpl(std::make_unique<CBigInt>())
	{
		assign(number);
	}

	BigInt::BigInt(const BigInt& other)
		: pImpl(std::make_unique<CBigInt>())
	{
		assign(other);
	}

	BigInt::BigInt(BigInt&& other)
		: pImpl(std::move(other.pImpl))
	{

	}

	////////////////////////////////////////////////////////////////
	//
	//		Destructor
	//
	////////////////////////////////////////////////////////////////

	BigInt::~BigInt()
	{

	}

	////////////////////////////////////////////////////////////////
	//
	//		assign
	//
	////////////////////////////////////////////////////////////////

	BigInt& BigInt::assign(int64 i)
	{
		this->pImpl->data.assign(i);
		return *this;
	}

	BigInt& BigInt::assign(uint64 i)
	{
		this->pImpl->data.assign(i);
		return *this;
	}

	BigInt& BigInt::assign(const char* number)
	{
		this->pImpl->data.assign(number);
		return *this;
	}

	BigInt& BigInt::assign(const wchar* number)
	{
		this->pImpl->data.assign(std::string(number, number + std::wcslen(number)));
		return *this;
	}

	BigInt& BigInt::assign(const std::string& number)
	{
		this->pImpl->data.assign(number);
		return *this;
	}

	BigInt& BigInt::assign(const std::wstring& number)
	{
		this->pImpl->data.assign(std::string(number.begin(), number.end()));
		return *this;
	}

	BigInt& BigInt::assign(const BigInt& other)
	{
		this->pImpl->data.assign(other.pImpl->data);
		return *this;
	}

	BigInt& BigInt::assign(BigInt&& other)
	{
		this->pImpl = std::move(other.pImpl);
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		+, ++
	//
	////////////////////////////////////////////////////////////////

	BigInt& BigInt::operator ++()
	{
		++this->pImpl->data;
		return *this;
	}

	BigInt BigInt::operator ++(int)
	{
		BigInt tmp(*this);
		++this->pImpl->data;
		return tmp;
	}

	BigInt BigInt::operator +(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data + i;
		return tmp;
	}

	BigInt BigInt::operator +(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data + i;
		return tmp;
	}

	BigInt BigInt::operator +(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data + i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator +=(int64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigInt& BigInt::operator +=(uint64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigInt& BigInt::operator +=(const BigInt& i)
	{
		this->pImpl->data += i.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		-, --
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator -() const &
	{
		BigInt tmp;
		tmp.pImpl->data = -(this->pImpl->data);
		return tmp;
	}

	BigInt BigInt::operator -() &&
	{
		this->pImpl->data = -(this->pImpl->data);
		return std::move(*this);
	}

	BigInt& BigInt::operator --()
	{
		--this->pImpl->data;
		return *this;
	}

	BigInt BigInt::operator --(int)
	{
		BigInt tmp(*this);
		--this->pImpl->data;
		return tmp;
	}

	BigInt BigInt::operator -(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data - i;
		return tmp;
	}

	BigInt BigInt::operator -(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data - i;
		return tmp;
	}

	BigInt BigInt::operator -(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data - i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator -=(int64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigInt& BigInt::operator -=(uint64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigInt& BigInt::operator -=(const BigInt& i)
	{
		this->pImpl->data -= i.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		*
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator *(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data * i;
		return tmp;
	}

	BigInt BigInt::operator *(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data * i;
		return tmp;
	}

	BigInt BigInt::operator *(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data * i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator *=(int64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigInt& BigInt::operator *=(uint64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigInt& BigInt::operator *=(const BigInt& i)
	{
		this->pImpl->data *= i.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		/
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator /(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data / i;
		return tmp;
	}

	BigInt BigInt::operator /(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data / i;
		return tmp;
	}

	BigInt BigInt::operator /(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data / i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator /=(int64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigInt& BigInt::operator /=(uint64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigInt& BigInt::operator /=(const BigInt& i)
	{
		this->pImpl->data /= i.pImpl->data;
		return *this;
	}

	BigInt operator /(int64 a, const BigInt& b)
	{
		BigInt tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}

	BigInt operator /(uint64 a, const BigInt& b)
	{
		BigInt tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}

	////////////////////////////////////////////////////////////////
	//
	//		%
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator %(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data % i;
		return tmp;
	}

	BigInt BigInt::operator %(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data % i;
		return tmp;
	}

	BigInt BigInt::operator %(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data % i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator %=(int64 i)
	{
		this->pImpl->data %= i;
		return *this;
	}

	BigInt& BigInt::operator %=(uint64 i)
	{
		this->pImpl->data %= i;
		return *this;
	}

	BigInt& BigInt::operator %=(const BigInt& i)
	{
		this->pImpl->data %= i.pImpl->data;
		return *this;
	}

	BigInt operator %(int64 a, const BigInt& b)
	{
		BigInt tmp;
		tmp.pImpl->data = a % b.pImpl->data;
		return tmp;
	}

	BigInt operator %(uint64 a, const BigInt& b)
	{
		BigInt tmp;
		tmp.pImpl->data = a % b.pImpl->data;
		return tmp;
	}

	////////////////////////////////////////////////////////////////
	//
	//		&
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator &(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data & i;
		return tmp;
	}

	BigInt BigInt::operator &(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data & i;
		return tmp;
	}

	BigInt BigInt::operator &(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data & i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator &=(int64 i)
	{
		this->pImpl->data &= i;
		return *this;
	}

	BigInt& BigInt::operator &=(uint64 i)
	{
		this->pImpl->data &= i;
		return *this;
	}

	BigInt& BigInt::operator &=(const BigInt& i)
	{
		this->pImpl->data &= i.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		|
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator |(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data | i;
		return tmp;
	}

	BigInt BigInt::operator |(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data | i;
		return tmp;
	}

	BigInt BigInt::operator |(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data | i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator |=(int64 i)
	{
		this->pImpl->data |= i;
		return *this;
	}

	BigInt& BigInt::operator |=(uint64 i)
	{
		this->pImpl->data |= i;
		return *this;
	}

	BigInt& BigInt::operator |=(const BigInt& i)
	{
		this->pImpl->data |= i.pImpl->data;
		return *this;
	}

	BigInt BigInt::operator ^(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data ^ i;
		return tmp;
	}

	////////////////////////////////////////////////////////////////
	//
	//		^
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator ^(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data ^ i;
		return tmp;
	}

	BigInt BigInt::operator ^(const BigInt& i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data ^ i.pImpl->data;
		return tmp;
	}

	BigInt& BigInt::operator ^=(int64 i)
	{
		this->pImpl->data ^= i;
		return *this;
	}

	BigInt& BigInt::operator ^=(uint64 i)
	{
		this->pImpl->data ^= i;
		return *this;
	}

	BigInt& BigInt::operator ^=(const BigInt& i)
	{
		this->pImpl->data ^= i.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		<<
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator <<(int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data << i;
		return tmp;
	}

	BigInt BigInt::operator <<(uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data << i;
		return tmp;
	}

	BigInt& BigInt::operator <<=(int64 i)
	{
		this->pImpl->data <<= i;
		return *this;
	}

	BigInt& BigInt::operator <<=(uint64 i)
	{
		this->pImpl->data <<= i;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		>>
	//
	////////////////////////////////////////////////////////////////

	BigInt BigInt::operator >> (int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data >> i;
		return tmp;
	}

	BigInt BigInt::operator >> (uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data >> i;
		return tmp;
	}

	BigInt& BigInt::operator >>=(int64 i)
	{
		this->pImpl->data >>= i;
		return *this;
	}

	BigInt& BigInt::operator >>=(uint64 i)
	{
		this->pImpl->data >>= i;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		compare
	//
	////////////////////////////////////////////////////////////////

	int32 BigInt::compare(int64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigInt::compare(uint64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigInt::compare(long double f) const
	{
		return this->pImpl->data.compare(f);
	}

	int32 BigInt::compare(const BigInt& i) const
	{
		return this->pImpl->data.compare(i.pImpl->data);
	}

	////////////////////////////////////////////////////////////////
	//
	//		math
	//
	////////////////////////////////////////////////////////////////

	BigInt::operator bool() const
	{
		return this->pImpl->data.operator bool();
	}

	bool BigInt::isZero() const
	{
		return this->pImpl->data.is_zero();
	}

	int32 BigInt::sign() const
	{
		return this->pImpl->data.sign();
	}

	BigInt BigInt::abs() const
	{
		BigInt tmp;
		tmp.pImpl->data = boost::multiprecision::abs(this->pImpl->data);
		return tmp;
	}

	BigInt BigInt::pow(uint32 x) const
	{
		BigInt tmp;
		tmp.pImpl->data = boost::multiprecision::pow(this->pImpl->data, x);
		return tmp;
	}

	void BigInt::divmod(const BigInt& x, BigInt& q, BigInt& r) const
	{
		boost::multiprecision::divide_qr(this->pImpl->data, x.pImpl->data, q.pImpl->data, r.pImpl->data);
	}

	uint32 BigInt::lsb() const
	{
		return boost::multiprecision::lsb(this->pImpl->data);
	}

	////////////////////////////////////////////////////////////////
	//
	//		bitTest
	//
	////////////////////////////////////////////////////////////////

	bool BigInt::bitTest(uint32 index) const
	{
		return boost::multiprecision::bit_test(this->pImpl->data, index);
	}

	BigInt& BigInt::bitSet(uint32 index, bool value)
	{
		if (value)
		{
			boost::multiprecision::bit_set(this->pImpl->data, index);
		}
		else
		{
			boost::multiprecision::bit_unset(this->pImpl->data, index);
		}

		return *this;
	}

	BigInt& BigInt::bitFlip(uint32 index)
	{
		boost::multiprecision::bit_flip(this->pImpl->data, index);
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		conversion
	//
	////////////////////////////////////////////////////////////////

	int32 BigInt::asInt32() const
	{
		return this->pImpl->data.convert_to<int32>();
	}

	int64 BigInt::asInt64() const
	{
		return this->pImpl->data.convert_to<int64>();
	}

	uint32 BigInt::asUint32() const
	{
		return this->pImpl->data.convert_to<uint32>();
	}

	uint64 BigInt::asUint64() const
	{
		return this->pImpl->data.convert_to<uint64>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		string
	//
	////////////////////////////////////////////////////////////////

	std::string BigInt::stdStr() const
	{
		return pImpl->data.str();
	}

	String BigInt::str() const
	{
		const std::string t = pImpl->data.str();
		return String(t.begin(), t.end());
	}

	////////////////////////////////////////////////////////////////
	//
	//		swap
	//
	////////////////////////////////////////////////////////////////

	void BigInt::swap(BigInt& other) noexcept
	{
		return this->pImpl->data.swap(other.pImpl->data);
	}

	////////////////////////////////////////////////////////////////
	//
	//		GCD, LCM
	//
	////////////////////////////////////////////////////////////////

	BigInt GCD(const BigInt& a, const BigInt& b)
	{
		BigInt result;
		result.pImpl->data = boost::multiprecision::gcd(a.pImpl->data, b.pImpl->data);
		return result;
	}

	BigInt LCM(const BigInt& a, const BigInt& b)
	{
		BigInt result;
		result.pImpl->data = boost::multiprecision::lcm(a.pImpl->data, b.pImpl->data);
		return result;
	}
}
