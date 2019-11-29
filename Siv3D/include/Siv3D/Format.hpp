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
# include <xmmintrin.h>
# include <sstream>
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Fwd.hpp"
# include "FormatBool.hpp"
# include "FormatInt.hpp"
# include "FormatFloat.hpp"
# include "FormatLiteral.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "Unicode.hpp"

namespace s3d
{
	/// <summary>
	/// Formatter の内部で使用するデータ
	/// </summary>
	struct FormatData
	{
		String string;

		struct DecimalPlaces
		{
			explicit constexpr DecimalPlaces(int32 v = 5) noexcept
				: value(v) {}
			
			int32 value;
		} decimalPlaces = DecimalPlaces(5);

		FormatData() = default;
	};

	/// <summary>
	/// 浮動小数点数を変換する際の小数点以下の最大桁数を指定するマニピュレータを返します。
	/// </summary>
	/// <param name="width">
	/// 小数点以下の最大桁数
	/// </param>
	/// <remarks>
	/// この関数が返すマニピュレータを Format の引数にすると、
	/// 該当 Format() 内のそれ以降の浮動小数点数の変換に適用されます。
	/// </remarks>
	/// <returns>
	/// Format に渡すマニピュレータ
	/// </returns>
	[[nodiscard]] inline constexpr FormatData::DecimalPlaces DecimalPlaces(const int32 width)
	{
		return FormatData::DecimalPlaces(width);
	}

	inline namespace Literals
	{
		inline namespace DecimalPlaceLiterals
		{
			[[nodiscard]] inline constexpr FormatData::DecimalPlaces operator ""_dp(unsigned long long width)
			{
				return DecimalPlaces(static_cast<int32>(width));
			}
		}
	}

	namespace detail
	{
		/// <summary>
		/// Format_impl の内部で使用するクラス
		/// </summary>
		template <class...>
		struct format_validation : std::true_type {};

		/// <summary>
		/// Format_impl の内部で使用するクラス
		/// </summary>
		template <class T, class... TT>
		struct format_validation<T, TT...> : std::bool_constant<!(std::is_same_v<std::decay_t<T>, char*> || std::is_same_v<std::decay_t<T>, wchar_t*>) && format_validation<TT...>::value> {};

		void AppendInt(char32** p, const long value);

		struct FormatPlaceholder_impl
		{
		private:

			String m_head;

			String m_tail;

		public:

			FormatPlaceholder_impl(String&& head, String&& tail)
				: m_head(std::move(head))
				, m_tail(std::move(tail)) {}

			template <class Type>
			String operator ()(const Type& value) const;
		};

		struct Format_impl
		{
		private:

			static void _format(const FormatData&)
			{
				return;
			}

			template <class Type, class... Args>
			static void _format(FormatData& formatData, const Type& value, const Args&... args)
			{
				Formatter(formatData, value);
				
				_format(formatData, args...);
			}

		public:

			/// <summary>
			/// 一連の引数を文字列に変換します。
			/// </summary>
			/// <param name="args">
			/// 変換する値
			/// </param>
			/// <returns>
			/// 引数を文字列に変換して連結した文字列
			/// </returns>
			template <class... Args, std::enable_if_t<format_validation<Args...>::value>* = nullptr>
			[[nodiscard]] String operator ()(const Args&... args) const
			{
				FormatData formatData;
				
				_format(formatData, args...);
				
				return std::move(formatData.string);
			}

			template <class... Args, std::enable_if_t<!format_validation<Args...>::value>* = nullptr>
			[[nodiscard]] String operator ()(const Args&...) const
			{
				// font(...) などで、U"..." (const char32*) ではない文字列が使われていることを知らせるエラーです
				static_assert(format_validation<Args...>::value, "string literal \"\" and L\"\" cannot be used in Format(). Use U\"\" instead.");
				
				return String();
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="ch">
			/// 変換する値
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]] String operator ()(const char32 ch) const
			{
				return String(1, ch);
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="str">
			/// 変換する文字列
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]] String operator ()(const char32* const text) const
			{
				return String(text);
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="str">
			/// 変換する文字列
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]] const String& operator ()(const String& text) const
			{
				return text;
			}

			/// <summary>
			/// 引数を文字列に変換します。
			/// </summary>
			/// <param name="str">
			/// 変換する文字列
			/// </param>
			/// <returns>
			/// 引数を文字列に変換した文字列
			/// </returns>
			[[nodiscard]] String operator ()(String&& text) const noexcept
			{
				return std::move(text);
			}
		
			[[nodiscard]] constexpr Format_impl operator ()(PlaceHolder_t) const
			{
				return detail::Format_impl();
			}

			template <class Head>
			[[nodiscard]] FormatPlaceholder_impl operator ()(Head&& head, PlaceHolder_t) const
			{
				return FormatPlaceholder_impl(operator()(std::forward<Head>(head)), String());
			}

			template <class Tail>
			[[nodiscard]] FormatPlaceholder_impl operator ()(PlaceHolder_t, Tail&& tail) const
			{
				return FormatPlaceholder_impl(String(), operator()(std::forward<Tail>(tail)));
			}

			template <class Head, class Tail>
			[[nodiscard]] FormatPlaceholder_impl operator ()(Head&& head, PlaceHolder_t, Tail&& tail) const
			{
				return FormatPlaceholder_impl(operator()(std::forward<Head>(head)), operator()(std::forward<Tail>(tail)));
			}
		};

		template <class Type>
		String FormatPlaceholder_impl::operator ()(const Type& value) const
		{
			return m_head + Format_impl()(value) + m_tail;
		}

		void FormatterHelper(String& dst, const std::wostringstream& ws);
	}

	inline constexpr auto Format = detail::Format_impl();

	void Formatter(FormatData& formatData, const FormatData::DecimalPlaces decimalPlace);

	void Formatter(FormatData& formatData, int32);

	void Formatter(FormatData& formatData, uint32 value);

	void Formatter(FormatData& formatData, long long value);

	void Formatter(FormatData& formatData, unsigned long long value);

	void Formatter(FormatData& formatData, double value);

	void Formatter(FormatData& formatData, const void* value);

	void Formatter(FormatData& formatData, const char* str) = delete;

	void Formatter(FormatData& formatData, const wchar_t* str) = delete;

	void Formatter(FormatData& formatData, char16_t ch);

	void Formatter(FormatData& formatData, char32_t ch);
	
	void Formatter(FormatData& formatData, std::nullptr_t);

	void Formatter(FormatData& formatData, bool value);

	void Formatter(FormatData& formatData, const char value);

	void Formatter(FormatData& formatData, const int8 value);

	void Formatter(FormatData& formatData, const uint8 value);

	void Formatter(FormatData& formatData, const int16 value);

	void Formatter(FormatData& formatData, const uint16 value);

	void Formatter(FormatData& formatData, const long value);

	void Formatter(FormatData& formatData, const unsigned long value);

	void Formatter(FormatData& formatData, const float value);
    
	void Formatter(FormatData& formatData, const long double value);

	void Formatter(FormatData& formatData, __m128 value);

	void Formatter(FormatData& formatData, const char32* const str);

	void Formatter(FormatData& formatData, const std::u32string& str);

	void Formatter(FormatData& formatData, const String& value);

# if __has_include(<compare>) && SIV3D_PLATFORM(WINDOWS)

	void Formatter(FormatData& formatData, std::strong_ordering value);

	void Formatter(FormatData& formatData, std::weak_ordering value);

	void Formatter(FormatData& formatData, std::partial_ordering value);

# endif

	template <class Iterator>
	inline void Formatter(FormatData& formatData, Iterator begin, Iterator end)
	{
		formatData.string.push_back(U'{');

		bool isFirst = true;

		while (begin != end)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				formatData.string.append(U", "_sv);
			}

			Formatter(formatData, *begin);

			++begin;
		}

		formatData.string.push_back(U'}');
	}

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const Type(&values)[N])
	{
		Formatter(formatData, std::begin(values), std::end(values));
	}

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const std::array<Type, N>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type, class Allocator = std::allocator<Type>>
	inline void Formatter(FormatData& formatData, const std::vector<Type, Allocator>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const std::initializer_list<Type>& ilist)
	{
		Formatter(formatData, ilist.begin(), ilist.end());
	}

	template <class Fitrst, class Second>
	inline void Formatter(FormatData& formatData, const std::pair<Fitrst, Second>& pair)
	{
		formatData.string.push_back(U'{');

		Formatter(formatData, pair.first);

		formatData.string.append(U", "_sv);
	
		Formatter(formatData, pair.second);

		formatData.string.push_back(U'}');
	}

	void Formatter(FormatData& formatData, const None_t&);

	template <class Type>
	inline void Formatter(FormatData& formatData, const Optional<Type>& value)
	{
		if (value)
		{
			formatData.string.append(U"Optional "_sv);

			Formatter(formatData, value.value());
		}
		else
		{
			Formatter(formatData, none);
		}
	}

	template <class Type, class = decltype(std::declval<std::wostream>() << std::declval<Type>())>
	inline void Formatter(FormatData& formatData, const Type& value)
	{
		std::wostringstream wos;

		wos << value;

		detail::FormatterHelper(formatData.string, wos);
	}
}

namespace s3d
{
	namespace detail
	{
		template <class ParseContext>
		auto GetFmtTag(String& tag, ParseContext& ctx)
		{
			auto it = fmt_s3d::internal::null_terminating_iterator<s3d::char32>(ctx);

			if (*it == ':')
			{
				++it;
			}

			auto end = it;

			while (*end && *end != '}')
			{
				++end;
			}

			tag.assign(fmt_s3d::internal::pointer_from(it), fmt_s3d::internal::pointer_from(end));

			return fmt_s3d::internal::pointer_from(end);
		}

		inline constexpr size_t MakeFmtArgLength_impl(const StringView view)
		{
			return view.size();
		}

		template <class... Args>
		inline constexpr size_t MakeFmtArgLength_impl(const StringView view, const Args&... args)
		{
			return view.size() + MakeFmtArgLength_impl(args...);
		}

		inline String MakeFmtArg_impl(String& result, const StringView view)
		{
			return result.append(view);
		}

		template <class... Args>
		inline String MakeFmtArg_impl(String& result, const StringView view, const Args&... args)
		{
			result.append(view);
			return MakeFmtArg_impl(result, args...);
		}

		template <class... Args>
		inline String MakeFmtArg(const StringView view, const Args&... args)
		{
			String result;
			result.reserve(MakeFmtArgLength_impl(view, args...));
			result.append(view);
			return MakeFmtArg_impl(result, args...);
		}
	}
}

namespace fmt_s3d
{
	template <>
	struct formatter<s3d::String, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::String& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(U"{:", tag, U"}");

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), wstring_view(value.data(), value.size()));
		}
	};

	template <>
	struct formatter<s3d::StringView, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::StringView value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(U"{:", tag, U"}");

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), wstring_view(value.data(), value.size()));
		}
	};
	
	template <class Type>
	struct formatter<Type, s3d::char32>
	{
		s3d::String tag;
		
		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}
		
		template <class Context>
		auto format(const Type& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(U"{:", tag, U"}");
			
			const s3d::String s = s3d::Format(value);
			
			const basic_string_view<s3d::char32> str(s.data(), s.size());
			
			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), str);
		}
	};
}
