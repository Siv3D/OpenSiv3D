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
}
