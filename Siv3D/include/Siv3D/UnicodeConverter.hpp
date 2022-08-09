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
# include <array>
# include "Common.hpp"

namespace s3d
{
	/// @brief UTF-8 から UTF-32 への逐次変換クラス
	struct UTF8toUTF32_Converter
	{
	public:

		/// @brief データを追加します。
		/// @param code 変換用の UTF-8 データ
		/// @return `get()` で文字を取得可能になった場合 true, それ以外の場合は false
		[[nodiscard]]
		bool put(char8 code) noexcept;

		/// @brief 作成された文字を取得します。
		/// @return 作成された文字
		[[nodiscard]]
		char32 get() const noexcept;

	private:

		char8 m_buffer[4];

		size_t m_count = 0;

		char32 m_result = 0;
	};

	/// @brief UTF-16 から UTF-32 への逐次変換クラス
	struct UTF16toUTF32_Converter
	{
	public:

		/// @brief データを追加します。
		/// @param code 変換用の UTF-16 データ
		/// @return `get()` で文字を取得可能になった場合 true, それ以外の場合は false
		[[nodiscard]]
		bool put(char16 code) noexcept;

		/// @brief 作成された文字を取得します。
		/// @return 作成された文字
		[[nodiscard]]
		char32 get() const noexcept;

	private:

		char32 m_result = 0;

		char16 m_buffer = 0;

		bool m_hasHighSurrogate = false;
	};

	/// @brief UTF-32 から UTF-8 への逐次変換クラス
	struct UTF32toUTF8_Converter
	{
	public:

		/// @brief データを追加します。
		/// @param code 変換用の UTF-32 データ
		/// @return 作成された UTF-8 データのサイズ
		[[nodiscard]]
		size_t put(char32 code) noexcept;

		/// @brief 作成された UTF-8 文字を取得します。
		/// @return 作成された UTF-8 文字
		[[nodiscard]]
		const std::array<char8, 4>& get() const noexcept;

		/// @brief 作成された UTF-8 文字の配列の先頭イテレータを返します。
		/// @return 作成された UTF-8 文字の配列の先頭イテレータ
		[[nodiscard]]
		std::array<char8, 4>::const_iterator begin() const noexcept;

	private:

		std::array<char8, 4> m_buffer;
	};

	/// @brief UTF-32 から UTF-16 への逐次変換クラス
	struct UTF32toUTF16_Converter
	{
	public:

		/// @brief データを追加します。
		/// @param code 変換用の UTF-32 データ
		/// @return `get()` で文字を取得可能になった場合 true, それ以外の場合は false
		[[nodiscard]]
		size_t put(char32 code) noexcept;

		/// @brief 作成された UTF-16 文字を取得します。
		/// @return 作成された UTF-16 文字
		[[nodiscard]]
		const std::array<char16, 2>& get() const noexcept;

		/// @brief 作成された UTF-16 文字の配列の先頭イテレータを返します。
		/// @return 作成された UTF-16 文字の配列の先頭イテレータ
		[[nodiscard]]
		std::array<char16, 2>::const_iterator begin() const noexcept;

	private:

		std::array<char16, 2> m_buffer;
	};
}

# include "detail/UnicodeConverter.ipp"
