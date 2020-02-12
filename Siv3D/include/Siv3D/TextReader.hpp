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
# include <memory>
# include "Fwd.hpp"
# include "String.hpp"
# include "Unspecified.hpp"
# include "TextEncoding.hpp"

namespace s3d
{
	/// <summary>
	/// 読み込み用テキストファイル
	/// </summary>
	class TextReader
	{
	private:

		class TextReaderDetail;

		std::shared_ptr<TextReaderDetail> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		TextReader();

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		explicit TextReader(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit TextReader(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified)
			: TextReader()
		{
			open(std::forward<Reader>(reader), encoding);
		}

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		explicit TextReader(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = unspecified);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~TextReader();

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified)
		{
			return open(std::make_shared<Reader>(std::forward<Reader>(reader)), encoding);
		}

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		bool open(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = unspecified);

		/// <summary>
		/// テキストファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// テキストファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool isOpen() const;

		/// <summary>
		/// テキストファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] explicit operator bool() const { return isOpen(); }

		/// <summary>
		/// テキストファイルから 1 文字読み込みます。
		/// </summary>
		/// <returns>
		/// 読み込みに成功した場合はその文字の Optional, ファイルの終端や失敗の場合は none
		/// </returns>
		[[nodiscard]] Optional<char32> readChar();

		/// <summary>
		/// テキストファイルから 1 行読み込みます。
		/// </summary>
		/// <returns>
		/// 読み込みに成功した場合はその文字列の Optional, ファイルの終端や失敗の場合は none
		/// </returns>
		[[nodiscard]] Optional<String> readLine();

		/// <summary>
		/// テキストファイルの内容をすべて読み込みます。
		/// </summary>
		/// <returns>
		/// 読み込んだ文字列
		/// </returns>
		[[nodiscard]] String readAll();

		/// <summary>
		/// テキストファイルから 1 文字読み込みます。
		/// </summary>
		/// <param name="ch">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功した場合 true, ファイルの終端や失敗の場合は false
		/// </returns>
		bool readChar(char32& ch);

		/// <summary>
		/// テキストファイルから 1 行読み込みます。
		/// </summary>
		/// <param name="str">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功した場合 true, ファイルの終端や失敗の場合は false
		/// </returns>
		bool readLine(String& str);

		/// <summary>
		/// テキストファイルの内容をすべて読み込みます。
		/// </summary>
		/// <param name="str">
		/// 読み込み先
		/// </param>
		void readAll(String& str);

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		[[nodiscard]] const FilePath& path() const;

		/// <summary>
		/// オープンしているテキストファイルのエンコーディング形式を返します。
		/// </summary>
		[[nodiscard]] TextEncoding encoding() const;
	};
}
