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
# include <fstream>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	class TextReader::CTextReader
	{
	private:

		std::shared_ptr<IReader> m_reader;

	# if defined(SIV3D_TARGET_WINDOWS)
		
		std::wifstream m_ifs;

	# else

		std::ifstream m_ifs;
		
	# endif
		
		FilePath m_fullPath;

		int64 m_size = 0;

		CharacterEncoding m_encoding = CharacterEncoding::Default;

		Optional<FilePath> m_temporaryFile;

		bool m_opened = false;

		char32_t readCodePoint();

	public:

		CTextReader();

		~CTextReader();

		bool open(const FilePath& path, const Optional<CharacterEncoding>& encoding);

		bool open(const std::shared_ptr<IReader>& reader, const Optional<CharacterEncoding>& encoding);

		void close();

		bool isOpened() const;

		void readAll(String& out);

		void readLine(String& str);

		char32_t readChar();

		bool eof();

		const FilePath& path() const;

		CharacterEncoding encoding() const;
	};
}
