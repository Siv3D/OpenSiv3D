//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "BigFloatDetail.hpp"
# include <Siv3D/BigInt/BigIntDetail.hpp>

namespace s3d
{
	BigFloat::BigFloat()
		: BigFloat(0.0)
	{

	}

	BigFloat::BigFloat(const int64 i)
		: pImpl(std::make_unique<BigFloatDetail>())
	{
		assign(i);
	}

	BigFloat::BigFloat(const uint64 i)
		: pImpl(std::make_unique<BigFloatDetail>())
	{
		assign(i);
	}

	BigFloat::BigFloat(const long double f)
		: pImpl(std::make_unique<BigFloatDetail>())
	{
		assign(f);
	}

	BigFloat::BigFloat(const BigInt& number)
		: pImpl(std::make_unique<BigFloatDetail>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const std::string_view number)
		: pImpl(std::make_unique<BigFloatDetail>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const StringView number)
		: pImpl(std::make_unique<BigFloatDetail>())
	{
		assign(number);
	}

	BigFloat::BigFloat(const BigFloat& other)
		: pImpl(std::make_unique<BigFloatDetail>())
	{
		assign(other);
	}

	BigFloat::BigFloat(BigFloat&& other) noexcept
		: pImpl(std::move(other.pImpl))
	{

	}

	BigFloat::~BigFloat()
	{

	}

	//////////////////////////////////////////////////
	//
	//	assign
	//
	//////////////////////////////////////////////////

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
		this->pImpl->data.assign(number._detail().data);
		return *this;
	}

	BigFloat& BigFloat::assign(const std::string_view number)
	{
		this->pImpl->data.assign(number);

		return *this;
	}

	BigFloat& BigFloat::assign(const StringView number)
	{
		this->pImpl->data.assign(Unicode::NarrowAscii(number));
		return *this;
	}

	BigFloat& BigFloat::assign(const BigFloat& other)
	{
		this->pImpl->data.assign(other.pImpl->data);
		return *this;
	}

	BigFloat& BigFloat::assign(BigFloat&& other) noexcept
	{
		this->pImpl = std::move(other.pImpl);
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	=
	//
	//////////////////////////////////////////////////

	BigFloat& BigFloat::operator =(int64 i)
	{
		return assign(i);
	}

	BigFloat& BigFloat::operator =(uint64 i)
	{
		return assign(i);
	}

	BigFloat& BigFloat::operator =(long double f)
	{
		return assign(f);
	}

	BigFloat& BigFloat::operator =(const BigInt& number)
	{
		return assign(number);
	}

	BigFloat& BigFloat::operator =(const std::string_view number)
	{
		return assign(number);
	}

	BigFloat& BigFloat::operator =(const StringView number)
	{
		return assign(number);
	}

	BigFloat& BigFloat::operator =(const BigFloat& other)
	{
		return assign(other);
	}

	BigFloat& BigFloat::operator =(BigFloat&& other) noexcept
	{
		return assign(std::move(other));
	}

	//////////////////////////////////////////////////
	//
	//	+
	//
	//////////////////////////////////////////////////

	const BigFloat& BigFloat::operator +() const
	{
		return *this;
	}

	BigFloat& BigFloat::operator ++()
	{
		++this->pImpl->data;
		return *this;
	}

	BigFloat BigFloat::operator ++(const int)
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
		tmp.pImpl->data = this->pImpl->data + BigFloatDetail::value_type(number._detail().data);
		return tmp;
	}

	BigFloat BigFloat::operator +(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data + number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator +=(const int64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigFloat& BigFloat::operator +=(const uint64 i)
	{
		this->pImpl->data += i;
		return *this;
	}

	BigFloat& BigFloat::operator +=(const long double f)
	{
		this->pImpl->data += f;
		return *this;
	}

	BigFloat& BigFloat::operator +=(const BigInt& number)
	{
		this->pImpl->data += BigFloatDetail::value_type(number._detail().data);
		return *this;
	}

	BigFloat& BigFloat::operator +=(const BigFloat& number)
	{
		this->pImpl->data += number.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	-
	//
	//////////////////////////////////////////////////

	BigFloat BigFloat::operator -() const&
	{
		BigFloat tmp;
		tmp.pImpl->data = -(this->pImpl->data);
		return tmp;
	}

	BigFloat BigFloat::operator -()&&
	{
		this->pImpl->data = -(this->pImpl->data);
		return std::move(*this);
	}

	BigFloat& BigFloat::operator --()
	{
		--this->pImpl->data;
		return *this;
	}

	BigFloat BigFloat::operator --(const int)
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
		tmp.pImpl->data = this->pImpl->data - BigFloatDetail::value_type(number._detail().data);
		return tmp;
	}

	BigFloat BigFloat::operator -(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data - number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator -=(const int64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigFloat& BigFloat::operator -=(const uint64 i)
	{
		this->pImpl->data -= i;
		return *this;
	}

	BigFloat& BigFloat::operator -=(const long double f)
	{
		this->pImpl->data -= f;
		return *this;
	}

	BigFloat& BigFloat::operator -=(const BigInt& number)
	{
		this->pImpl->data -= BigFloatDetail::value_type(number._detail().data);
		return *this;
	}

	BigFloat& BigFloat::operator -=(const BigFloat& number)
	{
		this->pImpl->data -= number.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	*
	//
	//////////////////////////////////////////////////

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
		tmp.pImpl->data = this->pImpl->data * BigFloatDetail::value_type(number._detail().data);
		return tmp;
	}

	BigFloat BigFloat::operator *(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data * number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator *=(const int64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigFloat& BigFloat::operator *=(const uint64 i)
	{
		this->pImpl->data *= i;
		return *this;
	}

	BigFloat& BigFloat::operator *=(const long double f)
	{
		this->pImpl->data *= f;
		return *this;
	}

	BigFloat& BigFloat::operator *=(const BigInt& number)
	{
		this->pImpl->data *= BigFloatDetail::value_type(number._detail().data);
		return *this;
	}

	BigFloat& BigFloat::operator *=(const BigFloat& number)
	{
		this->pImpl->data *= number.pImpl->data;
		return *this;
	}

	//////////////////////////////////////////////////
	//
	//	/
	//
	//////////////////////////////////////////////////

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
		tmp.pImpl->data = this->pImpl->data / BigFloatDetail::value_type(number._detail().data);
		return tmp;
	}

	BigFloat BigFloat::operator /(const BigFloat& number) const
	{
		BigFloat tmp;
		tmp.pImpl->data = this->pImpl->data / number.pImpl->data;
		return tmp;
	}

	BigFloat& BigFloat::operator /=(const int64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigFloat& BigFloat::operator /=(const uint64 i)
	{
		this->pImpl->data /= i;
		return *this;
	}

	BigFloat& BigFloat::operator /=(const long double f)
	{
		this->pImpl->data /= f;
		return *this;
	}

	BigFloat& BigFloat::operator /=(const BigInt& number)
	{
		this->pImpl->data /= BigFloatDetail::value_type(number._detail().data);
		return *this;
	}

	BigFloat& BigFloat::operator /=(const BigFloat& number)
	{
		this->pImpl->data /= number.pImpl->data;
		return *this;
	}

	BigFloat operator /(const int64 a, const BigFloat& b)
	{
		BigFloat tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}

	BigFloat operator /(const uint64 a, const BigFloat& b)
	{
		BigFloat tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}

	BigFloat operator /(const long double a, const BigFloat& b)
	{
		BigFloat tmp;
		tmp.pImpl->data = a / b.pImpl->data;
		return tmp;
	}

	//////////////////////////////////////////////////
	//
	//	compare
	//
	//////////////////////////////////////////////////

	int32 BigFloat::compare(const int64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigFloat::compare(const uint64 i) const
	{
		return this->pImpl->data.compare(i);
	}

	int32 BigFloat::compare(const long double f) const
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

		return this->pImpl->data.compare(BigFloatDetail::value_type(number._detail().data));
	}

	int32 BigFloat::compare(const BigFloat& number) const
	{
		return this->pImpl->data.compare(number.pImpl->data);
	}

	//////////////////////////////////////////////////
	//
	//	utilities
	//
	//////////////////////////////////////////////////

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

	void BigFloat::swap(BigFloat& other) noexcept
	{
		return this->pImpl->data.swap(other.pImpl->data);
	}

	size_t BigFloat::hash() const
	{
		return std::hash<boost::multiprecision::cpp_dec_float_100>{}(this->pImpl->data);
	}

	//////////////////////////////////////////////////
	//
	//	conversions
	//
	//////////////////////////////////////////////////

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

		if (result.back() == '.')
		{
			result.pop_back();
		}

		return result;
	}

	std::wstring BigFloat::stdWstr() const
	{
		const std::string str = pImpl->data.str();

		return std::wstring(str.begin(), str.end());
	}

	String BigFloat::str() const
	{
		const std::string t = stdStr();

		return String(t.begin(), t.end());
	}

	//////////////////////////////////////////////////
	//
	//	detail
	//
	//////////////////////////////////////////////////

	BigFloat::BigFloatDetail& BigFloat::_detail()
	{
		return *pImpl;
	}

	const BigFloat::BigFloatDetail& BigFloat::_detail() const
	{
		return *pImpl;
	}












	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			BigFloat operator ""_bigF(const unsigned long long int i)
			{
				return BigFloat{ i };
			}

			BigFloat operator ""_bigF(const char* s, const size_t length)
			{
				return BigFloat{ std::string_view{ s, length } };
			}

			BigFloat operator ""_bigF(const char32* s, const size_t length)
			{
				return BigFloat{ StringView{ s, length } };
			}
		}
	}
}
