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
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	class TextWriter::CTextWriter
	{
	private:

		BinaryWriter m_binaryWriter;

		TextEncoding m_textEncoding = TextEncoding::Default;

		bool m_writeBOM = true;

	public:

		CTextWriter();

		~CTextWriter();

		bool open(const FilePath& path, OpenMode openMode, TextEncoding encoding, bool writeBOM);

		void close();

		bool isOpened() const;

		void clear();

		void write(StringView str);

		void writeUTF8(UTF8StringView str);

		const FilePath& path() const;
	};
}
