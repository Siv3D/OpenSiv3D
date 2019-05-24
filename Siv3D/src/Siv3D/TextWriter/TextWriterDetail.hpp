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
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	class TextWriter::TextWriterDetail
	{
	private:

		BinaryWriter m_binaryWriter;

		TextEncoding m_encoding = TextEncoding::Default;

	public:

		TextWriterDetail();

		~TextWriterDetail();

		bool open(const FilePath& path, OpenMode openMode, TextEncoding encoding);

		void close();

		bool isOpened() const;

		void clear();

		void write(StringView view);

		void writeNewLine();

		void writeUTF8(std::string_view view);

		const FilePath& path() const;
	};
}
