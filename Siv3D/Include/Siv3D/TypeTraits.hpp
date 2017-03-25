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
	template <class T, class U, std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>* = nullptr>
	struct CommonFloat
	{
		using type = std::conditional_t<!std::is_floating_point<T>::value && !std::is_floating_point<U>::value, double, std::common_type_t<T, U>>;
	};

	template <class T, class U, std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>* = nullptr>
	using CommonFloat_t = typename CommonFloat<T, U>::type;
}
