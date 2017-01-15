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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/ByteArray.hpp>
# include "CTextReader.hpp"

namespace s3d
{
	namespace detail
	{
		static FilePath CreateTemporaryCopy(IReader& reader)
		{
			constexpr size_t bufferSize = 4096;

			const FilePath path = FileSystem::TempDirectoryPath();

			BinaryWriter writer(path);

			if (int64 sizeToRead = reader.size())
			{
				uint8* const buffer = static_cast<uint8*>(::malloc(bufferSize));

				while (sizeToRead)
				{
					const size_t readSize = reader.read(buffer, bufferSize);

					writer.write(buffer, readSize);

					sizeToRead -= readSize;
				}

				::free(buffer);
			}

			return path;
		}

		static void PushCodePoint(String& str, const char32_t codePoint)
		{
		# if defined(SIV3D_TARGET_WINDOWS)

			if (codePoint < 0x10000)
			{
				str.push_back(static_cast<wchar>(codePoint));
			}
			else if (codePoint < 0x110000)
			{
				const auto utf16 = CharacterSet::GetUTF16CodePoint(codePoint);
				str.push_back(utf16[0]);
				str.push_back(utf16[1]);
			}
			else
			{
				str.push_back(static_cast<wchar>(0xFFFD));
			}

		# else

			str.push_back(static_cast<wchar>(codePoint));

		# endif
		}
	}

	TextReader::CTextReader::CTextReader()
	{

	}

	TextReader::CTextReader::~CTextReader()
	{
		close();
	}

	bool TextReader::CTextReader::open(const FilePath& path, const Optional<CharacterEncoding>& encoding)
	{
		if (m_opened)
		{
			close();
		}

		std::shared_ptr<IReader> tmpIReader = std::make_shared<BinaryReader>(path);

		if (!tmpIReader->isOpened())
		{
			return false;
		}

		if (encoding)
		{
			m_encoding = encoding.value();
		}
		else
		{
			m_encoding = CharacterSet::GetEncoding(*tmpIReader);
		}

		if (m_encoding != CharacterEncoding::Unknown)
		{
			m_reader = tmpIReader;

			m_opened = m_reader->isOpened();

			if (const size_t bomSize = CharacterSet::GetBOMSize(m_encoding))
			{
				m_reader->skip(bomSize);
			}
		}
		else
		{
			tmpIReader->~IReader();

			m_wifReader.open(path.str());

			m_opened = m_wifReader.is_open();
		}

		if (!m_opened)
		{
			return false;
		}

		m_size = m_reader ? m_reader->size() : FileSystem::Size(path);

		m_fullPath = FileSystem::FullPath(path);

		return m_opened;
	}

	bool TextReader::CTextReader::open(const std::shared_ptr<IReader>& reader, const Optional<CharacterEncoding>& encoding)
	{
		if (!reader)
		{
			return false;
		}

		if (m_opened)
		{
			close();
		}

		if (encoding)
		{
			m_encoding = encoding.value();
		}
		else
		{
			m_encoding = CharacterSet::GetEncoding(*reader);
		}

		if (m_encoding != CharacterEncoding::Unknown)
		{
			m_reader = std::move(reader);

			m_opened = m_reader->isOpened();

			if (const size_t bomSize = CharacterSet::GetBOMSize(m_encoding))
			{
				m_reader->skip(bomSize);
			}
		}
		else
		{
			m_temporaryFile = detail::CreateTemporaryCopy(*reader);

			m_wifReader.open(m_temporaryFile->str());

			m_opened = m_wifReader.is_open();
		}

		m_size = m_reader ? m_reader->size() : reader->size();

		m_fullPath = L"(Archived File)";

		return m_opened;
	}

	void TextReader::CTextReader::close()
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
			m_wifReader.close();
		}

		if (m_temporaryFile)
		{
			FileSystem::Remove(m_temporaryFile.value());

			m_temporaryFile.reset();
		}

		m_encoding = CharacterEncoding::Default;

		m_size = 0;

		m_fullPath.clear();

		m_opened = false;
	}

	bool TextReader::CTextReader::isOpened() const
	{
		return m_opened;
	}

	void TextReader::CTextReader::readAll(String& out)
	{
		out.clear();

		if (!m_opened)
		{
			return;
		}

		if (m_reader)
		{
			const size_t bomSize = CharacterSet::GetBOMSize(m_encoding);

			Array<uint8> tmp(m_reader->size() - bomSize);
			
			if (tmp.empty())
			{
				return;
			}

			m_reader->read(tmp.data(), bomSize, tmp.size());

			ByteArray reader(std::move(tmp));

			const int64 size = reader.size();

			while (reader.getPos() < size)
			{
				char32_t codePoint = 0;

				if (m_encoding == CharacterEncoding::UTF16LE_BOM)
				{
					char16_t c0 = 0, c1 = 0;
					reader.read(c0);

					if (IsHighSurrogate(c0))
					{
						reader.read(c1);
						codePoint = (((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000;
					}
					else
					{
						codePoint = c0;
					}
				}
				else if (m_encoding == CharacterEncoding::UTF16BE_BOM)
				{
					char16_t c0 = 0, c1 = 0;
					reader.read(c0);
					c0 = ((c0 << 8) & 0xff00) | ((c0 >> 8) & 0xFF);

					if (IsHighSurrogate(c0))
					{
						reader.read(c1);
						c1 = ((c1 << 8) & 0xff00) | ((c1 >> 8) & 0xFF);

						codePoint = (((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000;
					}
					else
					{
						codePoint = c0;
					}
				}
				else // UTF8, UTF8_BOM
				{
					char buffer[6] = {};
					const size_t readSize = reader.lookahead(buffer, sizeof(buffer));
					const auto r = CharacterSet::GetUTF32CodePoint(buffer, readSize);
					reader.skip(r.second);
					codePoint = r.first;
				}

				if (codePoint != L'\r')
				{
					detail::PushCodePoint(out, codePoint);
				}
			}
		}
		else
		{
			std::wstring line;

			m_wifReader.seekg(0);

			for (;;)
			{
				if (std::getline(m_wifReader, line).eof())
				{
					m_wifReader.seekg(0, std::ios_base::end);
				}

				out.append(line);

				if (eof())
				{
					break;
				}
				else
				{
					out.push_back(L'\n');
				}
			}
		}
	}

	void TextReader::CTextReader::readLine(String& str)
	{
		str.clear();

		if (!m_opened)
		{
			return;
		}

		if (m_reader)
		{
			for (;;)
			{
				const char32_t codePoint = readChar();

				if (codePoint == L'\n' || codePoint == L'\0')
				{
					break;
				}
				else if (codePoint != L'\r')
				{
					detail::PushCodePoint(str, codePoint);
				}
			}
		}
		else
		{
			if (std::getline(m_wifReader, str.str()).eof())
			{
				m_wifReader.seekg(0, std::ios_base::end);
			}
		}
	}

	char32_t TextReader::CTextReader::readChar()
	{
		for (;;)
		{
			const auto c = readCodePoint();

			if (c != L'\r')
			{
				return c;
			}
		}
	}

	bool TextReader::CTextReader::eof()
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
			return m_wifReader.tellg() == m_size;
		}
	}

	const FilePath& TextReader::CTextReader::path() const
	{
		return m_fullPath;
	}

	CharacterEncoding TextReader::CTextReader::encoding() const
	{
		return m_encoding;
	}

	char32_t TextReader::CTextReader::readCodePoint()
	{
		if (m_encoding == CharacterEncoding::UTF16LE_BOM)
		{
			char16_t c0 = 0, c1 = 0;
			m_reader->read(c0);

			if (IsHighSurrogate(c0))
			{
				m_reader->read(c1);
				return (((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000;
			}

			return c0;
		}
		else if (m_encoding == CharacterEncoding::UTF16BE_BOM)
		{
			char16_t c0 = 0, c1 = 0;
			m_reader->read(c0);
			c0 = ((c0 << 8) & 0xff00) | ((c0 >> 8) & 0xFF);

			if (IsHighSurrogate(c0))
			{
				m_reader->read(c1);
				c1 = ((c1 << 8) & 0xff00) | ((c1 >> 8) & 0xFF);

				return (((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000;
			}

			return c0;
		}
		else if (m_encoding == CharacterEncoding::Unknown)
		{
			wchar ch;
			m_wifReader.get(ch);
			return ch;
		}
		else // UTF-8
		{
			char buffer[6] = {};
			const size_t readSize = m_reader->lookahead(buffer, sizeof(buffer));
			const auto r = CharacterSet::GetUTF32CodePoint(buffer, readSize);
			m_reader->skip(r.second);
			return r.first;
		}
	}
}
