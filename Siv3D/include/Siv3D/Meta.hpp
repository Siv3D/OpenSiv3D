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
# include <type_traits>

namespace s3d
{
	namespace Meta
	{
		template <class, class = void>
		struct HasUnaryPlus : std::false_type {};

		template <class Type>
		struct HasUnaryPlus<Type, std::void_t<decltype(+std::declval<Type&>())>> : std::true_type {};


		template <class, class = void>
		struct HasNegate : std::false_type {};

		template <class Type>
		struct HasNegate<Type, std::void_t<decltype(-std::declval<Type&>())>> : std::true_type {};


		template <class, class = void>
		struct HasPreIncrement : std::false_type {};

		template <class Type>
		struct HasPreIncrement<Type, std::void_t<decltype(++std::declval<Type&>())>> : std::true_type {};


		template <class, class = void>
		struct HasPreDecrement : std::false_type {};

		template <class Type>
		struct HasPreDecrement<Type, std::void_t<decltype(--std::declval<Type&>())>> : std::true_type {};


		template <class, class = void>
		struct HasOperatorBool : std::false_type {};

		template <class Type>
		struct HasOperatorBool<Type, std::void_t<decltype(!std::declval<Type&>(), std::declval<Type&>() ? 0 : 0)>> : std::true_type {};


		template <class, class = void>
		struct HasLogicalNot : std::false_type {};

		template <class Type>
		struct HasLogicalNot<Type, std::void_t<decltype(!std::declval<Type&>())>> : std::true_type {};


		template <class, class = void>
		struct HasComplement : std::false_type {};

		template <class Type>
		struct HasComplement<Type, std::void_t<decltype(~std::declval<Type&>())>> : std::true_type {};


		template <class, class = void>
		struct HasAddressOf : std::false_type {};

		template <class Type>
		struct HasAddressOf<Type, std::void_t<decltype(&std::declval<Type&>())>> : std::true_type {};


		template <class, class = void>
		struct HasOverloadedAddressOf : std::false_type {};

		template <class Type>
		struct HasOverloadedAddressOf<Type, std::void_t<decltype(std::declval<Type&>().operator&())>> : std::true_type {};


		template <class, class = void>
		struct HasPostIncrement : std::false_type {};

		template <class Type>
		struct HasPostIncrement<Type, std::void_t<decltype(std::declval<Type&>()++)>> : std::true_type {};


		template <class, class = void>
		struct HasPostDecrement : std::false_type {};

		template <class Type>
		struct HasPostDecrement<Type, std::void_t<decltype(std::declval<Type&>()--)>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasPlus : std::false_type {};

		template <class Type, class Arg>
		struct HasPlus<Type, Arg, std::void_t<decltype(std::declval<Type&>() + std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasMinus : std::false_type {};

		template <class Type, class Arg>
		struct HasMinus<Type, Arg, std::void_t<decltype(std::declval<Type&>() - std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasMultiply : std::false_type {};

		template <class Type, class Arg>
		struct HasMultiply<Type, Arg, std::void_t<decltype(std::declval<Type&>()* std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasDivide : std::false_type {};

		template <class Type, class Arg>
		struct HasDivide<Type, Arg, std::void_t<decltype(std::declval<Type&>() / std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasModulus : std::false_type {};

		template <class Type, class Arg>
		struct HasModulus<Type, Arg, std::void_t<decltype(std::declval<Type&>() % std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasPlusAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasPlusAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() += std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasMinusAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasMinusAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() -= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasMultiplyAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasMultiplyAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() *= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasDivideAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasDivideAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() /= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasModulusAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasModulusAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() %= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasEqualTo : std::false_type {};

		template <class Type, class Arg>
		struct HasEqualTo<Type, Arg, std::void_t<decltype(std::declval<Type&>() == std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasNotEqualTo : std::false_type {};

		template <class Type, class Arg>
		struct HasNotEqualTo<Type, Arg, std::void_t<decltype(std::declval<Type&>() != std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasLessThan : std::false_type {};

		template <class Type, class Arg>
		struct HasLessThan<Type, Arg, std::void_t<decltype(std::declval<Type&>() < std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasLessThanEqual : std::false_type {};

		template <class Type, class Arg>
		struct HasLessThanEqual<Type, Arg, std::void_t<decltype(std::declval<Type&>() <= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasGreaterThan : std::false_type {};

		template <class Type, class Arg>
		struct HasGreaterThan<Type, Arg, std::void_t<decltype(std::declval<Type&>() > std::declval<Arg&>())>> : std::true_type{};


		template <class Type, class Arg = Type, class = void>
		struct HasGreaterThanEqual : std::false_type {};

		template <class Type, class Arg>
		struct HasGreaterThanEqual<Type, Arg, std::void_t<decltype(std::declval<Type&>() >= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasBitwiseAnd : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseAnd<Type, Arg, std::void_t<decltype(std::declval<Type&>()& std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasBitwiseOr : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseOr<Type, Arg, std::void_t<decltype(std::declval<Type&>() | std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasBitwiseXor : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseXor<Type, Arg, std::void_t<decltype(std::declval<Type&>() ^ std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasBitwiseAndAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseAndAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() &= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasBitwiseOrAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseOrAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() |= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasBitwiseXorAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasBitwiseXorAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() ^= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasLeftShift : std::false_type {};

		template <class Type, class Arg>
		struct HasLeftShift<Type, Arg, std::void_t<decltype(std::declval<Type&>() << std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasRightShift : std::false_type {};

		template <class Type, class Arg>
		struct HasRightShift<Type, Arg, std::void_t<decltype(std::declval<Type&>() >> std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasLeftShiftAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasLeftShiftAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() <<= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasRightShiftAssign : std::false_type {};

		template <class Type, class Arg>
		struct HasRightShiftAssign<Type, Arg, std::void_t<decltype(std::declval<Type&>() >>= std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasLogicalAnd : std::false_type {};

		template <class Type, class Arg>
		struct HasLogicalAnd<Type, Arg, std::void_t<decltype(std::declval<Type&>() && std::declval<Arg&>())>> : std::true_type {};


		template <class Type, class Arg = Type, class = void>
		struct HasLogicalOr : std::false_type {};

		template <class Type, class Arg>
		struct HasLogicalOr<Type, Arg, std::void_t<decltype(std::declval<Type&>() || std::declval<Arg&>())>> : std::true_type {};

		template <class Type> constexpr bool HasUnaryPlus_v = HasUnaryPlus<Type>::value;
		template <class Type> constexpr bool HasNegate_v = HasNegate<Type>::value;
		template <class Type> constexpr bool HasPreIncrement_v = HasPreIncrement<Type>::value;
		template <class Type> constexpr bool HasPreDecrement_v = HasPreDecrement<Type>::value;
		template <class Type> constexpr bool HasOperatorBool_v = HasOperatorBool<Type>::value;
		template <class Type> constexpr bool HasLogicalNot_v = HasLogicalNot<Type>::value;
		template <class Type> constexpr bool HasComplement_v = HasComplement<Type>::value;
		template <class Type> constexpr bool HasAddressOf_v = HasAddressOf<Type>::value;
		template <class Type> constexpr bool HasOverloadedAddressOf_v = HasOverloadedAddressOf<Type>::value;
		template <class Type> constexpr bool HasPostIncrement_v = HasPostIncrement<Type>::value;
		template <class Type> constexpr bool HasPostDecrement_v = HasPostDecrement<Type>::value;
		template <class Type, class Type2 = Type> constexpr bool HasPlus_v = HasPlus<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasMinus_v = HasMinus<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasMultiply_v = HasMultiply<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasDivide_v = HasDivide<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasModulus_v = HasModulus<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasPlusAssign_v = HasPlusAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasMinusAssign_v = HasMinusAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasMultiplyAssign_v = HasMultiplyAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasDivideAssign_v = HasDivideAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasModulusAssign_v = HasModulusAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasEqualTo_v = HasEqualTo<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasNotEqualTo_v = HasNotEqualTo<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasLessThan_v = HasLessThan<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasLessThanEqual_v = HasLessThanEqual<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasGreaterThan_v = HasGreaterThan<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasGreaterThanEqual_v = HasGreaterThanEqual<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasBitwiseAnd_v = HasBitwiseAnd<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasBitwiseOr_v = HasBitwiseOr<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasBitwiseXor_v = HasBitwiseXor<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasBitwiseAndAssign_v = HasBitwiseAndAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasBitwiseOrAssign_v = HasBitwiseOrAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasBitwiseXorAssign_v = HasBitwiseXorAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasLeftShift_v = HasLeftShift<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasRightShift_v = HasRightShift<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasLeftShiftAssign_v = HasLeftShiftAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasRightShiftAssign_v = HasRightShiftAssign<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasLogicalAnd_v = HasLogicalAnd<Type, Type2>::value;
		template <class Type, class Type2 = Type> constexpr bool HasLogicalOr_v = HasLogicalOr<Type, Type2>::value;

		template <class ArrayIsh>
		struct HasAsArray
		{
		private:
			template <class U>
			static auto test(int) -> decltype(std::declval<U>().asArray(), std::true_type());

			template <class U>
			static auto test(...) -> decltype(std::false_type());

		public:
			using type = decltype(test<ArrayIsh>(0));
			static constexpr bool value = type::value;
		};
	}
}
