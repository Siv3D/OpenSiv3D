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
	//	==
	//
	//////////////////////////////////////////////////

	template <class TypeY>
	struct BinaryEqualX_impl
	{
		const TypeY& y;

		constexpr BinaryEqualX_impl(const TypeY& _y) noexcept
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) == y))
		{
			return (std::forward<TypeX>(x) == y);
		}
	};

	template <class TypeX>
	struct BinaryEqualY_impl
	{
		const TypeX& x;

		constexpr BinaryEqualY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x == std::forward<TypeY>(y)))
		{
			return (x == std::forward<TypeY>(y));
		}
	};

	struct BinaryEqual_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(const Type& x) const noexcept(noexcept(x == x))
		{
			return (x == x);
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) != y))
		{
			return (std::forward<TypeX>(x) != y);
		}
	};

	template <class TypeX>
	struct BinaryNotEqualY_impl
	{
		const TypeX& x;

		constexpr BinaryNotEqualY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x != std::forward<TypeY>(y)))
		{
			return (x != std::forward<TypeY>(y));
		}
	};

	struct BinaryNotEqual_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(const Type& x) const noexcept(noexcept(x != x))
		{
			return (x != x);
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) < y))
		{
			return (std::forward<TypeX>(x) < y);
		}
	};

	template <class TypeX>
	struct BinaryLessThanY_impl
	{
		const TypeX& x;

		constexpr BinaryLessThanY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x < std::forward<TypeY>(y)))
		{
			return (x < std::forward<TypeY>(y));
		}
	};

	struct BinaryLessThan_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(const Type& x) const noexcept(noexcept(x < x))
		{
			return (x < x);
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) <= y))
		{
			return (std::forward<TypeX>(x) <= y);
		}
	};

	template <class TypeX>
	struct BinaryLessThanEqualY_impl
	{
		const TypeX& x;

		constexpr BinaryLessThanEqualY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x <= std::forward<TypeY>(y)))
		{
			return (x <= std::forward<TypeY>(y));
		}
	};

	struct BinaryLessThanEqual_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(const Type& x) const noexcept(noexcept(x <= x))
		{
			return (x <= x);
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) > y))
		{
			return (std::forward<TypeX>(x) > y);
		}
	};

	template <class TypeX>
	struct BinaryGreaterThanY_impl
	{
		const TypeX& x;

		constexpr BinaryGreaterThanY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x > std::forward<TypeY>(y)))
		{
			return (x > std::forward<TypeY>(y));
		}
	};

	struct BinaryGreaterThan_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(const Type& x) const noexcept(noexcept(x > x))
		{
			return (x > x);
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) >= y))
		{
			return (std::forward<TypeX>(x) >= y);
		}
	};

	template <class TypeX>
	struct BinaryGreaterThanEqualY_impl
	{
		const TypeX& x;

		constexpr BinaryGreaterThanEqualY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x >= std::forward<TypeY>(y)))
		{
			return (x >= std::forward<TypeY>(y));
		}
	};

	struct BinaryGreaterThanEqual_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(const Type& x) const noexcept(noexcept(x >= x))
		{
			return (x >= x);
		}
	};

	//////////////////////////////////////////////////
	//
	//	+()
	//
	//////////////////////////////////////////////////

	struct UnaryPlus_impl
	{
		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(+(std::forward<TypeX>(x))))
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
		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(-(std::forward<TypeX>(x))))
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) + y))
		{
			return (std::forward<TypeX>(x) + y);
		}
	};

	template <class TypeX>
	struct BinaryPlusY_impl
	{
		const TypeX& x;

		constexpr BinaryPlusY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x + std::forward<TypeY>(y)))
		{
			return (x + std::forward<TypeY>(y));
		}
	};

	struct BinaryPlus_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(Type&& x) const noexcept(noexcept(std::forward<Type>(x) + std::forward<Type>(x)))
		{
			return (std::forward<Type>(x) + std::forward<Type>(x));
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) - y))
		{
			return (std::forward<TypeX>(x) - y);
		}
	};

	template <class TypeX>
	struct BinaryMinusY_impl
	{
		const TypeX& x;

		constexpr BinaryMinusY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x - std::forward<TypeY>(y)))
		{
			return (x - std::forward<TypeY>(y));
		}
	};

	struct BinaryMinus_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(Type&& x) const noexcept(noexcept(std::forward<Type>(x) - std::forward<Type>(x)))
		{
			return (std::forward<Type>(x) - std::forward<Type>(x));
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x)* y))
		{
			return (std::forward<TypeX>(x) * y);
		}
	};

	template <class TypeX>
	struct BinaryMultipliesY_impl
	{
		const TypeX& x;

		constexpr BinaryMultipliesY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x* std::forward<TypeY>(y)))
		{
			return (x * std::forward<TypeY>(y));
		}
	};

	struct BinaryMultiplies_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(Type&& x) const noexcept(noexcept(std::forward<Type>(x) * std::forward<Type>(x)))
		{
			return (std::forward<Type>(x) * std::forward<Type>(x));
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const noexcept(noexcept(std::forward<TypeX>(x) / y))
		{
			return (std::forward<TypeX>(x) / y);
		}
	};

	template <class TypeX>
	struct BinaryDividesY_impl
	{
		const TypeX& x;

		constexpr BinaryDividesY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const noexcept(noexcept(x / std::forward<TypeY>(y)))
		{
			return (x / std::forward<TypeY>(y));
		}
	};

	struct BinaryDivides_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(Type&& x) const noexcept(noexcept(std::forward<Type>(x) / std::forward<Type>(x)))
		{
			return (std::forward<Type>(x) / std::forward<Type>(x));
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
			: y{ _y } {}

		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator()(TypeX&& x) const
		{
			if constexpr (std::disjunction_v<std::is_floating_point<TypeX>, std::is_floating_point<TypeY>>)
			{
				return std::fmod(x, y);
			}
			else
			{
				return (std::forward<TypeX>(x) % y);
			}
		}
	};

	template <class TypeX>
	struct BinaryModulusY_impl
	{
		const TypeX& x;

		constexpr BinaryModulusY_impl(const TypeX& _x) noexcept
			: x{ _x } {}

		template <class TypeY>
		[[nodiscard]]
		constexpr auto operator()(TypeY&& y) const
		{
			if constexpr (std::disjunction_v<std::is_floating_point<TypeX>, std::is_floating_point<TypeY>>)
			{
				return std::fmod(x, y);
			}
			else
			{
				return (x % std::forward<TypeY>(y));
			}
		}
	};

	struct ModulusF_impl
	{
		template <class TypeX, class TypeY>
		[[nodiscard]]
		constexpr auto operator() (TypeX&& x, TypeY&& y) const
		{
			if constexpr (std::disjunction_v<std::is_floating_point<TypeX>, std::is_floating_point<TypeY>>)
			{
				return std::fmod(x, y);
			}
			else
			{
				return (x % y);
			}
		}
	};

	struct BinaryModulus_impl
	{
		template <class Type>
		[[nodiscard]]
		constexpr auto operator()(Type&& x) const
		{
			if constexpr (std::is_floating_point_v<Type>)
			{
				return std::fmod(x, x);
			}
			else
			{
				return (x % x);
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
		template <class TypeX>
		[[nodiscard]]
		constexpr auto operator ()(TypeX&& x) const noexcept(noexcept(!(std::forward<TypeX>(x))))
		{
			return !(std::forward<TypeX>(x));
		}
	};

	//////////////////////////////////////////////////
	//
	//	Max
	//
	//////////////////////////////////////////////////

	template <class Type>
	struct Max1_impl
	{
		const Type& a;

		constexpr Max1_impl(const Type& _a) noexcept
			: a{ _a } {}

		[[nodiscard]]
		constexpr const Type& operator()(const Type& b) const noexcept(noexcept(a < b))
		{
			return ((a < b) ? b : a);
		}
	};

	struct Max2_impl
	{
		SIV3D_CONCEPT_SCALAR
		[[nodiscard]]
		constexpr Scalar operator()(Scalar a, Scalar b) const noexcept
		{
			return ((a < b) ? b : a);
		}

	# if __cpp_lib_concepts
		template <class Type>
	# else
		template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
	# endif
		[[nodiscard]]
		constexpr const Type& operator()(const Type& a, const Type& b) const noexcept(noexcept(a < b))
		{
			return ((a < b) ? b : a);
		}
	};

	//////////////////////////////////////////////////
	//
	//	Min
	//
	//////////////////////////////////////////////////

	template <class Type>
	struct Min1_impl
	{
		const Type& a;

		constexpr Min1_impl(const Type& _a) noexcept
			: a{ _a } {}

		[[nodiscard]]
		constexpr const Type& operator()(const Type& b) const noexcept(noexcept(b < a))
		{
			return ((b < a) ? b : a);
		}
	};

	struct Min2_impl
	{
		SIV3D_CONCEPT_SCALAR
		[[nodiscard]]
		constexpr Scalar operator()(Scalar a, Scalar b) const noexcept
		{
			return ((b < a) ? b : a);
		}

	# if __cpp_lib_concepts
		template <class Type>
	# else
		template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
	# endif
		[[nodiscard]]
		constexpr const Type& operator()(const Type& a, const Type& b) const noexcept(noexcept(b < a))
		{
			return ((b < a) ? b : a);
		}
	};

	//////////////////////////////////////////////////
	//
	//	Clamp
	//
	//////////////////////////////////////////////////

	template <class Type>
	class Clamp_impl
	{
	private:

		const Type& min;

		const Type& max;

	public:

		constexpr Clamp_impl(const Type& _min, const Type& _max) noexcept
			: min{ _min }
			, max{ _max } {}

		[[nodiscard]]
		constexpr const Type& operator()(const Type& v) const noexcept(noexcept(max < v) && noexcept(v < min))
		{
			if (max < v)
			{
				return max;
			}

			if (v < min)
			{
				return min;
			}

			return v;
		}
	};

	//////////////////////////////////////////////////
	//
	//	InRange
	//
	//////////////////////////////////////////////////

	template <class Type>
	class InRange_impl
	{
	private:

		const Type& min;

		const Type& max;

	public:

		constexpr InRange_impl(const Type& _min, const Type& _max) noexcept
			: min{ _min }
			, max{ _max } {}

		[[nodiscard]]
		constexpr bool operator()(const Type& v) const noexcept(noexcept(min <= v))
		{
			return ((min <= v) && (v <= max));
		}
	};

	//////////////////////////////////////////////////
	//
	//	InOpenRange
	//
	//////////////////////////////////////////////////

	template <class Type>
	class InOpenRange_impl
	{
	private:

		const Type& min;

		const Type& max;

	public:

		constexpr InOpenRange_impl(const Type& _min, const Type& _max) noexcept
			: min{ _min }
			, max{ _max } {}

		[[nodiscard]]
		constexpr bool operator()(const Type& v) const noexcept(noexcept(min < v))
		{
			return (min < v) && (v < max);
		}
	};

	//////////////////////////////////////////////////
	//
	//	AbsDiff
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_ARITHMETIC
	struct AbsDiff1_impl
	{
		const Arithmetic a;

		constexpr AbsDiff1_impl(Arithmetic _a) noexcept
			: a(_a) {}

		[[nodiscard]]
		constexpr auto operator()(Arithmetic b) const noexcept
		{
			return AbsDiff(a, b);
		}
	};

	struct AbsDiff2_impl
	{
		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		constexpr auto operator()(Arithmetic a, Arithmetic b) const noexcept
		{
			return AbsDiff(a, b);
		}
	};
}
