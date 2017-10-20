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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/ByteArray.hpp>
# include "CTextReader.hpp"

# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

std::string ConvertLine(const std::string& line);

# endif

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
				Byte* const buffer = static_cast<Byte*>(::malloc(bufferSize));

				while (sizeToRead)
				{
					const int64 readSize = reader.read(buffer, bufferSize);

					writer.write(buffer, static_cast<size_t>(readSize));

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
			tmpIReader.reset();

		# if defined(SIV3D_TARGET_WINDOWS)
			
			m_ifs.open(path.str());

		# else
			
			m_ifs.open(path.narrow());
			
		# endif

			m_opened = m_ifs.is_open();
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
			
		# if defined(SIV3D_TARGET_WINDOWS)
			
			m_ifs.open(m_temporaryFile->str());
			
		# else
			
			m_ifs.open(m_temporaryFile->narrow());
			
		# endif
			
			m_opened = m_ifs.is_open();
		}

		m_size = m_reader ? m_reader->size() : reader->size();

		m_fullPath = S3DSTR("(Archived File)");

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
			m_ifs.close();
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

			Array<Byte> tmp(static_cast<size_t>(m_reader->size()) - bomSize);
			
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

				if (m_encoding == CharacterEncoding::UTF16LE)
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
				else if (m_encoding == CharacterEncoding::UTF16BE)
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
				else // UTF8, UTF8
				{
					char buffer[6] = {};
					const size_t readSize = static_cast<size_t>(reader.lookahead(buffer, sizeof(buffer)));
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
		# if defined(SIV3D_TARGET_WINDOWS)
			
			std::wstring line;

			m_ifs.seekg(0);

			for (;;)
			{
				if (std::getline(m_ifs, line).eof())
				{
					m_ifs.seekg(0, std::ios_base::end);
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
			
		# else

			std::string line;
			
			m_ifs.seekg(0);

			for (;;)
			{
				if (std::getline(m_ifs, line).eof())
				{
					m_ifs.seekg(0, std::ios_base::end);
				}
				
				out.append(CharacterSet::Widen(ConvertLine(line)));

				if (eof())
				{
					break;
				}
				else
				{
					out.push_back(L'\n');
				}
			}

		# endif
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
		# if defined(SIV3D_TARGET_WINDOWS)
			
			if (std::getline(m_ifs, str.str()).eof())
			{
				m_ifs.seekg(0, std::ios_base::end);
			}
			
		# else
			
			std::string line;
	
			if (std::getline(m_ifs, line).eof())
			{
				m_ifs.seekg(0, std::ios_base::end);
			}
				
			str = CharacterSet::Widen(ConvertLine(line));
			
		# endif
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
			return !m_ifs || m_ifs.tellg() == m_size;
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
		if (m_encoding == CharacterEncoding::UTF16LE)
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
		else if (m_encoding == CharacterEncoding::UTF16BE)
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
		# if defined(SIV3D_TARGET_WINDOWS)
			
			wchar ch = L'\0';
			m_ifs.get(ch);
			return ch;
			
		# else
			
			char ch = '\0';
			m_ifs.get(ch);
			return ch; // [Siv3D TODO]
			
		# endif
		}
		else // UTF-8
		{
			char buffer[6] = {};
			const size_t readSize = static_cast<size_t>(m_reader->lookahead(buffer, sizeof(buffer)));
			const auto r = CharacterSet::GetUTF32CodePoint(buffer, readSize);
			m_reader->skip(r.second);
			return r.first;
		}
	}
}
