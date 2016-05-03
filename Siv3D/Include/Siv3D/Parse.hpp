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

# pragma once
# include "Fwd.hpp"
# include "ParseInt.hpp"
# include "ParseFloat.hpp"
# include "ParseBool.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		Parse
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <class Type, std::enable_if_t<!std::is_arithmetic<Type>::value>* = nullptr>
	inline Type Parse(const String& str)
	{
		Type to;

		if (std::wistringstream{ str.str() } >> to)
		{
			return to;
		}

		return to;
	}

	template <class IntegerType, std::enable_if_t<std::is_integral<IntegerType>::value>* = nullptr>
	inline IntegerType Parse(const String& str)
	{
		return ParseInt<IntegerType>(str);
	}

	template <class FloatType, std::enable_if_t<std::is_floating_point<FloatType>::value>* = nullptr>
	inline FloatType Parse(const String& str)
	{
		return ParseFloat<FloatType>(str);
	}

	template <>
	inline bool Parse<bool>(const String& str)
	{
		return ParseBool(str);
	}

	template <>
	inline char Parse<char>(const String& str)
	{
		const String t = str.trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return static_cast<char>(t[0]);
	}

	template <>
	inline wchar Parse<wchar>(const String& str)
	{
		const String t = str.trimmed();

		if (t.isEmpty())
		{
			return 0;
		}

		return t[0];
	}

	template <>
	inline String Parse<String>(const String& str)
	{
		return str.trimmed();
	}
}
