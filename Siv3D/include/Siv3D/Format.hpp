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
# include <xmmintrin.h>
# include <sstream>
# include "Fwd.hpp"
# include "BoolFormat.hpp"
# include "IntFormat.hpp"
# include "FloatFormat.hpp"
# include "FormatLiteral.hpp"
# include "String.hpp"
# include "Unicode.hpp"

namespace s3d
{
	/// <summary>
	/// Formatter の内部で使用するデータ
	/// </summary>
	struct FormatData
	{
		String string;

		struct DecimalPlace
		{
			explicit constexpr DecimalPlace(int32 v = 5) noexcept : value(v) {}
			
			int32 value;
		} decimalPlace;
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
	[[nodiscard]] inline constexpr FormatData::DecimalPlace DecimalPlace(const int32 width)
	{
		return FormatData::DecimalPlace(width);
	}

	namespace Literals
	{
		[[nodiscard]] inline constexpr FormatData::DecimalPlace operator ""_dp(unsigned long long width)
		{
			return DecimalPlace(static_cast<int32>(width));
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
				static_assert(format_validation<Args...>::value, "type \"char* or wchar_t*\" cannot be used in Format()");
				
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
	}

	constexpr auto Format = detail::Format_impl();

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

	inline void Formatter(FormatData& formatData, const char value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, const int8 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, const uint8 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	inline void Formatter(FormatData& formatData, const int16 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, const uint16 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	inline void Formatter(FormatData& formatData, const long value)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		Formatter(formatData, static_cast<int32>(value));

	# else

		Formatter(formatData, static_cast<long long>(value));

	# endif	
	}

	inline void Formatter(FormatData& formatData, const unsigned long value)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		Formatter(formatData, static_cast<uint32>(value));

	# else

		Formatter(formatData, static_cast<unsigned long long>(value));

	# endif	
	}

	inline void Formatter(FormatData& formatData, const float value)
	{
		Formatter(formatData, static_cast<double>(value));
	}
    
   	inline void Formatter(FormatData& formatData, const long double value)
    {
        Formatter(formatData, static_cast<double>(value));
    }

	void Formatter(FormatData& formatData, __m128 value);

	inline void Formatter(FormatData& formatData, const FormatData::DecimalPlace decimalPlace)
	{
		formatData.decimalPlace = decimalPlace;
	}

	inline void Formatter(FormatData& formatData, const char32* const str)
	{
		formatData.string.append(str);
	}

	inline void Formatter(FormatData& formatData, const std::u32string& str)
	{
		formatData.string.append(str.begin(), str.end());
	}

	//inline void Formatter(FormatData& formatData, const char16_t* const str)
	//{
	//	formatData.string.append(Unicode::FromUTF16(str));
	//}

	//inline void Formatter(FormatData& formatData, const std::u16string& str)
	//{
	//	formatData.string.append(Unicode::FromUTF16(str));
	//}

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
				formatData.string.push_back(U',');
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

		formatData.string.push_back(U',');
	
		Formatter(formatData, pair.second);

		formatData.string.push_back(U'}');
	}

	inline void Formatter(FormatData& formatData, const None_t&)
	{
		formatData.string.append(U"none", 4);
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const Optional<Type>& value)
	{
		if (value)
		{
			formatData.string.append(U"Optional ", 9);

			Formatter(formatData, value.value());
		}
		else
		{
			formatData.string.append(U"none", 4);
		}
	}

	inline void Formatter(FormatData& formatData, const String& value)
	{
		formatData.string.append(value);
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const Type& value)
	{
		std::wostringstream wos;

		wos << value;

		formatData.string.append(Unicode::FromWString(wos.str()));
	}
}

namespace s3d
{
	namespace detail
	{
		template <class Char>
		std::basic_string<Char> GetTag(const Char*& format_str)
		{
			const Char* beg = format_str;

			if (*format_str == Char(':'))
			{
				++format_str;
			}

			const Char *end = format_str;

			while (*end && *end != Char('}'))
			{
				++end;
			}

			if (*end != Char('}'))
			{
				FMT_THROW(fmt::FormatError("missing '}' in format string"));
			}

			format_str = end + 1;

			return std::basic_string<Char>(beg, end);
		}
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::char32, ArgFormatter>& f, const s3d::char32*& format_str, const s3d::StringView& value)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = U"{" + tag + U"}";

		f.writer().write(fmt, value.to_string());
	}

	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::char32, ArgFormatter>& f, const s3d::char32*& format_str, const s3d::String& value)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = U"{" + tag + U"}";

		f.writer().write(fmt, value.str());
	}

	template <class Char, class ArgFormatter, class Type>
	void format_arg(BasicFormatter<Char, ArgFormatter> &f, const Char*& format_str, const Type &value)
	{
		const s3d::String us = s3d::Format(value);
		
		BasicStringRef<Char> str(&us[0], us.size());
		
		using MakeArg = internal::MakeArg<BasicFormatter<Char>>;
		
		format_str = f.format(format_str, MakeArg(str));
	}
}
