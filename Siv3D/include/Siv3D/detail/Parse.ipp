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

# pragma once
# include <Siv3D/FormatLiteral.hpp>

namespace s3d
{
	namespace detail
	{
		[[noreturn]]
		void ThrowParseError(const char* type, StringView s);
	}

	template <class Type>
	inline Type Parse(const StringView s)
	{
		if constexpr (std::is_integral_v<Type>)
		{
			return ParseInt<Type>(s);
		}
		else if constexpr (std::is_floating_point_v<Type>)
		{
			return ParseFloat<Type>(s);
		}
		else
		{
			Type to;

			if (not(std::wistringstream{ s.toWstr() } >> to))
			{
				detail::ThrowParseError(typeid(Type).name(), s);
			}

			return to;
		}
	}

	template <class Type>
	inline Optional<Type> ParseOpt(const StringView s)
	{
		if constexpr (std::is_integral_v<Type>)
		{
			return ParseIntOpt<Type>(s);
		}
		else if constexpr (std::is_floating_point_v<Type>)
		{
			return ParseFloatOpt<Type>(s);
		}
		else
		{
			Type to;

			if (not(std::wistringstream{ s.toWstr() } >> to))
			{
				return none;
			}

			return Optional<Type>(std::move(to));
		}
	}

	template <class Type, class U>
	inline Type ParseOr(StringView s, U&& defaultValue)
	{
		return ParseOpt<Type>(s).value_or(std::forward<U>(defaultValue));
	}
}
