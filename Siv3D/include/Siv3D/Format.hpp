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
# include "Common.hpp"
# include "PlaceHolder.hpp"
# include "FormatData.hpp"
# include "Formatter.hpp"

namespace s3d
{
	namespace detail
	{
		template <class...>
		struct FormatArgValidation : std::true_type {};

		template <class T, class... TT>
		struct FormatArgValidation<T, TT...> : std::bool_constant<!(std::disjunction_v<std::is_same<std::decay_t<T>, char*>, std::is_same<std::decay_t<T>, wchar_t*>>) && FormatArgValidation<TT...>::value> {};

		struct FormatPlaceholder_impl
		{
		private:

			String m_head;

			String m_tail;

		public:

			SIV3D_NODISCARD_CXX20
			FormatPlaceholder_impl(String&& head, String&& tail) noexcept
				: m_head(std::move(head))
				, m_tail(std::move(tail)) {}

			template <class Type>
			[[nodiscard]]
			String operator ()(const Type& value) const;
		};

		struct Format_impl
		{
		private:

			static void Apply(const FormatData&)
			{
				return;
			}

			template <class Type, class... Args>
			static void Apply(FormatData& formatData, const Type& value, const Args&... args)
			{
				Formatter(formatData, value);

				Apply(formatData, args...);
			}

		public:

		# if __cpp_lib_concepts

			/// @brief 一連の引数を文字列に変換します。
			/// @param ...args 変換する値
			/// @return 引数を文字列に変換して連結した文字列
			template <Concept::Formattable... Args>
			[[nodiscard]]
			String operator ()(const Args&... args) const
			{
				FormatData formatData;

				Apply(formatData, args...);

				return std::move(formatData.string);
			}

			// Format できない値が Format() に渡されたときに発生するエラーです
			template <class... Args>
			[[nodiscard]]
			String operator ()(const Args&...) const = delete;

		# else

			/// @brief 一連の引数を文字列に変換します。
			/// @param ...args 変換する値
			/// @return 引数を文字列に変換して連結した文字列
			template <class... Args, std::enable_if_t<FormatArgValidation<Args...>::value>* = nullptr>
			[[nodiscard]]
			String operator ()(const Args&... args) const
			{
				FormatData formatData;

				Apply(formatData, args...);

				return std::move(formatData.string);
			}

			template <class... Args, std::enable_if_t<not FormatArgValidation<Args...>::value>* = nullptr>
			[[nodiscard]]
			String operator ()(const Args&...) const
			{
				// font(...) などで、U"..." (const char32*) ではない文字列が使われていることを知らせるエラーです
				static_assert(FormatArgValidation<Args...>::value, "string literal \"\" and L\"\" cannot be used in Format(). Use U\"\" instead.");

				return{};
			}

		# endif

			/// @brief 引数を文字列に変換します。
			/// @param ch 変換する値
			/// @return 引数から変換された文字列	
			[[nodiscard]]
			String operator ()(const char32 ch) const
			{
				return String(1, ch);
			}

			/// @brief 引数を文字列に変換します。
			/// @param s 変換する値
			/// @return 引数から変換された文字列	
			[[nodiscard]]
			String operator ()(const char32* s) const
			{
				return String(s);
			}

			/// @brief 引数を文字列に変換します。
			/// @param s 変換する値
			/// @return 引数から変換された文字列	
			[[nodiscard]]
			String operator ()(StringView s) const
			{
				return String(s);
			}

			/// @brief 引数を文字列に変換します。
			/// @param s 変換する値
			/// @return 引数から変換された文字列	
			[[nodiscard]]
			const String& operator ()(const String& s) const
			{
				return s;
			}

			/// @brief 引数を文字列に変換します。
			/// @param s 変換する値
			/// @return 引数から変換された文字列	
			[[nodiscard]]
			String operator ()(String&& s) const noexcept
			{
				return std::move(s);
			}

			[[nodiscard]]
			constexpr Format_impl operator ()(PlaceHolder_t) const
			{
				return detail::Format_impl{};
			}

			template <class Head>
			[[nodiscard]]
			FormatPlaceholder_impl operator ()(Head&& head, PlaceHolder_t) const
			{
				return FormatPlaceholder_impl(operator()(std::forward<Head>(head)), String());
			}

			template <class Tail>
			[[nodiscard]]
			FormatPlaceholder_impl operator ()(PlaceHolder_t, Tail&& tail) const
			{
				return FormatPlaceholder_impl(String(), operator()(std::forward<Tail>(tail)));
			}

			template <class Head, class Tail>
			[[nodiscard]]
			FormatPlaceholder_impl operator ()(Head&& head, PlaceHolder_t, Tail&& tail) const
			{
				return FormatPlaceholder_impl(operator()(std::forward<Head>(head)), operator()(std::forward<Tail>(tail)));
			}
		};

		template <class Type>
		String FormatPlaceholder_impl::operator ()(const Type& value) const
		{
			return m_head + Format_impl{}(value) + m_tail;
		}
	}

	inline constexpr auto Format = detail::Format_impl{};
}
