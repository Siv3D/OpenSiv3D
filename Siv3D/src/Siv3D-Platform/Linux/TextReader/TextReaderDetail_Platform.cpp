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
# include <TextReader/TextReaderDetail.hpp>

namespace s3d
{
	namespace detail
	{
		static FilePath CreateTemporaryCopy(IReader& reader)
		{
			constexpr size_t bufferSize = 4096;

			const FilePath path = FileSystem::TemporaryDirectoryPath();

			BinaryWriter writer(path);

			if (int64 sizeToRead = reader.size())
			{
				Byte* const buffer = static_cast<Byte*>(std::malloc(bufferSize));

				while (sizeToRead)
				{
					const int64 readSize = reader.read(buffer, bufferSize);

					writer.write(buffer, static_cast<size_t>(readSize));

					sizeToRead -= readSize;
				}

				std::free(buffer);
			}

			return path;
		}

		std::string ConvertLine(const std::string& line)
		{
			// [Siv3D ToDo]
			return line;
		}
	}

	bool TextReader::TextReaderDetail::open(const FilePathView path, const Optional<TextEncoding>& encoding)
	{
		if (m_opened)
		{
			close();
		}

		std::shared_ptr<IReader> tmpIReader = std::make_shared<BinaryReader>(path);

		if (!tmpIReader->isOpen())
		{
			return false;
		}

		if (encoding)
		{
			m_encoding = encoding.value();
		}
		else
		{
			m_encoding = Unicode::GetTextEncoding(*tmpIReader);
		}

		if (m_encoding != TextEncoding::Unknown)
		{
			m_reader = tmpIReader;

			m_opened = m_reader->isOpen();

			if (const size_t bomSize = Unicode::GetBOMSize(m_encoding))
			{
				m_reader->skip(bomSize);
			}
		}
		else
		{
			tmpIReader.reset();

			m_ifs.open(Unicode::Narrow(path));

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

	bool TextReader::TextReaderDetail::open(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding)
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
			m_encoding = Unicode::GetTextEncoding(*reader);
		}

		if (m_encoding != TextEncoding::Unknown)
		{
			m_reader = reader;

			m_opened = m_reader->isOpen();

			if (const size_t bomSize = Unicode::GetBOMSize(m_encoding))
			{
				m_reader->skip(bomSize);
			}
		}
		else
		{
			m_temporaryFile = detail::CreateTemporaryCopy(*reader);

			m_ifs.open(m_temporaryFile->narrow());

			m_opened = m_ifs.is_open();
		}

		m_size = m_reader ? m_reader->size() : reader->size();

		m_fullPath = U"(Archived File)";

		return m_opened;
	}

	void TextReader::TextReaderDetail::readAll(String& out)
	{
		out.clear();

		if (!m_opened)
		{
			return;
		}

		if (m_reader)
		{
			const size_t bomSize = Unicode::GetBOMSize(m_encoding);

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
				char32 codePoint = 0;

				if (m_encoding == TextEncoding::UTF16LE)
				{
					char16 c0 = 0, c1 = 0;
					reader.read(c0);

					if (Unicode::IsHighSurrogate(c0))
					{
						reader.read(c1);
						codePoint = (((c0 - 0xD800) << 10) | (c1 - 0xDC00)) + 0x10000;
					}
					else
					{
						codePoint = c0;
					}
				}
				else if (m_encoding == TextEncoding::UTF16BE)
				{
					char16 c0 = 0, c1 = 0;
					reader.read(c0);
					c0 = ((c0 << 8) & 0xff00) | ((c0 >> 8) & 0xFF);

					if (Unicode::IsHighSurrogate(c0))
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
					char8 buffer[4] = {};
					
					const size_t readSize = static_cast<size_t>(reader.lookahead(buffer, sizeof(buffer)));
					
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
						reader.skip(i + 1);
						codePoint = translator.get();
					}
					else
					{
						reader.skip(readSize);
						codePoint = 0xFFFD;
					}
				}

				if (codePoint != U'\r')
				{
					out.push_back(codePoint);
				}
			}
		}
		else
		{
			std::string line;
			
			m_ifs.seekg(0);

			for (;;)
			{
				if (std::getline(m_ifs, line).eof())
				{
					m_ifs.seekg(0, std::ios_base::end);
				}

				out.append(Unicode::Widen(detail::ConvertLine(line)));

				if (eof())
				{
					break;
				}
				else
				{
					out.push_back(U'\n');
				}
			}
		}
	}

	void TextReader::TextReaderDetail::readLine(String& text)
	{
		text.clear();

		if (!m_opened)
		{
			return;
		}

		if (m_reader)
		{
			for (;;)
			{
				const char32 codePoint = readChar();

				if (codePoint == U'\n' || codePoint == U'\0')
				{
					break;
				}
				else if (codePoint != U'\r')
				{
					text.push_back(codePoint);
				}
			}
		}
		else
		{
			std::string line;

			if (std::getline(m_ifs, line).eof())
			{
				m_ifs.seekg(0, std::ios_base::end);
			}

			text = Unicode::Widen(detail::ConvertLine(line));
		}
	}
}
