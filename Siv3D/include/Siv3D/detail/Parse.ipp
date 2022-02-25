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
				throw ParseError(U"Parse<{}>(\"{}\") failed"_fmt(Demangle(typeid(Type).name()), s));
			}

			return to;
		}
	}

	template <>
	inline bool Parse<bool>(const StringView s)
	{
		return ParseBool(s);
	}

	template <>
	inline char Parse<char>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	inline char32 Parse<char32>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return t[0];
	}

	template <>
	inline String Parse<String>(const StringView s)
	{
		return String(s).trimmed();
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

	template <>
	inline Optional<bool> ParseOpt<bool>(const StringView s)
	{
		return ParseBoolOpt(s);
	}

	template <>
	inline Optional<char> ParseOpt<char>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	inline Optional<char32> ParseOpt<char32>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return t[0];
	}

	template <>
	inline Optional<String> ParseOpt<String>(const StringView s)
	{
		String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return Optional<String>(std::move(t));
	}

	template <class Type, class U>
	inline Type ParseOr(StringView s, U&& defaultValue)
	{
		return ParseOpt<Type>(s).value_or(std::forward<U>(defaultValue));
	}
}
