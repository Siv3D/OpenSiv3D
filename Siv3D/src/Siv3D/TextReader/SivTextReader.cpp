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

# include <Siv3D/TextReader.hpp>
# include "CTextReader.hpp"

namespace s3d
{
	TextReader::TextReader()
		: pImpl(std::make_shared<CTextReader>())
	{

	}

	TextReader::~TextReader()
	{

	}

	bool TextReader::open(const FilePath& path, const Optional<TextEncoding>& encoding)
	{
		return pImpl->open(path, encoding);
	}

	bool TextReader::open(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding)
	{
		return pImpl->open(reader, encoding);
	}

	void TextReader::close()
	{
		pImpl->close();
	}

	bool TextReader::isOpened() const
	{
		return pImpl->isOpened();
	}

	Optional<char32> TextReader::readChar()
	{
		if (pImpl->eof())
		{
			return none;
		}

		if (const char32 ch = pImpl->readChar())
		{
			return ch;
		}

		return none;
	}

	Optional<String> TextReader::readLine()
	{
		if (pImpl->eof())
		{
			return none;
		}

		String line;

		pImpl->readLine(line);

		return line;
	}

	String TextReader::readAll()
	{
		String result;

		pImpl->readAll(result);

		return result;
	}

	bool TextReader::readChar(char32& ch)
	{
		if (pImpl->eof())
		{
			return false;
		}

		ch = pImpl->readChar();

		return ch != U'\0';
	}

	bool TextReader::readLine(String& str)
	{
		if (pImpl->eof())
		{
			return false;
		}

		str.clear();

		pImpl->readLine(str);

		return true;
	}

	void TextReader::readAll(String& str)
	{
		if (!isOpened())
		{
			return;
		}

		pImpl->readAll(str);
	}

	const FilePath& TextReader::path() const
	{
		return pImpl->path();
	}

	TextEncoding TextReader::encoding() const
	{
		return pImpl->encoding();
	}
}
