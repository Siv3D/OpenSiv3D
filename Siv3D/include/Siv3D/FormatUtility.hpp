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

# pragma once
# include "Format.hpp"
# include "BigNumber.hpp"

namespace s3d
{
	/// <summary>
	/// 値を指定した文字数の文字列に変換します。
	/// </summary>
	/// <param name="value">
	/// 変換する値
	/// </param>
	/// <param name="padding">
	/// 文字数と詰め文字のペア
	/// </param>
	/// <returns>
	/// 変換した文字列
	/// </returns>
	template <class Type>
	[[nodiscard]] inline String Pad(const Type& value, const std::pair<int32, char32>& padding)
	{
		return Format(value).lpadded(padding.first, padding.second);
	}

	template <class Type, std::enable_if_t<std::is_integral_v<Type> || IsBigInt_v<Type>>* = nullptr>
	[[nodiscard]] inline String ThousandsSeparate(const Type& value, const String& separator = U",")
	{
		String result = Format(value);

		size_t count = 0;

		for (size_t i = result.size(); i != 0; --i)
		{
			if (++count == 4 && !(i == 1 && result[0] == S3DCHAR('-')))
			{
				result.insert(i, separator);

				count = 1;
			}
		}

		return result;
	}

	template <class Type, std::enable_if_t<std::is_floating_point_v<Type>>* = nullptr>
	[[nodiscard]] inline String ThousandsSeparate(const Type& value, const int32 decimalPlace = 3, bool fixed = false, const String& separator = U",")
	{
		String result = fixed ? ToFixed(value, decimalPlace) : ToString(value, decimalPlace);

		const size_t zeroPos = result.lastIndexOf(S3DCHAR('.'));

		size_t count = 0;

		for (size_t i = (zeroPos == String::npos) ? result.size() : zeroPos; i != 0; --i)
		{
			if (++count == 4 && !(i == 1 && result[0] == S3DCHAR('-')))
			{
				result.insert(i, separator);

				count = 1;
			}
		}

		return result;
	}
}
