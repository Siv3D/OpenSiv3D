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

# include <ThirdParty/fast_float/fast_float.h>
# include <Siv3D/ParseFloat.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/FormatLiteral.hpp>

namespace s3d
{
	namespace detail
	{
		[[noreturn]]
		static void ThrowParseError(const StringView s)
		{
			throw ParseError{ U"ParseFloat(\"{}\") failed"_fmt(s) };
		}

		static double ParseDouble(StringView s)
		{
			while ((not s.isEmpty()) && IsSpace(s.front()))
			{
				s.remove_prefix(1);
			}

			double result;
			auto [p, ec] = fast_float::from_chars(s.data(), (s.data() + s.size()), result);

			if (ec != std::errc{})
			{
				ThrowParseError(s);
			}

			return result;
		}

		template <class FloatType>
		static Optional<FloatType> ParseFloatingPointOpt(StringView s) noexcept
		{
			while ((not s.isEmpty()) && IsSpace(s.front()))
			{
				s.remove_prefix(1);
			}

			double result;
			auto [p, ec] = fast_float::from_chars(s.data(), (s.data() + s.size()), result);

			if (ec != std::errc{})
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
