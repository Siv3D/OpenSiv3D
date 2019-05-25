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
# include <string>
# include <array>
# include "Fwd.hpp"
# include "StringView.hpp"
# include "Utility.hpp"

namespace s3d
{
	namespace Unicode
	{
		[[nodiscard]] inline constexpr bool IsHighSurrogate(const char16 ch) noexcept
		{
			return InRange<char16>(ch, 0xD800, 0xDBFF);
		}

		[[nodiscard]] inline constexpr bool IsLowSurrogate(const char16 ch) noexcept
		{
			return InRange<char16>(ch, 0xDC00, 0xDFFF);
		}

		/// <summary>
		/// ASCII 文字列を String に変換します。
		/// </summary>
		/// <param name="asciiString">
		/// ASCII 文字で構成された文字列
		/// </param>
		/// <remarks>
		/// Widen() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] String WidenAscii(std::string_view asciiText);

		/// <summary>
		/// std::string を String に変換します。
		/// </summary>
		/// <param name="view">
		/// std::string
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] String Widen(std::string_view view);

		/// <summary>
		/// ASCII 文字列を std::string に変換します。
		/// </summary>
		/// <param name="asciiText">
		/// ASCII 文字で構成された文字列
		/// </param>
		/// <remarks>
		/// Narrow() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::string NarrowAscii(StringView asciiText);

		/// <summary>
		/// String を std::string に変換します。
		/// </summary>
		/// <param name="view">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::string Narrow(StringView view);

		/// <summary>
		/// String を std::wstring に変換します。
		/// </summary>
		/// <param name="view">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::wstring ToWString(StringView view);

		/// <summary>
		/// std::wstring を String に変換します。
		/// </summary>
		/// <param name="view">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] String FromWString(std::wstring_view view);

		/// <summary>
		/// UTF-8 文字列を String に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] String FromUTF8(std::string_view view);

		/// <summary>
		/// UTF-16 文字列を String に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] String FromUTF16(std::u16string_view view);

		/// <summary>
		/// UTF-32 文字列を String に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-32 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] String FromUTF32(std::u32string_view view);

		/// <summary>
		/// String を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::string ToUTF8(StringView view);

		/// <summary>
		/// String を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::u16string ToUTF16(StringView view);

		/// <summary>
		/// String を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::u32string ToUTF32(StringView view);

		/// <summary>
		/// UTF-8 文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::u16string UTF8ToUTF16(std::string_view view);

		/// <summary>
		/// UTF-8 文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::u32string UTF8ToUTF32(std::string_view view);

		/// <summary>
		/// UTF-16 文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::string UTF16ToUTF8(std::u16string_view view);

		/// <summary>
		/// UTF-16 文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::u32string UTF16ToUTF32(std::u16string_view view);

		/// <summary>
		/// UTF-32 文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::string UTF32ToUTF8(std::u32string_view view);

		/// <summary>
		/// UTF-32 文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="view">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]] std::u16string UTF32ToUTF16(std::u32string_view view);

		[[nodiscard]] size_t CountCodePoints(std::string_view view) noexcept;

		[[nodiscard]] size_t CountCodePoints(std::u16string_view view) noexcept;

		[[nodiscard]] size_t CountCodePoints(StringView view) noexcept;

		struct Translator_UTF8toUTF32
		{
		private:

			char8 m_buffer[4];

			uint32 m_count = 0;

			char32 m_result = 0;

		public:

			[[nodiscard]] bool put(char8 code) noexcept;

			[[nodiscard]] char32 get() const noexcept
			{
				return m_result;
			}
		};

		struct Translator_UTF16toUTF32
		{
		private:

			char32 m_result = 0;

			char16 m_buffer = 0;

			bool m_hasHighSurrogate = false;

		public:

			[[nodiscard]] bool put(char16 code) noexcept;

			[[nodiscard]] char32 get() const noexcept
			{
				return m_result;
			}
		};

		struct Translator_UTF32toUTF8
		{
		private:

			std::array<char8, 4> m_buffer;

		public:

			[[nodiscard]] size_t put(char32 code) noexcept;

			[[nodiscard]] const std::array<char8, 4>& get() const noexcept
			{
				return m_buffer;
			}

			[[nodiscard]] std::array<char8, 4>::const_iterator begin() const noexcept
			{
				return m_buffer.begin();
			}
		};

		struct Translator_UTF32toUTF16
		{
		private:

			std::array<char16, 2> m_buffer;

		public:

			[[nodiscard]] size_t put(char32 code) noexcept;

			[[nodiscard]] const std::array<char16, 2>& get() const noexcept
			{
				return m_buffer;
			}

			[[nodiscard]] std::array<char16, 2>::const_iterator begin() const noexcept
			{
				return m_buffer.begin();
			}
		};
	}
}
