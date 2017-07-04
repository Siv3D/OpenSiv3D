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
# include <memory>
# include "Fwd.hpp"
# include "FileSystem.hpp"
# include "CharacterEncoding.hpp"

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
		TextWriter(const FilePath& path, CharacterEncoding encoding)
			: TextWriter()
		{
			open(path, OpenMode::Trunc, encoding);
		}

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
		explicit TextWriter(const FilePath& path, OpenMode openMode = OpenMode::Trunc, CharacterEncoding encoding = CharacterEncoding::Default)
			: TextWriter()
		{
			open(path, openMode, encoding);
		}

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
		bool open(const FilePath& path, CharacterEncoding encoding)
		{
			return open(path, OpenMode::Trunc, encoding);
		}

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
		bool open(const FilePath& path, OpenMode openMode = OpenMode::Trunc, CharacterEncoding encoding = CharacterEncoding::Default);

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
		void write(StringView str);

		/// <summary>
		/// ファイルに文字を書き込みます。
		/// </summary>
		/// <param name="ch">
		/// 書き込む文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void write(wchar ch)
		{
			write(StringView(&ch, 1));
		}

		void write(char32_t ch)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			const auto c = CharacterSet::GetUTF16CodePoint(ch);

			if (!c[1])
			{
				const wchar value = c[0];
				write(StringView(&value, 1));
			}
			else
			{
				const wchar values[2] = { c[0], c[1] };
				write(StringView(values, 2));
			}

		# else

			write(StringView(static_cast<const wchar*>(static_cast<const void*>(&ch)), 1));

		# endif
		}

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
		void write(const String& str)
		{
			write(StringView(str));
		}

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
		void write(const wchar* const str)
		{
			write(StringView(str));
		}

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
		/// ファイルに文字列を書き込み、改行します。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeln(const StringView str)
		{
			write(str);

			write(S3DSTR("\r\n"));
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
		void writeln(wchar ch)
		{
			write(ch);

			write(S3DSTR("\r\n"));
		}

		void writeln(char32_t ch)
		{
			write(ch);

			write(S3DSTR("\r\n"));
		}

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
		void writeln(const String& str)
		{
			write(str);

			write(S3DSTR("\r\n"));
		}

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
		void writeln(const wchar* const str)
		{
			write(str);

			write(S3DSTR("\r\n"));
		}

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
		/// ファイルに UTF-8 文字列を書き込みます。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeUTF8(CStringView str);

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		const FilePath& path() const;
	};
}
