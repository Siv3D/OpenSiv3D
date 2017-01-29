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
# include "Fwd.hpp"

namespace s3d
{
	template <class FloatType>
	FloatType ParseFloat(const String& str);

	template <>
	float ParseFloat<float>(const String& str);

	template <>
	double ParseFloat<double>(const String& str);

	template <>
	inline long double ParseFloat<long double>(const String& str)
	{
		return ParseFloat<double>(str);
	}

	template <class FloatType>
	Optional<FloatType> ParseFloatOpt(const String& str);

	template <>
	Optional<float> ParseFloatOpt<float>(const String& str);

	template <>
	Optional<double> ParseFloatOpt<double>(const String& str);

	template <>
	Optional<long double> ParseFloatOpt<long double>(const String& str);
}
