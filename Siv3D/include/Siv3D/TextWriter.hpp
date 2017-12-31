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
# include <memory>
# include "Fwd.hpp"
# include "FileSystem.hpp"
# include "TextEncoding.hpp"

namespace s3d
{
	namespace detail
	{
		class TextWriterBuffer
		{
		private:

			TextWriter& m_writer;

			bool m_isLast = false;

		public:

			std::unique_ptr<FormatData> formatData;

			TextWriterBuffer(TextWriter& writer)
				: m_writer(writer)
				, m_isLast(true)
				, formatData(std::make_unique<FormatData>()) {}

			TextWriterBuffer(TextWriterBuffer&& other)
				: m_writer(other.m_writer)
				, m_isLast(true)
				, formatData(std::move(other.formatData))
			{
				other.m_isLast = false;
			}

			~TextWriterBuffer();

			template <class Type>
			TextWriterBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};
	}

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
		TextWriter(const FilePath& path, TextEncoding encoding)
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
		explicit TextWriter(const FilePath& path, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::Default)
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
		bool open(const FilePath& path, TextEncoding encoding)
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
		bool open(const FilePath& path, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::Default);

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
		[[nodiscard]] bool isOpened() const;

		/// <summary>
		/// テキストファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] explicit operator bool() const { return isOpened(); }

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
		void write(char32 ch)
		{
			write(StringView(&ch, 1));
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
		void write(const char32* const str)
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
		void writeln(const StringView view);

		/// <summary>
		/// ファイルに文字を書き込み、改行します。
		/// </summary>
		/// <param name="ch">
		/// 書き込む文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeln(char32 ch);

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
		void writeln(const char32* const str);

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
		/// <param name="view">
		/// 書き込む文字列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeUTF8(std::string_view view);

		void writelnUTF8(std::string_view view);

		template <class Type>
		detail::TextWriterBuffer operator <<(const Type& value)
		{
			detail::TextWriterBuffer buf(*this);

			Formatter(*buf.formatData, value);

			return buf;
		}

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		[[nodiscard]] const FilePath& path() const;
	};

	namespace detail
	{
		inline TextWriterBuffer::~TextWriterBuffer()
		{
			if (m_isLast)
			{
				m_writer.writeln(formatData->string);
			}
		}
	}
}
