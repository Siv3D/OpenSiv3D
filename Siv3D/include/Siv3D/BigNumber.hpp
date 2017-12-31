//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "BigInt.hpp"
# include "BigFloat.hpp"

namespace s3d
{
	template <class Type>
	struct IsBigInt : std::false_type {};

	template <>
	struct IsBigInt<BigInt> : std::true_type {};


	template <class Type>
	struct IsBigFloat : std::false_type {};

	template <>
	struct IsBigFloat<BigFloat> : std::true_type {};


	template <class Type>
	struct IsBigNumber : std::false_type {};

	template <>
	struct IsBigNumber<BigInt> : std::true_type {};

	template <>
	struct IsBigNumber<BigFloat> : std::true_type {};


	template <class Type> constexpr bool IsBigInt_v		= IsBigInt<Type>::value;
	template <class Type> constexpr bool IsBigFloat_v	= IsBigFloat<Type>::value;
	template <class Type> constexpr bool IsBigNumber_v	= IsBigNumber<Type>::value;
}
