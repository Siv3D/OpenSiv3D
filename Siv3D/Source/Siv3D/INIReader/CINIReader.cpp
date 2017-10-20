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
# include "CINIReader.hpp"

namespace s3d
{
	INIReader::CINIReader::CINIReader()
	{

	}

	INIReader::CINIReader::~CINIReader()
	{
		close();
	}

	bool INIReader::CINIReader::open(const FilePath& path, const bool)
	{
		close();

		TextReader textReader(path);

		return load(textReader);
	}

	bool INIReader::CINIReader::open(const std::shared_ptr<IReader>& reader)
	{
		close();

		TextReader textReader(reader);

		return load(textReader);
	}

	void INIReader::CINIReader::close()
	{
		m_sections.clear();

		m_keys.clear();

		m_path.clear();

		m_encoding = CharacterEncoding::Default;
	}

	bool INIReader::CINIReader::isOpened() const
	{
		return !m_keys.isEmpty();
	}

	const FilePath& INIReader::CINIReader::path() const
	{
		return m_path;
	}

	CharacterEncoding INIReader::CINIReader::encoding() const
	{
		return m_encoding;
	}

	const Array<INIReader::Section>& INIReader::CINIReader::getSections() const
	{
		return m_sections;
	}

	const Array<INIKey>& INIReader::CINIReader::getKeys() const
	{
		return m_keys;
	}

	bool INIReader::CINIReader::load(TextReader& reader)
	{
		const wchar semicolon = L';';
		const wchar hash = L'#';
		const wchar lbracket = L'[';
		const wchar rbracket = L']';

		Array<String> namesInCurrentSection;

		String currentSection;
		String line;

		for (size_t currentLine = 1; reader.readLine(line); ++currentLine)
		{
			line.trim();

			if (line.isEmpty())
			{
				continue;
			}

			// Comment
			if (line[0] == semicolon || line[0] == hash)
			{
				continue;
			}

			if (line[0] == lbracket)
			{
				const size_t end = line.indexOf(rbracket);

				if (end == String::npos)
				{
					// error: unmatched '['
					return false;
				}

				String section = line.substr(1, end - 1).trim();

				if (std::find(m_sections.begin(), m_sections.end(), section) != m_sections.end())
				{
					// duplicate section name
					return false;
				}

				currentSection = section;

				m_sections.push_back(std::move(section));

				namesInCurrentSection.clear();
			}
			else
			{
				const size_t eqpos = line.indexOf(L'=');

				if (eqpos == String::npos)
				{
					// error: '=' character not found in line
					return false;
				}

				if (eqpos == 0)
				{
					// error: key expected
					return false;
				}

				String name = line.substr(0, eqpos).trim();

				if (std::find(namesInCurrentSection.begin(), namesInCurrentSection.end(), name) != namesInCurrentSection.end())
				{
					// error: duplicate key name
					return false;
				}

				namesInCurrentSection.push_back(name);

				String value = line.substr(eqpos + 1).trim();

				if (currentSection.isEmpty())
				{
					m_keys.push_back(INIKey{ String(), std::move(name), std::move(value) });
				}
				else
				{
					m_keys.push_back(INIKey{ currentSection, std::move(name), std::move(value) });
				}
			}
		}

		std::sort(m_sections.begin(), m_sections.end());

		std::sort(m_keys.begin(), m_keys.end(), [](const INIKey& a, const INIKey& b)
		{
			const int32 cs = a.section.compare(b.section);

			if (cs < 0)
			{
				return true;
			}
			else if (cs > 0)
			{
				return false;
			}
			else
			{
				return a.name.compare(b.name) < 0;
			}
		});

		m_path = reader.path();

		m_encoding = reader.encoding();

		return true;
	}
}
