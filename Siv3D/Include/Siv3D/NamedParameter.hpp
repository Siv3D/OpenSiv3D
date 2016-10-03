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
			ValueType value;

			constexpr NamedParameter()
				: value() {}

			// *TODO* explicit は必要？
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

# define SIV3D_DECLEAR_NAMED_ARGUMENT(name)	template <class Type>\
struct name##_ : NamedParameter<Type, name##_<Type>>\
{\
	using base = NamedParameter<Type, name##_<Type>>;\
	using base::base;\
	using base::operator=;\
	template <class U, std::enable_if_t<std::is_convertible<U, Type>::value>* = nullptr>\
	constexpr name##_(const name##_<U>& other)\
		: name##_(static_cast<Type>(other.value)) {}\
};\
\
constexpr struct name##_conv\
{\
	template <class Type>\
	constexpr name##_<Type> operator =(Type val) const\
	{\
		return name##_<Type>{ val };\
	}\
} name{}\

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		SIV3D_DECLEAR_NAMED_ARGUMENT(r);
		SIV3D_DECLEAR_NAMED_ARGUMENT(theta);
		SIV3D_DECLEAR_NAMED_ARGUMENT(center);
	}
}


