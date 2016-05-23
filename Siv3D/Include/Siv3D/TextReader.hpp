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

		class CTextReader;

		std::shared_ptr<CTextReader> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		TextReader();

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
		explicit TextReader(const FilePath& path, const Optional<TextEncoding>& encoding = unspecified);

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		template <class Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value && !std::is_lvalue_reference<Reader>::value>* = nullptr>
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
		bool open(const FilePath& path, const Optional<TextEncoding>& encoding = unspecified);

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式、自動で設定する場合は unspecified
		/// </param>
		template <class Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value && !std::is_lvalue_reference<Reader>::value>* = nullptr>
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
		bool isOpened() const;

		/// <summary>
		/// テキストファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// テキストファイルから 1 文字読み込みます。
		/// </summary>
		/// <returns>
		/// 読み込みに成功した場合はその文字の Optional, ファイルの終端や失敗の場合は none
		/// </returns>
		Optional<wchar> readChar();

		/// <summary>
		/// テキストファイルから 1 行読み込みます。
		/// </summary>
		/// <returns>
		/// 読み込みに成功した場合はその文字列の Optional, ファイルの終端や失敗の場合は none
		/// </returns>
		Optional<String> readLine();

		/// <summary>
		/// テキストファイルの内容をすべて読み込みます。
		/// </summary>
		/// <returns>
		/// 読み込んだ文字列
		/// </returns>
		String readAll();

		/// <summary>
		/// テキストファイルから 1 文字読み込みます。
		/// </summary>
		/// <param name="ch">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功した場合 true, ファイルの終端や失敗の場合は false
		/// </returns>
		bool readChar(wchar& ch);

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
		/// テキストファイルの現在の読み込み位置以降の内容をすべて読み込みます。
		/// </summary>
		/// <param name="str">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功した場合 true, ファイルの終端や失敗の場合は false
		/// </returns>
		bool readAll(String& str);

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		const FilePath& path() const;

		/// <summary>
		/// オープンしているテキストファイルのエンコーディング形式を返します。
		/// </summary>
		TextEncoding encoding() const;
	};
}
