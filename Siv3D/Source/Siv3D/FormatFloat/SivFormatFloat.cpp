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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include "../../ThirdParty/double-conversion/double-conversion.h"

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

		size_t FormatFloat(wchar(&dst)[384], const double value, const int32 decimalPlace, const bool fixed)
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
				wchar* pDst = dst;
				while (p != end)
				{
					*(pDst++) = *(p++);
				}
				*pDst = S3DCHAR('\0');
				return ret;
			}
			else
			{
				conv.ToShortest(value, &builder);
				const int length = builder.position();
				const char* p = builder.Finalize();

				wchar* pDst = dst;
				const char* end = p + length;
				while (p != end)
				{
					*(pDst++) = *(p++);
				}
				*pDst = S3DCHAR('\0');
				return length;
			}
		}
	}
}
