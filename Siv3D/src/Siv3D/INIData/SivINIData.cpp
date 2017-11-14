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

# include <Siv3D/INIData.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/TextWriter.hpp>

namespace s3d
{
	namespace detail
	{
		static void WriteNewLine(TextWriter& writer)
		{
			writer.writeUTF8(u8"\r\n");
		}

		static void WriteSection(TextWriter& writer, const INIData::Section& section)
		{
			writer.writeUTF8(u8"[");
			writer.write(section);
			writer.writeUTF8(u8"]");
			WriteNewLine(writer);
		}

		static void WriteValue(TextWriter& writer, const INIData::Name& name, const INIData::Value& value)
		{
			writer.write(name);
			writer.writeUTF8(u8" = ");
			writer.write(value);
			WriteNewLine(writer);
		}
	}

	String& INIData::getValue(const Section& section, const Name& name)
	{
		auto itSection = m_keyIndices.find(section);

		if (itSection != m_keyIndices.end()) // Section が存在
		{
			const size_t sectionIndex = itSection->second.first;

			auto itKey = itSection->second.second.find(name);

			if (itKey != itSection->second.second.end()) // Key が存在
			{
				const size_t keyIndex = itKey->second;

				return m_sections[sectionIndex].keys[keyIndex].value;
			}
			else // Key が存在しない
			{
				m_sections[sectionIndex].keys.emplace_back(name, String());

				const size_t keyIndex = m_sections[sectionIndex].keys.size() - 1;

				itSection.value().second.emplace(name, keyIndex);

				return m_sections[sectionIndex].keys[keyIndex].value;
			}
		}
		else // Section が存在しない
		{
			m_sections.emplace_back(INISection{ section });

			const size_t sectionIndex = m_sections.size() - 1;

			m_sections.back().keys.emplace_back(name, String());

			const size_t keyIndex = 0;

			m_keyIndices.emplace(section, std::pair<size_t, HashTable<Name, size_t>>{ sectionIndex, { { name, keyIndex } }});

			return m_sections[sectionIndex].keys[keyIndex].value;
		}
	}

	bool INIData::loadFromTextReader(TextReader& reader)
	{
		const char32 semicolon	= U';';
		const char32 hash		= U'#';
		const char32 lbracket	= U'[';
		const char32 rbracket	= U']';

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

				const Section section = line.substr(1, end - 1).trim();

				if (auto itSection = m_keyIndices.find(section); itSection == m_keyIndices.end())
				{
					addSection(section);

					currentSection = section;
				}
				else
				{
					// duplicate section name
					return false;
				}
			}
			else
			{
				const size_t eqpos = line.indexOf(U'=');

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

				// add global section
				if (currentSection.isEmpty() && m_sections.isEmpty())
				{
					addSection(Section());
				}

				auto itSection = m_keyIndices.find(currentSection);

				assert(itSection != m_keyIndices.end());

				Name name = line.substr(0, eqpos).trim();

				if (auto itKey = itSection->second.second.find(name); itKey != itSection->second.second.end())
				{
					// error: duplicate key name
					return false;
				}

				auto& keys = m_sections[itSection->second.first].keys;

				itSection.value().second.emplace(name, keys.size());

				keys.emplace_back(std::move(name), line.substr(eqpos + 1).trim());
			}
		}

		return true;
	}

	std::pair<INIData::Section, INIData::Name> INIData::Split(const String& section_and_name)
	{
		const size_t dot = section_and_name.indexOf(L'.');

		if (dot == String::npos)
		{
			return{ String(), section_and_name };
		}
		else
		{
			return{ String(section_and_name.begin(), section_and_name.begin() + dot),
				String(section_and_name.begin() + dot + 1, section_and_name.end()) };
		}
	}

	INIData::INIData()
	{

	}

	INIData::INIData(const FilePath& path)
	{
		load(path);
	}

	INIData::INIData(const std::shared_ptr<IReader>& reader)
	{
		load(reader);
	}

	bool INIData::load(const FilePath& path)
	{
		TextReader textReader(path);

		if (!loadFromTextReader(textReader))
		{
			clear();

			return false;
		}

		return true;
	}

	bool INIData::load(const std::shared_ptr<IReader>& reader)
	{
		TextReader textReader(reader);

		if (!loadFromTextReader(textReader))
		{
			clear();

			return false;
		}

		return true;
	}

	void INIData::clear()
	{
		m_sections.clear();

		m_keyIndices.clear();
	}

	bool INIData::isEmpty() const
	{
		return m_sections.isEmpty();
	}

	bool INIData::hasSection(const Section& section) const
	{
		return m_keyIndices.find(section) != m_keyIndices.end();
	}

	bool INIData::hasValue(const Section& section, const Name& name) const
	{
		if (auto itSection = m_keyIndices.find(section); itSection != m_keyIndices.end()) // Section が存在
		{
			if (itSection->second.second.find(name) != itSection->second.second.end()) // Key が存在
			{
				return true;
			}
		}

		return false;
	}

	bool INIData::hasGlobalValue(const Name& name) const
	{
		return hasValue(Section(), name);
	}

	const Array<INISection>& INIData::sections() const
	{
		return m_sections;
	}

	const INISection& INIData::getSection(const Section& section) const
	{
		if (auto it = m_keyIndices.find(section); it != m_keyIndices.end())
		{
			return m_sections[it->second.first];
		}
		else
		{
			return m_dummySection;
		}
	}

	const String& INIData::getValue(const Section& section, const Name& name) const
	{
		if (auto itSection = m_keyIndices.find(section); itSection != m_keyIndices.end()) // Section が存在
		{
			const size_t sectionIndex = itSection->second.first;

			if (auto itKey = itSection->second.second.find(name); itKey != itSection->second.second.end()) // Key が存在
			{
				const size_t keyIndex = itKey->second;

				return m_sections[sectionIndex].keys[keyIndex].value;
			}
		}

		return m_dummyValue;
	}

	const String& INIData::getGlobalVaue(const Name& name)
	{
		return getValue(Section(), name);
	}

	const INIData::Value& INIData::operator [](const String& section_and_name) const
	{
		const auto[section, name] = Split(section_and_name);

		return getValue(section, name);
	}

	INIValueWrapper INIData::operator [](const String& section_and_name)
	{
		const auto[section, name] = Split(section_and_name);

		return INIValueWrapper(getValue(section, name));
	}

	void INIData::addSection(const Section& section)
	{
		if (hasSection(section))
		{
			return;
		}

		m_sections.push_back(INISection{ section,{} });

		const size_t sectionIndex = m_sections.size() - 1;

		m_keyIndices.emplace(section, std::pair<size_t, HashTable<Name, size_t>>{ sectionIndex, {}});
	}

	void INIData::write(const Section& section, const Name& name, const Value& value)
	{
		getValue(section, name) = value;
	}

	void INIData::writeGlobal(const Name& name, const Value& value)
	{
		write(Section(), name, value);
	}

	bool INIData::save(const FilePath& path) const
	{
		TextWriter writer(path);

		if (!writer)
		{
			return false;
		}

		if (auto itGlobalSection = m_keyIndices.find(Section()); itGlobalSection != m_keyIndices.end())
		{
			const size_t sectionIndex = itGlobalSection->second.first;

			for (const auto& key : m_sections[sectionIndex].keys)
			{
				detail::WriteValue(writer, key.name, key.value);
			}

			detail::WriteNewLine(writer);
		}

		for (const auto& sectionData : m_sections)
		{
			if (!sectionData.section)
			{
				// skip global section
				continue;
			}

			detail::WriteSection(writer, sectionData.section);

			for (const auto& key : sectionData.keys)
			{
				detail::WriteValue(writer, key.name, key.value);
			}

			detail::WriteNewLine(writer);
		}

		return true;
	}
}
