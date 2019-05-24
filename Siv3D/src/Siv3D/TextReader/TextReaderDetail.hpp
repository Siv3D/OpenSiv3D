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
# include <fstream>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	class TextReader::TextReaderDetail
	{
	private:

		std::shared_ptr<IReader> m_reader;

		std::ifstream m_ifs;

		FilePath m_fullPath;

		int64 m_size = 0;

		TextEncoding m_encoding = TextEncoding::Default;

		Optional<FilePath> m_temporaryFile;

		bool m_opened = false;

		char32_t readCodePoint();

	public:

		TextReaderDetail();

		~TextReaderDetail();

		bool open(const FilePath& path, const Optional<TextEncoding>& encoding);

		bool open(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding);

		void close();

		bool isOpened() const;

		void readAll(String& out);

		void readLine(String& text);

		char32 readChar();

		bool eof();

		const FilePath& path() const;

		TextEncoding encoding() const;
	};
}
