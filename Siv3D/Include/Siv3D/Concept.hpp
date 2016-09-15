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
# include <type_traits>

namespace s3d
{
	namespace Concept
	{
		struct NotImplemented {};

		template <class Type> NotImplemented operator + (const Type&);
		template <class Type> NotImplemented operator - (const Type&);
		template <class Type> NotImplemented operator ++(const Type&);
		template <class Type> NotImplemented operator --(const Type&);
		template <class Type> NotImplemented operator ! (const Type&);
		template <class Type> NotImplemented operator ~ (const Type&);
		template <class Type> NotImplemented operator ++(const Type&, int);
		template <class Type> NotImplemented operator --(const Type&, int);
		template <class Type, class Arg> NotImplemented operator + (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator - (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator * (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator / (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator % (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator +=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator -=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator *=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator /=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator %=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator ==(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator !=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator < (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator <=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator > (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator >=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator & (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator | (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator ^ (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator &=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator |=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator ^=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator <<(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator >> (const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator <<=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator >>=(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator &&(const Type&, const Arg&);
		template <class Type, class Arg> NotImplemented operator ||(const Type&, const Arg&);

		namespace detail
		{
			template <class U>
			inline auto HasOperatorBoolCheck(U v) -> decltype(!v, v ? 0 : 1, std::true_type());
			inline auto HasOperatorBoolCheck(...) -> decltype(std::false_type());
		}

		template <class Type>
		struct HasUnaryPlus
			: std::bool_constant<!std::is_same<decltype(+(*(Type*)(0))), NotImplemented>::value> {};

		template <class Type>
		struct HasNegate
			: std::bool_constant<!std::is_same<decltype(-(*(Type*)(0))), NotImplemented>::value> {};

		template <class Type>
		struct HasPreIncrement
			: std::bool_constant<!std::is_same<decltype(++(*(Type*)(0))), NotImplemented>::value> {};

		template <class Type>
		struct HasPreDecrement
			: std::bool_constant<!std::is_same<decltype(--(*(Type*)(0))), NotImplemented>::value> {};

		template <class Type>
		struct HasOperatorBool
			: decltype(detail::HasOperatorBoolCheck(std::declval<Type>())) {};

		template <class Type>
		struct HasLogicalNot
			: std::bool_constant<!std::is_same<decltype(!(*(Type*)(0))), NotImplemented>::value> {};

		template <class Type>
		struct HasComplement
			: std::conditional_t<std::is_floating_point<Type>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(~(*(std::conditional_t<std::is_floating_point<Type>::value, int, Type>*)(0))), NotImplemented>::value>> {};

		template <class Type>
		struct HasPostIncrement
			: std::bool_constant<!std::is_same<decltype((*(Type*)(0))++), NotImplemented>::value> {};

		template <class Type>
		struct HasPostDecrement
			: std::bool_constant<!std::is_same<decltype((*(Type*)(0))--), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasPlus
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) + *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasMinus
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) - *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasMultiply
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) * *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasDivide
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) / *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasModulus
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) %
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasPlusAssign
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) += *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasMinusAssign
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) -= *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasMultiplyAssign
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) *= *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasDivideAssign
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) /= *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasModulusAssign
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) %=
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasEqualTo
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) == *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasNotEqualTo
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) != *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasLessThan
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) < *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasLessThanEqual
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) <= *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasGreaterThan
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) > *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasGreaterThanEqual
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) >= *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasBitwiseAnd
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) &
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasBitwiseOr
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) |
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasBitwiseXor
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) ^
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasBitwiseAndAssign
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) &=
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasBitwiseOrAssign
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) |=
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasBitwiseXorAssign
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) ^=
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasLeftShift
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) <<
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasRightShift
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) >>
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasLeftShiftAssign
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) <<=
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasRightShiftAssign
			: std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, std::false_type,
				std::bool_constant<!std::is_same<decltype(
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Type>*)(0) >>=
					*(std::conditional_t<std::is_floating_point<Type>::value && std::is_floating_point<Arg>::value, int, Arg>*)(0)),
				NotImplemented>::value>> {};

		template <class Type, class Arg = Type>
		struct HasLogicalAnd
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) && *(Arg*)(0)), NotImplemented>::value> {};

		template <class Type, class Arg = Type>
		struct HasLogicalOr
			: std::bool_constant<!std::is_same<decltype(*(Type*)(0) || *(Arg*)(0)), NotImplemented>::value> {};

		/*
		template <class Type> constexpr bool HasUnaryPlus_v		= HasUnaryPlus<Type>::value;
		template <class Type> constexpr bool HasNegate_v		= HasNegate<Type>::value;
		template <class Type> constexpr bool HasPreIncrement_v	= HasPreIncrement<Type>::value;
		template <class Type> constexpr bool HasPreDecrement_v	= HasPreDecrement<Type>::value;
		template <class Type> constexpr bool HasOperatorBool_v	= HasOperatorBool<Type>::value;
		template <class Type> constexpr bool HasLogicalNot_v	= HasLogicalNot<Type>::value;
		template <class Type> constexpr bool HasComplement_v	= HasComplement<Type>::value;
		template <class Type> constexpr bool HasPostIncrement_v	= HasPostIncrement<Type>::value;
		template <class Type> constexpr bool HasPostDecrement_v	= HasPostDecrement<Type>::value;
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
