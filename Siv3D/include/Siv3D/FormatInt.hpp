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
# include "Common.hpp"
# include "PredefinedNamedParameter.hpp"
# include "LetterCase.hpp"
# include "String.hpp"

namespace s3d
{
	[[nodiscard]]
	String ToString(int8 value);

	[[nodiscard]]
	String ToString(uint8 value);

	[[nodiscard]]
	String ToString(int16 value);

	[[nodiscard]]
	String ToString(uint16 value);

	[[nodiscard]]
	String ToString(int32 value);

	[[nodiscard]]
	String ToString(uint32 value);

	[[nodiscard]]
	String ToString(long value);

	[[nodiscard]]
	String ToString(unsigned long value);

	[[nodiscard]]
	String ToString(long long value);

	[[nodiscard]]
	String ToString(unsigned long long value);


	[[nodiscard]]
	String ToString(char value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(int8 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(uint8 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(int16 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(uint16 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(int32 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(uint32 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(unsigned long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(long long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(unsigned long long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);


	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline String ToBinary(Int value);

	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline String ToOctal(Int value);

	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline String ToHex(Int value, LetterCase letterCase = LetterCase::Upper);
}

# include "detail/FormatInt.ipp"
