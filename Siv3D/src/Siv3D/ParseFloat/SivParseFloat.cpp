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
# include <Siv3D/Optional.hpp>
# include <Siv3D/ParseFloat.hpp>
# include "../../ThirdParty/double-conversion/double-conversion.h"

namespace s3d
{
	namespace detail
	{
		static float ParseFloat(const StringView view)
		{
			using namespace double_conversion;

			const int flags = StringToDoubleConverter::ALLOW_TRAILING_SPACES |
                StringToDoubleConverter::ALLOW_LEADING_SPACES |
				StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN;
			StringToDoubleConverter conv(flags, 0.0, 0.0, "inf", "nan");

			int unused;
			return static_cast<float>(conv.Siv3D_StringToIeee(view.data(), static_cast<int>(view.length()), false, &unused));
		}

		static double ParseDouble(const StringView view)
		{
			using namespace double_conversion;

            const int flags = StringToDoubleConverter::ALLOW_TRAILING_SPACES |
                StringToDoubleConverter::ALLOW_LEADING_SPACES |
                StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN;
			StringToDoubleConverter conv(flags, 0.0, 0.0, "inf", "nan");

			int unused;
			return conv.Siv3D_StringToIeee(view.data(), static_cast<int>(view.length()), true, &unused);
		}
	}

	template <>
	float ParseFloat<float>(const StringView view)
	{
		return detail::ParseFloat(view);
	}

	template <>
	double ParseFloat<double>(const StringView view)
	{
		return detail::ParseDouble(view);
	}

	template <>
	long double ParseFloat<long double>(const StringView view)
	{
		return detail::ParseDouble(view);
	}

	template <>
	Optional<float> ParseFloatOpt<float>(const StringView view)
	{
		const float result = detail::ParseFloat(view);

		if (std::isnan(result))
		{
			return none;
		}
		else
		{
			return result;
		}
	}

	template <>
	Optional<double> ParseFloatOpt<double>(const StringView view)
	{
		const double result = detail::ParseDouble(view);

		if (std::isnan(result))
		{
			return none;
		}
		else
		{
			return result;
		}
	}

	template <>
	Optional<long double> ParseFloatOpt<long double>(const StringView view)
	{
		const long double result = detail::ParseDouble(view);

		if (std::isnan(result))
		{
			return none;
		}
		else
		{
			return result;
		}
	}
}
