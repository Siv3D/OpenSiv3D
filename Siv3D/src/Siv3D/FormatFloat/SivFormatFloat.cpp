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

# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/FloatingPoint.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatData.hpp>
# include <Siv3D/PredefinedYesNo.hpp>
# include <ThirdParty/double-conversion/double-conversion.h>

namespace s3d
{
	namespace detail
	{
		using namespace double_conversion;

		inline constexpr size_t FormatFloatBufferSize = 384;

		inline constexpr int FormatFlags = DoubleToStringConverter::UNIQUE_ZERO |
			DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;

		static String FormatFloat(const double value, const int32 decimalPlace, const Fixed fixed)
		{
			DoubleToStringConverter conv(FormatFlags, "inf", "nan", 'e', -324, 309, 0, 0);

			char buffer[FormatFloatBufferSize];
			StringBuilder builder(buffer, FormatFloatBufferSize);

			if (conv.ToFixed(value, decimalPlace, &builder))
			{
				const int length = builder.position();
				const char* p = builder.Finalize();
				const char* end = p + length;

				if (!fixed && decimalPlace != 0)
				{
					while (*(end - 1) == '0')
					{
						--end;
					}

					if (*(end - 1) == '.')
					{
						--end;
					}
				}

				if ((end - p) == 2 && p[0] == '-' && p[1] == '0')
				{
					++p;
				}

				return String(p, end);
			}
			else
			{
				conv.ToShortest(value, &builder);
				const int length = builder.position();
				const char* p = builder.Finalize();
				return String(p, p + length);
			}
		}

		static size_t FormatFloat(char32(&dst)[FormatFloatBufferSize], const double value, int32 decimalPlace, const Fixed fixed)
		{
			DoubleToStringConverter conv(FormatFlags, "inf", "nan", 'e', -324, 309, 0, 0);

			char buffer[FormatFloatBufferSize];
			StringBuilder builder(buffer, FormatFloatBufferSize);

			if (conv.ToFixed(value, decimalPlace, &builder))
			{
				const int length = builder.position();
				const char* p = builder.Finalize();
				const char* end = p + length;

				if (!fixed && decimalPlace != 0)
				{
					while (*(end - 1) == '0')
					{
						--end;
					}

					if (*(end - 1) == '.')
					{
						--end;
					}
				}

				if ((end - p) == 2 && p[0] == '-' && p[1] == '0')
				{
					++p;
				}

				const size_t ret = end - p;
				char32* pDst = dst;
				while (p != end)
				{
					*(pDst++) = *(p++);
				}
				*pDst = U'\0';
				return ret;
			}
			else
			{
				conv.ToShortest(value, &builder);
				const int length = builder.position();
				const char* p = builder.Finalize();

				char32* pDst = dst;
				const char* end = p + length;
				while (p != end)
				{
					*(pDst++) = *(p++);
				}
				*pDst = U'\0';
				return length;
			}
		}
	}

	void Formatter(FormatData& formatData, const double value)
	{
		char32 buf[detail::FormatFloatBufferSize];
		const size_t len = detail::FormatFloat(buf, value, formatData.decimalPlaces.value, Fixed::No);
		formatData.string.append(buf, len);
	}

	String ToString(const float value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, Fixed::No);
	}

	String ToString(const double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, Fixed::No);
	}

	String ToString(const long double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, Fixed::No);
	}

	String ToFixed(const float value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, Fixed::Yes);
	}

	String ToFixed(const double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, Fixed::Yes);
	}

	String ToFixed(const long double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, Fixed::Yes);
	}

	String ToBinary(const float value)
	{
		return ToBinary(AsUint32(value));
	}

	String ToBinary(const double value)
	{
		return ToBinary(AsUint64(value));
	}

	String ToOctal(const float value)
	{
		return ToOctal(AsUint32(value));
	}

	String ToOctal(const double value)
	{
		return ToOctal(AsUint64(value));
	}

	String ToHex(const float value)
	{
		return ToHex(AsUint32(value));
	}

	String ToHex(const double value)
	{
		return ToHex(AsUint64(value));
	}
}
