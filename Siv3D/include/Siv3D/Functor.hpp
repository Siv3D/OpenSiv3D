//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <functional>
# include <cmath>
# include "PlaceHolder.hpp"

namespace s3d
{
//////////////////////////////////////////////////
//
//	==
//
//////////////////////////////////////////////////

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

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator ==(PlaceHolder_t, TypeY&& y) noexcept
	{
		return Equal(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator ==(TypeX&& x, PlaceHolder_t) noexcept
	{
		return Equal(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator ==(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return Equal(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	!=
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto NotEqual() noexcept
	{
		return std::not_equal_to<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto NotEqual(const TypeX& x) noexcept
	{
		return detail::BinaryNotEqualY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto NotEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::not_equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::not_equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto NotEqual(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryNotEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto NotEqual(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryNotEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto NotEqual(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::not_equal_to<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator !=(PlaceHolder_t, TypeY&& y) noexcept
	{
		return NotEqual(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator !=(TypeX&& x, PlaceHolder_t) noexcept
	{
		return NotEqual(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator !=(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return NotEqual(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	<
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThan() noexcept
	{
		return std::less<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThan(const TypeX& x) noexcept
	{
		return LessThan(Lambda::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto LessThan(TypeX&& x, TypeY&& y) noexcept(noexcept(std::less<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::less<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto LessThan(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThan(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryLessThanY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThan(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::less<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator <(PlaceHolder_t, TypeY&& y) noexcept
	{
		return LessThan(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator <(TypeX&& x, PlaceHolder_t) noexcept
	{
		return LessThan(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator <(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return LessThan(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	<=
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThanEqual() noexcept
	{
		return std::less_equal<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThanEqual(const TypeX& x) noexcept
	{
		return LessThanEqual(Lambda::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto LessThanEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::less_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::less_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto LessThanEqual(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThanEqual(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryLessThanEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThanEqual(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::less_equal<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator <=(PlaceHolder_t, TypeY&& y) noexcept
	{
		return LessThanEqual(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator <=(TypeX&& x, PlaceHolder_t) noexcept
	{
		return LessThanEqual(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator <=(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return LessThanEqual(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	>
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThan() noexcept
	{
		return std::greater<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThan(const TypeX& x) noexcept
	{
		return GreaterThan(Lambda::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThan(TypeX&& x, TypeY&& y) noexcept(noexcept(std::greater<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::greater<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThan(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThan(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryGreaterThanY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThan(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::greater<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator >(PlaceHolder_t, TypeY&& y) noexcept
	{
		return GreaterThan(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator >(TypeX&& x, PlaceHolder_t) noexcept
	{
		return GreaterThan(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator >(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return GreaterThan(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	>=
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThanEqual() noexcept
	{
		return std::greater_equal<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(const TypeX& x) noexcept
	{
		return GreaterThanEqual(Lambda::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryGreaterThanEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::greater_equal<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator >=(PlaceHolder_t, TypeY&& y) noexcept
	{
		return GreaterThanEqual(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator >=(TypeX&& x, PlaceHolder_t) noexcept
	{
		return GreaterThanEqual(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator >=(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return GreaterThanEqual(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	+()
//
//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type = void>
		struct UnaryPlusX
		{
			[[nodiscard]] constexpr auto operator()(const Type& x) const noexcept(noexcept(+x))
			{
				return +x;
			}
		};

		template <>
		struct UnaryPlusX<void>
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(+(std::forward<TypeX>(x))))
			{
				return +(std::forward<TypeX>(x));
			}
		};

		struct UnaryPlus_impl
		{
			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::UnaryPlusX<Type>();
			}

			template <class TypeX>
			[[nodiscard]] constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(+(std::forward<TypeX>(x))))
			{
				return +(std::forward<TypeX>(x));
			}
		};
	}

	constexpr auto UnaryPlus = detail::UnaryPlus_impl();

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator +(PlaceHolder_t) noexcept
	{
		return detail::UnaryPlusX<Type>();
	}


//////////////////////////////////////////////////
//
//	-()
//
//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type = void>
		struct UnaryMinusX
		{
			[[nodiscard]] constexpr auto operator()(const Type& x) const noexcept(noexcept(-x))
			{
				return -x;
			}
		};

		template <>
		struct UnaryMinusX<void>
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(-(std::forward<TypeX>(x))))
			{
				return -(std::forward<TypeX>(x));
			}
		};

		struct Negate_impl
		{
			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::UnaryMinusX<Type>();
			}

			template <class TypeX>
			[[nodiscard]] constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(-(std::forward<TypeX>(x))))
			{
				return -(std::forward<TypeX>(x));
			}
		};
	}

	constexpr auto Negate = detail::Negate_impl();

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator -(PlaceHolder_t) noexcept
	{
		return detail::UnaryMinusX<Type>();
	}


//////////////////////////////////////////////////
//
//	+
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Plus() noexcept
	{
		return std::plus<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Plus(const TypeX& x) noexcept
	{
		return detail::BinaryPlusY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Plus(TypeX&& x, TypeY&& y) noexcept(noexcept(std::plus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::plus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Plus(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryPlusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Plus(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryPlusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Plus(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::plus<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator +(PlaceHolder_t, TypeY&& y) noexcept
	{
		return Plus(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator +(TypeX&& x, PlaceHolder_t) noexcept
	{
		return Plus(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator +(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return Plus(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	-
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Minus() noexcept
	{
		return std::minus<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Minus(const TypeX& x) noexcept
	{
		return detail::BinaryMinusY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Minus(TypeX&& x, TypeY&& y) noexcept(noexcept(std::minus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::minus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Minus(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryMinusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Minus(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryMinusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Minus(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::minus<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator -(PlaceHolder_t, TypeY&& y) noexcept
	{
		return Minus(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator -(TypeX&& x, PlaceHolder_t) noexcept
	{
		return Minus(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator -(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return Minus(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	*
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Multiplies() noexcept
	{
		return std::multiplies<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Multiplies(const TypeX& x) noexcept
	{
		return detail::BinaryMultipliesY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Multiplies(TypeX&& x, TypeY&& y) noexcept(noexcept(std::multiplies<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::multiplies<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Multiplies(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryMultipliesX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Multiplies(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryMultipliesY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Multiplies(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::multiplies<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator *(PlaceHolder_t, TypeY&& y) noexcept
	{
		return Multiplies(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator *(TypeX&& x, PlaceHolder_t) noexcept
	{
		return Multiplies(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator *(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return Multiplies(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	/
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Divides() noexcept
	{
		return std::divides<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Divides(const TypeX& x) noexcept
	{
		return detail::BinaryDividesY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Divides(TypeX&& x, TypeY&& y) noexcept(noexcept(std::divides<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::divides<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Divides(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryDividesX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Divides(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryDividesY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Divides(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::divides<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator /(PlaceHolder_t, TypeY&& y) noexcept
	{
		return Divides(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator /(TypeX&& x, PlaceHolder_t) noexcept
	{
		return Divides(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator /(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return Divides(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	%
//
//////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryModulusX_impl
		{
			const TypeY& y;

			constexpr BinaryModulusX_impl(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			[[nodiscard]] constexpr auto operator()(TypeX&& x) const
			{
				if constexpr (!std::is_floating_point_v<TypeX> && !std::is_floating_point_v<TypeY>)
				{
					return std::forward<TypeX>(x) % y;
				}
				else
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
				if constexpr (!std::is_floating_point_v<TypeX> && !std::is_floating_point_v<TypeY>)
				{
					return x % std::forward<TypeY>(y);
				}
				else
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
				if constexpr (!std::is_floating_point_v<TypeX> && !std::is_floating_point_v<TypeY>)
				{
					return x % y;
				}
				else
				{
					return std::fmod(x, y);
				}
			}
		};
	}

	[[nodiscard]] inline constexpr auto Modulus() noexcept
	{
		return detail::ModulusF_impl();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Modulus(const TypeX& x) noexcept
	{
		return detail::BinaryModulusY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Modulus(TypeX&& x, TypeY&& y) noexcept(noexcept(detail::ModulusF_impl()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return detail::ModulusF_impl()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Modulus(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryModulusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Modulus(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryModulusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Modulus(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::ModulusF_impl();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator %(PlaceHolder_t, TypeY&& y) noexcept
	{
		return Modulus(Lambda::_, std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator %(TypeX&& x, PlaceHolder_t) noexcept
	{
		return Modulus(std::forward<TypeX>(x), Lambda::_);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator %(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return Modulus(Lambda::_, Lambda::_);
	}


//////////////////////////////////////////////////
//
//	!()
//
//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type = void>
		struct UnaryNotX
		{
			[[nodiscard]] constexpr auto operator()(const Type& x) const noexcept(noexcept(!x))
			{
				return !x;
			}
		};

		template <>
		struct UnaryNotX<void>
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator()(TypeX&& x) const noexcept(noexcept(!(std::forward<TypeX>(x))))
			{
				return !(std::forward<TypeX>(x));
			}
		};

		struct UnaryNot_impl
		{
			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::UnaryNotX<Type>();
			}

			template <class TypeX>
			[[nodiscard]] constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(!(std::forward<TypeX>(x))))
			{
				return !(std::forward<TypeX>(x));
			}
		};
	}

	constexpr auto Not = detail::UnaryNot_impl();

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator !(PlaceHolder_t) noexcept
	{
		return detail::UnaryNotX<Type>();
	}


//////////////////////////////////////////////////
//
//	Odd
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	constexpr auto IsOdd = detail::Odd_impl();

//////////////////////////////////////////////////
//
//	Even
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	constexpr auto IsEven = detail::Even_impl();


//////////////////////////////////////////////////
//
//	Id
//
//////////////////////////////////////////////////

	namespace detail
	{
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
	}

	constexpr auto Id = detail::Id_impl();
}
