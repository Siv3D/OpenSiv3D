//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/BigFloat.hpp>
# include <cstring>
# include "CBigFloat.hpp"
# include "../BigInt/CBigInt.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//	Constructor
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

	BigFloat::BigFloat(const char32* number)
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

	BigFloat::BigFloat(const String& number)
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
	//	Destructor
	//
	////////////////////////////////////////////////////////////////

	BigFloat::~BigFloat()
	{

	}

	////////////////////////////////////////////////////////////////
	//
	//	Assign
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

	BigFloat& BigFloat::assign(const char32* number)
	{
		this->pImpl->data.assign(std::string(number, number + std::char_traits<char32>::length(number)));
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
	
	BigFloat& BigFloat::assign(const String& number)
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
	//	+, ++
	//
	////////////////////////////////////////////////////////////////

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
		tmp.pImpl->data = this->pImpl->data + CBigFloat::value_type(number.pImpl->data);
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
	//	-, --
	//
	////////////////////////////////////////////////////////////////

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
		tmp.pImpl->data = this->pImpl->data - CBigFloat::value_type(number.pImpl->data);
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
	//	*
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
	//	/
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
		this->pImpl->data /= CBigFloat::value_type(number.pImpl->data);
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

	////////////////////////////////////////////////////////////////
	//
	//	Compare
	//
	////////////////////////////////////////////////////////////////

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

		return this->pImpl->data.compare(CBigFloat::value_type(number.pImpl->data));
	}

	int32 BigFloat::compare(const BigFloat& number) const
	{
		return this->pImpl->data.compare(number.pImpl->data);
	}

	////////////////////////////////////////////////////////////////
	//
	//	Math
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
	//	Conversion
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
	//	String
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

	////////////////////////////////////////////////////////////////
	//
	//	Swap
	//
	////////////////////////////////////////////////////////////////

	void BigFloat::swap(BigFloat& other) noexcept
	{
		return this->pImpl->data.swap(other.pImpl->data);
	}

	////////////////////////////////////////////////////////////////
	//
	//	Hash
	//
	////////////////////////////////////////////////////////////////

	//size_t BigFloat::hash() const
	//{
	//	return std::hash<boost::multiprecision::cpp_dec_float_100>()(this->pImpl->data);
	//}

	////////////////////////////////////////////////////////////////
	//
	//	Format
	//
	////////////////////////////////////////////////////////////////

	void Formatter(FormatData& formatData, const BigFloat& value)
	{
		formatData.string.append(value.str());
	}

	std::ostream& operator <<(std::ostream output, const BigFloat& value)
	{
		return output << value.stdStr();
	}

	std::wostream& operator <<(std::wostream& output, const BigFloat& value)
	{
		return output << value.stdWstr();
	}

	std::istream& operator >>(std::istream& input, BigFloat& value)
	{
		std::string s;

		input >> s;

		value.assign(s);

		return input;
	}

	std::wistream& operator >>(std::wistream& input, BigFloat& value)
	{
		std::wstring s;

		input >> s;

		value.assign(s);

		return input;
	}

	////////////////////////////////////////////////////////////////
	//
	//	detail
	//
	////////////////////////////////////////////////////////////////

	BigFloat::CBigFloat& BigFloat::detail()
	{
		return *pImpl;
	}

	const BigFloat::CBigFloat& BigFloat::detail() const
	{
		return *pImpl;
	}

	////////////////////////////////////////////////////////////////
	//
	//	Math Functions
	//
	////////////////////////////////////////////////////////////////

	namespace Math
	{
		BigFloat Abs(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::abs(x.detail().data);

			return result;
		}

		BigFloat Sqrt(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::sqrt(x.detail().data);

			return result;
		}

		BigFloat Floor(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::floor(x.detail().data);

			return result;
		}

		BigFloat Ceil(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::ceil(x.detail().data);

			return result;
		}

		BigFloat Round(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::round(x.detail().data);

			return result;
		}

		BigFloat Exp(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::exp(x.detail().data);

			return result;
		}

		BigFloat Exp2(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::exp2(x.detail().data);

			return result;
		}

		BigFloat Log(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::log(x.detail().data);

			return result;
		}

		BigFloat Log2(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::log2(x.detail().data);

			return result;
		}

		BigFloat Log10(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::log10(x.detail().data);

			return result;
		}

		BigFloat Cos(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::cos(x.detail().data);

			return result;
		}

		BigFloat Sin(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::sin(x.detail().data);

			return result;
		}

		BigFloat Tan(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::tan(x.detail().data);

			return result;
		}

		BigFloat Acos(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::acos(x.detail().data);

			return result;
		}

		BigFloat Asin(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::asin(x.detail().data);

			return result;
		}

		BigFloat Atan(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::atan(x.detail().data);

			return result;
		}

		BigFloat Cosh(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::cosh(x.detail().data);

			return result;
		}

		BigFloat Sinh(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::sinh(x.detail().data);

			return result;
		}

		BigFloat Tanh(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::tanh(x.detail().data);

			return result;
		}

		BigFloat Ldexp(const BigFloat& x, const int64 exp)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::ldexp(x.detail().data, exp);

			return result;
		}

		std::pair<BigFloat, int32> Frexp(const BigFloat& x)
		{
			BigFloat result;

			int32 exp = 0;

			result.detail().data = boost::multiprecision::frexp(x.detail().data, &exp);

			return{ result, exp };
		}

		BigFloat Frexp(const BigFloat& x, int32& exp)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::frexp(x.detail().data, &exp);

			return result;
		}

		BigFloat Pow(const BigFloat& x, const BigFloat& y)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::pow(x.detail().data, y.detail().data);

			return result;
		}

		BigFloat Fmod(const BigFloat& x, const BigFloat& y)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::fmod(x.detail().data, y.detail().data);

			return result;
		}

		BigFloat Atan2(const BigFloat& x, const BigFloat& y)
		{
			BigFloat result;

			result.detail().data = boost::multiprecision::atan2(x.detail().data, y.detail().data);

			return result;
		}

		BigFloat Sign(const BigFloat& x)
		{
			return x < 0.0 ? -1.0 : x > 0.0 ? 1.0 : 0.0;
		}

		BigFloat Radians(const BigFloat& x)
		{
			static const BigFloat degToRad("0.017453292519943295769236907684886127134428718885417254560971914401710091146034494436822415696345094822123044925073790592483854692275281");

			return x * degToRad;
		}

		BigFloat Degrees(const BigFloat& x)
		{
			static const BigFloat radToDeg("57.2957795130823208767981548141051703324054724665643215491602438612028471483215526324409689958511109441862233816328648932814482646012483");

			return x * radToDeg;
		}

		BigFloat Square(const BigFloat& x)
		{
			return x * x;
		}

		BigFloat Rsqrt(const BigFloat& x)
		{
			BigFloat result;

			result.detail().data = 1.0 / boost::multiprecision::sqrt(x.detail().data);

			return result;
		}

		BigFloat Saturate(const BigFloat& x)
		{
			if (x <= 0.0)
			{
				return 0.0;
			}
			else if (x >= 1.0)
			{
				return 1.0;
			}
			else
			{
				return x;
			}
		}
	}
}
