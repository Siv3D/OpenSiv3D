//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/TextReader.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	class TextReader::CTextReader
	{
	private:

		std::shared_ptr<IReader> m_reader;

		FilePath m_fullPath;

		int64 m_size = 0;

		int32 m_bomSize = 0;

		CharacterEncoding m_encoding = CharacterEncoding::Default;

		bool m_opened = false;

	public:

		CTextReader();

		~CTextReader();

		bool open(const FilePath& path, const Optional<CharacterEncoding>& encoding);

		bool open(const std::shared_ptr<IReader>& reader, const Optional<CharacterEncoding>& encoding);

		void close();

		bool isOpened() const;

		bool readAll(String& out);

		void readLine(String& str);

		wchar readChar();

		bool eof();

		const FilePath& path() const;

		CharacterEncoding encoding() const;
	};
}
