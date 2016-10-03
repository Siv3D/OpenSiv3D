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
	namespace Arg
	{
		template <class ValueType, class ArgType>
		struct NamedParameter
		{
			using base = NamedParameter;

			ValueType value;

			constexpr NamedParameter()
				: value() {}

			explicit constexpr NamedParameter(ValueType _val)
				: value(_val) {}

			constexpr ArgType operator =(ValueType val) const
			{
				return ArgType{ val };
			}

			explicit constexpr operator ValueType() const
			{
				return value;
			}
		};

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		
		template <class Type>
		struct r_ : NamedParameter<Type, r_<Type>>
		{
			using base::base;
			using base::operator=;

			template <class U, std::enable_if_t<std::is_convertible<U, Type>::value>* = nullptr>
			constexpr r_(const r_<U>& other)
				: r_(static_cast<Type>(other.value)) {}
        };

		constexpr struct r_conv
		{
			template <class Type>
			constexpr r_<Type> operator =(Type val) const
			{
				return r_<Type>{ val };
			}
		} r;

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		template <class Type>
		struct theta_ : NamedParameter<Type, theta_<Type>>
		{
			using base::base;
			using base::operator=;

			template <class U, std::enable_if_t<std::is_convertible<U, Type>::value>* = nullptr>
			constexpr theta_(const theta_<U>& other)
				: theta_(static_cast<Type>(other.value)) {}
		};

		constexpr struct theta_conv
		{
			template <class Type>
			constexpr theta_<Type> operator =(Type val) const
			{
				return theta_<Type>{ val };
			}
		} theta;

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//
	}
}


