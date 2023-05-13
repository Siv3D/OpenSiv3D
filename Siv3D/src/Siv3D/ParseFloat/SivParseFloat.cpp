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

# include <Siv3D/ParseFloat.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <ThirdParty/double-conversion/double-conversion.h>

namespace s3d
{
	namespace detail
	{
		inline static constexpr double sNaN = std::numeric_limits<double>::signaling_NaN();

		static double ParseDouble(const StringView s)
		{
			using namespace double_conversion;

			const int flags =
				StringToDoubleConverter::ALLOW_LEADING_SPACES
				| StringToDoubleConverter::ALLOW_TRAILING_SPACES
				| StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN
				| StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY;
			StringToDoubleConverter conv(flags, 0.0, sNaN, "inf", "nan");

			int unused;
			const double result = conv.Siv3D_StringToIeee(s.data(), static_cast<int>(s.length()), true, &unused);

			if (std::memcmp(&result, &sNaN, sizeof(double)) == 0)
			{
				throw ParseError(U"ParseFloat(\"{}\") failed"_fmt(s));
			}

			return result;
		}

		template <class FloatType>
		static Optional<FloatType> ParseFloatingPointOpt(const StringView s) noexcept
		{
			using namespace double_conversion;

			const int flags =
				StringToDoubleConverter::ALLOW_LEADING_SPACES
				| StringToDoubleConverter::ALLOW_TRAILING_SPACES
				| StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN
				| StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY;
			StringToDoubleConverter conv(flags, 0.0, sNaN, "inf", "nan");

			int unused;
			const double result = conv.Siv3D_StringToIeee(s.data(), static_cast<int>(s.length()), true, &unused);

			if (std::memcmp(&result, &sNaN, sizeof(double)) == 0)
			{
				return none;
			}

			return static_cast<FloatType>(result);
		}
	}

	template <>
	float ParseFloat<float>(const StringView s)
	{
		return static_cast<float>(detail::ParseDouble(s));
	}

	template <>
	double ParseFloat<double>(const StringView s)
	{
		return detail::ParseDouble(s);
	}

	template <>
	long double ParseFloat<long double>(const StringView s)
	{
		return detail::ParseDouble(s);
	}

	template <>
	Optional<float> ParseFloatOpt<float>(const StringView s) noexcept
	{
		return detail::ParseFloatingPointOpt<float>(s);
	}

	template <>
	Optional<double> ParseFloatOpt<double>(const StringView s) noexcept
	{
		return detail::ParseFloatingPointOpt<double>(s);
	}

	template <>
	Optional<long double> ParseFloatOpt<long double>(const StringView s) noexcept
	{
		return detail::ParseFloatingPointOpt<long double>(s);
	}
}
