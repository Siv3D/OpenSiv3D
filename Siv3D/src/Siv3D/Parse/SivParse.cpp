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

# include <Siv3D/Parse.hpp>

namespace s3d
{
	template <>
	bool Parse<bool>(StringView text)
	{
		return ParseBool(text);
	}

	template <>
	char Parse<char>(StringView text)
	{
		const String t = String(text).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	[[nodiscard]] char32 Parse<char32>(StringView text)
	{
		const String t = String(text).trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return t[0];
	}

	template <>
	String Parse<String>(StringView text)
	{
		return String(text).trimmed();
	}



	template <>
	Optional<bool> ParseOpt<bool>(StringView text)
	{
		return ParseBoolOpt(text);
	}

	template <>
	Optional<char> ParseOpt<char>(StringView text)
	{
		const String t = String(text).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	Optional<char32> ParseOpt<char32>(StringView text)
	{
		const String t = String(text).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return t[0];
	}

	template <>
	Optional<String> ParseOpt<String>(StringView text)
	{
		String t = String(text).trimmed();

		if (t.isEmpty())
		{
			return none;
		}

		return Optional<String>(std::move(t));
	}
}
