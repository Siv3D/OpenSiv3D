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
# include "FileSystem.hpp"
# include "TextEncoding.hpp"

namespace s3d
{
	/// <summary>
	/// 書き込み用テキストファイル
	/// </summary>
	class TextWriter
	{
	private:

		class CTextWriter;

		std::shared_ptr<CTextWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		TextWriter();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~TextWriter();

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式
		/// </param>
		TextWriter(const FilePath& path, TextEncoding encoding, bool writeBOM = true);

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="openMode">
		/// オープンモード
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式
		/// </param>
		explicit TextWriter(const FilePath& path, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::Default, bool writeBOM = true);

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, TextEncoding encoding, bool writeBOM = true);

		/// <summary>
		/// テキストファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="openMode">
		/// オープンモード
		/// </param>
		/// <param name="encoding">
		/// エンコーディング形式
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::Default, bool writeBOM = true);

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
		/// 現在開いているファイルの内容を消去し、書き込み位置を先頭に戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clear();

		/// <summary>
		/// ファイルに文字を書き込みます。
		/// </summary>
		/// <param name="ch">
		/// 書き込む文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void write(wchar ch);

		void write(char ch) = delete;

		/// <summary>
		/// ファイルに文字列を書き込みます。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void write(const String& str);

		/// <summary>
		/// ファイルに文字列を書き込みます。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void write(const wchar* str);

		/// <summary>
		/// ファイルに文字列を書き込みます。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列の先頭ポインタ
		/// </param>
		/// <param name="length">
		/// 書き込む文字列の長さ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void write(const wchar* str, size_t length);

		/// <summary>
		/// データを文字列に変換し、ファイルに書き込みます。
		/// </summary>
		/// <param name="args">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class ... Args>
		void write(const Args& ... args)
		{
			write(Format(args...));
		}

		/// <summary>
		/// データを文字列に変換し、ファイルに書き込みます。
		/// </summary>
		/// <param name="ilist">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Type>
		void write(std::initializer_list<Type> ilist)
		{
			for (const auto& elem : ilist)
			{
				write(Format(elem));
			}
		}

		/// <summary>
		/// ファイルに文字を書き込み、改行します。
		/// </summary>
		/// <param name="ch">
		/// 書き込む文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeln(wchar ch);

		void writeln(char ch) = delete;

		/// <summary>
		/// ファイルに文字列を書き込み、改行します。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeln(const String& str);

		/// <summary>
		/// ファイルに文字列を書き込み、改行します。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void writeln(const wchar* const str);

		/// <summary>
		/// ファイルに文字列を書き込み、改行します。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列の先頭ポインタ
		/// </param>
		/// <param name="length">
		/// 書き込む文字列の長さ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeln(const wchar* const str, size_t length);

		/// <summary>
		/// データを文字列に変換し、ファイルに書き込み、改行します。
		/// </summary>
		/// <param name="args">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class ... Args>
		void writeln(const Args& ... args)
		{
			writeln(Format(args...));
		}

		/// <summary>
		/// データを文字列に変換し、ファイルに書き込み、改行します。
		/// </summary>
		/// <param name="ilist">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Type>
		void writeln(std::initializer_list<Type> ilist)
		{
			for (const auto& elem : ilist)
			{
				writeln(Format(elem));
			}
		}

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		const FilePath& path() const;
	};
}
