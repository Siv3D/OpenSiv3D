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

	bool TextReader::open(const FilePath& path, const Optional<CharacterEncoding>& encoding)
	{
		return pImpl->open(path, encoding);
	}

	bool TextReader::open(const std::shared_ptr<IReader>& reader, const Optional<CharacterEncoding>& encoding)
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

	Optional<char32_t> TextReader::readChar()
	{
		if (pImpl->eof())
		{
			return none;
		}

		const char32_t ch = pImpl->readChar();

		return ch ? Optional<char32_t>{ ch } : none;
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

	bool TextReader::readChar(char32_t& ch)
	{
		if (pImpl->eof())
		{
			return false;
		}

		ch = pImpl->readChar();

		return ch != L'\0';
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

	CharacterEncoding TextReader::encoding() const
	{
		return pImpl->encoding();
	}
}
