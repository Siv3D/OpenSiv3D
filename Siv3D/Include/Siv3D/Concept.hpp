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
# include <type_traits>

namespace s3d
{
	namespace Concept
	{
		template <class, class = std::void_t<>>
		struct HasUnaryPlus : std::false_type {};

		template <class Type>
		struct HasUnaryPlus<Type, std::void_t<decltype(+std::declval<Type&>())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasNegate : std::false_type {};

		template <class Type>
		struct HasNegate<Type, std::void_t<decltype(-std::declval<Type&>())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasPreIncrement : std::false_type {};

		template <class Type>
		struct HasPreIncrement<Type, std::void_t<decltype(++std::declval<Type&>())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasPreDecrement : std::false_type {};

		template <class Type>
		struct HasPreDecrement<Type, std::void_t<decltype(--std::declval<Type&>())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasOperatorBool : std::false_type {};

		template <class Type>
		struct HasOperatorBool<Type, std::void_t<decltype(!std::declval<Type&>(), std::declval<Type&>() ? 0 : 0)>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasLogicalNot : std::false_type {};

		template <class Type>
		struct HasLogicalNot<Type, std::void_t<decltype(!std::declval<Type&>())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasComplement : std::false_type {};

		template <class Type>
		struct HasComplement<Type, std::void_t<decltype(~std::declval<Type&>())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasAddressOf : std::false_type {};

		template <class Type>
		struct HasAddressOf<Type, std::void_t<decltype(&std::declval<Type&>())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasOverloadedAddressOf : std::false_type {};

		template <class Type>
		struct HasOverloadedAddressOf<Type, std::void_t<decltype(std::declval<Type&>().operator&())>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasPostIncrement : std::false_type {};

		template <class Type>
		struct HasPostIncrement<Type, std::void_t<decltype(std::declval<Type&>()++)>> : std::true_type {};


		template <class, class = std::void_t<>>
		struct HasPostDecrement : std::false_type {};

		template <class Type>
		struct HasPostDecrement<Type, std::void_t<decltype(std::declval<Type&>()--)>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasPlus : std::false_type {};

		template <class Type, class Arg>
		struct HasPlus<Type, Arg, std::void_t<decltype(std::declval<Type&>() + std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasMinus : std::false_type {};

		template <class Type, class Arg>
		struct HasMinus<Type, Arg, std::void_t<decltype(std::declval<Type&>() - std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasMultiply : std::false_type {};

		template <class Type, class Arg>
		struct HasMultiply<Type, Arg, std::void_t<decltype(std::declval<Type&>() * std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasDivide : std::false_type {};

		template <class Type, class Arg>
		struct HasDivide<Type, Arg, std::void_t<decltype(std::declval<Type&>() / std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasModulus : std::false_type {};

		template <class Type, class Arg>
		struct HasModulus<Type, Arg, std::void_t<decltype(std::declval<Type&>() % std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasPlusAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasPlusAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() += std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasMinusAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasMinusAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() -= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasMultiplyAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasMultiplyAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() *= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasDivideAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasDivideAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() /= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasModulusAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasModulusAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() %= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasEqualTo : std::false_type {};

		template <class Type, class Arg>
		struct HasEqualTo<Type, Arg, std::void_t<decltype(std::declval<Type&>() == std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasNotEqualTo : std::false_type {};

		template <class Type, class Arg>
		struct HasNotEqualTo<Type, Arg, std::void_t<decltype(std::declval<Type&>() != std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasLessThan : std::false_type {};

		template <class Type, class Arg>
		struct HasLessThan<Type, Arg, std::void_t<decltype(std::declval<Type&>() < std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasLessThanEqual : std::false_type {};

		template <class Type, class Arg>
		struct HasLessThanEqual<Type, Arg, std::void_t<decltype(std::declval<Type&>() <= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasGreaterThan : std::false_type {};

		template <class Type, class Arg>
		struct HasGreaterThan<Type, Arg, std::void_t<decltype(std::declval<Type&>() > std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasGreaterThanEqual : std::false_type {};

		template <class Type, class Arg>
		struct HasGreaterThanEqual<Type, Arg, std::void_t<decltype(std::declval<Type&>() >= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasBitwiseAnd : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseAnd<Type, Arg, std::void_t<decltype(std::declval<Type&>() & std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasBitwiseOr : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseOr<Type, Arg, std::void_t<decltype(std::declval<Type&>() | std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasBitwiseXor : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseXor<Type, Arg, std::void_t<decltype(std::declval<Type&>() ^ std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasBitwiseAndAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseAndAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() &= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasBitwiseOrAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseOrAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() |= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasBitwiseXorAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseXorAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() ^= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasLeftShift : std::false_type {};

		template <class Type, class Arg>
		struct HasLeftShift<Type, Arg, std::void_t<decltype(std::declval<Type&>() << std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasRightShift : std::false_type {};

		template <class Type, class Arg>
		struct HasRightShift<Type, Arg, std::void_t<decltype(std::declval<Type&>() >> std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasLeftShiftAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasLeftShiftAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() <<= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasRightShiftAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasRightShiftAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() >>= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasLogicalAnd : std::false_type {};

		template <class Type, class Arg>
		struct HasLogicalAnd<Type, Arg, std::void_t<decltype(std::declval<Type&>() && std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = std::void_t<>>
		struct HasLogicalOr : std::false_type {};

		template <class Type, class Arg>
		struct HasLogicalOr<Type, Arg, std::void_t<decltype(std::declval<Type&>() || std::declval<Arg&>())>> : std::true_type {};
	
		/*
		template <class Type> constexpr bool HasUnaryPlus_v				= HasUnaryPlus<Type>::value;
		template <class Type> constexpr bool HasNegate_v				= HasNegate<Type>::value;
		template <class Type> constexpr bool HasPreIncrement_v			= HasPreIncrement<Type>::value;
		template <class Type> constexpr bool HasPreDecrement_v			= HasPreDecrement<Type>::value;
		template <class Type> constexpr bool HasOperatorBool_v			= HasOperatorBool<Type>::value;
		template <class Type> constexpr bool HasLogicalNot_v			= HasLogicalNot<Type>::value;
		template <class Type> constexpr bool HasComplement_v			= HasComplement<Type>::value;
		template <class Type> constexpr bool HasAddressOf_v				= HasAddressOf<Type>::value;
		template <class Type> constexpr bool HasOverloadedAddressOf_v	= HasOverloadedAddressOf<Type>::value;
		template <class Type> constexpr bool HasPostIncrement_v			= HasPostIncrement<Type>::value;
		template <class Type> constexpr bool HasPostDecrement_v			= HasPostDecrement<Type>::value;
		template <class Type, class Arg = Type> constexpr bool HasPlus_v				= HasPlus<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasMinus_v				= HasMinus<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasMultiply_v			= HasMultiply<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasDivide_v				= HasDivide<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasModulus_v				= HasModulus<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasPlusAssign_v			= HasPlusAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasMinusAssign_v			= HasMinusAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasMultiplyAssign_v		= HasMultiplyAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasDivideAssign_v		= HasDivideAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasModulusAssign_v		= HasModulusAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasEqualTo_v				= HasEqualTo<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasNotEqualTo_v			= HasNotEqualTo<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasLessThan_v			= HasLessThan<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasLessThanEqual_v		= HasLessThanEqual<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasGreaterThan_v			= HasGreaterThan<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasGreaterThanEqual_v	= HasGreaterThanEqual<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasBitwiseAnd_v			= HasBitwiseAnd<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasBitwiseOr_v			= HasBitwiseOr<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasBitwiseXor_v			= HasBitwiseXor<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasBitwiseAndAssign_v	= HasBitwiseAndAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasBitwiseOrAssign_v		= HasBitwiseOrAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasBitwiseXorAssign_v	= HasBitwiseXorAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasLeftShift_v			= HasLeftShift<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasRightShift_v			= HasRightShift<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasLeftShiftAssign_v		= HasLeftShiftAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasRightShiftAssign_v	= HasRightShiftAssign<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasLogicalAnd_v			= HasLogicalAnd<Type, Arg>::value;
		template <class Type, class Arg = Type> constexpr bool HasLogicalOr_v			= HasLogicalOr<Type, Arg>::value;
		*/
	}
}
