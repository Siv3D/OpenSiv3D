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
# include "Optional.hpp"
# include "BigInt.hpp"
# include "BigFloat.hpp"

namespace s3d
{
	template <class Type>
	struct IsOptional : std::false_type {};

	template <class Type>
	struct IsOptional<Optional<Type>> : std::true_type {};

	template <>
	struct IsOptional<nullopt_t> : std::true_type {};


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
}
