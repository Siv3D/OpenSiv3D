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
# include "PlaceHolder.hpp"

namespace s3d
{
////////////////////////////////////////////////////////////////
//
//	==
//
////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryEqualX_impl
		{
			const TypeY& y;

			constexpr BinaryEqualX_impl(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) == y))
			{
				return std::forward<TypeX>(x) == y;
			}
		};

		template <class TypeX>
		struct BinaryEqualY_impl
		{
			const TypeX& x;

			constexpr BinaryEqualY_impl(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x == std::forward<TypeY>(y)))
			{
				return x == std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Equal() noexcept
	{
		return std::equal_to<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Equal(const TypeX& x) noexcept
	{
		return detail::BinaryEqualY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Equal(TypeX&& x, TypeY&& y) noexcept(noexcept(std::equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Equal(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Equal(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Equal(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::equal_to<Type>();
	}
}
