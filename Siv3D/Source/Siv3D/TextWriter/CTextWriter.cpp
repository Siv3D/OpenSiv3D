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

	bool TextWriter::CTextWriter::open(const FilePath& path, const OpenMode openMode, const CharacterEncoding encoding)
	{
		if (isOpened())
		{
			close();
		}

		if (openMode == OpenMode::Append)
		{
			m_encoding = CharacterSet::GetEncoding(path);
            
            # if defined(SIV3D_TARGET_MACOS)
            
                if (m_encoding == CharacterEncoding::Unknown)
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

		const bool addBOM = (m_encoding == CharacterEncoding::UTF8_BOM)
			|| (m_encoding == CharacterEncoding::UTF16LE_BOM)
			|| (m_encoding == CharacterEncoding::UTF16BE_BOM);

		if (!addBOM || m_binaryWriter.size() != 0)
		{
			return true;
		}

		switch (m_encoding)
		{
		case CharacterEncoding::UTF8_BOM:
			{
				const uint8 utf8BOM[] = { 0xEF, 0xBB, 0xBF };

				m_binaryWriter.write(utf8BOM);

				break;
			}
		case CharacterEncoding::UTF16LE_BOM:
			{
				const uint8 utf16LEBOM[] = { 0xFF, 0xFE };

				m_binaryWriter.write(utf16LEBOM);

				break;
			}
		case CharacterEncoding::UTF16BE_BOM:
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

	void TextWriter::CTextWriter::write(const StringView str)
	{
		if (!isOpened())
		{
			return;
		}

		switch (m_encoding)
		{
		case CharacterEncoding::Unknown:
			{
				char previous = '\0';

				for (const char ch : CharacterSet::Narrow(str))
				{
					if (ch == '\n' && previous != '\r')
					{
						m_binaryWriter.write("\r\n", sizeof(char) * 2);
					}
					else
					{
						m_binaryWriter.write(ch);
					}

					previous = ch;
				}

				break;
			}
		case CharacterEncoding::UTF8:
		case CharacterEncoding::UTF8_BOM:
			{
				char previous = '\0';

				for (const char ch : CharacterSet::ToUTF8(str))
				{
					if (ch == '\n' && previous != '\r')
					{
						m_binaryWriter.write("\r\n", sizeof(char) * 2);
					}
					else
					{
						m_binaryWriter.write(ch);
					}

					previous = ch;
				}

				break;
			}
		case CharacterEncoding::UTF16LE_BOM:
			{
				# if defined(SIV3D_TARGET_WINDOWS)

					char16_t previous = '\0';

					for (const char16_t ch : str)
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

				# elif defined(SIV3D_TARGET_MACOS)
				
					char16_t previous = '\0';

					for (const char16_t ch : CharacterSet::ToUTF16(str))
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

				# endif

				break;
			}
		case CharacterEncoding::UTF16BE_BOM:
			{
				# if defined(SIV3D_TARGET_WINDOWS)

					char16_t previous = '\0';

					for (const char16_t ch : str)
					{
						if (ch == '\n' && previous != '\r')
						{
							const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };

							m_binaryWriter.write(newLine);
						}
						else
						{
							m_binaryWriter.write(static_cast<char16_t>(((ch << 8) & 0xFF00) | ((ch >> 8) & 0xFF)));
						}

						previous = ch;
					}

				# elif defined(SIV3D_TARGET_MACOS)
				
					char16_t previous = '\0';

					for (const char16_t ch : CharacterSet::ToUTF16(str))
					{
						if (ch == '\n' && previous != '\r')
						{
							const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };

							m_binaryWriter.write(newLine);
						}
						else
						{
							m_binaryWriter.write(static_cast<char16_t>(((ch << 8) & 0xFF00) | ((ch >> 8) & 0xFF)));
						}

						previous = ch;
					}

				# endif

				break;
			}
		}
	}

	void TextWriter::CTextWriter::writeUTF8(const UTF8StringView str)
	{
		if (!isOpened())
		{
			return;
		}

		switch (m_encoding)
		{
		case CharacterEncoding::Unknown:
		case CharacterEncoding::UTF8:
		case CharacterEncoding::UTF8_BOM:
			{
				char previous = '\0';

				for (const char ch : str)
				{
					if (ch == '\n' && previous != '\r')
					{
						m_binaryWriter.write("\r\n", sizeof(char) * 2);
					}
					else
					{
						m_binaryWriter.write(ch);
					}

					previous = ch;
				}

				break;
			}
		case CharacterEncoding::UTF16LE_BOM:
			{
				char16_t previous = '\0';

				for (const char16_t ch : CharacterSet::UTF8ToUTF16(str))
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
		case CharacterEncoding::UTF16BE_BOM:
			{
				char16_t previous = '\0';

				for (const char16_t ch : CharacterSet::UTF8ToUTF16(str))
				{
					if (ch == '\n' && previous != '\r')
					{
						const uint8 newLine[] = { 0x00, 0x0D, 0x00, 0x0A };

						m_binaryWriter.write(newLine);
					}
					else
					{
						m_binaryWriter.write(static_cast<char16_t>(((ch << 8) & 0xFF00) | ((ch >> 8) & 0xFF)));
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
