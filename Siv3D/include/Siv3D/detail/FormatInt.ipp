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
		inline constexpr size_t Uint32Width = (std::numeric_limits<uint32>::digits10 + 1);

		inline constexpr size_t Int32Width = (std::numeric_limits<int32>::digits10 + 2);

		void AppendUint32(char32** p, uint32 value);

		void AppendInt32(char32** p, int32 value);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline String ToBinary(const Int value)
	{
		return ToString(value, Arg::radix = 2);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline String ToOctal(const Int value)
	{
		return ToString(value, Arg::radix = 8);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline String ToHex(const Int value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}
}
