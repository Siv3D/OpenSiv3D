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
# define SIV3D_MAKE_NAMED_PARAMETER(name)	template <class ValueType>\
struct name##_\
{\
private:\
	ValueType m_value;\
\
public:\
\
	constexpr name##_()\
		: m_value() {}\
\
	explicit constexpr name##_(ValueType _val)\
		: m_value(_val) {}\
\
	template <class U, class V = ValueType, std::enable_if_t<std::is_convertible<U, V>::value>* = nullptr>\
	constexpr name##_(const name##_<U>& other)\
		: name##_(static_cast<ValueType>(*other)) {}\
\
	constexpr name##_ operator =(ValueType val) const\
	{\
		return name##_{ val };\
	}\
\
	constexpr ValueType const* operator ->() const\
	{\
		return &m_value;\
	}\
\
	constexpr ValueType const& operator *() const\
	{\
		return m_value;\
	}\
\
	constexpr ValueType const& value() const\
	{\
		return m_value;\
	}\
};\
\
constexpr struct name##_conv\
{\
	template <class Type>\
	constexpr name##_<Type> operator =(Type val) const\
	{\
		return name##_<Type>{ val };\
	}\
\
	template <class Type>\
	constexpr name##_<Type> operator()(Type val) const\
	{\
		return name##_<Type>{ val };\
	}\
} name{}\

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		SIV3D_MAKE_NAMED_PARAMETER(generator);
		SIV3D_MAKE_NAMED_PARAMETER(radix);
		SIV3D_MAKE_NAMED_PARAMETER(upperCase);
		SIV3D_MAKE_NAMED_PARAMETER(r);
		SIV3D_MAKE_NAMED_PARAMETER(theta);
		SIV3D_MAKE_NAMED_PARAMETER(center);
	}
}


