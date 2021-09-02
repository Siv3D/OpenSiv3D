////////////////////////////////////////////////////////////////
//
//	EnumBitmask
//	https://github.com/Reputeless/EnumBitmask
//	License: CC0 1.0 Universal
//
# pragma once
# include <type_traits>

namespace EnumBitmask
{
	template <class Enum>
	struct EnumWrapper
	{
		Enum e;

		constexpr explicit operator bool() const noexcept
		{
			return (e != Enum{ 0 });
		}

		constexpr operator Enum() const noexcept
		{
			return e;
		}
	};

	template <class Enum>
	EnumWrapper(Enum e)->EnumWrapper<Enum>;
}

# define DEFINE_BITMASK_OPERATORS(ENUM)									\
	static_assert(std::is_enum_v<ENUM>, "ENUM must be an enum type");	\
	[[nodiscard]]														\
	inline constexpr auto operator &(ENUM lhs, ENUM rhs) noexcept		\
	{																	\
		using U = std::underlying_type_t<ENUM>;							\
		return EnumBitmask::EnumWrapper{								\
			ENUM(static_cast<U>(lhs) & static_cast<U>(rhs))};			\
	}																	\
	[[nodiscard]]														\
	inline constexpr auto operator |(ENUM lhs, ENUM rhs) noexcept		\
	{																	\
		using U = std::underlying_type_t<ENUM>;							\
		return EnumBitmask::EnumWrapper{								\
			ENUM(static_cast<U>(lhs) | static_cast<U>(rhs))};			\
	}																	\
	[[nodiscard]]														\
	inline constexpr auto operator ^(ENUM lhs, ENUM rhs) noexcept		\
	{																	\
		using U = std::underlying_type_t<ENUM>;							\
		return EnumBitmask::EnumWrapper{								\
			ENUM(static_cast<U>(lhs) ^ static_cast<U>(rhs)) };			\
	}																	\
	[[nodiscard]]														\
	inline constexpr ENUM operator ~(ENUM value) noexcept				\
	{																	\
		using U = std::underlying_type_t<ENUM>;							\
		return ENUM(~static_cast<U>(value));							\
	}																	\
	inline constexpr ENUM& operator &=(ENUM& lhs, ENUM rhs) noexcept	\
	{																	\
		return lhs = (lhs & rhs);										\
	}																	\
	inline constexpr ENUM& operator |=(ENUM& lhs, ENUM rhs) noexcept	\
	{																	\
		return lhs = (lhs | rhs);										\
	}																	\
	inline constexpr ENUM& operator ^=(ENUM& lhs, ENUM rhs) noexcept	\
	{																	\
		return lhs = (lhs ^ rhs);										\
	}
//
////////////////////////////////////////////////////////////////
