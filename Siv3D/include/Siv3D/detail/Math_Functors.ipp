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

namespace s3d
{
	//////////////////////////////////////////////////
	//
	//	Fmod
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct FmodX_impl
		{
			const TypeY& y;

			constexpr FmodX_impl(const TypeY& _y) noexcept
				: y{ _y } {}

			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator()(const TypeX& x) const
			{
				return Math::Fmod(x, y);
			}
		};

		template <class TypeX>
		struct FmodY_impl
		{
			const TypeX& x;

			constexpr FmodY_impl(const TypeX& _x) noexcept
				: x{ _x } {}

			template <class TypeY>
			[[nodiscard]]
			constexpr auto operator()(const TypeY& y) const
			{
				return Math::Fmod(x, y);
			}
		};

		struct Fmod_impl
		{
			template <class TypeX, class TypeY>
			[[nodiscard]]
			constexpr auto operator() (const TypeX& x, const TypeY& y) const
			{
				return Math::Fmod(x, y);
			}
		};
	}

	[[nodiscard]]
	inline constexpr auto Fmod() noexcept
	{
		return detail::Fmod_impl{};
	}

	template <class TypeX>
	[[nodiscard]]
	inline constexpr auto Fmod(const TypeX& x) noexcept
	{
		return detail::FmodY_impl<TypeX>{ x };
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]]
	inline constexpr auto Fmod(const TypeX& x, const TypeY& y) noexcept
	{
		return detail::Fmod_impl{}(x, y);
	}

	template <class TypeY>
	[[nodiscard]]
	inline constexpr auto Fmod(PlaceHolder_t, const TypeY& y) noexcept
	{
		return detail::FmodX_impl<TypeY>{ y };
	}

	template <class TypeX>
	[[nodiscard]]
	inline constexpr auto Fmod(const TypeX& x, PlaceHolder_t) noexcept
	{
		return detail::FmodY_impl<TypeX>{ x };
	}

	template <class Type = void>
	[[nodiscard]]
	inline constexpr auto Fmod(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Fmod_impl{};
	}

	//////////////////////////////////////////////////
	//
	//	Fraction
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Fraction_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Fraction(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Fraction = detail::Fraction_impl{};

	//////////////////////////////////////////////////
	//
	//	Log
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Log_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Log(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Log = detail::Log_impl{};

	//////////////////////////////////////////////////
	//
	//	Log2
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Log2_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Log2(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Log2 = detail::Log2_impl{};

	//////////////////////////////////////////////////
	//
	//	Log10
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Log10_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Log10(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Log10 = detail::Log10_impl{};

	//////////////////////////////////////////////////
	//
	//	Pow
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class TypeY>
		struct PowX_impl
		{
			const TypeY& y;

			constexpr PowX_impl(const TypeY& _y) noexcept
				: y{ _y } {}

			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator()(const TypeX& x) const
			{
				return Math::Pow(x, y);
			}
		};

		template <class TypeX>
		struct PowY_impl
		{
			const TypeX& x;

			constexpr PowY_impl(const TypeX& _x) noexcept
				: x{ _x } {}

			template <class TypeY>
			[[nodiscard]]
			constexpr auto operator()(const TypeY& y) const
			{
				return Math::Pow(x, y);
			}
		};

		struct Pow_impl
		{
			template <class TypeX, class TypeY>
			[[nodiscard]]
			constexpr auto operator() (const TypeX& x, const TypeY& y) const
			{
				return Math::Pow(x, y);
			}
		};
	}

	[[nodiscard]]
	inline constexpr auto Pow() noexcept
	{
		return detail::Pow_impl{};
	}

	template <class TypeX>
	[[nodiscard]]
	inline constexpr auto Pow(const TypeX& x) noexcept
	{
		return detail::PowY_impl<TypeX>{ x };
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]]
	inline constexpr auto Pow(const TypeX& x, const TypeY& y) noexcept
	{
		return detail::Pow_impl{}(x, y);
	}

	template <class TypeY>
	[[nodiscard]]
	inline constexpr auto Pow(PlaceHolder_t, const TypeY& y) noexcept
	{
		return detail::PowX_impl<TypeY>{ y };
	}

	template <class TypeX>
	[[nodiscard]]
	inline constexpr auto Pow(const TypeX& x, PlaceHolder_t) noexcept
	{
		return detail::PowY_impl<TypeX>{ x };
	}

	template <class Type = void>
	[[nodiscard]]
	inline constexpr auto Pow(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Pow_impl{};
	}

	//////////////////////////////////////////////////
	//
	//	Sign
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Sign_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Sign(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Sign = detail::Sign_impl{};

	//////////////////////////////////////////////////
	//
	//	ToRadians
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct ToRadians_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::ToRadians(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto ToRadians = detail::ToRadians_impl{};

	//////////////////////////////////////////////////
	//
	//	ToDegrees
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct ToDegrees_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::ToDegrees(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto ToDegrees = detail::ToDegrees_impl{};

	//////////////////////////////////////////////////
	//
	//	Square
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Square_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Square(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Square = detail::Square_impl{};

	//////////////////////////////////////////////////
	//
	//	Exp
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Exp_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Exp(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Exp = detail::Exp_impl{};

	//////////////////////////////////////////////////
	//
	//	Exp2
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Exp2_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Exp2(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Exp2 = detail::Exp2_impl{};

	//////////////////////////////////////////////////
	//
	//	Rsqrt
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Rsqrt_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Rsqrt(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Rsqrt = detail::Rsqrt_impl{};

	//////////////////////////////////////////////////
	//
	//	Sqrt
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Sqrt_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Sqrt(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Sqrt = detail::Sqrt_impl{};

	//////////////////////////////////////////////////
	//
	//	Ceil
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Ceil_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Ceil(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Ceil = detail::Ceil_impl{};

	//////////////////////////////////////////////////
	//
	//	Floor
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Floor_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Floor(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Floor = detail::Floor_impl{};

	//////////////////////////////////////////////////
	//
	//	Round
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Round_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Round(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Round = detail::Round_impl{};

	//////////////////////////////////////////////////
	//
	//	Saturate
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Saturate_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Saturate(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Saturate = detail::Saturate_impl{};

	//////////////////////////////////////////////////
	//
	//	Acos
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Acos_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Acos(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Acos = detail::Acos_impl{};

	//////////////////////////////////////////////////
	//
	//	Asin
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Asin_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Asin(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Asin = detail::Asin_impl{};

	//////////////////////////////////////////////////
	//
	//	Atan
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Atan_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Atan(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Atan = detail::Atan_impl{};

	//////////////////////////////////////////////////
	//
	//	Atan2
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		struct Atan2X_impl
		{
			const Type& y;

			constexpr Atan2X_impl(const Type& _y) noexcept
				: y{ _y } {}

			[[nodiscard]] constexpr auto operator()(const Type& x) const
			{
				return Math::Atan2(x, y);
			}
		};

		template <class Type>
		struct Atan2Y_impl
		{
			const Type& x;

			constexpr Atan2Y_impl(const Type& _x) noexcept
				: x{ _x } {}

			[[nodiscard]]
			constexpr auto operator()(const Type& y) const
			{
				return Math::Atan2(x, y);
			}
		};

		struct Atan2_impl
		{
			template <class Type>
			[[nodiscard]]
			constexpr auto operator() (const Type& x, const Type& y) const
			{
				return Math::Atan2(x, y);
			}
		};
	}

	[[nodiscard]]
	inline constexpr auto Atan2() noexcept
	{
		return detail::Atan2_impl{};
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Atan2(const Type& x) noexcept
	{
		return detail::Atan2Y_impl<Type>{ x };
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Atan2(const Type& x, const Type& y) noexcept
	{
		return detail::Atan2_impl{}(x, y);
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Atan2(PlaceHolder_t, const Type& y) noexcept
	{
		return detail::Atan2X_impl<Type>{ y };
	}

	template <class Type>
	[[nodiscard]]
	inline constexpr auto Atan2(const Type& x, PlaceHolder_t) noexcept
	{
		return detail::Atan2Y_impl<Type>{ x };
	}

	[[nodiscard]]
	inline constexpr auto Atan2(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Atan2_impl{};
	}

	//////////////////////////////////////////////////
	//
	//	Cos
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Cos_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Cos(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Cos = detail::Cos_impl{};

	//////////////////////////////////////////////////
	//
	//	Cosh
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Cosh_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Cosh(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Cosh = detail::Cosh_impl{};

	//////////////////////////////////////////////////
	//
	//	Sin
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Sin_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Sin(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Sin = detail::Sin_impl{};

	//////////////////////////////////////////////////
	//
	//	Sinh
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Sinh_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Sinh(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Sinh = detail::Sinh_impl{};

	//////////////////////////////////////////////////
	//
	//	Tan
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Tan_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Tan(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Tan = detail::Tan_impl{};

	//////////////////////////////////////////////////
	//
	//	Tanh
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Tanh_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Tanh(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Tanh = detail::Tanh_impl{};

	//////////////////////////////////////////////////
	//
	//	Dot
	//
	//////////////////////////////////////////////////

	struct Dot_impl
	{
		template <class V1, class V2>
		[[nodiscard]]
		constexpr auto operator()(const V1 v1, const V2 v2) const noexcept
		{
			return Math::Dot(v1, v2);
		}

		template <class Type = void>
		[[nodiscard]]
		constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return *this;
		}
	};

	constexpr auto Dot = Dot_impl{};

	//////////////////////////////////////////////////
	//
	//	Cross
	//
	//////////////////////////////////////////////////

	struct Cross_impl
	{
		template <class V1, class V2>
		[[nodiscard]]
		constexpr auto operator()(const V1 v1, const V2 v2) const noexcept
		{
			return Math::Cross(v1, v2);
		}

		template <class Type = void>
		[[nodiscard]]
		constexpr auto operator ()(PlaceHolder_t) const noexcept
		{
			return *this;
		}
	};

	constexpr auto Cross = Cross_impl{};

	//////////////////////////////////////////////////
	//
	//	Normalize
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Normalize_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Normalize(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Normalize = detail::Normalize_impl{};

	//////////////////////////////////////////////////
	//
	//	Smoothstep
	//
	//////////////////////////////////////////////////

	namespace detail
	{
		struct Smoothstep_impl
		{
			template <class TypeX>
			[[nodiscard]]
			constexpr auto operator() (const TypeX x) const noexcept
			{
				return Math::Smoothstep(x);
			}

			template <class Type = void>
			[[nodiscard]]
			constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return *this;
			}
		};
	}

	constexpr auto Smoothstep = detail::Smoothstep_impl{};
}
