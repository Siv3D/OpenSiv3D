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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/EngineLog.hpp>
# include "TextReaderDetail.hpp"

namespace s3d
{
	TextReader::TextReaderDetail::TextReaderDetail()
	{

	}

	TextReader::TextReaderDetail::~TextReaderDetail()
	{
		close();
	}

	void TextReader::TextReaderDetail::close()
	{
		if (!m_opened)
		{
			return;
		}

		if (m_reader)
		{
			m_reader.reset();
		}
		else
		{
			m_ifs.close();
		}

		if (m_temporaryFile)
		{
			FileSystem::Remove(m_temporaryFile.value());

			m_temporaryFile.reset();
		}

		m_encoding = TextEncoding::Default;

		m_size = 0;

		m_fullPath.clear();

		m_opened = false;
	}

	bool TextReader::TextReaderDetail::isOpen() const
	{
		return m_opened;
	}

	char32 TextReader::TextReaderDetail::readChar()
	{
		for (;;)
		{
			const auto c = readCodePoint();

			if (c != U'\r')
			{
				return c;
			}
		}
	}

	bool TextReader::TextReaderDetail::eof()
	{
		if (!m_opened)
		{
			return true;
		}

		if (m_reader)
		{
			return m_reader->getPos() == m_size;
		}
		else
		{
			return !m_ifs || m_ifs.tellg() == m_size;
		}
	}

	const FilePath& TextReader::TextReaderDetail::path() const
	{
		return m_fullPath;
	}

	TextEncoding TextReader::TextReaderDetail::encoding() const
	{
		return m_encoding;
	}

	char32 TextReader::TextReaderDetail::readCodePoint()
	{
		if (m_encoding == TextEncoding::Unknown)
		{
			char8 ch = '\0';

			m_ifs.get(ch);

			return ch; // [Siv3D TODO]
		}
		
		if (m_reader->getPos() == m_reader->size())
		{
			return U'\0';
		}

		if (m_encoding == TextEncoding::UTF16LE)
		{
			char16 c0 = 0, c1 = 0;
			m_reader->read(c0);

			if (Unicode::IsHighSurrogate(c0))
			{
				m_reader->read(c1);
				return (((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000;
			}

			return c0;
		}
		else if (m_encoding == TextEncoding::UTF16BE)
		{
			char16 c0 = 0, c1 = 0;
			m_reader->read(c0);
			c0 = ((c0 << 8) & 0xff00) | ((c0 >> 8) & 0xFF);

			if (Unicode::IsHighSurrogate(c0))
			{
				m_reader->read(c1);
				c1 = ((c1 << 8) & 0xff00) | ((c1 >> 8) & 0xFF);

				return (((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000;
			}

			return c0;
		}
		else // UTF-8
		{
			char8 buffer[4] = {};

			const size_t readSize = static_cast<size_t>(m_reader->lookahead(buffer, sizeof(buffer)));

			Unicode::Translator_UTF8toUTF32 translator;

			size_t i = 0;

			for (; i < readSize; ++i)
			{
				if (translator.put(buffer[i]))
				{
					break;
				}
			}

			if (i != readSize)
			{
				m_reader->skip(i + 1);
				return translator.get();
			}
			else
			{
				m_reader->skip(readSize);
				return 0xFFFD;
			}
		}
	}
}
