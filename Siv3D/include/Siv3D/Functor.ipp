//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d::detail
{
	//////////////////////////////////////////////////
	//
	//	==
	//
	//////////////////////////////////////////////////
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

	//////////////////////////////////////////////////
	//
	//	!=
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryNotEqualX_impl
	{
		const TypeY& y;

		constexpr BinaryNotEqualX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) != y))
		{
			return std::forward<TypeX>(x) != y;
		}
	};

	template <class TypeX>
	struct BinaryNotEqualY_impl
	{
		const TypeX& x;

		constexpr BinaryNotEqualY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x != std::forward<TypeY>(y)))
		{
			return x != std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	<
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryLessThanX_impl
	{
		const TypeY& y;

		constexpr BinaryLessThanX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) < y))
		{
			return std::forward<TypeX>(x) < y;
		}
	};

	template <class TypeX>
	struct BinaryLessThanY_impl
	{
		const TypeX& x;

		constexpr BinaryLessThanY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x < std::forward<TypeY>(y)))
		{
			return x < std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	<=
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryLessThanEqualX_impl
	{
		const TypeY& y;

		constexpr BinaryLessThanEqualX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) <= y))
		{
			return std::forward<TypeX>(x) <= y;
		}
	};

	template <class TypeX>
	struct BinaryLessThanEqualY_impl
	{
		const TypeX& x;

		constexpr BinaryLessThanEqualY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x <= std::forward<TypeY>(y)))
		{
			return x <= std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	>
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryGreaterThanX_impl
	{
		const TypeY& y;

		constexpr BinaryGreaterThanX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) > y))
		{
			return std::forward<TypeX>(x) > y;
		}
	};

	template <class TypeX>
	struct BinaryGreaterThanY_impl
	{
		const TypeX& x;

		constexpr BinaryGreaterThanY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x > std::forward<TypeY>(y)))
		{
			return x > std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	>=
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryGreaterThanEqualX_impl
	{
		const TypeY& y;

		constexpr BinaryGreaterThanEqualX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) >= y))
		{
			return std::forward<TypeX>(x) >= y;
		}
	};

	template <class TypeX>
	struct BinaryGreaterThanEqualY_impl
	{
		const TypeX& x;

		constexpr BinaryGreaterThanEqualY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x >= std::forward<TypeY>(y)))
		{
			return x >= std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	+()
	//
	//////////////////////////////////////////////////
	struct UnaryPlus_impl
	{
		[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return detail::UnaryPlus_impl();
		}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(+(std::forward<TypeX>(x))))
		{
			return +(std::forward<TypeX>(x));
		}
	};

	//////////////////////////////////////////////////
	//
	//	-()
	//
	//////////////////////////////////////////////////
	struct Negate_impl
	{
		[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return detail::Negate_impl();
		}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(-(std::forward<TypeX>(x))))
		{
			return -(std::forward<TypeX>(x));
		}
	};

	//////////////////////////////////////////////////
	//
	//	+
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryPlusX_impl
	{
		const TypeY& y;

		constexpr BinaryPlusX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) + y))
		{
			return std::forward<TypeX>(x) + y;
		}
	};

	template <class TypeX>
	struct BinaryPlusY_impl
	{
		const TypeX& x;

		constexpr BinaryPlusY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x + std::forward<TypeY>(y)))
		{
			return x + std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	-
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryMinusX_impl
	{
		const TypeY& y;

		constexpr BinaryMinusX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) - y))
		{
			return std::forward<TypeX>(x) - y;
		}
	};

	template <class TypeX>
	struct BinaryMinusY_impl
	{
		const TypeX& x;

		constexpr BinaryMinusY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x - std::forward<TypeY>(y)))
		{
			return x - std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	*
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryMultipliesX_impl
	{
		const TypeY& y;

		constexpr BinaryMultipliesX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) * y))
		{
			return std::forward<TypeX>(x) * y;
		}
	};

	template <class TypeX>
	struct BinaryMultipliesY_impl
	{
		const TypeX& x;

		constexpr BinaryMultipliesY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x * std::forward<TypeY>(y)))
		{
			return x * std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	/
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryDividesX_impl
	{
		const TypeY& y;

		constexpr BinaryDividesX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) / y))
		{
			return std::forward<TypeX>(x) / y;
		}
	};

	template <class TypeX>
	struct BinaryDividesY_impl
	{
		const TypeX& x;

		constexpr BinaryDividesY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x / std::forward<TypeY>(y)))
		{
			return x / std::forward<TypeY>(y);
		}
	};

	//////////////////////////////////////////////////
	//
	//	%
	//
	//////////////////////////////////////////////////
	template <class TypeY>
	struct BinaryModulusX_impl
	{
		const TypeY& y;

		constexpr BinaryModulusX_impl(const TypeY& _y) noexcept
			: y(_y) {}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator()(TypeX&& x) const
		{
			if constexpr (Meta::HasModulus_v<TypeX, TypeY>)
			{
				return std::forward<TypeX>(x) % y;
			}
			else if constexpr (std::is_arithmetic_v<TypeX> && std::is_arithmetic_v<TypeY>)
			{
				return std::fmod(x, y);
			}
		}
	};

	template <class TypeX>
	struct BinaryModulusY_impl
	{
		const TypeX& x;

		constexpr BinaryModulusY_impl(const TypeX& _x) noexcept
			: x(_x) {}

		template <class TypeY>
		[[nodiscard]] constexpr auto operator()(TypeY&& y) const
		{
			if constexpr (Meta::HasModulus_v<TypeX, TypeY>)
			{
				return x % std::forward<TypeY>(y);
			}
			else if constexpr (std::is_arithmetic_v<TypeX> && std::is_arithmetic_v<TypeY>)
			{
				return std::fmod(x, y);
			}
		}
	};

	struct ModulusF_impl
	{
		template <class TypeX, class TypeY>
		constexpr auto operator() (TypeX&& x, TypeY&& y) const
		{
			if constexpr (Meta::HasModulus_v<TypeX, TypeY>)
			{
				return x % y;
			}
			else if constexpr (std::is_arithmetic_v<TypeX> && std::is_arithmetic_v<TypeY>)
			{
				return std::fmod(x, y);
			}
		}
	};

	//////////////////////////////////////////////////
	//
	//	!()
	//
	//////////////////////////////////////////////////
	struct UnaryNot_impl
	{
		[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return detail::UnaryNot_impl();
		}

		template <class TypeX>
		[[nodiscard]] constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(!(std::forward<TypeX>(x))))
		{
			return !(std::forward<TypeX>(x));
		}
	};

	//////////////////////////////////////////////////
	//
	//	Odd
	//
	//////////////////////////////////////////////////
	struct Odd_impl
	{
		template <class Type>
		constexpr bool operator()(const Type& x) const
		{
			return (x % 2) != 0;
		}

		constexpr Odd_impl operator()(PlaceHolder_t) const
		{
			return Odd_impl();
		}
	};

	//////////////////////////////////////////////////
	//
	//	Even
	//
	//////////////////////////////////////////////////
	struct Even_impl
	{
		template <class Type>
		constexpr bool operator()(const Type& x) const
		{
			return (x % 2) == 0;
		}

		constexpr Even_impl operator()(PlaceHolder_t) const
		{
			return Even_impl();
		}
	};

	//////////////////////////////////////////////////
	//
	//	Id
	//
	//////////////////////////////////////////////////
	struct Id_impl
	{
		template <class Type>
		constexpr decltype(auto) operator()(Type&& x) const noexcept
		{
			return std::forward<Type>(x);
		}

		constexpr Id_impl operator()(PlaceHolder_t) const noexcept
		{
			return Id_impl();
		}
	};

	//////////////////////////////////////////////////
	//
	//	FromEnum
	//
	//////////////////////////////////////////////////
	struct FromEnum_impl
	{
		template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>* = nullptr>
		[[nodiscard]] constexpr auto operator ()(Enum x) const noexcept
		{
			return static_cast<std::underlying_type_t<Enum>>(x);
		}

		[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return FromEnum_impl();
		}
	};

	//////////////////////////////////////////////////
	//
	//	ToEnum
	//
	//////////////////////////////////////////////////
	template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>* = nullptr>
	struct ToEnum_impl
	{
		[[nodiscard]] constexpr auto operator ()(std::underlying_type_t<Enum> x) const noexcept
		{
			return Enum{ x };
		}

		[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return ToEnum_impl();
		}
	};
}
