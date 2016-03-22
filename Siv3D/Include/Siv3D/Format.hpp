//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "FormatInt.hpp"
# include "FormatFloat.hpp"

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
			explicit constexpr DecimalPlace(int32 v = 5) : value(v) {}
			int32 value;
		} decimalPlace;
	};

	namespace detail
	{
		/// <summary>
		/// Format の内部で使用するクラス
		/// </summary>
		template <class...>
		struct format_validation : std::true_type {};

		/// <summary>
		/// Format の内部で使用するクラス
		/// </summary>
		template <class T, class... TT>
		struct format_validation<T, TT...>
			: std::integral_constant<bool, !std::is_same<std::decay_t<T>, char*>::value && format_validation<TT...>::value> {};

		/// <summary>
		/// Format の内部で使用する関数
		/// </summary>
		inline void Format(const FormatData&)
		{
			return;
		}

		/// <summary>
		/// Format の内部で使用する関数
		/// </summary>
		template <class Type, class ... Args>
		inline void Format(FormatData& formatData, const Type& value, const Args& ... args)
		{
			Formatter(formatData, value);
			Format(formatData, args...);
		}
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
		detail::Format(formatData, args...);
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
	inline String Format(wchar ch)
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
	inline String Format(String&& str)
	{
		return std::move(str);
	}

	inline void Formatter(FormatData& formatData, int32 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, uint32 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, int64 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, uint64 value)
	{
		const detail::FormatInt buffer(value);
		formatData.string.append(buffer.c_str(), buffer.size());
	}

	inline void Formatter(FormatData& formatData, double value)
	{
		wchar buf[384];
		const size_t len = detail::FormatFloat(buf, value, formatData.decimalPlace.value, false);
		formatData.string.append(buf, len);
	}

	//void Formatter(FormatData& formatData, const void* value);

	void Formatter(FormatData& formatData, const char* const str) = delete;

	inline void Formatter(FormatData& formatData, std::nullptr_t)
	{
		formatData.string.append(L"null", 4);
	}

	inline void Formatter(FormatData& formatData, bool value)
	{
		if (value)
		{
			formatData.string.append(L"true", 4);
		}
		else
		{
			formatData.string.append(L"false", 5);
		}
	}

	inline void Formatter(FormatData& formatData, char value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, int8 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, uint8 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	inline void Formatter(FormatData& formatData, int16 value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, uint16 value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	inline void Formatter(FormatData& formatData, long value)
	{
		Formatter(formatData, static_cast<int32>(value));
	}

	inline void Formatter(FormatData& formatData, unsigned long value)
	{
		Formatter(formatData, static_cast<uint32>(value));
	}

	inline void Formatter(FormatData& formatData, wchar value)
	{
		formatData.string.push_back(value);
	}

	inline void Formatter(FormatData& formatData, float value)
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

	inline void Formatter(FormatData& formatData, const String& str)
	{
		formatData.string.append(str);
	}
}
