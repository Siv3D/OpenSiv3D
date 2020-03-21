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
# include <Siv3D/Optional.hpp>
# include <Siv3D/ParseFloat.hpp>
# include <Siv3D/Error.hpp>
# include <double-conversion/double-conversion.h>

namespace s3d
{
	namespace detail
	{
		inline static constexpr double sNaN = std::numeric_limits<double>::signaling_NaN();

		static float ParseFloat(const StringView view)
		{
			using namespace double_conversion;

			const int flags =
				  StringToDoubleConverter::ALLOW_LEADING_SPACES
				| StringToDoubleConverter::ALLOW_TRAILING_SPACES
				| StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN
				| StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY;
			StringToDoubleConverter conv(flags, 0.0, sNaN, "inf", "nan");

			int unused;
			const double result = conv.Siv3D_StringToIeee(view.data(), static_cast<int>(view.length()), false, &unused);

			if (std::memcmp(&result, &sNaN, sizeof(double)) == 0)
			{
				throw ParseError(U"ParseFloat<float>(\"{}\") failed"_fmt(view));
			}

			return static_cast<float>(result);
		}

		static double ParseDouble(const StringView view)
		{
			using namespace double_conversion;

			const int flags =		
				  StringToDoubleConverter::ALLOW_LEADING_SPACES
				| StringToDoubleConverter::ALLOW_TRAILING_SPACES
				| StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN
				| StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY;
			StringToDoubleConverter conv(flags, 0.0, sNaN, "inf", "nan");

			int unused;
			const double result = conv.Siv3D_StringToIeee(view.data(), static_cast<int>(view.length()), false, &unused);

			if (std::memcmp(&result, &sNaN, sizeof(double)) == 0)
			{
				throw ParseError(U"ParseFloat<double>(\"{}\") failed"_fmt(view));
			}

			return result;
		}

		template <class FloatType>
		static Optional<FloatType> ParseFloatingPointOpt(const StringView view) noexcept
		{
			using namespace double_conversion;

			const int flags =
				StringToDoubleConverter::ALLOW_LEADING_SPACES
				| StringToDoubleConverter::ALLOW_TRAILING_SPACES
				| StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN
				| StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY;
			StringToDoubleConverter conv(flags, 0.0, sNaN, "inf", "nan");

			int unused;
			const double result = conv.Siv3D_StringToIeee(view.data(), static_cast<int>(view.length()), false, &unused);

			if (std::memcmp(&result, &sNaN, sizeof(double)) == 0)
			{
				return none;
			}

			return static_cast<FloatType>(result);
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
		return detail::ParseFloatingPointOpt<float>(view);
	}

	template <>
	Optional<double> ParseFloatOpt<double>(const StringView view)
	{
		return detail::ParseFloatingPointOpt<double>(view);
	}

	template <>
	Optional<long double> ParseFloatOpt<long double>(const StringView view)
	{
		return detail::ParseFloatingPointOpt<long double>(view);
	}
}
