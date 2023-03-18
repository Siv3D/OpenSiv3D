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

# include "TextReaderDetail.hpp"
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Endian.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/UnicodeConverter.hpp>

namespace s3d
{
	TextReader::TextReaderDetail::TextReaderDetail()
	{
		// do nothing
	}

	TextReader::TextReaderDetail::~TextReaderDetail()
	{
		close();
	}

	bool TextReader::TextReaderDetail::open(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		if (m_info.isOpen)
		{
			close();
		}

		std::unique_ptr<IReader> tmpReader = std::make_unique<BinaryReader>(path);

		if (not tmpReader->isOpen())
		{
			return false;
		}

		m_reader = std::move(tmpReader);

		m_info =
		{
			.fullPath	= FileSystem::FullPath(path),
			.encoding	= encoding ? *encoding : Unicode::GetTextEncoding(*m_reader),
			.isOpen		= true
		};

		if (const size_t bomSize = Unicode::GetBOMSize(m_info.encoding))
		{
			m_reader->skip(bomSize);
		}

		return true;
	}

	bool TextReader::TextReaderDetail::open(std::unique_ptr<IReader>&& reader, const Optional<TextEncoding>& encoding)
	{
		if (m_info.isOpen)
		{
			close();
		}

		if (not reader)
		{
			return false;
		}

		if (not reader->isOpen())
		{
			return false;
		}

		m_reader = std::move(reader);

		m_info =
		{
			.fullPath	= {},
			.encoding	= encoding ? *encoding : Unicode::GetTextEncoding(*m_reader),
			.isOpen		= true
		};

		if (const size_t bomSize = Unicode::GetBOMSize(m_info.encoding))
		{
			m_reader->skip(bomSize);
		}

		return true;
	}

	void TextReader::TextReaderDetail::close()
	{
		if (not m_info.isOpen)
		{
			return;
		}

		m_reader.reset();

		m_info = {};
	}

	bool TextReader::TextReaderDetail::isOpen() const noexcept
	{
		return m_info.isOpen;
	}

	Optional<char32> TextReader::TextReaderDetail::readChar()
	{
		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return none;
		}

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				return none;
			}

			if (codePoint == U'\0')
			{
				return none;
			}
			else if (codePoint != U'\r')
			{
				return codePoint;
			}
		}
	}

	Optional<String> TextReader::TextReaderDetail::readLine()
	{
		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return none;
		}

		String line;

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				if (line)
				{
					return line;
				}

				return none;
			}

			if ((codePoint == U'\n') || (codePoint == U'\0'))
			{
				return line;
			}
			else if (codePoint != U'\r')
			{
				line.push_back(codePoint);
			}
		}
	}

	Array<String> TextReader::TextReaderDetail::readLines()
	{
		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return{};
		}

		Array<String> lines;
		String line;

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				if (line)
				{
					lines.push_back(std::move(line));
				}

				return lines;
			}

			if ((codePoint == U'\n') || (codePoint == U'\0'))
			{
				lines.push_back(line);
				line.clear();
			}
			else if (codePoint != U'\r')
			{
				line.push_back(codePoint);
			}
		}
	}

	String TextReader::TextReaderDetail::readAll()
	{
		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return{};
		}

		String s;

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				return s;
			}

			if (codePoint == U'\0')
			{
				return s;
			}
			else if (codePoint != U'\r')
			{
				s.push_back(codePoint);
			}
		}
	}

	bool TextReader::TextReaderDetail::readChar(char32& ch)
	{
		ch = 0;

		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return false;
		}

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				return false;
			}

			if (codePoint == U'\0')
			{
				return false;
			}
			else if (codePoint != U'\r')
			{
				ch = codePoint;
				return true;
			}
		}
	}

	bool TextReader::TextReaderDetail::readLine(String& line)
	{
		line.clear();

		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return false;
		}

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				if (line)
				{
					return true;
				}

				return false;
			}

			if ((codePoint == U'\n') || (codePoint == U'\0'))
			{
				return true;
			}
			else if (codePoint != U'\r')
			{
				line.push_back(codePoint);
			}
		}
	}

	bool TextReader::TextReaderDetail::readLines(Array<String>& lines)
	{
		lines.clear();

		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return false;
		}

		String line;

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				if (line)
				{
					lines.push_back(std::move(line));
				}

				if (not lines)
				{
					return false;
				}

				return true;
			}

			if ((codePoint == U'\n') || (codePoint == U'\0'))
			{
				lines.push_back(line);
				line.clear();
			}
			else if (codePoint != U'\r')
			{
				line.push_back(codePoint);
			}
		}
	}

	bool TextReader::TextReaderDetail::readAll(String& s)
	{
		s.clear();

		if (not m_info.isOpen) SIV3D_UNLIKELY
		{
			return false;
		}

		for (;;)
		{
			char32 codePoint;

			if (not readCodePoint(codePoint))
			{
				if (not s)
				{
					return false;
				}

				return true;
			}

			if (codePoint == U'\0')
			{
				return true;
			}
			else if (codePoint != U'\r')
			{
				s.push_back(codePoint);
			}
		}
	}

	TextEncoding TextReader::TextReaderDetail::encoding() const noexcept
	{
		return m_info.encoding;
	}

	const FilePath& TextReader::TextReaderDetail::path() const noexcept
	{
		return m_info.fullPath;
	}

	bool TextReader::TextReaderDetail::readByte(uint8& c)
	{
		return m_reader->read(c);
	}

	bool TextReader::TextReaderDetail::readTwoBytes(uint16& c)
	{
		return m_reader->read(c);
	}

	bool TextReader::TextReaderDetail::readUTF8(char32& c)
	{
		uint8 cx;

		if (not readByte(cx))
		{
			return false;
		}

		UTF8toUTF32_Converter converter;

		if (converter.put(cx)) // 1
		{
			c = converter.get();
			return true;
		}

		if (not readByte(cx))
		{
			return false;
		}

		if (converter.put(cx)) // 2
		{
			c = converter.get();
			return true;
		}

		if (not readByte(cx))
		{
			return false;
		}

		if (converter.put(cx)) // 3
		{
			c = converter.get();
			return true;
		}

		if (not readByte(cx))
		{
			return false;
		}

		if (converter.put(cx)) // 4
		{
			c = converter.get();
			return true;
		}

		return false;
	}

	bool TextReader::TextReaderDetail::readUTF16LE(char32& c)
	{
		uint16 c0 = 0, c1 = 0;
		
		if (not readTwoBytes(c0))
		{
			return false;
		}

		if (Unicode::IsHighSurrogate(c0))
		{
			if (not readTwoBytes(c1))
			{
				return false;
			}

			c = ((((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000);
		}
		else
		{
			c = c0;
		}

		return true;
	}

	bool TextReader::TextReaderDetail::readUTF16BE(char32& c)
	{
		uint16 c0 = 0, c1 = 0;

		if (not readTwoBytes(c0))
		{
			return false;
		}

		c0 = SwapEndian(c0);

		if (Unicode::IsHighSurrogate(c0))
		{
			if (not readTwoBytes(c1))
			{
				return false;
			}

			c1 = SwapEndian(c1);

			c = ((((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000);
		}
		else
		{
			c = c0;
		}

		return true;
	}

	bool TextReader::TextReaderDetail::readCodePoint(char32& codePoint)
	{
		if (m_info.encoding == TextEncoding::UTF16LE)
		{
			return readUTF16LE(codePoint);
		}
		else if (m_info.encoding == TextEncoding::UTF16BE)
		{
			return readUTF16BE(codePoint);
		}
		else
		{
			return readUTF8(codePoint);
		}
	}
}
