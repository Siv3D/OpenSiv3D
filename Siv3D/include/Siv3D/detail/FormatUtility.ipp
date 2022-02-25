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

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		String ThousandsSeparateInt(String&& value, StringView separator);

		[[nodiscard]]
		String ThousandsSeparateFloat(String&& value, StringView separator);
	}

	template <class Type>
	inline String Pad(const Type& value, std::pair<int32, char32> padding)
	{
		return Format(value).lpadded(padding.first, padding.second);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline String ThousandsSeparate(const Int value, const StringView separator)
	{
		return detail::ThousandsSeparateInt(Format(value), separator);
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline String ThousandsSeparate(const Float value, const int32 decimalPlace, const Fixed fixed, const StringView separator)
	{
		return detail::ThousandsSeparateFloat(fixed ? ToFixed(value, decimalPlace) : ToString(value, decimalPlace), separator);
	}
}
