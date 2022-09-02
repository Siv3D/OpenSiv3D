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

namespace s3d::detail
{
	//////////////////////////////////////////////////
	//
	//	Abs
	//
	//////////////////////////////////////////////////

	struct Abs_impl
	{
	# if __cpp_lib_concepts
		template <Concept::Signed Signed>
	# else
		template <class Signed, std::enable_if_t<std::is_signed_v<Signed>>* = nullptr>
	# endif
		[[nodiscard]]
		constexpr auto operator ()(Signed x) const noexcept
		{
			if (x < 0)
			{
				return -x;
			}
			else
			{
				return x;
			}
		}
	};

	//////////////////////////////////////////////////
	//
	//	FromEnum
	//
	//////////////////////////////////////////////////

	struct FromEnum_impl
	{
		SIV3D_CONCEPT_ENUM
		[[nodiscard]]
		constexpr auto operator ()(Enum x) const noexcept
		{
			return static_cast<std::underlying_type_t<Enum>>(x);
		}
	};

	//////////////////////////////////////////////////
	//
	//	ToEnum
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_ENUM
	struct ToEnum_impl
	{
		[[nodiscard]]
		constexpr auto operator ()(std::underlying_type_t<Enum> x) const noexcept
		{
			return Enum{ x };
		}
	};

	//////////////////////////////////////////////////
	//
	//	IsOdd
	//
	//////////////////////////////////////////////////

	struct IsOdd_impl
	{
		/// @brief 数が奇数かを返します。
		/// @tparam Type 数値型
		/// @param x 数
		/// @return 数が奇数の場合 true, それ以外の場合は false
		template <class Type>
		[[nodiscard]]
		constexpr bool operator()(const Type& x) const
		{
			return (x % 2) != 0;
		}
	};

	//////////////////////////////////////////////////
	//
	//	IsEven
	//
	//////////////////////////////////////////////////

	struct IsEven_impl
	{
		/// @brief 数が偶数かを返します。
		/// @tparam Type 数値型
		/// @param x 数
		/// @return 数が偶数の場合 true, それ以外の場合は false
		template <class Type>
		[[nodiscard]]
		constexpr bool operator()(const Type& x) const
		{
			return (x % 2) == 0;
		}
	};

	//////////////////////////////////////////////////
	//
	//	Identity
	//
	//////////////////////////////////////////////////

	struct Identity_impl
	{
		using is_transparent = void;

		template <class Type>
		[[nodiscard]]
		constexpr Type&& operator()(Type&& x) const noexcept
		{
			return std::forward<Type>(x);
		}
	};
}
