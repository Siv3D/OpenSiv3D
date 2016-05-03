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
	Type Parse(const String& str)
	{
		Type to;

		if (std::wistringstream{ str.str() } >> to)
		{
			return to;
		}

		return to;
	}
}
