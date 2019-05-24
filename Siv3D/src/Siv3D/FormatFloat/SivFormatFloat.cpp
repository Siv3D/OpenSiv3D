//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatInt.hpp>
# include <double-conversion/double-conversion.h>

namespace s3d
{
	namespace detail
	{
		String FormatFloat(const double value, const int32 decimalPlace, const bool fixed)
		{
			using namespace double_conversion;

			const int flags = DoubleToStringConverter::UNIQUE_ZERO |
				DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
			DoubleToStringConverter conv(flags, "inf", "nan", 'e', -324, 309, 0, 0);

			const int bufferSize = 384;
			char buffer[bufferSize];
			StringBuilder builder(buffer, bufferSize);

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

		size_t FormatFloat(char32(&dst)[384], const double value, const int32 decimalPlace, const bool fixed)
		{
			using namespace double_conversion;

			const int flags = DoubleToStringConverter::UNIQUE_ZERO |
				DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN;
			DoubleToStringConverter conv(flags, "inf", "nan", 'e', -324, 309, 0, 0);

			const int bufferSize = 384;
			char buffer[bufferSize];
			StringBuilder builder(buffer, bufferSize);

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

	String ToString(const float value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, false);
	}

	String ToString(const double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, false);
	}

	String ToString(const long double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, false);
	}

	String ToFixed(const float value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, true);
	}

	String ToFixed(const double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(value, decimalPlace, true);
	}

	String ToFixed(const long double value, const int32 decimalPlace = 3)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, true);
	}

	uint32 AsUint(const float value) noexcept
	{
		static_assert(sizeof(uint32) == sizeof(float));
		return *static_cast<const uint32*>(static_cast<const void*>(&value));
	}

	uint64 AsUint(const double value) noexcept
	{
		static_assert(sizeof(uint64) == sizeof(double));
		return *static_cast<const uint64*>(static_cast<const void*>(&value));
	}

	String ToBinary(const float value)
	{
		return ToBinary(AsUint(value));
	}

	String ToBinary(const double value)
	{
		return ToBinary(AsUint(value));
	}

	String ToOctal(const float value)
	{
		return ToOctal(AsUint(value));
	}

	String ToOctal(const double value)
	{
		return ToOctal(AsUint(value));
	}

	String ToHex(const float value)
	{
		return ToHex(AsUint(value));
	}

	String ToHex(const double value)
	{
		return ToHex(AsUint(value));
	}
}
