//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextWriter.hpp>
# include "CTextWriter.hpp"

namespace s3d
{
	TextWriter::TextWriter()
		: pImpl(std::make_shared<CTextWriter>())
	{

	}

	TextWriter::~TextWriter()
	{

	}

	TextWriter::TextWriter(const FilePath& path, const TextEncoding encoding, const bool writeBOM)
		: TextWriter()
	{
		open(path, OpenMode::Trunc, encoding, writeBOM);
	}

	TextWriter::TextWriter(const FilePath& path, const OpenMode openMode, const TextEncoding encoding, const bool writeBOM)
		: TextWriter()
	{
		open(path, openMode, encoding, writeBOM);
	}

	bool TextWriter::open(const FilePath& path, const TextEncoding encoding, const bool writeBOM)
	{
		return open(path, OpenMode::Trunc, encoding, writeBOM);
	}

	bool TextWriter::open(const FilePath& path, const OpenMode openMode, const TextEncoding encoding, const bool writeBOM)
	{
		return pImpl->open(path, openMode, encoding, writeBOM);
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

	void TextWriter::write(const wchar_t ch)
	{
		pImpl->write(StringView(&ch, 1));
	}

	void TextWriter::write(const String& str)
	{
		pImpl->write(str);
	}

	void TextWriter::write(const wchar* const str)
	{
		pImpl->write(str);
	}

	void TextWriter::write(const wchar* const str, const size_t length)
	{
		pImpl->write(StringView(str, length));
	}

	void TextWriter::writeln(const wchar ch)
	{
		pImpl->write(StringView(&ch, 1));

		pImpl->write(L"\r\n");
	}

	void TextWriter::writeln(const String& str)
	{
		pImpl->write(str);

		pImpl->write(L"\r\n");
	}

	void TextWriter::writeln(const wchar* const str)
	{
		pImpl->write(str);

		pImpl->write(L"\r\n");
	}

	void TextWriter::writeln(const wchar* const str, const size_t length)
	{
		pImpl->write(StringView(str, length));

		pImpl->write(L"\r\n");
	}

	const FilePath& TextWriter::path() const
	{
		return pImpl->path();
	}
}
