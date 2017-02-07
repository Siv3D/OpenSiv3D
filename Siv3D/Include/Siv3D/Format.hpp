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
# include <sstream>
# include <array>
# include "Fwd.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "FormatInt.hpp"
# include "FormatFloat.hpp"
# include "FormatLiteral.hpp"

namespace s3d
{
	/// <summary>
	/// Format の内部で使用するデータ
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
	inline constexpr FormatData::DecimalPlace DecimalPlace(const int32 width)
	{
		return FormatData::DecimalPlace(width);
	}

	inline namespace literals
	{
		inline namespace formatting_literals
		{
			inline constexpr FormatData::DecimalPlace operator ""_dp(unsigned long long width)
			{
				return DecimalPlace(static_cast<int32>(width));
			}
		}
	}

	namespace detail
	{
		/// <summary>
		/// Format の内部で使用するクラス
		/// </summary>
		template <class...>
		struct format_validation
			: std::true_type {};

		/// <summary>
		/// Format の内部で使用するクラス
		/// </summary>
		template <class T, class... TT>
		struct format_validation<T, TT...>
			: std::integral_constant<bool, !std::is_same<std::decay_t<T>, char*>::value && format_validation<TT...>::value> {};

		/// <summary>
		/// Format の内部で使用する関数
		/// </summary>
		inline void Format_impl(const FormatData&)
		{
			return;
		}

		/// <summary>
		/// Format の内部で使用する関数
		/// </summary>
		template <class Type, class... Args>
		inline void Format_impl(FormatData& formatData, const Type& value, const Args&... args)
		{
			Formatter(formatData, value);
			Format_impl(formatData, args...);
		}

		void AppendInt(wchar** p, const long value);
	}

	/// <summary>
	/// 一連の引数を文字列に変換します。
	/// </summary>
	/// <param name="args">
	/// 変換する値
	/// </param>
	/// <returns>
	/// 引数を文字列に変換して連結した文字列
	/// </returns>
	template <class... Args>
	inline String Format(const Args&... args)
	{
		static_assert(detail::format_validation<Args...>::value, "type \"char*\" cannot be used in Format()");
		FormatData formatData;
		detail::Format_impl(formatData, args...);
		return std::move(formatData.string);
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
	inline String Format(const wchar ch)
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
	inline String Format(const wchar* const str)
	{
		return String(str);
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
	inline String Format(const String& str)
	{
		return str;
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
	inline String Format(String&& str) noexcept
	{
		return std::move(str);
	}

	void Formatter(FormatData& formatData, int32 value);

	void Formatter(FormatData& formatData, uint32 value);

	void Formatter(FormatData& formatData, int64 value);

	void Formatter(FormatData& formatData, uint64 value);

	void Formatter(FormatData& formatData, double value);

	void Formatter(FormatData& formatData, const void* value);

	void Formatter(FormatData& formatData, const char* str) = delete;

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

# ifndef SIV3D_TARGET_LINUX
	inline void Formatter(FormatData& formatData, const long value)
	{
		Formatter(formatData, static_cast<int64>(value));
	}

	inline void Formatter(FormatData& formatData, const unsigned long value)
	{
		Formatter(formatData, static_cast<uint64>(value));
	}
# endif

	inline void Formatter(FormatData& formatData, const wchar value)
	{
		formatData.string.push_back(value);
	}

	inline void Formatter(FormatData& formatData, const float value)
	{
		Formatter(formatData, static_cast<double>(value));
	}
    
   	inline void Formatter(FormatData& formatData, const long double value)
    {
        Formatter(formatData, static_cast<double>(value));
    }

	inline void Formatter(FormatData& formatData, const FormatData::DecimalPlace decimalPlace)
	{
		formatData.decimalPlace = decimalPlace;
	}

	inline void Formatter(FormatData& formatData, const wchar* const str)
	{
		formatData.string.append(str);
	}

	template <class Iterator>
	inline void Formatter(FormatData& formatData, Iterator begin, Iterator end)
	{
		formatData.string.push_back(L'{');

		bool isFirst = true;

		while (begin != end)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				formatData.string.push_back(L',');
			}

			Formatter(formatData, *begin);

			++begin;
		}

		formatData.string.push_back(L'}');
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
		formatData.string.push_back(L'{');

		Formatter(formatData, pair.first);

		formatData.string.push_back(L',');
	
		Formatter(formatData, pair.second);

		formatData.string.push_back(L'}');
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const Type& value)
	{
		std::wostringstream wos;

		wos << value;

		formatData.string.append(wos.str());
	}

	/*
	void Formatter(FormatData& formatData, const __m128& value);
	void Formatter(FormatData& formatData, const Circular& value);
	void Formatter(FormatData& formatData, const LineInt& value);
	void Formatter(FormatData& formatData, const Line& value);
	void Formatter(FormatData& formatData, const Rect& value);
	void Formatter(FormatData& formatData, const RectF& value);
	void Formatter(FormatData& formatData, const Circle& value);
	void Formatter(FormatData& formatData, const Ellipse& value);
	void Formatter(FormatData& formatData, const Triangle& value);
	void Formatter(FormatData& formatData, const Quad& value);
	void Formatter(FormatData& formatData, const RoundRect& value);
	void Formatter(FormatData& formatData, const Mat3x2& value);
	void Formatter(FormatData& formatData, const Quaternion& value);
	void Formatter(FormatData& formatData, const Mat4x4& value);
	void Formatter(FormatData& formatData, const Ray& value);
	*/
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

			if (*end != L'}')
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
	template <class ArgFormatter, class Type>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const Type& value)
	{
		s3d::detail::GetTag(format_str);
		
		f.writer() << s3d::Format(value).str();
	}
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting None_t
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[ ] istream
//	[x] wostream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, None_t)
	{
		formatData.string.append(L"none", 4);
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& os, None_t)
	{
		const CharType no[] = { 'n','o','n','e','\0' };

		return os << no;
	}
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Optional
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	template <class Type>
	inline void Formatter(FormatData& formatData, const Optional<Type>& opt)
	{
		if (opt)
		{
			formatData.string.append(L"Optional ", 9);

			Formatter(formatData, opt.value());
		}
		else
		{
			formatData.string.append(L"none", 4);
		}
	}

	template <class CharType, class Type>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Optional<Type>& x)
	{
		if (x)
		{
			const CharType opt[] = { 'O','p','t','i','o','n','a','l', ' ', '\0' };

			return os << opt << x.value();
		}
		else
		{
			const CharType no[] = { 'n','o','n','e','\0' };

			return os << no;
		}
	}
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting String
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[x] istream
//	[x] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const String& str)
	{
		formatData.string.append(str);
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::String& str)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = L"{" + tag + L"}";
				
		f.writer().write(fmt, str.str());
	}
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting StringView
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[-] istream
//	[-] wistream
//	[x] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const StringView str)
	{
		formatData.string.append(str.begin(), str.end());
	}
}

namespace fmt
{
	template <class ArgFormatter>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const s3d::StringView str)
	{
		const auto tag = s3d::detail::GetTag(format_str);

		const auto fmt = L"{" + tag + L"}";

		f.writer().write(fmt, std::wstring(str.begin(), str.end()));
	}
}
//
//////////////////////////////////////////////////////////////////////////////
