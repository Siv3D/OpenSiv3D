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

		template <class Type>
		struct HasUnaryPlus
		{
			static const bool value = !std::is_same<decltype(+(*(Type*)(0))), NotImplemented>::value;
		};

		template <class Type>
		struct HasNegate
		{
			static const bool value = !std::is_same<decltype(-(*(Type*)(0))), NotImplemented>::value;
		};

		template <class Type>
		struct HasPreIncrement
		{
			static const bool value = !std::is_same<decltype(++(*(Type*)(0))), NotImplemented>::value;
		};

		template <class Type>
		struct HasPreDecrement
		{
			static const bool value = !std::is_same<decltype(--(*(Type*)(0))), NotImplemented>::value;
		};

		template <class Type>
		struct HasOperatorBool
		{
		private:

			template <class U>
			static auto check(U v) -> decltype(!v, v ? 0 : 1, std::true_type());
			static auto check(...) -> decltype(std::false_type());

		public:

			static const bool value = decltype(check(std::declval<Type>()))::value;
		};

		template <class Type>
		struct HasLogicalNot
		{
			static const bool value = !std::is_same<decltype(!(*(Type*)(0))), NotImplemented>::value;
		};

		template <class Type>
		struct HasComplement
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(~(*(Type*)(0))), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type>
		struct HasPostIncrement
		{
			static const bool value = !std::is_same<decltype((*(Type*)(0))++), NotImplemented>::value;
		};

		template <class Type>
		struct HasPostDecrement
		{
			static const bool value = !std::is_same<decltype((*(Type*)(0))--), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasPlus
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) + *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasMinus
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) - *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasMultiply
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) * *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasDivide
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) / *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasModulus
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) % *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasPlusAssign
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) += *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasMinusAssign
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) -= *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasMultiplyAssign
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) *= *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasDivideAssign
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) /= *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasModulusAssign
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) %= *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasEqualTo
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) == *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasNotEqualTo
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) != *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasLessThan
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) < *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasLessThanEqual
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) <= *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasGreaterThan
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) > *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasGreaterThanEqual
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) >= *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasBitwiseAnd
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) & *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasBitwiseOr
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) | *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasBitwiseXor
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) ^ *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasBitwiseAndAssign
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) &= *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasBitwiseOrAssign
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) |= *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasBitwiseXorAssign
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) ^= *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasLeftShift
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) << *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasRightShift
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) >> *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasLeftShiftAssign
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) <<= *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasRightShiftAssign
		{
		private:

			template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return false;
			}

			template <class T = Type, std::enable_if_t<!std::is_floating_point<T>::value>* = nullptr>
			static constexpr bool getValue()
			{
				return !std::is_same<decltype(*(Type*)(0) >>= *(Arg*)(0)), NotImplemented>::value;
			}

		public:

			static const bool value = getValue();
		};

		template <class Type, class Arg = Type>
		struct HasLogicalAnd
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) && *(Arg*)(0)), NotImplemented>::value;
		};

		template <class Type, class Arg = Type>
		struct HasLogicalOr
		{
			static const bool value = !std::is_same<decltype(*(Type*)(0) || *(Arg*)(0)), NotImplemented>::value;
		};

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
