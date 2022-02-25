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
# include <utility>
# include <cmath>
# include <functional>
# include "Meta.hpp"
# include "detail/Functor.ipp"

namespace s3d
{
	/// @brief プレースホルダー型 | Place holder type
	struct PlaceHolder_t
	{
		struct init_t {};

		explicit constexpr PlaceHolder_t(init_t) noexcept {}

		//////////////////////////////////////////////////
		//
		//	==
		//
		//////////////////////////////////////////////////

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator ==(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryEqualX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator ==(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryEqualY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator ==(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryEqual_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	!=
		//
		//////////////////////////////////////////////////

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator !=(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryNotEqualX_impl<TypeY>(std::forward<TypeY>(y));
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator !=(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryNotEqualY_impl<TypeX>(std::forward<TypeX>(x));
		}

		[[nodiscard]]
		friend constexpr auto operator !=(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryNotEqual_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	<
		//
		//////////////////////////////////////////////////

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator <(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryLessThanX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator <(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryLessThanY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator <(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryLessThan_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	<=
		//
		//////////////////////////////////////////////////

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator <=(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryLessThanEqualX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator <=(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryLessThanEqualY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator <=(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryLessThanEqual_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	>
		//
		//////////////////////////////////////////////////

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator >(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryGreaterThanX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator >(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryGreaterThanY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator >(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryGreaterThan_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	>=
		//
		//////////////////////////////////////////////////

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator >=(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryGreaterThanEqualX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator >=(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryGreaterThanEqualY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator >=(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryGreaterThanEqual_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	+
		//
		//////////////////////////////////////////////////		
		
		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator +(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryPlusX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator +(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryPlusY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator +(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryPlus_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	-
		//
		//////////////////////////////////////////////////		

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator -(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryMinusX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator -(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryMinusY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator -(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryMinus_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	*
		//
		//////////////////////////////////////////////////		

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator *(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryMultipliesX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator *(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryMultipliesY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator *(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryMultiplies_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	/
		//
		//////////////////////////////////////////////////		

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator /(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryDividesX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator /(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryDividesY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator /(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryDivides_impl{};
		}

		//////////////////////////////////////////////////
		//
		//	%
		//
		//////////////////////////////////////////////////		

		template <class TypeY>
		[[nodiscard]]
		friend constexpr auto operator %(PlaceHolder_t, TypeY&& y) noexcept
		{
			return detail::BinaryModulusX_impl<TypeY>{ std::forward<TypeY>(y) };
		}

		template <class TypeX>
		[[nodiscard]]
		friend constexpr auto operator %(TypeX&& x, PlaceHolder_t) noexcept
		{
			return detail::BinaryModulusY_impl<TypeX>{ std::forward<TypeX>(x) };
		}

		[[nodiscard]]
		friend constexpr auto operator %(PlaceHolder_t, PlaceHolder_t) noexcept
		{
			return detail::BinaryModulus_impl{};
		}
	};

	namespace Arg
	{
		/// @brief プレースホルダー | Place holder
		inline constexpr PlaceHolder_t _{ PlaceHolder_t::init_t{} };
	}
}
