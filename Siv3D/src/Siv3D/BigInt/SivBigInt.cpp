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

# include "BigIntDetail.hpp"
# include <Siv3D/BigFloat.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	BigInt::BigInt()
		: BigInt{ 0 }
	{

	}

	BigInt::BigInt(const int64 i)
		: pImpl{ std::make_unique<BigIntDetail>() }
	{
		assign(i);
	}

	BigInt::BigInt(const uint64 i)
		: pImpl{ std::make_unique<BigIntDetail>() }
	{
		assign(i);
	}

	BigInt::BigInt(const std::string_view number)
		: pImpl{ std::make_unique<BigIntDetail>() }
	{
		assign(number);
	}

	BigInt::BigInt(const StringView number)
		: pImpl{ std::make_unique<BigIntDetail>() }
	{
		assign(number);
	}

	BigInt::BigInt(const BigInt& other)
		: pImpl{ std::make_unique<BigIntDetail>() }
	{
		assign(other);
	}

	BigInt::BigInt(BigInt&& other) noexcept
		: pImpl{ std::move(other.pImpl) }
	{

	}

	BigInt::~BigInt()
	{

	}

	//////////////////////////////////////////////////
	//
	//	assign
	//
	//////////////////////////////////////////////////

	BigInt& BigInt::assign(const int64 i)
	{
		this->pImpl->data.assign(i);
		return *this;
	}

	BigInt& BigInt::assign(const uint64 i)
	{
		this->pImpl->data.assign(i);
		return *this;
	}

	BigInt& BigInt::assign(const std::string_view number)
	{
		this->pImpl->data.assign(number);
		return *this;
	}

	BigInt& BigInt::assign(const StringView number)
	{
		this->pImpl->data.assign(Unicode::NarrowAscii(number));
		return *this;
	}

	BigInt& BigInt::assign(const BigInt& other)
	{
		this->pImpl->data.assign(other.pImpl->data);
		return *this;
	}

	BigInt& BigInt::assign(BigInt&& other) noexcept
	{
		this->pImpl = std::move(other.pImpl);
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	=
	//
	//////////////////////////////////////////////////

	BigInt& BigInt::operator =(const int64 i)
	{
		return assign(i);
	}

	BigInt& BigInt::operator =(const uint64 i)
	{
		return assign(i);
	}

	BigInt& BigInt::operator =(const std::string_view number)
	{
		return assign(number);
	}

	BigInt& BigInt::operator =(const StringView number)
	{
		return assign(number);
	}

	BigInt& BigInt::operator =(const BigInt& other)
	{
		return assign(other);
	}

	BigInt& BigInt::operator =(BigInt&& other) noexcept
	{
		return assign(std::move(other));
	}

	//////////////////////////////////////////////////
	//
	//	+
	//
	//////////////////////////////////////////////////

	const BigInt& BigInt::operator +() const
	{
		return *this;
	}

	BigInt& BigInt::operator ++()
	{
		++this->pImpl->data;
		return *this;
	}

	BigInt BigInt::operator ++(const int)
	{
		BigInt tmp(*this);
		++this->pImpl->data;
		return tmp;
	}

	BigInt BigInt::operator +(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data + i;
		return tmp;
	}

	BigInt BigInt::operator +(const uint64 i) const
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

	BigInt& BigInt::operator +=(const int64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigInt& BigInt::operator +=(const uint64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigInt& BigInt::operator +=(const BigInt& i)
	{
		this->pImpl->data += i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	-
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator -() const&
	{
		BigInt tmp;
		tmp.pImpl->data = -(this->pImpl->data);
		return tmp;
	}

	BigInt BigInt::operator -()&&
	{
		this->pImpl->data = -(this->pImpl->data);
		return std::move(*this);
	}

	BigInt& BigInt::operator --()
	{
		--this->pImpl->data;
		return *this;
	}

	BigInt BigInt::operator --(const int)
	{
		BigInt tmp(*this);
		--this->pImpl->data;
		return tmp;
	}

	BigInt BigInt::operator -(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data - i;
		return tmp;
	}

	BigInt BigInt::operator -(const uint64 i) const
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

	BigInt& BigInt::operator -=(const int64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigInt& BigInt::operator -=(const uint64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigInt& BigInt::operator -=(const BigInt& i)
	{
		this->pImpl->data -= i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	*
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator *(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data * i;
		return tmp;
	}

	BigInt BigInt::operator *(const uint64 i) const
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

	BigInt& BigInt::operator *=(const int64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigInt& BigInt::operator *=(const uint64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigInt& BigInt::operator *=(const BigInt& i)
	{
		this->pImpl->data *= i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	/
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator /(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data / i;
		return tmp;
	}

	BigInt BigInt::operator /(const uint64 i) const
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

	BigInt& BigInt::operator /=(const int64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigInt& BigInt::operator /=(const uint64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigInt& BigInt::operator /=(const BigInt& i)
	{
		this->pImpl->data /= i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	%
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator %(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data % i;
		return tmp;
	}

	BigInt BigInt::operator %(const uint64 i) const
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

	BigInt& BigInt::operator %=(const int64 i)
	{
		this->pImpl->data %= i;
		return *this;
	}

	BigInt& BigInt::operator %=(const uint64 i)
	{
		this->pImpl->data %= i;
		return *this;
	}

	BigInt& BigInt::operator %=(const BigInt& i)
	{
		this->pImpl->data %= i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	&
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator &(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data & i;
		return tmp;
	}

	BigInt BigInt::operator &(const uint64 i) const
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

	BigInt& BigInt::operator &=(const int64 i)
	{
		this->pImpl->data &= i;
		return *this;
	}

	BigInt& BigInt::operator &=(const uint64 i)
	{
		this->pImpl->data &= i;
		return *this;
	}

	BigInt& BigInt::operator &=(const BigInt& i)
	{
		this->pImpl->data &= i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	|
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator |(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data | i;
		return tmp;
	}

	BigInt BigInt::operator |(const uint64 i) const
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

	BigInt& BigInt::operator |=(const int64 i)
	{
		this->pImpl->data |= i;
		return *this;
	}

	BigInt& BigInt::operator |=(const uint64 i)
	{
		this->pImpl->data |= i;
		return *this;
	}

	BigInt& BigInt::operator |=(const BigInt& i)
	{
		this->pImpl->data |= i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	^
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator ^(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data ^ i;
		return tmp;
	}

	BigInt BigInt::operator ^(const uint64 i) const
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

	BigInt& BigInt::operator ^=(const int64 i)
	{
		this->pImpl->data ^= i;
		return *this;
	}

	BigInt& BigInt::operator ^=(const uint64 i)
	{
		this->pImpl->data ^= i;
		return *this;
	}

	BigInt& BigInt::operator ^=(const BigInt& i)
	{
		this->pImpl->data ^= i.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	<<
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator <<(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data << i;
		return tmp;
	}

	BigInt BigInt::operator <<(const uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data << i;
		return tmp;
	}

	BigInt& BigInt::operator <<=(const int64 i)
	{
		this->pImpl->data <<= i;
		return *this;
	}

	BigInt& BigInt::operator <<=(const uint64 i)
	{
		this->pImpl->data <<= i;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	>>
	//
	//////////////////////////////////////////////////

	BigInt BigInt::operator >>(const int64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data >> i;
		return tmp;
	}

	BigInt BigInt::operator >>(const uint64 i) const
	{
		BigInt tmp;
		tmp.pImpl->data = this->pImpl->data >> i;
		return tmp;
	}

	BigInt& BigInt::operator >>=(const int64 i)
	{
		this->pImpl->data >>= i;
		return *this;
	}

	BigInt& BigInt::operator >>=(const uint64 i)
	{
		this->pImpl->data >>= i;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	compare
	//
	//////////////////////////////////////////////////

	int32 BigInt::compare(const int64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigInt::compare(const uint64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigInt::compare(const long double f) const
	{
		return this->pImpl->data.compare(f);
	}

	int32 BigInt::compare(const BigInt& i) const
	{
		return this->pImpl->data.compare(i.pImpl->data);
	}

	//////////////////////////////////////////////////
	//
	//	utilities
	//
	//////////////////////////////////////////////////

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

	BigInt BigInt::pow(const uint32 x) const
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

	bool BigInt::bitTest(const uint32 index) const
	{
		return boost::multiprecision::bit_test(this->pImpl->data, index);
	}

	BigInt& BigInt::bitSet(const uint32 index, bool value)
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

	BigInt& BigInt::bitFlip(const uint32 index)
	{
		boost::multiprecision::bit_flip(this->pImpl->data, index);
		return *this;
	}

	void BigInt::swap(BigInt& other) noexcept
	{
		return this->pImpl->data.swap(other.pImpl->data);
	}

	size_t BigInt::hash() const
	{
		return std::hash<boost::multiprecision::cpp_int>{}(this->pImpl->data);
	}

	//////////////////////////////////////////////////
	//
	//	conversions
	//
	//////////////////////////////////////////////////

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

	size_t BigInt::asSize_t() const
	{
		return this->pImpl->data.convert_to<size_t>();
	}

	float BigInt::asFloat() const
	{
		return this->pImpl->data.convert_to<float>();
	}

	double BigInt::asDouble() const
	{
		return this->pImpl->data.convert_to<double>();
	}

	BigFloat BigInt::asBigFloat() const
	{
		return BigFloat(pImpl->data.str());
	}

	BigInt::operator size_t() const
	{
		return this->pImpl->data.convert_to<size_t>();
	}

	BigInt::operator float() const
	{
		return this->pImpl->data.convert_to<float>();
	}

	BigInt::operator double() const
	{
		return this->pImpl->data.convert_to<double>();
	}

	BigInt::operator BigFloat() const
	{
		return asBigFloat();
	}

	std::string BigInt::to_string() const
	{
		return pImpl->data.str();
	}

	std::wstring BigInt::to_wstring() const
	{
		const std::string str = pImpl->data.str();

		return std::wstring(str.begin(), str.end());
	}

	String BigInt::str() const
	{
		const std::string t = to_string();

		return String(t.begin(), t.end());
	}

	void Formatter(FormatData& formatData, const BigInt& value)
	{
		formatData.string.append(value.str());
	}

	//////////////////////////////////////////////////
	//
	//	detail
	//
	//////////////////////////////////////////////////
	
	BigInt::BigIntDetail& BigInt::_detail()
	{
		return *pImpl;
	}

	const BigInt::BigIntDetail& BigInt::_detail() const
	{
		return *pImpl;
	}

	//////////////////////////////////////////////////
	//
	//	_divI
	//
	//////////////////////////////////////////////////

	BigInt BigInt::_divI(const int64 a) const
	{
		BigInt tmp;
		tmp.pImpl->data = (a / pImpl->data);
		return tmp;
	}

	BigInt BigInt::_divI(const uint64 a) const
	{
		BigInt tmp;
		tmp.pImpl->data = (a / pImpl->data);
		return tmp;
	}

	//////////////////////////////////////////////////
	//
	//	_modI
	//
	//////////////////////////////////////////////////

	BigInt BigInt::_modI(const int64 a) const
	{
		BigInt tmp;
		tmp.pImpl->data = (a % pImpl->data);
		return tmp;
	}

	BigInt BigInt::_modI(const uint64 a) const
	{
		BigInt tmp;
		tmp.pImpl->data = (a % pImpl->data);
		return tmp;
	}

	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			BigInt operator ""_big(const char* s)
			{
				return BigInt{ std::string_view{ s } };
			}
		}
	}

	namespace Math
	{
		BigInt GCD(const BigInt& a, const BigInt& b)
		{
			BigInt result;
			result._detail().data = boost::multiprecision::gcd(a._detail().data, b._detail().data);
			return result;
		}

		BigInt LCM(const BigInt& a, const BigInt& b)
		{
			BigInt result;
			result._detail().data = boost::multiprecision::lcm(a._detail().data, b._detail().data);
			return result;
		}
	}
}
