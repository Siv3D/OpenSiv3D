//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextWriter.hpp>
# include <Siv3D/TextWriter/TextWriterDetail.hpp>

namespace s3d
{
	namespace detail
	{
		TextWriterBuffer::TextWriterBuffer(TextWriter& writer)
			: m_writer{ writer }
			, m_isLast{ true }
			, formatData{ std::make_unique<FormatData>() }
		{
			// do nothing
		}

		TextWriterBuffer::TextWriterBuffer(TextWriterBuffer&& other) noexcept
			: m_writer{ other.m_writer }
			, m_isLast{ true }
			, formatData{ std::move(other.formatData) }
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
		: pImpl{ std::make_shared<TextWriterDetail>() }
	{
		// do nothing
	}

	TextWriter::TextWriter(const FilePathView path, const TextEncoding encoding)
		: TextWriter{}
	{
		open(path, OpenMode::Trunc, encoding);
	}

	TextWriter::TextWriter(const FilePathView path, const OpenMode openMode, const TextEncoding encoding)
		: TextWriter{}
	{
		open(path, openMode, encoding);
	}

	bool TextWriter::open(const FilePathView path, const TextEncoding encoding)
	{
		return open(path, OpenMode::Trunc, encoding);
	}

	bool TextWriter::open(const FilePathView path, const OpenMode openMode, const TextEncoding encoding)
	{
		return pImpl->open(path, openMode, encoding);
	}

	void TextWriter::close()
	{
		pImpl->close();
	}

	bool TextWriter::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	void TextWriter::clear()
	{
		pImpl->clear();
	}

	void TextWriter::write(const StringView s)
	{
		pImpl->write(s);
	}

	void TextWriter::writeln(const StringView s)
	{
		pImpl->write(s);

		pImpl->writeNewLine();
	}

	void TextWriter::writeUTF8(const std::string_view s)
	{
		pImpl->writeUTF8(s);
	}

	void TextWriter::writelnUTF8(const std::string_view s)
	{
		pImpl->writeUTF8(s);

		pImpl->writeNewLine();
	}

	const FilePath& TextWriter::path() const noexcept
	{
		return pImpl->path();
	}
}
