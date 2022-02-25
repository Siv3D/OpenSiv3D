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
	//	Max
	//
	//////////////////////////////////////////////////

	template <class Type>
	struct Max1_impl
	{
		const Type& a;

		constexpr Max1_impl(const Type& _a) noexcept
			: a(_a) {}

		[[nodiscard]]
		constexpr const Type& operator()(const Type& b) const noexcept(noexcept(a < b))
		{
			return (a < b) ? b : a;
		}
	};

	struct Max2_impl
	{
		SIV3D_CONCEPT_SCALAR
		[[nodiscard]]
		constexpr Scalar operator()(Scalar a, Scalar b) const noexcept
		{
			return (a < b) ? b : a;
		}

	# if __cpp_lib_concepts
		template <class Type>
	# else
		template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
	# endif
		[[nodiscard]]
		constexpr const Type& operator()(const Type& a, const Type& b) const noexcept(noexcept(a < b))
		{
			return (a < b) ? b : a;
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
			: a(_a) {}

		[[nodiscard]]
		constexpr const Type& operator()(const Type& b) const noexcept(noexcept(b < a))
		{
			return (b < a) ? b : a;
		}
	};

	struct Min2_impl
	{
		SIV3D_CONCEPT_SCALAR
		[[nodiscard]]
		constexpr Scalar operator()(Scalar a, Scalar b) const noexcept
		{
			return (b < a) ? b : a;
		}

	# if __cpp_lib_concepts
		template <class Type>
	# else
		template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>* = nullptr>
	# endif
		[[nodiscard]]
		constexpr const Type& operator()(const Type& a, const Type& b) const noexcept(noexcept(b < a))
		{
			return (b < a) ? b : a;
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
			: min(_min)
			, max(_max) {}

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
			: min(_min)
			, max(_max) {}

		[[nodiscard]]
		constexpr bool operator()(const Type& v) const noexcept(noexcept(min <= v))
		{
			return (min <= v) && (v <= max);
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
			: min(_min)
			, max(_max) {}

		[[nodiscard]]
		constexpr bool operator()(const Type& v) const noexcept(noexcept(min < v))
		{
			return (min < v) && (v < max);
		}
	};

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

		[[nodiscard]]
		constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return Abs_impl{};
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
			if constexpr (std::is_integral_v<Arithmetic>)
			{
				using U = std::make_unsigned_t<Arithmetic>;
				return (a > b) ? (static_cast<U>(a) - static_cast<U>(b))
					: (static_cast<U>(b) - static_cast<U>(a));
			}
			else
			{
				return Abs_impl{}(a - b);
			}
		}
	};

	struct AbsDiff2_impl
	{
		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		constexpr auto operator()(Arithmetic a, Arithmetic b) const noexcept
		{
			if constexpr (std::is_integral_v<Arithmetic>)
			{
				using U = std::make_unsigned_t<Arithmetic>;
				return (a > b) ? (static_cast<U>(a) - static_cast<U>(b))
					: (static_cast<U>(b) - static_cast<U>(a));
			}
			else
			{
				return Abs_impl{}(a - b);
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

		[[nodiscard]]
		constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return FromEnum_impl{};
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

		[[nodiscard]]
		constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return ToEnum_impl{};
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

		[[nodiscard]]
		constexpr IsOdd_impl operator()(PlaceHolder_t) const
		{
			return IsOdd_impl{};
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

		[[nodiscard]]
		constexpr IsEven_impl operator()(PlaceHolder_t) const
		{
			return IsEven_impl{};
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

		[[nodiscard]]
		constexpr Identity_impl operator()(PlaceHolder_t) const noexcept
		{
			return Identity_impl{};
		}
	};
}
