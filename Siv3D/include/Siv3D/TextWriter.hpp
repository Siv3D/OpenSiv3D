﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "String.hpp"
# include "TextEncoding.hpp"
# include "OpenMode.hpp"
# include "Formatter.hpp"
# include "Format.hpp"

namespace s3d
{
	class TextWriter;

	namespace detail
	{
		class TextWriterBuffer
		{
		private:

			TextWriter& m_writer;

			bool m_isLast = false;

		public:

			std::unique_ptr<FormatData> formatData;

			TextWriterBuffer(TextWriter& writer);

			TextWriterBuffer(TextWriterBuffer&& other) noexcept;

			~TextWriterBuffer();

			template <class Type>
			TextWriterBuffer& operator <<(const Type& value);
		};
	}

	/// @brief 書き込み用テキストファイル
	class TextWriter
	{
	private:

		class TextWriterDetail;

		std::shared_ptr<TextWriterDetail> pImpl;

	public:

		SIV3D_NODISCARD_CXX20
		TextWriter();

		TextWriter(FilePathView path, TextEncoding encoding);

		explicit TextWriter(FilePathView path, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::UTF8_WITH_BOM);
	
		bool open(FilePathView path, TextEncoding encoding);

		bool open(FilePathView path, OpenMode openMode = OpenMode::Trunc, TextEncoding encoding = TextEncoding::UTF8_WITH_BOM);
	
		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		void clear();

		void write(char ch) = delete;

		void write(char32 ch);

		void write(const char32* s);

		void write(StringView s);

		void write(const String& s);

		SIV3D_CONCEPT_FORMATTABLE_ARGS
		void write(const Args& ... args);

		void writeln(char ch) = delete;

		void writeln(char32 ch);

		void writeln(const char32* s);

		void writeln(StringView s);

		void writeln(const String& s);

		SIV3D_CONCEPT_FORMATTABLE_ARGS
		void writeln(const Args& ... args);

		void writeUTF8(std::string_view s);

		void writelnUTF8(std::string_view s);

		SIV3D_CONCEPT_FORMATTABLE
		detail::TextWriterBuffer operator <<(const Formattable& value);

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}

# include "detail/TextWriter.ipp"
