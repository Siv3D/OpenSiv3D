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

# include "../../../Include/Siv3D/FormatFloat.hpp"
# include "../../ThirdParty/double-conversion/double-conversion.h"

namespace s3d
{
	String FormatFloat(double value, int32 decimalPlace, bool fixed)
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
}
