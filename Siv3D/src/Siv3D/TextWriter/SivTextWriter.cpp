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

# include <Siv3D/TextWriter.hpp>
# include "TextWriterDetail.hpp"

namespace s3d
{
	namespace detail
	{
		TextWriterBuffer::TextWriterBuffer(TextWriter& writer)
			: m_writer(writer)
			, m_isLast(true)
			, formatData(std::make_unique<FormatData>())
		{
		
		}

		TextWriterBuffer::TextWriterBuffer(TextWriterBuffer&& other)
			: m_writer(other.m_writer)
			, m_isLast(true)
			, formatData(std::move(other.formatData))
		{
			other.m_isLast = false;
		}

		TextWriterBuffer::~TextWriterBuffer()
		{
			if (m_isLast)
			{
				m_writer.writeln(formatData->string);
			}
		}
	}

	TextWriter::TextWriter()
		: pImpl(std::make_shared<TextWriterDetail>())
	{

	}

	TextWriter::~TextWriter()
	{

	}

	TextWriter::TextWriter(const FilePath& path, const TextEncoding encoding)
		: TextWriter()
	{
		open(path, OpenMode::Trunc, encoding);
	}

	TextWriter::TextWriter(const FilePath& path, const OpenMode openMode, const TextEncoding encoding)
		: TextWriter()
	{
		open(path, openMode, encoding);
	}

	bool TextWriter::open(const FilePath& path, const TextEncoding encoding)
	{
		return open(path, OpenMode::Trunc, encoding);
	}

	bool TextWriter::open(const FilePath& path, const OpenMode openMode, const TextEncoding encoding)
	{
		return pImpl->open(path, openMode, encoding);
	}

	void TextWriter::close()
	{
		pImpl->close();
	}

	bool TextWriter::isOpened() const
	{
		return pImpl->isOpened();
	}

	void TextWriter::clear()
	{
		pImpl->clear();
	}

	void TextWriter::write(const StringView view)
	{
		pImpl->write(view);
	}

	void TextWriter::writeln(const StringView view)
	{
		pImpl->write(view);

		pImpl->writeNewLine();
	}

	void TextWriter::writeln(const char32 ch)
	{
		pImpl->write(StringView(&ch, 1));

		pImpl->writeNewLine();
	}

	void TextWriter::writeln(const String& str)
	{
		pImpl->write(str);

		pImpl->writeNewLine();
	}

	void TextWriter::writeln(const char32* const str)
	{
		pImpl->write(str);

		pImpl->writeNewLine();
	}

	void TextWriter::writeUTF8(const std::string_view view)
	{
		pImpl->writeUTF8(view);
	}

	void TextWriter::writelnUTF8(const std::string_view view)
	{
		pImpl->writeUTF8(view);

		pImpl->writeNewLine();
	}

	const FilePath& TextWriter::path() const
	{
		return pImpl->path();
	}
}
