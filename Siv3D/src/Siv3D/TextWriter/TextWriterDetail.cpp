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

# include "TextWriterDetail.hpp"
# include <Siv3D/Endian.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/UnicodeConverter.hpp>

namespace s3d
{
	TextWriter::TextWriterDetail::TextWriterDetail()
	{
		// do nothing
	}

	TextWriter::TextWriterDetail::~TextWriterDetail()
	{
		close();
	}

	bool TextWriter::TextWriterDetail::open(const FilePathView path, const OpenMode openMode, const TextEncoding encoding)
	{
		close();

		if (openMode == OpenMode::Append)
		{
			m_encoding = Unicode::GetTextEncoding(path);

			if (m_encoding == TextEncoding::Unknown)
			{
				return false;
			}
		}
		else
		{
			m_encoding = encoding;
		}

		if (not m_binaryWriter.open(path, openMode))
		{
			return false;
		}

		if (m_binaryWriter.size() > 0)
		{
			return true;
		}

		switch (m_encoding)
		{
		case TextEncoding::UTF8_WITH_BOM:
			{
				constexpr uint8 utf8BOM[] = { 0xEF, 0xBB, 0xBF };
				m_binaryWriter.write(utf8BOM);
				break;
			}
		case TextEncoding::UTF16LE:
			{
				constexpr uint8 utf16LEBOM[] = { 0xFF, 0xFE };
				m_binaryWriter.write(utf16LEBOM);
				break;
			}
		case TextEncoding::UTF16BE:
			{
				constexpr uint8 utf16BEBOM[] = { 0xFE, 0xFF };
				m_binaryWriter.write(utf16BEBOM);
				break;
			}
		default:
			break;
		}

		return true;
	}

	void TextWriter::TextWriterDetail::close()
	{
		m_binaryWriter.close();

		m_encoding = TextEncoding::Default;
	}

	bool TextWriter::TextWriterDetail::isOpen() const noexcept
	{
		return m_binaryWriter.isOpen();
	}

	void TextWriter::TextWriterDetail::clear()
	{
		if (not isOpen())
		{
			return;
		}

		const FilePath path = m_binaryWriter.path();

		open(path, OpenMode::Trunc, m_encoding);
	}

	void TextWriter::TextWriterDetail::write(const StringView s)
	{
		switch (m_encoding)
		{
		case TextEncoding::UTF16LE:
			{
				char16 previous = u'\0';

				UTF32toUTF16_Converter translator;

				for (const char32 ch32 : s)
				{
					const size_t length = translator.put(ch32);

					if (length == 1)
					{
						const char16 ch = translator.get()[0];

						if ((ch == u'\n') && (previous != u'\r'))
						{
							m_binaryWriter.write(u"\r\n", 4);
						}
						else
						{
							m_binaryWriter.write(ch);
							previous = ch;
						}
					}
					else
					{
						m_binaryWriter.write(translator.get());
						previous = '\0';
					}
				}

				break;
			}
		case TextEncoding::UTF16BE:
			{
				char16 previous = u'\0';

				UTF32toUTF16_Converter translator;

				for (const char32 ch32 : s)
				{
					const size_t length = translator.put(ch32);

					if (length == 1)
					{
						const char16 ch = translator.get()[0];

						if ((ch == u'\n') && (previous != u'\r'))
						{
							const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };
							m_binaryWriter.write(newLine);
						}
						else
						{
							m_binaryWriter.write(SwapEndian(static_cast<uint16>(ch)));
							previous = ch;
						}
					}
					else
					{
						const uint16 chars[2] =
						{
							SwapEndian(static_cast<uint16>(translator.get()[0])),
							SwapEndian(static_cast<uint16>(translator.get()[1]))
						};

						m_binaryWriter.write(chars);
						previous = '\0';
					}
				}

				break;
			}
		default:
			{
				char8 previous = '\0';

				UTF32toUTF8_Converter translator;

				for (const char32 ch32 : s)
				{
					const size_t length = translator.put(ch32);

					if (length == 1)
					{
						const char8 ch = translator.get()[0];

						if ((ch == '\n') && (previous != '\r'))
						{
							m_binaryWriter.write("\r\n", 2);
						}
						else
						{
							m_binaryWriter.write(ch);
							previous = ch;
						}
					}
					else
					{
						m_binaryWriter.write(translator.get().data(), length);
						previous = '\0';
					}
				}

				break;
			}
		}
	}

	void TextWriter::TextWriterDetail::writeNewLine()
	{
		switch (m_encoding)
		{
		case TextEncoding::UTF16LE:
			{
				m_binaryWriter.write(u"\r\n", 4);
				break;
			}
		case TextEncoding::UTF16BE:
			{
				const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };
				m_binaryWriter.write(newLine);
				break;
			}
		default:
			{
				m_binaryWriter.write("\r\n", 2);
				break;
			}
		}
	}

	void TextWriter::TextWriterDetail::writeUTF8(const std::string_view s)
	{
		switch (m_encoding)
		{
		case TextEncoding::UTF16LE:
			{
				char16_t previous = '\0';

				for (const char16_t ch : Unicode::UTF8ToUTF16(s))
				{
					if ((ch == '\n') && (previous != '\r'))
					{
						const uint8 newLine[] = { 0x0D, 0x00, 0x0A, 0x00 };
						m_binaryWriter.write(newLine);
					}
					else
					{
						m_binaryWriter.write(ch);
					}

					previous = ch;
				}

				break;
			}
		case TextEncoding::UTF16BE:
			{
				char16_t previous = '\0';

				for (const char16_t ch : Unicode::UTF8ToUTF16(s))
				{
					if ((ch == '\n') && (previous != '\r'))
					{
						const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };
						m_binaryWriter.write(newLine);
					}
					else
					{
						m_binaryWriter.write(SwapEndian(static_cast<uint16>(ch)));
					}

					previous = ch;
				}

				break;
			}
		default:
			{
				char previous = '\0';

				for (const char8 ch : s)
				{
					if ((ch == '\n') && (previous != '\r'))
					{
						m_binaryWriter.write("\r\n", 2);
					}
					else
					{
						m_binaryWriter.write(ch);
					}

					previous = ch;
				}

				break;
			}
		}
	}

	TextEncoding TextWriter::TextWriterDetail::encoding() const noexcept
	{
		return m_encoding;
	}

	const FilePath& TextWriter::TextWriterDetail::path() const noexcept
	{
		return m_binaryWriter.path();
	}
}
