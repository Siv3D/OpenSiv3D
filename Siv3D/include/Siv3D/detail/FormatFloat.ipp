﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "../FloatingPoint.hpp"
# include "../FormatInt.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr size_t FormatFloatBufferSize = 384;

		[[nodiscard]]
		String FormatFloat(double value, int32 decimalPlace, bool fixed);

		[[nodiscard]]
		size_t FormatFloat(char32(&dst)[FormatFloatBufferSize], double value, int32 decimalPlace, bool fixed);
	}

	inline String ToString(const float value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, false);
	}

	inline String ToString(const double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, false);
	}

	inline String ToString(const long double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, false);
	}

	inline String ToFixed(const float value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, true);
	}

	inline String ToFixed(const double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(value, decimalPlace, true);
	}

	inline String ToFixed(const long double value, const int32 decimalPlace)
	{
		return detail::FormatFloat(static_cast<double>(value), decimalPlace, true);
	}

	inline String ToBinary(const float value)
	{
		return ToBinary(AsUint32(value));
	}

	inline String ToBinary(const double value)
	{
		return ToBinary(AsUint64(value));
	}

	inline String ToOctal(const float value)
	{
		return ToOctal(AsUint32(value));
	}

	inline String ToOctal(const double value)
	{
		return ToOctal(AsUint64(value));
	}

	inline String ToHex(const float value)
	{
		return ToHex(AsUint32(value));
	}

	inline String ToHex(const double value)
	{
		return ToHex(AsUint64(value));
	}
}
