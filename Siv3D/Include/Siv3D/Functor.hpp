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
# include <cmath>
# include <functional>
# include "Optional.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		==
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryEqualX
		{
			const TypeY& y;

			constexpr BinaryEqualX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) == y))
			{
				return std::forward<TypeX>(x) == y;
			}
		};

		template <class TypeX>
		struct BinaryEqualY
		{
			const TypeX& x;

			constexpr BinaryEqualY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x == std::forward<TypeY>(y)))
			{
				return x == std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto Equal() noexcept
	{
		return std::equal_to<Type>();
	}

	template <class TypeX>
	inline constexpr auto Equal(TypeX&& x) noexcept
	{
		return detail::BinaryEqualY<TypeX>{x};
	}

	template <class Type = void, class TypeX, class TypeY>
	inline constexpr auto Equal(TypeX&& x, TypeY&& y) noexcept(noexcept(std::equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	inline constexpr auto Equal(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryEqualX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto Equal(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryEqualY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto Equal(None_t, None_t) noexcept
	{
		return std::equal_to<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		!=
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryNotEqualX
		{
			const TypeY& y;

			constexpr BinaryNotEqualX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) != y))
			{
				return std::forward<TypeX>(x) != y;
			}
		};

		template <class TypeX>
		struct BinaryNotEqualY
		{
			const TypeX& x;

			constexpr BinaryNotEqualY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x != std::forward<TypeY>(y)))
			{
				return x != std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto NotEqual() noexcept
	{
		return std::not_equal_to<Type>();
	}

	template <class TypeX>
	inline constexpr auto NotEqual(TypeX&& x) noexcept
	{
		return detail::BinaryNotEqualY<TypeX>{x};
	}

	template <class Type = void, class TypeX, class TypeY>
	inline constexpr auto NotEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::not_equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::not_equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	inline constexpr auto NotEqual(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryNotEqualX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto NotEqual(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryNotEqualY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto NotEqual(None_t, None_t) noexcept
	{
		return std::not_equal_to<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		<
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryLessThanX
		{
			const TypeY& y;

			constexpr BinaryLessThanX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) < y))
			{
				return std::forward<TypeX>(x) < y;
			}
		};

		template <class TypeX>
		struct BinaryLessThanY
		{
			const TypeX& x;

			constexpr BinaryLessThanY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x < std::forward<TypeY>(y)))
			{
				return x < std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto LessThan() noexcept
	{
		return std::less<Type>();
	}

	template <class TypeY>
	inline constexpr auto LessThan(TypeY&& y) noexcept
	{
		return detail::BinaryLessThanX<TypeY>{y};
	}

	template <class Type = void, class TypeX, class TypeY>
	inline constexpr auto LessThan(TypeX&& x, TypeY&& y) noexcept(noexcept(std::less<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::less<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	inline constexpr auto LessThan(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto LessThan(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryLessThanY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto LessThan(None_t, None_t) noexcept
	{
		return std::less<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		<=
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryLessThanEqualX
		{
			const TypeY& y;

			constexpr BinaryLessThanEqualX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) <= y))
			{
				return std::forward<TypeX>(x) <= y;
			}
		};

		template <class TypeX>
		struct BinaryLessThanEqualY
		{
			const TypeX& x;

			constexpr BinaryLessThanEqualY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x <= std::forward<TypeY>(y)))
			{
				return x <= std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto LessThanEqual() noexcept
	{
		return std::less_equal<Type>();
	}

	template <class TypeY>
	inline constexpr auto LessThanEqual(TypeY&& y) noexcept
	{
		return detail::BinaryLessThanEqualX<TypeY>{y};
	}

	template <class Type = void, class TypeX, class TypeY>
	inline constexpr auto LessThanEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::less_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::less_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	inline constexpr auto LessThanEqual(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanEqualX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto LessThanEqual(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryLessThanEqualY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto LessThanEqual(None_t, None_t) noexcept
	{
		return std::less_equal<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		>
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryGreaterThanX
		{
			const TypeY& y;

			constexpr BinaryGreaterThanX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) > y))
			{
				return std::forward<TypeX>(x) > y;
			}
		};

		template <class TypeX>
		struct BinaryGreaterThanY
		{
			const TypeX& x;

			constexpr BinaryGreaterThanY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x > std::forward<TypeY>(y)))
			{
				return x > std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto GreaterThan() noexcept
	{
		return std::greater<Type>();
	}

	template <class TypeY>
	inline constexpr auto GreaterThan(TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanX<TypeY>{y};
	}

	template <class Type = void, class TypeX, class TypeY>
	inline constexpr auto GreaterThan(TypeX&& x, TypeY&& y) noexcept(noexcept(std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	inline constexpr auto GreaterThan(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto GreaterThan(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryGreaterThanY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto GreaterThan(None_t, None_t) noexcept
	{
		return std::greater<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		>=
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryGreaterThanEqualX
		{
			const TypeY& y;

			constexpr BinaryGreaterThanEqualX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) >= y))
			{
				return std::forward<TypeX>(x) >= y;
			}
		};

		template <class TypeX>
		struct BinaryGreaterThanEqualY
		{
			const TypeX& x;

			constexpr BinaryGreaterThanEqualY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x >= std::forward<TypeY>(y)))
			{
				return x >= std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto GreaterThanEqual() noexcept
	{
		return std::greater_equal<Type>();
	}

	template <class TypeY>
	inline constexpr auto GreaterThanEqual(TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanEqualX<TypeY>{y};
	}

	template <class Type = void, class TypeX, class TypeY>
	inline constexpr auto GreaterThanEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	inline constexpr auto GreaterThanEqual(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanEqualX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto GreaterThanEqual(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryGreaterThanEqualY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto GreaterThanEqual(None_t, None_t) noexcept
	{
		return std::greater_equal<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		+
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryPlusX
		{
			const TypeY& y;

			constexpr BinaryPlusX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) + y))
			{
				return std::forward<TypeX>(x) + y;
			}
		};

		template <class TypeX>
		struct BinaryPlusY
		{
			const TypeX& x;

			constexpr BinaryPlusY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x + std::forward<TypeY>(y)))
			{
				return x + std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto Plus() noexcept
	{
		return std::plus<Type>();
	}

	template <class TypeY>
	inline constexpr auto Plus(TypeY&& y) noexcept
	{
		return detail::BinaryPlusX<TypeY>{y};
	}

	template <class TypeX, class TypeY>
	inline constexpr auto Plus(TypeX&& x, TypeY&& y) noexcept(noexcept(std::forward<TypeX>(x) + std::forward<TypeY>(y)))
	{
		return std::forward<TypeX>(x) + std::forward<TypeY>(y);
	}

	template <class TypeY>
	inline constexpr auto Plus(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryPlusX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto Plus(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryPlusY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto Plus(None_t, None_t) noexcept
	{
		return std::plus<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		-
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryMinusX
		{
			const TypeY& y;

			constexpr BinaryMinusX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) - y))
			{
				return std::forward<TypeX>(x) - y;
			}
		};

		template <class TypeX>
		struct BinaryMinusY
		{
			const TypeX& x;

			constexpr BinaryMinusY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x - std::forward<TypeY>(y)))
			{
				return x - std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto Minus() noexcept
	{
		return std::minus<Type>();
	}

	template <class TypeY>
	inline constexpr auto Minus(TypeY&& y) noexcept
	{
		return detail::BinaryMinusX<TypeY>{y};
	}

	template <class TypeX, class TypeY>
	inline constexpr auto Minus(TypeX&& x, TypeY&& y) noexcept(noexcept(std::forward<TypeX>(x) - std::forward<TypeY>(y)))
	{
		return std::forward<TypeX>(x) - std::forward<TypeY>(y);
	}

	template <class TypeY>
	inline constexpr auto Minus(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryMinusX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto Minus(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryMinusY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto Minus(None_t, None_t) noexcept
	{
		return std::minus<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		+()
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class Type = void>
		struct UnaryPlusX
		{
			constexpr auto operator()(const Type& x) const noexcept(noexcept(+x))
			{
				return +x;
			}
		};

		template <>
		struct UnaryPlusX<void>
		{
			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(+(std::forward<TypeX>(x))))
			{
				return +(std::forward<TypeX>(x));
			}
		};
	}

	template <class Type = void>
	inline constexpr auto UnaryPlus() noexcept
	{
		return detail::UnaryPlusX<Type>();
	}

	template <class Type = void>
	inline constexpr auto UnaryPlus(None_t) noexcept
	{
		return detail::UnaryPlusX<Type>();
	}

	template <class TypeX>
	inline constexpr auto UnaryPlus(TypeX&& x) noexcept(noexcept(+(std::forward<TypeX>(x))))
	{
		return +(std::forward<TypeX>(x));
	}

	////////////////////////////////////////////////////////////////
	//
	//		-()
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class Type = void>
		struct UnaryMinusX
		{
			constexpr auto operator()(const Type& x) const noexcept(noexcept(-x))
			{
				return -x;
			}
		};

		template <>
		struct UnaryMinusX<void>
		{
			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(-(std::forward<TypeX>(x))))
			{
				return -(std::forward<TypeX>(x));
			}
		};
	}

	template <class Type = void>
	inline constexpr auto Negate() noexcept
	{
		return detail::UnaryMinusX<Type>();
	}

	template <class Type = void>
	inline constexpr auto Negate(None_t) noexcept
	{
		return detail::UnaryMinusX<Type>();
	}

	template <class TypeX>
	inline constexpr auto Negate(TypeX&& x) noexcept(noexcept(-(std::forward<TypeX>(x))))
	{
		return -(std::forward<TypeX>(x));
	}

	////////////////////////////////////////////////////////////////
	//
	//		*
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryMultipliesX
		{
			const TypeY& y;

			constexpr BinaryMultipliesX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) * y))
			{
				return std::forward<TypeX>(x) * y;
			}
		};

		template <class TypeX>
		struct BinaryMultipliesY
		{
			const TypeX& x;

			constexpr BinaryMultipliesY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x * std::forward<TypeY>(y)))
			{
				return x * std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto Multiplies() noexcept
	{
		return std::multiplies<Type>();
	}

	template <class TypeY>
	inline constexpr auto Multiplies(TypeY&& y) noexcept
	{
		return detail::BinaryMultipliesX<TypeY>{y};
	}

	template <class TypeX, class TypeY>
	inline constexpr auto Multiplies(TypeX&& x, TypeY&& y) noexcept(noexcept(std::forward<TypeX>(x) * std::forward<TypeY>(y)))
	{
		return std::forward<TypeX>(x) * std::forward<TypeY>(y);
	}

	template <class TypeY>
	inline constexpr auto Multiplies(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryMultipliesX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto Multiplies(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryMultipliesY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto Multiplies(None_t, None_t) noexcept
	{
		return std::multiplies<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		/
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryDividesX
		{
			const TypeY& y;

			constexpr BinaryDividesX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) / y))
			{
				return std::forward<TypeX>(x) / y;
			}
		};

		template <class TypeX>
		struct BinaryDividesY
		{
			const TypeX& x;

			constexpr BinaryDividesY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x / std::forward<TypeY>(y)))
			{
				return x / std::forward<TypeY>(y);
			}
		};
	}

	template <class Type = void>
	inline constexpr auto Divides() noexcept
	{
		return std::divides<Type>();
	}

	template <class TypeY>
	inline constexpr auto Divides(TypeY&& y) noexcept
	{
		return detail::BinaryDividesX<TypeY>{y};
	}

	template <class TypeX, class TypeY>
	inline constexpr auto Divides(TypeX&& x, TypeY&& y) noexcept(noexcept(std::forward<TypeX>(x) / std::forward<TypeY>(y)))
	{
		return std::forward<TypeX>(x) / std::forward<TypeY>(y);
	}

	template <class TypeY>
	inline constexpr auto Divides(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryDividesX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto Divides(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryDividesY<TypeX>{x};
	}

	template <class Type = void>
	inline constexpr auto Divides(None_t, None_t) noexcept
	{
		return std::divides<Type>();
	}

	////////////////////////////////////////////////////////////////
	//
	//		%
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct BinaryModulusX
		{
			const TypeY& y;

			constexpr BinaryModulusX(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX, std::enable_if_t<!std::is_floating_point<TypeX>::value && !std::is_floating_point<TypeY>::value>* = nullptr>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) % y))
			{
				return std::forward<TypeX>(x) % y;
			}

			template <class TypeX, std::enable_if_t<std::is_floating_point<TypeX>::value || std::is_floating_point<TypeY>::value>* = nullptr>
			constexpr auto operator()(TypeX&& x) const
			{
				return std::fmod(x, y);
			}
		};

		template <class TypeX>
		struct BinaryModulusY
		{
			const TypeX& x;

			constexpr BinaryModulusY(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY, std::enable_if_t<!std::is_floating_point<TypeX>::value && !std::is_floating_point<TypeY>::value>* = nullptr>
			constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x % std::forward<TypeY>(y)))
			{
				return x % std::forward<TypeY>(y);
			}

			template <class TypeY, std::enable_if_t<std::is_floating_point<TypeX>::value || std::is_floating_point<TypeY>::value>* = nullptr>
			constexpr auto operator()(TypeY&& y) const
			{
				return std::fmod(x, y);
			}
		};
        
        struct ModulusF
        {
            template <class TypeX, class TypeY, std::enable_if_t<!std::is_floating_point<TypeX>::value && !std::is_floating_point<TypeY>::value>* = nullptr>
            constexpr auto operator() (TypeX&& x, TypeY&& y) const noexcept(noexcept(x % y))
            {
                return x % y;
            }
            
            template <class TypeX, class TypeY, std::enable_if_t<std::is_floating_point<TypeX>::value || std::is_floating_point<TypeY>::value>* = nullptr>
            auto operator() (TypeX&& x, TypeY&& y) const
            {
                return std::fmod(x, y);
            }
        };
	}

	inline constexpr auto Modulus() noexcept
	{
        return detail::ModulusF();
	}

	template <class TypeY>
	inline constexpr auto Modulus(TypeY&& y) noexcept
	{
		return detail::BinaryModulusX<TypeY>{y};
	}

    template <class TypeX, class TypeY>
    inline constexpr auto Modulus(TypeX&& x, TypeY&& y) noexcept(noexcept(detail::ModulusF()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
    {
        return detail::ModulusF()(std::forward<TypeX>(x), std::forward<TypeY>(y));
    }
    
	template <class TypeY>
	inline constexpr auto Modulus(None_t, TypeY&& y) noexcept
	{
		return detail::BinaryModulusX<TypeY>{y};
	}

	template <class TypeX>
	inline constexpr auto Modulus(TypeX&& x, None_t) noexcept
	{
		return detail::BinaryModulusY<TypeX>{x};
	}

	inline constexpr auto Modulus(None_t, None_t) noexcept
	{
		return detail::ModulusF();
	}

	////////////////////////////////////////////////////////////////
	//
	//		&&
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		||
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		!
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		struct UnaryNotX
		{
			template <class TypeX>
			constexpr auto operator()(TypeX&& x) const noexcept(noexcept(!(std::forward<TypeX>(x))))
			{
				return !(std::forward<TypeX>(x));
			}
		};
	}

	inline constexpr auto Not() noexcept
	{
		return std::plus<>();
	}

	template <class TypeX>
	inline constexpr auto Not(TypeX&& x) noexcept(noexcept(!(std::forward<TypeX>(x))))
	{
		return !(std::forward<TypeX>(x));
	}

	inline constexpr auto Not(None_t) noexcept
	{
		return detail::UnaryNotX();
	}

	////////////////////////////////////////////////////////////////
	//
	//		<<
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		>>
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		&
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		|
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		^
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		~
	//
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	//
	//		InRange
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		template <class MinType, class MaxType>
		struct InRange_impl
		{
			const MinType& m_min;

			const MaxType& m_max;

			constexpr InRange_impl(const MinType& min, const MaxType& max)
				: m_min(min)
				, m_max(max) {}

			template <class Type>
			constexpr bool operator() (Type&& value) const
			{
				return (m_min <= value) && (value <= m_max);
			}
		};
	}

	template <class MinType, class MaxType>
	inline constexpr auto InRange(MinType&& min, MaxType&& max)
	{
		return detail::InRange_impl<MinType, MaxType>(std::forward<MinType>(min), std::forward<MaxType>(max));
	}

	////////////////////////////////////////////////////////////////
	//
	//		Odd
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		struct Odd_impl
		{
			template <class Type>
			constexpr bool operator()(const Type& x) const
			{
				return (x % 2) != 0;
			}

			constexpr Odd_impl operator()(None_t) const
			{
				return Odd_impl();
			}
		};
	}

	constexpr auto IsOdd = detail::Odd_impl();

	////////////////////////////////////////////////////////////////
	//
	//		Even
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		struct Even_impl
		{
			template <class Type>
			constexpr bool operator()(const Type& x) const
			{
				return (x % 2) == 0;
			}

			constexpr Even_impl operator()(None_t) const
			{
				return Even_impl();
			}
		};
	}

	constexpr auto IsEven = detail::Even_impl();

	////////////////////////////////////////////////////////////////
	//
	//		Id
	//
	////////////////////////////////////////////////////////////////

	namespace detail
	{
		struct Id_impl
		{
			template <class Type>
			constexpr decltype(auto) operator()(Type&& x) const
			{
				return std::forward<Type>(x);
			}
			constexpr Id_impl operator()(None_t) const
			{
				return Id_impl();
			}
		};
	}

	constexpr auto Id = detail::Id_impl();
}
