//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextReader.hpp>
# include <Siv3D/TextReader/TextReaderDetail.hpp>

namespace s3d
{
	TextReader::TextReader()
		: pImpl{ std::make_shared<TextReaderDetail>() }
	{

	}

	TextReader::TextReader(const FilePathView path, const Optional<TextEncoding>& encoding)
		: TextReader{}
	{
		open(path, encoding);
	}

	TextReader::TextReader(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
		: TextReader{}
	{
		open(std::move(reader), encoding);
	}

	bool TextReader::open(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		return pImpl->open(path, encoding);
	}

	bool TextReader::open(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
	{
		return pImpl->open(std::move(reader), encoding);
	}

	void TextReader::close()
	{
		pImpl->close();
	}

	bool TextReader::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	TextReader::operator bool() const noexcept
	{
		return pImpl->isOpen();
	}

	Optional<char32> TextReader::readChar()
	{
		return pImpl->readChar();
	}

	Optional<String> TextReader::readLine()
	{
		return pImpl->readLine();
	}

	Array<String> TextReader::readLines()
	{
		return pImpl->readLines();
	}

	String TextReader::readAll()
	{
		return pImpl->readAll();
	}

	bool TextReader::readChar(char32& ch)
	{
		return pImpl->readChar(ch);
	}

	bool TextReader::readLine(String& line)
	{
		return pImpl->readLine(line);
	}

	bool TextReader::readLines(Array<String>& lines)
	{
		return pImpl->readLines(lines);
	}

	bool TextReader::readAll(String& s)
	{
		return pImpl->readAll(s);
	}

	TextEncoding TextReader::encoding() const noexcept
	{
		return pImpl->encoding();
	}

	const FilePath& TextReader::path() const noexcept
	{
		return pImpl->path();
	}
}
