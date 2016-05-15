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

# include <Siv3D/BigFloat.hpp>
# include "CBigFloat.hpp"
# include "../BigInt/CBigInt.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		Constructor
	//
	////////////////////////////////////////////////////////////////

	BigFloat::BigFloat(const int64 i)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(i);
	}

	BigFloat::BigFloat(const uint64 i)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(i);
	}

	BigFloat::BigFloat(const long double f)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(f);
	}

	BigFloat::BigFloat(const BigInt& number)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const char* number)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const wchar* number)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const std::string& number)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const std::wstring& number)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const BigFloat& other)
		: pImpl(std::make_unique<CBigFloat>())
	{
		assign(other);
	}

	BigFloat::BigFloat(BigFloat&& other)
		: pImpl(std::move(other.pImpl))
	{

	}

	////////////////////////////////////////////////////////////////
	//
	//		Destructor
	//
	////////////////////////////////////////////////////////////////
	
	BigFloat::~BigFloat()
	{

	}

	////////////////////////////////////////////////////////////////
	//
	//		assign
	//
	////////////////////////////////////////////////////////////////

	BigFloat& BigFloat::assign(const int64 i)
	{
		this->pImpl->data.assign(i);
		return *this;
	}

	BigFloat& BigFloat::assign(const uint64 i)
	{
		this->pImpl->data.assign(i);
		return *this;
	}

	BigFloat& BigFloat::assign(const long double f)
	{
		this->pImpl->data.assign(f);
		return *this;
	}

	BigFloat& BigFloat::assign(const BigInt& number)
	{
		this->pImpl->data.assign(number.pImpl->data);
		return *this;
	}

	BigFloat& BigFloat::assign(const char* number)
	{
		this->pImpl->data.assign(number);
		return *this;
	}

	BigFloat& BigFloat::assign(const wchar* number)
	{
		this->pImpl->data.assign(std::string(number, number + std::wcslen(number)));
		return *this;
	}

	BigFloat& BigFloat::assign(const std::string& number)
	{
		this->pImpl->data.assign(number);
		return *this;
	}

	BigFloat& BigFloat::assign(const std::wstring& number)
	{
		this->pImpl->data.assign(std::string(number.begin(), number.end()));
		return *this;
	}

	BigFloat& BigFloat::assign(const BigFloat& other)
	{
		this->pImpl->data.assign(other.pImpl->data);
		return *this;
	}

	BigFloat& BigFloat::assign(BigFloat&& other)
	{
		this->pImpl = std::move(other.pImpl);
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		+, ++
	//
	////////////////////////////////////////////////////////////////

	BigFloat& BigFloat::operator ++()
	{
		++this->pImpl->data;
		return *this;
	}

	BigFloat BigFloat::operator ++(int)
	{
		BigFloat tmp(*this);
		++this->pImpl->data;
		return tmp;
	}

	BigFloat BigFloat::operator +(const int64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data + i;
		return tmp;
	}

	BigFloat BigFloat::operator +(const uint64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data + i;
		return tmp;
	}

	BigFloat BigFloat::operator +(const long double f) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data + f;
		return tmp;
	}

	BigFloat BigFloat::operator +(const BigInt& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data + CBigFloat::value_type(number.pImpl->data);
		return tmp;
	}

	BigFloat BigFloat::operator +(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data + number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator +=(int64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigFloat& BigFloat::operator +=(uint64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigFloat& BigFloat::operator +=(long double f)
	{
		this->pImpl->data += f;
		return *this;
	}

	BigFloat& BigFloat::operator +=(const BigInt& number)
	{
		this->pImpl->data += CBigFloat::value_type(number.pImpl->data);
		return *this;
	}

	BigFloat& BigFloat::operator +=(const BigFloat& number)
	{
		this->pImpl->data += number.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		-, --
	//
	////////////////////////////////////////////////////////////////

	BigFloat& BigFloat::operator --()
	{
		--this->pImpl->data;
		return *this;
	}

	BigFloat BigFloat::operator --(int)
	{
		BigFloat tmp(*this);
		--this->pImpl->data;
		return tmp;
	}

	BigFloat BigFloat::operator -(const int64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data - i;
		return tmp;
	}

	BigFloat BigFloat::operator -(const uint64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data - i;
		return tmp;
	}

	BigFloat BigFloat::operator -(const long double f) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data - f;
		return tmp;
	}

	BigFloat BigFloat::operator -(const BigInt& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data - CBigFloat::value_type(number.pImpl->data);
		return tmp;
	}

	BigFloat BigFloat::operator -(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data - number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator -=(int64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigFloat& BigFloat::operator -=(uint64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigFloat& BigFloat::operator -=(long double f)
	{
		this->pImpl->data -= f;
		return *this;
	}

	BigFloat& BigFloat::operator -=(const BigInt& number)
	{
		this->pImpl->data -= CBigFloat::value_type(number.pImpl->data);
		return *this;
	}

	BigFloat& BigFloat::operator -=(const BigFloat& number)
	{
		this->pImpl->data -= number.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		*
	//
	////////////////////////////////////////////////////////////////

	BigFloat BigFloat::operator *(const int64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data * i;
		return tmp;
	}

	BigFloat BigFloat::operator *(const uint64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data * i;
		return tmp;
	}

	BigFloat BigFloat::operator *(const long double f) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data * f;
		return tmp;
	}

	BigFloat BigFloat::operator *(const BigInt& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data * CBigFloat::value_type(number.pImpl->data);
		return tmp;
	}

	BigFloat BigFloat::operator *(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data * number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator *=(int64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigFloat& BigFloat::operator *=(uint64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigFloat& BigFloat::operator *=(long double f)
	{
		this->pImpl->data *= f;
		return *this;
	}

	BigFloat& BigFloat::operator *=(const BigInt& number)
	{
		this->pImpl->data *= CBigFloat::value_type(number.pImpl->data);
		return *this;
	}

	BigFloat& BigFloat::operator *=(const BigFloat& number)
	{
		this->pImpl->data *= number.pImpl->data;
		return *this;
	}

	////////////////////////////////////////////////////////////////
	//
	//		/
	//
	////////////////////////////////////////////////////////////////

	BigFloat BigFloat::operator /(const int64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data / i;
		return tmp;
	}

	BigFloat BigFloat::operator /(const uint64 i) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data / i;
		return tmp;
	}

	BigFloat BigFloat::operator /(const long double f) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data / f;
		return tmp;
	}

	BigFloat BigFloat::operator /(const BigInt& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data / CBigFloat::value_type(number.pImpl->data);
		return tmp;
	}

	BigFloat BigFloat::operator /(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data / number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator /=(int64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigFloat& BigFloat::operator /=(uint64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigFloat& BigFloat::operator /=(long double f)
	{
		this->pImpl->data /= f;
		return *this;
	}

	BigFloat& BigFloat::operator /=(const BigInt& number)
	{
		this->pImpl->data /= CBigFloat::value_type(number.pImpl->data);
		return *this;
	}

	BigFloat& BigFloat::operator /=(const BigFloat& number)
	{
		this->pImpl->data /= number.pImpl->data;
		return *this;
	}

	BigFloat operator /(int64 a, const BigFloat& b)
	{
		BigFloat tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}

	BigFloat operator /(uint64 a, const BigFloat& b)
	{
		BigFloat tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}
	
	BigFloat operator /(long double a, const BigFloat& b)
	{
		BigFloat tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}

	////////////////////////////////////////////////////////////////
	//
	//		compare
	//
	////////////////////////////////////////////////////////////////

	int32 BigFloat::compare(int64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigFloat::compare(uint64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigFloat::compare(long double f) const
	{
		return this->pImpl->data.compare(f);
	}

	int32 BigFloat::compare(const BigInt& number) const
	{
		const int32 sa = this->sign(), sb = number.sign();

		if (sa < sb)
		{
			return -1;
		}
		else if (sa > sb)
		{
			return 1;
		}

		return this->pImpl->data.compare(CBigFloat::value_type(number.pImpl->data));
	}

	int32 BigFloat::compare(const BigFloat& number) const
	{
		return this->pImpl->data.compare(number.pImpl->data);
	}

	////////////////////////////////////////////////////////////////
	//
	//		math
	//
	////////////////////////////////////////////////////////////////

	BigFloat::operator bool() const
	{
		return this->pImpl->data.operator bool();
	}

	bool BigFloat::isZero() const
	{
		return this->pImpl->data.is_zero();
	}

	int32 BigFloat::sign() const
	{
		return this->pImpl->data.sign();
	}

	BigFloat BigFloat::abs() const
	{
		BigFloat tmp;
		tmp.pImpl->data = boost::multiprecision::abs(this->pImpl->data);
		return tmp;
	}

	////////////////////////////////////////////////////////////////
	//
	//		conversion
	//
	////////////////////////////////////////////////////////////////

	float BigFloat::asFloat() const
	{
		return this->pImpl->data.convert_to<float>();
	}

	double BigFloat::asDouble() const
	{
		return this->pImpl->data.convert_to<double>();
	}

	long double BigFloat::asLongDouble() const
	{
		return this->pImpl->data.convert_to<long double>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		string
	//
	////////////////////////////////////////////////////////////////

	std::string BigFloat::stdStr() const
	{
		std::string result = pImpl->data.str(0, std::ios_base::fixed);

		const bool removeZeros =
			   (result.length() > 2 && result[0] == '0' && result[1] == '.')
			|| (result.length() > 2 && result[0] == '-' && result[1] == '0' && result[2] == '.')
			|| (result.find('.') != std::string::npos);

		if (removeZeros)
		{
			while (result.back() == '0')
			{
				result.pop_back();
			}
		}

		return result;
	}

	String BigFloat::str() const
	{
		const std::string t = stdStr();
		return String(t.begin(), t.end());
	}

	////////////////////////////////////////////////////////////////
	//
	//		swap
	//
	////////////////////////////////////////////////////////////////

	void BigFloat::swap(BigFloat& other) noexcept
	{
		return this->pImpl->data.swap(other.pImpl->data);
	}
}
