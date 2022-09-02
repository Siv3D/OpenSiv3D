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

# include <Siv3D/Parse.hpp>

namespace s3d
{
	namespace detail
	{
		void ThrowParseError(const char* type, const StringView s)
		{
			throw ParseError{ U"Parse<{}>(\"{}\") failed"_fmt(Demangle(type), s) };
		}
	}

	template <>
	bool Parse<bool>(const StringView s)
	{
		return ParseBool(s);
	}

	template <>
	char Parse<char>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	char32 Parse<char32>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return t[0];
	}

	template <>
	String Parse<String>(const StringView s)
	{
		return String(s).trimmed();
	}

	template <>
	Optional<bool> ParseOpt<bool>(const StringView s)
	{
		return ParseBoolOpt(s);
	}

	template <>
	Optional<char> ParseOpt<char>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	Optional<char32> ParseOpt<char32>(const StringView s)
	{
		const String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return t[0];
	}

	template <>
	Optional<String> ParseOpt<String>(const StringView s)
	{
		String t = String(s).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return Optional<String>(std::move(t));
	}
}
