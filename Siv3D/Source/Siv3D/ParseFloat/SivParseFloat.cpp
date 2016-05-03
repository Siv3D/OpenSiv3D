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

# include "../../../Include/Siv3D/Fwd.hpp"
# include "../../../Include/Siv3D/String.hpp"
# include "../../../Include/Siv3D/ParseFloat.hpp"
# include "../../ThirdParty/double-conversion/double-conversion.h"

namespace s3d
{
	template <>
	float ParseFloat<float>(const String& str)
	{
		using namespace double_conversion;

		const int flags = StringToDoubleConverter::ALLOW_TRAILING_SPACES |
			StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN;
		StringToDoubleConverter conv(flags, 0.0, 0.0, "inf", "nan");

		int unused;
		return static_cast<float>(conv.Siv3D_StringToIeee(str.c_str(), static_cast<int>(str.length()), false, &unused));
	}

	template <>
	double ParseFloat<double>(const String& str)
	{
		using namespace double_conversion;

		const int flags = StringToDoubleConverter::ALLOW_TRAILING_SPACES |
			StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN;
		StringToDoubleConverter conv(flags, 0.0, 0.0, "inf", "nan");

		int unused;
		return conv.Siv3D_StringToIeee(str.c_str(), static_cast<int>(str.length()), true, &unused);
	}
}
