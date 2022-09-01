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
# include <cassert>
# if  __has_include(<compare>)
#	include <compare>
# endif
# include <memory>
# include <optional>
# include "Common.hpp"
# include "Utility.hpp"
# include "Error.hpp"
# include "None.hpp"
# include "Format.hpp"
# include "FormatData.hpp"
# include "FormatLiteral.hpp"

namespace s3d
{
	/// @brief Optional
	/// @tparam Type Optional が持つ値の型
	template <class Type>
	class Optional : protected std::optional<Type>
	{
	public:

		using base_type = std::optional<Type>;

		/// @brief Optional が持つ値の型
		using value_type = Type;

		using base_type::optional;
		
		using base_type::operator->;
		using base_type::operator*;
		using base_type::operator bool;
		using base_type::has_value;
		using base_type::value;
		using base_type::value_or;
		using base_type::reset;
		using base_type::emplace;

		SIV3D_NODISCARD_CXX20
		Optional() = default;
		
		SIV3D_NODISCARD_CXX20
		constexpr Optional(None_t);

		SIV3D_NODISCARD_CXX20
		Optional(const Optional& other) = default;

		Optional& operator =(None_t) noexcept;
		
		constexpr Optional& operator =(const Optional& other);
		
		constexpr Optional& operator =(Optional&& other) noexcept(std::is_nothrow_move_assignable_v<Type> && std::is_nothrow_move_constructible_v<Type>);

		template <class U = Type>
		Optional& operator =(U&& value);

		template <class U>
		Optional& operator =(const Optional<U>& other);

		template <class U>
		Optional& operator =(Optional<U>&& other);

		void swap(Optional& other) noexcept(std::is_nothrow_move_constructible_v<Type>&& std::is_nothrow_swappable_v<Type>);

		template <class... Args, std::enable_if_t<std::conjunction_v<std::is_copy_constructible<Type>, std::is_constructible<Type, Args...>>>* = nullptr>
		[[nodiscard]]
		constexpr value_type value_or_construct(Args&&... args) const&;

		template <class... Args, std::enable_if_t<std::conjunction_v<std::is_move_constructible<Type>, std::is_constructible<Type, Args...>>>* = nullptr>
		[[nodiscard]]
		constexpr value_type value_or_construct(Args&&... args)&&;

		template <class Fty, std::enable_if_t<std::conjunction_v<std::is_copy_constructible<Type>, std::is_convertible<std::invoke_result_t<Fty>, Type>>>* = nullptr>
		[[nodiscard]]
		constexpr value_type value_or_eval(Fty&& f) const&;

		template <class Fty, std::enable_if_t<std::conjunction_v<std::is_move_constructible<Type>, std::is_convertible<std::invoke_result_t<Fty>, Type>>>* = nullptr>
		[[nodiscard]]
		constexpr value_type value_or_eval(Fty&& f)&&;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, value_type&>>* = nullptr>
		constexpr void then(Fty&& f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, value_type>>* = nullptr>
		constexpr void then(Fty&& f) const;

		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, value_type&>>>
		Optional<R> map(Fty f);

		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, value_type>>>
		Optional<R> map(Fty f) const;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Optional<Type>& value)
		{
			if constexpr (std::is_same_v<CharType, char32>)
			{
				const String s = Format(value);
				return output.write(s.data(), s.size());
			}
			else
			{
				if (value)
				{
					const CharType opt[] = { '(', 'O','p','t','i','o','n','a','l',')','\0' };

					if constexpr (std::is_same_v<Type, char32>)
					{
						return output << opt << String(1, *value);
					}
					else
					{
						return output << opt << *value;
					}
				}
				else
				{
					const CharType no[] = { 'n','o','n','e','\0' };
					return output << no;
				}
			}
		}

		friend void Formatter(FormatData& formatData, const Optional& value)
		{
			if (value)
			{
				formatData.string.append(U"(Optional)"_sv);

				Formatter(formatData, *value);
			}
			else
			{
				Formatter(formatData, none);
			}
		}
	};

	template <class Type1, class Type2>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<Type1>& lhs, const Optional<Type2>& rhs);

	template <class Type1, class Type2>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<Type1>& lhs, const Optional<Type2>& rhs);

	template <class Type1, class Type2>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<Type1>& lhs, const Optional<Type2>& rhs);

	template <class Type1, class Type2>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<Type1>& lhs, const Optional<Type2>& rhs);

	template <class Type1, class Type2>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<Type1>& lhs, const Optional<Type2>& rhs);

	template <class Type1, class Type2>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<Type1>& lhs, const Optional<Type2>& rhs);

#if __cpp_impl_three_way_comparison && __cpp_lib_concepts && !SIV3D_PLATFORM(MACOS) && !SIV3D_PLATFORM(WEB)
	template <class Type1, std::three_way_comparable_with<Type1> Type2>
	[[nodiscard]]
	inline constexpr std::compare_three_way_result_t<Type1, Type2> operator <=>(const Optional<Type1>& lhs, const Optional<Type2>& rhs);
#endif

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<Type>& opt, None_t) noexcept;

#if __cpp_impl_three_way_comparison

	template <class Type>
	[[nodiscard]]
	inline constexpr std::strong_ordering operator <=>(const Optional<Type>& opt, None_t) noexcept;

#else

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator ==(None_t, const Optional<Type>& opt) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<Type>& opt, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator !=(None_t, const Optional<Type>& opt) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<Type>& opt, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <(None_t, const Optional<Type>& opt) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<Type>& opt, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator <=(None_t, const Optional<Type>& opt) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<Type>& opt, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >(None_t, const Optional<Type>& opt) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<Type>& opt, None_t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr bool operator >=(None_t, const Optional<Type>& opt) noexcept;

#endif


	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator ==(const Optional<Type>& opt, const U& value);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator ==(const U& value, const Optional<Type>& opt);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator !=(const Optional<Type>& opt, const U& value);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator !=(const U& value, const Optional<Type>& opt);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator <(const Optional<Type>& opt, const U& value);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator <(const U& value, const Optional<Type>& opt);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator <=(const Optional<Type>& opt, const U& value);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator <=(const U& value, const Optional<Type>& opt);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator >(const U& value, const Optional<Type>& opt);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator >(const Optional<Type>& opt, const U& value);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator >=(const Optional<Type>& opt, const U& value);

	template <class Type, class U>
	[[nodiscard]]
	inline constexpr bool operator >=(const U& value, const Optional<Type>& opt);

#if __cpp_impl_three_way_comparison && __cpp_lib_concepts && !SIV3D_PLATFORM(MACOS) && !SIV3D_PLATFORM(WEB)
	namespace detail {
		template <class T, template <class...> class Tmp>
		inline constexpr bool is_specialization_v = false;

		template <template <class...> class Tmp, class... Args>
		inline constexpr bool is_specialization_v<Tmp<Args...>, Tmp> = true;
	}

	template <class Type, class U>
	requires (!detail::is_specialization_v<U, Optional>) && std::three_way_comparable_with<Type, U>
	[[nodiscard]]
	inline constexpr std::compare_three_way_result_t<Type, U> operator <=>(const Optional<Type>& opt, const U& value);
#endif

	template <class Type>
	[[nodiscard]]
	inline constexpr Optional<std::decay_t<Type>> MakeOptional(Type&& v);

	template <class Type, class... Args>
	[[nodiscard]]
	inline constexpr Optional<Type> MakeOptional(Args&&... args);

	template< class Type, class U, class... Args >
	[[nodiscard]]
	inline constexpr Optional<Type> MakeOptional(std::initializer_list<U> il, Args&&... args);

	template <class Type>
	inline void swap(Optional<Type>& a, Optional<Type>& b) noexcept(noexcept(a.swap(b)));

	template <class Type>
	Optional(Type)->Optional<Type>;
}

template <class Type>
struct SIV3D_HIDDEN fmt::formatter<s3d::Optional<Type>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Optional<Type>& value, FormatContext& ctx)
	{
		const s3d::String s = s3d::Format(value);
		const basic_string_view<s3d::char32> sv(s.data(), s.size());

		if (tag.empty())
		{
			return format_to(ctx.out(), U"{}", sv);
		}
		else
		{
			const std::u32string format = (U"{:" + tag + U'}');
			return format_to(ctx.out(), format, sv);
		}
	}
};

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <class Type>
struct std::hash<s3d::Optional<Type>>
{
	[[nodiscard]]
	size_t operator ()(const s3d::Optional<Type>& value) const noexcept
	{
		if (value)
		{
			return std::hash<Type>{}(*value);
		}
		else
		{
			return 0;
		}
	}
};

# include "detail/Optional.ipp"
