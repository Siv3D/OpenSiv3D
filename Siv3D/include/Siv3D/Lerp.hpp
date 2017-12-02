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
	namespace detail
	{
		template <class, class = std::void_t<>>
		struct HasLerp : std::false_type {};

		template <class Type>
		struct HasLerp<Type, std::void_t<decltype(std::declval<Type&>().lerp(std::declval<const Type&>(), 0.0))>> : std::true_type {};

		template <class Type> constexpr bool HasLerp_v = HasLerp<Type>::value;
	}

	namespace Math
	{
		/// <summary>
		/// 線形補間した結果を返します。
		/// </summary>
		template <class T, class U, class V>
		constexpr auto Lerp(const T& v1, const U& v2, V f)
		{
			if constexpr(s3d::detail::HasLerp_v<T>)
			{
				return v1.lerp(v2, f);
			}
			else
			{
				return v1 + (v2 - v1) * f;
			}
		}
	}
}
