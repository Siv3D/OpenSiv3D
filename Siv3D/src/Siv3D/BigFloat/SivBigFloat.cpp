//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "BigFloatDetail.hpp"
# include <Siv3D/BigInt/BigIntDetail.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static std::string RemoveTrailingZeros(std::string&& s) noexcept
		{
			if (s.find('.') == std::string::npos)
			{
				return s;
			}

			while (s.back() == '0')
			{
				s.pop_back();
			}

			if (s.back() == '.')
			{
				s.pop_back();
			}

			return s;
		}
	}

	BigFloat::BigFloat()
		: BigFloat{ 0.0 }
	{

	}

	BigFloat::BigFloat(const int64 i)
		: pImpl{ std::make_unique<BigFloatDetail>() }
	{
		assign(i);
	}

	BigFloat::BigFloat(const uint64 i)
		: pImpl{ std::make_unique<BigFloatDetail>() }
	{
		assign(i);
	}

	BigFloat::BigFloat(const long double f)
		: pImpl{ std::make_unique<BigFloatDetail>() }
	{
		assign(f);
	}

	BigFloat::BigFloat(const BigInt& number)
		: pImpl{ std::make_unique<BigFloatDetail>() }
	{
		assign(number);
	}

	BigFloat::BigFloat(const std::string_view number)
		: pImpl{ std::make_unique<BigFloatDetail>() }
	{
		assign(number);
	}

	BigFloat::BigFloat(const StringView number)
		: pImpl{ std::make_unique<BigFloatDetail>() }
	{
		assign(number);
	}

	BigFloat::BigFloat(const BigFloat& other)
		: pImpl{ std::make_unique<BigFloatDetail>() }
	{
		assign(other);
	}

	BigFloat::BigFloat(BigFloat&& other) noexcept
		: pImpl{ std::move(other.pImpl) }
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

	bool BigFloat::isNaN() const
	{
		return this->pImpl->data.backend().isnan();
	}

	bool BigFloat::isInf() const
	{
		return this->pImpl->data.backend().isinf();
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

	std::string BigFloat::to_string() const
	{
		std::string result = pImpl->data.str(100, std::ios_base::fixed);

		return detail::RemoveTrailingZeros(std::move(result));
	}

	std::wstring BigFloat::to_wstring() const
	{
		const std::string str = to_string();

		return std::wstring(str.begin(), str.end());
	}

	String BigFloat::str() const
	{
		const std::string t = to_string();

		return String(t.begin(), t.end());
	}

	void Formatter(FormatData& formatData, const BigFloat& value)
	{
		formatData.string.append(value.str());
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

	namespace Math
	{
		BigFloat Fmod(const BigFloat& x, const BigFloat& y)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::fmod(x._detail().data, y._detail().data);
			return result;
		}

		BigFloat Fraction(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = (x._detail().data - boost::multiprecision::floor(x._detail().data));
			return result;
		}

		BigFloat Frexp(const BigFloat& x, int32& exp)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::frexp(x._detail().data, &exp);
			return result;
		}

		BigFloat Ldexp(const BigFloat& x, const BigFloat& y)
		{
			BigFloat result;
			result._detail().data = (x._detail().data * boost::multiprecision::pow(2, y._detail().data));
			return result;
		}

		BigFloat Log(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::log(x._detail().data);
			return result;
		}

		BigFloat Log2(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::log2(x._detail().data);
			return result;
		}

		BigFloat Log10(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::log10(x._detail().data);
			return result;
		}

		BigFloat Modf(const BigFloat& x, BigFloat& exp)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::modf(x._detail().data, &exp._detail().data);
			return result;
		}

		BigInt Pow(const BigInt& x, const uint32 y)
		{
			BigInt result;
			result._detail().data = boost::multiprecision::pow(x._detail().data, y);
			return result;
		}

		BigFloat Pow(const BigFloat& x, const BigFloat& y)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::pow(x._detail().data, y._detail().data);
			return result;
		}

		int32 Sign(const BigInt& x)
		{
			const int32 c = x.compare(0);

			if (c < 0)
			{
				return -1;
			}
			else if (0 < c)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		int32 Sign(const BigFloat& x)
		{
			const int32 c = x.compare(0);

			if (c < 0)
			{
				return -1;
			}
			else if (0 < c)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		BigFloat ToRadians(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = (x._detail().data * (boost::math::constants::pi<boost::multiprecision::cpp_dec_float_100>() / 180));
			return result;
		}

		BigFloat ToDegrees(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = (x._detail().data * (180 / boost::math::constants::pi<boost::multiprecision::cpp_dec_float_100>()));
			return result;
		}

		BigFloat Abs(const BigInt& x)
		{
			return x.abs();
		}

		BigFloat Abs(const BigFloat& x)
		{
			return x.abs();
		}

		BigFloat AbsDiff(const BigFloat& x, const BigFloat& y)
		{
			return (x - y).abs();
		}

		BigFloat Square(const BigInt& x)
		{
			return (x * x);
		}

		BigFloat Square(const BigFloat& x)
		{
			return (x * x);
		}

		BigFloat Exp(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::exp(x._detail().data);
			return result;
		}

		BigFloat Exp2(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::exp2(x._detail().data);
			return result;
		}

		BigFloat Rsqrt(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = (1 / boost::multiprecision::sqrt(x._detail().data));
			return result;
		}

		BigFloat Sqrt(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::sqrt(x._detail().data);
			return result;
		}

		BigFloat Ceil(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::ceil(x._detail().data);
			return result;
		}

		BigFloat Floor(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::floor(x._detail().data);
			return result;
		}

		BigFloat Round(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::round(x._detail().data);
			return result;
		}

		BigFloat Clamp(const BigFloat& x, const BigFloat& min, const BigFloat& max)
		{
			if (max < x)
			{
				return max;
			}

			if (x < min)
			{
				return min;
			}

			return x;
		}

		BigFloat Saturate(const BigFloat& x)
		{
			if (1 < x)
			{
				return 1;
			}

			if (x < 0)
			{
				return 0;
			}

			return x;
		}

		BigFloat Acos(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::acos(x._detail().data);
			return result;
		}

		BigFloat Asin(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::asin(x._detail().data);
			return result;
		}

		BigFloat Atan(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::atan(x._detail().data);
			return result;
		}

		BigFloat Atan2(const BigFloat& y, const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::atan2(y._detail().data, x._detail().data);
			return result;
		}

		BigFloat Cos(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::cos(x._detail().data);
			return result;
		}

		BigFloat Cosh(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::cosh(x._detail().data);
			return result;
		}

		BigFloat Sin(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::sin(x._detail().data);
			return result;
		}

		BigFloat Sinh(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::sinh(x._detail().data);
			return result;
		}

		BigFloat Tan(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::tan(x._detail().data);
			return result;
		}

		BigFloat Tanh(const BigFloat& x)
		{
			BigFloat result;
			result._detail().data = boost::multiprecision::tanh(x._detail().data);
			return result;
		}

		BigFloat Normalize(const BigFloat& x)
		{
			if (x.isZero())
			{
				return 0;
			}

			return 1;
		}

		BigFloat Smoothstep(const BigFloat& min, const BigFloat& max, const BigFloat& x)
		{
			if (x <= min)
			{
				return 0;
			}
			else if (max <= x)
			{
				return 1;
			}

			const BigFloat t = ((x - min) / (max - min));

			return (t * t * (3 - 2 * t));
		}

		BigFloat Smoothstep(const BigFloat& x)
		{
			if (x <= 0)
			{
				return 0;
			}
			else if (1 <= x)
			{
				return 1;
			}

			return (x * x * (3 - 2 * x));
		}
	}

	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			BigFloat operator ""_bigF(const char* s)
			{
				return BigFloat{ std::string_view{ s } };
			}
		}
	}
}
