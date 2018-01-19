//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CTextWriter.hpp"

namespace s3d
{
	TextWriter::CTextWriter::CTextWriter()
	{

	}

	TextWriter::CTextWriter::~CTextWriter()
	{
		close();
	}

	bool TextWriter::CTextWriter::open(const FilePath& path, const OpenMode openMode, const TextEncoding encoding)
	{
		if (isOpened())
		{
			close();
		}

		if (openMode == OpenMode::Append)
		{
			m_encoding = Unicode::GetTextEncoding(path);

		# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

			if (m_encoding == TextEncoding::Unknown)
			{
				return false;
			}

		# endif
		}
		else
		{
			m_encoding = encoding;
		}

		FilePath fullPath;

		const FilePath parentFilePath = FileSystem::ParentPath(path, 0, &fullPath);

		if (!FileSystem::Exists(parentFilePath))
		{
			FileSystem::CreateDirectories(parentFilePath);
		}

		if (!m_binaryWriter.open(fullPath, openMode))
		{
			return false;
		}

		const bool addBOM = (m_encoding == TextEncoding::UTF8)
			|| (m_encoding == TextEncoding::UTF16LE)
			|| (m_encoding == TextEncoding::UTF16BE);

		if (!addBOM || m_binaryWriter.size() != 0)
		{
			return true;
		}

		switch (m_encoding)
		{
		case TextEncoding::UTF8:
			{
				const uint8 utf8BOM[] = { 0xEF, 0xBB, 0xBF };

				m_binaryWriter.write(utf8BOM);

				break;
			}
		case TextEncoding::UTF16LE:
			{
				const uint8 utf16LEBOM[] = { 0xFF, 0xFE };

				m_binaryWriter.write(utf16LEBOM);

				break;
			}
		case TextEncoding::UTF16BE:
			{
				const uint8 utf16BEBOM[] = { 0xFE, 0xFF };

				m_binaryWriter.write(utf16BEBOM);

				break;
			}
		default:
			break;
		}

		return true;
	}

	void TextWriter::CTextWriter::close()
	{
		if (!isOpened())
		{
			return;
		}

		m_binaryWriter.close();
	}

	bool TextWriter::CTextWriter::isOpened() const
	{
		return m_binaryWriter.isOpened();
	}

	void TextWriter::CTextWriter::clear()
	{
		if (!isOpened())
		{
			return;
		}

		const FilePath path = m_binaryWriter.path();

		open(path, OpenMode::Trunc, m_encoding);
	}

	void TextWriter::CTextWriter::write(const StringView view)
	{
		if (!isOpened())
		{
			return;
		}

		switch (m_encoding)
		{
		case TextEncoding::Unknown:
			{
				char previous = '\0';

				for (const char ch : Unicode::Narrow(view))
				{
					if (ch == '\n' && previous != '\r')
					{
						m_binaryWriter.write(u8"\r\n", sizeof(char) * 2);
					}
					else
					{
						m_binaryWriter.write(ch);
					}

					previous = ch;
				}

				break;
			}
		case TextEncoding::UTF8_NO_BOM:
		case TextEncoding::UTF8:
			{
				char8 previous = '\0';

				Unicode::Translator_UTF32toUTF8 translator;

				for (const char32 ch32 : view)
				{
					const size_t length = translator.put(ch32);

					if (length == 1)
					{
						const char8 ch = translator.get()[0];

						if (ch == '\n' && previous != '\r')
						{
							m_binaryWriter.write(u8"\r\n", 2);
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
		case TextEncoding::UTF16LE:
			{
				char16 previous = u'\0';

				Unicode::Translator_UTF32toUTF16 translator;

				for (const char32 ch32 : view)
				{
					const size_t length = translator.put(ch32);

					if (length == 1)
					{
						const char16 ch = translator.get()[0];

						if (ch == u'\n' && previous != u'\r')
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

				Unicode::Translator_UTF32toUTF16 translator;

				for (const char32 ch32 : view)
				{
					const size_t length = translator.put(ch32);

					if (length == 1)
					{
						const char16 ch = translator.get()[0];

						if (ch == u'\n' && previous != u'\r')
						{
							const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };
							m_binaryWriter.write(newLine);
						}
						else
						{
							m_binaryWriter.write(static_cast<char16>(((ch << 8) & 0xFF00) | ((ch >> 8) & 0xFF)));

							previous = ch;
						}
					}
					else
					{
						const char16 chars[2] =
						{
							static_cast<char16>(((translator.get()[0] << 8) & 0xFF00) | ((translator.get()[0] >> 8) & 0xFF)),
							static_cast<char16>(((translator.get()[1] << 8) & 0xFF00) | ((translator.get()[1] >> 8) & 0xFF))
						};

						m_binaryWriter.write(chars);

						previous = '\0';
					}
				}

				break;
			}
		}
	}

	void TextWriter::CTextWriter::writeNewLine()
	{
		if (!isOpened())
		{
			return;
		}

		switch (m_encoding)
		{
		case TextEncoding::Unknown:
		case TextEncoding::UTF8_NO_BOM:
		case TextEncoding::UTF8:
			{
				m_binaryWriter.write(u8"\r\n", 2);
				break;
			}
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
		}
	}

	void TextWriter::CTextWriter::writeUTF8(const std::string_view view)
	{
		if (!isOpened())
		{
			return;
		}

		switch (m_encoding)
		{
		case TextEncoding::Unknown:
		case TextEncoding::UTF8_NO_BOM:
		case TextEncoding::UTF8:
			{
				char previous = '\0';

				for (const char8 ch : view)
				{
					if (ch == '\n' && previous != '\r')
					{
						m_binaryWriter.write(u8"\r\n", sizeof(char) * 2);
					}
					else
					{
						m_binaryWriter.write(ch);
					}

					previous = ch;
				}

				break;
			}
		case TextEncoding::UTF16LE:
			{
				char16_t previous = '\0';

				for (const char16_t ch : Unicode::UTF8ToUTF16(view))
				{
					if (ch == '\n' && previous != '\r')
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

				for (const char16_t ch : Unicode::UTF8ToUTF16(view))
				{
					if (ch == '\n' && previous != '\r')
					{
						const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };

						m_binaryWriter.write(newLine);
					}
					else
					{
						m_binaryWriter.write(static_cast<char16>(((ch << 8) & 0xFF00) | ((ch >> 8) & 0xFF)));
					}

					previous = ch;
				}

				break;
			}
		}
	}

	const FilePath& TextWriter::CTextWriter::path() const
	{
		return m_binaryWriter.path();
	}
}
