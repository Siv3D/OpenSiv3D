//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
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

		bool open(FilePathView path, OpenMode openMode, TextEncoding encoding);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		void clear();

		void write(StringView s);

		void writeNewLine();

		void writeUTF8(std::string_view s);

		[[nodiscard]]
		TextEncoding encoding() const noexcept;

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}
